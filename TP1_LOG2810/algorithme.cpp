/****************************************************************************
 * Fichier: algorithme.cpp
 * Auteurs: Ouassim Ouali (1958275) , Pier-Luc Tanguay () et Mélody Roy ()
 * Date: 22 Mars 2020
 * Description: Implémentation des méthodes utilisée pour l'algorithme
 ****************************************************************************/
#include"algorithme.h"
#include <queue>

Algorithme::Algorithme()
{
}
Algorithme::Algorithme(Graphe graphe, Taxi taxi) : graphe_(graphe), taxi_(taxi)
{
	
}

Algorithme::~Algorithme()
{
	EffacerTousLesTrajets();
}
/****************************************************************************
  * Fonction: Algorithme::getListeTrajetsPossible
  * Description: Permet d'obtenir la liste des trajet possibles
  * Paramètres: aucun
  * Retour: liste des trajets possible
  ****************************************************************************/
vector<Trajet> Algorithme::getListeTrajetsPossible()
{
	return listeTrajetsPossible_;
}
/****************************************************************************
  * Fonction: Algorithme::getGraphe
  * Description: Permet d'obtenir le graphe
  * Paramètres: aucun
  * Retour: le graphe
  ****************************************************************************/
Graphe Algorithme::getGraphe()
{
	return graphe_;
}
/****************************************************************************
  * Fonction: Algorithme::getTaxi
  * Description: Permet d'obtenir le taxi
  * Paramètres: aucun
  * Retour: le taxi
  ****************************************************************************/
Taxi Algorithme::getTaxi()
{
	return taxi_;
}
/****************************************************************************
  * Fonction: Algorithme::ajouterTrajet
  * Description:  Permet d'ajouter un trajet à la liste des trajets possible
				  puis trie les elements selon leurs distances (depart,arrivee)
  * Paramètres: un trajet de type Trajet
  * Retour: aucun
  ****************************************************************************/
void Algorithme::ajouterTrajet(Trajet trajet)
{
	// TODO : Px etre ajouter un if pour ne pas ajouter le trajet s'il est deja present dans la liste
	listeTrajetsPossible_.push_back(trajet);

	// permet de trier la liste des trajet selon leur distance, en ordre croissant
	trierListeSelonDistance();
	
}
/****************************************************************************
  * Fonction: Algorithme::ajouterTrajetSiPlusCourt
  * Description: Permet d'ajouter un Trajet seulement si la distance est inférieur 
				 au trajet le plus court de la listeTrajetPossible 
  * Paramètres: le Trajet à ajouter
  * Retour: aucun
  ****************************************************************************/
void Algorithme::ajouterTrajetSiPlusCourt(Trajet trajet)
{
	if (listeTrajetsPossible_[0].distanceTotale > trajet.distanceTotale)
	{
		ajouterTrajet(trajet);
	}
}
/****************************************************************************
  * Fonction: Algorithme::EffacerTousLesTrajets
  * Description: Permet d'effacer tous les trajets de la liste
  * Paramètres: aucun
  * Retour: aucun
  ****************************************************************************/
void Algorithme::EffacerTousLesTrajets()
{
	listeTrajetsPossible_.clear();
}
/****************************************************************************
  * Fonction: Algorithme::EffacerUnTrajet
  * Description: Permet d'effacer le trajet passer en paramètre de la liste
  * Paramètres: Trajet
  * Retour: aucun
  ****************************************************************************/
void Algorithme::EffacerUnTrajet(Trajet trajet)
{
	bool TrajetPresent = false;
	vector<Trajet>::iterator it;
	it = listeTrajetsPossible_.begin();
	for (auto i = 0; i < listeTrajetsPossible_.size(); i++)
	{
		for (auto j = 0; j < trajet.listeSommetParcouru.size(); j++)
		{
			if (listeTrajetsPossible_[i].listeSommetParcouru[j] != trajet.listeSommetParcouru[j])
			{
				TrajetPresent = false;
			}
			else
			{
				TrajetPresent = true;
				break;
			}
		}
		if (!TrajetPresent)
		{
			it++;
		}	
	}
	listeTrajetsPossible_.erase(it);
	return;
}
/****************************************************************************
  * Fonction: canSwapTrajet
  * Description: Verifie que trajetASwap est plus court que Trajet de Comparaison
  * Paramètres: trajetASwap et Trajet de Comparaison
  * Retour: vrai si trajetASwap est plus court que Trajet de Comparaison
  ****************************************************************************/
bool canSwapTrajet(Trajet trajetASwap, Trajet TrajetdeComparaison)
{
	return trajetASwap.distanceTotale <= TrajetdeComparaison.distanceTotale;
}
/****************************************************************************
  * Fonction: Algorithme::trierListeSelonDistance
  * Description: Permet de trier la listes des trajets dans l'ordre croissant de distance
  * Paramètres: aucun
  * Retour: aucun
  ****************************************************************************/
void Algorithme::trierListeSelonDistance()
{	
	int droite = listeTrajetsPossible_.size();
	int gauche = droite - 1;
	while (canSwapTrajet(listeTrajetsPossible_[droite], listeTrajetsPossible_[gauche]))
	{
		swap(listeTrajetsPossible_[droite], listeTrajetsPossible_[gauche]);
	}
}

/****************************************************************************
  * Fonction: Algorithme::plusCourtChemin
  * Description: Permet de déterminer le chemin le plus court 
				 en se basant sur l'algorithme de Dijkstra
  * Paramètres: numero du sommet de depart et numero du sommet d'arrivee
  * Retour: le trajet le plus court (idéalement^^)
  ****************************************************************************/
Trajet Algorithme::plusCourtChemin(int depart, int arrivee)
{
	//TODO : finir plusCourtChemin
    Trajet trajet;
    
    int infini = numeric_limits<int>::max();
    int sommetDepart;

    // Fonction lambda de comparaison de distance, sera servi pour le priority_queue
    auto compareDistance = [](const pair<int, int>& a, const pair<int, int>& b) { return a.second > b.second; };

    //vector des distances, de taille NB_MAX_SOMMETS, initializé à infini  par défaut
    vector<int> vecteurDistances(graphe_.getNbSommets(), infini);

    //Sommet de départ possède une distance = 0
    vecteurDistances[depart] = 0;

    //Création d'un vector pour les parents des somemts, initializé à -1 par défaut
    vector<int> vecteurParents(graphe_.getNbSommets(), -1);

    // On utilise une priority queue pour que le sommet le plus proche soit toujours au dessus de la file
    // Une pair contient <index, distance par rapport départ>
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compareDistance)> queue(compareDistance);

    // On ajoute le sommet de départ à la file
    queue.push(make_pair(depart, 0));

    // Debut de Dijkstra
    while (!queue.empty()) {
        int indexSommetTopFile = queue.top().first;
        int distanceSommetTopFile = queue.top().second;
        queue.pop(); // on retire le sommet le plus pres de la file

        if (distanceSommetTopFile <= vecteurDistances[indexSommetTopFile]) {
            //On passe a travers tout les sommets adjacents du sommet sur le top de la file
            for (auto i : graphe_.getSommets()[indexSommetTopFile]->getSommetsAdjacents()) {
                auto indexSommetCourant = i.first->getNumeroDuSommet();
                auto distanceSommetCourant = i.second;

                if (vecteurDistances[indexSommetTopFile] + distanceSommetCourant < vecteurDistances[indexSommetCourant]) {
                    vecteurDistances[indexSommetCourant] = vecteurDistances[indexSommetTopFile] + distanceSommetCourant;
                    vecteurParents[indexSommetCourant] = indexSommetTopFile;
                    queue.push(make_pair(indexSommetCourant,vecteurDistances[indexSommetCourant]));
                }
            }
        }
    }

	return trajet;
}


