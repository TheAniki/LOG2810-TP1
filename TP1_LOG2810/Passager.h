/****************************************************************************
 * Fichier: Passager.h
 * Auteurs: Ouassim Ouali (1958275) , Pier-Luc Tanguay () et Mélody Roy ()
 * Date: 22 Mars 2020
 * Description: Définition de la classe Passager des de ses méthodes
 ****************************************************************************/
#ifndef PASSAGER_H
#define PASSAGER_H
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h> 
#include <vector>
#include "Sommet.h"
using namespace std;

class Passager
{
public:
	Passager();
	Passager(int id, int sommetDepart , int destination, int tempsArrivee );
	~Passager();

	//methode get
	
	const int getTempsArrivee();
	const int getDestination();
	const int getSommetDepart();
	const int getSommetArrive();
	const int getId();
	const bool getDansTaxi();
	void setDansTaxi(bool dansTaxi);
	const bool getComplete();
	void setComplete(bool complete);


	void modifierTemps(int tempsAretirer);

	bool operator==(const Passager& passager) const;
	friend ostream& operator<<(ostream& o, const Passager& unPassager);
private:

	int id_; // identifiant
	int tempsArrivee_; // temps limite.	
	int sommetDepart_; // numero du sommet de depart.
	int sommetArrive_; // numero du sommet a atteindre.
	bool dansTaxi_;
	bool complete_;
};


#endif // !PASSAGER_H
