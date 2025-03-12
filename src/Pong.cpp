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
float PelotitaVelX = 3.0f, PelotitaVelY = 3.0f;

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

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': // Mover jugador 1 hacia arriba
            if (jugador1 < (Altura / 2 - AltoPaleta / 2)) jugador1 += 10.0f;
            break;
        case 's': // Mover jugador 1 hacia abajo
            if (jugador1 > -(Altura / 2 - AltoPaleta / 2)) jugador1 -= 10.0f;
            break;
        case 'o': // Mover jugador 2 hacia arriba
            if (jugador2 < (Altura / 2 - AltoPaleta / 2)) jugador2 += 10.0f;
            break;
        case 'l': // Mover jugador 2 hacia abajo
            if (jugador2 > -(Altura / 2 - AltoPaleta / 2)) jugador2 -= 10.0f;
            break;
    }
    glutPostRedisplay();
}

void update(int value) {
    // Mover la pelota
    PelotitaX += PelotitaVelX;
    PelotitaY += PelotitaVelY;

    // Detectar colisión con los bordes superior e inferior
    if (PelotitaY > (Altura / 2 - 5) || PelotitaY < -(Altura / 2 - 5)) {
        PelotitaVelY = -PelotitaVelY; // Invertir la dirección vertical
    }
    // Detectar si la pelota sale por los lados izquierda o derecha 
    if (PelotitaX > (Ancho / 2) || PelotitaX < (-Ancho / 2)) {
        PelotitaX = 0.0f;
        PelotitaY = 0.0f;
    }

    glutPostRedisplay(); // Actualizar la pantalla
    glutTimerFunc(16, update, 0);
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
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, update, 0); 

    glutMainLoop();
    return 0;
}
