/****************************************************************************
 * Fichier:
 * Auteurs: Ouassim Ouali (1958275) , Pier-Luc Tanguay () et Mélody Roy ()
 * Date: 22 Mars 2020
 * Description: Implémentation des méthodes de la classe Graphe 
				et de méthode globale utilisé lors de la lecture des fichiers 
 ****************************************************************************/

#include "Graphe.h"
int NB_MAX_SOMMETS =  19;
int compteur = 0;
int compteurSommet = 0;
unsigned int compteurLigne = 0;

Graphe::Graphe():nomFichier_("")
{

}

Graphe::Graphe(string nomFichier):nomFichier_(nomFichier)
{
	
}

Graphe::~Graphe()
{
	EffacerTousSommets();
}




//****************************************************************************
//Getters
//****************************************************************************
const string Graphe::getNomFichier()
{
	return nomFichier_;
}


const vector<Sommet*> Graphe::getSommets()
{
	return sommets_;
}


const int Graphe::getNbSommets() 
{
	return nbSommets; 
}


const vector<string> Graphe::getListeDonnees()
{
	return listeDonnees_;
}

const vector<int> Graphe::getSommetsRecharge() {
	return listeSommetsRecharge_;
}

/****************************************************************************
  * Fonction: Graphe::modifierNomFichier
  * Description: Permet de modifier le nom du fichier 
  * Paramètres: string nouveauNomFichier
  * Retour: aucun
  ****************************************************************************/
void Graphe::modifierNomFichier(const string& nouveauNomFichier)
{
	nomFichier_ = nouveauNomFichier;
}



/****************************************************************************
  * Fonction: Graphe::lireFichier
  * Description: Permet de lire les lignes du fichier puis 
				 les place dans listeDonnees_ pour être traiter
  * Paramètres: le nom du fichier (string)
  * Retour: aucun
  ****************************************************************************/
void Graphe::lireFichier()
{
	ifstream fichier(nomFichier_);
	if (fichier.fail()) {

		cout << "ECHEC : Ouverture du fichier" << endl;
		return;
	}
	else
	{
		string ligneSommet, parametreAretes;
		for (int i = 0; i < NB_MAX_SOMMETS; i++)
		{
			getline(fichier, ligneSommet);
			listeDonnees_.push_back(ligneSommet);
		}
		while (!ws(fichier).eof())
		{
			getline(fichier, parametreAretes);
			listeDonnees_.push_back(parametreAretes);
		}
	}
	fichier.close();
}





/****************************************************************************
  * Fonction: partieVoisin
  * Description: Fonction générale permettant de compter le nombre de virgule
				 dans la ligne, afin de determinée si c'est la partie du fichier
				 contenant la liste des sommets et leurs voisins
  * Paramètres: string ligne
  * Retour: bool retourne true s'il y a 2 virgules et false pour les autres
  ****************************************************************************/
bool partieVoisin(string ligne)
{
	int compteurVirgule = 0;
	for (unsigned int i = 0; i < ligne.length(); i++)
	{
		if (ligne[i] == ',')
		{
			compteurVirgule++;
		}
	}
	return (compteurVirgule == 2) ? true : false;
}







/****************************************************************************
  * Fonction: partieSommet
  * Description: Fonction générale comptant le nombre de virgule afin de
				 déterminée si c'est la partie du fichier contenant 
				la liste des sommets
  * Paramètres: string ligne
  * Retour: bool true si une virgule dans la ligne et 
			false s'il y a moins ou plus qu'une virgule
  ****************************************************************************/
bool partieSommet(string ligne)
{
	int compteurVirgule = 0;
	for (unsigned int i = 0; i < ligne.length(); i++)
	{
		if (ligne[i] == ',')
		{
			compteurVirgule++;
		}
	}
	return (compteurVirgule == 1) ? true : false;
}







/****************************************************************************
  * Fonction: Graphe::creerGraphe
  * Description: Fonction crééant le graphe de façôn récursive grâce à 
				 la listeDonnees lue par la fonction lireFichier()
  * Paramètres: aucun
  * Retour: aucun
  ****************************************************************************/
void Graphe::creerGraphe()
{
	if (partieVoisin(listeDonnees_[compteurLigne]))
	{
		vector<string> listeDonneeFichier = split(listeDonnees_[compteurLigne], ',');

		int numSommetOrigine = convertStringtoInt(listeDonneeFichier[0]);
		int numSommetAdjacent = convertStringtoInt(listeDonneeFichier[1]);
		int temps = convertStringtoInt(listeDonneeFichier[2]);

		Sommet* SommetOrigine = chercherSommet(numSommetOrigine);
		Sommet* SommetAdjacent = chercherSommet(numSommetAdjacent);

		SommetOrigine->ajouterSommetAdjacent(SommetAdjacent, temps);
		SommetAdjacent->ajouterSommetAdjacent(SommetOrigine, temps);
		compteurLigne++;				
	}
	else if(partieSommet(listeDonnees_[compteurLigne]))
	{
		vector<string> listeDonneeFichier = split(listeDonnees_[compteurLigne], ',');

		int numeroSommet = convertStringtoInt(listeDonneeFichier[0]);
		bool presenceborne = convertStringtoBool(listeDonneeFichier[1]);
		Sommet* nouveauSommet = new Sommet(numeroSommet, presenceborne);

		if (presenceborne) {
			listeSommetsRecharge_.push_back(numeroSommet);
		}

		sommets_.push_back(nouveauSommet);
		compteurLigne++;			
		nbSommets++; 
	}			
	if (compteurLigne < listeDonnees_.size())
	{
		creerGraphe();
	}
	else
	{
		return;
	}		
	
}







/****************************************************************************
  * Fonction: Graphe::AffichageGraphe
  * Description: Méthode permettant d'afficher le graphe sous la forme 
				--------------------------------
					        Sommet 19

				  Presence borne : non

				  Liste des sommets adjacents :

				    Sommet A: X min
					Sommet B: Y min

  * Paramètres: aucun
  * Retour: aucun
  ****************************************************************************/
void Graphe::AffichageGraphe()
{

	if (compteur == 0)
	{
		cout << "==============================" << endl;
		cout << " Affichage Graphe : " << endl << endl;
	}
	// affichage sommet et borne 
	cout << endl << "--------------------------------" << endl;
	
	cout << "          Sommet " << sommets_[compteur]->getNumeroDuSommet() << endl << endl;
	cout << "  Presence borne : ";
	(sommets_[compteur]->getPresenceBorne()) ? (cout << "oui") : (cout << "non");
	
	//affichage des voisins
	cout << endl << endl << "  Liste des sommets adjacents : " << endl << endl;

	for (auto i : sommets_[compteur]->getSommetsAdjacents())
	{
		cout << "      Sommet " << i.first->getNumeroDuSommet() << ": " << i.second << " min" << endl;
	}

	compteur++;
	
	if (compteur == NB_MAX_SOMMETS)
	{
		compteur = 0;
		cout << endl << "==============================" << endl;
		return;
	}	

	AffichageGraphe();
}







/****************************************************************************
  * Fonction: Graphe::EffacerTousSommets
  * Description: Méthode permettant d'effacer tous les sommets de la liste de
				 sommets_
  * Paramètres: aucun
  * Retour: aucun
  ****************************************************************************/
void Graphe::EffacerTousSommets()
{
	for (auto it : sommets_)
	{
		if (it != nullptr) {
			it->EffacerTousSommetsAdjacents();
			it = nullptr;
			delete it;
		}
	}
	sommets_.clear();
	listeSommetsRecharge_.clear();
}







/****************************************************************************
  * Fonction: Graphe::miseAJourGraphe
  * Description: Méthode contenant la séquence de la mise à jour du graphe
  * Paramètres: aucun
  * Retour: aucun
  ****************************************************************************/
void Graphe::miseAJourGraphe()
{
	EffacerTousSommets();
	listeDonnees_.clear();
	nbSommets = 0;
	compteurLigne = 0;
	lireFichier();
	creerGraphe();
}








/****************************************************************************
  * Fonction: Graphe::chercherSommet
  * Description: Permet de chercher un sommet parmit la liste de sommets_
  * Paramètres: le numéro du sommet à chercher (int)
  * Retour: le sommet rechercher, s'il est dans la liste
  ****************************************************************************/
Sommet* Graphe::chercherSommet(int numeroSommet)
{
	for (auto it : sommets_)
	{
		if (it->getNumeroDuSommet() == numeroSommet)
		{			
			return it;
		}				
	}
	cout << "ERREUR : sommet " << numeroSommet << " non trouve" << endl;
	return nullptr;
}






/****************************************************************************
  * Fonction: split
  * Description: Fonction générale, permettant de séparer un string 
				 selon un charctère délimitant
  * Paramètres: le string s à séparer et le char delim (délimitant)
  * Retour: retourne le string séparer 
  ****************************************************************************/
//https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
vector<string> split(const string& s, char delim) {
	vector<string> result;
	stringstream ss(s);
	string item;

	while (getline(ss, item, delim)){
		result.push_back(item);
	}

	return result;
}






/****************************************************************************
  * Fonction: convertStringtoBool
  * Description: Permet de convertir le string en bool
  * Paramètres: string ligne
  * Retour: vrai si "1" et faux pour le reste
  ****************************************************************************/
bool convertStringtoBool(string ligne)
{
	return (ligne == "1") ? true : false;
}




/****************************************************************************
  * Fonction: convertStringtoInt
  * Description: Permet de convertir le string en int
  * Paramètres: string ligne
  * Retour: le string converti en int
  ****************************************************************************/
int convertStringtoInt(string ligne)
{
	stringstream convertir(ligne);
	int stringInt;
	convertir >> stringInt;
	return stringInt;
}

