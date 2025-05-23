#include <windows.h>
#include <iostream>
#include <GL/glut.h>
#include <cmath>

#define PI 3.14159265

using namespace std;

// Window size
int windowWidth = 1280;
int windowHeight = 720;

void drawFilledCurve(float centerX = 0, float centerY = 0, float radius = 0.1f, float startAngle = 0, float endAngle = 360) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(centerX, centerY); // center of fan

    for (float angle = startAngle; angle <= endAngle; angle += 1.0f) {
        float rad = angle * PI / 180.0f;
        float x = centerX + cos(rad) * radius;
        float y = centerY + sin(rad) * radius;
        glVertex2f(x, y);
    }

    glEnd();
}

void drawFilledEllipse(float centerX = 0, float centerY = 0, float radiusX = 0.2f, float radiusY = 0.3f) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(centerX, centerY); // center

    for (float angle = 0; angle <= 360; angle += 1.0f) {
        float rad = angle * PI / 180.0f;
        float x = centerX + cos(rad) * radiusX;
        float y = centerY + sin(rad) * radiusY;
        glVertex2f(x, y);
    }

    glEnd();
}



    //glBegin(GL_POLYGON);

    //glEnd();

void drawCloud1(float offX=0, float offY=0) {
    glColor3f(0.871f, 0.216f, 0.0f);
    drawFilledCurve(-0.884 + offX, 0.392 + offY, 0.041, 0, 180);
    drawFilledCurve(-0.829 + offX, 0.421 + offY, 0.037, 0, 180);
    drawFilledCurve(-0.741 + offX, 0.436 + offY, 0.071, 0, 180);
    drawFilledCurve(-0.645 + offX, 0.415 + offY, 0.043, 0, 180);
    drawFilledCurve(-0.589 + offX, 0.401 + offY, 0.028, -13, 180);

    glBegin(GL_POLYGON);
        glVertex2f(-0.747f + offX, 0.477f + offY);
        glVertex2f(-0.561f + offX, 0.393f + offY);
        glVertex2f(-0.925f + offX, 0.394f + offY);
    glEnd();
}

void drawCloud2(float offX=0, float offY=0) {
    glColor3f(0.871f, 0.216f, 0.0f);
    drawFilledCurve(-0.926 + offX, 0.293 + offY, 0.037, 0, 180);
    drawFilledCurve(-0.869 + offX, 0.329 + offY, 0.041, -40, 210);
    drawFilledCurve(-0.817 + offX, 0.293 + offY, 0.051, 0, 180);

    glBegin(GL_POLYGON);
        glVertex2f(-0.869f + offX, 0.330f + offY);
        glVertex2f(-0.926f + offX, 0.293f + offY);
        glVertex2f(-0.817f + offX, 0.293f + offY);
    glEnd();
}

void drawTree1() {
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

void drawTree2() {
    // Tree Leafs
    glColor3f(0.290f, 0.059f, 0.000f);
    drawFilledCurve(0.187f, -0.025f, 0.03f);
    drawFilledCurve(0.250f, -0.010f, 0.048f);
    drawFilledCurve(0.261f, 0.044f, 0.023f);
    drawFilledCurve(0.280f, 0.080f, 0.036f);
    drawFilledCurve(0.313f, 0.112f, 0.04f);
    drawFilledCurve(0.343f, 0.127f, 0.034f);
    drawFilledCurve(0.398f, 0.139f, 0.047f);
    drawFilledCurve(0.450f, 0.183f, 0.041f);
    drawFilledCurve(0.507f, 0.178f, 0.028f);
    drawFilledCurve(0.533f, 0.149f, 0.035f);

    glBegin(GL_POLYGON);
        glVertex2f(0.231f, -0.034f);
        glVertex2f(0.309f, 0.127f);
        glVertex2f(0.507f, 0.178f);
        glVertex2f(0.549f, 0.110f);
        glVertex2f(0.551f, -0.034f);
    glEnd();

    glColor3f(0.549f, 0.071f, 0.004f);
    glLineWidth(4.5f);
    glBegin(GL_LINES);
        glVertex2f(0.347f, 0.138f);
        glVertex2f(0.346f, -0.035f);
        glVertex2f(0.298f, 0.092f);
        glVertex2f(0.310f, 0.059f);

        glVertex2f(0.463f, 0.191f);
        glVertex2f(0.464f, -0.035f);
        glVertex2f(0.464f, 0.157f);
        glVertex2f(0.481f, 0.168f);
        glVertex2f(0.422f, 0.123f);
        glVertex2f(0.408f, 0.079f);
        glVertex2f(0.485f, 0.111f);
        glVertex2f(0.513f, 0.113f);
        glVertex2f(0.374f, 0.088f);
        glVertex2f(0.408f, 0.079f);

    glEnd();

    glBegin(GL_LINE_STRIP);
        glVertex2f(0.313f, 0.112f);
        glVertex2f(0.345f, 0.092f);
        glVertex2f(0.366f, 0.110f);
    glEnd();

    glBegin(GL_LINE_STRIP);
        glVertex2f(0.287f, 0.065f);
        glVertex2f(0.310f, 0.059f);
        glVertex2f(0.347f, 0.030f);
        glVertex2f(0.350f, 0.050f);
        glVertex2f(0.372f, 0.061f);
    glEnd();

    glBegin(GL_LINE_STRIP);
        glVertex2f(0.420f, 0.147f);
        glVertex2f(0.433f, 0.119f);
        glVertex2f(0.465f, 0.094f);
        glVertex2f(0.485f, 0.111f);
        glVertex2f(0.503f, 0.134f);
    glEnd();

    glBegin(GL_LINE_STRIP);
        glVertex2f(0.391f, 0.118f);
        glVertex2f(0.408f, 0.079f);
        glVertex2f(0.463f, 0.037f);
        glVertex2f(0.464f, 0.018f);
        glVertex2f(0.498f, 0.052f);
    glEnd();
}

void drawTree3() {
    // Tree Leafs
    glColor3f(0.149f, 0.055f, 0.004f);
    drawFilledCurve(-0.932f, -0.178f, 0.047f);
    drawFilledCurve(-0.890f, -0.214f, 0.067f);
    drawFilledCurve(-0.843f, -0.208f, 0.053f);
    drawFilledCurve(-0.880f, -0.140f, 0.051f);

    glColor3f(0.388f, 0.094f, 0.004f);
    drawFilledEllipse(-0.879, -0.345, 0.058, 0.009);

    glColor3f(0.549f, 0.071f, 0.004f);
    glLineWidth(12.0f);
    glBegin(GL_LINES);
        glVertex2f(-0.880f, -0.187f);
        glVertex2f(-0.881f, -0.342f);
    glEnd();

    glBegin(GL_LINE_STRIP);
        glVertex2f(-0.925f, -0.209f);
        glVertex2f(-0.881f, -0.251f);
        glVertex2f(-0.834f, -0.201f);
    glEnd();

}

void drawFlower(float centerX = 0, float centerY = 0, float petalLength = 0.3f, float petalWidth = 0.1f, int petalCount = 6) {
    float angleStep = 360.0f / petalCount;

    for (int i = 0; i < petalCount; ++i) {
        float angle = i * angleStep;

        // Save transformation state
        glPushMatrix();

        // Move to flower center and rotate
        glTranslatef(centerX, centerY, 0.0f);
        glRotatef(angle, 0.0f, 0.0f, 1.0f);

        // Move outward and draw petal as rotated ellipse
        glTranslatef(0.0f, petalLength / 2.0f, 0.0f);
        glColor3f(0.969f, 0.306f, 0.0f); // red petals
        drawFilledEllipse(0, 0, petalWidth, petalLength / 2.0f);

        // Restore transformation state
        glPopMatrix();
    }

    // Draw flower center
    glColor3f(0.639f, 0.133f, 0.008f); // yellow center
    drawFilledEllipse(centerX, centerY, 0.07f, 0.07f);
}



void drawWindowB1(float offX = 0.0f, float offY = 0.0f) {
    glColor3f(0.180f, 0.059f, 0.012f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.742f+offX, 0.293f+offY);
        glVertex2f(-0.704f+offX, 0.292f+offY);
        glVertex2f(-0.703f+offX, 0.243f+offY);
        glVertex2f(-0.742f+offX, 0.243f+offY);
    glEnd();
}

void drawWindowB2(float offX = 0.0f, float offY = 0.0f) {
    glColor3f(0.761f, 0.145f, 0.008f);
    glBegin(GL_POLYGON);
        glVertex2f(0.558f+offX, 0.028f+offY);
        glVertex2f(0.628f+offX, 0.028f+offY);
        glVertex2f(0.628f+offX, -0.019f+offY);
        glVertex2f(0.559f+offX, -0.020f+offY);
    glEnd();
}

void drawWindowB3(float offX = 0.0f, float offY = 0.0f) {
    glColor3f(0.188f, 0.051f, 0.000f);
    glBegin(GL_POLYGON);
        glVertex2f(0.644f+offX, 0.285f+offY);
        glVertex2f(0.672f+offX, 0.284f+offY);
        glVertex2f(0.673f+offX, 0.247f+offY);
        glVertex2f(0.644f+offX, 0.246f+offY);
    glEnd();
}

void drawDoorB2(float offX = 0.0f, float offY = 0.0f) {
    glColor3f(0.761f, 0.145f, 0.008f);
    glBegin(GL_POLYGON);
        glVertex2f(0.667f+offX, 0.030f+offY);
        glVertex2f(0.741f+offX, 0.028f+offY);
        glVertex2f(0.741f+offX, -0.062f+offY);
        glVertex2f(0.667f+offX, -0.061f+offY);
    glEnd();
}

void brokenBuilding1() {
    glColor3f(0.922f, 0.275f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.780f, -0.039f);
        glVertex2f(-0.510f, -0.039f);
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

    drawWindowB1();
    drawWindowB1(0.081f);
    drawWindowB1(0.157f);

    drawWindowB1(0.0f, -0.083f);
    drawWindowB1(0.081f, -0.083f);
    drawWindowB1(0.157f, -0.083f);

    drawWindowB1(0.0f, -0.167f);
    drawWindowB1(0.081f, -0.167f);
    drawWindowB1(0.157f, -0.167f);

    drawWindowB1(0.0f, -0.251f);
    drawWindowB1(0.081f, -0.251f);
    drawWindowB1(0.157f, -0.251f);

    glColor3f(0.188f, 0.039f, 0.000f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.509f, 0.252f);
        glVertex2f(-0.466f, 0.262f);
        glVertex2f(-0.463f, -0.025f);
        glVertex2f(-0.509f, -0.039f);
    glEnd();

}

void brokenBuilding2() {
    glColor3f(0.388f, 0.051f, 0.000f);
    glBegin(GL_POLYGON);
        glColor3f(0.435f, 0.043f, 0.000f);
        glVertex2f(0.502f, 0.073f);
        glVertex2f(0.594f, 0.158f);

        glColor3f(0.290f, 0.027f, 0.000f);
        glVertex2f(1.000f, 0.158f);
        glVertex2f(1.000f, 0.073f);
    glEnd();

    glColor3f(0.118f, 0.043f, 0.000f);
    glBegin(GL_POLYGON);
        glVertex2f(0.502f, 0.073f);
        glVertex2f(0.498f, 0.052f);
        glVertex2f(1.000f, 0.052f);
        glVertex2f(1.000f, 0.073f);
    glEnd();

    glColor3f(0.145f, 0.071f, 0.012f);
    glBegin(GL_POLYGON);
        glVertex2f(0.521f, 0.056f);
        glVertex2f(0.518f, -0.06f);
        glVertex2f(1.000f, -0.06f);
        glVertex2f(1.000f, 0.052f);
    glEnd();

    drawWindowB2();
    drawWindowB2(0.219f);
    drawWindowB2(0.32f);
    drawDoorB2();
}

void brokenBuilding3() {
    glColor3f(0.890f, 0.235f, 0.035f);
    glBegin(GL_POLYGON);
        glVertex2f(0.611f, 0.317f);
        glVertex2f(0.822f, 0.318f);
        glVertex2f(0.822f, 0.153f);
        glVertex2f(0.611f, 0.156f);
    glEnd();

    glColor3f(0.180f, 0.051f, 0.000f);
    glBegin(GL_POLYGON);
        glVertex2f(0.822f, 0.318f);
        glVertex2f(0.822f, 0.153f);
        glVertex2f(0.873f, 0.155f);
        glVertex2f(0.872f, 0.296f);
    glEnd();

    drawWindowB3();
    drawWindowB3(0.058f);
    drawWindowB3(0.117f);

    drawWindowB3(0.0f, -0.066f);
    drawWindowB3(0.058f, -0.066f);
    drawWindowB3(0.117f, -0.066f);
}

void brokenBuilding4(float offX=0, float offY=0) {
    glColor3f(0.239f, 0.067f, 0.004f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.158f + offX, 0.110f + offY);
        glVertex2f(-0.102f + offX, 0.055f + offY);
        glVertex2f(-0.100f + offX, -0.026f + offY);
        glVertex2f(-0.218f + offX, -0.024f + offY);
        glVertex2f(-0.220f + offX, 0.056f + offY);
    glEnd();

    glColor3f(0.188f, 0.051f, 0.000f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.268f + offX, 0.115f + offY);
        glVertex2f(-0.336f + offX, 0.040f + offY);
        glVertex2f(-0.371f + offX, 0.041f + offY);
        glVertex2f(-0.283f + offX, 0.147f + offY);
        glVertex2f(-0.180f + offX, 0.042f + offY);
        glVertex2f(-0.197f + offX, 0.041f + offY);
    glEnd();

    glColor3f(0.529f, 0.071f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.268f + offX, 0.115f + offY);
        glVertex2f(-0.197f + offX, 0.040f + offY);
        glVertex2f(-0.197f + offX, -0.040f + offY);
        glVertex2f(-0.333f + offX, -0.041f + offY);
        glVertex2f(-0.336f + offX, 0.040f + offY);
    glEnd();

    // door
    glColor3f(0.271f, 0.067f, 0.008f + offY);
    glBegin(GL_POLYGON);
        glVertex2f(-0.284f + offX, 0.013f + offY);
        glVertex2f(-0.213f + offX, 0.014f + offY);
        glVertex2f(-0.212f + offX, -0.038f + offY);
        glVertex2f(-0.285f + offX, -0.039f + offY);
    glEnd();
    drawFilledCurve(-0.249 + offX, 0.013 + offY, 0.035, 0, 180);

    glColor3f(0.239f, 0.067f, 0.004f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.283f + offX, 0.147f + offY);
        glVertex2f(-0.227f + offX, 0.124f + offY);
        glVertex2f(-0.203f + offX, 0.078f + offY);
        glVertex2f(-0.182f + offX, 0.065f + offY);
        glVertex2f(-0.168f + offX, 0.044f + offY);
        glVertex2f(-0.180f + offX, 0.042f + offY);
    glEnd();

    glColor3f(0.57f, 0.074f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.197f + offX, 0.041f + offY);
        glVertex2f(-0.102f + offX, 0.055f + offY);
        glVertex2f(-0.100f + offX, -0.026f + offY);
        glVertex2f(-0.197f + offX, -0.040f + offY);
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
        glVertex2f(-0.080f, -0.213f);
        glVertex2f(0.002f, -0.213f);
        glVertex2f(0.018f, -0.224f);
        glVertex2f(-0.065f, -0.231f);

        glVertex2f(0.018f, -0.224f);
        glVertex2f(-0.065f, -0.231f);
        glVertex2f(-0.06f, -0.252f);
        glVertex2f(0.03f, -0.241f);

        glVertex2f(-0.058f, -0.250f);
        glVertex2f(0.029f, -0.239f);
        glVertex2f(0.039f, -0.257f);
        glVertex2f(-0.060f, -0.268f);

        glVertex2f(-0.089f, -0.312f);
        glVertex2f(0.026f, -0.315f);
        glVertex2f(-0.179f, -0.595f);
        glVertex2f(-0.376f, -0.595f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(0.038f, -0.257f);
        glVertex2f(-0.060f, -0.268f);
        glVertex2f(-0.074f, -0.296f);
        glVertex2f(-0.089f, -0.312f);
        glVertex2f(0.026f, -0.315f);
        glVertex2f(0.035f, -0.295f);
        glVertex2f(0.038f, -0.277f);
        glVertex2f(0.039f, -0.257f);
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
    drawCloud1();
    drawCloud1(1.2, -0.05);
    drawCloud2(0.7);
    drawTree1();
    drawTree2();
    drawTree3();
    brokenBuilding1();
    brokenBuilding2();
    brokenBuilding3();
    brokenBuilding4();
    brokenBuilding4(0.24);

//    drawFlower(0.0f, 0.0f, 0.3f, 0.1f, 8);


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
