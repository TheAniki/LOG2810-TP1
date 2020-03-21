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
  * Param�tres:
  * Retour:
  ****************************************************************************/
int Sommet::getNumeroDuSommet()
{
	return numeroDuSommet_;
}
/****************************************************************************
  * Fonction:
  * Description:
  * Param�tres:
  * Retour:
  ****************************************************************************/
bool Sommet::getPresenceBorne()
{
	return presenceBorne_;
}
/****************************************************************************
  * Fonction:
  * Description:
  * Param�tres:
  * Retour:
  ****************************************************************************/
vector<pair<Sommet*, int>> Sommet::getSommetsAdjacents()
{
	return sommetsAdjacents_;
}
/****************************************************************************
  * Fonction:
  * Description:
  * Param�tres:
  * Retour:
  ****************************************************************************/
void Sommet::ajouterSommetAdjacent(Sommet* sommetAdjacent, int temps)
{
	sommetsAdjacents_.push_back(make_pair(sommetAdjacent, temps));
}
