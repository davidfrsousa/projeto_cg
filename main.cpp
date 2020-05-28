#include <gl/glut.h>
#include <GL/GLU.h>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "SOIL.h"

GLfloat randomX[400];
GLfloat randomY[400];

GLfloat zRotated = 0.0;
GLdouble radius = 1;
GLuint texture[5];
GLint list[1];
GLUquadricObj* sphere;

float no_mat[] = { 0.0f, 0.0f, 0.0f, 1.0f };
float mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
float mat_ambient_color[] = { 0.9f, 0.9f, 0.9f, 1.0f };
float mat_diffuse[] = { 0.85f, 0.8f, 0.8f, 1.0f };
float mat_specular[] = { 0.85f, 0.85F, 0.85f, 1.0f };
float no_shininess = 0.0f;
float low_shininess = 5.0f;
float high_shininess = 120.0f;
float mat_emission[] = { 0.3f, 0.2f, 0.2f, 0.0f };

float ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
float diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
float specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
float position[] = { 1.0f, 1.0f, 1.0f, 1.0f };

float model_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };

void desenhaEstrela() {
    glBegin(GL_POINTS);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.2f, 0.0f, 0.0f);
    glVertex3f(0.2f, 0.2f, 0.0f);
    glVertex3f(0.0f, 0.2f, 0.0f);
    glEnd();
}

void display() {

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f(0.8, 0.0, 0.8);

    for (int i = 0; i < 400; i++) {
        glLoadIdentity();
        glTranslatef(randomX[i], randomY[i], -199);
        glRotatef(45, 0, 0, 1);
        glColor3f(1.0f, 1.0f, 0.85f);
        desenhaEstrela();
        glLoadIdentity();
        glTranslatef(-randomX[i], -randomY[i], -199);
        glRotatef(45, 0, 0, 1);
        glColor3f(1.0f, 1.0f, 0.75f);
        desenhaEstrela();
        glLoadIdentity();
        glTranslatef(randomX[i], -randomY[i], -199);
        glRotatef(45, 0, 0, 1);
        glColor3f(1.0f, 1.0f, 0.75f);
        desenhaEstrela();
        glLoadIdentity();
        glTranslatef(-randomX[i], randomY[i], -199);
        glRotatef(45, 0, 0, 1);
        glColor3f(1.0f, 1.0f, 0.75f);
        desenhaEstrela();
    }

    glLoadIdentity();

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_CULL_FACE);

    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, high_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);
    glEnable(GL_LIGHTING);

    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glLoadIdentity();
    glTranslatef(0.0, 0.0, -3.5);
    glRotatef(90, 1.0, 0.0, 0.0);
    glRotatef(170, 0.0, 1.0, 0.0);
    glRotatef(160, 0.0, 0.0, 1.0);
    glRotatef(zRotated, 0.0, 0.0, 1.0);
    gluSphere(sphere, 1, 50, 50);

    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glLoadIdentity();
    glTranslatef(-23, 8, -50);
    glRotatef(90, 1.0, 0.0, 0.0);
    glRotatef(170, 0.0, 1.0, 0.0);
    glRotatef(zRotated, 0.0, 0.0, 1.0);
    gluSphere(sphere, 1, 50, 50);

    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glLoadIdentity();
    glTranslatef(-70, -20, -160);
    glRotatef(90, 1.0, 0.0, 0.0);
    glRotatef(140, 0.0, 1.0, 0.0);
    glRotatef(zRotated, 0.0, 0.0, 1.0);
    gluSphere(sphere, 1, 50, 50);

    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glLoadIdentity();
    glTranslatef(70, -12, -170);
    glRotatef(90, 1.0, 0.0, 0.0);
    glRotatef(30, 0.0, 1.0, 0.0);
    glRotatef(zRotated, 0.0, 0.0, 1.0);
    gluSphere(sphere, 1, 50, 50);

    glBindTexture(GL_TEXTURE_2D, texture[4]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glLoadIdentity();
    glTranslatef(70, 10, -180);
    glRotatef(90, 1.0, 0.0, 0.0);
    glRotatef(160, 0.0, 1.0, 0.0);
    glRotatef(zRotated, 0.0, 0.0, 1.0);
    gluSphere(sphere, 1, 50, 50);

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_CULL_FACE);
    glDisable(GL_LIGHTING);

    glutSwapBuffers();
}

void animacao(int) {
    glutPostRedisplay();
    glutTimerFunc(1000/60,animacao,0);

    if (zRotated < 360) {
        zRotated += 0.8;
    }
    else{
        zRotated = 0.8;
    }
}

void reshape(int x, int y) {
    if (y == 0 || x == 0) return;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(39.0, (GLdouble)x / (GLdouble)y, 0.1, 300.0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, x, y); 
}

void Init() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    texture[0] = SOIL_load_OGL_texture
    (
        "ds82.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );
    if (texture[0] == 0) {
        printf("Erro no carregamento da imagem\n");
    }
    else {
        printf("Sucesso no carregamento da imagem\n");
    }

    texture[1] = SOIL_load_OGL_texture
    (
        "earth_day.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );
    if (texture[1] == 0) {
        printf("Erro no carregamento da imagem\n");
    }
    else {
        printf("Sucesso no carregamento da imagem\n");
    }

    texture[2] = SOIL_load_OGL_texture
    (
        "saturn.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );
    if (texture[2] == 0) {
        printf("Erro no carregamento da imagem\n");
    }
    else {
        printf("Sucesso no carregamento da imagem\n");
    }

    texture[3] = SOIL_load_OGL_texture
    (
        "neptune.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );
    if (texture[3] == 0) {
        printf("Erro no carregamento da imagem\n");
    }
    else {
        printf("Sucesso no carregamento da imagem\n");
    }

    texture[4] = SOIL_load_OGL_texture
    (
        "venus.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );
    if (texture[4] == 0) {
        printf("Erro no carregamento da imagem\n");
    }
    else {
        printf("Sucesso no carregamento da imagem\n");
    }

    glShadeModel(GL_SMOOTH);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    /*glBindTexture(GL_TEXTURE_2D, texture[0]);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glEnable(GL_BLEND);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //glEnable(GL_CULL_FACE);

    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);*/

    //glNewList(list[0], GL_COMPILE);

    sphere = gluNewQuadric();
    gluQuadricDrawStyle(sphere, GLU_FILL);
    gluQuadricNormals(sphere, GLU_SMOOTH);
    gluQuadricOrientation(sphere, GLU_OUTSIDE);
    gluQuadricTexture(sphere, GL_TRUE);

    // glEndList();

    glEnable(GL_LIGHT0);
    //glEnable(GL_LIGHTING);

    for (int i = 0; i < 400; i++) {
        randomX[i] = (float)rand() / 100;
        randomY[i] = (float)rand() / 100;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Projeto Final CG");
    Init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0,animacao,0);
    glutMainLoop();
    return 0;
}
