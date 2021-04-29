#ifndef TEXTURES_HPP_INCLUDED
#define TEXTURES_HPP_INCLUDED

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <SDL/SDL_ttf.h>

#include <iostream>
#include <string>

class Textures
{
	public:
		Textures();
		Textures(SDL_Surface* surface, GLuint* texture);
		void chargeTexte(const char* message,int taille,Uint8 b,Uint8 g,Uint8 r);
		void dessineTexte(float x, float y);
		void libererTexte();
		void libererEspace(GLuint* texture);
	private:
		GLuint m_idTexture;
		SDL_Surface* m_surface;
		TTF_Font* font = NULL;
};

#endif