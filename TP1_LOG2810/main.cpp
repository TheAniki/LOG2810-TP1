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
Graphe optionUpdateMap(const Graphe& graphe)
{


	/*
	char afficher;

	cout << endl << "   Voulez-vous afficher le graphe? (Y/N) ";
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
		*/
	
	return graphe;
}
/****************************************************************************
  * Fonction: optionCheminPlusCourt()
  * Description: S�quence pour l'option b
  * Param�tres: aucun
  * Retour: aucun
  ****************************************************************************/
void optionCheminPlusCourt(const Graphe& graphe)
{

	Taxi taxi;

	Algorithme algorithme(graphe, taxi);

	int depart, arrive;
	cout << endl << "   1. Entrer le sommet de depart: ";
	cin >> depart;
	cout << "   2. Entrer le sommet d'arrive: ";
	cin >> arrive;

	algorithme.plusCourtChemin(depart, arrive);
	algorithme.EffacerTousLesTrajets();

}
/****************************************************************************
  * Fonction: optionTraiterRequ�te()
  * Description: S�quence pour l'option c
  * Param�tres: aucun
  * Retour: aucun
  ****************************************************************************/
void optionTraiterRequ�te(Graphe& graphe)
{
	Taxi taxi = Taxi("requetes.txt");

	taxi.miseAjourRequetes();
	taxi.placerPassagerDansGraphe();
	Algorithme algorithme(graphe, taxi);


	//Affichage
	char afficher;
	cout << endl << "   Voulez-vous afficher les requetes? (Y/N) ";

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
		cout << "=================================" << endl << endl;
	}

	algorithme.traiterRequetes();
}

int main()
{
	Graphe graphe = Graphe("arrondissements.txt");
	Taxi taxi = Taxi("requetes.txt");

	// Par d�faut on lit le fichier arrondissement.txt
	// Il peut �tre mis � jour par l'option A) lorsque le programme est d�j� lanc�
	graphe.lireFichier();
	graphe.creerGraphe();

	//******** Interface ********


	char charSelect, charContinu;

	// Forcer la selection parmis les choix disponibles
	do  
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

		// S�lection Update map
		case 'A':	
			cout << endl << "   --------------------------" << endl
			<< "   A) Mettre a jouer la carte" << endl
			<< "   --------------------------" << endl;

			// Construction du graphe � partir du fichier contenant les arrondissements
			//graphe.lireFichier();
			//graphe.creerGraphe();

			graphe.miseAJourGraphe();

			//graphe = optionUpdateMap(graphe);	


			char afficher;

			cout << endl << "   Voulez-vous afficher le graphe? (Y/N) ";
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

			break;


		// S�lection Chemin plus court
		case 'B' :	

			graphe.miseAJourGraphe();
			cout << endl << "   ----------------------------------------------" << endl
				<< "   B) Determiner le plus court chemin securitaire" << endl
				<< "   ----------------------------------------------" << endl;
			optionCheminPlusCourt(graphe);
			break;



		// S�lection Traiter requ�tes
		case 'C' :	

			graphe.miseAJourGraphe();
			cout << endl << "   -----------------------" << endl
				<< "   C) Traiter les requetes" << endl
				<< "   -----------------------" << endl;
			optionTraiterRequ�te(graphe);
			break;

		// S�lection Quitter
		case 'D':
					cout << endl << "   D) Quitter" << endl;
			break;


		default:						
			break;
		}
		if (charSelect != 'D'){
				// Forcer la selection entre y et n
				do 
				{
					cout << endl << "   Retourner au menu principal? (Y/N) ";
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
	return 0;
}

