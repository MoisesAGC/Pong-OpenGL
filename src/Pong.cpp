#include <GL/glut.h>
#include <math.h>

// Dimensiones de la ventana
const int Ancho = 800;
const int Altura = 600;

// Dimensiones de las paletas
const float AnchoPaleta = 10.0f;
const float AltoPaleta = 80.0f;

// Posiciones iniciales de los jugadores y el balón
float jugador1 = 0.0f;
float jugador2 = 0.0f;
float PelotitaX = 0.0f, PelotitaY = 0.0f;

// Función para dibujar un jugador
void dibujarJugador(float x, float y, float ancho, float alto, float r, float g, float b) {
    glPushMatrix();
    glTranslatef(x, y, 0);
    glColor3f(r, g, b);
    glBegin(GL_QUADS);
        glVertex2f(-ancho / 2, -alto / 2);
        glVertex2f(ancho / 2, -alto / 2);
        glVertex2f(ancho / 2, alto / 2);
        glVertex2f(-ancho / 2, alto / 2);
    glEnd();
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Dibujar jugador 1
    dibujarJugador(-Ancho / 2 + 20, jugador1, AnchoPaleta, AltoPaleta, 0.0f, 0.0f, 1.0f);
    
    // Dibujar jugador 2
    dibujarJugador(Ancho / 2 - 20, jugador2, AnchoPaleta, AltoPaleta, 1.0f, 0.0f, 0.0f);

    // Dibujar balón
    glPushMatrix();
    glTranslatef(PelotitaX, PelotitaY, 0);
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(-5, -5);
        glVertex2f(5, -5);
        glVertex2f(5, 5);
        glVertex2f(-5, 5);
    glEnd();
    glPopMatrix();

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(Ancho, Altura);
    glutCreateWindow("Pong");

    glViewport(0, 0, Ancho, Altura);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-Ancho / 2, Ancho / 2, -Altura / 2, Altura / 2);
    glMatrixMode(GL_MODELVIEW);

    glClearColor(0.0, 0.0, 0.0, 1.0);

    glutDisplayFunc(display);

    glutMainLoop();
    return 0;
}
