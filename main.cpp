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

static float aspectRatio;

void reshape(SDL_Surface** surface, unsigned int width, unsigned int height)
{
    SDL_Surface* surface_temp = SDL_SetVideoMode(
        width, height, BIT_PER_PIXEL,
        SDL_OPENGL | SDL_GL_DOUBLEBUFFER | SDL_RESIZABLE);
    if(NULL == surface_temp)
    {
        fprintf(
            stderr,
            "Erreur lors du redimensionnement de la fenetre.\n");
        exit(EXIT_FAILURE);
    }
    *surface = surface_temp;

    aspectRatio = width / (float) height;

    glViewport(0, 0, (*surface)->w, (*surface)->h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if( aspectRatio > 1)
    {
        gluOrtho2D(
        -GL_VIEW_SIZE / 2. * aspectRatio, GL_VIEW_SIZE / 2. * aspectRatio,
        -GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.);
    }
    else
    {
        gluOrtho2D(
        -GL_VIEW_SIZE / 2., GL_VIEW_SIZE / 2.,
        -GL_VIEW_SIZE / 2. / aspectRatio, GL_VIEW_SIZE / 2. / aspectRatio);
    }
}

int main(int argc, char** argv)
{
    int id_map=1;
    int nb_unite_depart=3;

    ///////////////////////////////////////////Initialisation des deux Joueurs
    // joueur1->creationUnite('a');
    // joueur2->creationUnite('g');
    // joueur1->creationUnite('t');
    // joueur2->creationUnite('n');
    bool contreIA;

    /* Initialisation de la SDL */
    if(-1 == SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(
            stderr,
            "Impossible d'initialiser la SDL. Fin du programme.\n");
        exit(EXIT_FAILURE);
    }

    /* Ouverture d'une fenetre et creation d'un contexte OpenGL */
    SDL_Surface* surface;
    reshape(&surface, WINDOW_WIDTH, WINDOW_HEIGHT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    /* Initialisation du titre de la fenetre */
	SDL_WM_SetCaption(WINDOW_TITLE, NULL);

    /* Initialisation de la police*/
    TTF_Init();

    //Création des textes
    int nbTexte = 66;
    Textures** textes = (Textures**) malloc(nbTexte*sizeof(Textures*));
    for(int i=0;i<nbTexte;i++)
    {
        textes[i] = new Textures();
        textes[i]->chargeTexte(" ",100,0,0,0);
    }
    //Initialisation des textes du menu
    creationTextesMenus(textes);

    //Coordonnées du clic
    float px;
    float py;

    /* Boucle principale */
    int loop = 1;
    int vainqueur = 0;
    while(loop!=0)
    {
        switch(loop)
        {
            case 1 :
                interface_menu(surface,&aspectRatio,&loop,&px,&py,textes,&contreIA);
                break;
            case 2:
                interface_jeu(surface,textes,&aspectRatio,&loop,&px,&py,id_map,nb_unite_depart,contreIA,&vainqueur);
                break;
            case 3 :
                interface_options(surface,&aspectRatio,&loop,&px,&py,textes,&nb_unite_depart,&id_map);
                break;
            case 4 :
                interface_regles(surface,&aspectRatio,&loop,&px,&py,textes,&nb_unite_depart,&id_map);
                break;
            case 5 :
                interface_fin(surface,&aspectRatio,&loop,&px,&py,textes,&contreIA,&vainqueur);
                break;
        }
    }

    glBlendFunc(GL_SRC_ALPHA,0);
    glDisable(GL_BLEND);

    for(int i=0;i<nbTexte;i++)
    {
        textes[i]->libererTexte();
    }

    /* Liberation des ressources associees a la SDL */
    TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}
