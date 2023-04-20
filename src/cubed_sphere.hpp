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


// Helper functions
void GetLatLon(Real *lat, Real *lon, Coordinates *pcoord, int k, int j, int i);
void GetLatLonFace2(Real *lat, Real *lon, Coordinates *pcoord, int k, int j, int i);
void GetLatLonFace3(Real *lat, Real *lon, Coordinates *pcoord, int k, int j, int i);

void GetUV(Real *U, Real *V, Coordinates *pcoord, Real V2, Real V3, int k, int j, int i);
void GetVyVz(Real *V2, Real *V3, Coordinates *pcoord, Real U, Real V, int k, int j, int i);
// Helper functions adapted from Paul
void VecTransABPFromRLL(
	Real X,
	Real Y,
	int blockID,
	Real U,
	Real V,
	Real *V2,
	Real *V3
);
void VecTransRLLFromABP(
	Real X,
	Real Y,
	int blockID,
	Real V2,
	Real V3,
	Real *U,
	Real *V
);
void RLLFromXYP(
	Real dX,
	Real dY,
	int nP,
	Real &lon,
	Real &lat
);
void XYPFromRLL(
	Real lon,
	Real lat,
	Real &dX,
	Real &dY,
	int &nP
);

class GnomonicEquiangle : public Coordinates {
public:
  GnomonicEquiangle(MeshBlock *pmb, ParameterInput *pin, bool flag);
  void Face1Area(const int k, const int j, const int il, const int iu,
                 AthenaArray<Real> &area) final;
  void Face2Area(const int k, const int j, const int il, const int iu,
                 AthenaArray<Real> &area) final;
  void Face3Area(const int k, const int j, const int il, const int iu,
                 AthenaArray<Real> &area) final;

  Real GetFace1Area(const int k, const int j, const int i) final;
  Real GetFace2Area(const int k, const int j, const int i) final;
  Real GetFace3Area(const int k, const int j, const int i) final;

  Real GetVolCenterFace1Area(const int k, const int j, const int i);
  Real GetVolCenterFace2Area(const int k, const int j, const int i);
  Real GetVolCenterFace3Area(const int k, const int j, const int i);

  void VolCenterFace1Area(const int k, const int j, const int il, const int iu,
                          AthenaArray<Real> &area) final;
  void VolCenterFace2Area(const int k, const int j, const int il, const int iu,
                          AthenaArray<Real> &area) final;
  void VolCenterFace3Area(const int k, const int j, const int il, const int iu,
                          AthenaArray<Real> &area) final;
  void CellVolume(const int k, const int j, const int il, const int iu,
                          AthenaArray<Real> &vol);
  Real GetCellVolume(const int k, const int j, const int i);

  void CenterWidth1(const int k, const int j, const int il, const int iu,
                                AthenaArray<Real> &dx1);
  void CenterWidth2(const int k, const int j, const int il, const int iu,
                                AthenaArray<Real> &dx2);
  void CenterWidth3(const int k, const int j, const int il, const int iu,
                                AthenaArray<Real> &dx3);

  void CellMetric(const int k, const int j, const int il, const int iu, AthenaArray<Real> &g, AthenaArray<Real> &g_inv);
  void Face1Metric(const int k, const int j, const int il, const int iu, AthenaArray<Real> &g, AthenaArray<Real> &g_inv);
  void Face2Metric(const int k, const int j, const int il, const int iu, AthenaArray<Real> &g, AthenaArray<Real> &g_inv);
  void Face3Metric(const int k, const int j, const int il, const int iu, AthenaArray<Real> &g, AthenaArray<Real> &g_inv);


  void PrimToLocal2(
        const int k, const int j, const int il, const int iu,
        const AthenaArray<Real> &b1_vals, AthenaArray<Real> &prim_left,
        AthenaArray<Real> &prim_right, AthenaArray<Real> &bx);
  void PrimToLocal3(
        const int k, const int j, const int il, const int iu,
        const AthenaArray<Real> &b1_vals, AthenaArray<Real> &prim_left,
        AthenaArray<Real> &prim_right, AthenaArray<Real> &bx);

  void FluxToGlobal2(
        const int k, const int j, const int il, const int iu,
        const AthenaArray<Real> &cons, const AthenaArray<Real> &bbx,
        AthenaArray<Real> &flux, AthenaArray<Real> &ey, AthenaArray<Real> &ez);
  void FluxToGlobal3(
        const int k, const int j, const int il, const int iu,
        const AthenaArray<Real> &cons, const AthenaArray<Real> &bbx,
        AthenaArray<Real> &flux, AthenaArray<Real> &ey, AthenaArray<Real> &ez);
  void AddCoordTermsDivergence(
    const Real dt, const AthenaArray<Real> *flux,
    const AthenaArray<Real> &prim, const AthenaArray<Real> &bcc, AthenaArray<Real> &u);


  void Edge1Length(const int k, const int j, const int il, const int iu,
      AthenaArray<Real> &len);
  void Edge2Length(const int k, const int j, const int il, const int iu,
      AthenaArray<Real> &len);
  void Edge3Length(const int k, const int j, const int il, const int iu,
      AthenaArray<Real> &len);
  void VolCenter1Length(const int k, const int j, const int il, const int iu,
      AthenaArray<Real> &len);
  void VolCenter2Length(const int k, const int j, const int il, const int iu,
      AthenaArray<Real> &len);
  void VolCenter3Length(const int k, const int j, const int il, const int iu,
      AthenaArray<Real> &len);
  Real GetEdge1Length(const int k, const int j, const int i);
  Real GetEdge2Length(const int k, const int j, const int i);
  Real GetEdge3Length(const int k, const int j, const int i);

};

class AffineCoordinate : public Coordinates {
public:
  AffineCoordinate(MeshBlock *pmb, ParameterInput *pin, bool flag);

  void Face1Area(const int k, const int j, const int il, const int iu,
                 AthenaArray<Real> &area) final;
  void Face2Area(const int k, const int j, const int il, const int iu,
                 AthenaArray<Real> &area) final;
  void Face3Area(const int k, const int j, const int il, const int iu,
                 AthenaArray<Real> &area) final;
  Real GetFace1Area(const int k, const int j, const int i) final;
  Real GetFace2Area(const int k, const int j, const int i) final;
  Real GetFace3Area(const int k, const int j, const int i) final;

  void VolCenterFace1Area(const int k, const int j, const int il, const int iu,
                          AthenaArray<Real> &area) final;
  void VolCenterFace2Area(const int k, const int j, const int il, const int iu,
                          AthenaArray<Real> &area) final;
  void VolCenterFace3Area(const int k, const int j, const int il, const int iu,
                          AthenaArray<Real> &area) final;
  void CellVolume(const int k, const int j, const int il, const int iu,
                          AthenaArray<Real> &vol);
  Real GetCellVolume(const int k, const int j, const int i);

  void CellMetric(const int k, const int j, const int il, const int iu, AthenaArray<Real> &g, AthenaArray<Real> &g_inv);
  void Face1Metric(const int k, const int j, const int il, const int iu, AthenaArray<Real> &g, AthenaArray<Real> &g_inv);
  void Face2Metric(const int k, const int j, const int il, const int iu, AthenaArray<Real> &g, AthenaArray<Real> &g_inv);
  void Face3Metric(const int k, const int j, const int il, const int iu, AthenaArray<Real> &g, AthenaArray<Real> &g_inv);


  void PrimToLocal2(
        const int k, const int j, const int il, const int iu,
        const AthenaArray<Real> &b1_vals, AthenaArray<Real> &prim_left,
        AthenaArray<Real> &prim_right, AthenaArray<Real> &bx);
  void PrimToLocal3(
        const int k, const int j, const int il, const int iu,
        const AthenaArray<Real> &b1_vals, AthenaArray<Real> &prim_left,
        AthenaArray<Real> &prim_right, AthenaArray<Real> &bx);

  void FluxToGlobal2(
        const int k, const int j, const int il, const int iu,
        const AthenaArray<Real> &cons, const AthenaArray<Real> &bbx,
        AthenaArray<Real> &flux, AthenaArray<Real> &ey, AthenaArray<Real> &ez);
  void FluxToGlobal3(
        const int k, const int j, const int il, const int iu,
        const AthenaArray<Real> &cons, const AthenaArray<Real> &bbx,
        AthenaArray<Real> &flux, AthenaArray<Real> &ey, AthenaArray<Real> &ez);
protected:
  Real theta_;
  Real sin_theta_;
  Real cos_theta_;
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

