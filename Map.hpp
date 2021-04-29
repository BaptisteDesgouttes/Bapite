#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <iostream>
#include <string>

class Map
{
public:
	Map(int idMap);
	void chargerTexture();
	void dessinerCarte();
	Case* caseSelectionnee(int j, int i);
	void occuperCase(int j, int i, Unite* unite);
	bool caseDisponible(int x, int y);
	void libererCase(int x, int y);
	void libererEspaceTexture();
	int getXCase(float px);
	int getYCase(float py);
	bool dansZone(int cx, int cy, int idJoueur);
	void dessinerZone(int idJoueur);
	void AStar(Case** depart, Case* destination);
	//void AStarArbre(Case** depart, Case* destination);
	int getTailleLargeur();
	int getTailleHauteur();
private:
	int m_id;
	int m_largeur, m_hauteur; //Nombre de cases en largeur et en hauteur
	int m_nbCases;
	Case** m_tabCases;
	Textures* m_tex;
	GLuint m_idTexture;
	const char* m_icone;
};

#endif
