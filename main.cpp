#include <iostream>
#include <vector>
#include <omp.h>
#include <random>
#include "include/sparse_blas_lib.h"

//void read_mtx(const std::string &filename, int &n, std::vector<int> &Ap, std::vector<int> &Ai, std::vector<double> &Ax);
 void read_mtx(const std::string &filename, int &rows, int &cols, std::vector<int> &Ap, std::vector<int> &Ai, std::vector<double> &Ax);
int main() {
    const std::string filename = "nd3k.mtx"; 
    
    int n;
    double r;
    std::vector<int> Ap(n);
    std::vector<int> Ai;
    std::vector<double> Ax;
    std::vector<double> x(n, 1.0);
    std::vector<double> y(n, 0.0); 

    read_mtx(filename,n,n, Ap, Ai, Ax);
        
    int supernode_size = 100; 
    int nodes = supernode_size - 1;
    std::vector<int> supernodes(nodes + 1);
    for (int i = 0; i <= nodes; i++) {
        supernodes[i] = i * supernode_size;
    }
    supernodes[nodes] = n;

   double Stime = omp_get_wtime();
   sym_lib::spmv_csc_block(n, Ap.data(), Ai.data(), Ax.data(), x.data(), y.data(), nodes, supernodes.data());
   std:: cout <<"time taken by csc block is :"<< omp_get_wtime()-Stime;

    return 0;
 }


 