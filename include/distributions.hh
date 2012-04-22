#include<iostream>
#include <cstdlib>  // pour "rand"
#include <cmath>    // pour "acos", "log" et "sqrt"
#include <vector>

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

