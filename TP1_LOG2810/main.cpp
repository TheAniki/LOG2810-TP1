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
		<< " D -> QUITTER" << endl << endl
		<< " T -> Lancer les tests (temporaire)" << endl << endl
		<< "Choisir option (A, B, C ou D) : ";
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
	if (choix == 'D') return true;
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

	cout << endl << "   1. Voulez-vous afficher le graphe? (Y/N) ";
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
	cout << endl << "   2. Voulez-vous afficher les requetes? (Y/N) ";

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
  * Description: Séquence pour l'option b
  * Paramètres: aucun
  * Retour: aucun
  ****************************************************************************/
void optionCheminPlusCourt(Algorithme& algorithme)
{

	int depart, arrive;
	cout << endl << "   1. Entrer le sommet de depart: ";
	cin >> depart;
	cout << "   2. Entrer le sommet d'arrive: ";
	cin >> arrive;

	algorithme.plusCourtChemin(depart, arrive);
	algorithme.EffacerTousLesTrajets();

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
	graphe.lireFichier();
	graphe.creerGraphe();

	Taxi taxi = Taxi("requetes.txt");
	taxi.lireFichier();
	taxi.placerPassagerDansGraphe();

	Algorithme algorithme(graphe, taxi);



	// methode de selectionnement du menu
	char charSelect, charContinu;


	do  // force selection parmis les choix disponibles
	{
		system("CLS");
		affichageOptions();

		cin >> charSelect;
		charSelect = toupper(charSelect);

	} while (!choixPossible(charSelect));
	
		
	while (charSelect != 'D')
	{
		switch (charSelect)
		{

		// Sélection Update map
		case 'A':	
			cout << endl << "   --------------------------" << endl
			<< "   A) Mettre a jouer la carte" << endl
			<< "   --------------------------" << endl;
			optionUpdateMap(graphe, taxi);		
			break;


		// Sélection Chemin plus court
		case 'B' :	

			cout << endl << "   ----------------------------------------------" << endl
				<< "   B) Determiner le plus court chemin securitaire" << endl
				<< "   ----------------------------------------------" << endl;
			optionCheminPlusCourt(algorithme);
			break;



		// Sélection Traiter requêtes
		case 'C' :	

			cout << endl << "   -----------------------" << endl
				<< "   C) Traiter les requetes" << endl
				<< "   -----------------------" << endl;
			optionTraiterRequête();
			break;

		// Sélection Quitter
		case 'D':
					cout << endl << "   D) Quitter" << endl;
			break;

		// Sélection Tests
		case 'T':
					 cout << endl << "****************** Debut des tests ******************" << endl << endl;
				     exectuterTousLesTests(graphe, taxi, algorithme);
			break;

		default:						
			break;
		}
		if (charSelect != 'D'){

				do // force selection entre y et n
				{
					cout << endl << "Retourner au menu principal? (Y/N) ";
					cin >> charContinu;
					charContinu = toupper(charContinu);
			

				} while (!choixYesNo(charContinu));				

				if (charContinu == 'Y')
				{
					system("CLS");
					affichageOptions();
					cin >> charSelect;
					charSelect = toupper(charSelect);

				}
				if (charContinu == 'N')
				{
					system("CLS");
					charSelect = 'D';
				}			
		}		
		
	}
	//====================================================================================//
	return 0;
}

