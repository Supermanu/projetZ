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


#ifndef PROJETZELECTRONSGENERATOR_HH
#define PROJETZELECTRONSGENERATOR_HH

#include "globals.hh"
#include <vector>
#include "G4ThreeVector.hh"

using namespace std;

class projetZElectronsGenerator
{

public:
    projetZElectronsGenerator();
    projetZElectronsGenerator ( const projetZElectronsGenerator& other );
    virtual ~projetZElectronsGenerator();
    
    virtual void setMassHiggs(G4double energie) {energieHiggs = energie;} ;
    virtual G4double getMassHiggs() const {return energieHiggs;} ;
    vector< double > boost( vector< double > p_i, vector< double > b );
    
    virtual vector<double> uniforpi();
    virtual double uniforme();
    
protected:
    G4double energieHiggs;
    vector<double> angleZ;
    vector<double> angleElectron;
    vector<double> energieElectrons[4];
    G4ThreeVector directionHiggs;
};

#endif // PROJETZELECTRONSGENERATOR_HH
