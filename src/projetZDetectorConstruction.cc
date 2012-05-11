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
// $Id: projetZDetectorConstruction.cc,v 1.9 2006-06-29 17:47:19 gunter Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//


#include "projetZDetectorConstruction.hh"
#include "projetZCaloSD.hh"
#include "projetZTrackerSD.hh"
#include "projetZTrackerParametrisation.hh"
#include "projetZCaloParametrisation.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4VSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4SDManager.hh"
#include "globals.hh"
#include <string>
#include "G4String.hh"
#include "G4UniformMagField.hh"
#include "G4TransportationManager.hh"
#include "G4FieldManager.hh"
#include "G4Color.hh"
#include "G4PVParameterised.hh"

projetZDetectorConstruction::projetZDetectorConstruction()
    :  WorldVolume_log ( 0 ), tracker_log ( 0 ),
       calorimeterBlock_log ( 0 ),
       World_Volume ( 0 ),calorimeterBlock_phys ( 0 ), tracker_phys ( 0 )
{
    SetMagField(4.*tesla);
}

projetZDetectorConstruction::~projetZDetectorConstruction()
{

}

G4VPhysicalVolume* projetZDetectorConstruction::Construct()
{

    //------------------------------------------------------ materials

    G4double a;  // atomic mass
    G4double z;  // atomic number
    G4double density;
    G4double temperature;
    G4double pressure;
    G4String name, symbole;
    G4int nel;
    
    G4Element* elI = new G4Element(name="Iodine",   symbole="I",  z = 53., a = 126.9*g/mole);
    a = 132.9*g/mole;
    G4Element* elCs= new G4Element(name="Cesium",   symbole="Cs", z = 55., a = 132.9*g/mole);
    
    G4Material* CsI = new G4Material(name="CsI", density=4.51*g/cm3, nel = 2);
    CsI->AddElement(elI, .5);
    CsI->AddElement(elCs,.5);

    //Air
  G4Element* N = new G4Element("Nitrogen", "N", z=7., a= 14.01*g/mole);
  G4Element* O = new G4Element("Oxygen"  , "O", z=8., a= 16.00*g/mole);
   
  G4Material* Air = new G4Material("Air", density= 1.29*mg/cm3, nel=2);
  Air->AddElement(N, 70*perCent);
  Air->AddElement(O, 30*perCent);


    G4Material* Si = new G4Material ( "Silicon", z=14., a= 28.09*g/mole, density= 2.33*g/cm3 );
    //------------------------------------------------------ volumes

    //------------------------------ experimental hall (world volume)


    G4Box* WorldSolid = new G4Box ( "World_Volume_solid",10.*m,10.*m,15.*m );

    WorldVolume_log = new G4LogicalVolume ( WorldSolid, Air,"World_Volume_log",0,0,0 ); // fill the solid with "Air"
    World_Volume = new G4PVPlacement ( 0,G4ThreeVector(),WorldVolume_log,"World_Volume",0,false,0 ); // raises it to physical volume

    //------------------------------ a tracker tube
    G4double trkTubs_rmin = 8.*cm;
    G4double trkTubs_rmax = 110.1*cm;
    G4double trkTubs_dz = 13.6*m;
    G4double trkTubs_sphi = 0.*deg;
    G4double trkTubs_dphi = 360.*deg;
    
    G4VSolid * tracker_tubs = new G4Tubs("trkTubs_tubs",trkTubs_rmin,trkTubs_rmax,trkTubs_dz, trkTubs_sphi,trkTubs_dphi);
    G4LogicalVolume * tracker_log = new G4LogicalVolume(tracker_tubs,Air,"trackerT_L",0,0,0);
    G4VPhysicalVolume * tracker_phys =    new G4PVPlacement(0,G4ThreeVector(),tracker_log,"tracker_phys",WorldVolume_log,false,0);
    G4VisAttributes* tracker_logVisAtt = new G4VisAttributes(G4Colour(1.0,0.0,1.0));
     tracker_logVisAtt->SetVisibility(false);
    tracker_log->SetVisAttributes(tracker_logVisAtt);

     G4VSolid * trackerLayer_tubs  = new G4Tubs("trkTubs_tubs",trkTubs_rmin,trkTubs_rmin+1.*mm,trkTubs_dz, trkTubs_sphi,trkTubs_dphi);
     G4LogicalVolume * trackerLayer_log = new G4LogicalVolume(trackerLayer_tubs,Si,"trackerB_L",0,0,0);
     G4VPVParameterisation * trackerParam = new projetZTrackerParametrisation;
     new G4PVParameterised("trackerLayer_phys",trackerLayer_log,tracker_log,kUndefined, 13, trackerParam);
     G4VisAttributes* trackerLayer_logVisAtt = new G4VisAttributes(G4Colour(0.5,0.0,1.0));
     trackerLayer_logVisAtt->SetForceWireframe(true);
     trackerLayer_logVisAtt->SetVisibility(false);
     trackerLayer_log->SetVisAttributes(trackerLayer_logVisAtt);
    

    //------------------------------ Le calorimètre

     G4SDManager* SDman = G4SDManager::GetSDMpointer(); // On initialise le manager Sensitive Detector
     
    G4double innerRadiusOfTheCalo = 1.5*m;
    G4double outerRadiusOfTheCalo = 3.*m;
    G4double hightOfTheCalo = 14.*m;

    G4double startAngleOfTheCalo = 0.*deg;
    G4double spanningAngleOfTheCalo = 360.*deg;
    G4Tubs* calorimeterBlock_tube = new G4Tubs ( "caloTube",innerRadiusOfTheCalo,outerRadiusOfTheCalo,hightOfTheCalo,startAngleOfTheCalo,spanningAngleOfTheCalo );
    calorimeterBlock_log = new G4LogicalVolume ( calorimeterBlock_tube,Air,"calo_log",0,0,0 );
    calorimeterBlock_phys = new G4PVPlacement ( 0,G4ThreeVector(),calorimeterBlock_log, "calo_phys",WorldVolume_log,false,0 );
    G4VisAttributes* caloBlock_logVisAtt = new G4VisAttributes(G4Color(1.0,1.0,1.0));
    calorimeterBlock_log->SetVisAttributes(caloBlock_logVisAtt);
    
    G4VSolid* caloCell_tubs = new G4Tubs("caloCell_tubs",innerRadiusOfTheCalo,outerRadiusOfTheCalo,hightOfTheCalo/20 ,0.*deg,360.*deg/40);
    G4LogicalVolume* caloCell_log = new G4LogicalVolume(caloCell_tubs,CsI,"caloCell_log",0,0,0);
    G4VPVParameterisation* calorimeterParam = new projetZCaloParametrisation;
    new G4PVParameterised("caloCell_phys",caloCell_log,calorimeterBlock_log,kUndefined, 40*20*2 - 40, calorimeterParam);
    G4VisAttributes* caloCell_logVisAtt = new G4VisAttributes(G4Colour(1.0,1.0,1.0));
    caloCell_logVisAtt->SetVisibility(false);
    caloCell_log->SetVisAttributes(caloCell_logVisAtt);

    //------------------------------- Détecteur sensible
    
   
    
    // Calorimètre
    G4String caloDetectSDname = "projetZ/caloDetectSD"; 
    projetZCaloSD* aCaloSD = new projetZCaloSD(caloDetectSDname);
    SDman->AddNewDetector(aCaloSD);
    caloCell_log->SetSensitiveDetector(aCaloSD);
    // Trackeur
    G4String trackerSDname = "projetZ/trackerDetectSD";
    projetZTrackerSD* trackerSD = new projetZTrackerSD(trackerSDname);
    SDman->AddNewDetector(trackerSD);
    trackerLayer_log->SetSensitiveDetector(trackerSD);
    

    return World_Volume;
}

void projetZDetectorConstruction::SetMagField(G4double fieldValue)
{
    G4UniformMagField* magField = new G4UniformMagField(G4ThreeVector(0.,0.,fieldValue));
    G4FieldManager* fieldMgr = G4TransportationManager::GetTransportationManager()->GetFieldManager();
    fieldMgr->SetDetectorField(magField);
    fieldMgr->CreateChordFinder(magField);
}
