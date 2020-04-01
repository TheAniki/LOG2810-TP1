/****************************************************************************
 * Fichier: Sommet.cpp
 * Auteurs: Ouassim Ouali (1958275) , Pier-Luc Tanguay (1953707) et Mélody Roy ()
 * Date: 22 Mars 2020
 * Description: Implémentation des méthodes de la classe Sommet
 ****************************************************************************/

#include "Sommet.h"
Sommet::Sommet() : numeroDuSommet_(0),presenceBorne_(false) {

}
Sommet::~Sommet()
{
	
}
Sommet::Sommet(int numeroDuSommet, bool presenceBorne) : numeroDuSommet_(numeroDuSommet) , presenceBorne_(presenceBorne)
{
}
/****************************************************************************
  * Fonction: Sommet::getNumeroDuSommet
  * Description: Méthode premettant d'accéder au numeroDuSommet_
  * Paramètres: aucun
  * Retour: int numeroDuSommet_
  ****************************************************************************/
int Sommet::getNumeroDuSommet()
{
	return numeroDuSommet_;
}
/****************************************************************************
  * Fonction: Sommet::getPresenceBorne
  * Description: Méthode permettant d'accéder à presenceBorne_ 
  * Paramètres: aucun
  * Retour: bool presenceBorne_
  ****************************************************************************/
bool Sommet::getPresenceBorne()
{
	return presenceBorne_;
}
/****************************************************************************
  * Fonction: Sommet::getSommetsAdjacents
  * Description: Permet d'accéder à la liste des sommetsAdjacents du sommet
  * Paramètres: aucun
  * Retour: liste des sommetsAdjacents_
  ****************************************************************************/
vector<pair<Sommet*, int>> Sommet::getSommetsAdjacents()
{
	return sommetsAdjacents_;
}
/****************************************************************************
  * Fonction: Sommet::ajouterSommetAdjacent
  * Description: Permet d'ajouter un sommetAdjacent et sa distance/temps
  * Paramètres: un pointeur Sommet et un integer temps
  * Retour: aucun
  ****************************************************************************/
void Sommet::ajouterSommetAdjacent(Sommet* sommetAdjacent, int temps)
{
	sommetsAdjacents_.push_back(make_pair(sommetAdjacent, temps));
	return;
}
/****************************************************************************
  * Fonction: Sommet::operator!=
  * Description: surcharge l'opérateur !=
  * Paramètres: un sommet a comparer
  * Retour: vrai si !=
  ****************************************************************************/
bool Sommet::operator!=(const Sommet sommet) const
{
	return sommet.numeroDuSommet_ != numeroDuSommet_;
}
