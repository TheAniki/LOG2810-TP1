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
 //   EffacerTousSommetsAdjacents();
}
Sommet::Sommet(int numeroDuSommet, bool presenceBorne) : numeroDuSommet_(numeroDuSommet) , presenceBorne_(presenceBorne)
{
}

// Getters
const int Sommet::getNumeroDuSommet()
{
	return numeroDuSommet_;
}

const bool Sommet::getPresenceBorne()
{
	return presenceBorne_;
}

const vector<pair<Sommet*, int>> Sommet::getSommetsAdjacents()
{
	return sommetsAdjacents_;
}

const int Sommet::getTempsParent()
{
    return tempsParent_;
}

//Setters
void Sommet::setTempsParent(int distance)
{
   tempsParent_ = distance;
}

/****************************************************************************
  * Fonction: Sommet::EffacerTousSommetsAdjacents
  * Description: Méthode permettant d'effacer tous les sommets adjcents 
                 de la liste de sommetsAdjacents_
  * Paramètres: aucun
  * Retour: aucun
  ****************************************************************************/
void Sommet::EffacerTousSommetsAdjacents()
{
    for (auto it : sommetsAdjacents_)
    {
        if (it.first != nullptr) {
            it.first = nullptr;
            delete(it.first);
        }
    }
    sommetsAdjacents_.clear();
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
