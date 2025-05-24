#include <windows.h>
#include <iostream>
#include <GL/glut.h>
#include <cmath>
#include <vector>

#define PI 3.14159265

using namespace std;

// Window size
int windowWidth = 1280;
int windowHeight = 720;

// Color
struct Color {
    float r;
    float g;
    float b;
};

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
void drawSmallGrass(float offX=0, float offY=0) {

    glBegin(GL_POLYGON);
        glVertex2f(-0.537f +offX, -0.439f +offY);
        glVertex2f(-0.526f +offX, -0.442f +offY);
        glVertex2f(-0.513f +offX, -0.457f +offY);
        glVertex2f(-0.524f +offX, -0.457f +offY);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(-0.518f +offX, -0.419f +offY);
        glVertex2f(-0.505f +offX, -0.436f +offY);
        glVertex2f(-0.504f +offX, -0.457f +offY);
        glVertex2f(-0.513f +offX, -0.457f +offY);
        glVertex2f(-0.519f +offX, -0.439f +offY);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(-0.504f +offX, -0.457f +offY);
        glVertex2f(-0.500f +offX, -0.436f +offY);
        glVertex2f(-0.488f +offX, -0.423f +offY);
        glVertex2f(-0.488f +offX, -0.451f +offY);
        glVertex2f(-0.492f +offX, -0.457f +offY);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(-0.488f +offX, -0.451f +offY);
        glVertex2f(-0.468f +offX, -0.432f +offY);
        glVertex2f(-0.475f +offX, -0.451f +offY);
        glVertex2f(-0.484f +offX, -0.458f +offY);
        glVertex2f(-0.492f +offX, -0.457f +offY);
    glEnd();
}



void drawBrokenFence(float offX=0, float offY=0) {
    glColor3f(0.160f, 0.051f, 0.000f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.727f, -0.341f);
        glVertex2f(-0.669f, -0.366f);
        glVertex2f(-0.456f, -0.364f);
        glVertex2f(-0.394f, -0.341f);
        glVertex2f(-0.428f, -0.322f);
        glVertex2f(-0.690f, -0.324f);
    glEnd();


    glLineWidth(12.0f);
    glBegin(GL_LINES);
        glColor3f(0.310f, 0.043f, 0.016f);
        glVertex2f(-0.666f +offX, -0.324f +offY);
        glVertex2f(-0.476f +offX, -0.321f +offY);

        glColor3f(0.152f, 0.047f, 0.012f);
        glVertex2f(-0.651f +offX, -0.235f +offY);
        glVertex2f(-0.669f +offX, -0.337f +offY);
        glVertex2f(-0.500f +offX, -0.250f +offY);
        glVertex2f(-0.470f +offX, -0.332f +offY);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glColor3f(0.310f, 0.043f, 0.016f);
        glVertex2f(-0.463f +offX, -0.291f +offY);
        glVertex2f(-0.686f +offX, -0.260f +offY);

        glColor3f(0.251f, 0.047f, 0.000f);
        glVertex2f(-0.481f +offX, -0.240f +offY);
    glEnd();

    glBegin(GL_LINE_LOOP);
        glColor3f(0.310f, 0.043f, 0.016f);
        glVertex2f(-0.686f +offX, -0.286f +offY);
        glVertex2f(-0.447f +offX, -0.316f +offY);

        glColor3f(0.251f, 0.047f, 0.000f);
        glVertex2f(-0.420f +offX, -0.334f +offY);
    glEnd();

}


void drawCloud1(float offX=0, float offY=0, const vector<Color>& colors = {}) {
    if (colors.empty()) {
        glColor3f(0.871f, 0.216f, 0.0f);
    } else {
        Color c1 = colors[0];
        glColor3f(c1.r, c1.g, c1.b);
    }
    drawFilledCurve(-0.884, 0.392, 0.041, 0, 180);
    drawFilledCurve(-0.829, 0.421, 0.037, 0, 180);
    drawFilledCurve(-0.741, 0.436, 0.071, 0, 180);
    drawFilledCurve(-0.645, 0.415, 0.043, 0, 180);
    drawFilledCurve(-0.589, 0.401, 0.028, -13, 180);

    glBegin(GL_POLYGON);
        glVertex2f(-0.747f, 0.477f);
        glVertex2f(-0.561f, 0.393f);
        glVertex2f(-0.925f, 0.394f);
    glEnd();
}

void drawCloud2(float offX=0, float offY=0) {
    glColor3f(0.871f, 0.216f, 0.0f);
    drawFilledCurve(-0.926, 0.293, 0.037, 0, 180);
    drawFilledCurve(-0.869, 0.329, 0.041, -40, 210);
    drawFilledCurve(-0.817, 0.293, 0.051, 0, 180);

    glBegin(GL_POLYGON);
        glVertex2f(-0.869f, 0.330f);
        glVertex2f(-0.926f, 0.293f);
        glVertex2f(-0.817f, 0.293f);
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

void drawFlower(float centerX = 0, float centerY = 0, float petalLength = 0.1f, int petalCount = 6) {
    glColor3f(0.949f, 0.290f, 0.0078f);
    for (int i = 0; i < petalCount; ++i) {
        float angle = 2 * PI * i / petalCount;

        float x = centerX + petalLength * cos(angle);
        float y = centerY + petalLength * sin(angle);
        drawFilledCurve(x, y, petalLength);
    }

    // Draw flower center
    glColor3f(0.639f, 0.133f, 0.008f); // yellow center
    drawFilledCurve(centerX, centerY, 0.02f);
}

void drawFlowerGrass() {
    glColor3f(0.1608f, 0.0471f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(0.185f, -0.477f);
        glVertex2f(0.135f, -0.473f);
        glVertex2f(0.076f, -0.454f);
        glVertex2f(0.029f, -0.416f);
        glVertex2f(0.095f, -0.431f);
        glVertex2f(0.128f, -0.453f);
        glVertex2f(0.185f, -0.477f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(0.185f, -0.477f);
        glVertex2f(0.128f, -0.453f);
        glVertex2f(0.092f, -0.400f);
        glVertex2f(0.070f, -0.331f);
        glVertex2f(0.125f, -0.391f);
        glVertex2f(0.143f, -0.428f);
        glVertex2f(0.185f, -0.477f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(0.167f, -0.450f);
        glVertex2f(0.143f, -0.428f);
        glVertex2f(0.127f, -0.367f);
        glVertex2f(0.095f, -0.279f);
        glVertex2f(0.142f, -0.344f);
        glVertex2f(0.160f, -0.397f);
        glVertex2f(0.167f, -0.450f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(0.167f, -0.450f);
        glVertex2f(0.178f, -0.400f);
        glVertex2f(0.209f, -0.338f);
        glVertex2f(0.178f, -0.400f);
        glVertex2f(0.182f, -0.450f);
        glVertex2f(0.185f, -0.477f);
        glVertex2f(0.167f, -0.450f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(0.185f, -0.477f);
        glVertex2f(0.182f, -0.450f);
        glVertex2f(0.204f, -0.420f);
        glVertex2f(0.229f, -0.398f);
        glVertex2f(0.225f, -0.425f);
        glVertex2f(0.215f, -0.445f);
        glVertex2f(0.185f, -0.477f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(0.185f, -0.477f);
        glVertex2f(0.215f, -0.445f);
        glVertex2f(0.261f, -0.406f);
        glVertex2f(0.298f, -0.384f);
        glVertex2f(0.277f, -0.423f);
        glVertex2f(0.221f, -0.472f);
        glVertex2f(0.185f, -0.477f);
    glEnd();

}

void drawFlowerGrass2() {
    glColor3f(0.1608f, 0.0471f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(0.3581f, -0.4850f);
        glVertex2f(0.3403f, -0.4827f);
        glVertex2f(0.3163f, -0.4584f);
        glVertex2f(0.3106f, -0.4394f);
        glVertex2f(0.3300f, -0.4493f);
        glVertex2f(0.3513f, -0.4698f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(0.3581f, -0.4850f);
        glVertex2f(0.3631f, -0.4572f);
        glVertex2f(0.3752f, -0.4158f);
        glVertex2f(0.3729f, -0.4508f);
        glVertex2f(0.3729f, -0.4857f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(0.3729f, -0.4857f);
        glVertex2f(0.3800f, -0.4600f);
        glVertex2f(0.3942f, -0.4420f);
        glVertex2f(0.3840f, -0.4766f);
        glVertex2f(0.3729f, -0.4857f);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(0.3729f, -0.4857f);
        glVertex2f(0.4064f, -0.4709f);
        glVertex2f(0.4132f, -0.4542f);
        glVertex2f(0.4280f, -0.4257f);
        glVertex2f(0.4299f, -0.4447f);
        glVertex2f(0.4276f, -0.4683f);
        glVertex2f(0.4075f, -0.4861f);
        glVertex2f(0.3729f, -0.4857f);
    glEnd();

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

void brokenBuilding4() {
    glColor3f(0.239f, 0.067f, 0.004f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.158f, 0.110f);
        glVertex2f(-0.102f, 0.055f);
        glVertex2f(-0.100f, -0.026f);
        glVertex2f(-0.218f, -0.024f);
        glVertex2f(-0.220f, 0.056f);
    glEnd();

    glColor3f(0.188f, 0.051f, 0.000f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.268f, 0.115f);
        glVertex2f(-0.336f, 0.040f);
        glVertex2f(-0.371f, 0.041f);
        glVertex2f(-0.283f, 0.147f);
        glVertex2f(-0.180f, 0.042f);
        glVertex2f(-0.197f, 0.041f);
    glEnd();

    glColor3f(0.529f, 0.071f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.268f, 0.115f);
        glVertex2f(-0.197f, 0.040f);
        glVertex2f(-0.197f, -0.040f);
        glVertex2f(-0.333f, -0.041f);
        glVertex2f(-0.336f, 0.040f);
    glEnd();

    // door
    glColor3f(0.271f, 0.067f, 0.008f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.284f, 0.013f);
        glVertex2f(-0.213f, 0.014f);
        glVertex2f(-0.212f, -0.038f);
        glVertex2f(-0.285f, -0.039f);
    glEnd();
    drawFilledCurve(-0.249, 0.013, 0.035, 0, 180);

    glColor3f(0.239f, 0.067f, 0.004f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.283f, 0.147f);
        glVertex2f(-0.227f, 0.124f);
        glVertex2f(-0.203f, 0.078f);
        glVertex2f(-0.182f, 0.065f);
        glVertex2f(-0.168f, 0.044f);
        glVertex2f(-0.180f, 0.042f);
    glEnd();

    glColor3f(0.57f, 0.074f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.197f, 0.041f);
        glVertex2f(-0.102f, 0.055f);
        glVertex2f(-0.100f, -0.026f);
        glVertex2f(-0.197f, -0.040f);
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

    // clouds
    drawCloud1();
    glTranslatef(1.2, -0.05, 0);
    drawCloud1();
    glLoadIdentity();

    glTranslatef(0.7, 0, 0);
    drawCloud2();
    glLoadIdentity();

    // trees
    drawTree1();
    drawTree2();
    drawTree3();

    // buildings
    brokenBuilding1();
    brokenBuilding2();
    brokenBuilding3();
    brokenBuilding4();

    glTranslatef(0.24, 0, 0);
    brokenBuilding4();
    glLoadIdentity();

    // broken fence
    drawBrokenFence();

    // grass
    vector<Color> cloudGrass = {
        { 0.153f, 0.047f, 0.000f }
    };
    glTranslatef(0, -0.9, 0);
    drawCloud1(0, 0, cloudGrass);
    glLoadIdentity();

    drawSmallGrass();
    glTranslatef(0.3, 0.15, 0);
    drawSmallGrass();
    glLoadIdentity();

    // flower 1
    glColor3f(0.361f, 0.082f, 0.0039f);
    drawFilledEllipse(0.164, -0.472, 0.127, 0.017);
    drawFlowerGrass();
    drawFlower(0.229f, -0.317f, 0.03f, 5);

    // flower 2
    glColor3f(0.361f, 0.082f, 0.0039f);
    drawFilledEllipse(0.386, -0.49, 0.1, 0.017);
    drawFlowerGrass2();
    drawFlower(0.376f, -0.401f, 0.02f, 5);


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
