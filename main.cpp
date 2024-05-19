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
    int n_parts = 10;
    std::vector<int> sets(n_parts + 1);
    std::vector<int> ids(n);
    std::vector<int> Ap(n + 1);
    std::vector<int> Ai;
    std::vector<double> Ax;
    std::vector<double> x(n, 1.0);
    std::vector<double> y(n, 0.0); 

    read_mtx(filename,n,n, Ap, Ai, Ax);
        
    for (int i = 0; i < n; ++i) {
        r = ((double) rand() / (RAND_MAX));
        x[i] = r;  
    }

    for (int i = 0; i <= n_parts; i++) {
        sets[i] = i * (n / n_parts);
    }
    sets[n_parts] = n;

    for (int i = 0; i < n; i++) {
        ids[i] = i;
    }

double Stime = omp_get_wtime();
   sym_lib::spmv_csc_lbc(n_parts, sets.data(), ids.data(), n, Ap.data(), Ai.data(), Ax.data(), x.data(), y.data());

    std:: cout <<"time taken by csc is :"<< omp_get_wtime()-Stime;

    return 0;
 }


 