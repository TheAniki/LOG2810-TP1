/****************************************************************************
 * Fichier:
 * Auteurs:
 * Date:
 * Description:
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
	const int getId();

	bool operator==(const Passager& passager) const;
private:

	int id_; // idfentifiant
	int tempsArrivee_; // temps limite.
	int sommetDepart_; // numero du sommet de depart.
	int destination_; // numero du sommet a atteindre.
};


#endif // !PASSAGER_H
