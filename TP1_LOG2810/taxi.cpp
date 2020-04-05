/****************************************************************************
 * Fichier: Taxi.cpp
 * Auteurs: Ouassim Ouali (1958275) , Pier-Luc Tanguay (1953707) et Mélody Roy (1991902)
 * Date: 22 Mars 2020
 * Description: Implémentation des méthodes de la classe Taxi
 ****************************************************************************/

#include "Taxi.h"

unsigned int compteurRequete = 0;
unsigned int compteurAffichage = 0;
unsigned int compteurPassager = 0;


Taxi::Taxi(): batterieRestante_(100),positionDeDepart_(0)
{
}

Taxi::Taxi(string nomFichier): nomFichier_(nomFichier), positionDeDepart_(0),batterieRestante_(100)
{
	
}

Taxi::~Taxi()
{
	EffacerTousRequetes();
	listeFichierRequete_.clear();
	listePassagersTaxi_.clear();
	historiqueSommetsParcouru_.clear();
}

//****************************************************************************
//Getters
//****************************************************************************
const int Taxi::getBatterieRestante()
{
	return batterieRestante_;
}

const int Taxi::getPositionDepart()
{
	return positionDeDepart_;
}

const int Taxi::getPositionActuelle()
{
	return positionActuelle_;
}

const vector<Passager*> Taxi::getListePassager()
{
	return listePassagersTaxi_;
}

//
// Setter
//
void Taxi::setPositionActuelle(int numeroDestination)
{
	positionActuelle_ = numeroDestination;
}


/****************************************************************************
  * Fonction: Taxi::getListeRequetes
  * Description: Permet d'acceder à la liste des requêtes importée
  * Paramètres: aucun
  * Retour: Liste des requêtes, provenant du fichier
  ****************************************************************************/
const vector<Passager*> Taxi::getListeRequetes()
{
	return listeRequete_;
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
		if (it != nullptr)
		{
			it = nullptr;
			delete it;
		}
	}
	listeRequete_.clear();
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
void Taxi::ajouterPassager(Passager* passager)
{
	if (listePassagersTaxi_.size() < NB_PLACES_TAXI)
	{
		listePassagersTaxi_.push_back(passager);
		passager->setDansTaxi(true);
		//trier selon id (en ordre croissant)
		//trierSelonId();
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
void Taxi::ajouterSommet(Sommet* sommet)
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
void Taxi::enleverPassager(Passager* passager)
{
	if (listePassagersTaxi_.size() != 1) {


		for (int i = 0; i <= listePassagersTaxi_.size() - 1; i++) {
			if (passager->getId() == listePassagersTaxi_[i]->getId())
				listePassagersTaxi_.erase(listePassagersTaxi_.begin() + i);

		}
	}
	else
		listePassagersTaxi_.erase(listePassagersTaxi_.begin());

	passager->setDansTaxi(false);

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
	batterieRestante_ = 100;
	//enleve 10 min a tous les passagers
	for (auto it : listePassagersTaxi_)
	{
		it->modifierTemps(10);
	}	
}


/****************************************************************************
  * Fonction: Taxi::modificationEnergieRestante
  * Description: Méthode de  modification de l'energie restante du taxi
  * Paramètres: un integer energie
  * Retour: aucun
  ****************************************************************************/
void Taxi::miseAJourBatterie(int distanceParcouru)
{
	batterieRestante_ = batterieRestante_ - distanceParcouru;
}

/****************************************************************************
  * Fonction: Taxi::lireFichier
  * Description: Permet de lire le fichier de requete et
				 intialise la position de depart du taxi, puis
				 lit le reste du fichier et le place dans listeFichierRequete.
  * Paramètres: aucun
  * Retour: aucun
  ****************************************************************************/
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
		positionActuelle_ = positionDeDepart_;

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
		cout << *listeRequete_[compteurAffichage]; //affiche un passager	
		compteurAffichage++;
		afficherRequetes();
	}
	else
	{
		compteurAffichage = 0;
		return;
	}	
}

