#include <iostream>
#include <vector>
#include <omp.h>
#include <random>
#include "include/sparse_blas_lib.h"

void read_mtx(const std::string &filename, int &n, std::vector<int> &Ap, std::vector<int> &Ai, std::vector<double> &Ax);
// void read_mtx(const std::string &filename, int &rows, int &cols, std::vector<int> &Ap, std::vector<int> &Ai, std::vector<double> &Ax);
int main() {
    const std::string filename = "nd3k.mtx"; 
    
    int n;
    double r;
    int supernode_size = 100;
    std::vector<int> Ap, Ai;
    std::vector<double> Ax;
    std::vector<double> x(n, 1.0);
    std::vector<double> y(n, 0.0); 
    std::vector<double> z(n, 0.0);
    double a = 2.0; // Example scaling factor for z
    double b = 3.0; // Example scaling factor for y

    read_mtx(filename,n, Ap, Ai, Ax);
        
    for (int i = 0; i < n; ++i) {
        r = ((double) rand() / (RAND_MAX));
        x[i] = r;  
    }
    int nodes = n / supernode_size; 
    std::vector<int> supernodes(nodes + 1);
    for (int i = 0; i <= nodes; ++i) {
        supernodes[i] = i * supernode_size;
    }
    supernodes[nodes] = n;

    //std::cout << "Calling spmv_csr function..." << std::endl;
    // Call the spmv_csr function
    double Stime = omp_get_wtime();
    sym_lib::spmv_csr_block(n, Ap.data(), Ai.data(), Ax.data(), nodes, supernodes.data(), x.data(), y.data());
    std:: cout <<"time taken by block csr is :"<< omp_get_wtime()-Stime;

    // Print the result
    // std::cout << "Result of spmv_csr: ";
    // for (int i = 0; i < rows; ++i) {
    //     std::cout << z[i] << " ";
    // }

    // double Stime = omp_get_wtime();
    // sym_lib::spmv_csr(n, Ap.data(), Ai.data(), Ax.data(), x.data(), y.data());
    // std:: cout <<"time taken by csr is :"<< omp_get_wtime()-Stime;

    return 0;
 }


 