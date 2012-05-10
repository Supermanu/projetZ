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

#include "G4Event.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "globals.hh"
#include "G4UnitsTable.hh"

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

    projetZElectronsGenerator quatreElectrons;
    
    G4cout << G4BestUnit ( quatreElectrons.getEnergyElectron(0),"Energy" )<< endl;
    G4cout << G4BestUnit ( quatreElectrons.getEnergyElectron(1),"Energy" )<< endl;
    G4cout << G4BestUnit ( quatreElectrons.getEnergyElectron(2),"Energy" )<< endl;
    G4cout << G4BestUnit ( quatreElectrons.getEnergyElectron(3),"Energy" )<< endl;
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName;
    particleGun->SetParticleDefinition ( particleTable->FindParticle ( particleName="e-" ) );
    particleGun->SetParticleMomentumDirection(quatreElectrons.getDirectionElectron(0));
    particleGun->SetParticleEnergy(quatreElectrons.getEnergyElectron(0));
    particleGun->SetParticlePosition(G4ThreeVector(0.*cm,0.*cm,0.*cm));
    particleGun->GeneratePrimaryVertex(anEvent);
    particleGun->SetParticleMomentumDirection(quatreElectrons.getDirectionElectron(2));
    particleGun->SetParticleEnergy(quatreElectrons.getEnergyElectron(2));
    particleGun->GeneratePrimaryVertex(anEvent);
    particleGun->SetParticleDefinition ( particleTable->FindParticle ( particleName="e+" ) );
    particleGun->SetParticleMomentumDirection(quatreElectrons.getDirectionElectron(1));
    particleGun->SetParticleEnergy(quatreElectrons.getEnergyElectron(1));
    particleGun->SetParticlePosition(G4ThreeVector(0.*cm,0.*cm,0.*cm));
    particleGun->GeneratePrimaryVertex(anEvent);
    particleGun->SetParticleMomentumDirection(quatreElectrons.getDirectionElectron(3));
    particleGun->SetParticleEnergy(quatreElectrons.getEnergyElectron(3));
    particleGun->GeneratePrimaryVertex(anEvent);
}


