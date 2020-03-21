/****************************************************************************
 * Fichier: Taxi.cpp
 * Auteurs: Ouassim Ouali (1958275) , Pier-Luc Tanguay () et Mélody Roy ()
 * Date: 22 Mars 2020
 * Description: Implémentation des méthodes de la classe Taxi
 ****************************************************************************/

#include "Taxi.h"

unsigned int compteurRequete = 0;
unsigned int compteurAffichage = 0;
unsigned int compteurPassager = 0;


Taxi::Taxi(): energieRestante_(100),positionDeDepart_(0)
{
}

Taxi::Taxi(string nomFichier): nomFichier_(nomFichier), positionDeDepart_(0),energieRestante_(100)
{
	
}

Taxi::~Taxi()
{
	EffacerTousRequetes();	
}
/****************************************************************************
  * Fonction: Taxi::EffacerTousRequetes
  * Description: Permet d'effacer toutes les requêtes de la listeRequete_ 
				 et d'effacer les élements de listeFichierRequete_
  * Paramètres: aucun
  * Retour: aucun
  ****************************************************************************/
void Taxi::EffacerTousRequetes()
{
	
	for (auto it : listeRequete_)
	{
		delete(it);
	}
	listeRequete_.clear();
	listeFichierRequete_.clear();

}
/****************************************************************************
  * Fonction: Taxi::miseAjourRequetes
  * Description: Séquence des opérations pour la mise à jour,
				 réinitialisation des compteurs
  * Paramètres: aucun
  * Retour: aucun
  ****************************************************************************/
void Taxi::miseAjourRequetes()
{
	EffacerTousRequetes();
	compteurRequete = 0;
	compteurAffichage = 0;
	compteurPassager = 0;
	lireFichier();
	placerPassagerDansGraphe();
}
/****************************************************************************
  * Fonction: Taxi::ajouterPassager
  * Description: Permet d'ajouter un passager dans le taxi 
				 si il y a de la place dans le taxi.
				 puis trie selon leur priorite
  * Paramètres: pointeur de la classe Passager
  * Retour: aucun
  ****************************************************************************/
// ajoute un passager dans le taxi si nbPassager < 4
void Taxi::ajouterPassager(Passager passager)
{
	if (listePassagersTaxi_.size() < 4)
	{
		listePassagersTaxi_.push_back(passager);
		//trier selon id (en ordre croissant)
		trierSelonId();
		//sort(listePassagersTaxi_.begin(), listePassagersTaxi_.end()/*, trierSelonId*/);
	}	
	else
	{
		cout << "Impossible d'ajouter passager, taxi plein" << endl;
		return;
	}
}
/****************************************************************************
  * Fonction: Taxi::ajouterSommet
  * Description: Permet d'ajouter un sommet dans l'historique des sommets
				 (à chaque fois qu'un taxi passe par un sommet l'ajoute dans l'historique)
  * Paramètres: un sommet de la classe Sommet
  * Retour: aucun
  ****************************************************************************/
// ajoute un sommet a historique
void Taxi::ajouterSommet(Sommet sommet)
{
	 historiqueSommetsParcouru_.push_back(sommet);
	 return;
}
/****************************************************************************
  * Fonction: Taxi::enleverPassager
  * Description: Enlever le passager passer en paramètre si il est le premier arrivée 
  * Paramètres: un pointeur Passager
  * Retour: aucun
  ****************************************************************************/
// enleve le passager prioritaire
void Taxi::enleverPassager(Passager passager)
{
	listePassagersTaxi_.erase(listePassagersTaxi_.begin());
}
/****************************************************************************
  * Fonction: Taxi::chargerTaxi
  * Description: Permet de charger le taxi à 100% et enleve 10 min à tous les
				 passager du taxi
  * Paramètres: aucun
  * Retour: aucun
  ****************************************************************************/
void Taxi::chargerTaxi()
{
	energieRestante_ = 100;
	//enleve 10 min a tous les passagers
	for (auto it : listePassagersTaxi_)
	{
		it.modifierTemps(10);
	}	
}
/****************************************************************************
  * Fonction: Taxi::modificationEnergieRestante
  * Description: Méthode de  modification de l'energie restante du taxi
  * Paramètres: un integer energie
  * Retour: aucun
  ****************************************************************************/
void Taxi::modificationEnergieRestante(int energie)
{
	energieRestante_ = energie;
}

/****************************************************************************
  * Fonction: Taxi::lireFichier
  * Description: Permet de lire le fichier de requete et
				 intialise la position de depart du taxi, puis
				 lit le reste du fichier et le place dans listeFichierRequete.
  * Paramètres: aucun
  * Retour: aucun
  ****************************************************************************/
//lit le fichier de requete et les place dans une liste de requete et positionne le taxi au point de depart
void Taxi::lireFichier()
{
	ifstream fichier(nomFichier_);
	if (fichier.fail()) {

		cout << "ECHEC : Ouverture du fichier" << endl;
		return;
	}
	else
	{
		string ligne;
		getline(fichier, ligne);
		positionDeDepart_ = convertStringtoInt(ligne); // lit la premiere ligne du fichier et la place dans position de depart
		while (!ws(fichier).eof())
		{
			getline(fichier, ligne);
			listeFichierRequete_.push_back(ligne);
		}
	}
	fichier.close();
}

/****************************************************************************
  * Fonction: Taxi::placerPassagerDansGraphe
  * Description: Permet de placer les requetes des passagers sur le graphe
  * Paramètres: aucun
  * Retour: aucun
  ****************************************************************************/
//methode place les passagers et leur requete.
void Taxi::placerPassagerDansGraphe()
{
	if (compteurRequete < listeFichierRequete_.size())
	{
		vector<string> listeDonneeFichier = split(listeFichierRequete_[compteurRequete], ','); // separe les donnees.

		int id = convertStringtoInt(listeDonneeFichier[0]);
		int sommetDepart = convertStringtoInt(listeDonneeFichier[1]); 
		int destination = convertStringtoInt(listeDonneeFichier[2]);
		int tempsArrive = convertStringtoInt(listeDonneeFichier[3]);

		Passager* passager = new Passager(id, sommetDepart, destination, tempsArrive); // creer nouveau passager
		listeRequete_.push_back(passager);
		compteurRequete++;
		placerPassagerDansGraphe();
	}
	else
	{
		return;
	}
}

//fin methode pour fichier.
//===================================================================================================================//
/****************************************************************************
  * Fonction: Taxi::afficherRequetes
  * Description: Méthode d'affichage qui affiche les Requetes des passagers
  * Paramètres: aucun
  * Retour: aucun
  ****************************************************************************/
void Taxi::afficherRequetes()
{
	if (compteurAffichage < compteurRequete)
	{	
		
		cout << " Id Passager " << listeRequete_[compteurAffichage]->getId() << " :"<< endl;
		cout << "| Sommet De Depart :" << listeRequete_[compteurAffichage]->getSommetDepart()
			<< " | Destination : " << listeRequete_[compteurAffichage]->getDestination()
			<< " | temps : " << listeRequete_[compteurAffichage]->getTempsArrivee() << " |" << endl << endl;
		compteurAffichage++;
		afficherRequetes();
	}
	else
	{
		compteurAffichage = 0;
		return;
	}
	
}
/****************************************************************************
  * Fonction: Taxi::afficherPassagerTaxi
  * Description: Méthode d'affichage permettant d'afficher la liste de passagers
				 présent dans le taxi
  * Paramètres: aucun
  * Retour: aucun
  ****************************************************************************/
void Taxi::afficherPassagerTaxi()
{
	
	cout << listePassagersTaxi_[compteurPassager];

	if (compteurPassager < listePassagersTaxi_.size())
	{
		compteurPassager++;
		afficherPassagerTaxi();
	}
}

/****************************************************************************
  * Fonction: canSwapPassager
  * Description: Verifie que passagerASwap est plus prioritaire(selon ID) 
				 que passagerdeComparaison(selon ID)
  * Paramètres: passagerASwap et passagerdeComparaison
  * Retour: vrai si passagerASwap est plus prioritaire que passagerdeComparaison
  ****************************************************************************/
bool canSwapPassager(Passager passagerASwap, Passager passagerdeComparaison)
{
	return passagerASwap.getId() < passagerdeComparaison.getId();
}


/****************************************************************************
  * Fonction: trierSelonId
  * Description: Permet de trier la liste des passagers dans le taxi selon 
				 leurs priorité.
  * Paramètres: passager1 et passager2
  * Retour: aucun
  ****************************************************************************/
void Taxi::trierSelonId()
{
	int droite = listePassagersTaxi_.size();
	int gauche = droite - 1;
	while (canSwapPassager(listePassagersTaxi_[droite], listePassagersTaxi_[gauche]))
	{
		swap(listePassagersTaxi_[droite], listePassagersTaxi_[gauche]);
	}
}
