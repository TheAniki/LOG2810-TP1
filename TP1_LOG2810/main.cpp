/****************************************************************************
 * Fichier:
 * Auteurs: Ouassim Ouali (1958275) , Pier-Luc Tanguay () et M�lody Roy ()
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
  * Param�tres: aucun
  * Retour: aucun
  ****************************************************************************/
void affichageOptions()
{
	cout << endl
		<< " A -> Mettre a jouer la carte" << endl
		<< " B -> Determiner le plus court chemin securitaire" << endl
		<< " C -> Traiter les requetes" << endl
		<< " D -> QUITTER" << endl << endl
		<< " T -> Lancer les tests (temporaire)" << endl << endl
		<< "Choisir option (A, B, C ou D) : ";
}
/****************************************************************************
  * Fonction: choixPossible
  * Description: Permet de forcer la s�lection parmit les char dans les if
  * Param�tres: char choix
  * Retour: vrai si choix est parmis les choix possible, faux si autre
  ****************************************************************************/

bool choixPossible(char choix)
{

	if (choix == 'A') return true;
	if (choix == 'B') return true;
	if (choix == 'C') return true;
	if (choix == 'D') return true;
	if (choix == 'T') return true;
	return false;
}
/****************************************************************************
  * Fonction: choixYesNo 
  * Description: Permet de forcer la s�lection � y/n 
  * Param�tres: char choix
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
  * Description: S�quence pour l'option a
  * Param�tres: aucun
  * Retour: aucun
  ****************************************************************************/
void optionUpdateMap(Graphe& graphe, Taxi& taxi)
{
	char afficher;

	cout << endl << "Voulez-vous afficher le graphe? (Y/N) ";
	cin >> afficher;
	afficher = toupper(afficher);
	cout << endl;

	while (!choixYesNo(afficher))
	{
		cin >> afficher;
		afficher = toupper(afficher);
	}

	if (afficher == 'Y')
		graphe.AffichageGraphe();
	cout << endl << "Voulez-vous afficher les requetes? (Y/N) ";
	cin >> afficher;
	afficher = toupper(afficher);
	cout << endl;
	while (!choixYesNo(afficher))
	{
		cin >> afficher;
		afficher = toupper(afficher);
	}
	if (afficher == 'Y') {
		cout << "=================================" << endl;
		cout << " Affichage de requetes: " << endl << endl;

		taxi.afficherRequetes();
		cout << "=================================" << endl;
	}
}
/****************************************************************************
  * Fonction: optionCheminPlusCourt()
  * Description: S�quence pour l'option b
  * Param�tres: aucun
  * Retour: aucun
  ****************************************************************************/
void optionCheminPlusCourt()
{

}
/****************************************************************************
  * Fonction: optionTraiterRequ�te()
  * Description: S�quence pour l'option c
  * Param�tres: aucun
  * Retour: aucun
  ****************************************************************************/
void optionTraiterRequ�te()
{

}

int main()
{
	Graphe graphe = Graphe("arrondissements.txt");
	graphe.lireFichier();
	graphe.creerGraphe();

	Taxi taxi = Taxi("requetes.txt");
	taxi.lireFichier();
	taxi.placerPassagerDansGraphe();

	Algorithme algorithme(graphe, taxi);




	//====================================================================================//
	// methode de selectionnement du menu
	char select, continu;


	do  // force selection parmis les choix disponibles
	{
		system("CLS");
		affichageOptions();
		cin >> select;
		select = toupper(select);
	} while (!choixPossible(select));
	
		
	while (select != 'D')
	{
		switch (select)
		{

		// S�lection Update map
		case 'A':	
					cout << endl << "   Choix: Mettre a jouer la carte" << endl;
					optionUpdateMap(graphe, taxi);		
			break;


		// S�lection Chemin plus court
		case 'B' :	
					cout << endl << "   Choix: Determiner le plus court chemin securitaire" << endl;
					optionCheminPlusCourt();
			break;



		// S�lection Traiter requ�tes
		case 'C' :	
					cout << endl << "   Choix: Traiter les requetes" << endl;
					optionTraiterRequ�te();
			break;

		// S�lection Quitter
		case 'D':
					cout << endl << "   Choix: Quitter" << endl;
			break;

		// S�lection Tests
		case 'T':
					 cout << endl << "****************** Debut des tests ******************" << endl << endl;
				     exectuterTousLesTests(graphe, taxi, algorithme);
			break;






		default:						
			break;
		}
		if (select != 'D'){

				do // force selection entre y et n
				{
					cout << endl << "Retourner au menu principal? (Y/N) ";
					cin >> continu;
					continu = toupper(continu);

				} while (!choixYesNo(continu));				

				if (continu == 'Y')
				{
					system("CLS");
					affichageOptions();
					cin >> select;
					continu = toupper(continu);

				}
				if (continu == 'N')
				{
					system("CLS");
					select = 'D';
				}			
		}		
		
	}
	//====================================================================================//
	return 0;
}

