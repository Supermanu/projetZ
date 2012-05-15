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
#include "projetZTrackerHit.hh"

class projetZRunManager : public G4RunManager
{
public:
    projetZRunManager();
    ~projetZRunManager();
    virtual void EcrireEnergie ( G4double energie, G4double cell[][40] );
    virtual bool TrouverJets(G4double cell[40][40], G4int[][2]);
    virtual bool regarderAutour (G4double cell[42][42], int n, int k);
    virtual bool DetectionJets(G4Event* anEvent, G4int positionsJets[4][2]);
    virtual void DetectionTrace (G4Event* anEvent);
    virtual bool TrouverTrace( G4Event* anEvent,G4int positionsJets[4][2], G4int numeroJet);
    virtual G4double masseH ();

protected:
    virtual void AnalyzeEvent ( G4Event* anEvent );
    
private:
    G4double valeurTampon[1];
    G4double e1;
    G4double th1;
    G4double phi1;
    G4double e2;
    G4double th2;
    G4double phi2;
    G4double e3;
    G4double th3;
    G4double phi3;
    G4double e4;
    G4double th4;
    G4double phi4;
    
};

#endif // PROJETZRUNMANAGER_HH
