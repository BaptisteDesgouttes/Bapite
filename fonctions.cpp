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

void drawSquare(float x, float y, float taille,int r, int v, int b,float a)
{
    glBegin(GL_TRIANGLE_FAN);
        glColor4f(r,v,b,a);
        glVertex2f(x,y);
        glVertex2f(x+taille,y);
        glVertex2f(x+taille,y-taille);
        glVertex2f(x,y-taille);
        glVertex2f(x,y);
        glColor4f(255,255,255,1);
    glEnd();
}

void drawRect(float x, float y, float w, float h,int r, int v, int b,float a)
{
    glBegin(GL_TRIANGLE_FAN);
        glColor4f(r,v,b,a);
        glVertex2f(x-w/2,y+h/2);
        glVertex2f(x+w/2,y+h/2);
        glVertex2f(x+w/2,y-h/2);
        glVertex2f(x-w/2,y-h/2);
        glVertex2f(x-w/2,y+h/2);
        glColor4f(255,255,255,1);
    glEnd();
}

void drawRect2(float x, float y, float w, float h,int r, int v, int b,float a)
{
    glBegin(GL_TRIANGLE_FAN);
      glColor4f(r,v,b,a);
      glVertex2f(x,y);
      glVertex2f(x+w,y);
      glVertex2f(x+w,y-h);
      glVertex2f(x,y-h);
      glVertex2f(x,y);
      glColor4f(255,255,255,1);
    glEnd();
}

// char* convertirNombreEnChar(int valeur, char* phrase)
// {
//     string str = to_string(valeur);
//     char* charetoile = (char*)str.c_str();
//     char* result;

//     result = (char*)malloc(strlen(charetoile)+1+strlen(phrase)+1);
//     strcpy(result,phrase);
//     strcat(phrase,charetoile);
//     return result;
// }
void creationTextesMenus(Textures** textes)
{
    for(int i=0;i<4;i++)
    {
        textes[i]->libererTexte();
    }
    textes[0]->chargeTexte("Jouer 1v1",100,222,191,43);
    textes[1]->chargeTexte("Jouer 1vC",100,222,191,43);
    textes[2]->chargeTexte("Options",100,222,191,43);
    textes[3]->chargeTexte("Quitter",100,222,191,43);

    for(int j=33;j<37;j++)
    {
        textes[j]->libererTexte();
    }
    textes[33]->chargeTexte("Dans quel monde veux-tu combattre ?",100,255,255,255);
    textes[34]->chargeTexte("Combien veux-tu d'unites ?",100,255,255,255);
    textes[35]->chargeTexte("3",100,255,0,0);
    textes[36]->chargeTexte("5",100,0,0,0);
    for(int j=46;j<63;j++)
    {
        textes[j]->libererTexte();
    }
    textes[46]->chargeTexte("Bienvenue dans Bapite !",100,255,255,255);
    textes[47]->chargeTexte("Bapite c'est la reconstitution d'une des plus grandes batailles du 16e siecle.",80,255,255,255);
    textes[48]->chargeTexte("Toi tu es le stratege de cette guerre.",80,255,255,255);
    textes[49]->chargeTexte("Dans le menu options tu vas pouvoir choisir l'effectif de ton armee.",80,255,255,255);
    textes[50]->chargeTexte("En debut de partie tu vas pouvoir la constituer ! Tu as acces a plus de 5 types de combattants !",80,255,255,255);
    textes[51]->chargeTexte("Tu as le choix entre un nain, un guerrier, un mage noir, un mage blanc et un archer.",80,255,255,255);
    textes[52]->chargeTexte("Mais ATTENTION ! Chaque unite a ses propres caracteristiques alors :",80,255,255,255);
    textes[53]->chargeTexte("SURTOUT SOIS STRATEGIQUE !",80,255,255,255);
    textes[54]->chargeTexte("Une fois que tu as fais tes choix le jeu commence. Place tes unites dans la zone qui t'es dediee.",80,255,255,255);
    textes[55]->chargeTexte("Tu peux suivre le deroulement du jeu sur le menu en haut a gauche.",80,255,255,255);
    textes[56]->chargeTexte("Tu peux effectuer tes actions avec le menu de gauche.",80,255,255,255);
    textes[57]->chargeTexte("Et enfin tout ce qui concerne tes unites est ecrit dans le menu du bas.",80,255,255,255);
    textes[58]->chargeTexte("N'oublie jamais que tous les coups son permis pour gagner cette furieuse bataille !",80,255,255,255);

    textes[59]->chargeTexte("Revenir au menu",100,0,0,0);
    textes[60]->chargeTexte("gg bg le j1",170,0,0,255);
    textes[61]->chargeTexte("gg bg le j2",170,255,0,0);
    textes[62]->chargeTexte("Ordi vainqueur, gros noob",150,255,255,255);
}

void creationTextes(Textures** textes, bool contreIA)
{
    for(int i=4;i<33;i++)
    {
        textes[i]->libererTexte();
    }
    textes[4]->chargeTexte("Attaquer et deplacer",100,0,0,0);
    textes[5]->chargeTexte("Acheter une unite",100,0,0,0);
    textes[6]->chargeTexte("Passer mon tour",100,0,0,0);
    textes[7]->chargeTexte("Deplacer d'abord",100,0,0,0);
    textes[8]->chargeTexte("Attaquer d'abord",100,0,0,0);
    // textes[15]->chargeTexte("Selectionnez une",100,255,255,255);
    // textes[16]->chargeTexte("unite a deplacer",100,255,255,255);
    textes[15]->chargeTexte("Selectionnez",100,255,255,255);
    textes[16]->chargeTexte("une unite",100,255,255,255);
    textes[17]->chargeTexte("Ou voulez-vous",100,255,255,255);
    textes[18]->chargeTexte("deplacer cette unite ?",100,255,255,255);
    textes[13]->chargeTexte("Selectionner",100,0,0,0);
    textes[14]->chargeTexte("une autre unite",100,0,0,0);
    textes[9]->chargeTexte("Ne pas se deplacer",100,0,0,0);
    textes[19]->chargeTexte("Selectionnez une",100,255,255,255);
    textes[20]->chargeTexte("unite attaquante",100,255,255,255);
    textes[21]->chargeTexte("Selectionnez une",100,255,255,255);
    textes[22]->chargeTexte("unite a attaquer",100,255,255,255);
    textes[10]->chargeTexte("Ne pas attaquer",100,0,0,0);
    textes[11]->chargeTexte("Fin des",100,0,0,0);
    textes[12]->chargeTexte("achats",100,0,0,0);

    textes[23]->chargeTexte("??????",100,0,0,0);
    textes[24]->chargeTexte("PV : ",100,0,0,0);
    textes[25]->chargeTexte("Force : ",100,0,0,0);
    textes[26]->chargeTexte("Portee : ",100,0,0,0);
    textes[27]->chargeTexte("Mobilite : ",100,0,0,0);
    textes[32]->chargeTexte("J?",100,0,0,0);
    textes[28]->chargeTexte("???",100,0,0,0);
    textes[29]->chargeTexte("???",100,0,0,0);
    textes[30]->chargeTexte("???",100,0,0,0);
    textes[31]->chargeTexte("???",100,0,0,0);

    textes[45]->libererTexte();
    textes[45]->chargeTexte("Annuler",100,0,0,0);


    textes[63]->libererTexte();
    textes[64]->libererTexte();
    textes[65]->libererTexte();
    textes[63]->chargeTexte("Joueur 1, choisis une unite !",125,0,0,255);
    textes[64]->chargeTexte("Joueur 2, choisis une unite !",125,255,0,0);
    textes[65]->chargeTexte("Retour au menu",80,0,0,0);
    for(int j=37;j<45;j++)
    {
        textes[j]->libererTexte();
    }

    textes[37]->chargeTexte("Joueur 1",100,0,0,255);
    if(contreIA)
    {
        textes[38]->chargeTexte("ORDI",100,255,0,0);
    }
    else
    {
        textes[38]->chargeTexte("Joueur 2",100,255,0,0);
    }
    textes[39]->chargeTexte("Unites en vie :",60,0,0,0);

    // char nbUnitesJ1[16];
    // sprintf(nbUnitesJ1,"%d",joueur1->returnNbUnites());
    // textes[43]->chargeTexte(nbUnitesJ1,60,255,0,0);
    textes[43]->chargeTexte("???",60,0,0,255);
    textes[40]->chargeTexte("Unites en vie :",60,0,0,0);

    // char nbUnitesJ2[16];
    // sprintf(nbUnitesJ2,"%d",joueur2->returnNbUnites());
    // textes[44]->chargeTexte(nbUnitesJ2,60,0,0,255);
    textes[44]->chargeTexte("???",60,255,0,0);

    // char argentJ1[16];
    // sprintf(argentJ1,"%d",joueur1->returnFonds());
    // textes[41]->chargeTexte(argentJ1,80,0,255,255);
    textes[41]->chargeTexte("???",80,255,255,0);

    // char argentJ2[16];
    // sprintf(argentJ2,"%d",joueur2->returnFonds());
    // textes[42]->chargeTexte(argentJ2,80,0,255,255);
    textes[42]->chargeTexte("???",80,255,255,0);
}

void dessinerTexte(Textures** textes, Menu* menu)
{
    switch(menu->getIdMenu())
    {
        case 1 :
            textes[0]->dessineTexte(menu->boutonGetX(0),menu->boutonGetY(0));
            textes[1]->dessineTexte(menu->boutonGetX(1),menu->boutonGetY(1));
            textes[2]->dessineTexte(menu->boutonGetX(2),menu->boutonGetY(2));
            textes[3]->dessineTexte(menu->boutonGetX(3),menu->boutonGetY(3));
            break;
        case 2 :
            textes[4]->dessineTexte(menu->boutonGetX(0),menu->boutonGetY(0));
            textes[5]->dessineTexte(menu->boutonGetX(1),menu->boutonGetY(1));
            textes[6]->dessineTexte(menu->boutonGetX(2),menu->boutonGetY(2));
            break;
        case 3 :
            textes[7]->dessineTexte(menu->boutonGetX(0),menu->boutonGetY(0));
            textes[8]->dessineTexte(menu->boutonGetX(1),menu->boutonGetY(1));
            textes[6]->dessineTexte(menu->boutonGetX(2),menu->boutonGetY(2));
            break;
        case 4 :
            textes[15]->dessineTexte(menu->boutonGetX(0),menu->boutonGetY(0)+0.7);
            textes[16]->dessineTexte(menu->boutonGetX(0),menu->boutonGetY(0)+0.6);
            //textes[9]->dessineTexte(menu->boutonGetX(0),menu->boutonGetY(0));
            textes[45]->dessineTexte(menu->boutonGetX(0),menu->boutonGetY(0));
            break;
        case 5 :
        //     textes[17]->dessineTexte(menu->boutonGetX(1),menu->boutonGetY(1)+0.35);
        //     textes[18]->dessineTexte(menu->boutonGetX(1),menu->boutonGetY(1)+0.25);
        //     textes[13]->dessineTexte(menu->boutonGetX(1),menu->boutonGetY(1)+0.05);
        //     textes[14]->dessineTexte(menu->boutonGetX(1),menu->boutonGetY(1)-0.05);
            textes[17]->dessineTexte(menu->boutonGetX(0),menu->boutonGetY(0)+0.75);
            textes[18]->dessineTexte(menu->boutonGetX(0),menu->boutonGetY(0)+0.65);
            // textes[13]->dessineTexte(menu->boutonGetX(0),menu->boutonGetY(0)+0.05);
            // textes[14]->dessineTexte(menu->boutonGetX(0),menu->boutonGetY(0)-0.05);
            textes[9]->dessineTexte(menu->boutonGetX(0),menu->boutonGetY(0));
            break;
        case 6 :
            textes[19]->dessineTexte(menu->boutonGetX(0),menu->boutonGetY(0)+0.7);
            textes[20]->dessineTexte(menu->boutonGetX(0),menu->boutonGetY(0)+0.6);
            textes[10]->dessineTexte(menu->boutonGetX(0),menu->boutonGetY(0));
            break;
        case 7 :
        //     textes[21]->dessineTexte(menu->boutonGetX(1),menu->boutonGetY(1)+0.35);
        //     textes[22]->dessineTexte(menu->boutonGetX(1),menu->boutonGetY(1)+0.25);
        //     textes[13]->dessineTexte(menu->boutonGetX(1),menu->boutonGetY(1)+0.05);
        //     textes[14]->dessineTexte(menu->boutonGetX(1),menu->boutonGetY(1)-0.05);
            textes[21]->dessineTexte(menu->boutonGetX(0),menu->boutonGetY(0)+0.7);
            textes[22]->dessineTexte(menu->boutonGetX(0),menu->boutonGetY(0)+0.6);
            // textes[13]->dessineTexte(menu->boutonGetX(0),menu->boutonGetY(0)+0.05);
            // textes[14]->dessineTexte(menu->boutonGetX(0),menu->boutonGetY(0)-0.05);
            textes[10]->dessineTexte(menu->boutonGetX(0),menu->boutonGetY(0));
            break;
        case 8 :
            textes[11]->dessineTexte(menu->boutonGetX(5),menu->boutonGetY(5)+0.07);
            textes[12]->dessineTexte(menu->boutonGetX(5),menu->boutonGetY(5)-0.07);
            break;
        case 9 :
            textes[37]->dessineTexte(menu->boutonGetX(0)-(RATIO*GL_VIEW_SIZE/2.-GL_VIEW_SIZE*RATIO/2./3.)/4,menu->boutonGetY(0)+0.45);
            textes[38]->dessineTexte(menu->boutonGetX(0)+(RATIO*GL_VIEW_SIZE/2.-GL_VIEW_SIZE*RATIO/2./3.)/4,menu->boutonGetY(0)+0.45);
            textes[39]->dessineTexte(menu->boutonGetX(0)-(RATIO*GL_VIEW_SIZE/2.-GL_VIEW_SIZE*RATIO/2./3.)/4-0.07,menu->boutonGetY(0)+0.3);
            textes[43]->dessineTexte(menu->boutonGetX(0)-(RATIO*GL_VIEW_SIZE/2.-GL_VIEW_SIZE*RATIO/2./3.)/4+0.2,menu->boutonGetY(0)+0.3);
            textes[40]->dessineTexte(menu->boutonGetX(0)+(RATIO*GL_VIEW_SIZE/2.-GL_VIEW_SIZE*RATIO/2./3.)/4-0.07,menu->boutonGetY(0)+0.3);
            textes[44]->dessineTexte(menu->boutonGetX(0)+(RATIO*GL_VIEW_SIZE/2.-GL_VIEW_SIZE*RATIO/2./3.)/4+0.2,menu->boutonGetY(0)+0.3);
            textes[41]->dessineTexte(menu->boutonGetX(0)-(RATIO*GL_VIEW_SIZE/2.-GL_VIEW_SIZE*RATIO/2./3.)/4,menu->boutonGetY(0)+0.15);
            textes[42]->dessineTexte(menu->boutonGetX(0)+(RATIO*GL_VIEW_SIZE/2.-GL_VIEW_SIZE*RATIO/2./3.)/4,menu->boutonGetY(0)+0.15);
            textes[65]->dessineTexte(menu->boutonGetX(0),menu->boutonGetY(0));
            break;
        case 10 :
            textes[33]->dessineTexte(0,0.8);
            textes[34]->dessineTexte(0,-0.2);
            textes[35]->dessineTexte(-0.3,-0.7);
            textes[36]->dessineTexte(0.3,-0.7);
            break;
        case 11 :
            textes[23]->dessineTexte(menu->boutonGetX(0)+0.4,menu->boutonGetY(0));
            textes[32]->dessineTexte(menu->boutonGetX(0)+0.4,menu->boutonGetY(0)+0.1);
            textes[24]->dessineTexte(menu->boutonGetX(0)+0.8,menu->boutonGetY(0)+0.1);
            textes[25]->dessineTexte(menu->boutonGetX(0)+0.8,menu->boutonGetY(0)-0.1);
            textes[26]->dessineTexte(menu->boutonGetX(0)+1.5,menu->boutonGetY(0)+0.1);
            textes[27]->dessineTexte(menu->boutonGetX(0)+1.5,menu->boutonGetY(0)-0.1);
            textes[28]->dessineTexte(menu->boutonGetX(0)+1.05,menu->boutonGetY(0)+0.1);
            textes[29]->dessineTexte(menu->boutonGetX(0)+1.05,menu->boutonGetY(0)-0.1);
            textes[30]->dessineTexte(menu->boutonGetX(0)+1.8,menu->boutonGetY(0)+0.1);
            textes[31]->dessineTexte(menu->boutonGetX(0)+1.8,menu->boutonGetY(0)-0.1);
            break;
        case 13 :
            textes[46]->dessineTexte(0,0.8);
            textes[47]->dessineTexte(0,0.6);
            textes[48]->dessineTexte(0,0.5);
            textes[49]->dessineTexte(0,0.4);
            textes[50]->dessineTexte(0,0.3);
            textes[51]->dessineTexte(0,0.2);
            textes[52]->dessineTexte(0,0.1);
            textes[53]->dessineTexte(0,-0.1);
            textes[54]->dessineTexte(0,-0.3);
            textes[55]->dessineTexte(0,-0.4);
            textes[56]->dessineTexte(0,-0.5);
            textes[57]->dessineTexte(0,-0.6);
            textes[58]->dessineTexte(0,-0.7);
            break;
        case 14 :
          textes[59]->dessineTexte(menu->boutonGetX(0),menu->boutonGetY(0));
          break;
    }
}

void dessinerImage(GLuint idTexture,float xg, float xd, float yh, float yb)
{
  glEnable(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, idTexture);

          glPushMatrix();

            glBegin(GL_QUADS);
              glTexCoord2f(0, 0);
              glVertex2f(xg,yh);

              glTexCoord2f(1, 0);
              glVertex2f(xd,yh);

              glTexCoord2f(1, 1);
              glVertex2f(xd,yb);

              glTexCoord2f(0, 1);
              glVertex2f(xg,yb);
            glEnd();

          glPopMatrix();


        glBindTexture(GL_TEXTURE_2D, 0);

    glDisable(GL_TEXTURE_2D);
}

bool selection(int cx, int cy, int* cxs, int* cys, int idMenu, int idProchainMenu, int* idNouveauMenu, Map* carte, Joueur** joueur, Unite** unite, Textures** texte1, Textures** texte2)
{
	if(cx<0 || cy<0)
	{
		*idNouveauMenu=idMenu;
        return false;
	}
	else
	{
		if(carte->caseSelectionnee(cx,cy)->occupee())
		{
			if((*joueur)->appartient(carte->caseSelectionnee(cx,cy)->selectUnite()))
			{
                if(!carte->caseSelectionnee(cx,cy)->selectUnite()->utilisee())
                {
    				*cxs=cx;
    				*cys=cy;
    				*unite= carte->caseSelectionnee(cx,cy)->selectUnite();
    				*idNouveauMenu=idProchainMenu;
                    return true;
                }
                else
                {
                    (*texte1)->libererTexte();
                    (*texte2)->libererTexte();
                    (*texte1)->chargeTexte("Vous avez deja",100,255,255,255);
                    (*texte2)->chargeTexte("utilise cette unite",100,255,255,255);
                    *idNouveauMenu=idMenu;
                    return false;
                }

			}
			else
			{
                (*texte1)->libererTexte();
                (*texte2)->libererTexte();
                (*texte1)->chargeTexte("Cette unite ne vous",100,255,255,255);
                (*texte2)->chargeTexte("appartient pas",100,255,255,255);
				*idNouveauMenu=idMenu;
                return false;
			}
		}
		else
		{
			*idNouveauMenu=idMenu;
            return false;
		}
	}
}

bool deplacement(int cx, int cy, int cxsd, int cysd, int* cxd, int* cyd, int idMenu, int idProchainMenu, int* idNouveauMenu, Map* carte, Unite** uniteActuelle, Textures** texte1, Textures** texte2)
{
    if(cx<0 || cy<0)
    {
        *idNouveauMenu=idMenu;
        return false;
    }
    else
    {
        if(cx==cxsd && cy==cysd)
        {
            (*texte1)->libererTexte();
            (*texte2)->libererTexte();
            (*texte1)->chargeTexte("La case d'arrivee ne peut",100,255,255,255);
            (*texte2)->chargeTexte("pas etre celle de depart",100,255,255,255);
            *idNouveauMenu=idMenu;
            return false;
        }
        else
        {
            if((*uniteActuelle)->verifDistance(cxsd,cysd,cx,cy))
            {
                if(!carte->caseSelectionnee(cx,cy)->estObstacle())
                {
                    if(!carte->caseSelectionnee(cx,cy)->occupee())
                    {
                        *cxd = cx;
                        *cyd = cy;
                        carte->caseSelectionnee(cxsd,cysd)->liberer();
                        (*uniteActuelle)->deplacer(cx,cy);
                        carte->caseSelectionnee(*cxd,*cyd)->occuper(*uniteActuelle);
                        *idNouveauMenu=idProchainMenu;
                        return true;
                    }
                    else
                    {
                        (*texte1)->libererTexte();
                        (*texte2)->libererTexte();
                        (*texte1)->chargeTexte("Il y a deja",100,255,255,255);
                        (*texte2)->chargeTexte("quelqu'un ici",100,255,255,255);
                        *idNouveauMenu=idMenu;
                        return false;
                    }
                }
                else
                {
                    (*texte1)->libererTexte();
                    (*texte2)->libererTexte();
                    (*texte1)->chargeTexte("Cette case n'est",100,255,255,255);
                    (*texte2)->chargeTexte("pas praticable !",100,255,255,255);
                    *idNouveauMenu=idMenu;
                    return false;
                }
            }
            else
            {
                (*texte1)->libererTexte();
                (*texte2)->libererTexte();
                (*texte1)->chargeTexte("C'est trop",100,255,255,255);
                (*texte2)->chargeTexte("loin !",100,255,255,255);
                *idNouveauMenu=idMenu;
                return false;
            }
        }
    }
}

bool attaque(int cx, int cy, int* cxa, int* cya, int idMenu, int idProchainMenu, int* idNouveauMenu, Joueur** joueur, Unite** uniteActuelle, Unite** uniteEnnemie, Map* carte, Textures** texte1, Textures** texte2, Quefeje* quefeje)
{
    if(cx<0 || cy<0)
    {
        *idNouveauMenu=idMenu;
        return false;
    }
    else
    {
         if(carte->caseSelectionnee(cx,cy)->occupee())
        {
            if((*joueur)->appartient(carte->caseSelectionnee(cx,cy)->selectUnite()))
            {
                (*texte1)->libererTexte();
                (*texte2)->libererTexte();
                (*texte1)->chargeTexte("Vous ne pouvez pas",100,255,255,255);
                (*texte2)->chargeTexte("attaquer vos allies !",100,255,255,255);
                *idNouveauMenu=idMenu;
                return false;
            }
            else
            {
                if((*uniteActuelle)->verifPortee(cx,cy))
                {
                    *cxa=cx;
                    *cya=cy;
                    (*uniteEnnemie)=carte->caseSelectionnee(cx,cy)->selectUnite();
                    (*uniteActuelle)->attaquer(*uniteEnnemie);
                    if((*uniteActuelle)->estMorte())
                    {
                        (*joueur)->argentSuicide();
                        *idNouveauMenu=3;
                    }
                    else
                    {
                        *idNouveauMenu=idProchainMenu;
                    }
                    if ((*uniteEnnemie)->estMorte())
                    {
                      (*joueur)->argentUniteTuee();
                    }
                    return true;
                }
                else
                {
                    (*texte1)->libererTexte();
                    (*texte2)->libererTexte();
                    (*texte1)->chargeTexte("La portee de votre unite",100,255,255,255);
                    (*texte2)->chargeTexte("est insuffisante",100,255,255,255);
                    *idNouveauMenu=idMenu;
                    return false;
                }
            }
        }
        else
        {
            *idNouveauMenu=idMenu;
            return false;
        }
    }
}

bool estDans(int val, Case** tableau, int size)
{
    for(int i=0; i<size;i++)
    {
        if(tableau[i]->getId()==val)
        {
            return true;
        }
    }
    return false;
}

bool estVide(Case** tableau, int size)
{
    for(int i=0; i<size; i++)
    {
        if(tableau[i]->getId()>=0)
        {
            return false;
        }
    }
    return true;
}
