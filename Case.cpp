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

Case::Case()
{
	m_id=-1;
	m_taille=0;
	m_r=0;
	m_v=0;
	m_b=0;
	m_occupee=false;
	m_obs=true;
	//m_type=0;
	m_j=-1;
	m_i=-1;
	m_x=0;
	m_y=0;
	dessus=NULL;
	dessous=NULL;
	gauche=NULL;
	droite=NULL;
	parent=NULL;
	next=NULL;
}

Case::Case(bool obs,int x,int y, int nbCasesLargeur)
{
	m_id=x+y*nbCasesLargeur;
	m_obs=obs;
	m_taille=2*GL_VIEW_SIZE*RATIO/((float)nbCasesLargeur*3);
	//m_type=type;
	m_occupee=false;
	m_j=x;
	m_i=y;
	m_x=-RATIO+x*m_taille;
	m_y=1-y*m_taille;
	dessus=NULL;
	dessous=NULL;
	gauche=NULL;
	droite=NULL;
	parent=NULL;
	next=NULL;
	//m_tex = new Textures(this->m_surface, this->m_icone, &(this->m_idTexture));
}

// void Case::chargerTexture(){
// 	this->m_tex = new Textures(IMG_Load(this->m_icone), &(this->m_idTexture));
// }

// void Case::libererEspaceTexture(){
// 	this->m_tex->libererEspace(&(this->m_idTexture));
// }

void Case::dessinerCase()
{
	//dessinerImage(this->m_idTexture,m_x,m_x+m_taille,m_y,m_y-m_taille);
	if(this->m_occupee){
		m_occupant->dessinerUnite(this->m_x,this->m_y,this->m_taille);
	}
	drawSquare(this->m_x+0.01,this->m_y-0.01,this->m_taille-0.02,255,255,255,0.1);
}

void Case::occuper(Unite* unite)
{
	this->m_occupee=true;
	this->m_occupant=unite;
	unite->deplacer(this->m_j,this->m_i);
}

bool Case::occupee()
{
	return m_occupee;
}


void Case::liberer()
{
	this->m_occupee=false;
	this->m_occupant=NULL;
}

Unite* Case::selectUnite(){
	if(m_occupee)
	{
		return(m_occupant);
	}
	else
	{
		return NULL;
	}
}

bool Case::dansZone(int idMap, int idJoueur)
{
	bool in=true;
	switch(idMap)
	{
		case 1 :
			if(idJoueur == 1)
			{
				in=(m_j<4 && !this->m_obs && !m_occupee);
			}
			else if(idJoueur == 2)
			{
				in=(m_j>7 && !this->m_obs && !m_occupee);
			}
			break;
		case 2 :
			if(idJoueur == 1)
			{
				in=(m_j<3 && !this->m_obs && !m_occupee);
			}
			else if(idJoueur == 2)
			{
				in=(m_j>5 && !this->m_obs && !m_occupee);
			}
			break;
		default :
			return in;
			break;
	}
	return in;
}

void Case::briller(int r, int v, int b, float a)
{
	drawRect2(m_x,m_y,m_taille,m_taille,r,v,b,a);
}

Case* Case::deplacerOrdi(int mob)
{
	int i=0;
	this->liberer();
	Case* current=this;
	while(current->next!=NULL && !current->next->occupee() && i<=mob)
	{
		current=current->next;
		i++;
	}
	return current;
}

void Case::brillerleAStar(int* i)
{
	if(this->next==NULL || *i>1000)
	{
		this->briller(255,255,0,0.5);
		return;
	}
	else
	{
		this->briller(255,255,0,0.5);
		*i+=1;
		this->next->brillerleAStar(i);
	}
}

void Case::setVoisins(Case** voisins)
{
	if(voisins[0]->getId()>=0)
	{
		this->gauche = voisins[0];
		voisins[0]->setParent(this);
	}
	if(voisins[1]->getId()>=0)
	{
		this->dessus = voisins[1];
		voisins[1]->setParent(this);
	}
	if(voisins[2]->getId()>=0)
	{
		this->droite = voisins[2];
		voisins[2]->setParent(this);
	}
	if(voisins[3]->getId()>=0)
	{
		this->dessous = voisins[3];
		voisins[3]->setParent(this);
	}
}

void Case::setParent(Case* lacase)
{
	this->parent= lacase;
}

void Case::setNext(Case* lacase)
{
	this->next= lacase;
}

Case* Case::getParent()
{
	return this->parent;
}

int Case::getId()
{
	return this->m_id;
}

int Case::getX()
{
	return this->m_j;
}

int Case::getY()
{
	return this->m_i;
}

bool Case::estObstacle()
{
	if(this->m_obs)
	{
		return true;
	}
	else
	{
		return false;
	}
}