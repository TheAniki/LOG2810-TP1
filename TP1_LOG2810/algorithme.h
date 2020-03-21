/****************************************************************************
 * Fichier:
 * Auteurs:
 * Date:
 * Description:
 ****************************************************************************/
#ifndef ALGORITHME_H
#define ALGORITHME_H

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h> 
#include <vector>
#include <sstream>
#include "Sommet.h"
#include "Taxi.h"
#include "Graphe.h"
using namespace std;

struct Trajet
{
	vector<Sommet> listeSommetParcouru;
	int distanceTotale;
};

class Algorithme
{
public:
	Algorithme();
	~Algorithme();

	Trajet plusCourtChemin(int depart, int arrivee);

private:
	vector<Trajet> listeTrajets_;
	Graphe graphe_;
};


#endif // !ALGORITHME_H

