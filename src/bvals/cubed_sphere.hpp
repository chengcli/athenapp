#ifndef CUBED_SPHERE_HPP
#define CUBED_SPHERE_HPP
#include "../athena.hpp"
void TransformOxForCubedSphere(int *ox2, int *ox3, int *tox2, int *tox3,
  LogicalLocation const& loc);

void PackDataCubedSphere(const AthenaArray<Real> &src, Real *buf,
         int sn, int en, int si, int ei, int sj, int ej, int sk, int ek, int &offset,
         int ox1, int ox2, int ox3,LogicalLocation const& loc);

Real CubedSphereMeshGeneratorX2(Real x, LogicalLocation const& loc);
Real CubedSphereMeshGeneratorX3(Real x, LogicalLocation const& loc);

#endif

