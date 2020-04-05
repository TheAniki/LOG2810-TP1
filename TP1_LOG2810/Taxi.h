/****************************************************************************
 * Fichier: Taxi.h
 * Auteurs: Ouassim Ouali (1958275) , Pier-Luc Tanguay (1953707) et Mélody Roy (1991902)
 * Date: 22 Mars 2020
 * Description: Définition de la classe Taxi des de ses méthodes
 ****************************************************************************/
#ifndef TAXI_H
#define TAXI_H
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h> 
#include <vector>
#include <sstream>
#include <algorithm>
#include "Sommet.h"
#include "Passager.h"
#include "Graphe.h"
using namespace std;


const int NB_PLACES_TAXI = 4;


class Taxi : public Graphe, public Sommet
{
public:
	Taxi();
	Taxi(string nomFichier);
	~Taxi();

	const int getPositionDepart();
	const int getPositionActuelle();
	const vector<Passager*> getListePassager();


	void setPositionActuelle(int numeroDestination);

	// Requetes
	void EffacerTousRequetes();
	void miseAjourRequetes();
	const vector<Passager*> getListeRequetes();

	// Passagers
	void ajouterPassager(Passager* passager);
	void ajouterSommet(Sommet* sommet);
	void enleverPassager(Passager* passager);

	// Batteries
	const int getBatterieRestante();
	void chargerTaxi();
	void miseAJourBatterie(int distanceParcouru);

	// methode lecture requete;
	void lireFichier();
	void placerPassagerDansGraphe();

	// methode affichage
	void afficherRequetes();	

private:
	int batterieRestante_;
	int positionDeDepart_;
	int positionActuelle_;
	string nomFichier_;
	vector<string> listeFichierRequete_;
	vector<Passager*> listeRequete_;
	vector<Passager*> listePassagersTaxi_;
	vector<Sommet*> historiqueSommetsParcouru_;
};



#endif // !TAXI_H#pragma once
