
#ifndef projetZTrackerParametrisation_H
#define projetZTrackerParametrisation_H 1

#include "globals.hh"
#include "G4VPVParameterisation.hh"

class G4VPhysicalVolume;
class G4Tubs;

// Dummy declarations to get rid of warnings ...
class G4Trd;
class G4Trap;
class G4Cons;
class G4Orb;
class G4Sphere;
class G4Torus;
class G4Para;
class G4Hype;
class G4Box;
class G4Polycone;
class G4Polyhedra;

class projetZTrackerParametrisation : public G4VPVParameterisation
{
public:

    projetZTrackerParametrisation();
    virtual ~projetZTrackerParametrisation();
    void ComputeTransformation ( const G4int copyNo,
                                 G4VPhysicalVolume *physVol ) const;
    void ComputeDimensions ( G4Tubs & trackerLayer,
                             const G4int copyNo,
                             const G4VPhysicalVolume * physVol ) const;

private:  // Dummy declarations to get rid of warnings ...

    void ComputeDimensions ( G4Trd&,const G4int,const G4VPhysicalVolume* ) const {}
    void ComputeDimensions ( G4Trap&,const G4int,const G4VPhysicalVolume* ) const {}
    void ComputeDimensions ( G4Cons&,const G4int,const G4VPhysicalVolume* ) const {}
    void ComputeDimensions ( G4Orb&,const G4int,const G4VPhysicalVolume* ) const {}
    void ComputeDimensions ( G4Sphere&,const G4int,const G4VPhysicalVolume* ) const {}
    void ComputeDimensions ( G4Torus&,const G4int,const G4VPhysicalVolume* ) const {}
    void ComputeDimensions ( G4Para&,const G4int,const G4VPhysicalVolume* ) const {}
    void ComputeDimensions ( G4Hype&,const G4int,const G4VPhysicalVolume* ) const {}
    void ComputeDimensions ( G4Box&,const G4int,const G4VPhysicalVolume* ) const {}
    void ComputeDimensions ( G4Polycone&,const G4int,const G4VPhysicalVolume* ) const {}
    void ComputeDimensions ( G4Polyhedra&,const G4int,const G4VPhysicalVolume* ) const {}

private:

    G4double tracker_radius[13] ;
    G4double trkTubs_rmax;
    G4double trkTubs_rmin;
    G4double trkTubs_dz;
    G4double trkTubs_sphi;
    G4double trkTubs_dphi;
    G4double tracker_thick;
    G4double tracker_length[13];
    G4int notrkLayers;

};

#endif
