#ifndef NOEUD_HPP_INCLUDED
#define NOEUD_HPP_INCLUDED

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <iostream>
#include <string>

class Noeud
{
public:
	Noeud();
	Noeud(Case* lacase, float distance);
	void inserer(Noeud* aInserer);
	int hauteur();
	Noeud* plusPetiteDist();
	bool estSeul();
	Case* caseDuNoeud();
	void detruire();
	void detruireFils(float dist);
	Noeud* getRacine();
	void rotationDroite();
	void rotationGauche();
	void rotationGaucheDroite();
	void rotationDroiteGauche();
	void reequilibrer();
	void afficherConsole();
private:
	Case* lacase;
	float distance;
	Noeud* gauche;
	Noeud* droite;
	Noeud* parent;
};

#endif