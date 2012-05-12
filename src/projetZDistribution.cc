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


#include "projetZDistribution.hh"

#include<iostream>
#include <cstdlib>  // pour "rand"
#include <cmath>    // pour "acos", "log" et "sqrt"
#include <vector>
#include <time.h>

G4double distribUniforme()
{
    // renvoie une variable pseudo aléatoire distribuée uniformément entre 0. et 1.
    return rand() / ( G4double ) RAND_MAX;
}

G4double distribExpo ( const G4double lambda )
{
    // renvoie une variable pseudo aléatoire distribuée en exponentielle décroissante
    // u = expo(lambda) = -lambda log(1-R) si R est uniforme entre [0 et 1[
    G4double R;
    do {
        R = distribUniforme();
    } while ( R==1 );
    // rejette la valeur R = 1;
    return -lambda * log ( 1 - R );
}

G4double distribGauss ( const G4double mu, const G4double sigma )
{
    // renvoie une variable pseudo aléatoire distribuée selon une gaussienne
    // w = gauss(mu, sig) = sqrt(2 u sig^2) cos (2 pi R)
    // 	si R est uniforme entre [0 et 1] et
    // 	si u est exponentielle avec lambda =1
    return sqrt ( 2*sigma*sigma*distribExpo ( 1 ) ) * cos ( 2*pi*distribUniforme() ) + mu;
}

void uniforpi(G4double resultat[])
{
    //renvoie une direction (un théta et un phi dans l'ordre)
    resultat[0] = distribUniforme() *2*pi;
    resultat[1] = distribUniforme() *pi;
}

G4double normm ( G4double x, G4double y, G4double a )
{

    G4double resultat;
    resultat = ( 1/pi ) * ( y/ ( ( x-a ) * ( x-a ) +y*y ) );
    return resultat;
}

G4double bw ( G4double x, G4double y, G4double a )
{

    G4double resultat;
    resultat = ( 1/pi ) * ( y/ ( ( x-a ) * ( x-a ) +y*y ) );
    return resultat;
}

G4double breitWigner ( G4double y, G4double a )
{
    srand ( time ( NULL ) ); // initialisation de rand

    //créer 2 nombre aléatoire dans un cadre allant de 197 à 203 et variant en hauteur de 0 à 100
    G4double nombre_aleatoire[2];
    //je donne des valeurs au 2 nombres pour faire démarrer le while
    nombre_aleatoire[1]=1/ ( pi*y ) +1;
    nombre_aleatoire[0]=a;


    G4double masse;
    while ( nombre_aleatoire[1] > bw ( nombre_aleatoire[0],y,a ) ) {

        G4double t1=rand();
        G4double t2 = rand();

        nombre_aleatoire[0] = a+ ( -10+ ( t1/RAND_MAX ) * ( 20 ) );
        nombre_aleatoire[1] = G4double ( t2/RAND_MAX ) * ( 1/ ( pi*y ) );

        if ( nombre_aleatoire[1] <= bw ( nombre_aleatoire[0],y,a ) ) {
            masse = nombre_aleatoire[0];
        }
    }
    return masse;
}

projetZDistribution::projetZDistribution (G4double resultat[], G4String category, G4double argument1, G4double argument2)
{
  if (category == "distribExpo")
  {
	resultat[0] = distribExpo(argument1);
  }
  else if (category == "distribGauss")
  {
      resultat[0] = distribGauss(argument1, argument2);
  }
  else if (category == "distribUniforme")
  {
      resultat[0] = distribUniforme();
  }
  else if (category == "uniforpi")
  {
      uniforpi(resultat);
  }
  else if (category == "breitWigner")
  {
      resultat[0] = breitWigner(argument1,argument2);
  }
  else
  {
      G4cout << "ERREUR, catégorie inconnue  !! Valeur par défaut: 1" << G4endl;
      resultat[0]=1;
  }
}

projetZDistribution::~projetZDistribution()
{}


