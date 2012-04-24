

#include "projetZTrackerParametrisation.hh"

#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4Tubs.hh"

projetZTrackerParametrisation::projetZTrackerParametrisation()
{

#include "projetZTrackerParameterDef.icc"

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
  trackerLayer.SetZHalfLength(tracker_length[copyNo]);
  trackerLayer.SetStartPhiAngle(trkTubs_sphi,false);
  trackerLayer.SetDeltaPhiAngle(trkTubs_dphi);
}
