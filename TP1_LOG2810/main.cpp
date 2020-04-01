/****************************************************************************
 * Fichier:
 * Auteurs: Ouassim Ouali (1958275) , Pier-Luc Tanguay () et Mélody Roy ()
 * Date: 22 Mars 2020
 * Description:
 ****************************************************************************/
#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h> 
#include <vector>
#include <sstream>

#include "Graphe.h"
#include "Taxi.h"
#include "Test.h"
#include "algorithme.h"
#include "Sommet.h"
#include "Passager.h"

using namespace std;
/****************************************************************************
  * Fonction: affichageOptions()
  * Description: Permet d'afficher les options
  * Paramètres: aucun
  * Retour: aucun
  ****************************************************************************/
void affichageOptions()
{
	cout << " Selectionner operation voulue : " << endl
		<< " a : Mettre a jouer la carte ." << endl
		<< " b : Determiner le plus court chemin securitaire. " << endl
		<< " c : Traiter les requetes. " << endl
		<< " d : Quitter. " << endl
		<< " t : tests " << endl;
}
/****************************************************************************
  * Fonction: choixPossible
  * Description: Permet de forcer la sélection parmit les char dans les if
  * Paramètres: char choix
  * Retour: vrai si choix est parmis les choix possible, faux si autre
  ****************************************************************************/

bool choixPossible(char choix)
{
	if (choix == 'a') return true;
	if (choix == 'b') return true;
	if (choix == 'c') return true;
	if (choix == 'd') return true;
	if (choix == 't') return true;
	return false;
}
/****************************************************************************
  * Fonction: choixYesNo 
  * Description: Permet de forcer la sélection à y/n 
  * Paramètres: char choix
  * Retour: vrai si y ou n , faux pour le reste
  ****************************************************************************/
/*
methode choixYesNo 
retourne true si choix est y et n sinon
retourne false
*/
bool choixYesNo(char choix)
{
	if (choix == 'y') return true;
	if (choix == 'n') return true;
	return false;
}
/****************************************************************************
  * Fonction: MethodeDeLOptionA()
  * Description: Séquence pour l'option a
  * Paramètres: aucun
  * Retour: aucun
  ****************************************************************************/
void MethodeDeLOptionA()
{
	
	Graphe graphe = Graphe("arrondissements.txt");
	Taxi taxi = Taxi("requetes.txt");
	char afficher;

	graphe.miseAJourGraphe();
	taxi.miseAjourRequetes();

	cout << " voulez-vous afficher le graphe? (y/n)" << endl;
	cin >> afficher;
	while (!choixYesNo(afficher))
	{
		cin >> afficher;
	}
	if (afficher == 'y')
		graphe.AffichageGraphe();
	cout << " voulez-vous afficher les requetes? (y/n)" << endl;
	cin >> afficher;
	while (!choixYesNo(afficher))
	{
		cin >> afficher;
	}
	if (afficher == 'y')
		taxi.afficherRequetes();		
}
/****************************************************************************
  * Fonction: MethodeDeLOptionB()
  * Description: Séquence pour l'option b
  * Paramètres: aucun
  * Retour: aucun
  ****************************************************************************/
void MethodeDeLOptionB()
{

}
/****************************************************************************
  * Fonction: MethodeDeLOptionC()
  * Description: Séquence pour l'option c
  * Paramètres: aucun
  * Retour: aucun
  ****************************************************************************/
void MethodeDeLOptionC()
{

}

int main()
{

	//====================================================================================//
	// methode de selectionnement du menu
	char select, continu, afficher;
	Graphe graphe;
	do  // force selection parmis les choix disponibles
	{
		system("CLS");
		affichageOptions();
		cin >> select;
	} while (!choixPossible(select));
	
		
	while (select != 'd')
	{
		switch (select)
		{
		case 'a':	cout << "Mettre a jouer la carte ." << endl;
					MethodeDeLOptionA();		
			break;
		case 'b' :	cout << "Determiner le plus court chemin securitaire. " << endl;
					MethodeDeLOptionB();
			break;
		case 'c' :	cout << "Traiter les requetes. " << endl;
					MethodeDeLOptionC();
			break;
		case 'd' : cout << "Quitter" << endl;
			break;
		case 't': cout << "test" << endl; // si besoin
				  exectuterTousLesTests();

		default:						
			break;
		}
		if (select != 'd'){

				do // force selection entre y et n
				{
					cout << "continue? (y/n)" << endl;
					cin >> continu;

				} while (!choixYesNo(continu));				

				if (continu == 'y')
				{
					system("CLS");
					affichageOptions();
					cin >> select;
				}
				if (continu == 'n')
				{
					system("CLS");
					select = 'd';
				}			
		}		
		
	}
	//====================================================================================//
	return 0;
}

