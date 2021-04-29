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

Unite::Unite(){
	m_id=0;
	m_existe = 0;
	m_r=0;
	m_v=0;
	m_b=0;
	m_j=-1;
	m_i=-1;
	m_pv=0;
	m_force=0;
	m_defense=0;
	m_portee=0;
	m_mobilite=0;
	m_cout=0;
	m_icone="img/IMAGE_NULLE.png"; //Référence du fichier de l'icone de l'unite
	m_type='\0';
	m_typeMouvement='\0';
	m_efficacite='\0';
	m_utilisee=true;
	this->chargerIcone();
}

Unite::Unite(int id, char type)
{
	switch(type)
	{
		case 'g' : //////////////////////////////////Création du guerrier
			m_force=0.6;
			m_defense=1.6;
			m_portee=2;
			m_mobilite=3;
			m_cout=100;
			m_icone="img/unites/guerrier_humain.png"; //Référence du fichier de l'icone de l'unite
			m_typeMouvement='p';
			m_efficacite='v';
			break;
		case 'a' : //////////////////////////////Création de l'archer
			m_force=0.4;
			m_defense=1.;
			m_portee=6;
			m_mobilite=2;
			m_cout=120;
			m_icone="img/unites/archer.png"; //Référence du fichier de l'icone de l'unite
			m_typeMouvement='p';
			m_efficacite='g';
			break;
		case 't' : //////////////////////////////////Création du tank
			m_force=0.3;
			m_defense=2.2;
			m_portee=1;
			m_mobilite=2;
			m_cout=200;
			m_icone="img/unites/nain.png"; //Référence du fichier de l'icone de l'unite
			m_typeMouvement='p';
			m_efficacite='a';
			break;
		case 'n' : //////////////////////////Création de Superman
			m_force=0.5;
			m_defense=1.3;
			m_portee=4;
			m_mobilite=4;
			m_cout=200;
			m_icone="img/unites/mage_noir.png"; //Référence du fichier de l'icone de l'unite
			m_typeMouvement='v';
			m_efficacite='b';
			break;
		case 'b' : //////////////////////////Création de Superman
			m_force=0.5;
			m_defense=1.3;
			m_portee=4;
			m_mobilite=4;
			m_cout=200;
			m_icone="img/unites/mage_blanc.png"; //Référence du fichier de l'icone de l'unite
			m_typeMouvement='v';
			m_efficacite='n';
			break;
	}
	m_id=id;
	m_existe=1;
	m_r=0;
	m_v=0;
	m_b=255;
	m_pv=100;
	m_j=0;
	m_i=0;
	m_type=type;
	m_utilisee=false;
}

void Unite::chargerIcone(){
	this->m_tex = new Textures(IMG_Load(this->m_icone), &(this->m_idTexture));
}

void Unite::libererEspace(){
	this->m_tex->libererEspace(&(this->m_idTexture));
}

void Unite::dessinerUnite(float x,float y,float tailleCase){
	dessinerImage(this->m_idTexture,x+tailleCase/10,x+9*tailleCase/10,y-tailleCase/10,y-9*tailleCase/10);
}

void Unite::deplacer(int j, int i)
{
	this->m_j=j;
	this->m_i=i;
}


bool Unite::verifDistance(int prec_x,int prec_y,int nouv_x,int nouv_y)
{
	int diff_x=abs(nouv_x-prec_x);
	int diff_y=abs(nouv_y-prec_y);
	int mob_nec=diff_x+diff_y;
	if(mob_nec>this->m_mobilite)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool Unite::verifPortee(int son_x,int son_y)
{
	int diff_x=abs(son_x-this->m_j);
	int diff_y=abs(son_y-this->m_i);
	int portee_nec=diff_x+diff_y;
	if(portee_nec>this->m_portee)
	{
		return false;
	}
	else
	{
		return true;
	}
}

void Unite::attaquer(Unite* ennemi)
{
	ennemi->seFaitAttaquer(this, this->m_pv,this->m_force,false);
	//printf("Vie attaquant : %d \n",this->m_pv);
}

void Unite::seFaitAttaquer(Unite* ennemi,int pv_ennemi,float force_ennemie,bool finAttaque)
{
	this->m_pv-=(int) (pv_ennemi*force_ennemie/this->m_defense);
	if(!this->estMorte())
	{
		if(!finAttaque)
		{
			ennemi->seFaitAttaquer(this,this->m_pv,this->m_force,true);
		}
	}
}

bool Unite::estMorte()
{
	if(this->m_pv>0)
	{
		return false;
	}
	else{
		return true;
	}
}

const char* Unite::afficherUnite(Textures** type, Textures** j, Textures** pv, Textures** force, Textures** portee, Textures** mob)
{
	(*type)->libererTexte();
	switch(this->m_type)
	{
		case 'g' :
			(*type)->chargeTexte("GUERRIER",100,255,255,255);
			break;
		case 'a' :
			(*type)->chargeTexte("ARCHER",100,255,255,255);
			break;
		case 't' :
			(*type)->chargeTexte("NAIN",100,255,255,255);
			break;
		case 'n' :
			(*type)->chargeTexte("MAGE NOIR",100,255,255,255);
			break;
		case 'b' :
			(*type)->chargeTexte("MAGE BLANC",100,255,255,255);
			break;
		default :
			break;
	}

	switch(this->m_id)
	{
		case 1 :
			(*j)->chargeTexte("J1",100,0,0,255);
			break;
		case 2 :
			(*j)->chargeTexte("J2",100,255,0,0);
			break;
		case 3 :
			(*j)->chargeTexte("ORDI",100,255,0,0);
			break;
		default :
			break;
	}

	(*pv)->libererTexte();
    char charpv[16];
    sprintf(charpv,"%d",this->m_pv);
    (*pv)->chargeTexte(charpv,100,255,255,255);

    (*force)->libererTexte();
    char charforce[16];
    sprintf(charforce,"%d",(int)(74*this->m_force));
    (*force)->chargeTexte(charforce,100,255,255,255);

    (*portee)->libererTexte();
    char charportee[16];
    sprintf(charportee,"%d",this->m_portee);
    (*portee)->chargeTexte(charportee,100,255,255,255);

	(*mob)->libererTexte();
    char charmob[16];
    sprintf(charmob,"%d",this->m_mobilite);
    (*mob)->chargeTexte(charmob,100,255,255,255);

	return(this->m_icone);
}

int Unite::getMobilite()
{
	return this->m_mobilite;
}

int Unite::getPortee()
{
	return this->m_portee;
}

bool Unite::utilisee()
{
	return this->m_utilisee;
}

void Unite::utiliser()
{
	this->m_utilisee=true;
}

void Unite::desutiliser()
{
	this->m_utilisee=false;
}

void Unite::mourir()
{
	this->libererEspace();
	this->m_id=0;
	this->m_existe = 0;
	this->m_r=0;
	this->m_v=0;
	this->m_b=0;
	this->m_j=-1;
	this->m_i=-1;
	this->m_pv=0;
	this->m_force=0;
	this->m_portee=0;
	this->m_mobilite=0;
	this->m_cout=0;
	this->m_icone="img/IMAGE_NULLE.png"; //Référence du fichier de l'icone de l'unite
	this->m_type='\0';
	this->m_typeMouvement='\0';
	this->m_efficacite='\0';
	this->chargerIcone();
}

int Unite::getId()
{
	return this->m_id;
}

int Unite::getX()
{
	return this->m_j;
}

int Unite::getY()
{
	return this->m_i;
}

int Unite::getExiste()
{
	return m_existe;
}

char Unite::getType()
{
	return this->m_type;
}

void Unite::afficherConsole()
{
	if(this->m_utilisee)
	{
		printf("U-Type : %c \t pv : %d \t CoorX : %d \t CoorY : %d \n",this->m_type,this->m_pv,this->m_j,this->m_i);
	}
	else
	{
		printf("NU-Type : %c \t pv : %d \t CoorX : %d \t CoorY : %d \n",this->m_type,this->m_pv,this->m_j,this->m_i);
	}

}
