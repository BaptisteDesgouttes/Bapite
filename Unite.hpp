#ifndef UNITE_HPP_INCLUDED
#define UNITE_HPP_INCLUDED

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include <iostream>
#include <string>

class Unite
{
public:
	Unite();
	Unite(int id, char type);
	void chargerIcone();
	void libererEspace();
	void dessinerUnite(float x,float y,float tailleCase);
	void deplacer(int j, int i);
	bool verifDistance(int prec_x,int prec_y,int nouv_x,int nouv_y);
	bool verifPortee(int son_x,int son_y);
	void attaquer(Unite* ennemi);
	void seFaitAttaquer(Unite* unite, int pv_ennemi, float force_ennemie,bool finAttaque);
	bool estMorte();
	const char* afficherUnite(Textures** type, Textures** j, Textures** pv, Textures** force, Textures** portee, Textures** mob);
	int getMobilite();
	int getPortee();
	bool utilisee();
	void utiliser();
	void desutiliser();
	void mourir();
	int getId();
	int getX();
	int getY();
	int getExiste();
	char getType();
	void afficherConsole();
private:
	int m_id; //id du joueur qui la possède
	int m_existe;
	int m_r, m_v, m_b;
	int m_j, m_i; //Indices de la case que l'unité occupe
	int m_pv;
	float m_force;
	float m_defense;
	int m_portee;
	int m_mobilite;
	int m_cout;
	Textures* m_tex;
	GLuint m_idTexture;
	char m_type;
	char m_typeMouvement;
	int m_efficacite;
	bool m_utilisee;
	const char* m_icone; //Référence du fichier de l'icone de l'unite
};

#endif
