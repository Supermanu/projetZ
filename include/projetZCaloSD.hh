/*
    <one line to give the program's name and a brief idea of what it does.>
    Copyright (C) 2012  Manuel Tondeur <manueltondeur@gmail.com>>

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


#ifndef PROJETZCALOSD_H
#define PROJETZCALOSD_H

#include "projetZCaloHit.h" 
#include <G4VSensitiveDetector.hh>

class G4Step;
class G4HCofThisEvent;

class projetZCaloSD : public G4VSensitiveDetector
{

public:
    projetZCaloSD ( G4String name );
    ~projetZCaloSD();
    virtual void Initialize ( G4HCofThisEvent* );
    virtual void EndOfEvent ( G4HCofThisEvent* );
    G4bool ProcessHits ( G4Step* aStep, G4TouchableHistory* );
private:
    projetZCaloHitsCollection* caloCollection;
};

#endif // PROJETZCALOSD_H
