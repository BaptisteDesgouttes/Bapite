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

void interface_options(SDL_Surface* surface,float* aspectRatio,int* loop,float* px,float* py,Textures** textes,int* nb_unite_depart,int* id_map)
{
    Menu* menuOption = new Menu(10);
    menuOption->chargerFond();
    menuOption->chargerBoutons();

	while(*loop==3)
    {
        /* Recuperation du temps au debut de la boucle */
        Uint32 startTime = SDL_GetTicks();

        /* Placer ici le code de dessin */
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        menuOption->dessinerFond();
        menuOption->dessinerBoutons();
        dessinerTexte(textes,menuOption);
		if(*id_map==1)
		{
			drawRect(-0.7,0.3,0.9,0.6,255,255,255,0.5);
		}
		if(*id_map==2)
		{
			drawRect(0.7,0.3,0.9,0.6,255,255,255,0.5);
		}
        /* Echange du front et du back buffer : mise a jour de la fenetre */
        SDL_GL_SwapBuffers();

        /* Boucle traitant les evenements */
        SDL_Event e;
        while(SDL_PollEvent(&e))
        {
            /* L'utilisateur ferme la fenetre : */
            if(e.type == SDL_QUIT)
            {
                *loop = 0;
                break;
            }

            if( e.type == SDL_KEYDOWN
                && (e.key.keysym.sym == SDLK_q || e.key.keysym.sym == SDLK_ESCAPE))
            {
                *loop = 0;
                break;
            }

            /* Quelques exemples de traitement d'evenements : */
            switch(e.type)
            {
                /* Redimensionnement fenetre */
                case SDL_VIDEORESIZE:
                    reshape(&surface, e.resize.w, e.resize.h);
                    break;

                /* Clic souris */
                case SDL_MOUSEBUTTONUP:
                    //printf("clic en (%d, %d)\n", e.button.x, e.button.y);
                    *px=e.button.x;
                    *py=e.button.y;
                    *px=-0.5+(*px)/(surface->w);
                    *py=-0.5+(*py)/(surface->h);
                    *px=*px*GL_VIEW_SIZE;
                    *py=(-1)*(*py)*GL_VIEW_SIZE;
                    if(*aspectRatio<1)
                    {
                    *py=*py/(*aspectRatio);
                    }
                    else
                    {
                      *px=*px*(*aspectRatio);
                    }
                    menuOption->quelBoutonMenuOptions(*px,*py,loop,id_map,nb_unite_depart,textes);
					//printf("nombre de joueurs %d\n",*nb_unite_depart);
            }
        }
        /* Calcul du temps ecoule */
        Uint32 elapsedTime = SDL_GetTicks() - startTime;
        /* Si trop peu de temps s'est ecoule, on met en pause le programme */
        if(elapsedTime < FRAMERATE_MILLISECONDS)
        {
            SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
        }
    }
		menuOption->libererEspace();
}
