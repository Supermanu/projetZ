//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id: projetZDetectorConstruction.hh,v 1.6 2006-06-29 17:47:13 gunter Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//

#ifndef projetZDetectorConstruction_H
#define projetZDetectorConstruction_H 1

class G4LogicalVolume;
class G4VPhysicalVolume;
class G4Material;
class G4Element;

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class projetZDetectorConstruction : public G4VUserDetectorConstruction
{
public:

    projetZDetectorConstruction();
    ~projetZDetectorConstruction();

    G4VPhysicalVolume* Construct();

private:

    // Logical volumes
    //
    G4LogicalVolume* WorldVolume_log;
    G4LogicalVolume* tracker_log;
    G4LogicalVolume* calorimeterBlock_log;
    G4LogicalVolume* calorimeterLayer_log;

    // Physical volumes
    //
    G4VPhysicalVolume* World_Volume;
    G4VPhysicalVolume* calorimeterBlock_phys;
    G4VPhysicalVolume* tracker;
    
    // Eléments et matériaux
    //
    G4Material* CsI;
    G4Material* Vacuum;
    G4Material* Si;
  
    G4Element* elI;
    G4Element* elCs;
};

#endif

