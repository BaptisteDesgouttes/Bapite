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

Map::Map(int idMap)
{
	m_id=idMap;
	switch(idMap)
	{
		case 1 :
			m_largeur = 12;
			m_hauteur = 8;
			m_icone="img/maps/map.png";
			break;
		case 2 :
			m_largeur = 9;
			m_hauteur = 6;
			m_icone="img/maps/map_castle.jpg";
			break;
	}
	m_nbCases=0;
	m_tabCases = (Case**)malloc(m_largeur*m_hauteur*sizeof(Case*));
	for(int i=0;i<m_hauteur;i++)
	{
		for(int j=0;j<m_largeur;j++)
		{
			bool obs=false;
			switch(idMap)
			{
				case 1 :
					if(i*m_largeur+j==22 || i*m_largeur+j==27 || i*m_largeur+j==72 || i*m_largeur+j==79 || i*m_largeur+j==84 || i*m_largeur+j==85)
					{
						obs=true;
					}
					break;
				case 2 :
					if(i==0 || i==5)
					{
						obs=true;
					}
					if(i==4 && j==0)
					{
						obs=true;
					}
					break;
			}

			Case* lacase = new Case(obs,j,i,m_largeur);
			m_tabCases[i*m_largeur+j]=lacase;
			m_nbCases++;
		}
	}
}

void Map::chargerTexture(){
	this->m_tex = new Textures(IMG_Load(this->m_icone), &(this->m_idTexture));
}

void Map::dessinerCarte()
{
	//dessinerImage(this->m_idTexture,-1,1,1,-1);
	dessinerImage(this->m_idTexture,-RATIO*GL_VIEW_SIZE/2,-RATIO*GL_VIEW_SIZE/2+(2./3.)*RATIO*GL_VIEW_SIZE,GL_VIEW_SIZE/2,GL_VIEW_SIZE/2-(4./9.)*RATIO*GL_VIEW_SIZE);
	for(int i=0; i<this->m_hauteur;i++)
    {
        for(int j=0;j<this->m_largeur;j++)
        {
        	this->m_tabCases[i*this->m_largeur+j]->dessinerCase();
        }
    }
}

Case* Map::caseSelectionnee(int j,int i)
{
	return(m_tabCases[i*m_largeur+j]);
}

void Map::occuperCase(int j, int i, Unite* unite)
{
	if(!this->m_tabCases[j+i*this->m_largeur]->occupee())
	{
		this->m_tabCases[j+i*this->m_largeur]->occuper(unite);
	}
	else
	{
		////////////////////////////////////////////////////////////////////////// A compléter
	}
}

bool Map::caseDisponible(int x, int y)
{
	if(!m_tabCases[y*this->m_largeur+x]->occupee() && !m_tabCases[y*this->m_largeur+x]->estObstacle())
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Map::libererCase(int x, int y)
{
	this->m_tabCases[x+y*this->m_largeur]->liberer();
}

void Map::libererEspaceTexture()
{
	this->m_tex->libererEspace(&(this->m_idTexture));
}

int Map::getXCase(float px)
{
	return (int) m_largeur*px;
}

int Map::getYCase(float py)
{
	return (int) m_hauteur*py;
}

bool Map::dansZone(int cx, int cy, int idJoueur)
{
	return this->m_tabCases[cx+cy*m_largeur]->dansZone(this->m_id,idJoueur);
}

void Map::dessinerZone(int idJoueur)
{
	for(int i=0;i<m_largeur*m_hauteur;i++)
	{
		if(m_tabCases[i]->dansZone(this->m_id,idJoueur))
		{
			if(idJoueur == 1)
			{
				m_tabCases[i]->briller(0,0,255,0.2);
			}
			else if(idJoueur == 2)
			{
				m_tabCases[i]->briller(255,0,0,0.2);
			}
		}
	}
}

void Map::AStar(Case** depart, Case* destination)
{
	bool* visited;
	visited=(bool*)malloc(m_largeur*m_hauteur*sizeof(bool));
	for(int i=0;i<this->m_largeur*this->m_hauteur;i++)
	{
		visited[i]=false;
	}
	Case** to_visit;
	to_visit=(Case**)malloc(m_largeur*m_hauteur*sizeof(Case*));
	for(int j=0;j<this->m_largeur*this->m_hauteur;j++)
	{
		to_visit[j]= new Case();
	}
	Case* current = *depart;
	while(current->getId()!=destination->getId())
	{
		visited[current->getId()]=true;

		Case** voisins;
		voisins = (Case**) malloc(4*sizeof(Case*));
		for(int v=0;v<4;v++)
		{
			voisins[v] = new Case();
		}
		if(!current->occupee() || current->getId()==(*depart)->getId())
		{
			//CASE DE GAUCHE
			if(!(current->getId()-1<0 || current->getId()/this->m_largeur!=(current->getId()-1)/this->m_largeur))
			{
				if(!visited[current->getId()-1])
				{
					if(!this->m_tabCases[current->getId()-1]->estObstacle())
					{
						if(!estDans(current->getId()-1,to_visit,this->m_largeur*this->m_hauteur))
						{
							voisins[0]=this->m_tabCases[current->getId()-1];
						}
					}
				}
			}

			//CASE DU DESSUS
			if(!(current->getId()-this->m_largeur<0))
			{
				if(!visited[current->getId()-this->m_largeur])
				{
					if(!this->m_tabCases[current->getId()-this->m_largeur]->estObstacle())
					{
						if(!estDans(current->getId()-this->m_largeur,to_visit,this->m_largeur*this->m_hauteur))
						{
							voisins[1]=this->m_tabCases[current->getId()-this->m_largeur];
						}
					}
				}
			}

			//CASE DE DROITE
			if(!(current->getId()+1>this->m_largeur*this->m_hauteur || current->getId()/this->m_largeur!=(current->getId()+1)/this->m_largeur))
			{
				if(!visited[current->getId()+1])
				{
					if(!this->m_tabCases[current->getId()+1]->estObstacle())
					{
						if(!estDans(current->getId()+1,to_visit,this->m_largeur*this->m_hauteur))
						{
							voisins[2]=this->m_tabCases[current->getId()+1];
						}
					}
				}
			}

			//CASE DU DESSOUS
			if(!(current->getId()+m_largeur>this->m_largeur*this->m_hauteur))
			{
				if(!visited[current->getId()+this->m_largeur])
				{
					if(!this->m_tabCases[current->getId()+this->m_largeur]->estObstacle())
					{
						if(!estDans(current->getId()+this->m_largeur,to_visit,this->m_largeur*this->m_hauteur))
						{
							voisins[3]=this->m_tabCases[current->getId()+this->m_largeur];
						}
					}
				}
			}

			for(int k=0;k<4;k++)
			{
				current->setVoisins(voisins);
				if(voisins[k]->getId()>=0)
				{
					int c=0;
					while(to_visit[c]->getId()>=0)
					{
						c++;
					}
					to_visit[c]=voisins[k];
				}
			}
		}

		if(estVide(to_visit,this->m_largeur*this->m_hauteur))
		{
			return;
		}

		int count=0;
		int indexMin=0;
		float distance_min=sqrt(this->m_largeur*this->m_largeur+this->m_hauteur*this->m_hauteur);
		while(to_visit[count]->getId()>=0)
		{
			int xDepart=(*depart)->getId()%this->m_largeur;
			int yDepart=(*depart)->getId()/this->m_largeur;
			int x=to_visit[count]->getId()%this->m_largeur;
			int y=to_visit[count]->getId()/this->m_largeur;
			int xArrivee=destination->getId()%this->m_largeur;
			int yArrivee=destination->getId()/this->m_largeur;
			float dDepartTovisit = sqrt((float)(x-xDepart)*(float)(x-xDepart)+(float)(y-yDepart)*(float)(y-yDepart));
			float dTovisitArrivee = sqrt((float)(x-xArrivee)*(float)(x-xArrivee)+(float)(y-yArrivee)*(float)(y-yArrivee));
			if(dDepartTovisit+dTovisitArrivee<distance_min)
			{
				distance_min=dDepartTovisit+dTovisitArrivee;
				indexMin=count;
			}
			count++;
		}
		current=to_visit[indexMin];
		if(count>0)
		{
			to_visit[indexMin]=to_visit[count-1];
			to_visit[count-1]=new Case();
		}
		else
		{
			to_visit[0]=new Case();
		}

		free(voisins);
	}

	while(current->getId()!=(*depart)->getId())
	{
		current->getParent()->setNext(current);
		current=current->getParent();
	}
	free(to_visit);
	free(visited);
}

// void Map::AStarArbre(Case** depart, Case* destination)
// {
// 	bool* visited;
// 	int xDepart=(*depart)->getId()%this->m_largeur;
// 	int yDepart=(*depart)->getId()/this->m_largeur;
// 	int xArrivee=destination->getId()%this->m_largeur;
// 	int yArrivee=destination->getId()/this->m_largeur;
// 	visited=(bool*)malloc(this->m_largeur*this->m_hauteur*sizeof(bool));
// 	for(int i=0;i<this->m_largeur*this->m_hauteur;i++)
// 	{
// 		visited[i]=false;
// 	}
// 	Noeud* to_visit=new Noeud();

// 	Case* current = *depart;
// 	while(current->getId()!=destination->getId())
// 	{
// 		visited[current->getId()]=true;
// 		to_visit->getRacine()->reequilibrer();
// 		to_visit = to_visit->getRacine();

// 		if(!current->occupee() || current->getId()==(*depart)->getId())
// 		{
// 			//CASE DE GAUCHE
// 			if(!(current->getId()-1<0 || current->getId()/this->m_largeur!=(current->getId()-1)/this->m_largeur))
// 			{
// 				if(!visited[current->getId()-1])
// 				{
// 					if(!this->m_tabCases[current->getId()-1]->estObstacle())
// 					{
// 						int x=(current->getId()-1)%this->m_largeur;
// 						int y=(current->getId()-1)/this->m_largeur;
// 						float dDepartTovisit = sqrt((float)(x-xDepart)*(float)(x-xDepart)+(float)(y-yDepart)*(float)(y-yDepart));
// 						float dTovisitArrivee = sqrt((float)(x-xArrivee)*(float)(x-xArrivee)+(float)(y-yArrivee)*(float)(y-yArrivee));
// 						if(to_visit->caseDuNoeud()->getId()<0)
// 						{
// 							to_visit=new Noeud(this->m_tabCases[current->getId()-1],dDepartTovisit+dTovisitArrivee);
// 						}
// 						else
// 						{
// 							to_visit->inserer(new Noeud(this->m_tabCases[current->getId()-1],dDepartTovisit+dTovisitArrivee));
// 							to_visit=to_visit->getRacine();
// 						}
// 						this->m_tabCases[current->getId()-1]->setParent(current);
// 					}
// 				}
// 			}

// 			//CASE DU DESSUS
// 			if(!(current->getId()-this->m_largeur<0))
// 			{
// 				if(!visited[current->getId()-this->m_largeur])
// 				{
// 					if(!this->m_tabCases[current->getId()-this->m_largeur]->estObstacle())
// 					{
// 						int x=(current->getId()-this->m_largeur)%this->m_largeur;
// 						int y=(current->getId()-this->m_largeur)/this->m_largeur;
// 						float dDepartTovisit = sqrt((float)(x-xDepart)*(float)(x-xDepart)+(float)(y-yDepart)*(float)(y-yDepart));
// 						float dTovisitArrivee = sqrt((float)(x-xArrivee)*(float)(x-xArrivee)+(float)(y-yArrivee)*(float)(y-yArrivee));
// 						if(to_visit->caseDuNoeud()->getId()<0)
// 						{
// 							to_visit = new Noeud(this->m_tabCases[current->getId()-this->m_largeur],dDepartTovisit+dTovisitArrivee);
// 						}
// 						else
// 						{
// 							to_visit->inserer(new Noeud(this->m_tabCases[current->getId()-this->m_largeur],dDepartTovisit+dTovisitArrivee));
// 							to_visit=to_visit->getRacine();
// 						}
// 						this->m_tabCases[current->getId()-this->m_largeur]->setParent(current);
// 					}
// 				}
// 			}

// 			//CASE DE DROITE
// 			if(!(current->getId()+1>this->m_largeur*this->m_hauteur || current->getId()/this->m_largeur!=(current->getId()+1)/this->m_largeur))
// 			{
// 				if(!visited[current->getId()+1])
// 				{
// 					if(!this->m_tabCases[current->getId()+1]->estObstacle())
// 					{
// 						int x=(current->getId()+1)%this->m_largeur;
// 						int y=(current->getId()+1)/this->m_largeur;
// 						float dDepartTovisit = sqrt((float)(x-xDepart)*(float)(x-xDepart)+(float)(y-yDepart)*(float)(y-yDepart));
// 						float dTovisitArrivee = sqrt((float)(x-xArrivee)*(float)(x-xArrivee)+(float)(y-yArrivee)*(float)(y-yArrivee));
// 						if(to_visit->caseDuNoeud()->getId()<0)
// 						{
// 							to_visit = new Noeud(this->m_tabCases[current->getId()+1],dDepartTovisit+dTovisitArrivee);
// 						}
// 						else
// 						{
// 							to_visit->inserer(new Noeud(this->m_tabCases[current->getId()+1],dDepartTovisit+dTovisitArrivee));
// 							to_visit=to_visit->getRacine();
// 						}
// 						this->m_tabCases[current->getId()+1]->setParent(current);
// 					}
// 				}
// 			}

// 			//CASE DU DESSOUS
// 			if(!(current->getId()+m_largeur>this->m_largeur*this->m_hauteur))
// 			{
// 				if(!visited[current->getId()+this->m_largeur])
// 				{
// 					if(!this->m_tabCases[current->getId()+this->m_largeur]->estObstacle())
// 					{
// 						int x=(current->getId()+this->m_largeur)%this->m_largeur;
// 						int y=(current->getId()+this->m_largeur)/this->m_largeur;
// 						float dDepartTovisit = sqrt((float)(x-xDepart)*(float)(x-xDepart)+(float)(y-yDepart)*(float)(y-yDepart));
// 						float dTovisitArrivee = sqrt((float)(x-xArrivee)*(float)(x-xArrivee)+(float)(y-yArrivee)*(float)(y-yArrivee));
// 						if(to_visit->caseDuNoeud()->getId()<0)
// 						{
// 							to_visit = new Noeud(this->m_tabCases[current->getId()+this->m_largeur],dDepartTovisit+dTovisitArrivee);
// 						}
// 						else
// 						{
// 							to_visit->inserer(new Noeud(this->m_tabCases[current->getId()+this->m_largeur],dDepartTovisit+dTovisitArrivee));
// 							to_visit=to_visit->getRacine();
// 						}
// 						this->m_tabCases[current->getId()+this->m_largeur]->setParent(current);
// 					}
// 				}
// 			}
// 		}
// 		to_visit = to_visit->getRacine();
// 		Noeud* noeudProche = to_visit->plusPetiteDist();
// 		current = noeudProche->caseDuNoeud();
// 		if(to_visit->getRacine()->estSeul())
// 		{
// 			to_visit = new Noeud();
// 		}
// 		else
// 		{
// 		 	noeudProche->detruire();
// 		}
// 	}
// 	while(current->getId()!=(*depart)->getId())
// 	{
// 		current->getParent()->setNext(current);
// 		current=current->getParent();
// 	}
// }

int Map::getTailleLargeur()
{
	return this->m_largeur;
}

int Map::getTailleHauteur()
{
	return this->m_hauteur;
}
