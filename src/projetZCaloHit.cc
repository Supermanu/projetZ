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


#include "projetZCaloHit.hh"
#include "G4UnitsTable.hh"

G4Allocator<projetZCaloHit> projetZCaloHitAllocator;

projetZCaloHit::projetZCaloHit() {}
projetZCaloHit::~projetZCaloHit() {}


projetZCaloHit::projetZCaloHit ( const projetZCaloHit& other ) :G4VHit()
{
    trackID = other.trackID;
    caloNb = other.caloNb;
    eDep = other.eDep;
}

projetZCaloHit& projetZCaloHit::operator= ( const projetZCaloHit& other )
{
    trackID = other.trackID;
    caloNb = other.caloNb;
    eDep = other.eDep;
    return *this;
}

G4int projetZCaloHit::operator== ( const projetZCaloHit& other ) const
{
    return ( this==&other ) ? 1 : 0;
}

void projetZCaloHit::Draw()
{
    G4VHit::Draw(); ///TODO
}

void projetZCaloHit::Print()
{
    G4cout << "TrackID: " << trackID << "  caloNb: " << caloNb
           << "  energy deposit: " << G4BestUnit ( eDep,"Energy" );
}
