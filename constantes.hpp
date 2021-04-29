#ifndef CONSTANTES_HPP_INCLUDED
#define CONSTANTES_HPP_INCLUDED

#include <iostream>
#include <string>

/* Dimensions initiales et titre de la fenetre */
static const unsigned int WINDOW_WIDTH = 1850;
static const unsigned int WINDOW_HEIGHT = 1020;
static const char WINDOW_TITLE[] = "IMACWARS 2.0";

static const float RATIO=(float)WINDOW_WIDTH/(float)WINDOW_HEIGHT;

/* Espace fenetre virtuelle */
static const float GL_VIEW_SIZE = 2.;

/* Nombre de bits par pixel de la fenetre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

static const int NB_BOUTONS_MAX=6;

enum Actions{
	DEPLACER,
	ATTAQUER
};

enum Quefeje{
	VASEDEPLACER,
	VAATTAQUER,
	VASELECTIONNER,
	ENACHAT
};

enum Tour{
	tourj1,
	tourj2
};

#endif
