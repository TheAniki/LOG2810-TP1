/****************************************************************************
 * Fichier:
 * Auteurs: Ouassim Ouali (1958275) , Pier-Luc Tanguay (1953707) et Mélody Roy ()
 * Date:
 * Description:
 ****************************************************************************/
#include "Test.h"


void exectuterTousLesTests(Graphe& graphe, Taxi& taxi, Algorithme& algorithme)
{


    //************** Test chemin le plus court **************
    
    cout << "TEST 1: chemin le plus court:" << endl;
    int depart, arrive;
    cout << endl << "  Entrer le sommet de depart: ";
    cin >> depart;
    cout << "  Entrer le sommet d'arrive: ";
    cin >> arrive;

    algorithme.plusCourtChemin(depart, arrive);


    algorithme.EffacerTousLesTrajets();

    //************** Fin Test chemin le plus court 

    
}


