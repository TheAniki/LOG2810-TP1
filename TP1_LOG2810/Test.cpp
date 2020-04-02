/****************************************************************************
 * Fichier:
 * Auteurs: Ouassim Ouali (1958275) , Pier-Luc Tanguay (1953707) et Mélody Roy ()
 * Date:
 * Description:
 ****************************************************************************/
#include "Test.h"


void exectuterTousLesTests()
{

    Graphe graphe = Graphe("arrondissements.txt");
    

    Taxi taxi = Taxi("requetes.txt");

    graphe.miseAJourGraphe();

    Algorithme algo(graphe,taxi);

    algo.plusCourtChemin(12, 2);


}


