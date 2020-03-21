/****************************************************************************
 * Fichier:
 * Auteurs:
 * Date:
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

using namespace std;
/****************************************************************************
  * Fonction:
  * Description:
  * Paramètres:
  * Retour:
  ****************************************************************************/
//Methode permettant l'affichage des options
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
  * Fonction:
  * Description:
  * Paramètres:
  * Retour:
  ****************************************************************************/
/*
methode choixPossible
retourne true si choix est a,b,d ou d sinon
retourne false
*/
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
  * Fonction:
  * Description:
  * Paramètres:
  * Retour:
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
  * Fonction:
  * Description:
  * Paramètres:
  * Retour:
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
  * Fonction:
  * Description:
  * Paramètres:
  * Retour:
  ****************************************************************************/
void MethodeDeLOptionB()
{

}
/****************************************************************************
  * Fonction:
  * Description:
  * Paramètres:
  * Retour:
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

