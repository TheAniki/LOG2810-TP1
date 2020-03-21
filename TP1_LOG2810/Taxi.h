/****************************************************************************
 * Fichier:
 * Auteurs:
 * Date:
 * Description:
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


	void ajouterPassager(Passager* passager);
	void ajouterSommet(Sommet sommet);
	void enleverPassager(Passager* passager);

	void chargerTaxi();
	void modificationEnergieRestante(int energie);

	//methode lecture requete;
	void lireFichier();
	void placerPassager();

	//methode affichage
	void afficherRequetes();
	void afficherPassagerTaxi();

private:
	int energieRestante_;
	int positionDeDepart_;
	string nomFichier_;
	vector<string> listeFichierRequete_;
	vector<Passager*> listeRequete_;

	vector<pair<Passager*,int>> listePassagersTaxi_; // passager et  int priortie
	vector<Sommet> historiqueSommetsParcouru_;
};



#endif // !TAXI_H
