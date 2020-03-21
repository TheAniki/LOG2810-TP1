/****************************************************************************
 * Fichier:
 * Auteurs:
 * Date:
 * Description:
 ****************************************************************************/
#ifndef SOMMET_H
#define SOMMET_H
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h> 
#include <vector>
using namespace std;


class Sommet
{
public:
	Sommet();	
	~Sommet();
	Sommet(int numeroDuSommet, bool presenceBorne); //constructeur par parametre
	//methode d'acces
	int getNumeroDuSommet();
	bool getPresenceBorne();
	vector<pair<Sommet*, int>> getSommetsAdjacents();
	void ajouterSommetAdjacent(Sommet* sommetAdjacent, int temps);


private:
	vector<pair<Sommet*, int>> sommetsAdjacents_; //Sommet : pour le sommet et int pour le temps entre les 2
	int numeroDuSommet_;
	bool presenceBorne_;
};


#endif // !SOMMET_H

