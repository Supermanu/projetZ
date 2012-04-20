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


#include "projetZElectronsGenerator.hh"
#include "G4ios.hh"
#include <cmath>

// Je crois que Geant4 travaille en Mev

projetZElectronsGenerator::projetZElectronsGenerator() : energieHiggs(200000.0), directionHiggs(0,0,1)
{
  srand(time(NULL));

}

projetZElectronsGenerator::~projetZElectronsGenerator()
{
}

vector<double> projetZElectronsGenerator::boost(vector<double> p_i,vector<double> b)
{
    double b2=b[0]*b[0]+b[1]*b[1]+b[2]*b[2];
    double bx=b[0];
    double by=b[1];
    double bz=b[2];
    double g=1/sqrt(1-b2);
    double L[4][4]={{  g,        -bx*g,            -by*g,             -bz*g},
                   {-bx*g,  1+(g-1)*(bx*bx/b2), (g-1)*bx*by/b2, (g-1)*bx*bz/b2},
		   {-by*g, (g-1)*bx*by/b2,     1+(g-1)*by*by/b2,  (g-1)*bz*by/b2},
		   { -bz*g,  (g-1)*bx*bz/b2, (g-1)*bz*by/b2,    1+(g-1)*bz*bz/b2},
                  };
                  
    vector<double> p_i_boosted;            
     
    //boost             
    double P_temp[4];
	
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

vector<double> projetZElectronsGenerator::uniforpi() {
	//renvoie une direction (un théta et un phi dans l'ordre)
	const G4double pi = 3.14159265;
	vector<double> dir;
	dir.push_back(uniforme() * 2 * pi);
	dir.push_back(uniforme() * pi);
// 	cout << "Angles aléatoires générés (en radian)" << endl;
// 	cout << dir[0] << " et " << dir[1];
	return dir;
}

double projetZElectronsGenerator::uniforme() 
{
    srand(rand());
    return rand()/(double)RAND_MAX;
  
}
    