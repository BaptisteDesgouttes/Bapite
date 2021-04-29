#ifndef JOUEUR_HPP_INCLUDED
#define JOUEUR_HPP_INCLUDED

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <iostream>
#include <string>

class Joueur
{
public:
	Joueur();
	Joueur(int id, int r, int v, int b);
	Unite* creationUnite(char type);
	bool achatUnite(char type,int valeur);
	void chargerLesIcones(int nbUniteDepart);
	void libererEspaceUnites();
	void initialiserNbUnite(int nb);
	//void acheterUnite();
	void ajouterUniteAuTableau(Unite* unite);
	// void organiser();
	// void agir(Menu** menu, Actions* action, float x, float y, int* cxs, int* cys, int* cxd, int* cyd, int* cxa,int* cya, Map* carte, int largeur, int hauteur, Unite* uniteActuelle, int* loop, Tour* tour, int* idNouveauMenu);
	// int getId();
	bool appartient(Unite* unite);
	void libererCasesVides(Map* carte);
	bool tourFini();
	void finTour();
	void miseAJourDonnees(Textures** textunite, Textures** textargent);
	Unite* selectionIA();
	bool perdant();
	int getId();
	void argentFinDeTour();
	void argentUniteTuee();
	void argentSuicide();
	void mortUnite(Map* carte);
	void printTabUnite();
	int returnNbUnites();
	int returnFonds();
protected:
	int m_id;
	int m_r, m_v, m_b;
	int m_fonds;
	int m_nbUnites;
	Unite** m_tabUnites;
	//bool* utilisees;
};

#endif