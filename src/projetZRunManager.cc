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
#include "projetZTrackerHit.hh"
#include "projetZTrackerSD.hh"
#include <iostream>
#include <fstream>
#include "G4UnitsTable.hh"
#include "projetZDistribution.hh"
#include <vector>
#include "cmath"

projetZRunManager::projetZRunManager() : G4RunManager()
{}

projetZRunManager::~projetZRunManager()
{
}

void projetZRunManager::AnalyzeEvent ( G4Event* anEvent )
{
    G4RunManager::AnalyzeEvent ( anEvent );
    G4int positionsJets[4][2];
    bool jetLocalised = DetectionJets ( anEvent, positionsJets );
    if ( jetLocalised ) {
	bool tracefinder;
        for ( int jt=0 ; jt<4 ; jt++ ) {
            tracefinder = TrouverTrace ( anEvent ,positionsJets, jt );
        }
        G4cout << "La masse du Higgs vaut : " << G4BestUnit(masseH(), "Energy") << G4endl;
	if (tracefinder)
	{
	  std::string const nomFichier ( "masseHiggs.txt" );
        std::ofstream fluxe ( nomFichier.c_str(), std::ios::app );
        if ( fluxe ) {
            fluxe << masseH() << G4endl ;

        } else {
            G4cout << "ERREUR: Impossible d'ouvrir le fichier." << G4endl;
        }
	}
    }
}

void projetZRunManager::DetectionTrace ( G4Event* anEvent )
{
    G4HCofThisEvent *HCE;
    HCE = anEvent->GetHCofThisEvent();
    projetZTrackerHitsCollection* trackerCollection = 0;
    if ( HCE ) {
        trackerCollection = ( projetZTrackerHitsCollection* ) ( HCE->GetHC ( 1 ) );
    }

    G4cout << trackerCollection->GetSDname() <<G4endl;

    G4int NbHits = trackerCollection->entries();
    G4cout << "Il y a " << NbHits << " hits dans le tracker" << G4endl;
}

bool projetZRunManager::TrouverTrace( G4Event* anEvent, G4int positionsJets[4][2], G4int numeroJet )
{
    G4HCofThisEvent *HCE;
    HCE = anEvent->GetHCofThisEvent();
    projetZTrackerHitsCollection* trackerCollection = 0;
    if ( HCE ) {
        trackerCollection = ( projetZTrackerHitsCollection* ) ( HCE->GetHC ( 1 ) );
    }
    G4cout << trackerCollection->GetSDname() <<G4endl;

    G4int NbHits = trackerCollection->entries();
    G4cout << "Il y a " << NbHits << " hits dans le tracker" << G4endl;
    std::vector<projetZTrackerHit> tracker_0(0);
    std::vector<projetZTrackerHit> tracker_1(0);
    std::vector<projetZTrackerHit> tracker_2(0);
    std::vector<projetZTrackerHit> tracker_3(0);
    std::vector<projetZTrackerHit> tracker_4(0);
    std::vector<projetZTrackerHit> tracker_5(0);
    std::vector<projetZTrackerHit> tracker_6(0);
    std::vector<projetZTrackerHit> tracker_7(0);
    std::vector<projetZTrackerHit> tracker_8(0);
    std::vector<projetZTrackerHit> tracker_9(0);
    std::vector<projetZTrackerHit> tracker_10(0);
    std::vector<projetZTrackerHit> tracker_11(0);
    std::vector<projetZTrackerHit> tracker_12(0);
    for ( int n=0 ; n<NbHits ; n++ ) {
        G4int numeroTracker = ( *trackerCollection ) [n]->GetTrackerNb();
        projetZTrackerHit hitTracker = * ( ( *trackerCollection ) [n] );
        switch ( numeroTracker ) {
        case 0:
            tracker_0.push_back ( hitTracker );
            break;
        case 1:
            tracker_1.push_back ( hitTracker );
            break;
        case 2:
            tracker_2.push_back ( hitTracker );
            break;
        case 3:
            tracker_3.push_back ( hitTracker );
            break;
        case 4:
            tracker_4.push_back ( hitTracker );
            break;
        case 5:
            tracker_5.push_back ( hitTracker );
            break;
        case 6:
            tracker_6.push_back ( hitTracker );
            break;
        case 7:
            tracker_7.push_back ( hitTracker );
            break;
        case 8:
            tracker_8.push_back ( hitTracker );
            break;
        case 9:
            tracker_9.push_back ( hitTracker );
            break;
        case 10:
            tracker_10.push_back ( hitTracker );
            break;
        case 11:
            tracker_11.push_back ( hitTracker );
            break;
        case 12:
            tracker_12.push_back ( hitTracker );
            break;
        default:
            G4cout << "ERREUR : Il y a des hits qui n'appartiennent à aucun tracker..." << G4endl;
            break;
        }
    }
    std::vector< std::vector<projetZTrackerHit> > vecteurHits (0);
    vecteurHits.push_back(tracker_0);
    vecteurHits.push_back(tracker_1);
    vecteurHits.push_back(tracker_2);
    vecteurHits.push_back(tracker_3);
    vecteurHits.push_back(tracker_4);
    vecteurHits.push_back(tracker_5);
    vecteurHits.push_back(tracker_6);
    vecteurHits.push_back(tracker_7);
    vecteurHits.push_back(tracker_8);
    vecteurHits.push_back(tracker_9);
    vecteurHits.push_back(tracker_10);
    vecteurHits.push_back(tracker_11);
    vecteurHits.push_back(tracker_12);
    G4double tracker_radius[13];
    tracker_radius[0]  = 8.*cm;
    tracker_radius[1]  = 9.*cm;
    tracker_radius[2]  = 10.*cm;
    tracker_radius[3]  = 20.*cm;
    tracker_radius[4]  = 30.*cm;
    tracker_radius[5]  = 40.*cm;
    tracker_radius[6]  = 50.*cm;
    tracker_radius[7]  = 60.*cm;
    tracker_radius[8]  = 70.*cm;
    tracker_radius[9]  = 80.*cm;
    tracker_radius[10] = 90.*cm;
    tracker_radius[11] = 100.*cm;
    tracker_radius[12] = 110.*cm;
    
    G4double a = (9*positionsJets[numeroJet][0] +4.5)*pi/180; //angle theta en seed
    G4double c = ( pi/2 - atan ( ( ( positionsJets[numeroJet][1] ) -20.5 ) *14/40 ) ); // angle phi en seed
    G4cout << "Les angles en seed sont :" << G4endl << "Théta : " << a/deg << G4endl << "Phi : " << c/deg << G4endl;

    //définir droite reliant le vertex au jet, tq on sait quel est le centre droite du cone sur chaque vertex
    G4ThreeVector droite [13];
    for ( int i = 0; i<13; i++ ) {
        droite[i].setX(tracker_radius[i]*cos ( a ) *sin ( c )) ;
        droite[i].setY(tracker_radius[i]*sin ( a ) *sin ( c ));
        droite[i].setZ(tracker_radius[i]*cos ( c )); 
    }

    //vecteur contenant la "trace" rendu à la fin de la fonction
    G4double theta(0.);
    G4double phi(0.);
    G4double x;
    G4double y;
    G4double z;
    G4double rayon;
    G4int bonHits ( 0 );
    G4double hitTheta;
    G4double hitPhi;
    
    // Une façon d'améliorer l'algo, c'est d'éliminer les points parasites. Ces points sont caractérisés par le fait qu'ils sont très proches et très nombreux, alors qu'une bonne particules va laisser maximum trois ou quatres hits dans la même direction.
    for ( int i = 0; i<2; i++ ) {
        std::vector<projetZTrackerHit> leVecteurDeHits = vecteurHits[i]; // On récupère le vecteur de hit associé au bon tracker
        int p = leVecteurDeHits.size(); // Nombre de hit dans le tracker
	G4cout << "Recherche dans le tracker : " << i << G4endl;
	G4cout << "Nombre hit dans ce tracker : " << p << G4endl;
        for ( int j = 0; j<p ; j++ ) {
            projetZTrackerHit leVecteurHit = leVecteurDeHits.at ( j ); // On récupère le hit
            G4ThreeVector leVecteurPosition = leVecteurHit.GetPos(); // On récupère le G4ThreeVector associé au hit
            x = leVecteurPosition.getX();
            y = leVecteurPosition.getY();
            z = leVecteurPosition.getZ();
	    rayon = leVecteurPosition.getR();
            hitPhi = acos ( z/rayon );
            if ( y < 0 ) {
                hitTheta = 2*pi - acos ( x/sqrt ( x*x + y*y ) );
            } else {
                hitTheta = acos ( x/sqrt ( x*x + y*y ) );
            }
//             G4cout << "Angle Théta du hit : " << hitTheta/deg << G4endl;
// 	    G4cout << "Angle Phi du hit : " << hitPhi/deg << G4endl;
            if (  abs(hitTheta/deg -a/deg) < 20 && abs(hitPhi/deg - c/deg) < 20 )  {
                bonHits++;
		theta += hitTheta;
		phi += hitPhi;
            }
        }
    }
    if (bonHits > 0)
    {
    theta = theta/bonHits;
    phi = phi/bonHits;
    G4cout << "Angle théta trouvé par le tracker : " << theta/deg << G4endl;
    G4cout << "Angle phi trouvé par le tracker : " << phi/deg << G4endl;
    switch (numeroJet)
    {
      case 0:
	th1 = theta;
	phi1 = phi;
	return true;
      case 1:
	th2 = theta;
	phi2 = phi;
	return true;
      case 2:
	th3 = theta;
	phi3 = phi;
	return true;
      case 3:
	th4 = theta;
	phi4 = phi;
	return true;
      default:
	G4cout << "Problèèèèmeeee !!!" << G4endl;
	return false;
    }
    
    }
    else
    {
      G4cout << "Aucun bon hit n'a été trouvé" << G4endl;
      return false;
    }
}

bool projetZRunManager::DetectionJets ( G4Event* anEvent, G4int positionsJets[4][2] )
{
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
	    projetZDistribution ( valeurTampon, "distribGauss", 0., 1000. );
            energieCell[n][k] = abs(valeurTampon[0]);
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
    if (TrouverJets ( energieCell ,positionsJets))
    {return true;}
    else {return false;}
    
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
    std::string const nomFichier3 ( "plotCaloBrut.txt" );
    std::ofstream monFlux3 ( nomFichier3.c_str(), std::ios::app );
    if ( monFlux2 ) {
        for ( int n=0 ; n<40 ; n++ ) {
            for ( int k=0 ; k<40 ; k++ ) {
                monFlux2 << cell[n][k] << " " ;
                monFlux3 << n << " " << k << " " << cell[n][k] << std::endl;
            }
            monFlux2 << std::endl;
        }
        monFlux2 << -1 << G4endl;
        monFlux3 << -1 << G4endl;

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

bool projetZRunManager::TrouverJets ( G4double ecell[][40], G4int positionsJets[4][2] )
{
    std::vector<G4ThreeVector> posJets(4);
    const G4int nbreJetAttendu = 4;
    G4int taillePhi = 40;
    G4int tailleZ = 40;
    //std::ifstream monFlux ( "depotCalorimetre.txt" ); //Ouverture d'un fichier en lecture
    G4double cell[42][42];
    G4int nombreJet ( 0 );
    G4double energiesJets [nbreJetAttendu];
//     int positionsJets[nbreJetAttendu][2];
    for ( int n=0 ; n<taillePhi+2 ; n++ ) {
        for ( int k=0 ; k<tailleZ+2 ; k++ ) {
            cell[n][k] = 0 ;
        }
    }

    for ( int n=1 ; n<taillePhi+1 ; n++ ) {
        for ( int k=1 ; k<tailleZ+1 ; k++ ) {
            cell[n][k] =ecell[n-1][k-1];
            cell[n][k] += abs ( valeurTampon[0] );
        }
    }
    // On relie les bords de la séparation angulaire
    for ( int k=0 ; k<tailleZ+2 ; k++ ) {
        cell[0][k] = cell[taillePhi][k];
        cell[taillePhi+1][k] = cell[1][k];
    }

    // On doit maintenant parcourir toutes les cellules
    G4double minEnergie = 6000.*MeV;
    std::string const nomFichier ( "plotCaloNet.txt" );
    std::ofstream leFlux ( nomFichier.c_str(), std::ios::app );
    for ( int n=1 ; n<taillePhi+1 ; n++ ) {
        for ( int k=1 ; k<tailleZ+1 ; k++ ) {
            if ( cell[n][k] > minEnergie ) {
                if ( regarderAutour ( cell, n, k ) && nombreJet < nbreJetAttendu+1) {
                    nombreJet++;
                    energiesJets[nombreJet-1] = cell[n][k];
                    positionsJets[nombreJet-1][0] = n;
                    positionsJets[nombreJet-1][1] = k;
                    for ( int i=-1 ; i<2 ; i++ ) {
                        if ( nombreJet > nbreJetAttendu ) {
                            G4cout << "ERREUR :  Trop de jets détectés" << G4endl;
                        } else if ( cell[n+i][k-1] > minEnergie ) {
                            energiesJets[nombreJet-1] += cell[n+i][k-1];
                        }
                    }
                    for ( int i=0 ; i<2 ; i++ ) {
                        if ( nombreJet > nbreJetAttendu ) {
                            G4cout << "ERREUR :  Trop de jets d1étectés" << G4endl;
                        } else if ( cell[n+1][k+i] > minEnergie ) {
                            energiesJets[nombreJet-1] += cell[n+1][k+i];
                        }
                    }
                    for ( int i=0 ; i<2 ; i++ ) {
                        if ( nombreJet > nbreJetAttendu ) {
                            G4cout << "ERREUR :  Trop de jets détectés" << G4endl;
                        } else if ( cell[n-i][k+1] > minEnergie ) {
                            energiesJets[nombreJet-1] += cell[n-i][k+1];
                        }
                    }
                    for ( int i=0 ; i<2 ; i++ ) {
                        if ( nombreJet > nbreJetAttendu ) {
                            G4cout << "ERREUR :  Trop de jets détectés" << G4endl;
                        } else if ( cell[n-1][k-i] > minEnergie ) {
                            energiesJets[nombreJet-1] += cell[n-1][k-i];
                        }
                    }
                    leFlux << energiesJets[nombreJet-1] << " " ;
                } else {
                    leFlux << 0 << " " ;
                }
            } else {
                leFlux << 0 << " " ;
            }
            if ( k == 40 ) {
                leFlux << G4endl;
            }
        }
    }
    if ( nombreJet > nbreJetAttendu ) {
        std::string const nomFichier ( "erreurDetection.txt" );
        std::ofstream monFlux2 ( nomFichier.c_str(), std::ios::app );
        if ( monFlux2 ) {
            monFlux2 << " " << -2 << G4endl ;
        }
        return false;
    }
    if ( nombreJet < nbreJetAttendu ) {
        G4cout << "Erreur, il manque des jets" << G4endl;
        std::string const nomFichier ( "erreurDetection.txt" );
        std::ofstream monFlux2 ( nomFichier.c_str(), std::ios::app );
        if ( monFlux2 ) {
            monFlux2 << " " << -1 << G4endl ;

        } else {
            G4cout << "ERREUR: Impossible d'ouvrir le fichier." << G4endl;
        }
        return false;
    } else if ( nombreJet == nbreJetAttendu ) {
        for ( int i=0 ; i<nbreJetAttendu ; i++ ) {
	    
            G4cout << "Jet d'énergie : " << G4BestUnit ( energiesJets[i] + 0.0230304*energiesJets[i], "Energy" ) << " Et de position (n,k) : " << positionsJets[i][0] << " " << positionsJets[i][1]  << " Et theta : " << 9*positionsJets[i][0] +4.5 <<  " Et phi : " << ( pi/2 - atan ( ( ( positionsJets[i][1] ) -20.5 ) *14/40 ) ) *180/pi << G4endl;
            switch ( i ) {
            case 0:
		e1 = energiesJets[i] + 0.0330304*energiesJets[i];
                break;
            case 1:
                e2 = energiesJets[i] + 0.0330304*energiesJets[i];
                break;
            case 2:
                e3 = energiesJets[i] + 0.0330304*energiesJets[i];
                break;
            case 3:
                e4 = energiesJets[i] + 0.0330304*energiesJets[i];
                break;
            default:
                G4cout << "Problèèèèmeeee !!! (le retour)" << G4endl;
                break;
            }

        }

        std::string const nomFichier ( "erreurDetection.txt" );
        std::ofstream monFlux2 ( nomFichier.c_str(), std::ios::app );
        if ( monFlux2 ) {
            monFlux2 << " " << energiesJets[0] << G4endl ;

        } else {
            G4cout << "ERREUR: Impossible d'ouvrir le fichier." << G4endl;
        }
        return true;
    }
    
}




// Fonction qui prend en argument l'énergie en Mev et les theta phi des électrons et qui renvoit la masse du Higgs en Mev.
//NB je considère que l'énergie renvoyée par les calos est l'énergie totale tenant compte de l'impulsion et de l'énergie de masse.
//La masse des électrons est négligeable mais ça ne coute pas cher d'en tenir compte donc je le fais.

G4double projetZRunManager::masseH ()
{
    G4double masseH;
    G4double p1[3],p2[3],p3[3],p4[3];  //trivecteur impulsion des électrons au vertex
    G4double Np1=sqrt ( e1*e1-0.511*0.511 ) *MeV; // Norme de l'impulsion des électrons
    G4double Np2=sqrt ( e2*e2-0.511*0.511 ) *MeV;
    G4double Np3=sqrt ( e3*e3-0.511*0.511 ) *MeV;
    G4double Np4=sqrt ( e4*e4-0.511*0.511 ) *MeV;

    // contruction des trivecteurs impulsions

    p1[0]=Np1*cos ( th1 ) *sin ( phi1 );
    p1[1]=Np1*sin ( th1 ) *sin ( phi1 );
    p1[2] =Np1 * cos ( phi1 );
    p2[0]=Np2*cos ( th2 ) *sin ( phi2 );
    p2[1]=Np2*sin ( th2 ) *sin ( phi2 );
    p2[2] =Np2 * cos ( phi2 );
    p3[0]=Np3*cos ( th3 ) *sin ( phi3 );
    p3[1]=Np3*sin ( th3 ) *sin ( phi3 );
    p3[2] =Np3 * cos ( phi3 );
    p4[0]=Np4*cos ( th4 ) *sin ( phi4 );
    p4[1]=Np4*sin ( th4 ) *sin ( phi4 );
    p4[2] =Np4 * cos ( phi4 );

    // Reconstruction de la masse invariante

    G4double ptot[3];
    ptot[0]= p1[0]+p2[0]+p3[0]+p4[0];
    ptot[1]= p1[1]+p2[1]+p3[1]+p4[1];
    ptot[2]= p1[2]+p2[2]+p3[2]+p4[2];

    masseH=sqrt ( ( e1+e2+e3+e4 ) * ( e1+e2+e3+e4 )- ( ptot[0]*ptot[0]+ptot[1]*ptot[1]+ptot[2]*ptot[2] ) );

    return masseH;
}















