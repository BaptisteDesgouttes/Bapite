#ifndef CASE_HPP_INCLUDED
#define CASE_HPP_INCLUDED

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <iostream>
#include <string>
class Case
{
public:
	Case();
	Case(bool obs,int x,int y,int nbCases);
	// void chargerTexture();
	// void libererEspaceTexture();
	void dessinerCase();
	void occuper(Unite* unite);
	bool occupee();
	void liberer();
	Unite* selectUnite();
	bool dansZone(int idMap, int idJoueur);
	void briller(int r, int v, int b, float a);
	Case* deplacerOrdi(int mob);
	void brillerleAStar(int* i);
	void setVoisins(Case** voisons);
	void setParent(Case* lacase);
	void setNext(Case* lacase);
	Case* getParent();
	int getId();
	int getX();
	int getY();
	bool estObstacle();
private:
	int m_id;
	bool m_obs;
	float m_taille;
	int m_r, m_v, m_b;
	char m_type;
	int m_j,m_i; //Indices de la case
	float m_x,m_y; //Coordonnées en openGL du coin supérieur gauche de la case
	bool m_occupee;
	Unite* m_occupant;
	Case* dessus;
	Case* dessous;
	Case* gauche;
	Case* droite;
	Case* parent;
	Case* next;
	// Textures* m_tex;
	// GLuint m_idTexture;
	// const char* m_icone;
};

#endif