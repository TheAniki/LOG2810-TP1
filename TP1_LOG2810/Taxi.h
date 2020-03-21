/****************************************************************************
 * Fichier: Taxi.h
 * Auteurs: Ouassim Ouali (1958275) , Pier-Luc Tanguay () et Mélody Roy ()
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
//int autonomie = 100; // 100% d'autonomie;



class Taxi : public Graphe , public Sommet
{
public:
	Taxi();
	Taxi(string nomFichier);
	~Taxi();
	//mise a jour requete
	void EffacerTousRequetes();
	void miseAjourRequetes();


	void ajouterPassager(Passager passager);
	void ajouterSommet(Sommet sommet);
	void enleverPassager(Passager passager);

	void chargerTaxi();
	void modificationEnergieRestante(int energie);

	//bool trierSelonId(Passager passager1, Passager passager2);

	//bool operator<(Passager& passager1, Passager& passager2);

	//methode lecture requete;
	void lireFichier();
	void placerPassagerDansGraphe();

	//methode affichage
	void afficherRequetes();
	void afficherPassagerTaxi();

	void trierSelonId();

private:
	int energieRestante_;
	int positionDeDepart_;
	string nomFichier_;
	vector<string> listeFichierRequete_;
	vector<Passager*> listeRequete_;

	vector<Passager> listePassagersTaxi_;
	vector<Sommet> historiqueSommetsParcouru_;
};



#endif // !TAXI_H
