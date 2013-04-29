
#include "Texture.h"
#include <SFML/OpenGL.hpp>
#include <iostream>
#include <stdio.h>
#include "lodepng.h"
#include <math.h>
#include <stdlib.h>


// Lighting data
GLfloat lightAmbient[] = { 0.2f, 0.2f, 0.2f, 1.0f };
GLfloat lightDiffuse[] = { 0.7f, 0.7f, 0.7f, 1.0f };
GLfloat lightSpecular[] = { 0.9f, 0.9f, 0.9f };
GLfloat materialColor[] = { 0.8f, 0.0f, 0.0f };
GLfloat vLightPos[] = { -80.0f, 120.0f, 100.0f, 0.0f };
GLfloat ground[3][3] = { { 0.0f, -25.0f, 0.0f },
                        { 10.0f, -25.0f, 0.0f },
                        { 10.0f, -25.0f, -10.0f } };

// implementation of how to load a png and get the handle from OpenGL
unsigned int LoadTexture( char *szFile )
{
	std::vector<unsigned char> image;
	unsigned int retHandle = -1;
	unsigned width, height;

	// Black background
	glClearColor(0.6f, 0.0f, 1.0f, 1.f );

    glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glGenTextures( 1, &retHandle );

	lodepng::decode(image, width, height, szFile);

	// This is the "give your application bugs" code
	// RJD $$$$
	//// Texture size must be power of two for the primitive OpenGL version this is written for. Find next power of two.
	//size_t u2 = 1; while(u2 < width) u2 *= 2;
	//size_t v2 = 1; while(v2 < height) v2 *= 2;
	//// Ratio for power of two version compared to actual version, to render the non power of two image with proper size.
	//double u3 = (double)width / u2;
	//double v3 = (double)height / v2;

	//// Make power of two version of the image.
	//std::vector<unsigned char> image2(u2 * v2 * 4);
	//for(size_t y = 0; y < height; y++)
	//for(size_t x = 0; x < width; x++)
	//for(size_t c = 0; c < 4; c++)
	//{
	//	image2[4 * u2 * y + 4 * x + c] = image[4 * width * y + 4 * x + c];
	//}

	glBindTexture(GL_TEXTURE_2D, retHandle );

	//GL_CLAMP_TO_BORDER
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image[0]);

	// for full bug effect, you must add this line and comment out line above...
	// RJD $$$$
	//glTexImage2D(GL_TEXTURE_2D, 0, 4, u2, v2, 0, GL_RGBA, GL_UNSIGNED_BYTE, &image2[0]);

	return retHandle;
}

void DrawDice( unsigned int *textures, double h, double v, double l )
{
	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);

	glPushMatrix();

    	glRotated(l,0.0d,0.0d,0.2d);
    	glRotated(h,0.2d,0.0d,0.0d);
    	glRotated(v,0.0d,0.2d,0.0d);

		glColor3ub(255,255,255);
		glEnable(GL_TEXTURE_2D);

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);
		glEnable(GL_COLOR_MATERIAL);

		glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
		glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glMaterialfv(GL_FRONT, GL_SPECULAR,lightSpecular);
		glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, materialColor);
		glMateriali(GL_FRONT, GL_SHININESS,128);

		//back
		//glColor3f(1.0f,0.0f,0.0f); //red
		glBindTexture(GL_TEXTURE_2D, textures[0] );
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-0.2f,0.2f,0.2f); //top left
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(0.2f,0.2f,0.2f); //top right
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(0.2f,-0.2f,0.2f); //bottom right
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-0.2f,-0.2f,0.2f); //bottom left
		glEnd();

		//bottom
		//glColor3f(0.0f,1.0f,0.0f); //green
		glBindTexture(GL_TEXTURE_2D, textures[1]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(0.2f,-0.2f,0.2f); //back right
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(-0.2f,-0.2f,0.2f); //back left
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(-0.2f,-0.2f,-0.2f); //front left
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(0.2f,-0.2f,-0.2f); //front right
		glEnd();

		//front
		//glColor3f(0.0f,0.0f,1.0f); //blue
		glBindTexture(GL_TEXTURE_2D, textures[2]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(0.2f,-0.2f,-0.2f); //bottom right
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(-0.2f,-0.2f,-0.2f); //bottom left
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(-0.2f,0.2f,-0.2f); //top left
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(0.2f,0.2f,-0.2f); //top right
		glEnd();

		//top
		//glColor3f(1.0f,1.0f,0.0f); //yellow
		glBindTexture(GL_TEXTURE_2D, textures[3]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(0.2f,0.2f,-0.2f); //front right
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(-0.2f,0.2f,-0.2f); //front left
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(-0.2f,0.2f,0.2f); //back left
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(0.2f,0.2f,0.2f); //back right
		glEnd();

		//left
		//glColor3f(0.0f,1.0f,1.0f); //pink
		glBindTexture(GL_TEXTURE_2D, textures[4]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(-0.2f,-0.2f,-0.2f); //bottom front
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(-0.2f,-0.2f,0.2f); //bottom back
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(-0.2f,0.2f,0.2f); //top back
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(-0.2f,0.2f,-0.2f); //top front
		glEnd();

		//right
		//glColor3f(1.0f,0.0f,1.0f); //cyan
		glBindTexture(GL_TEXTURE_2D, textures[5]);
		glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(0.2f,-0.2f,-0.2f); //bottom front
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(0.2f,-0.2f,0.2f); //bottom back
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(0.2f,0.2f,0.2f); //top back
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(0.2f,0.2f,-0.2f); //top front Front Face (before rotation)
		glEnd();

	glPopMatrix();

	// Disable lighting, we'll just draw the shadow as black
	glDisable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	glPushMatrix();

		glTranslatef(-10.0f, 0.0f, 10.0f);

		// Set drawing color to Black
		glColor3f(0.0f, 0.0f, 0.0f);

	glPopMatrix();
}
