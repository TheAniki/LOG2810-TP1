/****************************************************************************
 * Fichier: algorithme.h
 * Auteurs: Ouassim Ouali (1958275) , Pier-Luc Tanguay (1953707) et Mélody Roy (1991902)
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

const int SEUIL_RECHARGE = 15;

// structure Trajet utilise pour avoir des trajets dans la liste de trajets
struct Trajet
{
	vector<Sommet*> listeSommetParcouru;
	int distanceTotale;
	enum Type_T {recharge, recupere, destination};
	Type_T type;
};


class Algorithme
{
public:
	Algorithme();
	Algorithme(const Graphe& graphe, const Taxi& taxi);
	~Algorithme();
	vector<Trajet> getListeTrajetsPossible();
	Graphe getGraphe();
	Taxi getTaxi();


	void ajouterTrajet(Trajet trajet);	

	void EffacerTousLesTrajets();
	void EffacerUnTrajet(Trajet trajet);
	
	Trajet dijkstra(int numeroSommetDepart, int numeroSommetArrive);
	void plusCourtChemin(int numeroSommetDepart, int numeroSommetArrive);
	void traiterRequetes();
	Trajet conduireVersSommet(int numeroSommetDestination);

	Trajet trajetRecharger(int numeroPositionActuelle);
	Trajet miseAJoutTrajetFinal(const Trajet& trajet, Trajet trajetFinal);
	Trajet prochainTrajet(int positionActuelle, Passager* requeteCourante);
	void miseAJourTaxi(Trajet trajet);

private:
	vector<Trajet> listeTrajetsEffectue; // contient la liste des trajets possible
	Graphe graphe;
	Taxi taxi;
};


#endif // !ALGORITHME_H

