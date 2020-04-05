/****************************************************************************
 * Fichier: algorithme.cpp
 * Auteurs: Ouassim Ouali (1958275) , Pier-Luc Tanguay (1953707) et Mélody Roy (1991902)
 * Date: 22 Mars 2020
 * Description: Implémentation des méthodes utilisée pour l'algorithme
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
  * Paramètres: aucun
  * Retour: liste des trajets possible
  ****************************************************************************/
vector<Trajet> Algorithme::getListeTrajetsPossible()
{
	return listeTrajetsEffectue;
}
/****************************************************************************
  * Fonction: Algorithme::getGraphe
  * Description: Permet d'obtenir le graphe
  * Paramètres: aucun
  * Retour: le graphe
  ****************************************************************************/
Graphe Algorithme::getGraphe()
{
	return graphe;
}
/****************************************************************************
  * Fonction: Algorithme::getTaxi
  * Description: Permet d'obtenir le taxi
  * Paramètres: aucun
  * Retour: le taxi
  ****************************************************************************/
Taxi Algorithme::getTaxi()
{
	return taxi;
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
	listeTrajetsEffectue.push_back(trajet);
}


/****************************************************************************
  * Fonction: Algorithme::EffacerTousLesTrajets
  * Description: Permet d'effacer tous les trajets de la liste
  * Paramètres: aucun
  * Retour: aucun
  ****************************************************************************/
void Algorithme::EffacerTousLesTrajets()
{
	listeTrajetsEffectue.clear();
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
  * Fonction: Algorithme::dijkstra
  * Description: Algorithme de détection de chemin le plus court
  * Paramètres: sommet de départ et d'arrivé
  * Retour: le trajet
  ****************************************************************************/
Trajet Algorithme::dijkstra(int numeroSommetDepart, int numeroSommetArrive) {

    Trajet trajetDepartArrive;

    if (numeroSommetArrive != numeroSommetDepart) {

        int infini = numeric_limits<int>::max();

        // Fonction lambda de comparaison de distance, sera servi pour le priority_queue
        auto compareDistance = [](const pair<int, int>& a, const pair<int, int>& b) { return a.second > b.second; };

        //vector des distances, de taille NB_MAX_SOMMETS+1, initializé à infini  par défaut
        // +1 pour que les index match le numéro du sommet
        vector<int> vecteurTemps(graphe.getNbSommets() + 1, infini);

        //Sommet de départ possède une distance = 0
        vecteurTemps[numeroSommetDepart] = 0;

        //Création d'un vector pour les parents des sommets, initializé à -1 par défaut
        // +1 pour que les index match le numéro du sommet
        vector<int> vecteurParents(graphe.getNbSommets() + 1, -1);

        // On utilise une priority queue pour que le sommet le plus proche soit toujours au dessus de la file
        // Une pair contient <index, distance par rapport départ>
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(compareDistance)> queue(compareDistance);

        // On ajoute le sommet de départ à la priority_queue
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

                    // condition qui vérifiera, pour chaque Sommet adjacent, celui qui prendra le moins de temps (faible distance)
                    // A la fin de la boucle, on aura la distance la plus courte à l'index 
                    if (tempsAddSommetCourant < vecteurTemps[numeroSommetCourant]) {
                        vecteurTemps[numeroSommetCourant] = tempsAddSommetCourant;
                        //graphe.getSommets()[numeroSommetCourant]->setTempsParent(tempsSommetCourant);
                        vecteurParents[numeroSommetCourant] = numeroSommetTopQueue;
                        queue.push(make_pair(numeroSommetCourant, vecteurTemps[numeroSommetCourant]));
                    }
                }
            }

        }

      


        // Boucle pour contruire le trajet au complet, entre départ et arrivé
        //    1. Ajout du sommet d'arrivé
        trajetDepartArrive.listeSommetParcouru.push_back(graphe.getSommets()[numeroSommetArrive - 1]);
        trajetDepartArrive.distanceTotale = vecteurTemps[numeroSommetArrive];

        //    2. Ajout du sommet entre arrivé et départ, pushback du sommet parent de chacun des sommets courant
        for (auto i = vecteurParents[numeroSommetArrive]; i != numeroSommetDepart; i = vecteurParents[i]) {
            trajetDepartArrive.listeSommetParcouru.push_back(graphe.getSommets()[i - 1]);
        }

        //    3. Ajout du sommet de départ
        trajetDepartArrive.listeSommetParcouru.push_back(graphe.getSommets()[numeroSommetDepart - 1]);
    }

    else {
        trajetDepartArrive.listeSommetParcouru.push_back(graphe.getSommets()[numeroSommetDepart - 1]);
        trajetDepartArrive.listeSommetParcouru.push_back(graphe.getSommets()[numeroSommetArrive - 1]);
        trajetDepartArrive.listeSommetParcouru.front()->setTempsParent(0);
        trajetDepartArrive.distanceTotale = 0;
    }

    // Ajouter les distance entre chaque sommet
    trajetDepartArrive.listeSommetParcouru.back()->setTempsParent(0);
    for (int i = 0; i < trajetDepartArrive.listeSommetParcouru.size() - 1; i++) {

        for (int j = 0; j < trajetDepartArrive.listeSommetParcouru[i]->getSommetsAdjacents().size(); j++) {
         

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
  * Fonction: Algorithme::plusCourtChemin
  * Description: Permet de déterminer le chemin le plus court de tous les sommets
				 en se basant sur l'algorithme de Dijkstra
  * Paramètres: numero du sommet de depart
  * Retour: le trajet le plus court pour franchir tous les sommets
  ****************************************************************************/
void Algorithme::plusCourtChemin(int numeroSommetDepart, int numeroSommetArrive)
{

    // on trouve le trajet le plus court par l'algorithme Dijkstra's
    Trajet trajet = dijkstra(numeroSommetDepart,numeroSommetArrive);
 
    //Affichage du trajet

    cout << endl << "     ------------------ Trajet de " << trajet.listeSommetParcouru.back()->getNumeroDuSommet() << " a "
        << trajet.listeSommetParcouru.front()->getNumeroDuSommet() << "------------------";

    cout << endl << "     Chemin le plus court pour s'y rendre: ";
    for (int i = trajet.listeSommetParcouru.size() - 1; i >= 0; i--) {
        cout << trajet.listeSommetParcouru[i]->getNumeroDuSommet();
        if (i != 0)
            cout << "->";
    }
    cout << endl << "     Temps: " << trajet.distanceTotale << " min" << endl;

    //Affichage de la distance
    taxi.miseAJourBatterie(trajet.distanceTotale);
    cout << "     Pourcentage de la batterie restante: " << taxi.getBatterieRestante() << "%" << endl;

}


/****************************************************************************
  * Fonction: Algorithme::conduireVersSommet
  * Description: fait avancer un taxi vers la destination
  * Paramètres: numero de destination
  * Retour: retourne le trajet effectué
  ****************************************************************************/
Trajet Algorithme::conduireVersSommet(int numeroSommetDestination) {
    
    // Calcul le "sous" trajet le plus court avec Dijkstra   
    Trajet trajet = dijkstra(taxi.getPositionActuelle(), numeroSommetDestination);
    
    // Mise à jour taxi: position actuelle, charge et ajout le "sous" trajet
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


/****************************************************************************
  * Fonction: Algorithme::miseAJourTaxi
  * Description: mets a jour les parametre du taxi en fonction du trajet 
  * Paramètres: un trajet
  * Retour: rien
  ****************************************************************************/
void Algorithme::miseAJourTaxi(Trajet trajet) {


    // Mise à jour taxi: position actuelle, charge et ajout le "sous" trajet
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
        if (taxi.getListePassager().back()->getSommetDepart() != taxi.getPositionActuelle())
            taxi.getListePassager().back()->modifierTemps(trajet.distanceTotale);

    }

    if (trajet.type == Trajet::recharge)
        taxi.chargerTaxi();

}


/****************************************************************************
  * Fonction: Algorithme::trajetRecharger
  * Description: calcul quelle borne de recharge est la plus près
  * Paramètres: position actuelle
  * Retour: un trajet
  ****************************************************************************/
Trajet Algorithme::trajetRecharger(int numeroPositionActuelle) {

    Trajet trajetBorne;
    trajetBorne.distanceTotale = numeric_limits<int>::max();


    for (int i = 0; i <= graphe.getSommetsRecharge().size() - 1; i++) {
        Trajet trajetTemporaire = dijkstra(numeroPositionActuelle, graphe.getSommetsRecharge()[i]);
        if (trajetTemporaire.distanceTotale < trajetBorne.distanceTotale)
            trajetBorne = trajetTemporaire;
    }

    return trajetBorne;
}

/****************************************************************************
  * Fonction: Algorithme::miseAJourTrajetFinal
  * Description: ajout le trajet courant et trajet final deja créer
  * Paramètres: le trajet courant et le Final courant
  * Retour: un trajet
  ****************************************************************************/
Trajet Algorithme::miseAJourTrajetFinal(const Trajet& trajetCourant, Trajet trajetFinal)
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

/****************************************************************************
  * Fonction: Algorithme::prochainTrajet
  * Description: decision de la prochaine destination :
  *                     -Vers Borne
  *                     -Vers un nouveau client
  *                     -Aller porter un passager du taxi
  * Paramètres: position actuelle et la requete courante
  * Retour: un trajet
  ****************************************************************************/
Trajet Algorithme::prochainTrajet(int posititionAtuelle, Passager* requeteCourante) {

    Trajet trajetChoisi;
    Trajet trajetNouveauPassager;
    Trajet trajetDestinationRequete;
   
    int index;
        
    // Trajet de la destination de la requete du passager pris en paramètre
    if (taxi.getListePassager().size() == 1) {
        if (!requeteCourante->getComplete() && !requeteCourante->getTempsDepasse()) {
            trajetDestinationRequete = dijkstra(posititionAtuelle, requeteCourante->getDestination());
            trajetChoisi = trajetDestinationRequete;
            trajetChoisi.type = Trajet::destination;
        }
    }
    else if (taxi.getListePassager().size() == 0) {
        trajetChoisi = dijkstra(posititionAtuelle, requeteCourante->getSommetDepart());
        trajetChoisi.type = Trajet::recupere;
        index = 0;
    }
    else {
        // Si il y a plus qu'un passager dans le taxi, on calcul le plus court chemin entre la position actuelle et leur destination
        trajetChoisi.distanceTotale = numeric_limits<int>::max();
        for (int i = 0; i < taxi.getListePassager().size() - 1; i++) {
            trajetDestinationRequete = dijkstra(posititionAtuelle, taxi.getListePassager()[i]->getDestination());

            if (trajetDestinationRequete.distanceTotale < trajetChoisi.distanceTotale) {
                trajetChoisi = trajetDestinationRequete;
                trajetChoisi.type = Trajet::destination;
            }
        }
    }


    if ((taxi.getListePassager().size() < NB_PLACES_TAXI) && (taxi.getListePassager().size() > 0)) {

        // On compare la distance du trajet de destination à celle du départ des autres requêtes

        for (int i = 0; i < taxi.getListeRequetes().size()-1; i++) {
            if (requeteCourante->getId() != taxi.getListeRequetes()[i]->getId()) {
                if (!taxi.getListeRequetes()[i]->getDansTaxi() && !taxi.getListeRequetes()[i]->getComplete() 
                    && !taxi.getListeRequetes()[i]->getTempsDepasse()) {

                    trajetNouveauPassager = dijkstra(posititionAtuelle, taxi.getListeRequetes()[i]->getSommetDepart());

                    if ((trajetNouveauPassager.distanceTotale < trajetDestinationRequete.distanceTotale) && (trajetNouveauPassager.distanceTotale < trajetChoisi.distanceTotale)) {
                        trajetChoisi = trajetNouveauPassager;
                        trajetChoisi.type = Trajet::recupere;
                        index = i;
                    }
                }
            }
        }

        if (trajetChoisi.type == Trajet::recupere) {
            if (!taxi.getListeRequetes()[index]->getDansTaxi() && !taxi.getListeRequetes()[index]->getComplete())
                taxi.ajouterPassager(taxi.getListeRequetes()[index]);
         }
            
        
    }
    else if (taxi.getListePassager().size() == 0) {
        taxi.ajouterPassager(requeteCourante);
    }

    if ((taxi.getBatterieRestante() - trajetChoisi.distanceTotale) < SEUIL_RECHARGE) {

        trajetChoisi = trajetRecharger(posititionAtuelle);
        trajetChoisi.type = Trajet::recharge;
    }
  
    return trajetChoisi;

}

/****************************************************************************
  * Fonction: Algorithme::traiterRequêtes
  * Description: la faisabilité de requêtes de clients  et de déterminer le 
                 chemin qu’il faut prendre pour desservir ceux-ci, en tenant
                 compte des restrictions de charge de batterie, temps et
                 maximum 4 clients à la fois
  * Paramètres: numero du sommet de depart
  * Retour: le trajet le plus court pour franchir tous les sommets
  ****************************************************************************/
void Algorithme::traiterRequetes() {

    Trajet trajetComplet;
    Trajet sousTrajet;


    taxi.ajouterSommet(graphe.chercherSommet(taxi.getPositionDepart()));

    sousTrajet = conduireVersSommet(taxi.getListeRequetes().front()->getSommetDepart());

    trajetComplet = miseAJourTrajetFinal(sousTrajet, trajetComplet);
    
    taxi.ajouterPassager(taxi.getListeRequetes().front());



    int requeteCourante = 0;
    bool termine = false;
    int passagerQuitte = 0;
    int batterieRestante;

    while(!termine) {
        
        if (taxi.getListePassager().size() ==0)
            for (int i = 0; i <= taxi.getListeRequetes().size() - 1; i++) {
                if (!taxi.getListeRequetes()[i]->getDansTaxi() && !taxi.getListeRequetes()[i]->getComplete()
                    && !taxi.getListeRequetes()[i]->getTempsDepasse())
                    requeteCourante = taxi.getListeRequetes()[i]->getId();
            }


        sousTrajet = prochainTrajet(taxi.getPositionActuelle(), taxi.getListeRequetes()[requeteCourante]);
        miseAJourTaxi(sousTrajet);
        trajetComplet = miseAJourTrajetFinal(sousTrajet, trajetComplet);

        batterieRestante = taxi.getBatterieRestante();

        // On analyse les passager dans le taxi, à savoir si à chaque point du trajet il doit débarquer
        // ---> Temps écoulé OU atteint la destination?
        int sousTempsParcouru = 0;
        for (int i = sousTrajet.listeSommetParcouru.size() - 1; i >= 0; i--) {

            sousTempsParcouru += sousTrajet.listeSommetParcouru[i]->getTempsParent();


            // Pour chaque passager du taxi
            if (taxi.getListePassager().size() > 1) {
                for (int j = 0; j <= (taxi.getListePassager().size() - 1); j++) {

                    // Si le temps du passager - le nouveau temps pacrouru est plus grand que 0
                    if (((taxi.getListePassager()[j]->getTempsArrivee() + sousTrajet.distanceTotale) - sousTempsParcouru) > 0) {

                        // Et si le sommet de destination de la requete est la position actuelle
                        if (taxi.getListePassager()[j]->getDestination() == sousTrajet.listeSommetParcouru[i]->getNumeroDuSommet()) {

                            taxi.getListePassager()[j]->setComplete(true);
                            taxi.enleverPassager(taxi.getListePassager()[j]);
                            if (taxi.getListePassager().size() == 1)
                                requeteCourante = taxi.getListePassager().front()->getId();
                            passagerQuitte++;
                            j = -1;
						}
					}                    
                    else{
                        taxi.getListePassager()[j]->setTempsDepasse(true);
                        taxi.enleverPassager(taxi.getListePassager()[j]);
                        if (taxi.getListePassager().size() == 1)
                            requeteCourante = taxi.getListePassager().front()->getId();
                        passagerQuitte++;
                    }
                }
            }
            else{
                // Si le temps du passager - le nouveau temps pacrouru est plus grand que 0
                if (((taxi.getListePassager().front()->getTempsArrivee() + sousTrajet.distanceTotale) - sousTempsParcouru) > 0) {

					// Et si le sommet de destination de la requete est la position actuelle
					if (taxi.getListePassager().front()->getDestination() == sousTrajet.listeSommetParcouru[i]->getNumeroDuSommet()) {

						taxi.getListePassager().front()->setComplete(true);
						taxi.enleverPassager(taxi.getListePassager().front());
						if (taxi.getListePassager().size() == 1)
							requeteCourante = taxi.getListePassager().front()->getId();
						passagerQuitte++;
					}
				}
            }
        }
        if (passagerQuitte == taxi.getListeRequetes().size())
            termine = true;
    }
    //Affichage du trajet

    cout << endl << "     ------------------ Trajet de la liste de requete ------------------";

    cout << endl << "     Chemin le plus court pour s'y rendre: ";
    for (int i = trajetComplet.listeSommetParcouru.size() - 1; i >= 0; i--) {
        cout << trajetComplet.listeSommetParcouru[i]->getNumeroDuSommet();
        if (i != 0)
            cout << "->";
    }
    cout << endl << "     Distance: " << trajetComplet.distanceTotale << " min" << endl;

    //Affichage de la distance
    taxi.miseAJourBatterie(trajetComplet.distanceTotale);
    cout << "     Pourcentage de la batterie restante: " << batterieRestante << "%" << endl;

}