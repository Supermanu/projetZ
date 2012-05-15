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


#ifndef PROJETZTRACKERHIT_H
#define PROJETZTRACKERHIT_H

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class projetZTrackerHit : public G4VHit
{

public:
    
      projetZTrackerHit();
      projetZTrackerHit(const projetZTrackerHit& );
      ~projetZTrackerHit();
      
      
      virtual projetZTrackerHit& operator=(const projetZTrackerHit& );
      G4int operator==(const projetZTrackerHit& ) const;

      inline void *operator new(size_t);
      inline void operator delete(void *aHit);

      void Draw();
      const std::map<G4String,G4AttDef>* GetAttDefs() const;
      std::vector<G4AttValue>* CreateAttValues() const;
      void Print();

private:
      G4double edep;
      G4ThreeVector pos;
      G4int trackerNb;
      static std::map<G4String,G4AttDef> fAttDefs;

public:
      inline void SetEdep(G4double de)
      { edep = de; }
      inline G4double GetEdep()
      { return edep; }
      inline void SetPos(G4ThreeVector xyz)
      { pos = xyz; }
      inline G4ThreeVector GetPos()
      { return pos; }
      inline G4int GetTrackerNb()
      {return trackerNb;}
      inline void SetTrackerNb(G4int Nb)
      { trackerNb = Nb; }

};

typedef G4THitsCollection<projetZTrackerHit> projetZTrackerHitsCollection;

extern G4Allocator<projetZTrackerHit> projetZTrackerHitAllocator;

inline void* projetZTrackerHit::operator new(size_t)
{
  void *aHit;
  aHit = (void *) projetZTrackerHitAllocator.MallocSingle();
  return aHit;
}

inline void projetZTrackerHit::operator delete(void *aHit)
{
  projetZTrackerHitAllocator.FreeSingle((projetZTrackerHit*) aHit);
}

#endif