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


#ifndef PROJETZDISTRIBUTION_HH
#define PROJETZDISTRIBUTION_HH

#include "globals.hh"

class projetZDistribution
{
public:
    projetZDistribution ( G4double resultat[], G4String category, G4double argument1=0, G4double argument2=0 );
    ~projetZDistribution();
};

#endif // PROJETZDISTRIBUTION_HH
