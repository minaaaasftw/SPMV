#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdexcept>

void read_mtx(const std::string &filename, int &n, std::vector<int> &Ap, std::vector<int> &Ai, std::vector<double> &Ax) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }

    std::string line;

    while (std::getline(file, line)) {
        if (line[0] == '%') continue; 
        break; 
    }

    std::istringstream iss(line);
    int rows, cols, nonzeros;
    if (!(iss >> rows >> cols >> nonzeros)) {
        std::cerr << "Error parsing header: " << line << std::endl;
        throw std::runtime_error("Error parsing header");
    }

    if (rows <= 0 || cols <= 0 || nonzeros <= 0) {
        std::cerr << "Invalid matrix dimensions or non-zero entries: " << rows << " " << cols << " " << nonzeros << std::endl;
        throw std::runtime_error("Invalid matrix dimensions or non-zero entries");
    }

    n = rows;
    Ap.resize(cols + 1, 0);
    std::vector<std::vector<std::pair<int, double> > > data(cols);

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        int row, col;
        double value;
        if (!(iss >> row >> col >> value)) {
            std::cerr << "Error parsing line: " << line << std::endl;
            continue;
        }
        row--; 
        col--; 
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            std::cerr << "Index out of bounds: row = " << row << ", col = " << col << std::endl;
            continue;
        }
        data[col].emplace_back(row, value);
    }

    for (int col = 0; col < cols; ++col) {
        Ap[col + 1] = Ap[col] + data[col].size();
        for (const auto &entry : data[col]) {
            Ai.push_back(entry.first);
            Ax.push_back(entry.second);
        }
    }

    // std::cout << "Matrix loaded with " << rows << " rows, " << cols << " columns, and " << nonzeros << " nonzeros.\n";
    // std::cout << "Ap: ";
    // for (int i = 0; i < Ap.size(); ++i) std::cout << Ap[i] << " ";
    // std::cout << "\nAi: ";
    // for (int i = 0; i < Ai.size(); ++i) std::cout << Ai[i] << " ";
    // std::cout << "\nAx: ";
    // for (int i = 0; i < Ax.size(); ++i) std::cout << Ax[i] << " ";
    // std::cout << "\n";
}
