// Athena++ headers
#include "../athena.hpp"
#include "../athena_arrays.hpp"
#include "../hydro/hydro.hpp"
#include "../mesh/mesh.hpp"
#include "reconstruction.hpp"
#include "interpolation.hpp"

void Reconstruction::Weno5X1(const int k, const int j, const int il, const int iu,
  const AthenaArray<Real> &w, AthenaArray<Real> &wl, AthenaArray<Real> &wr)
{
  for (int n=0; n<w.GetDim4(); ++n) 
#pragma omp simd
    for (int i=il; i<=iu; ++i) {
      wl(n,i+1) = interp_weno5(w(n,k,j,i+2),w(n,k,j,i+1),w(n,k,j,i),w(n,k,j,i-1),w(n,k,j,i-2));
      wr(n,i) = interp_weno5(w(n,k,j,i-2),w(n,k,j,i-1),w(n,k,j,i),w(n,k,j,i+1),w(n,k,j,i+2));
    }

  return;
}

void Reconstruction::Weno5X2(const int k, const int j, const int il, const int iu,
  const AthenaArray<Real> &w, AthenaArray<Real> &wl, AthenaArray<Real> &wr)
{
  for (int n=0; n<w.GetDim4(); ++n)
#pragma omp simd
    for (int i=il; i<=iu; ++i) {
      wl(n,i) = interp_weno5(w(n,k,j+2,i),w(n,k,j+1,i),w(n,k,j,i),w(n,k,j-1,i),w(n,k,j-2,i));
      wr(n,i) = interp_weno5(w(n,k,j-2,i),w(n,k,j-1,i),w(n,k,j,i),w(n,k,j+1,i),w(n,k,j+2,i));
    }

  return;
}

void Reconstruction::Weno5X3(const int k, const int j, const int il, const int iu,
  const AthenaArray<Real> &w, AthenaArray<Real> &wl, AthenaArray<Real> &wr)
{
  for (int n=0; n<w.GetDim4(); ++n)
#pragma omp simd
    for (int i=il; i<=iu; ++i) {
      wl(n,i) = interp_weno5(w(n,k+2,j,i),w(n,k+1,j,i),w(n,k,j,i),w(n,k-1,j,i),w(n,k-2,j,i));
      wr(n,i) = interp_weno5(w(n,k-2,j,i),w(n,k-1,j,i),w(n,k,j,i),w(n,k+1,j,i),w(n,k+2,j,i));
    }

  return;
}
