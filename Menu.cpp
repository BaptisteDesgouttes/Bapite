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

Menu::Menu(int id){
	m_id = id;
	switch(id)
	{
		case 1 :
			m_icone="img/fond_menu_2.jpg"; //Référence du fichier de l'icone de l'unite
			m_nbBoutons = 5;
			m_xg=-RATIO*GL_VIEW_SIZE/2.;
			m_xd=RATIO*GL_VIEW_SIZE/2.;
			m_yh=GL_VIEW_SIZE/2.;
			m_yb=-GL_VIEW_SIZE/2.;
			break;
		case 2 :
			m_icone="img/background_boutons.png";
			m_nbBoutons = 3;
			m_xg=GL_VIEW_SIZE*RATIO/2./3.;
			m_xd=RATIO*GL_VIEW_SIZE/2.;
			m_yh=GL_VIEW_SIZE/2./3.;
			m_yb=-GL_VIEW_SIZE/2.;
			break;
		case 3 :
			m_icone="img/background_boutons.png";
			m_nbBoutons = 3;
			m_xg=GL_VIEW_SIZE*RATIO/2./3.;
			m_xd=RATIO*GL_VIEW_SIZE/2.;
			m_yh=GL_VIEW_SIZE/2./3.;
			m_yb=-GL_VIEW_SIZE/2.;
			break;
		case 4 :
			m_icone="img/background_boutons.png";
			m_nbBoutons = 1;
			m_xg=GL_VIEW_SIZE*RATIO/2./3.;
			m_xd=RATIO*GL_VIEW_SIZE/2.;
			m_yh=GL_VIEW_SIZE/2./3.;
			m_yb=-GL_VIEW_SIZE/2.;
			break;
		case 5 :
			m_icone="img/background_boutons.png";
			//m_nbBoutons = 2;
			m_nbBoutons = 1;
			m_xg=GL_VIEW_SIZE*RATIO/2./3.;
			m_xd=RATIO*GL_VIEW_SIZE/2.;
			m_yh=GL_VIEW_SIZE/2./3.;
			m_yb=-GL_VIEW_SIZE/2.;
			break;
		// case 6 :
		// 	m_icone="img/fond_menu.jpg";
		// 	m_nbBoutons = 1;
		// 	m_xg=GL_VIEW_SIZE*RATIO/2./3.;
		// 	m_xd=RATIO*GL_VIEW_SIZE/2.;
		// 	m_yh=GL_VIEW_SIZE/2./3.;
		// 	m_yb=-GL_VIEW_SIZE/2.;
		// 	break;
		case 7 :
			m_icone="img/background_boutons.png";
			//m_nbBoutons = 2;
			m_nbBoutons = 1;
			m_xg=GL_VIEW_SIZE*RATIO/2./3.;
			m_xd=RATIO*GL_VIEW_SIZE/2.;
			m_yh=GL_VIEW_SIZE/2./3.;
			m_yb=-GL_VIEW_SIZE/2.;
			break;
		case 8 :
			m_icone="img/background_boutons.png";
			m_nbBoutons = 6;
			m_xg=GL_VIEW_SIZE*RATIO/2./3.;
			m_xd=RATIO*GL_VIEW_SIZE/2.;
			m_yh=GL_VIEW_SIZE/2./3.;
			m_yb=-GL_VIEW_SIZE/2.;
			break;
		case 9 :
			m_icone="img/menu_joueur_clair.png";
			m_nbBoutons = 1;
			m_xg=GL_VIEW_SIZE*RATIO/2./3.;
			m_xd=RATIO*GL_VIEW_SIZE/2.;
			m_yh=GL_VIEW_SIZE/2;
			m_yb=GL_VIEW_SIZE/2./3.;
			break;
		case 10 :
			m_icone="img/fond_menu_couleurs.jpg"; //Référence du fichier de l'icone de l'unite
			m_nbBoutons = 7;
			m_xg=-RATIO*GL_VIEW_SIZE/2;
			m_xd=RATIO*GL_VIEW_SIZE/2;
			m_yh=GL_VIEW_SIZE/2;
			m_yb=-GL_VIEW_SIZE/2;
			break;
		case 11 :
			m_icone="img/bouton_pas_survole.png";
			m_nbBoutons = 1;
			m_xg=-GL_VIEW_SIZE*RATIO/2.;
			m_xd=GL_VIEW_SIZE*RATIO/2./3.;
			m_yh=GL_VIEW_SIZE/2.-(4./9.)*GL_VIEW_SIZE*RATIO;
			m_yb=-GL_VIEW_SIZE/2.;
			break;
		case 12 :
			m_icone="img/menu_joueur_clair.png";
			m_nbBoutons = 6;
			m_xg=-GL_VIEW_SIZE*RATIO/4.;
			m_xd=GL_VIEW_SIZE*RATIO/4.;
			m_yh=GL_VIEW_SIZE/4.;
			m_yb=-GL_VIEW_SIZE/4.;
			break;
		case 13 :
			m_icone="img/fond_regles.jpg"; //Référence du fichier de l'icone de l'unite
			m_nbBoutons = 7;
			m_xg=-RATIO*GL_VIEW_SIZE/2;
			m_xd=RATIO*GL_VIEW_SIZE/2;
			m_yh=GL_VIEW_SIZE/2;
			m_yb=-GL_VIEW_SIZE/2;
			break;
		case 14 :
			m_icone="img/fond_menu_2.jpg"; //Référence du fichier de l'icone de l'unite
			m_nbBoutons = 1;
			m_xg=-RATIO*GL_VIEW_SIZE/2.;
			m_xd=RATIO*GL_VIEW_SIZE/2.;
			m_yh=GL_VIEW_SIZE/2.;
			m_yb=-GL_VIEW_SIZE/2.;
			break;
	}
	tabBoutons = (Bouton**) malloc(this->m_nbBoutons*sizeof(Bouton*));
	for(int i=0; i<this->m_nbBoutons; i++)
	{
		tabBoutons[i]= new Bouton();
	}
}


void Menu::chargerFond()
{
	this->m_tex = new Textures(IMG_Load(this->m_icone),&(this->m_texture));
}

void Menu::dessinerFond()
{
	dessinerImage(this->m_texture,this->m_xg,this->m_xd,this->m_yh,this->m_yb);
}

void Menu::libererEspace()
{
	this->m_tex->libererEspace(&(this->m_texture));
	for(int i=0; i<this->m_nbBoutons; i++)
	{
		this->tabBoutons[i]->libererEspace();
	}
}

void Menu::chargerBoutons()
{
	switch(this->m_id)
	{
		case 1 :
			this->tabBoutons[0] = new Bouton(0,0,0.9,0.1,"img/bouton_bois.png");
			this->tabBoutons[1] = new Bouton(0,-0.2,0.9,0.1,"img/bouton_bois.png");
			this->tabBoutons[2] = new Bouton(0,-0.4,0.9,0.1,"img/bouton_bois.png");
			this->tabBoutons[3] = new Bouton(0,-0.6,0.9,0.1,"img/bouton_bois.png");
			this->tabBoutons[4] = new Bouton(1.6,-0.8,0.2,0.2,"img/regles.png");
			break;
		case 2 :
			this->tabBoutons[0] = new Bouton((this->m_xg+this->m_xd)/2,this->m_yb+5*(this->m_yh-this->m_yb)/6,this->m_xd-this->m_xg-0.1,(this->m_yh-this->m_yb)/3-0.1,"img/bouton_pas_survole.png");
			this->tabBoutons[1] = new Bouton((this->m_xg+this->m_xd)/2,this->m_yb+(this->m_yh-this->m_yb)/2,this->m_xd-this->m_xg-0.1,(this->m_yh-this->m_yb)/3-0.1,"img/bouton_pas_survole.png");
			this->tabBoutons[2] = new Bouton((this->m_xg+this->m_xd)/2,this->m_yb+(this->m_yh-this->m_yb)/6,this->m_xd-this->m_xg-0.1,(this->m_yh-this->m_yb)/3-0.15,"img/bouton_pas_survole.png");
			break;
		case 3 :
			this->tabBoutons[0] = new Bouton((this->m_xg+this->m_xd)/2,this->m_yb+5*(this->m_yh-this->m_yb)/6,this->m_xd-this->m_xg-0.1,(this->m_yh-this->m_yb)/3-0.1,"img/bouton_pas_survole.png");
			this->tabBoutons[1] = new Bouton((this->m_xg+this->m_xd)/2,this->m_yb+(this->m_yh-this->m_yb)/2,this->m_xd-this->m_xg-0.1,(this->m_yh-this->m_yb)/3-0.1,"img/bouton_pas_survole.png");
			this->tabBoutons[2] = new Bouton((this->m_xg+this->m_xd)/2,this->m_yb+(this->m_yh-this->m_yb)/6,this->m_xd-this->m_xg-0.1,(this->m_yh-this->m_yb)/3-0.15,"img/bouton_pas_survole.png");
			break;
		case 4 :
			this->tabBoutons[0] = new Bouton((this->m_xg+this->m_xd)/2,this->m_yb+(this->m_yh-this->m_yb)/6,this->m_xd-this->m_xg-0.1,(this->m_yh-this->m_yb)/3-0.15,"img/bouton_pas_survole.png");
			break;
		case 5 :
			this->tabBoutons[0] = new Bouton((this->m_xg+this->m_xd)/2,this->m_yb+(this->m_yh-this->m_yb)/6,this->m_xd-this->m_xg-0.1,(this->m_yh-this->m_yb)/3-0.15,"img/bouton_pas_survole.png");
			//this->tabBoutons[1] = new Bouton((this->m_xg+this->m_xd)/2,this->m_yb+(this->m_yh-this->m_yb)/2,this->m_xd-this->m_xg-0.1,(this->m_yh-this->m_yb)/3-0.15,"img/bouton_pas_survole.jpg");
			break;
		// case 6 :
		// 	this->tabBoutons[0] = new Bouton((this->m_xg+this->m_xd)/2,this->m_yb+(this->m_yh-this->m_yb)/6,this->m_xd-this->m_xg-0.1,(this->m_yh-this->m_yb)/3-0.15,"img/bouton_pas_survole.jpg");
		// 	break;
		case 7 :
			this->tabBoutons[0] = new Bouton((this->m_xg+this->m_xd)/2,this->m_yb+(this->m_yh-this->m_yb)/6,this->m_xd-this->m_xg-0.1,(this->m_yh-this->m_yb)/3-0.15,"img/bouton_pas_survole.png");
			//this->tabBoutons[1] = new Bouton((this->m_xg+this->m_xd)/2,this->m_yb+(this->m_yh-this->m_yb)/2,this->m_xd-this->m_xg-0.1,(this->m_yh-this->m_yb)/3-0.15,"img/bouton_pas_survole.jpg");
			break;
		case 8 :
			this->tabBoutons[0] = new Bouton((this->m_xg+this->m_xd)/2-(((this->m_yh-this->m_yb)/3-0.1)/2+0.1),this->m_yh-(this->m_yh-this->m_yb)/6+0.1,(this->m_yh-this->m_yb)/3-0.1,(this->m_yh-this->m_yb)/3-0.1,"img/unites/nain2.png");
			this->tabBoutons[1] = new Bouton((this->m_xg+this->m_xd)/2+(((this->m_yh-this->m_yb)/3-0.1)/2+0.1),this->m_yh-(this->m_yh-this->m_yb)/6+0.1,(this->m_yh-this->m_yb)/3-0.1,(this->m_yh-this->m_yb)/3-0.1,"img/unites/archer2.png");
			this->tabBoutons[2] = new Bouton((this->m_xg+this->m_xd)/2-(((this->m_yh-this->m_yb)/3-0.1)/2+0.1),this->m_yh-(this->m_yh-this->m_yb)/2+0.1,(this->m_yh-this->m_yb)/3-0.1,(this->m_yh-this->m_yb)/3-0.1,"img/unites/guerrier_humain2.png");
			this->tabBoutons[3] = new Bouton((this->m_xg+this->m_xd)/2+(((this->m_yh-this->m_yb)/3-0.1)/2+0.1),this->m_yh-(this->m_yh-this->m_yb)/2+0.1,(this->m_yh-this->m_yb)/3-0.1,(this->m_yh-this->m_yb)/3-0.1,"img/unites/mage_blanc2.png");
			this->tabBoutons[4] = new Bouton((this->m_xg+this->m_xd)/2-(((this->m_yh-this->m_yb)/3-0.1)/2+0.1),this->m_yh-5*(this->m_yh-this->m_yb)/6+0.1,(this->m_yh-this->m_yb)/3-0.1,(this->m_yh-this->m_yb)/3-0.1,"img/unites/mage_noir2.png");
			this->tabBoutons[5] = new Bouton((this->m_xg+this->m_xd)/2+(((this->m_yh-this->m_yb)/3-0.1)/2+0.1),this->m_yh-5*(this->m_yh-this->m_yb)/6+0.1,(this->m_yh-this->m_yb)/3-0.1,(this->m_yh-this->m_yb)/3-0.1,"img/bouton_pas_survole.png");
			break;
		case 9 :
			this->tabBoutons[0] = new Bouton((this->m_xg+this->m_xd)/2,this->m_yb+(this->m_yh-this->m_yb)/6,(this->m_xd-this->m_xg)/2,(this->m_yh-this->m_yb)/6,"img/bouton_pas_survole.png");
			break;
		case 10 :
			this->tabBoutons[0] = new Bouton(-0.7,0.3,0.9,0.6,"img/maps/map.png");
			this->tabBoutons[1] = new Bouton(0.7,0.3,0.9,0.6,"img/maps/map_castle.jpg");
			this->tabBoutons[2] = new Bouton(1.6,-0.8,0.2,0.2,"img/return.png");
			this->tabBoutons[3] = new Bouton(-0.3,-0.7,0.3,0.1,"img/bouton_pas_survole.png");
			this->tabBoutons[4] = new Bouton(0.3,-0.7,0.3,0.1,"img/bouton_pas_survole.png");
			this->tabBoutons[5] = new Bouton(-0.3,-0.41,0.4,0.4,"img/3_unites.png");
			this->tabBoutons[6] = new Bouton(0.3,-0.41,0.4,0.4,"img/5_unites.png");
			break;
		case 11 :
			this->tabBoutons[0] = new Bouton(this->m_xg+(this->m_yh-this->m_yb-0.1)/2+0.1,this->m_yh-(this->m_yh-this->m_yb)/2,this->m_yh-this->m_yb-0.1,this->m_yh-this->m_yb-0.1,"img/unites/interrogation.png");
			break;
		case 12 :
			this->tabBoutons[0] = new Bouton(this->m_xg+(this->m_xd-this->m_xg)/6.,this->m_yh-(this->m_yh-this->m_yb)/4.,(this->m_xd-this->m_xg)/6.-0.1,(this->m_xd-this->m_xg)/6.-0.1,"img/unites/nain.png");
			this->tabBoutons[1] = new Bouton(this->m_xg+3.*(this->m_xd-this->m_xg)/6.,this->m_yh-(this->m_yh-this->m_yb)/4.,(this->m_xd-this->m_xg)/6.-0.1,(this->m_xd-this->m_xg)/6.-0.1,"img/unites/archer.png");
			this->tabBoutons[2] = new Bouton(this->m_xg+5.*(this->m_xd-this->m_xg)/6.,this->m_yh-(this->m_yh-this->m_yb)/4.,(this->m_xd-this->m_xg)/6.-0.1,(this->m_xd-this->m_xg)/6.-0.1,"img/unites/guerrier_humain.png");
			this->tabBoutons[3] = new Bouton(this->m_xg+2.*(this->m_xd-this->m_xg)/6.,this->m_yh-3.*(this->m_yh-this->m_yb)/4.,(this->m_xd-this->m_xg)/6.-0.1,(this->m_xd-this->m_xg)/6.-0.1,"img/unites/mage_blanc.png");
			this->tabBoutons[4] = new Bouton(this->m_xg+4.*(this->m_xd-this->m_xg)/6.,this->m_yh-3.*(this->m_yh-this->m_yb)/4.,(this->m_xd-this->m_xg)/6.-0.1,(this->m_xd-this->m_xg)/6.-0.1,"img/unites/mage_noir.png");
			this->tabBoutons[5] = new Bouton(this->m_xg+5.*(this->m_xd-this->m_xg)/6.,this->m_yh-3.*(this->m_yh-this->m_yb)/4.,(this->m_xd-this->m_xg)/6.-0.1,(this->m_xd-this->m_xg)/6.-0.1,"img/return.png");
			break;
		case 13 :
			this->tabBoutons[0] = new Bouton(1.6,-0.8,0.2,0.2,"img/return.png");
			break;
		case 14 :
			this->tabBoutons[0] = new Bouton((this->m_xg+this->m_xd)/2,this->m_yb+(this->m_yh-this->m_yb)/6,(this->m_xd-this->m_xg)/4,(this->m_yh-this->m_yb)/10,"img/bouton_pas_survole.png");
			break;
	}
	for(int i=0; i<this->m_nbBoutons;i++)
	{
		this->tabBoutons[i]->chargerFond();
	}
}

void Menu::dessinerBoutons()
{
	for(int i=0;i<this->m_nbBoutons;i++)
	{
		this->tabBoutons[i]->dessinerBouton();
	}
}

void Menu::quelBoutonMenu(float x, float y, int* loop, bool* contreIA)
{
	switch(m_id)
	{
		case 1 :
			if(this->tabBoutons[0]->cliqueBouton(x,y))
			{
				*loop=2;
				*contreIA=false;
			}
			else if(this->tabBoutons[1]->cliqueBouton(x,y))
			{
				*loop=2;
				*contreIA=true;
			}
			else if(this->tabBoutons[2]->cliqueBouton(x,y))
			{
				*loop=3;
			}
			else if(this->tabBoutons[3]->cliqueBouton(x,y))
			{
				*loop=0;
			}
			else if(this->tabBoutons[4]->cliqueBouton(x,y))
			{
				*loop=4;
			}
			break;

		case 9 :
			if(this->tabBoutons[0]->cliqueBouton(x,y))
			{
				*loop=1;
			}
			else
			{
				*loop=2;
			}
			break;
	}
}

void Menu::quelBoutonMenuOptions(float x, float y, int* loop, int* id_map,int* nb_unite_depart,Textures** textes)
{
	if(this->tabBoutons[0]->cliqueBouton(x,y))
	{
		*id_map=1;
	}
	else if(this->tabBoutons[1]->cliqueBouton(x,y))
	{
		*id_map=2;
	}
	else if(this->tabBoutons[3]->cliqueBouton(x,y))
	{
		textes[35]->libererTexte();
		textes[36]->libererTexte();
		textes[35]->chargeTexte("3",100,255,0,0);
		textes[36]->chargeTexte("5",100,0,0,0);
		*nb_unite_depart=3;
	}
	else if(this->tabBoutons[4]->cliqueBouton(x,y))
	{
		textes[35]->libererTexte();
		textes[36]->libererTexte();
		textes[35]->chargeTexte("3",100,0,0,0);
		textes[36]->chargeTexte("5",100,255,0,0);
		*nb_unite_depart=5;
	}
	else if(this->tabBoutons[2]->cliqueBouton(x,y))
	{
		*loop=1;
	}
	else
	{
		*loop=3;
	}
}

void Menu::quelBoutonMenuRegles(float x, float y, int* loop)
{
	if(this->tabBoutons[0]->cliqueBouton(x,y))
	{
		*loop=1;
	}
	else
	{
		*loop=4;
	}
}

void Menu::quelBoutonMenuJeu(float x, float y, Joueur** joueur, Unite** nouvelleUnite, int nb_unite_depart, int* loop, Tour* tour, bool* placement, Textures** textes)
{
	if(this->tabBoutons[0]->cliqueBouton(x,y))
	{
		*placement=true;
		*nouvelleUnite = (*joueur)->creationUnite('t');
	}
	else if(this->tabBoutons[1]->cliqueBouton(x,y))
	{
		*placement=true;
		*nouvelleUnite = (*joueur)->creationUnite('a');
	}
	else if(this->tabBoutons[2]->cliqueBouton(x,y))
	{
		*placement=true;
		*nouvelleUnite = (*joueur)->creationUnite('g');
	}
	else if(this->tabBoutons[3]->cliqueBouton(x,y))
	{
		*placement=true;
		*nouvelleUnite = (*joueur)->creationUnite('b');
	}
	else if(this->tabBoutons[4]->cliqueBouton(x,y))
	{
		*placement=true;
		*nouvelleUnite = (*joueur)->creationUnite('n');
	}
	else if(this->tabBoutons[5]->cliqueBouton(x,y))
	{
		*loop=1;
	}
	else
	{
		*loop=2;
	}
}

void Menu::quelBoutonJeu(float x, float y, int* cxs, int* cys, int* cxd, int* cyd, int* cxa,int* cya,
							Map* carte, Joueur** joueur, Unite** uniteActuelle, Unite** uniteEnnemie,
							Tour* tour, int* idNouveauMenu, Actions* action, Textures** textes, Menu** menuUnite, Quefeje* quefeje)
{
	float px=x+RATIO*GL_VIEW_SIZE/2.;
	float py=-(y-GL_VIEW_SIZE/2.);
	px=px/((2./3.)*RATIO*GL_VIEW_SIZE);
	py=py/((4./9.)*GL_VIEW_SIZE*RATIO);

	int cx;
	int cy;

	if(px<0 || px>1 || py<0 || py>1)
	{
		cx=-1;
		cy=-1;
	}
	else
	{
		cx=carte->getXCase(px);
		cy=carte->getYCase(py);
	}

	switch(this->m_id)
	{
		case 2 :
			if(this->tabBoutons[0]->cliqueBouton(x,y))
			{
				*idNouveauMenu=3;
			}
			else if(this->tabBoutons[1]->cliqueBouton(x,y))
			{
				*idNouveauMenu=8;
			}
			else if(this->tabBoutons[2]->cliqueBouton(x,y))
			{
				if(*tour==tourj1)
				{
					*tour=tourj2;
				}
				else
				{
					*tour=tourj1;
				}
				(*joueur)->finTour();
				*idNouveauMenu=2;
			}
			else
			{
				if(cx>=0 && cy>=0)
				{
					if(carte->caseSelectionnee(cx,cy)->occupee())
					{
						const char* iconeUnite = carte->caseSelectionnee(cx,cy)->selectUnite()->afficherUnite(&textes[23],&textes[32],&textes[28],&textes[29],&textes[30],&textes[31]);
						(*menuUnite)->tabBoutons[0]->modifierIcone(iconeUnite);
					}
				}
				*idNouveauMenu=2;
			}
			break;
		case 3 :
			if(this->tabBoutons[0]->cliqueBouton(x,y))
			{
				*action = DEPLACER;
				*quefeje = VASELECTIONNER;
				*idNouveauMenu=4;
			}
			else if(this->tabBoutons[1]->cliqueBouton(x,y))
			{
				*action = ATTAQUER;
				*quefeje = VASELECTIONNER;
				*idNouveauMenu=4;
			}
			else if(this->tabBoutons[2]->cliqueBouton(x,y))
			{
				if(*tour==tourj1)
				{
					*tour=tourj2;
				}
				else
				{
					*tour=tourj1;
				}
				(*joueur)->finTour();
				*idNouveauMenu=2;
			}
			else
			{
				if(cx>=0 && cy>=0)
				{
					if(carte->caseSelectionnee(cx,cy)->occupee())
					{
						const char* iconeUnite = carte->caseSelectionnee(cx,cy)->selectUnite()->afficherUnite(&textes[23],&textes[32],&textes[28],&textes[29],&textes[30],&textes[31]);
						(*menuUnite)->tabBoutons[0]->modifierIcone(iconeUnite);
					}
				}
				*idNouveauMenu=3;
			}
			break;
		case 4 :
			if(*action == DEPLACER)
			{
				if(this->tabBoutons[0]->cliqueBouton(x,y))
				{
					*quefeje=VASELECTIONNER;
					textes[15]->libererTexte();
	                textes[16]->libererTexte();
	                // textes[15]->chargeTexte("Selectionnez une",100,255,255,255);
	                // textes[16]->chargeTexte("unite a deplacer",100,255,255,255);
	                textes[15]->chargeTexte("Selectionnez",100,255,255,255);
	                textes[16]->chargeTexte("une unite",100,255,255,255);
					*idNouveauMenu=3;
				}
				else
				{
					if(selection(cx,cy,cxs,cys,this->m_id,5,idNouveauMenu,carte,joueur,uniteActuelle,&textes[15],&textes[16]))
					{
						*quefeje=VASEDEPLACER;
						const char* iconeUnite = (*uniteActuelle)->afficherUnite(&textes[23],&textes[32],&textes[28],&textes[29],&textes[30],&textes[31]);
						(*menuUnite)->tabBoutons[0]->modifierIcone(iconeUnite);
						textes[15]->libererTexte();
		                textes[16]->libererTexte();
		                // textes[15]->chargeTexte("Selectionnez une",100,255,255,255);
		                // textes[16]->chargeTexte("unite a deplacer",100,255,255,255);
		                textes[15]->chargeTexte("Selectionnez",100,255,255,255);
		                textes[16]->chargeTexte("une unite",100,255,255,255);
					}
				}
			}
			else
			{
				if(this->tabBoutons[0]->cliqueBouton(x,y))
				{
					*quefeje=VASELECTIONNER;
					textes[15]->libererTexte();
	                textes[16]->libererTexte();
	                // textes[15]->chargeTexte("Selectionnez une",100,255,255,255);
	                // textes[16]->chargeTexte("unite a deplacer",100,255,255,255);
	                textes[15]->chargeTexte("Selectionnez",100,255,255,255);
	                textes[16]->chargeTexte("une unite",100,255,255,255);
					*idNouveauMenu=3;
					// if(*tour==tourj1)
					// {
					// 	*tour=tourj2;
					// }
					// else
					// {
					// 	*tour=tourj1;
					// }
				}
				else
				{
					if(selection(cx,cy,cxs,cys,this->m_id,7,idNouveauMenu,carte,joueur,uniteActuelle,&textes[15],&textes[16]))
					{
						*quefeje=VAATTAQUER;
						const char* iconeUnite = (*uniteActuelle)->afficherUnite(&textes[23],&textes[32],&textes[28],&textes[29],&textes[30],&textes[31]);
						(*menuUnite)->tabBoutons[0]->modifierIcone(iconeUnite);
						textes[15]->libererTexte();
		                textes[16]->libererTexte();
		                // textes[15]->chargeTexte("Selectionnez une",100,255,255,255);
		                // textes[16]->chargeTexte("unite a deplacer",100,255,255,255);
		                textes[15]->chargeTexte("Selectionnez",100,255,255,255);
		                textes[16]->chargeTexte("une unite",100,255,255,255);
					}
				}
			}
			break;
		case 5 :
			if(*action == DEPLACER)
			{
				if(this->tabBoutons[0]->cliqueBouton(x,y))
				{
					*quefeje=VAATTAQUER;
					textes[17]->libererTexte();
	                textes[18]->libererTexte();
	                textes[17]->chargeTexte("Ou voulez-vous",100,255,255,255);
	                textes[18]->chargeTexte("deplacer cette unite ?",100,255,255,255);
					*idNouveauMenu=7;
				}
				// else if(this->tabBoutons[1]->cliqueBouton(x,y))
				// {
				// 	textes[17]->libererTexte();
	   //              textes[18]->libererTexte();
	   //              textes[17]->chargeTexte("Ou voulez-vous",100,255,255,255);
	   //              textes[18]->chargeTexte("deplacer cette unite ?",100,255,255,255);
				// 	*idNouveauMenu=4;
				// }
				else
				{
					if(deplacement(cx,cy,*cxs,*cys,cxd,cyd,this->m_id,7,idNouveauMenu,carte,uniteActuelle,&textes[17],&textes[18]))
					{
						*quefeje=VAATTAQUER;
						textes[17]->libererTexte();
		                textes[18]->libererTexte();
		                textes[17]->chargeTexte("Ou voulez-vous",100,255,255,255);
		                textes[18]->chargeTexte("deplacer cette unite ?",100,255,255,255);
					}
				}
			}
			else
			{
				if(this->tabBoutons[0]->cliqueBouton(x,y))
				{
					*quefeje=VASELECTIONNER;
					textes[17]->libererTexte();
	                textes[18]->libererTexte();
	                textes[17]->chargeTexte("Ou voulez-vous",100,255,255,255);
	                textes[18]->chargeTexte("deplacer cette unite ?",100,255,255,255);
					// if(*tour==tourj1)
					// {
					// 	*tour=tourj2;
					// }
					// else
					// {
					// 	*tour=tourj1;
					// }
					// *idNouveauMenu=2;
					(*uniteActuelle)->utiliser();
					*idNouveauMenu=3;
				}
				// else if(this->tabBoutons[1]->cliqueBouton(x,y))
				// {
				// 	textes[17]->libererTexte();
	   //              textes[18]->libererTexte();
	   //              textes[17]->chargeTexte("Ou voulez-vous",100,255,255,255);
	   //              textes[18]->chargeTexte("deplacer cette unite ?",100,255,255,255);
				// 	*idNouveauMenu=4;
				// }
				else
				{
					if(deplacement(cx,cy,*cxs,*cys,cxd,cyd,this->m_id,3,idNouveauMenu,carte,uniteActuelle,&textes[17],&textes[18]))
					{
						*quefeje=VASELECTIONNER;
						textes[17]->libererTexte();
		                textes[18]->libererTexte();
		                textes[17]->chargeTexte("Ou voulez-vous",100,255,255,255);
		                textes[18]->chargeTexte("deplacer cette unite ?",100,255,255,255);
						// if(*tour==tourj1)
						// {
						// 	*tour=tourj2;
						// }
						// else
						// {
						// 	*tour=tourj1;
						// }
						(*uniteActuelle)->utiliser();
					}
				}
			}
			break;
		// case 6 :
		// 	// if(*action == ATTAQUER)
		// 	// {
		// 		if(this->tabBoutons[0]->cliqueBouton(x,y))
		// 		{
		// 			textes[19]->libererTexte();
	 //                textes[20]->libererTexte();
	 //                textes[19]->chargeTexte("Selectionnez une",100,255,255,255);
	 //                textes[20]->chargeTexte("unite attaquante",100,255,255,255);
		// 			*idNouveauMenu=4;
		// 		}
		// 		else
		// 		{
		// 			if(selection(cx,cy,cxs,cys,this->m_id,7,idNouveauMenu,carte,joueur,uniteActuelle,&textes[19],&textes[20]))
		// 			{
		// 				const char* iconeUnite = (*uniteActuelle)->afficherUnite(&textes[23],&textes[32],&textes[28],&textes[29],&textes[30],&textes[31]);
		// 				(*menuUnite)->tabBoutons[0]->modifierIcone(iconeUnite);
		// 				textes[19]->libererTexte();
		//                 textes[20]->libererTexte();
		//                 textes[19]->chargeTexte("Selectionnez une",100,255,255,255);
		//                 textes[20]->chargeTexte("unite attaquante",100,255,255,255);
		// 			}
		// 		}
		// 	// }
		// 	// else
		// 	// {
		// 	// 	if(this->tabBoutons[0]->cliqueBouton(x,y))
		// 	// 	{
		// 	// 		textes[19]->libererTexte();
	 //  //               textes[20]->libererTexte();
	 //  //               textes[19]->chargeTexte("Selectionnez une",100,255,255,255);
	 //  //               textes[20]->chargeTexte("unite attaquante",100,255,255,255);
		// 	// 		if(*tour==tourj1)
		// 	// 		{
		// 	// 			*tour=tourj2;
		// 	// 		}
		// 	// 		else
		// 	// 		{
		// 	// 			*tour=tourj1;
		// 	// 		}
		// 	// 		*idNouveauMenu=2;
		// 	// 	}
		// 	// 	else
		// 	// 	{
		// 	// 		if(selection(cx,cy,cxsa,cysa,this->m_id,7,idNouveauMenu,carte,joueur,uniteActuelle,&textes[19],&textes[20]))
		// 	// 		{
		// 	// 			const char* iconeUnite = (*uniteActuelle)->afficherUnite(&textes[23],&textes[32],&textes[28],&textes[29],&textes[30],&textes[31]);
		// 	// 			(*menuUnite)->tabBoutons[0]->modifierIcone(iconeUnite);
		// 	// 			textes[19]->libererTexte();
		//  //                textes[20]->libererTexte();
		//  //                textes[19]->chargeTexte("Selectionnez une",100,255,255,255);
		//  //                textes[20]->chargeTexte("unite attaquante",100,255,255,255);
		// 	// 		}
		// 	// 	}
		// 	// }
		// 	break;
		case 7 :
			if(*action == ATTAQUER)
			{
				if(this->tabBoutons[0]->cliqueBouton(x,y))
				{
					*quefeje=VASEDEPLACER;
					textes[21]->libererTexte();
	                textes[22]->libererTexte();
	                textes[21]->chargeTexte("Selectionnez une",100,255,255,255);
	                textes[22]->chargeTexte("unite a attaquer",100,255,255,255);
					*idNouveauMenu=5;
				}
				// else if(this->tabBoutons[1]->cliqueBouton(x,y))
				// {
				// 	textes[21]->libererTexte();
	   //              textes[22]->libererTexte();
	   //              textes[21]->chargeTexte("Selectionnez une",100,255,255,255);
	   //              textes[22]->chargeTexte("unite a attaquer",100,255,255,255);
				// 	*idNouveauMenu=6;
				// }
				else
				{
					if(attaque(cx,cy,cxa,cya,this->m_id,5,idNouveauMenu,joueur,uniteActuelle,uniteEnnemie,carte,&textes[21],&textes[22],quefeje))
					{
						if((*uniteActuelle)->estMorte())
						{
							*quefeje=VASELECTIONNER;
						}
						else
						{
                        	*quefeje=VASEDEPLACER;
						}
						textes[21]->libererTexte();
		                textes[22]->libererTexte();
		                textes[21]->chargeTexte("Selectionnez une",100,255,255,255);
		                textes[22]->chargeTexte("unite a attaquer",100,255,255,255);
					}
				}
			}
			else
			{			this->tabBoutons[4] = new Bouton(1.6,-0.8,0.2,0.2,"img/regles.png");
				if(this->tabBoutons[0]->cliqueBouton(x,y))
				{
					*quefeje=VASELECTIONNER;
					textes[21]->libererTexte();
	                textes[22]->libererTexte();
	                textes[21]->chargeTexte("Selectionnez une",100,255,255,255);
	                textes[22]->chargeTexte("unite a attaquer",100,255,255,255);
					// if(*tour==tourj1)
					// {
					// 	*tour=tourj2;
					// }
					// else
					// {
					// 	*tour=tourj1;
					// }
					// *idNouveauMenu=2;
					*idNouveauMenu=3;
					(*uniteActuelle)->utiliser();
				}
				// else if(this->tabBoutons[1]->cliqueBouton(x,y))
				// {
				// 	textes[21]->libererTexte();
	   //              textes[22]->libererTexte();
	   //              textes[21]->chargeTexte("Selectionnez une",100,255,255,255);
	   //              textes[22]->chargeTexte("unite a attaquer",100,255,255,255);
				// 	*idNouveauMenu=6;
				// }
				else
				{
					if(attaque(cx,cy,cxa,cya,this->m_id,3,idNouveauMenu,joueur,uniteActuelle,uniteEnnemie,carte,&textes[21],&textes[22],quefeje))
					{
						*quefeje=VASELECTIONNER;
						textes[21]->libererTexte();
			            textes[22]->libererTexte();
			            textes[21]->chargeTexte("Selectionnez une",100,255,255,255);
			            textes[22]->chargeTexte("unite a attaquer",100,255,255,255);
						// if(*tour==tourj1)
						// {
						// 	*tour=tourj2;
						// }
						// else
						// {
						// 	*tour=tourj1;
						// }
						(*uniteActuelle)->utiliser();
					}
				}
			}
			break;
		case 8 : ////////////////////////////////////////////////////////DANS CE CAS, LE PROGRAMME AGIS COMME SI LES BOUTONS DU DEUX ETAIENT ENCORE LA.
			if(this->tabBoutons[0]->cliqueBouton(x,y))
			{
				if((*joueur)->achatUnite('t',200))
				{
					(*uniteActuelle) = (*joueur)->creationUnite('t');
	    			//carte->occuperCase(0,0,nouvelleUnite);
					(*uniteActuelle)->chargerIcone();
					*quefeje=ENACHAT;
					// if(*tour==tourj1)
					// {
					// 	*tour=tourj2;
					// 	(*joueur)->argentFinDeTour();
					// }
					// else
					// {
					// 	*tour=tourj1;
					// 	(*joueur)->argentFinDeTour();
					// }
					*idNouveauMenu=2;
				}
				else
				{
					*idNouveauMenu=8;
				}
			}
			else if(this->tabBoutons[1]->cliqueBouton(x,y))
			{
				if((*joueur)->achatUnite('a',230))
				{
					(*uniteActuelle) = (*joueur)->creationUnite('a');
	    			// carte->occuperCase(0,0,nouvelleUnite);
					(*uniteActuelle)->chargerIcone();
					*quefeje=ENACHAT;
					// if(*tour==tourj1)
					// {
					// 	*tour=tourj2;
					// 	(*joueur)->argentFinDeTour();
					// }
					// else
					// {
					// 	*tour=tourj1;
					// 	(*joueur)->argentFinDeTour();
					// }
					*idNouveauMenu=2;
				}
				else
				{
					*idNouveauMenu=8;
				}
			}
			else if(this->tabBoutons[2]->cliqueBouton(x,y))
			{
				if((*joueur)->achatUnite('g',200))
				{
					(*uniteActuelle) = (*joueur)->creationUnite('g');
	    			// carte->occuperCase(0,0,nouvelleUnite);
					(*uniteActuelle)->chargerIcone();
					*quefeje=ENACHAT;
					// if(*tour==tourj1)
					// {
					// 	*tour=tourj2;
					// 	(*joueur)->argentFinDeTour();
					// }
					// else
					// {
					// 	*tour=tourj1;
					// 	(*joueur)->argentFinDeTour();
					// }
					*idNouveauMenu=2;
				}
				else
				{
					*idNouveauMenu=8;
				}
			}
			else if(this->tabBoutons[3]->cliqueBouton(x,y))
			{
				if((*joueur)->achatUnite('b',300))
				{
					(*uniteActuelle) = (*joueur)->creationUnite('b');
	    			// carte->occuperCase(0,0,nouvelleUnite);
					(*uniteActuelle)->chargerIcone();
					*quefeje=ENACHAT;
					// if(*tour==tourj1)
					// {
					// 	*tour=tourj2;
					// 	(*joueur)->argentFinDeTour();
					// }
					// else
					// {
					// 	*tour=tourj1;
					// 	(*joueur)->argentFinDeTour();
					// }
					*idNouveauMenu=2;
				}
				else
				{
					*idNouveauMenu=8;
				}
			}
			else if(this->tabBoutons[4]->cliqueBouton(x,y))
			{
				if((*joueur)->achatUnite('n',300))
				{
					(*uniteActuelle) = (*joueur)->creationUnite('n');
	    			// carte->occuperCase(0,0,nouvelleUnite);
					(*uniteActuelle)->chargerIcone();
					*quefeje=ENACHAT;
					// if(*tour==tourj1)
					// {
					// 	*tour=tourj2;
					// 	(*joueur)->argentFinDeTour();
					// }
					// else
					// {
					// 	*tour=tourj1;
					// 	(*joueur)->argentFinDeTour();
					// }
					*idNouveauMenu=2;
				}
				else
				{
					*idNouveauMenu=8;
				}
			}
			else if(this->tabBoutons[5]->cliqueBouton(x,y))
			{
				*idNouveauMenu=2;
			}
			else
			{
				if(cx>=0 && cy>=0)
				{
					if(carte->caseSelectionnee(cx,cy)->occupee())
					{
						const char* iconeUnite = carte->caseSelectionnee(cx,cy)->selectUnite()->afficherUnite(&textes[23],&textes[32],&textes[28],&textes[29],&textes[30],&textes[31]);
						(*menuUnite)->tabBoutons[0]->modifierIcone(iconeUnite);
					}
				}
				*idNouveauMenu=8;
			}
			break;
		case 11 :
			break;
	}
}

void Menu::quelBoutonMenuFin(float x, float y, int* loop, bool* contreIA)
{
	switch(m_id)
	{
		case 14 :
			if(this->tabBoutons[0]->cliqueBouton(x,y))
			{
				*loop=1;
			}
			break;

	}
}

float Menu::boutonGetX(int indice)
{
	return tabBoutons[indice]->getX();
}

float Menu::boutonGetY(int indice)
{
	return tabBoutons[indice]->getY();
}

int Menu::getIdMenu()
{
	return this->m_id;
}
