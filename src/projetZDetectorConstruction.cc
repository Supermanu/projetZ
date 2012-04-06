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

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4SDManager.hh"
#include "globals.hh"
#include <string>
#include "G4String.hh"

projetZDetectorConstruction::projetZDetectorConstruction()
    :  WorldVolume_log ( 0 ), tracker_log ( 0 ),
       calorimeterBlock_log ( 0 ), calorimeterLayer_log ( 0 ),
       World_Volume ( 0 ),calorimeterBlock_phys ( 0 ), tracker ( 0 )
{
    ;
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

    G4Material* Ar =
        new G4Material ( "ArgonGas", z= 18., a= 39.95*g/mole, density= 1.782*mg/cm3 );

    G4Material* Al =
        new G4Material ( "Aluminum", z= 13., a= 26.98*g/mole, density= 2.7*g/cm3 );

    G4Material* Pb =
        new G4Material ( "Lead", z= 82., a= 207.19*g/mole, density= 11.35*g/cm3 );

    // Ajout du vide (nitrogen ~70%) et du silicium
    G4Material* Vacuum =
        new G4Material ( "Vacuum", z = 7, a = 14.0067*g/mole, density = 1.e-25*g/cm3, kStateGas, temperature = 2.73*kelvin, pressure  = 3.e-18*pascal );

    G4Material* Si = new G4Material ( "Silicon", z=14., a= 28.09*g/mole, density= 2.33*g/cm3 );
    //------------------------------------------------------ volumes

    //------------------------------ experimental hall (world volume)

    G4double innerRadiusOfTheTube = 0.*m;
    G4double outerRadiusOfTheTube = 20.*m;
    G4double hightOfTheTube = 12.5*m;     //half length of the tube
    G4double startAngleOfTheTube = 0.*deg;
    G4double spanningAngleOfTheTube = 360.*deg;

    G4Tubs* WorldSolid = new G4Tubs ( "World_Volume_solid",innerRadiusOfTheTube,outerRadiusOfTheTube,hightOfTheTube,startAngleOfTheTube,spanningAngleOfTheTube );

    WorldVolume_log = new G4LogicalVolume ( WorldSolid, Vacuum,"World_Volume_log",0,0,0 ); // fill the solid with "Vacuum"
    World_Volume = new G4PVPlacement ( 0,G4ThreeVector(),WorldVolume_log,"World_Volume",0,false,0 ); // raises it to physical volume

    //------------------------------ a tracker tube

    int const nbTracker=13;
    G4int Iradii[nbTracker]= {8*cm,9*cm,10*cm,20*cm,30*cm,40*cm,50*cm,60*cm,70*cm,80*cm,90*cm,100*cm,110*cm};
    G4int Oradii[nbTracker]= {8.1*cm,9.1*cm,10.1*cm,20.1*cm,30.1*cm,40.1*cm,50.1*cm,60.1*cm,70.1*cm,80.1*cm,90.1*cm,100.1*cm,110.1*cm};
    int const nbSteps=3;

    std::string namesTracker[nbSteps][nbTracker] =
    {"t1s","t2s","t3s","t4s","t5s","t6s","t7s","t8s","t9s","t10s","t11s","t12s","t13s","t1l","t2l","t3l","t4l","t5l","t6l","t7l","t8l","t9l","t10l","t11l","t12l","t13l","t1","t2","t3","t4","t5","t6","t7","t8","t9","t10","t11","t12","t13"} ; // J'ai inversé nbSteps et nbTracker pour bien définir l'array. J'ai répercuté le changement dans la boucle en bas.


    for ( int i=0; i<12; i++ ) {
        G4double innerRadiusOfTheTube = Iradii[i];
        G4double outerRadiusOfTheTube =Oradii[i];
        G4double hightOfTheTube = 5.8*m;     //half length of the tube
        G4double startAngleOfTheTube = 0.*deg;
        G4double spanningAngleOfTheTube = 360.*deg;

        G4Tubs* tracker_Solid = new G4Tubs ( namesTracker[0][i],innerRadiusOfTheTube,outerRadiusOfTheTube,hightOfTheTube,startAngleOfTheTube,spanningAngleOfTheTube );

        tracker_log = new G4LogicalVolume ( tracker_Solid, Si,namesTracker[1][i],0,0,0 ); // fill the solid with "Silicon"       variable non declarée...
        ///TODO G4SensitiveDetector* trackerS_log = new   //
        tracker = new G4PVPlacement ( 0,G4ThreeVector(),tracker_log, namesTracker[2][i],WorldVolume_log,false,0 ); // raises it to physical volume
    }


    //------------------------------ Le calorimètre

    const int nbrCalo = 20 ;
    std::string nomsCalo[3][nbrCalo] = { "cal01t", "cal02t", "cal03t", "cal04t", "cal05t", "cal06t", "cal07t", "cal08t" "cal09t", "cal10t", "cal11t", "cal12t", "cal13t", "cal14t", "cal15t", "cal16t", "cal17t", "cal18t", "cal19t", "cal20t","cal01l", "cal02l", "cal03l", "cal04l", "cal05l", "cal06l", "cal07l", "cal08l" "cal09l", "cal10l", "cal11l", "cal12l", "cal13l", "cal14l", "cal15l", "cal16l", "cal17l", "cal18l", "cal19l", "cal20l","cal01", "cal02", "cal03", "cal04", "cal05", "cal06", "cal07", "cal08" "cal09", "cal10", "cal11", "cal12", "cal13", "cal14", "cal15", "cal16", "cal17", "cal18", "cal19", "cal20" };
    G4double innerRadiusOfTheCalo = 1.5*m;
    G4double outerRadiusOfTheCalo = 3.*m;
    G4double hightOfTheCalo = 5.8*m;

    for ( int n = 0; n< nbrCalo ; n++ ) {
        G4double startAngleOfTheCalo = n*18.*deg;
        G4double spanningAngleOfTheCalo = 18.*deg;
        G4Tubs* calorimeterBlock_tube = new G4Tubs ( nomsCalo[0][n],innerRadiusOfTheCalo,outerRadiusOfTheCalo,hightOfTheCalo,startAngleOfTheCalo,spanningAngleOfTheCalo );
        calorimeterBlock_log = new G4LogicalVolume ( calorimeterBlock_tube,Pb,nomsCalo[1][n],0,0,0 );
        calorimeterBlock_phys = new G4PVPlacement ( 0,G4ThreeVector(),calorimeterBlock_log,nomsCalo[2][n],WorldVolume_log,false,n );
    }

    //------------------------------- Détecteur sensible
    
    G4SDManager* SDman = G4SDManager::GetSDMpointer(); // On initialise le manager Sensitive Detector
    
    // Calorimètre
    G4String caloDetectSDname = "projetZ/caloDetectSD"; 
    projetZCaloSD* aCaloSD = new projetZCaloSD(caloDetectSDname);
    SDman->AddNewDetector(aCaloSD);
    calorimeterBlock_log->SetSensitiveDetector(aCaloSD);
    // Trackeur
    
    
    

    return World_Volume;
}


