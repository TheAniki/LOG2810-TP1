/****************************************************************************
 * Fichier:
 * Auteurs:
 * Date:
 * Description:
 ****************************************************************************/

#include "Graphe.h"
int NB_MAX_SOMMETS =  19;
bool MiseAJour = true;
int compteur = 0;
int compteurSommet = 0;
unsigned int compteurLigne = 0;
bool fichierOuvert = false;

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
/****************************************************************************
  * Fonction:
  * Description:
  * Param�tres:
  * Retour:
  ****************************************************************************/
string Graphe::getNomFichier()
{
	return nomFichier_;
}
/****************************************************************************
  * Fonction:    
  * Description: 
  * Param�tres:  
  * Retour:      
  ****************************************************************************/
const vector<Sommet*> Graphe::getSommets()
{
	return sommets_;
}
/****************************************************************************
  * Fonction:
  * Description:
  * Param�tres:
  * Retour:
  ****************************************************************************/
const vector<string> Graphe::getListeDonnees()
{
	return listeDonnees_;
}
/****************************************************************************
  * Fonction:
  * Description:
  * Param�tres:
  * Retour:
  ****************************************************************************/
const void Graphe::modifierNomFichier(const string& nouveauNomFichier)
{
	nomFichier_ = nouveauNomFichier;
}
/****************************************************************************
  * Fonction:
  * Description:
  * Param�tres:
  * Retour:
  ****************************************************************************/
void Graphe::lireFichier(string nomFichier)
{
	ifstream fichier(nomFichier);
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
  * Fonction:
  * Description:
  * Param�tres:
  * Retour:
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
  * Fonction:
  * Description:
  * Param�tres:
  * Retour:
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
  * Fonction:
  * Description:
  * Param�tres:
  * Retour:
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
				sommets_.push_back(nouveauSommet);
				compteurLigne++;				
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
  * Fonction:
  * Description:
  * Param�tres:
  * Retour:
  ****************************************************************************/
void Graphe::AffichageGraphe()
{

	if (compteur == 0)
	{
		cout << "|============================|" << endl;
		cout << " Affichage Graphe : " << endl;
	}
	// affichage sommet et borne 
	cout << "----------------------------------" << endl;
	
	cout << " Sommet : " << sommets_[compteur]->getNumeroDuSommet() << "| presenceBorne : ";
	(sommets_[compteur]->getPresenceBorne()) ? (cout << "oui") : (cout << "non");
	cout << endl;
	//affichage des voisins
	cout << endl;
	cout << " liste des sommets adjacents : " << endl;
	for (auto i : sommets_[compteur]->getSommetsAdjacents())
	{
		cout << "   Sommet : " << i.first->getNumeroDuSommet() << " temps : " << i.second << endl;
	}
	cout << "----------------------------------" << endl;
	compteur++;
	if (compteur == NB_MAX_SOMMETS)
	{
		compteur = 0;
		cout << "|============================|" << endl;
		return;

	}	
	AffichageGraphe();
}
/****************************************************************************
  * Fonction:
  * Description:
  * Param�tres:
  * Retour:
  ****************************************************************************/
void Graphe::EffacerTousSommets()
{
	for (auto it : sommets_)
	{
		delete(it);		
	}
	sommets_.clear();
}
/****************************************************************************
  * Fonction:
  * Description:
  * Param�tres:
  * Retour:
  ****************************************************************************/
void Graphe::miseAJourGraphe()
{
	EffacerTousSommets();
	compteurLigne = 0;
	lireFichier(nomFichier_);
	creerGraphe();
}
/****************************************************************************
  * Fonction:
  * Description:
  * Param�tres:
  * Retour:
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
  * Fonction:
  * Description:
  * Param�tres:
  * Retour:
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
  * Fonction:
  * Description:
  * Param�tres:
  * Retour:
  ****************************************************************************/
bool convertStringtoBool(string ligne)
{
	return (ligne == "1") ? true : false;
}
/****************************************************************************
  * Fonction:
  * Description:
  * Param�tres:
  * Retour:
  ****************************************************************************/
int convertStringtoInt(string ligne)
{
	stringstream convertir(ligne);
	int stringInt;
	convertir >> stringInt;
	return stringInt;
}

