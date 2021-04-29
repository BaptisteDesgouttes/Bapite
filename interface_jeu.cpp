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

void interface_jeu(SDL_Surface* surface,Textures** textes, float* aspectRatio,int* loop, float* px, float* py, int idMap, int nbInitJoueur, bool contreIA, int* vainqueur)
{
    Menu* menuChoix = new Menu(2);
    menuChoix->chargerFond();
    menuChoix->chargerBoutons();

    Menu* menuJoueurs = new Menu(9);
    menuJoueurs->chargerFond();
    menuJoueurs->chargerBoutons();

    Menu* menuUnite = new Menu(11);
    menuUnite->chargerFond();
    menuUnite->chargerBoutons();

    Menu* menuDebutJeu = new Menu(12);
    menuDebutJeu->chargerFond();
    menuDebutJeu->chargerBoutons();

    //Création des textes
    creationTextes(textes,contreIA);

	//MIS EN PLACE
    /*Création carte*/
    Map* carte = new Map(idMap);
    carte->chargerTexture();

  	//Initialisation J1
  	Joueur* joueur1 = new Joueur(1,0,0,0);

    //Initialisation J2
    Joueur *joueur2 = new Joueur(2,0,0,0);

    //Initialisation IA
    Ordinateur* ordinateur = new Ordinateur(3,0,0,0);

    /*Déclaration des variables*/
    bool debutJeu = true;
    bool placement =false;
    int nbUnite=0;
    int cxs;
    int cys;
    // int cxsd;
    // int cysd;
    int cxd;
    int cyd;
    // int cxsa;
    // int cysa;
    int cxa;
    int cya;
    Actions action=DEPLACER;
    Quefeje quefeje=VASELECTIONNER;
    Tour tour=tourj1;
    int idNouveauMenu=1;
    Unite* uniteActuelle = new Unite();
    Unite* uniteEnnemie = new Unite();
    Unite* nouvelleUnite = new Unite();
    Case* chemin = new Case();


    //BOUCLE DE JEU
	while(*loop==2)
	{
		/* Recuperation du temps au debut de la boucle */
		Uint32 startTime = SDL_GetTicks();

		if(!debutJeu && contreIA && tour==tourj2)
		{
			chemin = new Case();
			ordinateur->setUniteCible(joueur1);
        	uniteActuelle = ordinateur->selectionIA();
         	ordinateur->tourOrdi(&uniteActuelle,&chemin,carte);
         	uniteActuelle->utiliser();
		    if(ordinateur->tourFini())
		    {
		    	ordinateur->finTour();
		    	tour=tourj1;
		    }
		}

		/* Code de dessin */
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		menuChoix->dessinerFond();
        menuChoix->dessinerBoutons();
		menuUnite->dessinerFond();
        menuUnite->dessinerBoutons();
		menuJoueurs->dessinerFond();

		if(!debutJeu)
		{
	        joueur1->libererCasesVides(carte);
	        joueur1->miseAJourDonnees(&textes[43],&textes[41]);
	        if(contreIA)
	        {
	        	ordinateur->libererCasesVides(carte);
	        	ordinateur->miseAJourDonnees(&textes[44],&textes[42]);
	        }
	        else
	        {
	        	joueur2->libererCasesVides(carte);
	        	joueur2->miseAJourDonnees(&textes[44],&textes[42]);
	        }

			if(tour==tourj1){
				glPushMatrix();
					drawRect2(GL_VIEW_SIZE*RATIO/2./3.,GL_VIEW_SIZE/2.,((GL_VIEW_SIZE*RATIO/2./3.+RATIO*GL_VIEW_SIZE/2.)/4.), 0.666,0,0,255,0.2);
				glPopMatrix();
			}

			if(tour==tourj2){
				glPushMatrix();
					glTranslatef(((GL_VIEW_SIZE*RATIO/2./3.+RATIO*GL_VIEW_SIZE/2.)/4.), 0., 0.);
					drawRect2(GL_VIEW_SIZE*RATIO/2./3.,GL_VIEW_SIZE/2.,((GL_VIEW_SIZE*RATIO/2./3.+RATIO*GL_VIEW_SIZE/2.)/4.), 0.666,255,0,0,0.2);
				glPopMatrix();
			}
    	}
		menuJoueurs->dessinerBoutons();

		carte->dessinerCarte();
		//chemin->brillerleAStar(&test);
		dessinerTexte(textes,menuChoix);
    dessinerTexte(textes,menuUnite);
    dessinerTexte(textes,menuJoueurs);

    if(quefeje==VASEDEPLACER)
    {
      if(tour==tourj1)
      {
        for(int i=0; i<=(uniteActuelle->getMobilite()); i++)
        {
          for(int j=0; j<=(uniteActuelle->getMobilite()); j++)
          {
            if((uniteActuelle->getX()+i)<carte->getTailleLargeur() && (uniteActuelle->getY()+j)<carte->getTailleHauteur() && uniteActuelle->verifDistance(uniteActuelle->getX(),uniteActuelle->getY(),uniteActuelle->getX()+i,uniteActuelle->getY()+j) && !(carte->caseSelectionnee(uniteActuelle->getX()+i,uniteActuelle->getY()+j)->estObstacle()) && !(carte->caseSelectionnee(uniteActuelle->getX()+i,uniteActuelle->getY()+j)->occupee()))
            {
              carte->caseSelectionnee(uniteActuelle->getX()+i,uniteActuelle->getY()+j)->briller(0,0,255,0.2);
            }
            if((uniteActuelle->getX()-i)>=0 && (uniteActuelle->getY()+j)<carte->getTailleHauteur() && uniteActuelle->verifDistance(uniteActuelle->getX(),uniteActuelle->getY(),uniteActuelle->getX()-i,uniteActuelle->getY()+j) && !(carte->caseSelectionnee(uniteActuelle->getX()-i,uniteActuelle->getY()+j)->estObstacle()) && !(carte->caseSelectionnee(uniteActuelle->getX()-i,uniteActuelle->getY()+j)->occupee()))
            {
              carte->caseSelectionnee(uniteActuelle->getX()-i,uniteActuelle->getY()+j)->briller(0,0,255,0.2);
            }
            if((uniteActuelle->getX()+i)<carte->getTailleLargeur() && (uniteActuelle->getY()-j)>=0 && uniteActuelle->verifDistance(uniteActuelle->getX(),uniteActuelle->getY(),uniteActuelle->getX()+i,uniteActuelle->getY()-j) && !(carte->caseSelectionnee(uniteActuelle->getX()+i,uniteActuelle->getY()-j)->estObstacle()) && !(carte->caseSelectionnee(uniteActuelle->getX()+i,uniteActuelle->getY()-j)->occupee()))
            {
              carte->caseSelectionnee(uniteActuelle->getX()+i,uniteActuelle->getY()-j)->briller(0,0,255,0.2);
            }
            if((uniteActuelle->getX()-i)>=0 && (uniteActuelle->getY()-j)>=0 && uniteActuelle->verifDistance(uniteActuelle->getX(),uniteActuelle->getY(),uniteActuelle->getX()+i,uniteActuelle->getY()+j) && !(carte->caseSelectionnee(uniteActuelle->getX()-i,uniteActuelle->getY()-j)->estObstacle()) && !(carte->caseSelectionnee(uniteActuelle->getX()-i,uniteActuelle->getY()-j)->occupee()))
            {
              carte->caseSelectionnee(uniteActuelle->getX()-i,uniteActuelle->getY()-j)->briller(0,0,255,0.2);
            }
          }
        }
      }
      if(tour==tourj2)
      {
        for(int i=0; i<=(uniteActuelle->getMobilite()); i++)
        {
          for(int j=0; j<=(uniteActuelle->getMobilite()); j++)
          {
            if((uniteActuelle->getX()+i)<carte->getTailleLargeur() && (uniteActuelle->getY()+j)<carte->getTailleHauteur() && uniteActuelle->verifDistance(uniteActuelle->getX(),uniteActuelle->getY(),uniteActuelle->getX()+i,uniteActuelle->getY()+j) && !(carte->caseSelectionnee(uniteActuelle->getX()+i,uniteActuelle->getY()+j)->estObstacle()) && !(carte->caseSelectionnee(uniteActuelle->getX()+i,uniteActuelle->getY()+j)->occupee()))
            {
              carte->caseSelectionnee(uniteActuelle->getX()+i,uniteActuelle->getY()+j)->briller(255,0,0,0.2);
            }
            if((uniteActuelle->getX()-i)>=0 && (uniteActuelle->getY()+j)<carte->getTailleHauteur() && uniteActuelle->verifDistance(uniteActuelle->getX(),uniteActuelle->getY(),uniteActuelle->getX()-i,uniteActuelle->getY()+j) && !(carte->caseSelectionnee(uniteActuelle->getX()-i,uniteActuelle->getY()+j)->estObstacle()) && !(carte->caseSelectionnee(uniteActuelle->getX()-i,uniteActuelle->getY()+j)->occupee()))
            {
              carte->caseSelectionnee(uniteActuelle->getX()-i,uniteActuelle->getY()+j)->briller(255,0,0,0.2);
            }
            if((uniteActuelle->getX()+i)<carte->getTailleLargeur() && (uniteActuelle->getY()-j)>=0 && uniteActuelle->verifDistance(uniteActuelle->getX(),uniteActuelle->getY(),uniteActuelle->getX()+i,uniteActuelle->getY()-j) && !(carte->caseSelectionnee(uniteActuelle->getX()+i,uniteActuelle->getY()-j)->estObstacle()) && !(carte->caseSelectionnee(uniteActuelle->getX()+i,uniteActuelle->getY()-j)->occupee()))
            {
              carte->caseSelectionnee(uniteActuelle->getX()+i,uniteActuelle->getY()-j)->briller(255,0,0,0.2);
            }
            if((uniteActuelle->getX()-i)>=0 && (uniteActuelle->getY()-j)>=0 && uniteActuelle->verifDistance(uniteActuelle->getX(),uniteActuelle->getY(),uniteActuelle->getX()+i,uniteActuelle->getY()+j) && !(carte->caseSelectionnee(uniteActuelle->getX()-i,uniteActuelle->getY()-j)->estObstacle()) && !(carte->caseSelectionnee(uniteActuelle->getX()-i,uniteActuelle->getY()-j)->occupee()))
            {
              carte->caseSelectionnee(uniteActuelle->getX()-i,uniteActuelle->getY()-j)->briller(255,0,0,0.2);
            }
          }
        }
      }
    }
    if(quefeje==VAATTAQUER)
    {
      if(tour==tourj1)
      {
        for(int i=0; i<=(uniteActuelle->getPortee()); i++)
        {
          for(int j=0; j<=(uniteActuelle->getPortee()); j++)
          {
            if((uniteActuelle->getX()+i)<carte->getTailleLargeur() && (uniteActuelle->getY()+j)<carte->getTailleHauteur() && uniteActuelle->verifPortee(uniteActuelle->getX()+i,uniteActuelle->getY()+j) && !(carte->caseSelectionnee(uniteActuelle->getX()+i,uniteActuelle->getY()+j)->estObstacle()))
            {
              carte->caseSelectionnee(uniteActuelle->getX()+i,uniteActuelle->getY()+j)->briller(255,255,0,0.2);
            }
            if((uniteActuelle->getX()-i)>=0 && (uniteActuelle->getY()+j)<carte->getTailleHauteur() && uniteActuelle->verifPortee(uniteActuelle->getX()-i,uniteActuelle->getY()+j) && !(carte->caseSelectionnee(uniteActuelle->getX()-i,uniteActuelle->getY()+j)->estObstacle()))
            {
              carte->caseSelectionnee(uniteActuelle->getX()-i,uniteActuelle->getY()+j)->briller(255,255,0,0.2);
            }
            if((uniteActuelle->getX()+i)<carte->getTailleLargeur() && (uniteActuelle->getY()-j)>=0 && uniteActuelle->verifPortee(uniteActuelle->getX()+i,uniteActuelle->getY()-j) && !(carte->caseSelectionnee(uniteActuelle->getX()+i,uniteActuelle->getY()-j)->estObstacle()))
            {
              carte->caseSelectionnee(uniteActuelle->getX()+i,uniteActuelle->getY()-j)->briller(255,255,0,0.2);
            }
            if((uniteActuelle->getX()-i)>=0 && (uniteActuelle->getY()-j)>=0 && uniteActuelle->verifPortee(uniteActuelle->getX()+i,uniteActuelle->getY()+j) && !(carte->caseSelectionnee(uniteActuelle->getX()-i,uniteActuelle->getY()-j)->estObstacle()))
            {
              carte->caseSelectionnee(uniteActuelle->getX()-i,uniteActuelle->getY()-j)->briller(255,255,0,0.2);
            }
          }
        }
      }
      if(tour==tourj2)
      {
        for(int i=0; i<=(uniteActuelle->getPortee()); i++)
        {
          for(int j=0; j<=(uniteActuelle->getPortee()); j++)
          {
            if((uniteActuelle->getX()+i)<carte->getTailleLargeur() && (uniteActuelle->getY()+j)<carte->getTailleHauteur() && uniteActuelle->verifPortee(uniteActuelle->getX()+i,uniteActuelle->getY()+j) && !(carte->caseSelectionnee(uniteActuelle->getX()+i,uniteActuelle->getY()+j)->estObstacle()))
            {
              carte->caseSelectionnee(uniteActuelle->getX()+i,uniteActuelle->getY()+j)->briller(255,255,0,0.2);
            }
            if((uniteActuelle->getX()-i)>=0 && (uniteActuelle->getY()+j)<carte->getTailleHauteur() && uniteActuelle->verifPortee(uniteActuelle->getX()-i,uniteActuelle->getY()+j) && !(carte->caseSelectionnee(uniteActuelle->getX()-i,uniteActuelle->getY()+j)->estObstacle()))
            {
              carte->caseSelectionnee(uniteActuelle->getX()-i,uniteActuelle->getY()+j)->briller(255,255,0,0.2);
            }
            if((uniteActuelle->getX()+i)<carte->getTailleLargeur() && (uniteActuelle->getY()-j)>=0 && uniteActuelle->verifPortee(uniteActuelle->getX()+i,uniteActuelle->getY()-j) && !(carte->caseSelectionnee(uniteActuelle->getX()+i,uniteActuelle->getY()-j)->estObstacle()))
            {
              carte->caseSelectionnee(uniteActuelle->getX()+i,uniteActuelle->getY()-j)->briller(255,255,0,0.2);
            }
            if((uniteActuelle->getX()-i)>=0 && (uniteActuelle->getY()-j)>=0 && uniteActuelle->verifPortee(uniteActuelle->getX()+i,uniteActuelle->getY()+j) && !(carte->caseSelectionnee(uniteActuelle->getX()-i,uniteActuelle->getY()-j)->estObstacle()))
            {
              carte->caseSelectionnee(uniteActuelle->getX()-i,uniteActuelle->getY()-j)->briller(255,255,0,0.2);
            }
          }
        }
      }
    }

        if(debutJeu || quefeje==ENACHAT)
        {
        	if(!placement && quefeje!=ENACHAT)
        	{
        		drawRect(0,0,GL_VIEW_SIZE*RATIO,GL_VIEW_SIZE,0,0,0,0.7);
	        	menuDebutJeu->dessinerFond();
	        	menuDebutJeu->dessinerBoutons();
				if(tour==tourj1)
				{
	        		textes[63]->dessineTexte(menuDebutJeu->boutonGetX(1),menuDebutJeu->boutonGetY(1)+0.15);
	        	}
				if(tour==tourj2)
				{
    				textes[64]->dessineTexte(menuDebutJeu->boutonGetX(1),menuDebutJeu->boutonGetY(1)+0.15);
    			}
        	}
        	else
        	{
				if(tour==tourj1)
				{
					carte->dessinerZone(1);
				}

				if(tour==tourj2)
				{
					carte->dessinerZone(2);
				}
			}
        }

        if(!debutJeu)
        {
			/* Test de victoire*/
        	if(contreIA)
        	{
        		if(ordinateur->perdant())
				{
					*vainqueur = 1;
					*loop=5;
				}
				else if(joueur1->perdant())
				{
					*vainqueur = 3;
					*loop=5;
				}
        	}
        	else
        	{
				if(joueur1->perdant())
				{
          			*vainqueur = 2;
					*loop=5;
				}
				else if(joueur2->perdant())
				{
          			*vainqueur = 1;
					*loop=5;
				}
			}
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
		            *px = e.button.x;
		            *py = e.button.y;
		            *px=-0.5+(*px)/surface->w;
		            *py=-0.5+(*py)/surface->h;
		            *px=*px*GL_VIEW_SIZE;
		            *py=*py*GL_VIEW_SIZE*(-1);
		            if(*aspectRatio<1)
		            {
		                *py=*py/(*aspectRatio);
		            }
		            else
		            {
		                *px=*px*(*aspectRatio);
		            }
		            if(debutJeu)
		            {
		            	if(!contreIA)
			            {
			            	if(!placement)
			            	{
			            		if(tour==tourj1)
			            		{
			            			menuDebutJeu->quelBoutonMenuJeu(*px,*py,&joueur1,&nouvelleUnite,nbInitJoueur,loop,&tour,&placement,textes);
		        				}
		        				else if(tour==tourj2)
		        				{
		        					menuDebutJeu->quelBoutonMenuJeu(*px,*py,&joueur2,&nouvelleUnite,nbInitJoueur,loop,&tour,&placement,textes);
		        				}
			            	}
			            	else
			            	{
			          			float x=*px+RATIO*GL_VIEW_SIZE/2.;
								float y=-(*py-GL_VIEW_SIZE/2.);
								x=x/((2./3.)*RATIO*GL_VIEW_SIZE);
								y=y/((4./9.)*GL_VIEW_SIZE*RATIO);
								if(!(x<0 || x>1 || y<0 || y>1))
								{
									int cx=carte->getXCase(x);
									int cy=carte->getYCase(y);
									nouvelleUnite->chargerIcone();

									if(!(carte->caseSelectionnee(cx,cy)->occupee()))
			            			{
										if(tour==tourj1)
				            			{
			            					if(carte->dansZone(cx,cy,1))
			            					{
				            					carte->occuperCase(cx,cy,nouvelleUnite);
												placement=false;
												tour=tourj2;
												nbUnite++;
											}
										}
										else if(tour==tourj2)
										{
											if(carte->dansZone(cx,cy,2))
											{
												carte->occuperCase(cx,cy,nouvelleUnite);
												placement=false;
												tour=tourj1;
												nbUnite++;
											}
										}
									}
								}
					            if(nbUnite>=2*nbInitJoueur)
					            {
					            	debutJeu=false;
					            	joueur1->chargerLesIcones(nbInitJoueur);
					            	joueur2->chargerLesIcones(nbInitJoueur);
					            }
				            }
				        }
			        	else
			        	{
			        		if(!placement)
			            	{
			            		menuDebutJeu->quelBoutonMenuJeu(*px,*py,&joueur1,&nouvelleUnite,nbInitJoueur,loop,&tour,&placement,textes);
			            	}
			            	else
			            	{
			          			float x=*px+RATIO*GL_VIEW_SIZE/2.;
								float y=-(*py-GL_VIEW_SIZE/2.);
								x=x/((2./3.)*RATIO*GL_VIEW_SIZE);
								y=y/((4./9.)*GL_VIEW_SIZE*RATIO);

								if(!(x<0 || x>1 || y<0 || y>1))
								{
									int cx=carte->getXCase(x);
									int cy=carte->getYCase(y);
									nouvelleUnite->chargerIcone();
									if(!(carte->caseSelectionnee(cx,cy)->occupee()))
			            			{
		            					if(carte->dansZone(cx,cy,1))
		            					{
			            					carte->occuperCase(cx,cy,nouvelleUnite);
											placement=false;
											nbUnite++;
										}
									}
								}
					            if(nbUnite>=nbInitJoueur)
					            {
					            	debutJeu=false;
					            	joueur1->chargerLesIcones(nbInitJoueur);
					            	for(int i=0;i<nbInitJoueur;i++)
					            	{
					            		char car;
					            		switch(i%5)
					            		{
					            			case 0 :
					            				car = 't';
					            				break;
					            			case 1 :
					            				car = 'a';
					            				break;
					            			case 2 :
					            				car = 'g';
					            				break;
					            			case 3 :
					            				car = 'n';
					            				break;
					            			case 4 :
					            				car = 'b';
					            				break;
					            		}
					            		int x=carte->getTailleLargeur()-1;
					            		int y=0;
					            		while(!carte->caseDisponible(x,y))
					            		{
					            			if(y<carte->getTailleHauteur()-1)
					            			{
					            				y++;
					            			}
					            			else
					            			{
					            				x--;
					            				y=0;
					            			}
					            		}
					            		carte->occuperCase(x,y,ordinateur->creationUnite(car));
					            	}
					            	ordinateur->chargerLesIcones(0);
					            }
				            }
				        }
		            }
		            else
		            {
			            if(!contreIA)
			            {
				            if(tour==tourj1)
				            {
				            	if(quefeje==ENACHAT)
				            	{
				            		float x=*px+RATIO*GL_VIEW_SIZE/2.;
									float y=-(*py-GL_VIEW_SIZE/2.);
									x=x/((2./3.)*RATIO*GL_VIEW_SIZE);
									y=y/((4./9.)*GL_VIEW_SIZE*RATIO);
									if(!(x<0 || x>1 || y<0 || y>1))
									{
										int cx=carte->getXCase(x);
										int cy=carte->getYCase(y);
										//nouvelleUnite->chargerIcone();

										if(!(carte->caseSelectionnee(cx,cy)->occupee()))
				            			{
			            					if(carte->dansZone(cx,cy,1))
			            					{
				            					carte->occuperCase(cx,cy,uniteActuelle);
												tour=tourj2;
												quefeje=VASELECTIONNER;
											}
										}
									}
				            	}
				            	menuChoix->quelBoutonJeu(*px,*py,&cxs,&cys,&cxd,&cyd,&cxa,&cya,carte,&joueur1,&uniteActuelle,&uniteEnnemie,&tour,&idNouveauMenu,&action,textes,&menuUnite,&quefeje);
								menuChoix->libererEspace();
								menuChoix = new Menu(idNouveauMenu);
							    menuChoix->chargerFond();
							    menuChoix->chargerBoutons();
							    if(joueur1->tourFini())
							    {
							    	joueur1->finTour();
							    	menuChoix->libererEspace();
									menuChoix = new Menu(2);
								    menuChoix->chargerFond();
								    menuChoix->chargerBoutons();
							    	tour=tourj2;
                    				quefeje=VASELECTIONNER;
							    }
				            }
				            else if(tour==tourj2)
				            {
				            	if(quefeje==ENACHAT)
				            	{
				            		float x=*px+RATIO*GL_VIEW_SIZE/2.;
									float y=-(*py-GL_VIEW_SIZE/2.);
									x=x/((2./3.)*RATIO*GL_VIEW_SIZE);
									y=y/((4./9.)*GL_VIEW_SIZE*RATIO);
									if(!(x<0 || x>1 || y<0 || y>1))
									{
										int cx=carte->getXCase(x);
										int cy=carte->getYCase(y);
										//nouvelleUnite->chargerIcone();

										if(!(carte->caseSelectionnee(cx,cy)->occupee()))
				            			{
			            					if(carte->dansZone(cx,cy,1))
			            					{
				            					carte->occuperCase(cx,cy,uniteActuelle);
												tour=tourj1;
												quefeje=VASELECTIONNER;
											}
										}
									}
				            	}
				            	menuChoix->quelBoutonJeu(*px,*py,&cxs,&cys,&cxd,&cyd,&cxa,&cya,carte,&joueur2,&uniteActuelle,&uniteEnnemie,&tour,&idNouveauMenu,&action,textes,&menuUnite,&quefeje);
								menuChoix->libererEspace();
								menuChoix = new Menu(idNouveauMenu);
							    menuChoix->chargerFond();
							    menuChoix->chargerBoutons();
							    if(joueur2->tourFini())
							    {
							    	joueur2->finTour();
							    	menuChoix->libererEspace();
									menuChoix = new Menu(2);
								    menuChoix->chargerFond();
								    menuChoix->chargerBoutons();
							    	tour=tourj1;
                    				quefeje=VASELECTIONNER;
							    }
				            }
			        	}
			        	else
			        	{
			        		if(tour==tourj1)
				            {
				            	if(quefeje==ENACHAT)
				            	{
				            		float x=*px+RATIO*GL_VIEW_SIZE/2.;
									float y=-(*py-GL_VIEW_SIZE/2.);
									x=x/((2./3.)*RATIO*GL_VIEW_SIZE);
									y=y/((4./9.)*GL_VIEW_SIZE*RATIO);
									if(!(x<0 || x>1 || y<0 || y>1))
									{
										int cx=carte->getXCase(x);
										int cy=carte->getYCase(y);
										//nouvelleUnite->chargerIcone();

										if(!(carte->caseSelectionnee(cx,cy)->occupee()))
				            			{
			            					if(carte->dansZone(cx,cy,1))
			            					{
				            					carte->occuperCase(cx,cy,uniteActuelle);
												tour=tourj2;
												quefeje=VASELECTIONNER;
											}
										}
									}
				            	}
				            	menuChoix->quelBoutonJeu(*px,*py,&cxs,&cys,&cxd,&cyd,&cxa,&cya,carte,&joueur1,&uniteActuelle,&uniteEnnemie,&tour,&idNouveauMenu,&action,textes,&menuUnite,&quefeje);
								menuChoix->libererEspace();
								menuChoix = new Menu(idNouveauMenu);
							    menuChoix->chargerFond();
							    menuChoix->chargerBoutons();
							    if(joueur1->tourFini())
							    {
							    	joueur1->finTour();
							    	menuChoix->libererEspace();
									menuChoix = new Menu(2);
								    menuChoix->chargerFond();
								    menuChoix->chargerBoutons();
							    	tour=tourj2;
                    				quefeje=VASELECTIONNER;
							    }
				            }
			        	}

			            menuJoueurs->quelBoutonMenu(*px,*py,loop,&contreIA);
		            }

		        /* Touche clavier */
		        case SDL_KEYDOWN:
		            //printf("touche pressee (code = %d)\n", e.key.keysym.sym);
		            break;

		        default:
		            break;
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
    joueur1->libererEspaceUnites();
    joueur2->libererEspaceUnites();
    ordinateur->libererEspaceUnites();

    carte->libererEspaceTexture();

    menuChoix->libererEspace();
    menuUnite->libererEspace();
    menuJoueurs->libererEspace();
    menuDebutJeu->libererEspace();
}
