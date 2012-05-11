#ifndef DISTRIBUTION_HH
#define DISTRIBUTION_HH

#include<iostream>
#include <cstdlib>  // pour "rand"
#include <cmath>    // pour "acos", "log" et "sqrt"
#include <vector>
#include <time.h>


#include "globals.hh" // Pour inclure pi


using namespace std;

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

vector<G4double> uniforpi()
{
    //renvoie une direction (un théta et un phi dans l'ordre)
    vector<G4double> dir;
    dir.push_back ( distribUniforme() *2*pi );
    dir.push_back ( distribUniforme() *pi );
    return dir;
}

G4double normm ( G4double x, G4double y, G4double a )
{

    G4double resultat;
    resultat = ( 1/pi ) * ( y/ ( ( x-a ) * ( x-a ) +y*y ) );
    return resultat;
}

double bw(double x, double y, double a) {
	
	double resultat;
		resultat = (1/pi)*(y/((x-a)*(x-a)+y*y)); 
	return resultat;
	}
	
double breitWigner(double y, double a){
	srand(time(NULL)); // initialisation de rand
    
	//créer 2 nombre aléatoire dans un cadre allant de 197 à 203 et variant en hauteur de 0 à 100
	double nombre_aleatoire[2];
	//je donne des valeurs au 2 nombres pour faire démarrer le while
	nombre_aleatoire[1]=1/(pi*y)+1;
	nombre_aleatoire[0]=a;
	
	
    	double masse; 
	while (nombre_aleatoire[1] > bw(nombre_aleatoire[0],y,a))
	{
	
	double t1=rand();
	double t2 = rand();
	
	nombre_aleatoire[0] = a+(-10+(t1/RAND_MAX)*(20));
	nombre_aleatoire[1] = double(t2/RAND_MAX)*(1/(pi*y));
	
		if  (nombre_aleatoire[1] <= bw(nombre_aleatoire[0],y,a))
		{ 	
			masse = nombre_aleatoire[0];
			
			
		}

	}
   


		
	//system("PAUSE");

return masse;	}

#endif
