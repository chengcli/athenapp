#ifndef CUBED_SPHERE_HPP
#define CUBED_SPHERE_HPP
#include "athena.hpp"
#include "coordinates/coordinates.hpp"

int FindBlockID(LogicalLocation const& loc);

void TransformOxForCubedSphere(int *ox2, int *ox3, int *tox2, int *tox3,
  LogicalLocation const& loc);

void PackDataCubedSphere(const AthenaArray<Real> &src, Real *buf,
         int sn, int en, int si, int ei, int sj, int ej, int sk, int ek, int &offset,
         int ox1, int ox2, int ox3,LogicalLocation const& loc);

void ProjectLocalCartesianAffine(const AthenaArray<Real> &src, 
        AthenaArray<Real> &tgt, Real affine_angle, int sn, int en, int si, int ei, int sj, 
        int ej, int sk, int ek, int Dir);

void DeProjectLocalCartesianAffine(AthenaArray<Real> &flux, 
        Real affine_angle, int sn, int en, int si, int ei, int sj, int ej, int sk, int ek, int Dir);

Real CubedSphereMeshGeneratorX2(Real x, LogicalLocation const& loc);
Real CubedSphereMeshGeneratorX3(Real x, LogicalLocation const& loc);

class GnomonicEquiangle : public Coordinates {
public:
  GnomonicEquiangle(MeshBlock *pmb, ParameterInput *pin, bool flag);
};

class AffineCoordinate : public Coordinates {
public:
  AffineCoordinate(MeshBlock *pmb, ParameterInput *pin, bool flag);

  // ...to compute area of faces
  void Face1Area(const int k, const int j, const int il, const int iu,
                 AthenaArray<Real> &area) final;
  void Face2Area(const int k, const int j, const int il, const int iu,
                 AthenaArray<Real> &area) final;
  void Face3Area(const int k, const int j, const int il, const int iu,
                 AthenaArray<Real> &area) final;
  Real GetFace1Area(const int k, const int j, const int i) final;
  Real GetFace2Area(const int k, const int j, const int i) final;
  Real GetFace3Area(const int k, const int j, const int i) final;
  // ...to compute area of faces joined by cell centers (for non-ideal MHD)
  void VolCenterFace1Area(const int k, const int j, const int il, const int iu,
                          AthenaArray<Real> &area) final;
  void VolCenterFace2Area(const int k, const int j, const int il, const int iu,
                          AthenaArray<Real> &area) final;
  void VolCenterFace3Area(const int k, const int j, const int il, const int iu,
                          AthenaArray<Real> &area) final;
  void CellVolume(const int k, const int j, const int il, const int iu,
                          AthenaArray<Real> &vol);
  Real GetCellVolume(const int k, const int j, const int i);

};

class CubedSphereLR{
  public:
    void SetMeshBlock(MeshBlock *pmb_in);
    void InitializeSizes(int nc3, int nc2, int nc1);
    void SaveLR3DValues(AthenaArray<Real> &L_in, AthenaArray<Real> &R_in, int direction, int k, int j, int il, int iu);
    void LoadLR3DValues(AthenaArray<Real> &L_in, AthenaArray<Real> &R_in, int direction, int k, int j, int il, int iu);
    void SynchronizeFluxes();
    void SendNeighborBlocks(LogicalLocation const& loc, int ox2, int ox3, int tg_rank, int tg_gid);
    void RecvNeighborBlocks(LogicalLocation const& loc, int ox2, int ox3, int tg_rank, int tg_gid);

    AthenaArray<Real> L3DValues, R3DValues;
    MeshBlock *pmb;
};

#endif

