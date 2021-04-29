#ifndef ORDINATEUR_HPP_INCLUDED
#define ORDINATEUR_HPP_INCLUDED

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <iostream>
#include <string>

class Ordinateur : public Joueur
{
public :
	Ordinateur();
	Ordinateur(int id, int r, int v, int b);
	void setUniteCible(Joueur* joueur);
	void tourOrdi(Unite** uniteActuelle, Case** depart, Map* carte);
private :
	Unite* m_uniteCible;
};

#endif