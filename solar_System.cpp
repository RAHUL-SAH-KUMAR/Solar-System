#include <GLUT/glut.h>
#include <cmath>

float angleMercury = 0.0f;
float angleVenus = 0.0f;
float angleEarth = 0.0f;
float angleMars = 0.0f;

void drawCircle(float radius) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < 360; i++) {
        float angle = i * 3.14159f / 180.0f;
        glVertex2f(cos(angle) * radius, sin(angle) * radius);
    }
    glEnd();
}

void drawPlanet(float orbitRadius, float angle, float size, float r, float g, float b) {
    float x = cos(angle) * orbitRadius;
    float y = sin(angle) * orbitRadius;

    glColor3f(r, g, b);
    glPushMatrix();
    glTranslatef(x, y, 0);
    glutSolidSphere(size, 20, 20);
    glPopMatrix();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    // Sun
    glColor3f(1.0f, 0.7f, 0.0f);
    glutSolidSphere(0.1, 30, 30);

    // Orbits
    glColor3f(1, 1, 1);
    drawCircle(0.3f); // Mercury
    drawCircle(0.5f); // Venus
    drawCircle(0.7f); // Earth
    drawCircle(0.9f); // Mars

    // Planets
    drawPlanet(0.3f, angleMercury, 0.02f, 0.5f, 0.5f, 0.5f);
    drawPlanet(0.5f, angleVenus,   0.03f, 0.9f, 0.6f, 0.2f);
    drawPlanet(0.7f, angleEarth,   0.035f, 0.2f, 0.5f, 1.0f);
    drawPlanet(0.9f, angleMars,    0.03f, 1.0f, 0.2f, 0.1f);

    glutSwapBuffers();
}

void update(int value) {
    angleMercury += 0.05f;
    angleVenus   += 0.03f;
    angleEarth   += 0.02f;
    angleMars    += 0.015f;

    if (angleMercury > 360) angleMercury -= 360;
    if (angleVenus > 360) angleVenus -= 360;
    if (angleEarth > 360) angleEarth -= 360;
    if (angleMars > 360) angleMars -= 360;

    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // ~60 FPS
}

void init() {
    glClearColor(0.0f, 0.0f, 0.1f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-1, 1, -1, 1);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Solar System Simulation - OpenGL");

    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}
