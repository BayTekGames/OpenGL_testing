#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include <stdio.h>
//#include "lodepng.h"
#include "Texture.h"

const int MAX_DICE_SIDES = 6;
const int MAX_FILENAME_SIZE = 64;

int main() {

	// create the window
    sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default,
            sf::ContextSettings(32));
    window.setVerticalSyncEnabled(true);

    GLuint texture[MAX_DICE_SIDES];

    for( int ii = 0; ii < MAX_DICE_SIDES; ++ii )
    {
    	char szImageName[MAX_FILENAME_SIZE];
    	sprintf( szImageName, "media/graphics/fake%d.png", (ii+1) );
    	texture[ii] = LoadTexture( szImageName );
    	printf( "OpenGL Image Handle (%d)\n", texture[ii] );
    }

    // run the main loop
    bool running = true;

    GLdouble h = 0.0d;
    GLdouble v = 0.0d;
    GLdouble l = 0.0d;

    while (running) {
        // handle events
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                // end the program
                running = false;
            }
            else if (event.type == sf::Event::Resized)
            {
                // adjust the viewport when the window is resized
                glViewport(0, 0, event.size.width, event.size.height);
            }

            if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
            	running = false;
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Right))
				v+=1.0d;
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Left))
				v-=1.0d;
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Up))
				h+=1.0d;
			if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Down))
				h-=1.0d;
        }

//        //glEnable( GL_CULL_FACE );
//        //glCullFace( GL_FRONT );
//        glClearColor(0, 0, 0, 0);
//        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
//        glEnable(GL_DEPTH_TEST);
//        glEnable(GL_TEXTURE_2D);
//        glLoadIdentity();
//
//        glRotated(l,0.0d,0.0d,0.2d);
//        glRotated(h,0.2d,0.0d,0.0d);
//        glRotated(v,0.0d,0.2d,0.0d);
//        glBegin(GL_QUADS);
//
//        glEnable( GL_CULL_FACE );
//        glFrontFace(GL_CW);
//
//        //back
//        //glColor3f(1.0f,0.0f,0.0f); //red
//        glBindTexture(GL_TEXTURE_2D, texture[4] );
//        glTexCoord2f(0.0f, 0.0f);
//        glVertex3f(-0.2f,0.2f,0.2f); //top left
//        glTexCoord2f(1.0f, 0.0f);
//        glVertex3f(0.2f,0.2f,0.2f); //top right
//        glTexCoord2f(1.0f, 1.0f);
//        glVertex3f(0.2f,-0.2f,0.2f); //bottom right
//        glTexCoord2f(0.0f, 1.0f);
//        glVertex3f(-0.2f,-0.2f,0.2f); //bottom left
//
//        //bottom
//        //glColor3f(0.0f,1.0f,0.0f); //green
//        glBindTexture(GL_TEXTURE_2D, texture[4]);
//        glTexCoord2f(0.0f, 0.0f);
//        glVertex3f(0.2f,-0.2f,0.2f); //back right
//        glTexCoord2f(1.0f, 0.0f);
//        glVertex3f(-0.2f,-0.2f,0.2f); //back left
//        glTexCoord2f(1.0f, 1.0f);
//        glVertex3f(-0.2f,-0.2f,-0.2f); //front left
//        glTexCoord2f(0.0f, 1.0f);
//        glVertex3f(0.2f,-0.2f,-0.2f); //front right
//
//        //front
//        //glColor3f(0.0f,0.0f,1.0f); //blue
//        glBindTexture(GL_TEXTURE_2D, texture[4]);
//        glTexCoord2f(0.0f, 0.0f);
//        glVertex3f(0.2f,-0.2f,-0.2f); //bottom right
//        glTexCoord2f(1.0f, 0.0f);
//        glVertex3f(-0.2f,-0.2f,-0.2f); //bottom left
//        glTexCoord2f(1.0f, 1.0f);
//        glVertex3f(-0.2f,0.2f,-0.2f); //top left
//        glTexCoord2f(0.0f, 1.0f);
//        glVertex3f(0.2f,0.2f,-0.2f); //top right
//
//        //top
//        //glColor3f(1.0f,1.0f,0.0f); //yellow
//        glBindTexture(GL_TEXTURE_2D, texture[4]);
//        glTexCoord2f(0.0f, 0.0f);
//        glVertex3f(0.2f,0.2f,-0.2f); //front right
//        glTexCoord2f(1.0f, 0.0f);
//        glVertex3f(-0.2f,0.2f,-0.2f); //front left
//        glTexCoord2f(1.0f, 1.0f);
//        glVertex3f(-0.2f,0.2f,0.2f); //back left
//        glTexCoord2f(0.0f, 1.0f);
//        glVertex3f(0.2f,0.2f,0.2f); //back right
//
//        //left
//        //glColor3f(0.0f,1.0f,1.0f); //pink
//        glBindTexture(GL_TEXTURE_2D, texture[4]);
//        glTexCoord2f(0.0f, 0.0f);
//        glVertex3f(-0.2f,-0.2f,-0.2f); //bottom front
//        glTexCoord2f(1.0f, 0.0f);
//        glVertex3f(-0.2f,-0.2f,0.2f); //bottom back
//        glTexCoord2f(1.0f, 1.0f);
//        glVertex3f(-0.2f,0.2f,0.2f); //top back
//        glTexCoord2f(0.0f, 1.0f);
//        glVertex3f(-0.2f,0.2f,-0.2f); //top front
//
//        //right
//        //glColor3f(1.0f,0.0f,1.0f); //cyan
//        glBindTexture(GL_TEXTURE_2D, texture[4]);
//        glTexCoord2f(0.0f, 0.0f);
//        glVertex3f(0.2f,-0.2f,-0.2f); //bottom front
//        glTexCoord2f(1.0f, 0.0f);
//        glVertex3f(0.2f,-0.2f,0.2f); //bottom back
//        glTexCoord2f(1.0f, 1.0f);
//        glVertex3f(0.2f,0.2f,0.2f); //top back
//        glTexCoord2f(0.0f, 1.0f);
//        glVertex3f(0.2f,0.2f,-0.2f); //top front
//
//
//       glDisable( GL_CULL_FACE );
//       glEnd();

        DrawDice(texture, h, v, l );

       // end the current frame (internally swaps the front and back buffers)
       window.display();
    }

    // release resources...

    return 0;
}
