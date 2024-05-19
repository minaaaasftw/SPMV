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
    std::vector<int> Ap, Ai;
    std::vector<double> Ax;
    std::vector<double> x(n, 1.0);
    std::vector<double> y(n, 0.0); 
    std::vector<double> z(n, 0.0);
    std::vector<double> a(n, 2.0); 
    std::vector<double> b(n, 3.0);
    // double a[n] = 2.0; 
    // double b[n] = 3.0;
    read_mtx(filename,n,n, Ap, Ai, Ax);
        
    for (int i = 0; i < n; ++i) {
        r = ((double) rand() / (RAND_MAX));
        x[i] = r;  
    }

    double Stime = omp_get_wtime();
    sym_lib::spmv_csc(n, Ap.data(), Ai.data(), Ax.data(), x.data(), y.data(),z.data(),a.data(),b.data());
    std:: cout <<"time taken by csc is :"<< omp_get_wtime()-Stime;

    return 0;
 }


 