#include <Rcpp.h>

using Rcpp::NumericMatrix;
using Rcpp::NumericVector;

// [[Rcpp::export]]
NumericMatrix row_col_dot_matmat(
    const NumericMatrix& A, const NumericMatrix& B
  ) {
  if (A.ncol() != B.nrow()) {
    Rcpp::stop("Incompatible dimensions");
  }
  int n_row_out = A.nrow();
  int n_col_out = B.ncol();
  NumericMatrix result(n_row_out, n_col_out);
  // Fill in; remember to use (,) instead of [,] for accessing matrix elements
  for (int i = 0; i < n_row_out; ++i) {
    for (int j = 0; j < n_col_out; ++j){
      result(i, j) = 0;
      for (int q = 0; q < A.ncol(); ++q){
        result(i, j) += A(i, q) * B(q, j);
      }
    }
  }
  return result;
}

// [[Rcpp::export]]
NumericMatrix col_oriented_matmat(
    const NumericMatrix& A, const NumericMatrix& B
  ) {
  if (A.ncol() != B.nrow()) {
    Rcpp::stop("Incompatible dimensions");
  }
  int n_row_out = A.nrow();
  int n_row_A = A.ncol();
  int n_col_out = B.ncol();
  NumericMatrix result(n_row_out, n_col_out);
  for (int j = 0; j < n_col_out; ++j) {
    // Calculate result[, j] = A %*% B[, j] in column-oriented manner for each j
    // Fill in
    NumericVector b = B(Rcpp::_, j);
    for (int i = 0; i < n_row_A; ++i){
      for (int q = 0; q < n_row_out; ++q){
        result(q, j) += A(q, i) * b[i];
      }
    }
  }
  return result;
}
