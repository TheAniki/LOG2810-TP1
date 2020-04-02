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
	cout << endl
		<< " A -> Mettre a jouer la carte" << endl
		<< " B -> Determiner le plus court chemin securitaire" << endl
		<< " C -> Traiter les requetes" << endl
		<< " T -> Lancer les tests" << endl 
		<< " Q -> QUITTER" << endl << endl
		<< "Choisir option (A, B, C, T ou Q) : ";
}
/****************************************************************************
  * Fonction: choixPossible
  * Description: Permet de forcer la sélection parmit les char dans les if
  * Paramètres: char choix
  * Retour: vrai si choix est parmis les choix possible, faux si autre
  ****************************************************************************/

bool choixPossible(char choix)
{
	if (choix == 'A') return true;
	if (choix == 'B') return true;
	if (choix == 'C') return true;
	if (choix == 'Q') return true;
	if (choix == 'T') return true;
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
	if (choix == 'Y') return true;
	if (choix == 'N') return true;
	return false;
}
/****************************************************************************
  * Fonction: optionUpdateMap()
  * Description: Séquence pour l'option a
  * Paramètres: aucun
  * Retour: aucun
  ****************************************************************************/
void optionUpdateMap(Graphe& graphe, Taxi& taxi)
{
	char afficher;

	cout << endl << "Voulez-vous afficher le graphe? (Y/N) ";
	cin >> afficher;
	cout << endl;

	while (!choixYesNo(afficher))
	{
		cin >> afficher;
	}

	if (afficher == 'Y')
		graphe.AffichageGraphe();
	cout << endl << "Voulez-vous afficher les requetes? (Y/N) ";
	cin >> afficher;
	cout << endl;
	while (!choixYesNo(afficher))
	{
		cin >> afficher;
	}
	if (afficher == 'Y')
		cout << "=================================" << endl;
		cout << " Affichage de requetes: " << endl << endl;

		taxi.afficherRequetes();
		cout << "=================================" << endl;

}
/****************************************************************************
  * Fonction: optionCheminPlusCourt()
  * Description: Séquence pour l'option b
  * Paramètres: aucun
  * Retour: aucun
  ****************************************************************************/
void optionCheminPlusCourt()
{

}
/****************************************************************************
  * Fonction: optionTraiterRequête()
  * Description: Séquence pour l'option c
  * Paramètres: aucun
  * Retour: aucun
  ****************************************************************************/
void optionTraiterRequête()
{

}

int main()
{
	Graphe graphe = Graphe("arrondissements.txt");
	Taxi taxi = Taxi("requetes.txt");

	graphe.miseAJourGraphe();
	taxi.miseAjourRequetes();

	Algorithme algorithme(graphe, taxi);
	//====================================================================================//
	// methode de selectionnement du menu
	char select, continu;
	//Graphe graphe;


	do  // force selection parmis les choix disponibles
	{
		system("CLS");
		affichageOptions();
		cin >> select;
	} while (!choixPossible(select));
	
		
	while (select != 'Q')
	{
		switch (select)
		{
		case 'A':	
					cout << endl << "   Choix: Mettre a jouer la carte" << endl;
					optionUpdateMap(graphe, taxi);		


			break;
		case 'B' :	
					cout << endl << "   Choix: Determiner le plus court chemin securitaire" << endl;
					optionCheminPlusCourt();
			break;
		case 'C' :	
					cout << endl << "   Choix:  les requetes" << endl;
					optionTraiterRequête();
			break;


		case 'T': 
					 cout << endl << "****************** Debut des tests ******************" << endl << endl;
				     exectuterTousLesTests(graphe, taxi, algorithme);

		case 'Q':
			cout << endl << "   Choix: Quitter" << endl;
			break;

		default:						
			break;
		}
		if (select != 'Q'){

				do // force selection entre y et n
				{
					cout << endl << "Retourner au menu principal? (Y/N) ";
					cin >> continu;

				} while (!choixYesNo(continu));				

				if (continu == 'Y')
				{
					system("CLS");
					affichageOptions();
					cin >> select;
				}
				if (continu == 'N')
				{
					system("CLS");
					select = 'Q';
				}			
		}		
		
	}
	//====================================================================================//
	return 0;
}

