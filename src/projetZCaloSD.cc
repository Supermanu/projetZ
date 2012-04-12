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

#include "projetZCaloSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4UnitsTable.hh"
#include <iostream>
#include <fstream>

// On donne un nom au détecteur pour pouvoir l'identifier
projetZCaloSD::projetZCaloSD ( G4String name ) :G4VSensitiveDetector ( name )
{
    G4String HCname;
    collectionName.insert ( HCname="caloCollection" );
}

projetZCaloSD::~projetZCaloSD() {}

// La méthode Initialize est appelé à chaque début d'évenement. On va la faire ranger
// la colletion de hits de cet évenement dans le G4HCofThisEvent.

void projetZCaloSD::Initialize ( G4HCofThisEvent* HCE )
{			
    caloCollection = new projetZCaloHitCollection ( SensitiveDetectorName,collectionName[0] );
    static G4int HCID = -1;
    if ( HCID<0 ) {
        HCID = G4SDManager::GetSDMpointer()->GetCollectionID ( collectionName[0] );
    }
    HCE->AddHitsCollection ( HCID, caloCollection );
    energieTotal = 0;
}

// Dans cette méthode, on décrit ce qu'il se passe quand un step (une étape de la particule)
// passe par le détecteur.

G4bool projetZCaloSD::ProcessHits ( G4Step* aStep, G4TouchableHistory* )
{
    G4double eDep = aStep->GetTotalEnergyDeposit(); // On sort l'énergie.
    if ( eDep==0. ) {
        return false;    // Si l'énergie est nulle, on sort.
    }
    projetZCaloHit* newhit = new projetZCaloHit(); // On crée un hit.
    newhit->SetTrackID ( aStep->GetTrack()->GetTrackID() );
    newhit->SetCaloNb ( aStep->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber() );
    newhit->SetEdep ( eDep );
    caloCollection->insert ( newhit );
    energieTotal += eDep;
    // On range le hit dans la collection du calorimètre.
    // newhit->Print(); // Si on veut un cout.
    return true;
}

// Donne juste des détails
void projetZCaloSD::EndOfEvent ( G4HCofThisEvent* )
{
//     if ( verboseLevel>0 ) {
        G4int NbHits = caloCollection->entries();
        G4cout << "\n-------->Collection de hits: dans cet évenement il y a " <<  NbHits
               << " hits dans le calorimètre: " << G4endl;
/// Je comprends pas pourquoi je dois diviser par deux :(
	G4cout << "L'énergie totale déposé est de : " << G4BestUnit ( energieTotal/2,"Energy" ) << G4endl;
	EcrireEnergie(energieTotal/2);
//         for ( G4int i=0; i<NbHits; i++ ) {
//             ( *caloCollection ) [i]->Print();
//         }
//     }
}

void projetZCaloSD::EcrireEnergie (G4double energie)
{
    std::string const nomFichier("energieCalorimetre.txt");
    std::ofstream monFlux(nomFichier.c_str(), std::ios::app);
    if(monFlux)    
    {
        monFlux << energie << G4endl;
    }
    else
    {
        G4cout << "ERREUR: Impossible d'ouvrir le fichier." << G4endl;
    }
}
