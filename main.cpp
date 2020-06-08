#include <gl/glut.h>
#include <GL/GLU.h>
#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "SOIL.h"
#define pi 3.14159265359

typedef struct {
    GLfloat x;
    GLfloat y;
    //GLfloat z;
}Estrela;

Estrela estrela[1000];

GLfloat posicaoNaveX[10];
GLfloat posicaoNaveY[10];
GLfloat posicaoNaveZ[10];

GLfloat rotacaoEM = 0.0;
GLfloat rotacaoP = 0.0;
GLuint texture[9];
GLUquadricObj* esfera;
GLUquadricObj* cilindro;

float no_mat[] = { 0.0f, 0.0f, 0.0f, 1.0f };
float mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
float mat_ambient_color[] = { 0.9f, 0.9f, 0.9f, 1.0f };
float mat_diffuse[] = { 0.85f, 0.8f, 0.8f, 1.0f };
float mat_specular[] = { 0.85f, 0.85F, 0.85f, 1.0f };
float high_shininess = 120.0f;
float mat_emission[] = { 0.3f, 0.2f, 0.2f, 0.0f };
float terra_emission[] = {0.03,0.03,0.03f,0.01f};
float nave_emission[] = {0.2f,0.2f,0.2f,0.2f};
float turbina_emission[] = { 0.1f,0.1f,0.1f,0.1f };

float ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
float diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
float specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
float position[] = { 10.0f, 2.0f, 10.0f, 0.0f };//0,0,1,0

float model_ambient[] = { 0.5f, 0.5f, 0.5f, 1.0f };

float alpha = 0.3f;

/*GLfloat v[32][3] = {
{0,4.741, -0.062049},
{0, 0.080271, 0.1148},
{-0.85714, 0.080271, 0.1148},
{-0.98473, -4.741, -0.062049},

{ -0.98473, -4.741, -0.062049 },
{ -0.85714, 0.080271, 0.1148 },
{ -1.7354, 0.080271, -1.6121 },
{ -1.863, -4.741, -1.2523 },

{ -1.863, -4.741, -1.2523 },
{ -1.7354, 0.080271, -1.6121 },
{ -0.85714, 0.080271, -2.3244 },
{ -0.98473, -4.741, -2.3244 },

{ -0.98473, -4.741, -2.3244 },
{ -0.85714, 0.080271, -2.3244 },
{ 0, 0.080271, -2.3244 },
{ 0, -4.741, -2.3244 },

{ 0, -4.741, -2.3244 },
{ 0, 0.080271, -2.3244 },
{ 0.85714, 0.080271, -2.3244 },
{ 0.98473, -4.741, -2.3244 },

{ 0.98473, -4.741, -2.3244 },
{ 0.85714, 0.080271, -2.3244 },
{ 1.7354, 0.080271, -1.6121 },
{ 1.863, -4.741, -1.2523 },

{ 1.863, -4.741, -1.2523 },
{ 1.7354, 0.080271, -1.6121 },
{ 0.85714, 0.080271, 0.1148 },
{ 0.98473, -4.741, -0.062049 },

{ 0.98473, -4.741, -0.062049 },
{ 0.85714, 0.080271, 0.1148 },
{ 0, 0.080271, 0.1148 },
{ 0, -4.741, -0.062049 }
};
*/

//float vn[988][3];

float direcao = 0.0;
float vx = 0.0f, vz = -1.0f;
float x = 0.0f, z = 5.0f, y = 1.0f;

float random(int min, int max) {
    float n = min + rand() / (RAND_MAX / (max - min + 1) + 1);
    return n;
}

/*void calculaNormal(GLfloat v[988][3]) {

    for (int i = 0; i < 247; i++) {
        float va[] = { v[i * 4 + 0][0],v[i * 4 + 0][1],v[i * 4 + 0][2] };
        float vb[] = { v[i * 4 + 1][0],v[i * 4 + 1][1],v[i * 4 + 1][2] };
        float vc[] = { v[i * 4 + 2][0],v[i * 4 + 2][1],v[i * 4 + 2][2] };
        float vd[] = { v[i * 4 + 3][0],v[i * 4 + 3][1],v[i * 4 + 3][2] };

        float v1[] = { vc[0] - va[0],vc[1] - va[1],vc[2] - va[2] };
        float v2[] = { vd[0] - vb[0],vd[1] - vb[1],vd[2] - vb[2] };

        vn[i][0] = (v1[1] * v2[2]) - (v1[2] * v2[1]);
        vn[i][1] = (v2[0] * v1[2]) - (v2[2] * v1[0]);
        vn[i][2] = (v1[0] * v2[1]) - (v1[1] * v2[0]);

        float tamanho = sqrtf((vn[i][0] * vn[i][0]) + (vn[i][1] * vn[i][1]) + (vn[i][2] * vn[i][2]));

        vn[i][0] = vn[i][0] / tamanho;
        vn[i][1] = vn[i][1] / tamanho;
        vn[i][2] = vn[i][2] / tamanho;

    }
}
*/

void Skybox() {
    for (int i = 0; i < 1000; i++) {
        glColor4f(1.0f, 0.8f, 0.85f, alpha);        
        glBegin(GL_POINTS);
        glVertex3f(estrela[i].x, estrela[i].y, -200);
        glVertex3f(estrela[i].y, estrela[i].x, 200);
        glVertex3f(200, estrela[i].y, estrela[i].x);
        glVertex3f(-200, estrela[i].x, estrela[i].y);
        glVertex3f(estrela[i].x, -200, estrela[i].y);
        glVertex3f(estrela[i].y, 200, estrela[i].x);
        glEnd();
    }
}

/*void desenhaNave() {
    glBegin(GL_QUADS);
    v[0][0] = 0.98473; v[0][1] = -4.741; v[0][2] = -0.062049;
    v[1][0] = 0.85714; v[1][1] = 0.080271; v[1][2] = 0.1148;
    v[2][0] = -0.85714; v[2][1] = 0.080271; v[2][2] = 0.1148;
    v[3][0] = -0.98473; v[3][1] = -4.741; v[3][2] = -0.062049;

    glNormal3f(vn[0][0], vn[0][1], vn[0][2]);
    glVertex3f(v[0][0],v[0][1],v[0][2]);
    glVertex3f(v[1][0],v[1][1],v[1][2]);
    glVertex3f(v[2][0],v[2][1],v[2][2]);
    glVertex3f(v[3][0],v[3][1],v[3][2]);

    glNormal3f(vn[1][0], vn[1][1], vn[1][2]);
    glVertex3f(-0.98473, -4.741, -0.062049);
    glVertex3f(-0.85714, 0.080271, 0.1148);
    glVertex3f(-1.7354, 0.080271, -1.6121);
    glVertex3f(-1.863, -4.741, -1.2523);

    glNormal3f(vn[2][0], vn[2][1], vn[2][2]);
    glVertex3f(-1.863, -4.741, -1.2523);
    glVertex3f(-1.7354, 0.080271, -1.6121);
    glVertex3f(-0.85714, 0.080271, -2.3244);
    glVertex3f(-0.98473, -4.741, -2.3244);

    glNormal3f(vn[3][0], vn[3][1], vn[3][2]);
    glVertex3f(-0.98473, -4.741, -2.3244);
    glVertex3f(-0.85714, 0.080271, -2.3244);
    glVertex3f(0.85714, 0.080271, -2.3244);
    glVertex3f(0.98473, -4.741, -2.3244);

    glNormal3f(vn[4][0], vn[4][1], vn[4][2]);
    glVertex3f(0.98473, -4.741, -2.3244);
    glVertex3f(0.85714, 0.080271, -2.3244);
    glVertex3f(1.7354, 0.080271, -1.6121);
    glVertex3f(1.863, -4.741, -1.2523);

    glNormal3f(vn[5][0], vn[5][1], vn[5][2]);
    glVertex3f(1.863, -4.741, -1.2523);
    glVertex3f(1.7354, 0.080271, -1.6121);
    glVertex3f(0.85714, 0.080271, 0.1148);
    glVertex3f(0.98473, -4.741, -0.062049);



    glEnd();
}
*/

void desenhaNave2() {
    glBindTexture(GL_TEXTURE_2D, texture[5]);
    glPushMatrix();
    glRotatef(180, 1, 0, 0);
    gluCylinder(cilindro, 0.2, 0.2, 0.8, 50, 50);
    glPopMatrix();

    glPushMatrix();
    glRotatef(180, 1, 0, 0);
    glTranslatef(0, 0, 0.8);
    gluCylinder(cilindro, 0.2, 0.05, 1.5, 50, 50);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, texture[7]);
    glPushMatrix();
    glRotatef(180, 1, 0, 0);
    glTranslatef(0, 0, -0.075);
    gluCylinder(cilindro, 0.075, 0.075, 0.2, 50, 50);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, texture[8]);
    glPushMatrix();
    float nr = 50;
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0,0); glVertex3f(0, 0, 0); // center of circle
    for (int i = 0; i <= nr; i++) {
        float px, py;
        px = (0.205 * cos(i * (2 * pi) / nr));
        py = (0.205 * sin(i * (2 * pi) / nr));
        float tx = 0.205 * cos(i * (2 * pi));
        float ty = 0.205 * sin(i * (2 * pi));
        glNormal3f(0.0f, 0.0f, 1.0f);
        glTexCoord2f(tx,ty);
        glVertex3f(px, py, 0);
    }
    glEnd();
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, texture[6]);
    glPushMatrix();
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glRotatef(20, 0, 0, 1);
    glTranslatef(0, 0, -0.05f);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(1,0); glVertex3f(-0.2f, 0.0f, 0.0f);
    glTexCoord2f(1,1); glVertex3f(-0.2f, 0.0f, -0.5f);
    glTexCoord2f(0,1); glVertex3f(-1.8f, 0.0f, -0.5f);
    glTexCoord2f(0,0.8); glVertex3f(-1.8f, 0.0f, -0.3f);
    

    glTexCoord2f(0,0); glVertex3f(0.2f, 0.0f, -0.2f);
    glTexCoord2f(1,0.8); glVertex3f(1.8f, 0.0f, -0.5f);
    glTexCoord2f(1,1); glVertex3f(1.8f, 0.0f, -0.7f);
    glTexCoord2f(0,1); glVertex3f(0.2f, 0.0f, -0.7f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glRotatef(-20, 0, 0, 1);
    glTranslatef(0, 0, -0.05f);
    glBegin(GL_QUADS);
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0, 0); glVertex3f(0.2f, 0.0f, 0.0f);
    glTexCoord2f(1, 0.8); glVertex3f(1.8f, 0.0f, -0.3f);
    glTexCoord2f(1, 1); glVertex3f(1.8f, 0.0f, -0.5f);
    glTexCoord2f(0, 1); glVertex3f(0.2f, 0.0f, -0.5f);
    
    glTexCoord2f(1,0); glVertex3f(-0.2f, 0.0f, -0.2f);
    glTexCoord2f(1,1); glVertex3f(-0.2f, 0.0f, -0.7f);
    glTexCoord2f(0,1); glVertex3f(-1.8f, 0.0f, -0.7f);
    glTexCoord2f(0,0.8); glVertex3f(-1.8f, 0.0f, -0.5f);
    glEnd();
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    gluLookAt(x, y, z,
              x + vx, y, z + vz,
              0.0f, 1.0f, 0.0f);
    
    glPushMatrix();
    Skybox();
    
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);

    glEnable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, texture[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, high_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, terra_emission);

    glPushMatrix();
    glTranslatef(2.0, 0.0, -10);
    glRotatef(90, 1.0, 0.0, 0.0);
    glRotatef(170, 0.0, 1.0, 0.0);
    glRotatef(160, 0.0, 0.0, 1.0);
    glRotatef(rotacaoEM, 0.0, 0.0, 1.0);
    gluSphere(esfera, 1, 50, 50);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, texture[1]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    glMaterialfv(GL_FRONT, GL_EMISSION, terra_emission);
    glPushMatrix();
    glTranslatef(-10, 0, -10.0);
    glRotatef(90, 1.0, 0.0, 0.0);
    glRotatef(170, 0.0, 1.0, 0.0);
    glRotatef(-rotacaoP, 0.0, 0.0, 1.0);
    gluSphere(esfera, 8, 50, 50);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, texture[2]);
    glPushMatrix();
    glTranslatef(140, -45, -260);
    glRotatef(90, 1.0, 0.0, 0.0);
    glRotatef(140, 0.0, 1.0, 0.0);
    glRotatef(rotacaoP, 0.0, 0.0, 1.0);
    gluSphere(esfera, 1, 50, 50);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, texture[3]);
    glPushMatrix();
    glTranslatef(70, -12, -220);
    glRotatef(90, 1.0, 0.0, 0.0);
    glRotatef(30, 0.0, 1.0, 0.0);
    glRotatef(rotacaoP, 0.0, 0.0, 1.0);
    gluSphere(esfera, 1, 50, 50);
    glPopMatrix();

    glBindTexture(GL_TEXTURE_2D, texture[4]);
    glPushMatrix();
    glTranslatef(70, 40, -180);
    glRotatef(90, 1.0, 0.0, 0.0);
    glRotatef(160, 0.0, 1.0, 0.0);
    glRotatef(rotacaoP, 0.0, 0.0, 1.0);
    gluSphere(esfera, 1, 50, 50);
    glPopMatrix();

    glMaterialfv(GL_FRONT, GL_EMISSION, nave_emission);
    glPushMatrix();
    desenhaNave2();
    glPopMatrix();

    for (int i = 0; i < 10; i++) {
        glPushMatrix();
        glTranslatef(posicaoNaveX[i], posicaoNaveY[i], posicaoNaveZ[i]);
        desenhaNave2();
        glPopMatrix();
    }

    /*glPushMatrix();
    calculaNormal(v);
    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
    glTranslatef(.5, -.5, -2);
    glRotatef(-90, 1, 0, 0);
    glScalef(0.2, 0.2, 0.2);
    desenhaNave();
    glPopMatrix();*/

    glDisable(GL_TEXTURE_2D);
    
    glDisable(GL_LIGHTING);    

    glutSwapBuffers();
}

void animacao(int) {
    glutPostRedisplay();
    glutTimerFunc(1000/60,animacao,0);
    if (rotacaoEM < 360) {
        rotacaoEM += 0.6;
    }
    else{
        rotacaoEM = 0.6;
    }
    if (rotacaoP < 360) {
        rotacaoP += 0.1;
    }
    else {
        rotacaoP = 0.1;
    }
}

void reshape(int x, int y) {
    if (y == 0 || x == 0) return;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(39.0, (GLdouble)x / (GLdouble)y, 0.1, 300.0);
    //gluLookAt(0, 0, 5, 1, 0, -10, 0, 1, 0);
    glMatrixMode(GL_MODELVIEW);
    glViewport(0, 0, x, y); 
}

void Init() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    texture[0] = SOIL_load_OGL_texture
    (
        "ds93.jpg",
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

    texture[5] = SOIL_load_OGL_texture(
        "corpo.png",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );
    if (texture[5] == 0) {
        printf("Erro no carregamento da imagem, %s\n", SOIL_last_result);
    }
    else {
        printf("Sucesso no carregamento da imagem\n");
    }

    texture[6] = SOIL_load_OGL_texture(
        "asa.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );
    if (texture[6] == 0) {
        printf("Erro no carregamento da imagem, %s\n", SOIL_last_result);
    }
    else {
        printf("Sucesso no carregamento da imagem\n");
    }

    texture[7] = SOIL_load_OGL_texture(
        "turbina.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );
    if (texture[7] == 0) {
        printf("Erro no carregamento da imagem, %s\n", SOIL_last_result);
    }
    else {
        printf("Sucesso no carregamento da imagem\n");
    }

    texture[8] = SOIL_load_OGL_texture(
        "ds4.jpg",
        SOIL_LOAD_AUTO,
        SOIL_CREATE_NEW_ID,
        SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
    );
    if (texture[8] == 0) {
        printf("Erro no carregamento da imagem, %s\n", SOIL_last_result);
    }
    else {
        printf("Sucesso no carregamento da imagem\n");
    }


    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHT0);

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model_ambient);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, 1);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    esfera = gluNewQuadric();
    gluQuadricDrawStyle(esfera, GLU_FILL);
    gluQuadricNormals(esfera, GLU_SMOOTH);
    gluQuadricOrientation(esfera, GLU_OUTSIDE);
    gluQuadricTexture(esfera, GL_TRUE);

    cilindro = gluNewQuadric();
    gluQuadricDrawStyle(cilindro, GLU_FILL);
    gluQuadricNormals(cilindro, GLU_SMOOTH);
    gluQuadricOrientation(cilindro, GLU_OUTSIDE);
    gluQuadricTexture(cilindro, GL_TRUE);

    for (int i = 0; i < 1000; i++) {
        estrela[i].x = random(-200, 200);
        estrela[i].y = random(-200, 200);
    }

    for (int i = 0; i < 10; i++) {
        posicaoNaveX[i] = random(0,10);
        posicaoNaveY[i] = random(-10,10);
        posicaoNaveZ[i] = random(-5,5);
    }
}

void teclado(unsigned char key, int x, int y) {
    if (key == 27) {
        exit(0);
    }

}

void moverCamera(int key, int xx, int yy) {
    float movimento = 0.5;

    switch (key) {
    case GLUT_KEY_LEFT:
        direcao -= 0.05f;
        vx = sin(direcao);
        vz = -cos(direcao);
        //x -= movimento;
        break;
    case GLUT_KEY_RIGHT:
        direcao += 0.05f;
        vx = sin(direcao);
        vz = -cos(direcao);
        //x += movimento;
        break;
    case GLUT_KEY_UP:
        x += vx * movimento;
        z += vz * movimento;
        break;
    case GLUT_KEY_DOWN:
        x -= vx * movimento;
        z -= vz * movimento;
        break;
    case GLUT_KEY_PAGE_UP:
        y += 0.5;
        break;
    case GLUT_KEY_PAGE_DOWN:
        y -= 0.5;
        break;
    }
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1920, 1080);
    glutCreateWindow("Projeto Final CG");
    Init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0,animacao,0);
    glutKeyboardFunc(teclado);
    glutSpecialFunc(moverCamera);
    glutMainLoop();
    return 0;
}
