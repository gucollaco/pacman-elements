#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

GLUquadricObj *object;

float angX = 0.0;
float angY = 0.0;
float angZ = 0.0;

float animation1 = 0.2;
float animation2 = 0.2;
float aniRate = 1.0;

typedef struct {
    int r;
    int g;
    int b;
}Color;

void init() {
    glClearColor(0.2, 0.0, 0.2, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    object = gluNewQuadric();

    glOrtho(-10, 10, -10, 10, -10, 10);
    glPushMatrix();
}

void drawPellet() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
        glRotatef(angX, 1.0, 0.0, 0.0);
        glRotatef(angY, 0.0, 1.0, 0.0);
        glRotatef(angZ, 0.0, 0.0, 1.0);

        glPushMatrix();
            glColor3ub(255, 200, 0);
            gluSphere(object, 1.5, 50, 10);
        glPopMatrix();
    glPopMatrix();

    glPopMatrix();
	glutSwapBuffers();
}

void display() {
    drawPellet();
}

void transformacoes(int key, int x, int y) {
     switch(key) {
        case GLUT_KEY_UP :
           angX += 15;
           break;
        case GLUT_KEY_DOWN :
           angX -= 15;
           break ;
        case GLUT_KEY_LEFT :
           angY -= 15;
           break;
        case GLUT_KEY_RIGHT :
           angY += 15;
           break ;
        default:
           break;
     }
     glutPostRedisplay() ;
}

void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 'w' :
        case 'W' :
            angZ += 15;
            break ;
        case 's' :
        case 'S' :
            angZ -= 15;
            break ;
        default:
            break;
     }
     glutPostRedisplay() ;
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 2.0f, 2.0f, 2.0f, 2.0f };
const GLfloat light_specular[] = { 2.0f, 2.0f, 2.0f, 2.0f };
const GLfloat light_position[] = { 3.0f, 7.0f, 7.0f, 0.0f };

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Pacman Power Pellet");

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glutDisplayFunc(display);
    glutSpecialFunc(transformacoes);
    glutKeyboardFunc(keyboard);
    init();
    glutMainLoop();
}
