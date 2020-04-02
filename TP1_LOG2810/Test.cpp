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

    cout << endl << "     Chemin le plus court pour s'y rendre: ";
    for (int i = algorithme.getListeTrajetsPossible()[0].listeSommetParcouru.size()-1; i >= 0; i--) {
        cout << algorithme.getListeTrajetsPossible()[0].listeSommetParcouru[i]->getNumeroDuSommet();
        if (i != 0)
            cout << "->";
    }
    cout << endl << "     Distance: ";
    cout << algorithme.getListeTrajetsPossible()[0].distanceTotale << endl;

    //************** Fin Test chemin le plus court 


}


