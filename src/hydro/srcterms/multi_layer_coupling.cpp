#include "../../athena.hpp"
#include "../../mesh/mesh.hpp"
#include "../../coordinates/coordinates.hpp"
#include "../hydro.hpp"
#include "hydro_srcterms.hpp"

void HydroSourceTerms::MultiLayerCoupling(const Real dt,const AthenaArray<Real> *flx,
  const AthenaArray<Real> &prim, AthenaArray<Real> &cons)
{ 
  MeshBlock *pmb = pmy_hydro_->pmy_block;
  Coordinates *pcoord = pmb->pcoord;

  for (int k = pmb->ks; k <= pmb->ke; ++k)
    for (int j = pmb->js; j <= pmb->je; ++j) {
      int i1 = pmb->is, i2 = pmb->is+1;
      Real delta = pcoord->dx1f(i2)/pcoord->dx1f(i1);
      cons(IM2,k,j,i1) += - dt*delta*prim(IDN,k,j,i1)*
        (prim(IDN,k,j+1,i2) - prim(IDN,k,j-1,i2))/(pcoord->x2v(j+1) - pcoord->x2v(j-1));
      cons(IM3,k,j,i1) += - dt*delta*prim(IDN,k,j,i1)*
        (prim(IDN,k+1,j,i2) - prim(IDN,k-1,j,i2))/(pcoord->x3v(k+1) - pcoord->x3v(k-1));

      cons(IM2,k,j,i2) += - dt*prim(IDN,k,j,i2)*
        (prim(IDN,k,j+1,i1) - prim(IDN,k,j-1,i1))/(pcoord->x2v(j+1) - pcoord->x2v(j-1));
      cons(IM3,k,j,i2) += - dt*prim(IDN,k,j,i2)*
        (prim(IDN,k+1,j,i1) - prim(IDN,k-1,j,i1))/(pcoord->x3v(k+1) - pcoord->x3v(k-1));
    }

  return;
}
