

#include "projetZTrackerParametrisation.hh"

#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4Tubs.hh"

projetZTrackerParametrisation::projetZTrackerParametrisation()
{

  trkTubs_rmax =  110.1*cm;
  trkTubs_rmin =  8.*cm;
  trkTubs_dz   = 13.6*m;
  trkTubs_sphi =   0.*deg;
  trkTubs_dphi = 360.*deg;

  notrkLayers = 13;
  
  tracker_radius[0]  = 8.*cm;
  tracker_radius[1]  = 9.*cm;
  tracker_radius[2]  = 10.*cm;
  tracker_radius[3]  = 20.*cm;
  tracker_radius[4]  = 30.*cm;
  tracker_radius[5]  = 40.*cm;
  tracker_radius[6]  = 50.*cm;
  tracker_radius[7]  = 60.*cm;
  tracker_radius[8]  = 70.*cm;
  tracker_radius[9]  = 80.*cm;
  tracker_radius[10] = 90.*cm;
  tracker_radius[11] = 100.*cm;
  tracker_radius[12] = 110.*cm;
  tracker_thick =  0.1*cm;



}

projetZTrackerParametrisation::~projetZTrackerParametrisation()
{;}

void projetZTrackerParametrisation::ComputeTransformation
(const G4int, G4VPhysicalVolume* physVol) const
{
  G4ThreeVector origin;
  physVol->SetTranslation(origin);
}

void projetZTrackerParametrisation::ComputeDimensions
(G4Tubs& trackerLayer, const G4int copyNo, const G4VPhysicalVolume*) const
{

  trackerLayer.SetInnerRadius(tracker_radius[copyNo]);
  trackerLayer.SetOuterRadius(tracker_radius[copyNo]+tracker_thick);
  trackerLayer.SetZHalfLength(trkTubs_dz);
  trackerLayer.SetStartPhiAngle(trkTubs_sphi,false);
  trackerLayer.SetDeltaPhiAngle(trkTubs_dphi);
}
