#ifndef CUBED_SPHERE_HPP
#define CUBED_SPHERE_HPP

void TransformOxForCubedSphere(int *ox1, int *ox2, int *tox1, int *tox2,
  LogicalLocation const& loc);

void PackDataCubedSphere(const AthenaArray<Real> &src, Real *buf,
         int sn, int en, int si, int ei, int sj, int ej, int sk, int ek, int &offset,
         int ox2, int ox3,LogicalLocation const& loc);
#endif
