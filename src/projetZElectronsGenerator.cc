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
using namespace std;

#include "projetZElectronsGenerator.hh"
#include "G4ios.hh"
#include <cmath>
#include "math.h"
#include "distributions.hh"
#include "Randomize.hh"
#include "G4UnitsTable.hh"

// Je crois que Geant4 travaille en Mev

projetZElectronsGenerator::projetZElectronsGenerator() : masseHiggs(200.0*GeV), directionHiggs(0,0,1)
{
  srand(time(NULL));
  // on va d'abord calculer l'énergie des Z pour un H au repos, ensuite l'énergie pour des électrons avec un Z au repos.
  // Et finalement, on va booster l'énergie des électrons pour se retrouver dans le référentiel du labo.
  
  G4double pZ = sqrt((masseHiggs*masseHiggs)/4 - 91.187*GeV*91.187*GeV);
  G4double energieZ = masseHiggs/2;
  G4double EnergieCinetiqueH = distribExpo(30.*GeV);
  G4double vitesseH = sqrt(1 - (1/(((EnergieCinetiqueH/masseHiggs)+1)*((EnergieCinetiqueH/masseHiggs)+1))));
  G4cout << "Energie cinétique du H: " << G4BestUnit(EnergieCinetiqueH, "Energy") << endl;
  G4cout << "Vitesse du H: " << vitesseH << endl;
  G4double pElectron = sqrt((91.187*GeV*91.187*GeV)/4 - 0.511*MeV*0.511*MeV);
  G4double energieElectron = 91.187*GeV/2;
  
  // On va maintenant distribuer la quantité de mouvement pour un angle aléatoire
  
  vector<G4double> angleAleatoire = uniforpi();
  vector<G4double> pVectorZ(4);
  pVectorZ[0] = energieZ;
  pVectorZ[1] = pZ * cos(angleAleatoire[0])*sin(angleAleatoire[1]);
  pVectorZ[2] = pZ * sin(angleAleatoire[0])*sin(angleAleatoire[1]);
  pVectorZ[3] = pZ * cos(angleAleatoire[1]);
  
  // On calcul le "vecteur" de boost, c'est-à-dire la vitesse
  
  G4double vitesseZ = sqrt((pZ*pZ)/(91.187*GeV*91.187*GeV + pZ*pZ));
  G4cout << "La vitesse vaut : " << vitesseZ << endl;
  vector<G4double> boostZ (3);
  boostZ[0] = - vitesseZ* pVectorZ[1] / pZ;
  boostZ[1] = - vitesseZ* pVectorZ[2] / pZ;
  boostZ[2] = - vitesseZ* pVectorZ[3] / pZ;
  
  // On distribue la quantité de mouvement des électrons.
  
  angleAleatoire = uniforpi();
  
  vector<G4double> pVectorElectron(4);
  pVectorElectron[0] = energieElectron;
  pVectorElectron[1] = pElectron * cos(angleAleatoire[0])*sin(angleAleatoire[1]);
  pVectorElectron[2] = pElectron * sin(angleAleatoire[0])*sin(angleAleatoire[1]);
  pVectorElectron[3] = pElectron * cos(angleAleatoire[1]);

  // On boost des électrons
  
  vector<G4double> pVectorElectronBoosted = boost(pVectorElectron, boostZ);

  for (int n = 0 ; n<4 ; n++)
  {
    momentumElectrons[0][n] = pVectorElectronBoosted[n];
  }
  
  // On regarde l'autre électron
  
  pVectorElectron[1] = - pVectorElectron[1];
  pVectorElectron[2] = - pVectorElectron[2];
  pVectorElectron[3] = - pVectorElectron[3];
  
  pVectorElectronBoosted = boost(pVectorElectron, boostZ);
  for (int n = 0 ; n<4 ; n++)
  {
    momentumElectrons[1][n] = pVectorElectronBoosted[n];
  }
  
  // On prend l'autre Z, et donc le boost opposé
  
  boostZ[0] = - boostZ[0];
  boostZ[1] = - boostZ[1];
  boostZ[2] = - boostZ[2];
  
  angleAleatoire = uniforpi();
  pVectorElectron[1] = pElectron * cos(angleAleatoire[0])*sin(angleAleatoire[1]);
  pVectorElectron[2] = pElectron * sin(angleAleatoire[0])*sin(angleAleatoire[1]);
  pVectorElectron[3] = pElectron * cos(angleAleatoire[1]);
  
  pVectorElectronBoosted = boost(pVectorElectron, boostZ);
  for (int n = 0 ; n<4 ; n++)
  {
    momentumElectrons[2][n] = pVectorElectronBoosted[n];
  }
  
  pVectorElectron[1] = - pVectorElectron[1];
  pVectorElectron[2] = - pVectorElectron[2];
  pVectorElectron[3] = - pVectorElectron[3];
  
  pVectorElectronBoosted = boost(pVectorElectron, boostZ);
  for (int n = 0 ; n<4 ; n++)
  {
    momentumElectrons[3][n] = pVectorElectronBoosted[n];
  }
}

projetZElectronsGenerator::~projetZElectronsGenerator()
{
}

vector<G4double> projetZElectronsGenerator::boost(vector<G4double> p_i,vector<G4double> b)
{
    G4double b2=b[0]*b[0]+b[1]*b[1]+b[2]*b[2];
    G4double bx=b[0];
    G4double by=b[1];
    G4double bz=b[2];
    G4double g=1/sqrt(1-b2);
    G4double L[4][4]={{  g,        -bx*g,            -by*g,             -bz*g},
                   {-bx*g,  1+(g-1)*(bx*bx/b2), (g-1)*bx*by/b2, (g-1)*bx*bz/b2},
		   {-by*g, (g-1)*bx*by/b2,     1+(g-1)*by*by/b2,  (g-1)*bz*by/b2},
		   { -bz*g,  (g-1)*bx*bz/b2, (g-1)*bz*by/b2,    1+(g-1)*bz*bz/b2},
                  };
                  
    vector<G4double> p_i_boosted;            
     
    //boost             
    G4double P_temp[4];
	
    for (unsigned int i=0; i<4; i++) 
    {
	P_temp[i]=0; 
	
	for (unsigned int j=0; j<4; j++)
	{
	    P_temp[i] += L[i][j]*p_i[j];
	}
    }
    
    for (unsigned int i=0; i<4; i++) 
    {
	p_i_boosted.push_back(P_temp[i]);	
    }
    return p_i_boosted;
     
}

G4ThreeVector projetZElectronsGenerator::getDirectionElectron( int electron)
{
    G4double pElec = sqrt(momentumElectrons[electron][1]*momentumElectrons[electron][1] + momentumElectrons[electron][2]*momentumElectrons[electron][2] + momentumElectrons[electron][3]*momentumElectrons[electron][3]);
    G4ThreeVector moment(momentumElectrons[electron][1]/pElec,momentumElectrons[electron][2]/pElec,momentumElectrons[electron][3]/pElec);
    return moment;
}

G4double projetZElectronsGenerator::getEnergyElectron (int electron)
{
    return (momentumElectrons[electron][0] - 511.*keV) ;
}
    