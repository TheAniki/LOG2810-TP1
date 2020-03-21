/****************************************************************************
 * Fichier:
 * Auteurs:
 * Date:
 * Description:
 ****************************************************************************/
#include "Passager.h"

Passager::Passager() : id_(0), sommetDepart_(0),
destination_(0), tempsArrivee_(0)
{
}
Passager::Passager(int id, int sommetDepart, int destination, int tempsArrivee) : id_(id), sommetDepart_(sommetDepart),
	destination_(destination), tempsArrivee_(tempsArrivee)
{

}
Passager::~Passager()
{
}


const int Passager::getTempsArrivee()
{
	return tempsArrivee_;
}

const int Passager::getDestination()
{
	return destination_;
}
const int Passager::getSommetDepart()
{
	return sommetDepart_;
}
const int Passager::getId()
{
	return id_;
}

bool Passager::operator==(const Passager& passager) const
{
	return (
		id_ == passager.id_ &&
		sommetDepart_ == passager.sommetDepart_ &&
		destination_ == passager.destination_ &&
		tempsArrivee_ == passager.tempsArrivee_
		);
}
