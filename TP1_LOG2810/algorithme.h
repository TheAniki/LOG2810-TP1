/****************************************************************************
 * Fichier: algorithme.h
 * Auteurs: Ouassim Ouali (1958275) , Pier-Luc Tanguay () et Mélody Roy ()
 * Date: 22 Mars 2020
 * Description: Initialisation de la classe Algorithme et 
				définition de la struct Trajet et des méthodes de l'algorithme
 ****************************************************************************/
#ifndef ALGORITHME_H
#define ALGORITHME_H

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h> 
#include <vector>
#include <sstream>
#include <algorithm>
#include "Sommet.h"
#include "Taxi.h"
#include "Graphe.h"
using namespace std;

// structure Trajet utilise pour avoir des trajets dans la liste de trajets
struct Trajet
{
	vector<Sommet> listeSommetParcouru;
	int distanceTotale;	
};


class Algorithme
{
public:
	Algorithme();
	Algorithme(Graphe graphe, Taxi taxi);
	~Algorithme();
	vector<Trajet> getListeTrajetsPossible();
	Graphe getGraphe();
	Taxi getTaxi();


	void ajouterTrajet(Trajet trajet);
	void ajouterTrajetSiPlusCourt(Trajet trajet);

	void EffacerTousLesTrajets();
	void EffacerUnTrajet(Trajet trajet);

	void trierListeSelonDistance();

	//bool comparerDistance(Trajet trajetAComparer,Trajet trajetDeLaListe);
	//bool operator<(const Trajet& trajetAComparer); const

	Trajet plusCourtChemin(int depart, int arrivee);

private:
	vector<Trajet> listeTrajetsPossible_; // contient la liste des trajets possible
	Graphe graphe_;
	Taxi taxi_;
};


#endif // !ALGORITHME_H

