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
    
    virtual void setMassHiggs(G4double energie) {masseHiggs = energie;} ;
    virtual G4double getMassHiggs() const {return masseHiggs;} ;
    virtual G4ThreeVector getDirectionElectron( int electron) ;
    virtual G4ThreeVector getAnglesElectron(int electron);
    virtual vector< G4double > boost( vector< G4double > p_i, vector< G4double > b );
    virtual G4double getEnergyElectron(int electron);
    
protected:
    G4double masseHiggs;
    vector<G4double> angleZ;
    vector<G4double> angleElectron;
    G4double momentumElectrons[4][4];
    G4ThreeVector directionHiggs;
    
};

#endif // PROJETZELECTRONSGENERATOR_HH
