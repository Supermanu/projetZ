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


#include "projetZTrackerSD.hh"
#include "projetZTrackerHit.hh"
#include "G4Step.hh"
#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4ios.hh"

projetZTrackerSD::projetZTrackerSD(G4String name)
:G4VSensitiveDetector(name)
{
  G4String HCname;
  collectionName.insert(HCname="trackerCollection");
}

projetZTrackerSD::~projetZTrackerSD(){;}

void projetZTrackerSD::Initialize(G4HCofThisEvent* HCE)
{
  static int HCID = -1;
  trackerCollection = new projetZTrackerHitsCollection
                      (SensitiveDetectorName,collectionName[0]); 
  if(HCID<0)
  { HCID = GetCollectionID(0); }
  HCE->AddHitsCollection(HCID,trackerCollection);
}

G4bool projetZTrackerSD::ProcessHits(G4Step* aStep, G4TouchableHistory*)
{
  G4double edep = aStep->GetTotalEnergyDeposit();
  if(edep==0.) return false;

  projetZTrackerHit* newHit = new projetZTrackerHit();
  newHit->SetEdep( edep );
  newHit->SetPos( aStep->GetPreStepPoint()->GetPosition() );
  newHit->SetTrackerNb(aStep->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber() );
  trackerCollection->insert( newHit );

  return true;
}

void projetZTrackerSD::EndOfEvent(G4HCofThisEvent*)
{
}

void projetZTrackerSD::clear()
{
} 

void projetZTrackerSD::DrawAll()
{
} 

void projetZTrackerSD::PrintAll()
{
} 
