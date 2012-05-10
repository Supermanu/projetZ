#include<iostream>
#include <cstdlib>  // pour "rand"
#include <cmath>    // pour "acos", "log" et "sqrt"
#include <vector>
#include <time.h>


#include "globals.hh" // Pour inclure pi

using namespace std;

G4double distribUniforme() {
	// renvoie une variable pseudo aléatoire distribuée uniformément entre 0. et 1.
	return rand()/(G4double)RAND_MAX;
}

vector<G4double> uniforpi() {
	//renvoie une direction (un théta et un phi dans l'ordre)
	vector<G4double> dir;
	dir.push_back(distribUniforme()*2*pi);
	dir.push_back(distribUniforme()*pi);
	return dir;
}

double distribExpo(const double lambda) {
	// renvoie une variable pseudo aléatoire distribuée en exponentielle décroissante
	// u = expo(lambda) = -lambda log(1-R) si R est uniforme entre [0 et 1[
	double R;
	do {
		R = distribUniforme();
	} while (R==1);
	// rejette la valeur R = 1;
	return -lambda * log( 1 - R);
}

double distribGauss(const double mu, const double sigma) {
	// renvoie une variable pseudo aléatoire distribuée selon une gaussienne
	// w = gauss(mu, sig) = sqrt(2 u sig^2) cos (2 pi R) 
	// 	si R est uniforme entre [0 et 1] et 
	// 	si u est exponentielle avec lambda =1
	return sqrt(2*sigma*sigma*distribExpo(1)) * cos(2*pi*distribUniforme()) + mu;
}

	double norm(double x, double y, double a) {
	
	double resultat;
		resultat = (1/pi)*(y/((x-a)*(x-a)+y*y)); 
	return resultat;
	}


double breitWigner(double y, double a){
	srand(time(NULL)); // initialisation de rand
    
	//créer 2 nombre aléatoire dans un cadre allant de 197 à 203 et variant en hauteur de 0 à 100
	double nombre_aleatoire[2];
	//je donne des valeurs au 2 nombres pour faire démarrer le while
	nombre_aleatoire[1]=1/(pi*y);
	nombre_aleatoire[0]=a;

    	double masse; 
	while (nombre_aleatoire[1] > norm(nombre_aleatoire[0],y,a))
	{
		
	nombre_aleatoire[0] = rand()/RAND_MAX*(a+10);
	nombre_aleatoire[1] = rand()/RAND_MAX*(1/(pi*y));
		
		
		if  (nombre_aleatoire[1] <= norm(nombre_aleatoire[0],y,a))
		{ 	
			masse = nombre_aleatoire[0];
			//cout<< nombre_aleatoire[0] << endl;
			//cout<< nombre_aleatoire[1] << endl;
			//cout<< norm(nombre_aleatoire[0],y,a) << endl;
			
			
		}

	}
   

	//system("PAUSE");

return masse;
  
}