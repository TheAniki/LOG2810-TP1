/****************************************************************************
 * Fichier: Sommet.cpp
 * Auteurs: Ouassim Ouali (1958275) , Pier-Luc Tanguay (1953707) et M�lody Roy ()
 * Date: 22 Mars 2020
 * Description: Impl�mentation des m�thodes de la classe Sommet
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
  * Description: M�thode premettant d'acc�der au numeroDuSommet_
  * Param�tres: aucun
  * Retour: int numeroDuSommet_
  ****************************************************************************/
int Sommet::getNumeroDuSommet()
{
	return numeroDuSommet_;
}
/****************************************************************************
  * Fonction: Sommet::getPresenceBorne
  * Description: M�thode permettant d'acc�der � presenceBorne_ 
  * Param�tres: aucun
  * Retour: bool presenceBorne_
  ****************************************************************************/
bool Sommet::getPresenceBorne()
{
	return presenceBorne_;
}
/****************************************************************************
  * Fonction: Sommet::getSommetsAdjacents
  * Description: Permet d'acc�der � la liste des sommetsAdjacents du sommet
  * Param�tres: aucun
  * Retour: liste des sommetsAdjacents_
  ****************************************************************************/
vector<pair<Sommet*, int>> Sommet::getSommetsAdjacents()
{
	return sommetsAdjacents_;
}
/****************************************************************************
  * Fonction: Sommet::ajouterSommetAdjacent
  * Description: Permet d'ajouter un sommetAdjacent et sa distance/temps
  * Param�tres: un pointeur Sommet et un integer temps
  * Retour: aucun
  ****************************************************************************/
void Sommet::ajouterSommetAdjacent(Sommet* sommetAdjacent, int temps)
{
	sommetsAdjacents_.push_back(make_pair(sommetAdjacent, temps));
	return;
}
/****************************************************************************
  * Fonction: Sommet::operator!=
  * Description: surcharge l'op�rateur !=
  * Param�tres: un sommet a comparer
  * Retour: vrai si !=
  ****************************************************************************/
bool Sommet::operator!=(const Sommet sommet) const
{
	return sommet.numeroDuSommet_ != numeroDuSommet_;
}
