/***
 * @file mahalanobis_distance.cc
 * @author Ryan Curtin
 *
 * Implementation of the Mahalanobis distance.
 */
#ifndef __MLPACK_CORE_KERNELS_MAHALANOBIS_DISTANCE_IMPL_H
#define __MLPACK_CORE_KERNELS_MAHALANOBIS_DISTANCE_IMPL_H

#include "mahalanobis_distance.h"

namespace mlpack {
namespace kernel {

/**
 * Specialization for non-rooted case.
 */
template<>
double MahalanobisDistance<false>::Evaluate(const arma::vec& a,
                                            const arma::vec& b) {
  // Check if covariance matrix has been initialized.
  if (covariance_.n_rows == 0)
    covariance_ = arma::eye<arma::mat>(a.n_elem, a.n_elem);

  arma::vec m = (a - b);
  arma::mat out = trans(m) * covariance_ * m; // 1x1
  return out[0];
}

/**
 * Specialization for rooted case.  This requires one extra evaluation of
 * sqrt().
 */
template<>
double MahalanobisDistance<true>::Evaluate(const arma::vec& a,
                                           const arma::vec& b) {
  // Check if covariance matrix has been initialized.
  if (covariance_.n_rows == 0)
    covariance_ = arma::eye<arma::mat>(a.n_elem, a.n_elem);

  arma::vec m = (a - b);
  arma::mat out = trans(m) * covariance_ * m; // 1x1;
  return sqrt(out[0]);
}

};
};

#endif