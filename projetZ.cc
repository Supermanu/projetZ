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

#include "projetZRunManager.hh"
#include "G4UImanager.hh"

#include "projetZDetectorConstruction.hh"
#include "projetZPhysicsList.hh"
#include "projetZPrimaryGeneratorAction.hh"
#include "projetZElectronsGenerator.hh"

// Inclusion de la visualisation
#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

// Ajout la possibilité d'un prompt
#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

int main ( int argc,char** argv )
{
    srand ( time ( NULL ) );
    // Construct the default run manager
    //
    projetZRunManager* runManager = new projetZRunManager;

    // set mandatory initialization classes
    //
    G4VUserDetectorConstruction* detector = new projetZDetectorConstruction;
    runManager->SetUserInitialization ( detector );
    //
    G4VUserPhysicsList* physics = new projetZPhysicsList;
    runManager->SetUserInitialization ( physics );

    // set mandatory user action class
    //
    G4VUserPrimaryGeneratorAction* gen_action = new projetZPrimaryGeneratorAction;
    runManager->SetUserAction ( gen_action );

    // Initialize G4 kernel
    //
    runManager->Initialize();

#ifdef G4VIS_USE
    // Initialize visualization
    G4VisManager* visManager = new G4VisExecutive;
    // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
    // G4VisManager* visManager = new G4VisExecutive("Quiet");
    visManager->Initialize();
#endif

    // Get the pointer to the UI manager and set verbosities
    //
    G4UImanager* UImanager = G4UImanager::GetUIpointer();

    if ( argc!=1 ) {

        // interactive mode : define UI session
#ifdef G4UI_USE
        G4UIExecutive* ui = new G4UIExecutive ( argc, argv );
#ifdef G4VIS_USE
        UImanager->ApplyCommand ( "/control/execute init_vis.mac" );
#else
        UImanager->ApplyCommand ( "/control/execute init.mac" );
#endif
        ui->SessionStart();
        delete ui;
#endif
    } else {

        // batch mode
        UImanager->ApplyCommand ( "/run/verbose 0" );
        UImanager->ApplyCommand ( "/event/verbose 0" );
        UImanager->ApplyCommand ( "/tracking/verbose 0" );
    }

    // Start a run
    //
    G4int numberOfEvent = 500;
    runManager->BeamOn ( numberOfEvent );

#ifdef G4VIS_USE
    delete visManager;
#endif

    delete runManager;

    return 0;
}


