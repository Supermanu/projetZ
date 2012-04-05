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


#ifndef PROJETZCALOHIT_H
#define PROJETZCALOHIT_H

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"

class projetZCaloHit : public G4VHit
{

public:
    
    projetZCaloHit();
    projetZCaloHit ( const projetZCaloHit& );
    virtual ~projetZCaloHit();
    virtual projetZCaloHit& operator= ( const projetZCaloHit& );
    virtual G4int operator== ( const projetZCaloHit& ) const;
    
    inline void* operator new(size_t);
    inline void  operator delete(void*);
    
    virtual void Draw();
    virtual void Print();

public:
  
    void SetTrackID  (G4int track)      { trackID = track; };
    void SetCaloNb(G4int calo)      { caloNb = calo; };  
    void SetEdep     (G4double de)      { eDep = de; };
    
private:
  
    G4int trackID;
    G4int caloNb;
    G4double eDep;
};

// On utilise le template donné par G4THitsCollection pour définir une collection de hit
typedef G4THitsCollection<projetZCaloHit> projetZCaloHitCollection;

extern G4Allocator<projetZCaloHit> projetZCaloHitAllocator;

// Je crois que ces inlines servent à allouer dynamiquement la mémoire des hits lorsqu'on utilise operator... 
// Mais je comprends pas vraiment comment ça marche. Si quelqu'un a une idée ?

inline void* projetZCaloHit::operator new(size_t)
{
  void *aHit;
  aHit = (void *) projetZCaloHitAllocator.MallocSingle();
  return aHit;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void projetZCaloHit::operator delete(void *aHit)
{
  projetZCaloHitAllocator.FreeSingle((projetZCaloHit*) aHit);
}
#endif // PROJETZCALOHIT_H
