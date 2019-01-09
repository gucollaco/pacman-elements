#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

GLUquadricObj *object;

float angX = 0.0;
float angY = 0.0;
float animation = 0.0;
float aniRate = 0.0;
float transl = 0.0;
float tRate = 0.0;

typedef struct {
    int r;
    int g;
    int b;
    bool isReversed;
}GhostType;

GhostType clyde = {255, 165, 0, false};
GhostType pinky = {255, 105, 180, false};
GhostType inky = {0, 255, 255, false};
GhostType blinky = {255, 0, 0, false};
GhostType reversed = {0, 0, 255, true};

void init() {
    glClearColor(0.2, 0.2, 0.0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    object = gluNewQuadric();

    glOrtho(-10, 10, -10, 10, -10, 10);
    glPushMatrix();
}

void timerFunc(int value) {
    animation += aniRate;
    transl += tRate;
	glutPostRedisplay();
	glutTimerFunc(10, timerFunc, 1);
}

void drawGhost(GhostType ghost) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPushMatrix();
        if(angY == 0 || angY == 180) {
            glTranslatef(transl, 0.0, 0.0);
        } else if(angY == 90 || angY == 270) {
            glTranslatef(0.0, 0.0, transl);
        }
        glRotatef(angX, 1.0, 0.0, 0.0);
        glRotatef(angY, 0.0, 1.0, 0.0);

        //glRotatef(20, 0.0, 1.0, 0.0);
        glPushMatrix();
            glTranslatef(0.0, 2.0, 0.0);
            //ghost body
            glColor3ub(ghost.r, ghost.g, ghost.b);
            glPushMatrix();
                glRotatef(90.0, 1.0, 0.0, 0.0);
                gluSphere(object, 4, 50, 10);
                gluCylinder(object, 4, 4, 6, 50, 10);
            glPopMatrix();
            glPushMatrix();
                glTranslatef(0.0, -6.0, 0.0);
                glRotatef(90.0, 1.0, 0.0, 0.0);
                gluDisk(object, 0, 4, 50, 10);
            glPopMatrix();

            //ghost eyes - white part
            glColor3ub(255, 255, 255);
            glPushMatrix();
                glRotatef(20, 0.0, 1.0, 0.0);
                glTranslatef(2.0, 2.0, 2.0);
                gluSphere(object, 1, 50, 10);
            glPopMatrix();
            glPushMatrix();
                glRotatef(70, 0.0, 1.0, 0.0);
                glTranslatef(2.0, 2.0, 2.0);
                gluSphere(object, 1, 50, 10);
            glPopMatrix();

            if(!ghost.isReversed) {
                //ghost eyes - black part
                glColor3ub(0, 0, 0);
                glPushMatrix();
                    glColor3ub(0, 0, 0);
                    glRotatef(20, 0.0, 1.0, 0.0);
                    glTranslatef(2.4, 2.4, 2.4);
                    gluSphere(object, 0.5, 50, 10);
                glPopMatrix();
                glPushMatrix();
                    glRotatef(70, 0.0, 1.0, 0.0);
                    glTranslatef(2.4, 2.4, 2.4);
                    gluSphere(object, 0.5, 50, 10);
                glPopMatrix();
            }

            //ghost leg - central leg
            glColor3ub(ghost.r, ghost.g, ghost.b);
            glPushMatrix();
                glTranslatef(0.0, -6.0, 0.0);
                glPushMatrix();
                    glRotatef(90, 1.0, 0.0, 0.0);
                    gluCylinder(object, 1, 0.75, 1.5, 50 , 10);
                glPopMatrix();
                glPushMatrix();
                    glTranslatef(0.0, -1.5, 0.0);
                    gluSphere(object, 0.75, 50, 10);
                glPopMatrix();
            glPopMatrix();

            //ghost leg - other legs
            glColor3ub(ghost.r, ghost.g, ghost.b);
            glPushMatrix();
                aniRate = !(ghost.isReversed) ? 1.5 : 3.0;
                glRotatef(animation, 0, 1, 0);
                int i = 0;
                while(i <= 360) {
                    glPushMatrix();
                        glRotatef(-20 + i, 0.0, 1.0, 0.0);
                        glTranslatef(2.975, -6.0, 0.0);
                        glPushMatrix();
                            glRotatef(90, 1.0, 0.0, 0.0);
                            gluCylinder(object, 1, 0.75, 1.5, 50 , 10);
                        glPopMatrix();
                        glPushMatrix();
                            glTranslatef(0.0, -1.5, 0.0);
                            gluSphere(object, 0.75, 50, 10);
                        glPopMatrix();
                    glPopMatrix();
                    i = i + 60;
                }
            glPopMatrix();

        glPopMatrix();

    glPopMatrix();
	glutSwapBuffers();
}

void display() {
    drawGhost(blinky);
}

void keyboard(unsigned char key, int x, int y) {
    switch(key) {
        case 'w' :
        case 'W' :
            if(angY == 0) {
                tRate = 0.1;
            } else if(angY == 180) {
                tRate = -0.1;
            }
            break ;
        case 's' :
        case 'S' :
            if(angY == 0) {
                tRate = -0.1;
            } else if(angY == 180) {
                tRate = 0.1;
            }
            break ;
        case 'e' :
        case 'E' :
            tRate = 0.0;
            break;
        default:
            break;
     }
     glutPostRedisplay() ;
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
           angY += 90;
           if(angY == 360) angY = 0;
           printf("%f\n", fabs(angY));
           break;
        case GLUT_KEY_RIGHT :
           angY -= 90;
           if(angY == -360) angY = 0;
           printf("%f\n", fabs(angY));
           break ;
        default:
           break;
     }
     glutPostRedisplay();
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
    glutCreateWindow("Pacman Ghost");

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
	glutTimerFunc(10, timerFunc, 1);
    init();
    glutMainLoop();
}
