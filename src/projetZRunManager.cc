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


#include "projetZRunManager.hh"
#include "projetZCaloHit.hh"
#include "G4HCofThisEvent.hh"
#include "G4SDManager.hh"
#include "projetZCaloSD.hh"
#include <iostream>
#include <fstream>
#include "G4UnitsTable.hh"
#include "projetZDistribution.hh"

projetZRunManager::projetZRunManager() : G4RunManager()
{}

projetZRunManager::~projetZRunManager()
{
//   G4RunManager::~G4RunManager();
}

void projetZRunManager::AnalyzeEvent ( G4Event* anEvent )
{
    srand ( time ( NULL ) );
    G4RunManager::AnalyzeEvent ( anEvent );
    G4HCofThisEvent *HCE;
    HCE = anEvent->GetHCofThisEvent();
    projetZCaloHitCollection* caloCollection = 0;
    if ( HCE ) {
        caloCollection = ( projetZCaloHitCollection* ) ( HCE->GetHC ( 0 ) );
    }
    G4int NbHits = caloCollection->entries();
    G4cout << caloCollection->GetSDname() << G4endl;
    G4double energieTotal ( 0. );
    G4double energieCell[40][40];
    for ( int n = 0 ; n<40 ; n++ ) {
        for ( int k = 0 ; k<40 ; k++ ) {
            energieCell[n][k] = 0;
        }
    }
    for ( G4int i=0; i<NbHits; i++ ) {
        G4int positionCell = ( *caloCollection ) [i]->GetCaloNb();
        G4int positionZ = int ( positionCell/ ( 40 ) );
        G4int positionpPhi = positionCell - positionZ*40;
        G4double energieTampon = ( *caloCollection ) [i]->GetEdep();
        energieTotal += energieTampon;
        energieCell[positionpPhi][positionZ] += energieTampon;
    }
    EcrireEnergie ( energieTotal,energieCell );
    TrouverJets ( energieCell );
}

void projetZRunManager::EcrireEnergie ( G4double energie, G4double cell[][40] )
{
    std::string const nomFichier ( "energieCalorimetre.txt" );
    std::ofstream monFlux ( nomFichier.c_str(), std::ios::app );
    if ( monFlux ) {
        monFlux << energie << G4endl;
    } else {
        G4cout << "ERREUR: Impossible d'ouvrir le fichier." << G4endl;
    }
    std::string const nomFichier2 ( "depotCalorimetre.txt" );
    std::ofstream monFlux2 ( nomFichier2.c_str(), std::ios::app );
    if ( monFlux2 ) {
        for ( int n=0 ; n<40 ; n++ ) {
            for ( int k=0 ; k<40 ; k++ ) {
                monFlux2 << cell[n][k] << " " ;
            }
            monFlux2 << std::endl;
        }
        monFlux2 << -1 << G4endl;

    } else {
        G4cout << "ERREUR: Impossible d'ouvrir le fichier." << G4endl;
    }
}

bool projetZRunManager::regarderAutour ( double cell[42][42], int n, int k )
{
    for ( int i=-1 ; i<2 ; i++ ) {
        if ( cell[n][k] < cell[n+i][k-1] ) {
            return false;
        }
    }
    for ( int i=0 ; i<2 ; i++ ) {
        if ( cell[n][k] < cell[n+1][k+i] ) {
            return false;
        }
    }
    for ( int i=0 ; i<2 ; i++ ) {
        if ( cell[n][k] < cell[n-i][k+1] ) {
            return false;
        }
    }
    for ( int i=0 ; i<2 ; i++ ) {
        if ( cell[n][k] < cell[n-1][k-i] ) {
            return false;
        }
    }
    return true;
}

void projetZRunManager::TrouverJets ( G4double ecell[][40] )
{
    G4int taillePhi = 40;
    G4int tailleZ = 40;
    //std::ifstream monFlux ( "depotCalorimetre.txt" ); //Ouverture d'un fichier en lecture
    G4double cell[42][42];
    G4int nombreJet ( 0 );
    G4double energiesJets [4];
    int positionsJets[4][2];
    for ( int n=0 ; n<taillePhi+2 ; n++ ) {
        for ( int k=0 ; k<tailleZ+2 ; k++ ) {
            cell[n][k] = 0 ;
        }
    }
    
    for ( int n=1 ; n<taillePhi+1 ; n++ ) {
        for ( int k=1 ; k<tailleZ+1 ; k++ ) {
            cell[n][k] =ecell[n-1][k-1];
	    projetZDistribution(valeurTampon, "distribGauss", 0., 1000.);
            cell[n][k] += abs (valeurTampon[0]);
        }
    }
    // On relie les bords de la séparation angulaire
    for ( int k=0 ; k<tailleZ+2 ; k++ ) {
        cell[0][k] = cell[taillePhi][k];
        cell[taillePhi+1][k] = cell[1][k];
    }

    // On doit maintenant parcourir toutes les cellules
    G4double minEnergie = 5000.;
    for ( int n=1 ; n<taillePhi+1 ; n++ ) {
        for ( int k=1 ; k<tailleZ+1 ; k++ ) {
            if ( cell[n][k] > minEnergie ) {
                if ( regarderAutour ( cell, n, k ) ) {
                    nombreJet++;
                    energiesJets[nombreJet-1] = cell[n][k];
                    positionsJets[nombreJet-1][0] = n;
                    positionsJets[nombreJet-1][1] = k;
                    for ( int i=-1 ; i<2 ; i++ ) {
                        if ( nombreJet > 4 ) {
                            G4cout << "ERREUR :  Trop de jets détectés" << G4endl;
                        } else if ( cell[n+i][k-1] > minEnergie ) {
                            energiesJets[nombreJet-1] += cell[n+i][k-1];
                        }
                    }
                    for ( int i=0 ; i<2 ; i++ ) {
                        if ( nombreJet > 4 ) {
                            G4cout << "ERREUR :  Trop de jets détectés" << G4endl;
                        } else if ( cell[n+1][k+i] > minEnergie ) {
                            energiesJets[nombreJet-1] += cell[n+1][k+i];
                        }
                    }
                    for ( int i=0 ; i<2 ; i++ ) {
                        if ( nombreJet > 4 ) {
                            G4cout << "ERREUR :  Trop de jets détectés" << G4endl;
                        } else if ( cell[n-i][k+1] > minEnergie ) {
                            energiesJets[nombreJet-1] += cell[n-i][k+1];
                        }
                    }
                    for ( int i=0 ; i<2 ; i++ ) {
                        if ( nombreJet > 4 ) {
                            G4cout << "ERREUR :  Trop de jets détectés" << G4endl;
                        } else if ( cell[n-1][k-i] > minEnergie ) {
                            energiesJets[nombreJet-1] += cell[n-1][k-i];
                        }
                    }
                }
            }
        }
    }
    if ( nombreJet < 4 ) {
        G4cout << "Erreur, il manque des jets" << G4endl;
    } else {
        for ( int i=0 ; i<4 ; i++ ) {
            G4cout << "Jet d'énergie : " << G4BestUnit( energiesJets[i], "Energy") << " Et de position (n,k) : " << positionsJets[i][0] << " " << positionsJets[i][1]  << " Et theta : " << 9*positionsJets[i][0] +4.5 <<  " Et phi : " <<  (pi/2 - atan(((positionsJets[i][1]) -20.5)*14/40))*180/pi << G4endl;
        }
    }

}
