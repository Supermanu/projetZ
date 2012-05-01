/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2012  Manuel Tondeur <manueltondeur@gmail.com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#include "projetZCaloParametrisation.hh"
#include "G4VPhysicalVolume.hh"
#include "globals.hh"
#include "G4ThreeVector.hh"
#include "G4Tubs.hh"

projetZCaloParametrisation::projetZCaloParametrisation()
{
    G4int nbreSegmentPhi = 48;    
    G4int nbreSegmentZ = 20;
    G4double caloCell_rmax = 3.0*m;
    G4double caloCell_rmin = 1.5*m;
    G4double caloCell_dz   = 14.*m/nbreSegmentZ;
    G4double caloCell_sphi = 0.*deg;
    G4double caloCell_dphi = 360.*deg/nbreSegmentPhi;
}

projetZCaloParametrisation::~projetZCaloParametrisation()
{}

void projetZCaloParametrisation::ComputeTransformation ( const G4int copyNo, G4VPhysicalVolume* physVol) const
{
    G4ThreeVector origin;
    physVol->SetTranslation(G4ThreeVector(0.,0.,-14.*m +14.*m/20 + int(copyNo/48)*(14.*m/20)));
}

void projetZCaloParametrisation::ComputeDimensions (G4Tubs & calorimeterBlock, const G4int copyNo, const G4VPhysicalVolume* physVol) const
{
    calorimeterBlock.SetInnerRadius(1.5*m);
    calorimeterBlock.SetOuterRadius(3.*m);
    calorimeterBlock.SetZHalfLength(14.*m/20);
    calorimeterBlock.SetStartPhiAngle(copyNo*360.*deg/48);
    calorimeterBlock.SetDeltaPhiAngle(360.*deg/48);
}



