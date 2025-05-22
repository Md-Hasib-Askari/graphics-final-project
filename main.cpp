#include <windows.h>
#include <iostream>
#include <GL/glut.h>
#include <cmath>

using namespace std;

// Window size
int windowWidth = 1280;
int windowHeight = 720;

void drawWindow(float offX = 0.0f, float offY = 0.0f) {
    glColor3f(0.180f, 0.059f, 0.012f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.742f+offX, 0.293f+offY);
        glVertex2f(-0.704f+offX, 0.292f+offY);
        glVertex2f(-0.703f+offX, 0.243f+offY);
        glVertex2f(-0.742f+offX, 0.243f+offY);
    glEnd();
}

void brokenBuilding1() {
    glColor3f(0.922f, 0.275f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.780f, -0.039f);
        glVertex2f(-0.510f, -0.037f);
        glVertex2f(-0.510f, 0.253f);
        glVertex2f(-0.516f, 0.254f);
        glVertex2f(-0.523f, 0.235f);
        glVertex2f(-0.523f, 0.254f);
        glVertex2f(-0.533f, 0.267f);
        glVertex2f(-0.533f, 0.285f);
        glVertex2f(-0.545f, 0.291f);

        glVertex2f(-0.551f, 0.286f);
        glVertex2f(-0.553f, 0.292f);
        glVertex2f(-0.553f, 0.301f);
        glVertex2f(-0.548f, 0.308f);
        glVertex2f(-0.548f, 0.316f);
        glVertex2f(-0.544f, 0.322f);
        glVertex2f(-0.550f, 0.333f);
        glVertex2f(-0.782f, 0.335f);
        glVertex2f(-0.780f, -0.039f);
    glEnd();

    glColor3f(0.180f, 0.051f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.497f, 0.294f);
        glVertex2f(-0.488f, 0.294f);
        glVertex2f(-0.481f, 0.291f);
        glVertex2f(-0.480f, 0.266f);
        glVertex2f(-0.476f, 0.261f);
        glVertex2f(-0.465f, 0.255f);
        glVertex2f(-0.510f, 0.254f);
        glVertex2f(-0.516f, 0.254f);
        glVertex2f(-0.515f, 0.276f);
        glVertex2f(-0.497f, 0.276f);
        glVertex2f(-0.497f, 0.294f);
    glEnd();

    drawWindow();
    drawWindow(0.081f);
    drawWindow(0.157f);

    drawWindow(0.0f, -0.083f);
    drawWindow(0.081f, -0.083f);
    drawWindow(0.157f, -0.083f);

    drawWindow(0.0f, -0.167f);
    drawWindow(0.081f, -0.167f);
    drawWindow(0.157f, -0.167f);

    drawWindow(0.0f, -0.251f);
    drawWindow(0.081f, -0.251f);
    drawWindow(0.157f, -0.251f);

}

void drawTree() {
    glColor3f(0.149f, 0.051f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.869f, 0.248f);
        glVertex2f(-0.818f, 0.147f);
        glVertex2f(-0.927f, 0.150f);

        glVertex2f(-0.872f, 0.183f);
        glVertex2f(-0.798f, 0.081f);
        glVertex2f(-0.941f, 0.085f);

        glVertex2f(-0.870f, 0.129f);
        glVertex2f(-0.782f, 0.010f);
        glVertex2f(-0.966f, 0.013f);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(-0.882f, 0.014f);
        glVertex2f(-0.859f, 0.014f);
        glVertex2f(-0.856f, -0.045f);
        glVertex2f(-0.884f, -0.045f);
    glEnd();
}

void drawBackground() {
    // background
    glBegin(GL_QUADS);
        glColor3f(0.51f, 0.08, 0.0f);
        glVertex2f(-1.0f, 0.5625f);
        glVertex2f(1.0f, 0.5625f);

        glColor3f(0.79f, 0.14f, 0.0f);
        glVertex2f(1.0f, 0.0f);
        glVertex2f(-1.0f, 0.0f);
    glEnd();

    glBegin(GL_QUADS);
        glColor3f(0.73f, 0.12f, 0.01f);
        glVertex2f(-1.0f, 0.0f);
        glVertex2f(1.0f, 0.0f);

        glColor3f(0.61f, 0.14f, 0.03f);
        glVertex2f(1.0f, -0.5625f);
        glVertex2f(-1.0f, -0.5625f);
    glEnd();


    // road
    glColor3f(0.23f, 0.06f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, -0.073f);
        glVertex2f(1.0f, -0.073f);
        glVertex2f(1.0f, -0.213f);
        glVertex2f(-1.0f, -0.213f);
    glEnd();

    glColor3f(0.83f, 0.17f, 0.0f);
    glLineWidth(7.0f);
    glBegin(GL_LINES);
        glVertex2f(-1.0f, -0.073f);
        glVertex2f(1.0f, -0.073f);
    glEnd();

    // walking road
    glColor3f(0.94f, 0.25f, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.080f, -0.18f);
        glVertex2f(0.002f, -0.18f);
        glVertex2f(0.018f, -0.191f);
        glVertex2f(-0.065f, -0.198f);

        glVertex2f(0.018f, -0.191f);
        glVertex2f(-0.065f, -0.198f);
        glVertex2f(-0.06f, -0.219f);
        glVertex2f(0.03f, -0.208f);

        glVertex2f(-0.058f, -0.217f);
        glVertex2f(0.029f, -0.206f);
        glVertex2f(0.039f, -0.224f);
        glVertex2f(-0.060f, -0.235f);

        glVertex2f(-0.089f, -0.279f);
        glVertex2f(0.026f, -0.282f);
        glVertex2f(-0.179f, -0.5625f);
        glVertex2f(-0.376f, -0.5625f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(0.038f, -0.224f);
        glVertex2f(-0.060f, -0.235f);
        glVertex2f(-0.074f, -0.263f);
        glVertex2f(-0.089f, -0.279f);
        glVertex2f(0.026f, -0.282f);
        glVertex2f(0.035f, -0.262f);
        glVertex2f(0.038f, -0.244f);
        glVertex2f(0.039f, -0.224f);
    glEnd();

    // Hills
    glColor3f(0.44f, 0.11f, 0.00f);
    glBegin(GL_TRIANGLE_STRIP);
    for (float x = -1.0f; x <= 1.0f; x += 0.01f) {
        float frequency = 5.0f;
        int loop = (int)floorf((x + 1.0f) * frequency / 2.0f); // loop index

        // Use a better seed to avoid same height per frame
        srand(loop * 9301 + 49297);

        // Generate a more varied random height between 0 and 0.15
        float randAmp = ((rand() % 1000) / 1000.0f) * 0.15f;
        randAmp += ((rand() % 500) / 1000.0f) * 0.15f; // add randomness boost

        if (randAmp > 0.15f) randAmp = 0.15f; // clamp max

        float y = randAmp * sinf(frequency * 3.1416f * x) + 0.17;
        glVertex2f(x, y);
        glVertex2f(x, 0.0f);
    }
    glEnd();
}

void mergeComponents() {
    drawBackground();
    drawTree();
    brokenBuilding1();
}

// Initialization
void initGL() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Background color
}

// Display callback
void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Clear the screen

    mergeComponents(); // Merge all the components into 1 scene

    glutSwapBuffers(); // Swap buffers (double buffering)
}

// Window resize callback
void reshape(int width, int height) {
    windowWidth = width;
    windowHeight = height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -0.5625, 0.5625); // Orthographic 2D projection
    glMatrixMode(GL_MODELVIEW);
}

// Entry point
int main(int argc, char** argv) {
    glutInit(&argc, argv);                      // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);// Double buffer, RGB mode
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("OpenGL GLUT Boilerplate"); // Create window

    glutDisplayFunc(display);   // Register display callback
    glutReshapeFunc(reshape);   // Register reshape callback

    initGL();                   // Set initial OpenGL state

    glutMainLoop();             // Start main loop
    return 0;
}
