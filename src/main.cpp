#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>

int main() {
    // create the window
    sf::Window window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default,
            sf::ContextSettings(32));
    window.setVerticalSyncEnabled(true);

    // load resources, initialize the OpenGL states, ...

    // run the main loop
    bool running = true;

    GLdouble h = 0.0d;
        GLdouble v = 0.0d;
        GLdouble l = 0.0d;

    while (running) {
        // handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                // end the program
                running = false;
            } else if (event.type == sf::Event::Resized) {
                // adjust the viewport when the window is resized
                glViewport(0, 0, event.size.width, event.size.height);
            }



                                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Right))
                                    v+=10.0d;
                                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Left))
                                    v-=10.0d;
                                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Up))
                                    h+=10.0d;
                                if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Down))
                                    h-=10.0d;
        }

        glClearColor(0, 0, 0, 0);
               glClear(GL_COLOR_BUFFER_BIT);
               glLoadIdentity();



               glRotated(l,0.0d,0.0d,0.2d);
               glRotated(h,0.2d,0.0d,0.0d);
               glRotated(v,0.0d,0.2d,0.0d);
               glBegin(GL_QUADS);
               //back
               glColor3f(1.0f,0.0f,0.0f); //red
               glVertex3f(-0.2f,0.2f,0.2f); //top left
               glVertex3f(0.2f,0.2f,0.2f); //top right
               glVertex3f(0.2f,-0.2f,0.2f); //bottom right
               glVertex3f(-0.2f,-0.2f,0.2f); //bottom left
               //bottom
               glColor3f(0.0f,1.0f,0.0f); //green
               glVertex3f(0.2f,-0.2f,0.2f); //back right
               glVertex3f(-0.2f,-0.2f,0.2f); //back left
               glVertex3f(-0.2f,-0.2f,-0.2f); //front left
               glVertex3f(0.2f,-0.2f,-0.2f); //front right
               //front
               glColor3f(0.0f,0.0f,1.0f); //blue
               glVertex3f(0.2f,-0.2f,-0.2f); //bottom right
               glVertex3f(-0.2f,-0.2f,-0.2f); //bottom left
               glVertex3f(-0.2f,0.2f,-0.2f); //top left
               glVertex3f(0.2f,0.2f,-0.2f); //top right
               //top
               glColor3f(1.0f,1.0f,0.0f); //yellow
               glVertex3f(0.2f,0.2f,-0.2f); //front right
               glVertex3f(-0.2f,0.2f,-0.2f); //front left
               glVertex3f(-0.2f,0.2f,0.2f); //back left
               glVertex3f(0.2f,0.2f,0.2f); //back right
               //left
               glColor3f(0.0f,1.0f,1.0f); //pink
               glVertex3f(-0.2f,-0.2f,-0.2f); //bottom front
               glVertex3f(-0.2f,-0.2f,0.2f); //bottom back
               glVertex3f(-0.2f,0.2f,0.2f); //top back
               glVertex3f(-0.2f,0.2f,-0.2f); //top front
               //right
               glColor3f(1.0f,0.0f,1.0f); //cyan
               glVertex3f(0.2f,-0.2f,-0.2f); //bottom front
               glVertex3f(0.2f,-0.2f,0.2f); //bottom back
               glVertex3f(0.2f,0.2f,0.2f); //top back
               glVertex3f(0.2f,0.2f,-0.2f); //top front

        glEnd();

        // end the current frame (internally swaps the front and back buffers)
        window.display();


    }

    // release resources...

    return 0;
}
