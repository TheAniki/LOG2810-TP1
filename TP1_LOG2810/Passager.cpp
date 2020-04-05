/****************************************************************************
 * Fichier: Passager.cpp
 * Auteurs: Ouassim Ouali (1958275) , Pier-Luc Tanguay (1953707) et Mélody Roy (1991902)
 * Date: 22 Mars 2020
 * Description: Implémentation des méthodes de la classe Passager
 ****************************************************************************/
#include "Passager.h"

Passager::Passager() : id_(0), sommetDepart_(0),
	sommetArrive_(0), tempsArrivee_(0), complete_(false), dansTaxi_(false), tempsDepasse_(false)
{
}
Passager::Passager(int id, int sommetDepart, int destination, int tempsArrivee) : id_(id), sommetDepart_(sommetDepart),
	sommetArrive_(destination), tempsArrivee_(tempsArrivee), complete_(false), dansTaxi_(false), tempsDepasse_(false)
{

}
Passager::~Passager()
{
	
}

//***************************************************************************
//Getters
//***************************************************************************

const int Passager::getTempsArrivee()
{
	return tempsArrivee_;
}

const int Passager::getDestination()
{
	return sommetArrive_;
}

const int Passager::getSommetDepart()
{
	return sommetDepart_;
}

const int Passager::getId()
{
	return id_;
}

const bool Passager::getDansTaxi()
{
	return dansTaxi_;
}

const bool Passager::getTempsDepasse()
{
	return tempsDepasse_;
}


const bool Passager::getComplete()
{
	return complete_;
}


//setters
void Passager::setDansTaxi(bool dansTaxi)
{
	dansTaxi_ = dansTaxi;
}

void Passager::setTempsDepasse(bool tempsDepasse)
{
	tempsDepasse_ = tempsDepasse;
}


void Passager::setComplete(bool complete)
{
	complete_ =  complete;
}

/****************************************************************************
  * Fonction: Passager::modifierTemps
  * Description: Permet de modifier le tempsArrivee
  * Paramètres: nouveauTemps
  * Retour: tempsArrivee du passager
  ****************************************************************************/
void Passager::modifierTemps(int tempsAretirer)
{
	tempsArrivee_ -= tempsAretirer;
	if (tempsArrivee_ <= 0)
	{
		tempsArrivee_ = 0;
	}
}

/****************************************************************************
  * Fonction: operator<<
  * Description: surcharge de l'opérateur <<
				 pour faire les oprération Passager == Passager
  * Paramètres: un ostream et le passager a afficher.
  * Retour: affichage o
  ****************************************************************************/
ostream& operator<<(ostream& o, const Passager& unPassager)
{
	return o << " Passager " << unPassager.id_ << " :" << endl
		 << "    Sommet De Depart : " << unPassager.sommetDepart_ << endl
		<< "    Sommet De Destination : " << unPassager.sommetArrive_ << endl
		<< "    Temps maximum tolere: " << unPassager.tempsArrivee_<< " min" << endl << endl; 	
}
