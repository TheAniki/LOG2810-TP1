/****************************************************************************
 * Fichier: Graphe.h
 * Auteurs: Ouassim Ouali (1958275) , Pier-Luc Tanguay (1953707) et Mélody Roy (1991902)
 * Date: 22 Mars 2020
 * Description: Définition de la classe Graphe
 ****************************************************************************/
#ifndef GRAPHE_H
#define GRAPHE_H


#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h> 
#include <vector>
#include <sstream>
#include "Sommet.h"

using namespace std;


//methode generale de converstion :
vector<string> split(const string& s, char delim);
int convertStringtoInt(string ligne);
bool convertStringtoBool(string ligne);

class Graphe
{
public:
	Graphe();
	Graphe(string nomFichier);
	~Graphe();

	//methode d'acces	
	const vector<Sommet*> getSommets();
	const int getNbSommets();
	const vector<int> getSommetsRecharge();
		
	//reste des fonctions
	void creerGraphe();
	void AffichageGraphe();
	void EffacerTousSommets();
	void miseAJourGraphe();
	void lireFichier();
	
	Sommet* chercherSommet(int numeroSommet);

private:
	string nomFichier_;
	vector<Sommet*> sommets_;
	vector<string> listeDonnees_;
	vector<int> listeSommetsRecharge_;
	int nbSommets;
};


#endif // !GRAPHE_H

