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

Joueur::Joueur(){

}

Joueur::Joueur(int id, int r, int v, int b)
{
	m_id =id;
	m_r = r;
	m_v = v;
	m_b = b;
	m_fonds = 100;
	m_nbUnites = 0;
	m_tabUnites= (Unite**)malloc(15*sizeof(Unite*));
	for (int i=0; i<15;i++)
	{
	    m_tabUnites[i] = new Unite();
	}
	// utilisees= (bool*)malloc(15*sizeof(bool));
	// for (int i=0; i<15;i++)
	// {
	//     utilisees[i] = false;
	// }
}

Unite* Joueur::creationUnite(char type)
{
	Unite* unite = new Unite(this->m_id,type);
	this->ajouterUniteAuTableau(unite);
	return unite;
}

bool Joueur::achatUnite(char type,int valeur)
{
	if (this->m_fonds>=valeur)
	{
		this->m_fonds-=valeur;
		return true;
	}
	else
	{
		return false;
	}
}

void Joueur::chargerLesIcones(int nbUniteDepart)
{
	for (int i=nbUniteDepart; i<15;i++)
	{
	   	m_tabUnites[i]->chargerIcone();
	}
}

void Joueur::libererEspaceUnites()
{
	for (int i=0; i<15;i++)
	{
	    m_tabUnites[i]->libererEspace();
	}
}

void Joueur::ajouterUniteAuTableau(Unite* unite)
{
	int i;
    for(i=0; i<15; i++)
    {
    	if(m_tabUnites[i]->estMorte())
    	{
        	m_tabUnites[i] = unite;
	    	this->m_nbUnites+=1;
        	break;
    	}
    }
    if(i==15)
    {
    	printf("On ne peut pas avoir plus de 15 unités \n");
    }
    // if(this->m_nbUnites==15)
    // {
    // 	printf("On ne peut pas avoir plus de 15 unités \n");
    // }
    // else
    // {
	   //  this->m_tabUnites[this->m_nbUnites]=unite;
	   //  this->m_nbUnites+=1;
    // }
}

bool Joueur::appartient(Unite* unite)
{
	if(unite->getId()==this->m_id)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Joueur::libererCasesVides(Map* carte)
{
	for(int i=0; i<15; i++)
	{
		if(this->m_tabUnites[i]->estMorte() && this->appartient(this->m_tabUnites[i]))
		{
			carte->libererCase(this->m_tabUnites[i]->getX(),this->m_tabUnites[i]->getY());
			this->m_tabUnites[i]->libererEspace();
			this->m_tabUnites[i]=new Unite();
			this->m_nbUnites-=1;

			this->m_fonds+=10;
		}
	}
}

bool Joueur::tourFini()
{
	// for(int i=0;i>15;i++)
	// {
	// 	if(!m_tabUnites[i]->utilisee())
	// 	{
	// 		return false;
	// 	}
	// }
	// return true;
	int i=0;
	while(i<15 && this->m_tabUnites[i]->utilisee())
	{
		i++;
	}
	if(i==15)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Joueur::finTour()
{
	// for(int i=0;i<15;i++)
	// {
	// 	if(!this->m_tabUnites[i]->estMorte())
	// 	{
	// 		utilisees[i]=true;
	// 	}
	// 	else
	// 	{
	// 		utilisees[i]=false;
	// 	}
	// }
	for(int i=0;i<15;i++)
	{
		if(!this->m_tabUnites[i]->estMorte())
		{
			this->m_tabUnites[i]->desutiliser();
		}
	}
	this->argentFinDeTour();
}

void Joueur::miseAJourDonnees(Textures** textunite, Textures** textargent)
{
	(*textunite)->libererTexte();
	(*textargent)->libererTexte();

	char nbUnites[16];
    sprintf(nbUnites,"%d",this->m_nbUnites);
    switch(this->m_id)
    {
    	case 1 :
    		(*textunite)->chargeTexte(nbUnites,60,0,0,255);
    		break;
    	case 2 :
    		(*textunite)->chargeTexte(nbUnites,60,255,0,0);
   			break;
    	case 3 :
    		(*textunite)->chargeTexte(nbUnites,60,255,0,0);
   			break;

    }
    char argent[16];
    sprintf(argent,"%d",this->m_fonds);
    (*textargent)->chargeTexte(argent,80,255,255,0);
}

Unite* Joueur::selectionIA()
{
	int i=0;
	while((this->m_tabUnites[i]->estMorte() || this->m_tabUnites[i]->utilisee()) && i<15)
	{
		i++;
	}
	return this->m_tabUnites[i];
}

bool Joueur::perdant()
{
	if(this->m_nbUnites==0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Joueur::argentFinDeTour(){
	this->m_fonds+=5;
}

void Joueur::argentUniteTuee(){
	this->m_fonds+=50;
}

void Joueur::argentSuicide()
{
	this->m_fonds+=20;
}

void Joueur::mortUnite(Map* carte)
{
	for(int i=0; i<15; i++)
	{
		if(this->m_tabUnites[i]->estMorte() && this->appartient(this->m_tabUnites[i]))
		{
			this->m_fonds+=20;
			cout << "\n\n\n\n\n\n\n mort unite" << endl;
		}
	}
}

void Joueur::printTabUnite()
{
  	for (int i =0; i<15; i++)
  	{
    	m_tabUnites[i]->afficherConsole();
  	}
}

int Joueur::returnNbUnites()
{
  	return m_nbUnites;
}

int Joueur::returnFonds()
{
	return m_fonds;
}
