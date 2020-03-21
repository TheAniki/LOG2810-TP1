/****************************************************************************
 * Fichier:
 * Auteurs:
 * Date:
 * Description:
 ****************************************************************************/

#include "Sommet.h"
Sommet::Sommet():numeroDuSommet_(0),presenceBorne_(false) {

}
Sommet::~Sommet()
{

}
Sommet::Sommet(int numeroDuSommet, bool presenceBorne) : numeroDuSommet_(numeroDuSommet) , presenceBorne_(presenceBorne)
{
}
/****************************************************************************
  * Fonction:
  * Description:
  * Paramètres:
  * Retour:
  ****************************************************************************/
int Sommet::getNumeroDuSommet()
{
	return numeroDuSommet_;
}
/****************************************************************************
  * Fonction:
  * Description:
  * Paramètres:
  * Retour:
  ****************************************************************************/
bool Sommet::getPresenceBorne()
{
	return presenceBorne_;
}
/****************************************************************************
  * Fonction:
  * Description:
  * Paramètres:
  * Retour:
  ****************************************************************************/
vector<pair<Sommet*, int>> Sommet::getSommetsAdjacents()
{
	return sommetsAdjacents_;
}
/****************************************************************************
  * Fonction:
  * Description:
  * Paramètres:
  * Retour:
  ****************************************************************************/
void Sommet::ajouterSommetAdjacent(Sommet* sommetAdjacent, int temps)
{
	sommetsAdjacents_.push_back(make_pair(sommetAdjacent, temps));
}
