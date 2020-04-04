/****************************************************************************
 * Fichier: algorithme.cpp
 * Auteurs: Ouassim Ouali (1958275) , Pier-Luc Tanguay () et M�lody Roy ()
 * Date: 22 Mars 2020
 * Description: Impl�mentation des m�thodes utilis�e pour l'algorithme
 ****************************************************************************/
#include"algorithme.h"
#include <queue>

Algorithme::Algorithme()
{
}
Algorithme::Algorithme(const Graphe& graphe, const Taxi& taxi) : graphe(graphe), taxi(taxi)
{

    
}

Algorithme::~Algorithme()
{
	EffacerTousLesTrajets();

}
/****************************************************************************
  * Fonction: Algorithme::getListeTrajetsPossible
  * Description: Permet d'obtenir la liste des trajet possibles
  * Param�tres: aucun
  * Retour: liste des trajets possible
  ****************************************************************************/
vector<Trajet> Algorithme::getListeTrajetsPossible()
{
	return listeTrajetsEffectue;
}
/****************************************************************************
  * Fonction: Algorithme::getGraphe
  * Description: Permet d'obtenir le graphe
  * Param�tres: aucun
  * Retour: le graphe
  ****************************************************************************/
Graphe Algorithme::getGraphe()
{
	return graphe;
}
/****************************************************************************
  * Fonction: Algorithme::getTaxi
  * Description: Permet d'obtenir le taxi
  * Param�tres: aucun
  * Retour: le taxi
  ****************************************************************************/
Taxi Algorithme::getTaxi()
{
	return taxi;
}
/****************************************************************************
  * Fonction: Algorithme::ajouterTrajet
  * Description:  Permet d'ajouter un trajet � la liste des trajets possible
				  puis trie les elements selon leurs distances (depart,arrivee)
  * Param�tres: un trajet de type Trajet
  * Retour: aucun
  ****************************************************************************/
void Algorithme::ajouterTrajet(Trajet trajet)
{
	// TODO : Px etre ajouter un if pour ne pas ajouter le trajet s'il est deja present dans la liste
	listeTrajetsEffectue.push_back(trajet);

	// permet de trier la liste des trajet selon leur distance, en ordre croissant
	//trierListeSelonDistance();
	
}
/****************************************************************************
  * Fonction: Algorithme::ajouterTrajetSiPlusCourt
  * Description: Permet d'ajouter un Trajet seulement si la distance est inf�rieur 
				 au trajet le plus court de la listeTrajetPossible 
  * Param�tres: le Trajet � ajouter
  * Retour: aucun
  ****************************************************************************/
void Algorithme::ajouterTrajetSiPlusCourt(Trajet trajet)
{
	if (listeTrajetsEffectue[0].distanceTotale > trajet.distanceTotale)
	{
		ajouterTrajet(trajet);
	}
}



/****************************************************************************
  * Fonction: Algorithme::EffacerTousLesTrajets
  * Description: Permet d'effacer tous les trajets de la liste
  * Param�tres: aucun
  * Retour: aucun
  ****************************************************************************/
void Algorithme::EffacerTousLesTrajets()
{
	listeTrajetsEffectue.clear();
}
/****************************************************************************
  * Fonction: Algorithme::EffacerUnTrajet
  * Description: Permet d'effacer le trajet passer en param�tre de la liste
  * Param�tres: Trajet
  * Retour: aucun
  ****************************************************************************/
void Algorithme::EffacerUnTrajet(Trajet trajet)
{
	bool TrajetPresent = false;
	vector<Trajet>::iterator it;
	it = listeTrajetsEffectue.begin();
	for (auto i = 0; i < listeTrajetsEffectue.size(); i++)
	{
		for (auto j = 0; j < trajet.listeSommetParcouru.size(); j++)
		{
			if (listeTrajetsEffectue[i].listeSommetParcouru[j] != trajet.listeSommetParcouru[j])
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
	listeTrajetsEffectue.erase(it);
	return;
}
/****************************************************************************
  * Fonction: canSwapTrajet
  * Description: Verifie que trajetASwap est plus court que Trajet de Comparaison
  * Param�tres: trajetASwap et Trajet de Comparaison
  * Retour: vrai si trajetASwap est plus court que Trajet de Comparaison
  ****************************************************************************/
bool canSwapTrajet(Trajet trajetASwap, Trajet TrajetdeComparaison)
{
	return trajetASwap.distanceTotale <= TrajetdeComparaison.distanceTotale;
}
/****************************************************************************
  * Fonction: Algorithme::trierListeSelonDistance
  * Description: Permet de trier la listes des trajets dans l'ordre croissant de distance
  * Param�tres: aucun
  * Retour: aucun
  ****************************************************************************/
void Algorithme::trierListeSelonDistance()
{	
    if (listeTrajetsEffectue.size() != 1) {
        int droite = listeTrajetsEffectue.size();
        int gauche = droite - 1;
        while (canSwapTrajet(listeTrajetsEffectue[droite], listeTrajetsEffectue[gauche]))
        {
            swap(listeTrajetsEffectue[droite], listeTrajetsEffectue[gauche]);
        }
    }
}



Trajet Algorithme::dijkstra(int numeroSommetDepart, int numeroSommetArrive) {

    Trajet trajetDepartArrive;

    if (numeroSommetArrive != numeroSommetDepart) {

        int infini = numeric_limits<int>::max();

        // Fonction lambda de comparaison de distance, sera servi pour le priority_queue
        auto compareDistance = [](const pair<int, int>& a, const pair<int, int>& b) { return a.second > b.second; };

        //vector des distances, de taille NB_MAX_SOMMETS+1, initializ� � infini  par d�faut
        // +1 pour que les index match le num�ro du sommet
        vector<int> vecteurTemps(graphe.getNbSommets() + 1, infini);

        //Sommet de d�part poss�de une distance = 0
        vecteurTemps[numeroSommetDepart] = 0;

        //Cr�ation d'un vector pour les parents des sommets, initializ� � -1 par d�faut
        // +1 pour que les index match le num�ro du sommet
        vector<int> vecteurParents(graphe.getNbSommets() + 1, -1);

        // On utilise une priority queue pour que le sommet le plus proche soit toujours au dessus de la file
        // Une pair contient <index, distance par rapport d�part>
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compareDistance)> queue(compareDistance);

        // On ajoute le sommet de d�part � la priority_queue
        queue.push(make_pair(numeroSommetDepart, 0));


        int numeroSommetTopQueue = queue.top().first;
        int tempsSommetTopQueue = queue.top().second;

        while (numeroSommetTopQueue != numeroSommetArrive) {
            numeroSommetTopQueue = queue.top().first;
            tempsSommetTopQueue = queue.top().second;
            queue.pop(); // on retire le sommet dont le temps est connu

            if (tempsSommetTopQueue <= vecteurTemps[numeroSommetTopQueue]) {

                //On passe a travers tout les sommets adjacents du sommet sur le top de la file
                for (auto i : graphe.getSommets()[numeroSommetTopQueue - 1]->getSommetsAdjacents()) {
                    auto numeroSommetCourant = i.first->getNumeroDuSommet();
                    auto tempsSommetCourant = i.second;

                    // Addition de la distance actuelle et de la distance du Sommet adjacent
                    int tempsAddSommetCourant = vecteurTemps[numeroSommetTopQueue] + tempsSommetCourant;

                    // condition qui v�rifiera, pour chaque Sommet adjacent, celui qui prendra le moins de temps (faible distance)
                    // A la fin de la boucle, on aura la distance la plus courte � l'index 
                    if (tempsAddSommetCourant < vecteurTemps[numeroSommetCourant]) {
                        vecteurTemps[numeroSommetCourant] = tempsAddSommetCourant;
                        //graphe.getSommets()[numeroSommetCourant]->setTempsParent(tempsSommetCourant);
                        vecteurParents[numeroSommetCourant] = numeroSommetTopQueue;
                        queue.push(make_pair(numeroSommetCourant, vecteurTemps[numeroSommetCourant]));
                    }
                }
            }

        }

      


        // Boucle pour contruire le trajet au complet, entre d�part et arriv�
        //    1. Ajout du sommet d'arriv�
        trajetDepartArrive.listeSommetParcouru.push_back(graphe.getSommets()[numeroSommetArrive - 1]);
        trajetDepartArrive.distanceTotale = vecteurTemps[numeroSommetArrive];

        //    2. Ajout du sommet entre arriv� et d�part, pushback du sommet parent de chacun des sommets courant
        for (auto i = vecteurParents[numeroSommetArrive]; i != numeroSommetDepart; i = vecteurParents[i]) {
            trajetDepartArrive.listeSommetParcouru.push_back(graphe.getSommets()[i - 1]);
        }

        //    3. Ajout du sommet de d�part
        trajetDepartArrive.listeSommetParcouru.push_back(graphe.getSommets()[numeroSommetDepart - 1]);
    }

    else {
        trajetDepartArrive.listeSommetParcouru.push_back(graphe.getSommets()[numeroSommetDepart - 1]);
        trajetDepartArrive.listeSommetParcouru.push_back(graphe.getSommets()[numeroSommetArrive - 1]);
        trajetDepartArrive.distanceTotale = 0;
    }

    // Ajouter les distance entre chaque sommet
    for (int i = 0; i < trajetDepartArrive.listeSommetParcouru.size() - 1; i++) {
        cout << trajetDepartArrive.listeSommetParcouru[i]->getNumeroDuSommet() << endl;

        for (int j = 0; j < trajetDepartArrive.listeSommetParcouru[i]->getSommetsAdjacents().size(); j++) {
         
            cout << trajetDepartArrive.listeSommetParcouru[i]->getSommetsAdjacents()[j].first->getNumeroDuSommet() << endl;

            if (trajetDepartArrive.listeSommetParcouru[i]->getSommetsAdjacents()[j].first->getNumeroDuSommet() ==
                trajetDepartArrive.listeSommetParcouru[i+1]->getNumeroDuSommet())

                trajetDepartArrive.listeSommetParcouru[i]->setTempsParent(trajetDepartArrive.listeSommetParcouru[i]->getSommetsAdjacents()[j].second);


        }
    }


    // Ajout dans conteneur de trajet
    ajouterTrajet(trajetDepartArrive);

    return trajetDepartArrive;
}



/****************************************************************************
  * Fonction: Algorithme::afficherTrajet
  * Description: Affiche le chemin, distance parcouru et batterie restante
  * Param�tres: un trajet
  * Retour: rien
  ****************************************************************************/
const void Algorithme::afficherTrajet(Trajet trajet) {

    cout << endl << "     ------------------ Trajet de " << trajet.listeSommetParcouru.back()->getNumeroDuSommet() << " a " 
         << trajet.listeSommetParcouru.front()->getNumeroDuSommet() << "------------------";

    cout << endl << "     Chemin le plus court pour s'y rendre: ";
    for (int i = trajet.listeSommetParcouru.size() - 1; i >= 0; i--) {
        cout << trajet.listeSommetParcouru[i]->getNumeroDuSommet();
        if (i != 0)
            cout << "->";
    }
    cout << endl << "     Distance: " << trajet.distanceTotale << " min" << endl;

    //Affichage de la distance
    taxi.miseAJourBatterie(trajet.distanceTotale);
    cout << "     Pourcentage de la batterie restante: " << taxi.getBatterieRestante() << "%" << endl;
}



/****************************************************************************
  * Fonction: Algorithme::plusCourtChemin
  * Description: Permet de d�terminer le chemin le plus court de tous les sommets
				 en se basant sur l'algorithme de Dijkstra
  * Param�tres: numero du sommet de depart
  * Retour: le trajet le plus court pour franchir tous les sommets
  ****************************************************************************/
void Algorithme::plusCourtChemin(int numeroSommetDepart, int numeroSommetArrive)
{

    // on trouve le trajet le plus court par l'algorithme Dijkstra's
    Trajet trajet = dijkstra(numeroSommetDepart,numeroSommetArrive);
 
    //Affichage du trajet
    afficherTrajet(trajet);

}

Trajet Algorithme::conduireVersSommet(int numeroSommetDestination) {
    
    // Calcul le "sous" trajet le plus court avec Dijkstra   
    Trajet trajet = dijkstra(taxi.getPositionActuelle(), numeroSommetDestination);
    
    // Mise � jour taxi: position actuelle, charge et ajout le "sous" trajet
    taxi.setPositionActuelle(numeroSommetDestination);
    taxi.miseAJourBatterie(trajet.distanceTotale);
    listeTrajetsEffectue.push_back(trajet);

    // Ajoute les sommets parcouru la la liste du taxi
    for (int i = trajet.listeSommetParcouru.size() - 2; i >= 0; i--) {
        taxi.ajouterSommet(trajet.listeSommetParcouru[i]);
    }

    // Modifier le temps de chaque passager
    if (taxi.getListePassager().size() != 0) {
        for (int i = 0; i < taxi.getListePassager().size() - 1; i++) {
            taxi.getListePassager()[i]->modifierTemps(trajet.distanceTotale);
        }
    }

    return trajet;
}


void Algorithme::miseAJourTaxi(Trajet trajet) {


    // Mise � jour taxi: position actuelle, charge et ajout le "sous" trajet
    taxi.setPositionActuelle(trajet.listeSommetParcouru.front()->getNumeroDuSommet());
    taxi.miseAJourBatterie(trajet.distanceTotale);
    listeTrajetsEffectue.push_back(trajet);

    // Ajoute les sommets parcouru la la liste du taxi
    if (trajet.listeSommetParcouru.front()->getNumeroDuSommet() != trajet.listeSommetParcouru.back()->getNumeroDuSommet()) {

        for (int i = trajet.listeSommetParcouru.size() - 2; i >= 0; i--) {
            taxi.ajouterSommet(trajet.listeSommetParcouru[i]);
        }
    }

    // Modifier le temps de chaque passager
    if (taxi.getListePassager().size() != 0) {
        for (int i = 0; i < taxi.getListePassager().size() - 1; i++) {
            taxi.getListePassager()[i]->modifierTemps(trajet.distanceTotale);
        }
    }

}


Trajet Algorithme::trajetRecharger(int numeroPositionActuelle) {

    Trajet trajetBorne;


    for (int i = 0; i < graphe.getSommetsRecharge().size() - 1; i ) {
        Trajet trajetTemporaire = trajetBorne = dijkstra(numeroPositionActuelle, graphe.getSommetsRecharge()[i]);
        if (trajetBorne.distanceTotale > trajetTemporaire.distanceTotale)
            trajetBorne = trajetTemporaire;
    }

    return trajetBorne;
}


Trajet Algorithme::miseAJoutTrajetFinal(const Trajet& trajetCourant, Trajet trajetFinal)
{
    Trajet trajet;

    if (trajetCourant.distanceTotale != 0) {
        if (trajetFinal.listeSommetParcouru.size() != 0) {

            for (int i = 0; i < trajetCourant.listeSommetParcouru.size() - 1; i++) {
                trajet.listeSommetParcouru.push_back(trajetCourant.listeSommetParcouru[i]);
            }

            for (int i = 0; i < trajetFinal.listeSommetParcouru.size(); i++) {
                trajet.listeSommetParcouru.push_back(trajetFinal.listeSommetParcouru[i]);
            }
        }
        else {

            for (int i = 0; i <= trajetCourant.listeSommetParcouru.size() - 1; i++) {
                trajet.listeSommetParcouru.push_back(trajetCourant.listeSommetParcouru[i]);
            }
        }

        if (trajetFinal.listeSommetParcouru.size() != 0)
            trajet.distanceTotale = trajetCourant.distanceTotale + trajetFinal.distanceTotale;
        else
            trajet.distanceTotale = trajetCourant.distanceTotale;
    }
    else
        trajet = trajetFinal;

    return trajet;
}


Trajet Algorithme::prochainTrajet(int posititionAtuelle, Passager* requeteCourante) {

    Trajet trajetChoisi;
    Trajet trajetNouveauPassager;

    // Trajet de la destination de la requete du passager pris en param�tre
    Trajet trajetDestinationRequete = dijkstra(posititionAtuelle, requeteCourante->getDestination());
    trajetChoisi = trajetDestinationRequete;
    trajetChoisi.type = Trajet::destination;
    if (taxi.getListePassager().size() < 4) {

        // On compare la distance du trajet de destination � celle du d�part des autres requ�tes
        int index;
        for (int i = requeteCourante->getId() + 1; i < taxi.getListeRequetes().size(); i++) {

            trajetNouveauPassager = dijkstra(posititionAtuelle, taxi.getListeRequetes()[i]->getSommetDepart());

            if ((trajetNouveauPassager.distanceTotale < trajetDestinationRequete.distanceTotale) && (trajetNouveauPassager.distanceTotale < trajetChoisi.distanceTotale)) {
                trajetChoisi = trajetNouveauPassager;
                trajetChoisi.type = Trajet::recupere;
                index = i;
            }
            
        }
        if (trajetChoisi.type == Trajet::recupere) {
            if (!taxi.getListeRequetes()[index]->getDansTaxi() && !taxi.getListeRequetes()[index]->getComplete())
            taxi.ajouterPassager(taxi.getListeRequetes()[index]);
        }
    }

    if ((taxi.getBatterieRestante() - trajetChoisi.distanceTotale) < SEUIL_RECHARGE) {

        trajetChoisi = trajetRecharger(posititionAtuelle);
        trajetChoisi.type = Trajet::recharge;
    }
  
    return trajetChoisi;

}

/****************************************************************************
  * Fonction: Algorithme::traiterRequ�tes
  * Description: la faisabilit� de requ�tes de clients  et de d�terminer le 
                 chemin qu�il faut prendre pour desservir ceux-ci, en tenant
                 compte des restrictions de charge de batterie, temps et
                 maximum 4 clients � la fois
  * Param�tres: numero du sommet de depart
  * Retour: le trajet le plus court pour franchir tous les sommets
  ****************************************************************************/
void Algorithme::traiterRequetes() {

    Trajet trajetComplet;
    Trajet sousTrajet;


    taxi.ajouterSommet(graphe.chercherSommet(taxi.getPositionDepart()));

    sousTrajet = conduireVersSommet(taxi.getListeRequetes().front()->getSommetDepart());

    trajetComplet = miseAJoutTrajetFinal(sousTrajet, trajetComplet);
    
    taxi.ajouterPassager(taxi.getListeRequetes().front());




    for (int i = 0; taxi.getListeRequetes().size() - 1; i++)
    { 

        sousTrajet = prochainTrajet(taxi.getPositionActuelle(), taxi.getListeRequetes()[i]);
        miseAJourTaxi(sousTrajet);
        trajetComplet = miseAJoutTrajetFinal(sousTrajet, trajetComplet);
   


    }
    

    //Affichage du trajet
    afficherTrajet(trajetComplet);



}


