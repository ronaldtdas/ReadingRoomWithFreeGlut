#include <GL/freeglut.h>
#include <cmath>

float cameraAngleX = 0.0f;
float cameraAngleY = 0.0f;
float cameraDistance = 10.0f;

void drawTable() {
    // Draw table legs
    glColor3f(0.5, 0.35, 0.05); // Brown color
    glPushMatrix();
    glTranslatef(-2.0, -2.5, -2.0);
    glScalef(0.1, 1.5, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.0, -2.5, -2.0);
    glScalef(0.1, 1.5, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-2.0, -2.5, 2.0);
    glScalef(0.1, 1.5, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(2.0, -2.5, 2.0);
    glScalef(0.1, 1.5, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();

    // Draw table top
    glColor3f(0.5, 0.35, 0.05); // Brown color
    glPushMatrix();
    glTranslatef(0.0, -0.25, 0.0);
    glScalef(4.0, 0.1, 4.0);
    glutSolidCube(1.0);
    glPopMatrix();
}

void drawRoom() {
    // Draw back wall
    glColor3f(0.8, 0.6, 0.6); // Light red color
    glPushMatrix();
    glTranslatef(0.0, 0.0, -5.0);
    glScalef(8.0, 3.0, 0.1);
    glutSolidCube(1.0);
    glPopMatrix();

    // Draw left wall
    glColor3f(0.6, 0.8, 0.6); // Light green color
    glPushMatrix();
    glTranslatef(-4.0, 0.0, 0.0);
    glScalef(0.1, 3.0, 10.0);
    glutSolidCube(1.0);
    glPopMatrix();

    // Draw right wall
    glColor3f(0.6, 0.6, 0.8); // Light blue color
    glPushMatrix();
    glTranslatef(4.0, 0.0, 0.0);
    glScalef(0.1, 3.0, 10.0);
    glutSolidCube(1.0);
    glPopMatrix();

    // Draw floor
    glColor3f(0.7, 0.7, 0.7); // Light gray color
    glPushMatrix();
    glTranslatef(0.0, -1.5, 0.0);
    glScalef(8.0, 0.1, 10.0);
    glutSolidCube(1.0);
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(
        cameraDistance * sin(cameraAngleY) * cos(cameraAngleX),
        cameraDistance * sin(cameraAngleX),
        cameraDistance * cos(cameraAngleY) * cos(cameraAngleX),
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0
    );

    drawRoom();
    drawTable();

    glutSwapBuffers();
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)w / (float)h, 1.0, 20.0);
}

void specialKeys(int key, int x, int y) {
    switch (key) {
    case GLUT_KEY_UP:
        cameraAngleX += 0.1f;
        break;
    case GLUT_KEY_DOWN:
        cameraAngleX -= 0.1f;
        break;
    case GLUT_KEY_LEFT:
        cameraAngleY -= 0.1f;
        break;
    case GLUT_KEY_RIGHT:
        cameraAngleY += 0.1f;
        break;
    }

    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
    case 'w':
        cameraDistance -= 0.1f;
        break;
    case 's':
        cameraDistance += 0.1f;
        break;
    }

    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 600);
    glutCreateWindow("OpenGL Room with Table");

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(specialKeys);
    glutKeyboardFunc(keyboard);

    glutMainLoop();

    return 0;
}