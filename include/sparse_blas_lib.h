#ifndef SPARSE_BLAS_LIB_H
#define SPARSE_BLAS_LIB_H

#include "aggregation/def.h"

namespace sym_lib {
    void spmv_csr(const int n, const int *Ap, const int *Ai, const double *Ax,
                  const double *x, double *y);

    void spmv_csr(int n, const int *Ap, const int *Ai, const double *Ax,
                  const double *x, const double *y, double *z, double a,
                  double b);

    void spmv_csr_parallel(int n, const int *Ap, const int *Ai, const double *Ax,
                           const double *x, double *y);

    void spmv_csr_block(int n, const int *Ap, const int *Ai, const double *Ax,
                        int nodes, const int *supernodes, const double *x,
                        double *y);

    void spmv_csc(int n, const int *Ap, const int *Ai, const double *Ax,
                  const double *x, double *y);

    void spmv_csc(int n, const int *Ap, const int *Ai, const double *Ax,
                  const double *x, const double *y, double *z, double a,
                  double b);

    void spmv_csc(int n, const int *Ap, const int *Ai, const double *Ax,
                  const double *x, const double *y, double *z, double *a,
                  double *b);

    void spmv_csc_parallel(int n, const int *Ap, const int *Ai, const double *Ax,
                           const double *x, double *y);

    void spmv_csc_lbc(int n_parts, const int *sets, const int *ids,
                      int n, const int *Ap, const int *Ai,
                      const double *Ax, const double *x, double *y);

    void spmv_csc_lbc(const int *set_ptr, const int *sets, const int *ids,
                      int n, const int *Ap, const int *Ai,
                      const double *Ax, const double *x, double *y);

    void spmv_csc_block(int n, const int *Ap, const int *Ai, const double *Ax,
                        const double *x, double *y, int nodes,
                        const int *supernodes);

    int BandedMatrixVectorMult(const double **d, const double *v,
                               const int dNum, const int row,
                               double *&result);





}
#endif  //FUSION_SPARSEBLASLIB_H