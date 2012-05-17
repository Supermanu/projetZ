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
// $Id: projetZPrimaryGeneratorAction.cc,v 1.6 2006-06-29 17:47:23 gunter Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
//

#include "projetZPrimaryGeneratorAction.hh"
#include "projetZElectronsGenerator.hh"
#include "projetZDistribution.hh"

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"
#include "G4UnitsTable.hh"
#include <iostream>
#include <fstream>

projetZPrimaryGeneratorAction::projetZPrimaryGeneratorAction()
{
    G4int n_particle = 1;
    particleGun = new G4ParticleGun ( n_particle );
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName;
    particleGun->SetParticleDefinition ( particleTable->FindParticle ( particleName="e-" ) );
}

projetZPrimaryGeneratorAction::~projetZPrimaryGeneratorAction()
{
    delete particleGun;
}

void projetZPrimaryGeneratorAction::GeneratePrimaries ( G4Event* anEvent )
{
    bool desintegrationHiggs = true;
    if ( desintegrationHiggs ) {
        projetZElectronsGenerator quatreElectrons;
        G4double enDeg = 180/pi;
        G4cout << G4BestUnit ( quatreElectrons.getEnergyElectron ( 0 ),"Energy" ) << " Avec comme angle phi: "<< quatreElectrons.getDirectionElectron(0).theta()*enDeg  << " Et theta : "<< quatreElectrons.getDirectionElectron(0).phi()*enDeg<< endl;
        G4cout << G4BestUnit ( quatreElectrons.getEnergyElectron ( 1 ),"Energy" ) << "Avec comme angle phi: "<< quatreElectrons.getDirectionElectron(1).theta()*enDeg << " Et theta : "<< quatreElectrons.getDirectionElectron(1).phi()*enDeg<< endl;
        G4cout << G4BestUnit ( quatreElectrons.getEnergyElectron ( 2 ),"Energy" ) << "Avec comme angle phi: "<< quatreElectrons.getDirectionElectron(2).theta()*enDeg << " Et theta : "<< quatreElectrons.getDirectionElectron(2).phi()*enDeg<< endl;
        G4cout << G4BestUnit ( quatreElectrons.getEnergyElectron ( 3 ),"Energy" ) << "Avec comme angle phi: "<< quatreElectrons.getDirectionElectron(3).theta()*enDeg << " Et theta : "<< quatreElectrons.getDirectionElectron(3).phi()*enDeg<< endl;
        G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
        G4String particleName;
        particleGun->SetParticleDefinition ( particleTable->FindParticle ( particleName="e-" ) );
        particleGun->SetParticleMomentumDirection ( quatreElectrons.getDirectionElectron ( 0 ) );
        particleGun->SetParticleEnergy ( quatreElectrons.getEnergyElectron ( 0 ) );
        particleGun->SetParticlePosition ( G4ThreeVector ( 0.*cm,0.*cm,0.*cm ) );
        particleGun->GeneratePrimaryVertex ( anEvent );
        particleGun->SetParticleMomentumDirection ( quatreElectrons.getDirectionElectron ( 2 ) );
        particleGun->SetParticleEnergy ( quatreElectrons.getEnergyElectron ( 2 ) );
        particleGun->GeneratePrimaryVertex ( anEvent );
        particleGun->SetParticleDefinition ( particleTable->FindParticle ( particleName="e+" ) );
        particleGun->SetParticleMomentumDirection ( quatreElectrons.getDirectionElectron ( 1 ) );
        particleGun->SetParticleEnergy ( quatreElectrons.getEnergyElectron ( 1 ) );
        particleGun->SetParticlePosition ( G4ThreeVector ( 0.*cm,0.*cm,0.*cm ) );
        particleGun->GeneratePrimaryVertex ( anEvent );
        particleGun->SetParticleMomentumDirection ( quatreElectrons.getDirectionElectron ( 3 ) );
        particleGun->SetParticleEnergy ( quatreElectrons.getEnergyElectron ( 3 ) );
        particleGun->GeneratePrimaryVertex ( anEvent );
//         std::string const nomFichier ( "energiesElectrons.txt" );
//         std::ofstream monFlux ( nomFichier.c_str(), std::ios::app );
//         if ( monFlux ) {
//             for ( int n=0 ; n<4 ; n++ ) {
//                 monFlux << quatreElectrons.getEnergyElectron ( n ) << " " ;
//             }
//             monFlux << G4endl;
//         } else {
//             G4cout << "ERREUR: Impossible d'ouvrir le fichier." << G4endl;
//         }
    } else {
        G4double energieTampon[1];
        projetZDistribution ( energieTampon, "distribGauss", 60.*GeV, 25.*GeV );
        G4cout << "Energie de l'electron projeté : " << G4BestUnit ( energieTampon[0], "Energy" ) << G4endl;
        particleGun->SetParticleEnergy ( sqrt ( energieTampon[0]*energieTampon[0] ) );
        G4double angleTampon[2];
        projetZDistribution ( angleTampon, "uniforpi" );
//         if ( abs ( angleTampon[1] ) < atan ( 0.2 ) ) {
//             angleTampon[1] += atan ( 0.25 );
//         }
        G4double x = cos ( angleTampon[0] ) *sin ( angleTampon[1] );
        G4double y = sin ( angleTampon[0] ) *sin ( angleTampon[1] );
        G4double z = cos ( angleTampon[1] );


        particleGun->SetParticleMomentumDirection ( G4ThreeVector ( x,y,z ) );
        particleGun->GeneratePrimaryVertex ( anEvent );

//         std::string const nomFichier ( "erreurDetection.txt" );
//         std::ofstream monFlux2 ( nomFichier.c_str(), std::ios::app );
//         if ( monFlux2 ) {
//             monFlux2 << energieTampon[0] ;
//         } else {
//             G4cout << "ERREUR: Impossible d'ouvrir le fichier." << G4endl;
//         }
    }
}


