// Athena++ headers
#include "../athena.hpp"
#include "../athena_arrays.hpp"
#include "../hydro/hydro.hpp"
#include "../mesh/mesh.hpp"
#include "reconstruction.hpp"
#include "interpolation.hpp"

void Reconstruction::Weno3X1(const int k, const int j, const int il, const int iu,
  const AthenaArray<Real> &w, const AthenaArray<Real> &bcc,
  AthenaArray<Real> &wl, AthenaArray<Real> &wr)
{
  for (int n=0; n<(NHYDRO); ++n) {
#pragma omp simd
    for (int i=il; i<=iu; ++i){
      wl(n,i) = interp_weno3(w(n,k,j,i+1), w(n,k,j,i), w(n,k,j,i-1));
      wr(n,i) = interp_weno3(w(n,k,j,i-1), w(n,k,j,i), w(n,k,j,i+1));
    }
  }

  return;
}

void Reconstruction::Weno3X2(const int k, const int j, const int il, const int iu,
  const AthenaArray<Real> &w, const AthenaArray<Real> &bcc,
  AthenaArray<Real> &wl, AthenaArray<Real> &wr)
{
  for (int n=0; n<(NHYDRO); ++n) {
#pragma omp simd
    for (int i=il; i<=iu; ++i){
      wl(n,i) = interp_weno3(w(n,k,j+1,i), w(n,k,j,i), w(n,k,j-1,i));
      wr(n,i) = interp_weno3(w(n,k,j-1,i), w(n,k,j,i), w(n,k,j+1,i));
    }
  }

  return;
}

void Reconstruction::Weno3X3(const int k, const int j, const int il, const int iu,
  const AthenaArray<Real> &w, const AthenaArray<Real> &bcc,
  AthenaArray<Real> &wl, AthenaArray<Real> &wr)
{
  for (int n=0; n<NHYDRO; ++n) {
#pragma omp simd
    for (int i=il; i<=iu; ++i){
      wl(n,i) = interp_weno3(w(n,k+1,j,i), w(n,k,j,i), w(n,k-1,j,i));
      wr(n,i) = interp_weno3(w(n,k-1,j,i), w(n,k,j,i), w(n,k+1,j,i));
    }
  }

  return;
}
