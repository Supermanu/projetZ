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

#include "projetZTrackerHit.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4UnitsTable.hh"
#include "G4AttValue.hh"
#include "G4AttDef.hh"
#include "G4AttCheck.hh"

G4Allocator<projetZTrackerHit> projetZTrackerHitAllocator;

projetZTrackerHit::projetZTrackerHit() {}

projetZTrackerHit::~projetZTrackerHit() {}

projetZTrackerHit::projetZTrackerHit(const projetZTrackerHit& right)   //on demande l'objet dans notre constructeur de cet objet?! fonction right???
  : G4VHit()
{
  edep = right.edep;
  pos = right.pos;
  trackerNb = right.trackerNb;
}

projetZTrackerHit& projetZTrackerHit::operator=(const projetZTrackerHit& right)
{
  edep = right.edep;
  trackerNb = right.trackerNb;
  pos = right.pos;
  return *this;
}

G4int projetZTrackerHit::operator==(const projetZTrackerHit& right) const
{
  return (this==&right) ? 1 : 0;
}

std::map<G4String,G4AttDef> projetZTrackerHit::fAttDefs;

void projetZTrackerHit::Draw()
{
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if(pVVisManager)
  {
    G4Circle circle(pos);
    circle.SetScreenSize(0.04);
    circle.SetFillStyle(G4Circle::filled);
    G4Colour colour(1.,0.,0.);
    G4VisAttributes attribs(colour);
    circle.SetVisAttributes(attribs);
    pVVisManager->Draw(circle);
  }
}

const std::map<G4String,G4AttDef>* projetZTrackerHit::GetAttDefs() const
{
  // G4AttDefs have to have long life.  Use static member...
  if (fAttDefs.empty()) {
    fAttDefs["HitType"] =
      G4AttDef("HitType","Type of hit","Physics","","G4String");
  }
  return &fAttDefs;
}

std::vector<G4AttValue>* projetZTrackerHit::CreateAttValues() const
{
  // Create expendable G4AttsValues for picking...
  std::vector<G4AttValue>* attValues = new std::vector<G4AttValue>;
  attValues->push_back
    (G4AttValue("HitType","projetZTrackerHit",""));
  //G4cout << "Checking...\n" << G4AttCheck(attValues, GetAttDefs());
  return attValues;
}

void projetZTrackerHit::Print()
{;}


