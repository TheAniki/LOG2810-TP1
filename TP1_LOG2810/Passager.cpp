/****************************************************************************
 * Fichier: Passager.cpp
 * Auteurs: Ouassim Ouali (1958275) , Pier-Luc Tanguay () et Mélody Roy ()
 * Date: 22 Mars 2020
 * Description: Implémentation des méthodes de la classe Passager
 ****************************************************************************/
#include "Passager.h"

Passager::Passager() : id_(0), sommetDepart_(0),
destination_(0), tempsArrivee_(0)
{
}
Passager::Passager(int id, int sommetDepart, int destination, int tempsArrivee) : id_(id), sommetDepart_(sommetDepart),
	destination_(destination), tempsArrivee_(tempsArrivee)
{

}
Passager::~Passager()
{
	
}

/****************************************************************************
  * Fonction: Passager::getTempsArrivee
  * Description: Permet d'obtenir le tempsArrivee désirer du passger
  * Paramètres: aucun
  * Retour: tempsArrivee du passager
  ****************************************************************************/
const int Passager::getTempsArrivee()
{
	return tempsArrivee_;
}
/****************************************************************************
  * Fonction: Passager::getDestination
  * Description: Permet d'obtenir le numero du sommet de destination du passager
  * Paramètres: aucun
  * Retour: destination_
  ****************************************************************************/
const int Passager::getDestination()
{
	return destination_;
}
/****************************************************************************
  * Fonction: Passager::getSommetDepart
  * Description: Permet d'obtenir le Sommet de départ du passager
  * Paramètres: aucun
  * Retour: sommetDepart_
  ****************************************************************************/
const int Passager::getSommetDepart()
{
	return sommetDepart_;
}
/****************************************************************************
  * Fonction:  Passager::getId
  * Description: Permet d'obtenir l'identifiant du passager
  * Paramètres: aucun
  * Retour: id_
  ****************************************************************************/
const int Passager::getId()
{
	return id_;
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
  * Fonction: Passager::operator==
  * Description: surcharge de l'opérateur == 
				 pour faire les oprération Passager == Passager
  * Paramètres: un Passager passer par adresse
  * Retour: un bool true si passager1 == passager2 et false autrement
  ****************************************************************************/
bool Passager::operator==(const Passager& passager) const
{
	return (
		id_ == passager.id_ &&
		sommetDepart_ == passager.sommetDepart_ &&
		destination_ == passager.destination_ &&
		tempsArrivee_ == passager.tempsArrivee_
		);
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
	return o << " Passager # " << unPassager.id_ 
		<< " | Sommet de depart: " << unPassager.sommetDepart_ 
		<< " | Destination : " << unPassager.destination_ 
		<< " | tempsRestant : " << unPassager.tempsArrivee_ << endl;
	if (unPassager.tempsArrivee_ <= 0)
	{
		cout << "Temps expiree pour le passager " << unPassager.id_;
	}
}
