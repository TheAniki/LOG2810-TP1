/****************************************************************************
 * Fichier: 
 * Auteurs:
 * Date: 
 * Description: 
 ****************************************************************************/

#include "Taxi.h"

unsigned int compteurRequete = 0;
unsigned int compteurAffichage = 0;


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
  * Fonction:
  * Description:
  * Paramètres:
  * Retour:
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
  * Fonction:
  * Description:
  * Paramètres:
  * Retour:
  ****************************************************************************/
void Taxi::miseAjourRequetes()
{
	EffacerTousRequetes();
	compteurRequete = 0;
	lireFichier();
	placerPassager();
}
/****************************************************************************
  * Fonction:
  * Description:
  * Paramètres:
  * Retour:
  ****************************************************************************/
// ajoute un passager dans le taxi si nbPassager < 4
void Taxi::ajouterPassager(Passager* passager)
{
	unsigned int priorite = listePassagersTaxi_.size();
	if (listePassagersTaxi_.size() < 4)
	{
		listePassagersTaxi_.push_back(make_pair(passager, priorite));		
	}	
	else
	{
		cout << "Impossible d'ajouter passager, taxi plein" << endl;
		return;
	}
}
/****************************************************************************
  * Fonction:
  * Description:
  * Paramètres:
  * Retour:
  ****************************************************************************/
// ajoute un sommet a historique
void Taxi::ajouterSommet(Sommet sommet)
{
	 historiqueSommetsParcouru_.push_back(sommet);
	 return;
}
/****************************************************************************
  * Fonction:
  * Description:
  * Paramètres:
  * Retour:
  ****************************************************************************/
// enleve le passager prioritaire
void Taxi::enleverPassager(Passager* passager)
{
	for (auto it : listePassagersTaxi_)
	{
		if (it.second == 0 && it.first == passager)
		{
			return; //TODO remove passager 
			// besoin de sort?
		}
	}

}
/****************************************************************************
  * Fonction:
  * Description:
  * Paramètres:
  * Retour:
  ****************************************************************************/
void Taxi::chargerTaxi()
{
	energieRestante_ = 100;
	// TODO: enlever 10 min a tt le monde 
}
/****************************************************************************
  * Fonction:
  * Description:
  * Paramètres:
  * Retour:
  ****************************************************************************/
void Taxi::modificationEnergieRestante(int energie)
{
	energieRestante_ = energie;
}

/****************************************************************************
  * Fonction:
  * Description:
  * Paramètres:
  * Retour:
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
  * Fonction:
  * Description:
  * Paramètres:
  * Retour:
  ****************************************************************************/
//methode place les passagers et leur requete.
void Taxi::placerPassager()
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
		placerPassager();
	}
	else
	{
		return;
	}
}

//fin methode pour fichier.
//===================================================================================================================//
/****************************************************************************
  * Fonction:
  * Description:
  * Paramètres:
  * Retour:
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
  * Fonction:
  * Description:
  * Paramètres:
  * Retour:
  ****************************************************************************/
void Taxi::afficherPassagerTaxi()
{
	//TODO : afficher les passager du taxi
}
