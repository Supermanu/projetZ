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


#ifndef PROJETZRUNMANAGER_HH
#define PROJETZRUNMANAGER_HH

#include <Geant4/G4RunManager.hh>
#include "projetZCaloHit.hh" 

class projetZRunManager : public G4RunManager
{
public:
    projetZRunManager();
    ~projetZRunManager();
    virtual void EcrireEnergie ( G4double energie, G4double cell[][40] );
    virtual void TrouverJets(G4double cell[40][40]);
    virtual bool regarderAutour (G4double cell[42][42], int n, int k);

protected:
    virtual void AnalyzeEvent ( G4Event* anEvent );
    G4double valeurTampon[1];
};

#endif // PROJETZRUNMANAGER_HH
