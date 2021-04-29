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

Noeud::Noeud()
{
	lacase=new Case();
	distance=0;
	gauche=NULL;
	droite=NULL;
	parent=NULL;
}

Noeud::Noeud(Case* caseNoeud, float dist)
{
	lacase=caseNoeud;
	distance=dist;
	gauche=NULL;
	droite=NULL;
	parent=NULL;
}

void Noeud::inserer(Noeud* aInserer)
{
	Noeud* current = this;
	while(!(current->droite==NULL && current->gauche==NULL))
	{
		if(aInserer->distance<current->distance)
		{
			if(current->gauche==NULL)
			{
				if(current->lacase->getId()!=aInserer->lacase->getId())
				{
					current->gauche=aInserer;
					current->gauche->parent=current;
				}
				current->getRacine()->reequilibrer();
				return;
			}
			else
			{
				current=current->gauche;
			}
		}
		else
		{
			if(current->droite==NULL)
			{
				if(current->lacase->getId()!=aInserer->lacase->getId())
				{
					current->droite=aInserer;
					current->droite->parent=current;
				}
				current->getRacine()->reequilibrer();
				return;
			}
			else
			{
				current=current->droite;
			}
		}
	}
	if(aInserer->distance<current->distance)
	{
		if(current->lacase->getId()!=aInserer->lacase->getId())
		{
			current->gauche=aInserer;
			current->gauche->parent=current;
		}
		current->getRacine()->reequilibrer();
		return;
	}
	else
	{
		if(current->lacase->getId()!=aInserer->lacase->getId())
		{
			current->droite=aInserer;
			current->droite->parent=current;
		}
		current->getRacine()->reequilibrer();
		return;
	}
}

int Noeud::hauteur()
{
	if(this->gauche==NULL && this->droite==NULL)
	{
		return 1;
	}
	else
	{
		int hgauche;
		int hdroite;
		if(this->gauche==NULL)
		{
			hgauche=1;
		}
		else
		{
			hgauche=this->gauche->hauteur()+1;
		}
		if(this->droite==NULL)
		{
			hdroite=1;
		}
		else
		{
			hdroite=this->droite->hauteur()+1;
		}
		if(hgauche>hdroite)
		{
			return hgauche;
		}
		else
		{
			return hdroite;
		}
	}
}

bool Noeud::estSeul()
{
	return (this->droite==NULL && this->gauche==NULL);
}

Noeud* Noeud::plusPetiteDist()
{
	Noeud* current=this;
	while(current->gauche!=NULL)
	{
		current=current->gauche;
	}
	return current;
}

Case* Noeud::caseDuNoeud()
{
	return this->lacase;
}

void Noeud::detruire()
{
	if(this->droite==NULL)
	{
		this->parent->detruireFils(this->distance);
	}
	else
	{
		if(this->parent->distance>this->distance)
		{
			this->parent->gauche=this->droite;
			this->droite->parent=this->parent;
		}
		else
		{
			this->parent->droite=this->droite;
			this->droite->parent=this->parent;
		}
		
	}
	//this->getRacine()->reequilibrer();
}

void Noeud::detruireFils(float dist)
{
	if(dist<this->distance)
	{
		this->gauche=NULL;
	}
	else
	{
		this->droite=NULL;
	}
}

Noeud* Noeud::getRacine()
{
	Noeud* current=this;
	while(current->parent!=NULL)
	{
		current=current->parent;
	}
	return current;
}

void Noeud::rotationDroite()
{
	if(this->gauche->droite!=NULL)
	{
		this->gauche->droite->parent=this;
		Noeud* aDeplacer=this->gauche->droite;
		if(this->parent==NULL)
		{
			this->gauche->parent=NULL;
		}
		else
		{
			this->gauche->parent=this->parent;
			if(this->distance>this->parent->distance)
			{
				this->parent->droite=this->gauche;
			}
			else
			{
				this->parent->gauche=this->gauche;
			}
		}
		this->parent=this->gauche;
		this->gauche->droite=this;
		this->gauche=aDeplacer;
	}
	else
	{
		if(this->parent==NULL)
		{
			this->gauche->parent=NULL;
		}
		else
		{
			this->gauche->parent=this->parent;
			if(this->distance>this->parent->distance)
			{
				this->parent->droite=this->gauche;
			}
			else
			{
				this->parent->gauche=this->gauche;
			}
		}
		this->parent=this->gauche;
		this->gauche->droite=this;
		this->gauche=NULL;
	}
}

void Noeud::rotationGauche()
{
	if(this->droite->gauche!=NULL)
	{
		this->droite->gauche->parent=this;
		Noeud* aDeplacer=this->droite->gauche;
		if(this->parent==NULL)
		{
			this->droite->parent=NULL;
		}
		else
		{
			this->droite->parent=this->parent;
			if(this->distance>this->parent->distance)
			{
				this->parent->droite=this->droite;
			}
			else
			{
				this->parent->gauche=this->droite;
			}
		}
		this->parent=this->droite;
		this->droite->gauche=this;
		this->droite=aDeplacer;
	}
	else
	{
		if(this->parent==NULL)
		{
			this->droite->parent=NULL;
		}
		else
		{
			this->droite->parent=this->parent;
			if(this->distance>this->parent->distance)
			{
				this->parent->droite=this->droite;
			}
			else
			{
				this->parent->gauche=this->droite;
			}
		}
		this->parent=this->droite;
		this->droite->gauche=this;
		this->droite=NULL;
	}
}

void Noeud::rotationGaucheDroite()
{
	this->gauche->rotationGauche();
	this->rotationDroite();
}

void Noeud::rotationDroiteGauche()
{
	this->droite->rotationDroite();
	this->rotationGauche();
}

void Noeud::reequilibrer()
{
	Noeud* current=this;
	int hd=0;
	int hg=0;
	if(current->droite!=NULL)
	{
		hd=current->droite->hauteur();
	}
	if(current->gauche!=NULL)
	{
		hg=current->gauche->hauteur();
	}
	int equ=hd-hg;
	if(equ==1)
	{
		current->rotationGauche();
	}
	if(equ<-1 || equ>1)
	{
		while(equ<-1 || equ>1)
		{
			if(equ<-1)
			{
				current=current->gauche; //Si l'équilibre est négatif il y a forcément quelque chose à gauche
			}
			else if(equ>1)
			{
				current=current->droite; //Si l'équilibre est positif il y a forcément quelque chose à droite
			}
			hd=0;
			hg=0;
			if(current->droite!=NULL)
			{
				hd=current->droite->hauteur();
			}
			if(current->gauche!=NULL)
			{
				hg=current->gauche->hauteur();
			}
			equ=hd-hg;
		}
		current=current->parent; //On remonte d'un cran pour accéder au noeud le plus bas encore déséquilibré
		hd=0;
		hg=0;
		if(current->droite!=NULL)
		{
			hd=current->droite->hauteur();
		}
		if (current->gauche!=NULL)
		{
			hg=current->gauche->hauteur();
		}
		int equ=hd-hg;
		if(equ<-1)
		{
			int hgd=0;
			int hgg=0;
			if(current->gauche->droite!=NULL)
			{
				hgd=current->gauche->droite->hauteur();
			}
			if(current->gauche->gauche!=NULL)
			{
				hgg=current->gauche->gauche->hauteur();
			}
			int equg=hgd-hgg;
			if(equg<0)
			{
				current->rotationDroite();
			}
			else if(equg>0)
			{
				current->rotationGaucheDroite();
			}
		}
		else if(equ>1)
		{
			int hdd=0;
			int hdg=0;
			if(current->droite->droite!=NULL)
			{
				hdd=current->droite->droite->hauteur();
			}
			if(current->droite->gauche!=NULL)
			{
				hdg=current->droite->gauche->hauteur();
			}
			int equd=hdd-hdg;
			if(equd<0)
			{
				current->rotationDroiteGauche();
			}
			else if(equd>0)
			{
				current->rotationGauche();
			}
		}
	}
}

void Noeud::afficherConsole()
{
	printf("%f \n",this->distance);

	if(this->gauche==NULL && this->droite==NULL)
	{
		printf("pas de noeud \t pas de noeud \n");
	}
	if(this->gauche!=NULL && this->droite==NULL)
	{
		printf("%f \t pas de noeud \n",this->gauche->distance);
	}
	if(this->droite!=NULL && this->gauche==NULL)
	{
		printf("pas de noeud \t %f \n",this->droite->distance);
	}
	if(this->gauche!=NULL && this->droite!=NULL)
	{
		printf("%f \t %f \n",this->gauche->distance,this->droite->distance);
	
	


	if(this->gauche->gauche==NULL && this->gauche->droite==NULL && this->droite->gauche==NULL && this->droite->droite==NULL)
	{
		printf("pas de noeud \t pas de noeud \t pas de noeud \t pas de noeud \n");
	}
	if(this->gauche->gauche==NULL && this->gauche->droite==NULL && this->droite->gauche==NULL && this->droite->droite!=NULL)
	{
		printf("pas de noeud \t pas de noeud \t pas de noeud \t %f \n",this->droite->droite->distance);
	}
	if(this->gauche->gauche==NULL && this->gauche->droite==NULL && this->droite->gauche!=NULL && this->droite->droite==NULL)
	{
		printf("pas de noeud \t pas de noeud \t %f \t pas de noeud \n",this->droite->gauche->distance);
	}
	if(this->gauche->gauche==NULL && this->gauche->droite==NULL && this->droite->gauche!=NULL && this->droite->droite!=NULL)
	{
		printf("pas de noeud \t pas de noeud \t %f \t %f \n",this->droite->gauche->distance,this->droite->droite->distance);
	}
	if(this->gauche->gauche==NULL && this->gauche->droite!=NULL && this->droite->gauche==NULL && this->droite->droite==NULL)
	{
		printf("pas de noeud \t %f \t pas de noeud \t pas de noeud \n",this->gauche->droite->distance);
	}
	if(this->gauche->gauche==NULL && this->gauche->droite!=NULL && this->droite->gauche==NULL && this->droite->droite!=NULL)
	{
		printf("pas de noeud \t %f \t pas de noeud \t %f \n",this->gauche->droite->distance,this->droite->droite->distance);
	}
	if(this->gauche->gauche==NULL && this->gauche->droite!=NULL && this->droite->gauche!=NULL && this->droite->droite==NULL)
	{
		printf("pas de noeud \t %f \t %f \t pas de noeud \n",this->gauche->droite->distance,this->droite->gauche->distance);
	}
	if(this->gauche->gauche==NULL && this->gauche->droite!=NULL && this->droite->gauche!=NULL && this->droite->droite!=NULL)
	{
		printf("pas de noeud \t %f \t %f \t %f \n",this->gauche->droite->distance,this->droite->gauche->distance,this->droite->droite->distance);
	}
	if(this->gauche->gauche!=NULL && this->gauche->droite==NULL && this->droite->gauche==NULL && this->droite->droite==NULL)
	{
		printf("%f \t pas de noeud \t pas de noeud \t pas de noeud \n",this->gauche->gauche->distance);
	}
	if(this->gauche->gauche!=NULL && this->gauche->droite==NULL && this->droite->gauche==NULL && this->droite->droite!=NULL)
	{
		printf("%f \t pas de noeud \t pas de noeud \t %f \n",this->gauche->gauche->distance,this->droite->droite->distance);
	}
	if(this->gauche->gauche!=NULL && this->gauche->droite==NULL && this->droite->gauche!=NULL && this->droite->droite==NULL)
	{
		printf("%f \t pas de noeud \t %f \t pas de noeud \n",this->gauche->gauche->distance,this->droite->gauche->distance);
	}
	if(this->gauche->gauche!=NULL && this->gauche->droite==NULL && this->droite->gauche!=NULL && this->droite->droite!=NULL)
	{
		printf("%f \t pas de noeud \t %f \t %f \n",this->gauche->gauche->distance,this->droite->gauche->distance,this->droite->droite->distance);
	}
	if(this->gauche->gauche!=NULL && this->gauche->droite!=NULL && this->droite->gauche==NULL && this->droite->droite==NULL)
	{
		printf("%f \t %f \t pas de noeud \t pas de noeud \n",this->gauche->gauche->distance,this->gauche->droite->distance);
	}
	if(this->gauche->gauche!=NULL && this->gauche->droite!=NULL && this->droite->gauche==NULL && this->droite->droite!=NULL)
	{
		printf("%f \t %f \t pas de noeud \t %f \n",this->gauche->gauche->distance,this->gauche->droite->distance,this->droite->droite->distance);
	}
	if(this->gauche->gauche!=NULL && this->gauche->droite!=NULL && this->droite->gauche!=NULL && this->droite->droite==NULL)
	{
		printf("%f \t %f \t %f \t pas de noeud \n",this->gauche->gauche->distance,this->gauche->droite->distance,this->droite->gauche->distance);
	}
	if(this->gauche->gauche!=NULL && this->gauche->droite!=NULL && this->droite->gauche!=NULL && this->droite->droite!=NULL)
	{
		printf("%f \t %f \t %f \t %f \n",this->gauche->gauche->distance,this->gauche->droite->distance,this->droite->gauche->distance,this->droite->droite->distance);
	}
	}
	printf("\n \n");
}