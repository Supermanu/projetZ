/*
    ProjetZ est un programme de simulation de la désintégration d'un boson de Higgs de 200 Gev
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


#ifndef projetZTrackerSD_h
#define projetZTrackerSD_h 1

#include "G4VSensitiveDetector.hh"
#include "projetZTrackerHit.hh"
class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class projetZTrackerSD : public G4VSensitiveDetector
{

public:
    projetZTrackerSD ( G4String name );
    ~projetZTrackerSD();

    void Initialize ( G4HCofThisEvent*HCE );
    G4bool ProcessHits ( G4Step*aStep,G4TouchableHistory*ROhist );
    void EndOfEvent ( G4HCofThisEvent*HCE );
    void clear();
    void DrawAll();
    void PrintAll();

private:
    projetZTrackerHitsCollection *trackerCollection;

public:
};




#endif

