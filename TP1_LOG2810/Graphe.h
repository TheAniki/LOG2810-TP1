/****************************************************************************
 * Fichier:
 * Auteurs:
 * Date:
 * Description:
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
	string getNomFichier(); const
	vector<Sommet*> getSommets(); const
	int getNbSommets(); const
	vector<string> getListeDonnees(); const
	//methode modification
	void modifierNomFichier(const string& nouveauNomFichier);
	
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
	int nbSommets; 
};


#endif // !GRAPHE_H

