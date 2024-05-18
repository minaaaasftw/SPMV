#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdexcept>

struct Entry {
    int row;
    int col;
    double value;
    Entry(int r, int c, double v) : row(r), col(c), value(v) {}
};

void read_mtx(const std::string &filename, int &rows, int &cols, std::vector<int> &Ap, std::vector<int> &Ai, std::vector<double> &Ax) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    std::string line;

    // Skip comments
    while (std::getline(file, line)) {
        if (line[0] != '%') break;
    }

    std::istringstream header(line);
    int nonzeros;
    if (!(header >> rows >> cols >> nonzeros)) {
        std::cerr << "Error parsing header: " << line << std::endl;
        throw std::runtime_error("Error parsing header");
    }

    if (rows <= 0 || cols <= 0 || nonzeros <= 0) {
        std::cerr << "Invalid matrix dimensions or non-zero entries: " << rows << " " << cols << " " << nonzeros << std::endl;
        throw std::runtime_error("Invalid matrix dimensions or non-zero entries");
    }

    Ap.resize(cols + 1, 0);
    Ai.resize(nonzeros);
    Ax.resize(nonzeros);

    std::vector<int> col_counts(cols, 0);
    std::vector<Entry> entries;

    // First pass: read entries and count the entries in each column
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int row, col;
        double value;
        if (!(iss >> row >> col >> value)) {
            std::cerr << "Error parsing line: " << line << std::endl;
            continue;
        }
        row--; // Convert to 0-based index
        col--; // Convert to 0-based index
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            std::cerr << "Index out of bounds: row = " << row << ", col = " << col << std::endl;
            continue;
        }
        col_counts[col]++;
        entries.push_back(Entry(row, col, value));
    }

    // Fill the column pointers array
    for (int col = 0; col < cols; ++col) {
        Ap[col + 1] = Ap[col] + col_counts[col];
    }

    // Second pass: fill Ai and Ax
    std::vector<int> current_pos = Ap;
    for (const auto& entry : entries) {
        int row = entry.row;
        int col = entry.col;
        double value = entry.value;

        int pos = current_pos[col]++;
        Ai[pos] = row;
        Ax[pos] = value;
    }
}
