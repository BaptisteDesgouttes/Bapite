#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "constantes.hpp"
#include "Textures.hpp"
#include "Unite.hpp"
#include "Case.hpp"
#include "Noeud.hpp"
#include "Map.hpp"
#include "bouton.hpp"
#include "Joueur.hpp"
#include "ordinateur.hpp"
#include "Menu.hpp"
#include "fonctions.hpp"

using namespace std;

Ordinateur::Ordinateur() : Joueur()
{

}

Ordinateur::Ordinateur(int id, int r, int v, int b) : Joueur(id,r,v,b), m_uniteCible(new Unite())
{
	
}

void Ordinateur::setUniteCible(Joueur* joueur)
{
	if(m_uniteCible->estMorte())
	{
		this->m_uniteCible=joueur->selectionIA();
	}
}

void Ordinateur::tourOrdi(Unite** uniteActuelle, Case** depart, Map* carte)
{
    (*depart) = carte->caseSelectionnee((*uniteActuelle)->getX(),(*uniteActuelle)->getY());
    Case* caseCible = carte->caseSelectionnee(this->m_uniteCible->getX(),this->m_uniteCible->getY());
    carte->AStar(depart,caseCible);
    Case* dest=(*depart)->deplacerOrdi((*uniteActuelle)->getMobilite());
	(*uniteActuelle)->deplacer(dest->getX(),dest->getY());
	dest->occuper(*uniteActuelle);
	if((*uniteActuelle)->verifPortee(this->m_uniteCible->getX(),this->m_uniteCible->getY()))
	{
		(*uniteActuelle)->attaquer(this->m_uniteCible);
	}
    //(*depart)->brillerleAStar();

	//printf("%c \n",(*uniteActuelle)->getType());
}