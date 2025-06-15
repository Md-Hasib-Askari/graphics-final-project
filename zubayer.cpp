#include <windows.h>
#include <iostream>
#include <GL/glut.h>
#include <cmath>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

using namespace std;

// Window size
int windowWidth = 1280;
int windowHeight = 720;

//glBegin(GL_POLYGON);

//glEnd();

// === Add these global variables ===
//fire animation
float fireScale = 0.7f;
bool growing = true;
int fireTimer = 0;
bool showFires = false;

float carPos = -0.8f;
float truckPos = 0.7f;
int carState = 0, truckState = 0; // 0=forward, 1=reset back, 2=stopped

float jetPlaneOffsetX = -300.0f;
float planeOffsetX = -600.0f;
bool startPlane = false;

float rocketY = 0.09f;              // Rocket's Y-position
bool showRocket = false;            // Whether to show rocket
bool startRocketFall = false;       // Whether to begin falling
int rocketTimer = 0;                // Timer tracker

float rocket2Y = 0.15f, rocket3Y = 0.15f;
bool showRockets = false;
bool explodeRocket2 = false, explodeRocket3 = false;
float explosionRadius = 0.0f;
bool hideRocket2 = false, hideRocket3 = false;
int explosionTime = 0;

bool jetSoundPlaying = false;
int jetSoundTimer = 0;

bool vehicleSoundPlayed = false;
int vehicleSoundTimer = 0;


void Circle(float centerX, float centerY, float radius, float rColor, float gColor, float bColor) {
    glColor3f(rColor, gColor, bColor);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float pi = 3.1416;
        float angle = (i * 2 * pi) / 180;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(centerX + x, centerY + y);
    }
    glEnd();
}

void SemiCircle(float centerX, float centerY, float radius, float rColor, float gColor, float bColor) {
    glColor3f(rColor, gColor, bColor);
    glBegin(GL_POLYGON);
    for (int i = 0; i <= 180; i++) {
        float pi = 3.1416f;
        float angle = (i * pi) / 180.0f; // Only 0° to 180°
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        glVertex2f(centerX + x, centerY + y);
    }
    glEnd();
}


void cloud() {
    Circle(0.07f, 0.45f, 0.05f, 0.671f, 0.235f, 0.082f);
    Circle(0.15f, 0.45f, 0.05f, 0.671f, 0.235f, 0.082f);
    Circle(0.22f, 0.45f, 0.05f, 0.671f, 0.235f, 0.082f);
    Circle(0.15f, 0.50f, 0.05f, 0.671f, 0.235f, 0.082f);

    Circle(-0.48f, 0.5f, 0.05f, 0.671f, 0.235f, 0.082f);
    Circle(-0.4f, 0.5f, 0.05f, 0.671f, 0.235f, 0.082f);
    Circle(-0.33f, 0.5f, 0.05f, 0.671f, 0.235f, 0.082f);
    Circle(-0.4f, 0.55f, 0.05f, 0.671f, 0.235f, 0.082f);
}

void drawSun() {
    float centerX = 0.75f;
    float centerY = 0.45f;
    float radius = 0.08f;

    // Draw sun body
    Circle(centerX, centerY, radius, 0.980f, 0.494f, 0.004f);

    // Draw sun rays
    glLineWidth(3);
    glColor3f(0.980f, 0.494f, 0.004f);
    glBegin(GL_LINES);

    // Up
    glVertex2f(centerX, centerY + radius);
    glVertex2f(centerX, centerY + radius + 0.05f);

    // Down
    glVertex2f(centerX, centerY - radius);
    glVertex2f(centerX, centerY - radius - 0.05f);

    // Left
    glVertex2f(centerX - radius, centerY);
    glVertex2f(centerX - radius - 0.05f, centerY);

    // Right
    glVertex2f(centerX + radius, centerY);
    glVertex2f(centerX + radius + 0.05f, centerY);

    // Top-left
    glVertex2f(centerX - radius * 0.7f, centerY + radius * 0.7f);
    glVertex2f(centerX - radius * 0.7f - 0.035f, centerY + radius * 0.7f + 0.035f);

    // Top-right
    glVertex2f(centerX + radius * 0.7f, centerY + radius * 0.7f);
    glVertex2f(centerX + radius * 0.7f + 0.035f, centerY + radius * 0.7f + 0.035f);

    // Bottom-left
    glVertex2f(centerX - radius * 0.7f, centerY - radius * 0.7f);
    glVertex2f(centerX - radius * 0.7f - 0.035f, centerY - radius * 0.7f - 0.035f);

    // Bottom-right
    glVertex2f(centerX + radius * 0.7f, centerY - radius * 0.7f);
    glVertex2f(centerX + radius * 0.7f + 0.035f, centerY - radius * 0.7f - 0.035f);

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


void updateFire(int value) {
    // 🔥 Fire grow/shrink animation
    if (growing) {
        fireScale += 0.005f;
        if (fireScale >= 0.85f) growing = false;
    } else {
        fireScale -= 0.005f;
        if (fireScale <= 0.65f) growing = true;
    }

    // 🔄 Visibility trigger after 11 seconds
    if (!showFires) {
        fireTimer += 30; // Matches updateFire timer interval
        if (fireTimer >= 11000) {
            showFires = true;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(30, updateFire, 0); // restart timer
}


//fire 1
void drawFireFlame(float x = -0.45f, float y = -0.05f, float scale = 0.7f) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    // 🔴 Back flame (red layer)
    glColor3f(0.7f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.1f, 0.0f);
        glVertex2f(0.0f, 0.15f);
        glVertex2f(0.1f, 0.05f);
        glVertex2f(0.15f, 0.25f);
        glVertex2f(0.05f, 0.35f);
        glVertex2f(0.0f, 0.30f);
        glVertex2f(-0.05f, 0.35f);
        glVertex2f(-0.12f, 0.20f);
        glVertex2f(-0.1f, 0.0f);
    glEnd();

    // 🟠 Middle flame (orange)
    glColor3f(1.0f, 0.4f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.08f, 0.0f);
        glVertex2f(0.0f, 0.12f);
        glVertex2f(0.08f, 0.04f);
        glVertex2f(0.12f, 0.18f);
        glVertex2f(0.05f, 0.26f);
        glVertex2f(-0.04f, 0.25f);
        glVertex2f(-0.08f, 0.10f);
        glVertex2f(-0.08f, 0.0f);
    glEnd();

    // 🟡 Inner flame (yellow)
    glColor3f(1.0f, 0.9f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.04f, 0.0f);
        glVertex2f(0.0f, 0.07f);
        glVertex2f(0.03f, 0.02f);
        glVertex2f(0.06f, 0.14f);
        glVertex2f(0.0f, 0.18f);
        glVertex2f(-0.05f, 0.14f);
        glVertex2f(-0.04f, 0.0f);
    glEnd();

    glPopMatrix();

}


//fire 2
void drawFireFlame2(float x = -0.1f, float y = -0.05f, float scale = 0.5f) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    // 🔴 Back flame (red layer)
    glColor3f(0.7f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.1f, 0.0f);
        glVertex2f(0.0f, 0.15f);
        glVertex2f(0.1f, 0.05f);
        glVertex2f(0.15f, 0.25f);
        glVertex2f(0.05f, 0.35f);
        glVertex2f(0.0f, 0.30f);
        glVertex2f(-0.05f, 0.35f);
        glVertex2f(-0.12f, 0.20f);
        glVertex2f(-0.1f, 0.0f);
    glEnd();

    // 🟠 Middle flame (orange)
    glColor3f(1.0f, 0.4f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.08f, 0.0f);
        glVertex2f(0.0f, 0.12f);
        glVertex2f(0.08f, 0.04f);
        glVertex2f(0.12f, 0.18f);
        glVertex2f(0.05f, 0.26f);
        glVertex2f(-0.04f, 0.25f);
        glVertex2f(-0.08f, 0.10f);
        glVertex2f(-0.08f, 0.0f);
    glEnd();

    // 🟡 Inner flame (yellow)
    glColor3f(1.0f, 0.9f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.04f, 0.0f);
        glVertex2f(0.0f, 0.07f);
        glVertex2f(0.03f, 0.02f);
        glVertex2f(0.06f, 0.14f);
        glVertex2f(0.0f, 0.18f);
        glVertex2f(-0.05f, 0.14f);
        glVertex2f(-0.04f, 0.0f);
    glEnd();

    glPopMatrix();

}

//fire 3
void drawFireFlame3(float x = 0.3f, float y = -0.06f, float scale = 0.6f) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    // 🔴 Back flame (red layer)
    glColor3f(0.7f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.1f, 0.0f);
        glVertex2f(0.0f, 0.15f);
        glVertex2f(0.1f, 0.05f);
        glVertex2f(0.15f, 0.25f);
        glVertex2f(0.05f, 0.35f);
        glVertex2f(0.0f, 0.30f);
        glVertex2f(-0.05f, 0.35f);
        glVertex2f(-0.12f, 0.20f);
        glVertex2f(-0.1f, 0.0f);
    glEnd();

    // 🟠 Middle flame (orange)
    glColor3f(1.0f, 0.4f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.08f, 0.0f);
        glVertex2f(0.0f, 0.12f);
        glVertex2f(0.08f, 0.04f);
        glVertex2f(0.12f, 0.18f);
        glVertex2f(0.05f, 0.26f);
        glVertex2f(-0.04f, 0.25f);
        glVertex2f(-0.08f, 0.10f);
        glVertex2f(-0.08f, 0.0f);
    glEnd();

    // 🟡 Inner flame (yellow)
    glColor3f(1.0f, 0.9f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.04f, 0.0f);
        glVertex2f(0.0f, 0.07f);
        glVertex2f(0.03f, 0.02f);
        glVertex2f(0.06f, 0.14f);
        glVertex2f(0.0f, 0.18f);
        glVertex2f(-0.05f, 0.14f);
        glVertex2f(-0.04f, 0.0f);
    glEnd();

    glPopMatrix();

}

//fire 4
void drawFireFlame4(float x = 0.85f, float y = 0.08f, float scale = 0.7f) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    // 🔴 Back flame (red layer)
    glColor3f(0.7f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.1f, 0.0f);
        glVertex2f(0.0f, 0.15f);
        glVertex2f(0.1f, 0.05f);
        glVertex2f(0.15f, 0.25f);
        glVertex2f(0.05f, 0.35f);
        glVertex2f(0.0f, 0.30f);
        glVertex2f(-0.05f, 0.35f);
        glVertex2f(-0.12f, 0.20f);
        glVertex2f(-0.1f, 0.0f);
    glEnd();

    // 🟠 Middle flame (orange)
    glColor3f(1.0f, 0.4f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.08f, 0.0f);
        glVertex2f(0.0f, 0.12f);
        glVertex2f(0.08f, 0.04f);
        glVertex2f(0.12f, 0.18f);
        glVertex2f(0.05f, 0.26f);
        glVertex2f(-0.04f, 0.25f);
        glVertex2f(-0.08f, 0.10f);
        glVertex2f(-0.08f, 0.0f);
    glEnd();

    // 🟡 Inner flame (yellow)
    glColor3f(1.0f, 0.9f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.04f, 0.0f);
        glVertex2f(0.0f, 0.07f);
        glVertex2f(0.03f, 0.02f);
        glVertex2f(0.06f, 0.14f);
        glVertex2f(0.0f, 0.18f);
        glVertex2f(-0.05f, 0.14f);
        glVertex2f(-0.04f, 0.0f);
    glEnd();

    glPopMatrix();

}

//fire 5
void drawFireFlame5(float x = 0.87f, float y = -0.35f, float scale = 0.8f) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    // 🔴 Back flame (red layer)
    glColor3f(0.7f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.1f, 0.0f);
        glVertex2f(0.0f, 0.15f);
        glVertex2f(0.1f, 0.05f);
        glVertex2f(0.15f, 0.25f);
        glVertex2f(0.05f, 0.35f);
        glVertex2f(0.0f, 0.30f);
        glVertex2f(-0.05f, 0.35f);
        glVertex2f(-0.12f, 0.20f);
        glVertex2f(-0.1f, 0.0f);
    glEnd();

    // 🟠 Middle flame (orange)
    glColor3f(1.0f, 0.4f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.08f, 0.0f);
        glVertex2f(0.0f, 0.12f);
        glVertex2f(0.08f, 0.04f);
        glVertex2f(0.12f, 0.18f);
        glVertex2f(0.05f, 0.26f);
        glVertex2f(-0.04f, 0.25f);
        glVertex2f(-0.08f, 0.10f);
        glVertex2f(-0.08f, 0.0f);
    glEnd();

    // 🟡 Inner flame (yellow)
    glColor3f(1.0f, 0.9f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.04f, 0.0f);
        glVertex2f(0.0f, 0.07f);
        glVertex2f(0.03f, 0.02f);
        glVertex2f(0.06f, 0.14f);
        glVertex2f(0.0f, 0.18f);
        glVertex2f(-0.05f, 0.14f);
        glVertex2f(-0.04f, 0.0f);
    glEnd();

    glPopMatrix();

}

//fire 6
void drawFireFlame6(float x = 0.05f, float y = -0.5f, float scale = 0.9f) {
    glPushMatrix();
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    // 🔴 Back flame (red layer)
    glColor3f(0.7f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.1f, 0.0f);
        glVertex2f(0.0f, 0.15f);
        glVertex2f(0.1f, 0.05f);
        glVertex2f(0.15f, 0.25f);
        glVertex2f(0.05f, 0.35f);
        glVertex2f(0.0f, 0.30f);
        glVertex2f(-0.05f, 0.35f);
        glVertex2f(-0.12f, 0.20f);
        glVertex2f(-0.1f, 0.0f);
    glEnd();

    // 🟠 Middle flame (orange)
    glColor3f(1.0f, 0.4f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.08f, 0.0f);
        glVertex2f(0.0f, 0.12f);
        glVertex2f(0.08f, 0.04f);
        glVertex2f(0.12f, 0.18f);
        glVertex2f(0.05f, 0.26f);
        glVertex2f(-0.04f, 0.25f);
        glVertex2f(-0.08f, 0.10f);
        glVertex2f(-0.08f, 0.0f);
    glEnd();

    // 🟡 Inner flame (yellow)
    glColor3f(1.0f, 0.9f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.04f, 0.0f);
        glVertex2f(0.0f, 0.07f);
        glVertex2f(0.03f, 0.02f);
        glVertex2f(0.06f, 0.14f);
        glVertex2f(0.0f, 0.18f);
        glVertex2f(-0.05f, 0.14f);
        glVertex2f(-0.04f, 0.0f);
    glEnd();

    glPopMatrix();

}

void building1() {

    glColor3f(0.804f, 0.353f, 0.016f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.780f, -0.039f);
        glVertex2f(-0.510f, -0.037f);
        glVertex2f(-0.510f, 0.335f);
        glVertex2f(-0.780f, 0.335f);
    glEnd();

    // Side wall
    glColor3f(0.502f, 0.212f, 0.008f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.510f, -0.037f);
        glVertex2f(-0.480f, -0.022f);
        glVertex2f(-0.480f, 0.350f);
        glVertex2f(-0.510f, 0.335f);
    glEnd();

    // Roof top
    glColor3f(0.678f, 0.298f, 0.000f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.780f, 0.335f);
        glVertex2f(-0.510f, 0.335f);
        glVertex2f(-0.480f, 0.350f);
        glVertex2f(-0.750f, 0.350f);
    glEnd();

    // Draw windows
    drawWindowB1();                       // row 1
    drawWindowB1(0.081f);
    drawWindowB1(0.157f);

    drawWindowB1(0.0f, -0.083f);          // row 2
    drawWindowB1(0.081f, -0.083f);
    drawWindowB1(0.157f, -0.083f);

    drawWindowB1(0.0f, -0.167f);          // row 3
    drawWindowB1(0.081f, -0.167f);
    drawWindowB1(0.157f, -0.167f);

    drawWindowB1(0.0f, -0.251f);          // row 4
    drawWindowB1(0.081f, -0.251f);
    drawWindowB1(0.157f, -0.251f);
}




void building2() {
    glColor3f(0.463f, 0.184f, 0.063f);
    glBegin(GL_POLYGON);

        glVertex2f(0.502f, 0.073f);
        glVertex2f(0.594f, 0.158f);


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

    glColor3f(0.145f, 0.286f, 0.267f);
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

void building3() {
    glColor3f(0.804f, 0.353f, 0.016f);
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

void building4() {
    float xOffset = -0.3f;
    float yOffset = -0.01f;
    float scale = 0.7f;

    // Front wall – deep burgundy
    glColor3f(0.35f, 0.0f, 0.1f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.15f * scale + xOffset, -0.05f * scale + yOffset);
        glVertex2f( 0.15f * scale + xOffset, -0.05f * scale + yOffset);
        glVertex2f( 0.15f * scale + xOffset,  0.15f * scale + yOffset);
        glVertex2f(-0.15f * scale + xOffset,  0.15f * scale + yOffset);
    glEnd();

    // Right wall – dark maroon
    glColor3f(0.25f, 0.0f, 0.08f);
    glBegin(GL_POLYGON);
        glVertex2f(0.15f * scale + xOffset, -0.05f * scale + yOffset);
        glVertex2f(0.25f * scale + xOffset,  0.00f * scale + yOffset);
        glVertex2f(0.25f * scale + xOffset,  0.20f * scale + yOffset);
        glVertex2f(0.15f * scale + xOffset,  0.15f * scale + yOffset);
    glEnd();

    // Roof front – deep rust
    glColor3f(0.4f, 0.1f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.18f * scale + xOffset, 0.15f * scale + yOffset);
        glVertex2f( 0.18f * scale + xOffset, 0.15f * scale + yOffset);
        glVertex2f( 0.00f * scale + xOffset, 0.25f * scale + yOffset);
    glEnd();

    // Roof side – deep brown
    glColor3f(0.25f, 0.08f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(0.18f * scale + xOffset, 0.15f * scale + yOffset);
        glVertex2f(0.28f * scale + xOffset, 0.20f * scale + yOffset);
        glVertex2f(0.00f * scale + xOffset, 0.25f * scale + yOffset);
    glEnd();

    // Door – dark navy
    glColor3f(0.05f, 0.05f, 0.2f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.03f * scale + xOffset, -0.05f * scale + yOffset);
        glVertex2f( 0.03f * scale + xOffset, -0.05f * scale + yOffset);
        glVertex2f( 0.03f * scale + xOffset,  0.05f * scale + yOffset);
        glVertex2f(-0.03f * scale + xOffset,  0.05f * scale + yOffset);
    glEnd();

    // Left window – deep teal glass
    glColor3f(0.0f, 0.3f, 0.35f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.12f * scale + xOffset, 0.05f * scale + yOffset);
        glVertex2f(-0.07f * scale + xOffset, 0.05f * scale + yOffset);
        glVertex2f(-0.07f * scale + xOffset, 0.10f * scale + yOffset);
        glVertex2f(-0.12f * scale + xOffset, 0.10f * scale + yOffset);
    glEnd();

    // Right window – same as left
    glBegin(GL_POLYGON);
        glVertex2f(0.07f * scale + xOffset, 0.05f * scale + yOffset);
        glVertex2f(0.12f * scale + xOffset, 0.05f * scale + yOffset);
        glVertex2f(0.12f * scale + xOffset, 0.10f * scale + yOffset);
        glVertex2f(0.07f * scale + xOffset, 0.10f * scale + yOffset);
    glEnd();
}



void building5() {
    float xOffset = 0.05f;
    float yOffset = -0.01f;
    float scale = 0.7f;

    // Reuse the same structure as building4
    // You can copy the content from building4 here and just update xOffset
    glColor3f(0.58f, 0.29f, 0.00f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.15f * scale + xOffset, -0.05f * scale + yOffset);
        glVertex2f( 0.15f * scale + xOffset, -0.05f * scale + yOffset);
        glVertex2f( 0.15f * scale + xOffset,  0.15f * scale + yOffset);
        glVertex2f(-0.15f * scale + xOffset,  0.15f * scale + yOffset);
    glEnd();

    glColor3f(0.47f, 0.22f, 0.00f);
    glBegin(GL_POLYGON);
        glVertex2f(0.15f * scale + xOffset, -0.05f * scale + yOffset);
        glVertex2f(0.25f * scale + xOffset,  0.00f * scale + yOffset);
        glVertex2f(0.25f * scale + xOffset,  0.20f * scale + yOffset);
        glVertex2f(0.15f * scale + xOffset,  0.15f * scale + yOffset);
    glEnd();

    glColor3f(0.36f, 0.14f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.18f * scale + xOffset, 0.15f * scale + yOffset);
        glVertex2f( 0.18f * scale + xOffset, 0.15f * scale + yOffset);
        glVertex2f( 0.00f * scale + xOffset, 0.25f * scale + yOffset);
    glEnd();

    glColor3f(0.24f, 0.10f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(0.18f * scale + xOffset, 0.15f * scale + yOffset);
        glVertex2f(0.28f * scale + xOffset, 0.20f * scale + yOffset);
        glVertex2f(0.00f * scale + xOffset, 0.25f * scale + yOffset);
    glEnd();

    glColor3f(0.30f, 0.10f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.03f * scale + xOffset, -0.05f * scale + yOffset);
        glVertex2f( 0.03f * scale + xOffset, -0.05f * scale + yOffset);
        glVertex2f( 0.03f * scale + xOffset,  0.05f * scale + yOffset);
        glVertex2f(-0.03f * scale + xOffset,  0.05f * scale + yOffset);
    glEnd();

    glColor3f(0.0f, 0.3f, 0.3f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.12f * scale + xOffset, 0.05f * scale + yOffset);
        glVertex2f(-0.07f * scale + xOffset, 0.05f * scale + yOffset);
        glVertex2f(-0.07f * scale + xOffset, 0.10f * scale + yOffset);
        glVertex2f(-0.12f * scale + xOffset, 0.10f * scale + yOffset);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex2f(0.07f * scale + xOffset, 0.05f * scale + yOffset);
        glVertex2f(0.12f * scale + xOffset, 0.05f * scale + yOffset);
        glVertex2f(0.12f * scale + xOffset, 0.10f * scale + yOffset);
        glVertex2f(0.07f * scale + xOffset, 0.10f * scale + yOffset);
    glEnd();
}



void drawTree() {
    glColor3f(0.188f, 0.278f, 0.071f);
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
    glColor3f(0.306f, 0.149f, 0.043f);

        glVertex2f(-0.882f, 0.014f);
        glVertex2f(-0.859f, 0.014f);
        glVertex2f(-0.856f, -0.045f);
        glVertex2f(-0.884f, -0.045f);
    glEnd();
}

void drawTree2(float x = 0.4f, float y = -0.05f, float scale = 1.0f) {
    // Trunk (shorter height)
    glColor3f(0.396f, 0.157f, 0.063f); // Brown
    glBegin(GL_QUADS);
        glVertex2f(x - 0.03f * scale, y);
        glVertex2f(x + 0.03f * scale, y);
        glVertex2f(x + 0.03f * scale, y + 0.20f * scale);  // was 0.30f
        glVertex2f(x - 0.03f * scale, y + 0.20f * scale);
    glEnd();

    // Leaves (lowered + slightly smaller)
    Circle(x, y + 0.23f * scale, 0.06f * scale, 0.188f, 0.278f, 0.071f);
    Circle(x - 0.05f * scale, y + 0.22f * scale, 0.06f * scale, 0.188f, 0.278f, 0.071f);
    Circle(x + 0.05f * scale, y + 0.22f * scale, 0.06f * scale, 0.188f, 0.278f, 0.071f);
    Circle(x - 0.03f * scale, y + 0.27f * scale, 0.06f * scale, 0.188f, 0.278f, 0.071f);
    Circle(x + 0.03f * scale, y + 0.27f * scale, 0.06f * scale, 0.188f, 0.278f, 0.071f);
}

void drawSmallTree(float x = -0.75f, float y = -0.5f, float scale = 1.5f) {
    // Trunk
    glColor3f(0.396f, 0.157f, 0.063f); // Brown
    glBegin(GL_QUADS);
        glVertex2f(x - 0.01f * scale, y);
        glVertex2f(x + 0.01f * scale, y);
        glVertex2f(x + 0.01f * scale, y + 0.1f * scale);
        glVertex2f(x - 0.01f * scale, y + 0.1f * scale);
    glEnd();

    // Leaves
    Circle(x, y + 0.13f * scale, 0.04f * scale, 0.188f, 0.278f, 0.071f);
    Circle(x - 0.035f * scale, y + 0.1f * scale, 0.04f * scale, 0.188f, 0.278f, 0.071f);
    Circle(x + 0.035f * scale, y + 0.1f * scale, 0.04f * scale, 0.188f, 0.278f, 0.071f);
}


// Lake
void drawLake(float scale = 1.5f, float xOffset = -0.1f, float yOffset = 0.15f) {
    // Lake Body
    glColor3f(0.553f, 0.847f, 0.914f);
    glBegin(GL_POLYGON);
        glVertex2f((0.15f * scale) + xOffset, (-0.32f * scale) + yOffset);
        glVertex2f((0.25f * scale) + xOffset, (-0.42f * scale) + yOffset);
        glVertex2f((0.45f * scale) + xOffset, (-0.45f * scale) + yOffset);
        glVertex2f((0.60f * scale) + xOffset, (-0.40f * scale) + yOffset);
        glVertex2f((0.62f * scale) + xOffset, (-0.35f * scale) + yOffset);
        glVertex2f((0.58f * scale) + xOffset, (-0.30f * scale) + yOffset);
        glVertex2f((0.50f * scale) + xOffset, (-0.27f * scale) + yOffset);
        glVertex2f((0.35f * scale) + xOffset, (-0.25f * scale) + yOffset);
        glVertex2f((0.20f * scale) + xOffset, (-0.27f * scale) + yOffset);
    glEnd();

    // Lake Border
    glColor3f(0.306f, 0.149f, 0.043f);
    glLineWidth(2.5f);
    glBegin(GL_LINE_LOOP);
        glVertex2f((0.15f * scale) + xOffset, (-0.32f * scale) + yOffset);
        glVertex2f((0.25f * scale) + xOffset, (-0.42f * scale) + yOffset);
        glVertex2f((0.45f * scale) + xOffset, (-0.45f * scale) + yOffset);
        glVertex2f((0.60f * scale) + xOffset, (-0.40f * scale) + yOffset);
        glVertex2f((0.62f * scale) + xOffset, (-0.35f * scale) + yOffset);
        glVertex2f((0.58f * scale) + xOffset, (-0.30f * scale) + yOffset);
        glVertex2f((0.50f * scale) + xOffset, (-0.27f * scale) + yOffset);
        glVertex2f((0.35f * scale) + xOffset, (-0.25f * scale) + yOffset);
        glVertex2f((0.20f * scale) + xOffset, (-0.27f * scale) + yOffset);
    glEnd();

    // Reflections (light blue)
    glColor3f(0.788f, 0.933f, 0.973f);
    Circle((0.32f * scale) + xOffset, (-0.33f * scale) + yOffset, 0.015f * scale, 0.788f, 0.933f, 0.973f);
    Circle((0.42f * scale) + xOffset, (-0.37f * scale) + yOffset, 0.012f * scale, 0.788f, 0.933f, 0.973f);
    Circle((0.50f * scale) + xOffset, (-0.34f * scale) + yOffset, 0.010f * scale, 0.788f, 0.933f, 0.973f);
}




void car(float xOffset = -0.9f, float yOffset = -0.19f, float scale = 0.7f) {
    glPushMatrix();
    glTranslatef(xOffset, yOffset, 0.0f); // Position on the road

    // Lower body (Red)
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(0.0f * scale, 0.0f);
        glVertex2f(0.4f * scale, 0.0f);
        glVertex2f(0.39f * scale, 0.07f * scale);
        glVertex2f(0.0f * scale, 0.07f * scale);
    glEnd();

    // Upper body (Red)
    glBegin(GL_POLYGON);
        glVertex2f(0.05f * scale, 0.07f * scale);
        glVertex2f(0.35f * scale, 0.07f * scale);
        glVertex2f(0.30f * scale, 0.14f * scale);
        glVertex2f(0.10f * scale, 0.14f * scale);
    glEnd();

    // Window 1 (White)
    glColor3f(1.0f, 1.0f, 1.0f);
    glBegin(GL_POLYGON);
        glVertex2f(0.08f * scale, 0.07f * scale);
        glVertex2f(0.18f * scale, 0.07f * scale);
        glVertex2f(0.16f * scale, 0.13f * scale);
        glVertex2f(0.10f * scale, 0.13f * scale);
    glEnd();

    // Window 2 (White)
    glBegin(GL_POLYGON);
        glVertex2f(0.22f * scale, 0.07f * scale);
        glVertex2f(0.32f * scale, 0.07f * scale);
        glVertex2f(0.28f * scale, 0.13f * scale);
        glVertex2f(0.22f * scale, 0.13f * scale);
    glEnd();

    // Outer Wheels (Black)
    glColor3f(0.0f, 0.0f, 0.0f);
    Circle(0.10f * scale, 0.0f, 0.025f * scale, 0.0f, 0.0f, 0.0f);
    Circle(0.30f * scale, 0.0f, 0.025f * scale, 0.0f, 0.0f, 0.0f);

    // Inner Wheels (White)
    Circle(0.10f * scale, 0.0f, 0.015f * scale, 1.0f, 1.0f, 1.0f);
    Circle(0.30f * scale, 0.0f, 0.015f * scale, 1.0f, 1.0f, 1.0f);

    glPopMatrix();
}


void truck(float xOffset = 0.8f, float yOffset = -0.19f, float scale = 0.8f) {
    glPushMatrix();
    glTranslatef(xOffset, yOffset, 0.0f);

    // Truck body - back
    glColor3f(0.0f, 0.0f, 0.545f);
    glBegin(GL_POLYGON);
        glVertex2f(0.0f * scale, 0.0f);
        glVertex2f(-0.45f * scale, 0.0f);
        glVertex2f(-0.45f * scale, 0.14f * scale);
        glVertex2f(0.0f * scale, 0.14f * scale);
    glEnd();

    // Truck front - base
    glColor3f(1.0f, 0.8f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.45f * scale, 0.0f);
        glVertex2f(-0.65f * scale, 0.0f);
        glVertex2f(-0.65f * scale, 0.07f * scale);
        glVertex2f(-0.45f * scale, 0.07f * scale);
    glEnd();

    // Truck front - top
    glBegin(GL_POLYGON);
        glVertex2f(-0.45f * scale, 0.07f * scale);
        glVertex2f(-0.62f * scale, 0.07f * scale);
        glVertex2f(-0.57f * scale, 0.14f * scale);
        glVertex2f(-0.45f * scale, 0.14f * scale);
    glEnd();

    // Window
    glColor3f(0.86f, 0.86f, 0.86f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.45f * scale, 0.07f * scale);
        glVertex2f(-0.58f * scale, 0.07f * scale);
        glVertex2f(-0.55f * scale, 0.13f * scale);
        glVertex2f(-0.45f * scale, 0.13f * scale);
    glEnd();

    // Wheels - outer black
    Circle(-0.10f * scale, 0.0f, 0.025f * scale, 0.0f, 0.0f, 0.0f);
    Circle(-0.50f * scale, 0.0f, 0.025f * scale, 0.0f, 0.0f, 0.0f);

    // Wheels - inner white
    Circle(-0.10f * scale, 0.0f, 0.015f * scale, 1.0f, 1.0f, 1.0f);
    Circle(-0.50f * scale, 0.0f, 0.015f * scale, 1.0f, 1.0f, 1.0f);

    glPopMatrix();
}



void drawJet()
{
    glPushMatrix();
    glScalef(0.012f, 0.012f, 1.0f);
    glTranslatef(jetPlaneOffsetX, -10.0f, 0.0f);


    // left tail wing
    glColor3f(0.6,0.6,0.6);
    glBegin(GL_POLYGON);
    glVertex2f(5.5,47.0);
    glVertex2f(8.5,47.0);
    glVertex2f(5.5,48.0);
    glVertex2f(4.5,48.0);
    glEnd();

    // left front wing
    glColor3f(0.6,0.6,0.6);
    glBegin(GL_POLYGON);
    glVertex2f(13.0,47.0);
    glVertex2f(20.0,47.0);
    glVertex2f(13.0,50.0);
    glVertex2f(11.0,50.0);
    glEnd();

    // tail
    glColor3f(0.5,0.5,0.5);
    glBegin(GL_POLYGON);
    glVertex2f(4.7,45.0);
    glVertex2f(5.5,51.0);
    glVertex2f(7.0,51.0);
    glVertex2f(9.0,45.0);
    glEnd();

    // body
    glColor3f(0.5,0.5,0.5);
    glBegin(GL_POLYGON);
    glVertex2f(5.0,48.0);
    glVertex2f(11.0,48.0);
    glVertex2f(22.0,46.5);
    glVertex2f(22.0,45.0);
    glVertex2f(5.0,45.0);
    glEnd();

    // right front wing
    glColor3f(0.6,0.6,0.6);
    glBegin(GL_POLYGON);
    glVertex2f(13.0,46.0);
    glVertex2f(18.0,46.0);
    glVertex2f(13.0,41.0);
    glVertex2f(11.0,41.0);
    glEnd();

    // dome
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(13.0,47.0);
    glVertex2f(15.0,48.5);
    glVertex2f(17.0,49.0);
    glVertex2f(19.0,48.0);
    glVertex2f(21.0,46.0);
    glVertex2f(17.0,46.0);
    glVertex2f(15.0,47.5);
    glVertex2f(13.0,47.0);
    glEnd();

    // right tail wing
    glColor3f(0.6,0.6,0.6);
    glBegin(GL_POLYGON);
    glVertex2f(5.5,47.0);
    glVertex2f(8.5,47.0);
    glVertex2f(5.5,43.0);
    glVertex2f(4.5,43.0);
    glEnd();

    // front tip
    glColor3f(0.4,0.4,0.4);
    glBegin(GL_POLYGON);
    glVertex2f(22.0,45.0);
    glVertex2f(22.3,45.375);
    glVertex2f(22.6,45.75);
    glVertex2f(22.3,46.125);
    glVertex2f(22.0,46.5);
    glEnd();

    glPopMatrix();
}

void drawJet2()
{
    glPushMatrix();
    glScalef(0.012f, 0.012f, 1.0f);
    glTranslatef(jetPlaneOffsetX + 30.0f, -15.0f, 0.0f);
    // left tail wing
    glColor3f(0.6,0.6,0.6);
    glBegin(GL_POLYGON);
    glVertex2f(5.5,47.0);
    glVertex2f(8.5,47.0);
    glVertex2f(5.5,48.0);
    glVertex2f(4.5,48.0);
    glEnd();

    // left front wing
    glColor3f(0.6,0.6,0.6);
    glBegin(GL_POLYGON);
    glVertex2f(13.0,47.0);
    glVertex2f(20.0,47.0);
    glVertex2f(13.0,50.0);
    glVertex2f(11.0,50.0);
    glEnd();

    // tail
    glColor3f(0.5,0.5,0.5);
    glBegin(GL_POLYGON);
    glVertex2f(4.7,45.0);
    glVertex2f(5.5,51.0);
    glVertex2f(7.0,51.0);
    glVertex2f(9.0,45.0);
    glEnd();

    // body
    glColor3f(0.5,0.5,0.5);
    glBegin(GL_POLYGON);
    glVertex2f(5.0,48.0);
    glVertex2f(11.0,48.0);
    glVertex2f(22.0,46.5);
    glVertex2f(22.0,45.0);
    glVertex2f(5.0,45.0);
    glEnd();

    // right front wing
    glColor3f(0.6,0.6,0.6);
    glBegin(GL_POLYGON);
    glVertex2f(13.0,46.0);
    glVertex2f(18.0,46.0);
    glVertex2f(13.0,41.0);
    glVertex2f(11.0,41.0);
    glEnd();

    // dome
    glColor3f(0.0,0.0,0.0);
    glBegin(GL_POLYGON);
    glVertex2f(13.0,47.0);
    glVertex2f(15.0,48.5);
    glVertex2f(17.0,49.0);
    glVertex2f(19.0,48.0);
    glVertex2f(21.0,46.0);
    glVertex2f(17.0,46.0);
    glVertex2f(15.0,47.5);
    glVertex2f(13.0,47.0);
    glEnd();

    // right tail wing
    glColor3f(0.6,0.6,0.6);
    glBegin(GL_POLYGON);
    glVertex2f(5.5,47.0);
    glVertex2f(8.5,47.0);
    glVertex2f(5.5,43.0);
    glVertex2f(4.5,43.0);
    glEnd();

    // front tip
    glColor3f(0.4,0.4,0.4);
    glBegin(GL_POLYGON);
    glVertex2f(22.0,45.0);
    glVertex2f(22.3,45.375);
    glVertex2f(22.6,45.75);
    glVertex2f(22.3,46.125);
    glVertex2f(22.0,46.5);
    glEnd();

    glPopMatrix();


}

void drawPlane()
{
    if (!startPlane) return;
    glPushMatrix();
    glScalef(0.003f, 0.003f, 1.0f);
    glTranslatef(planeOffsetX, 90.0f, 0.0f);

    // rectangular body
    glColor3f(0.5,0.5,0.5);
    glBegin(GL_POLYGON);
    glVertex2f(0.0, 30.0);
    glVertex2f(0.0, 55.0);
    glVertex2f(135.0, 55.0);
    glVertex2f(135.0, 30.0);
    glEnd();

    // ---------------------
    // 1 Black Door (left side)
    // ---------------------
    // 1 Black Door (front right side)
glColor3f(0.0, 0.0, 0.0);
glBegin(GL_QUADS);
glVertex2f(110.0, 30.0);
glVertex2f(110.0, 45.0);
glVertex2f(125.0, 45.0);
glVertex2f(125.0, 30.0);
glEnd();


    // ---------------------
    // 4 Black Windows
    // ---------------------
    glBegin(GL_QUADS);

    // Window 1
    glVertex2f(35.0, 45.0);
    glVertex2f(35.0, 50.0);
    glVertex2f(45.0, 50.0);
    glVertex2f(45.0, 45.0);

    // Window 2
    glVertex2f(50.0, 45.0);
    glVertex2f(50.0, 50.0);
    glVertex2f(60.0, 50.0);
    glVertex2f(60.0, 45.0);

    // Window 3
    glVertex2f(65.0, 45.0);
    glVertex2f(65.0, 50.0);
    glVertex2f(75.0, 50.0);
    glVertex2f(75.0, 45.0);

    // Window 4
    glVertex2f(80.0, 45.0);
    glVertex2f(80.0, 50.0);
    glVertex2f(90.0, 50.0);
    glVertex2f(90.0, 45.0);

    glEnd();

    // upper triangle
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex2f(135.0, 55.0);
    glVertex2f(150.0, 50.0);
    glVertex2f(155.0, 45.0);
    glVertex2f(160.0, 40.0);
    glVertex2f(135.0, 40.0);
    glEnd();



    // lower triangle
    glColor3f(0.5, 0.5, 0.5);
    glBegin(GL_POLYGON);
    glVertex2f(135.0, 40.0);
    glVertex2f(160.0, 40.0);
    glVertex2f(160.0, 37.0);
    glVertex2f(145.0, 30.0);
    glVertex2f(135.0, 30.0);
    glEnd();

    // back wing
    glColor3f(0.6,0.6,0.6);
    glBegin(GL_POLYGON);
    glVertex2f(0.0, 55.0);
    glVertex2f(0.0, 80.0);
    glVertex2f(10.0, 80.0);
    glVertex2f(40.0, 55.0);
    glEnd();

    // left side wing
    glColor3f(0.6,0.6,0.6);
    glBegin(GL_POLYGON);
    glVertex2f(65.0, 55.0);
    glVertex2f(50.0, 70.0);
    glVertex2f(75.0, 70.0);
    glVertex2f(90.0, 55.0);
    glEnd();

    // rightside wing
    glColor3f(0.6,0.6,0.6);
    glBegin(GL_POLYGON);
    glVertex2f(70.0, 40.0);
    glVertex2f(100.0, 40.0);
    glVertex2f(80.0, 15.0);
    glVertex2f(50.0, 15.0);
    glEnd();

    glPopMatrix();
}



void drawRocket() {
    glPushMatrix();

    glTranslatef(0.05f, rocketY, 0.0f);
    glRotatef(180, 0.0f, 0.0f, 1.0f);
    glScalef(0.4f, 0.4f, 1.0f);

    glLineWidth(2.0f);  // Set border thickness

    // ===== BODY =====
    // Border
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.05f, -0.525f);
        glVertex2f( 0.05f, -0.525f);
        glVertex2f( 0.05f, -0.3375f);
        glVertex2f(-0.05f, -0.3375f);
    glEnd();

    // Fill
    glColor3f(0.50f, 0.55f, 0.55f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.05f, -0.525f);
        glVertex2f( 0.05f, -0.525f);
        glVertex2f( 0.05f, -0.3375f);
        glVertex2f(-0.05f, -0.3375f);
    glEnd();

    // ===== CONE =====
    // Border
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.05f, -0.3375f);
        glVertex2f( 0.05f, -0.3375f);
        glVertex2f( 0.0f,  -0.225f);
    glEnd();

    // Fill
    glColor3f(0.17f, 0.24f, 0.31f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.05f, -0.3375f);
        glVertex2f( 0.05f, -0.3375f);
        glVertex2f( 0.0f,  -0.225f);
    glEnd();

    // ===== LEFT WING =====
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.05f, -0.525f);
        glVertex2f(-0.15f, -0.525f);
        glVertex2f(-0.05f, -0.4375f);
    glEnd();

    glColor3f(0.17f, 0.24f, 0.31f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.05f, -0.525f);
        glVertex2f(-0.15f, -0.525f);
        glVertex2f(-0.05f, -0.4375f);
    glEnd();

    // ===== RIGHT WING =====
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(0.05f, -0.525f);
        glVertex2f(0.15f, -0.525f);
        glVertex2f(0.05f, -0.4375f);
    glEnd();

    glColor3f(0.17f, 0.24f, 0.31f);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.05f, -0.525f);
        glVertex2f(0.15f, -0.525f);
        glVertex2f(0.05f, -0.4375f);
    glEnd();


    // Flames (Outer)
    glColor3f(1.0f, 0.25f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.05f, -0.525f);
        glVertex2f(-0.08f, -0.56f);
        glVertex2f(-0.04f, -0.6f);
        glVertex2f(0.0f, -0.625f);
        glVertex2f(0.04f, -0.6f);
        glVertex2f(0.08f, -0.56f);
        glVertex2f(0.05f, -0.525f);
    glEnd();

    // Flames (Inner)
    glColor3f(1.0f, 0.816f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.03f, -0.525f);
        glVertex2f(0.0f, -0.58f);
        glVertex2f(0.03f, -0.525f);
    glEnd();
    glColor3f(1.0f, 0.816f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.03f, -0.525f);
        glVertex2f(0.0f, -0.58f);
        glVertex2f(0.03f, -0.525f);
    glEnd();
// ===== NUCLEAR SYMBOL =====
float cx = 0.0f, cy = -0.44f;  // Position on rocket body
float scale = 1.5f;            // Adjust this for size (1.0 = normal)

// Translate to center, then scale
glTranslatef(cx, cy, 0.0f);
glScalef(scale, scale, 1.0f);

// Draw logo at (0,0) because we've translated
float R = 0.025f;
float bladeLength = R * 0.9f;
float bladeAngle = 3.1416f / 6.0f;  // 30 degrees

// Outer yellow circle
Circle(0.0f, 0.0f, R, 1.0f, 1.0f, 0.0f);  // Yellow

// 3 black blades
glColor3f(0.0f, 0.0f, 0.0f);
for (int i = 0; i < 3; i++) {
    float angle = i * 2.0f * 3.1416f / 3;
    float a1 = angle - bladeAngle;
    float a2 = angle + bladeAngle;

    glBegin(GL_TRIANGLES);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(cos(a1) * bladeLength, sin(a1) * bladeLength);
        glVertex2f(cos(a2) * bladeLength, sin(a2) * bladeLength);
    glEnd();
}

// Inner black circle
Circle(0.0f, 0.0f, R * 0.25f, 0.0f, 0.0f, 0.0f);  // Black
    glPopMatrix();

}


// === Explosion effect ===
void drawExplosion(float x, float y, float radius) {
    // Outer glow
    glColor4f(1.0f, 0.6f, 0.1f, 0.4f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y);
        for (int i = 0; i <= 50; i++) {
            float angle = 2.0f * 3.1416f * i / 50;
            glVertex2f(x + cos(angle) * radius * 1.8f, y + sin(angle) * radius * 1.8f);
        }
    glEnd();

    // Middle bright core
    glColor3f(1.0f, 0.9f, 0.1f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y);
        for (int i = 0; i <= 50; i++) {
            float angle = 2.0f * 3.1416f * i / 50;
            glVertex2f(x + cos(angle) * radius, y + sin(angle) * radius);
        }
    glEnd();

    // Inner reddish spark
    glColor3f(1.0f, 0.3f, 0.0f);
    glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y);
        for (int i = 0; i <= 30; i++) {
            float angle = 2.0f * 3.1416f * i / 30;
            glVertex2f(x + cos(angle) * radius * 0.4f, y + sin(angle) * radius * 0.4f);
        }
    glEnd();
}

void drawRocket2() {
    glPushMatrix();

    glTranslatef(-0.3f, 0.15f, 0.0f);
    glRotatef(-135, 0.0f, 0.0f, 1.0f);
    glScalef(0.2f, 0.2f, 1.0f);

    glLineWidth(2.0f);  // Set border thickness

    // ===== BODY =====
    // Border
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.05f, -0.525f);
        glVertex2f( 0.05f, -0.525f);
        glVertex2f( 0.05f, -0.3375f);
        glVertex2f(-0.05f, -0.3375f);
    glEnd();

    // Fill
    glColor3f(0.663f, 0.663f, 0.663f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.05f, -0.525f);
        glVertex2f( 0.05f, -0.525f);
        glVertex2f( 0.05f, -0.3375f);
        glVertex2f(-0.05f, -0.3375f);
    glEnd();

    // ===== CONE =====
    // Border
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.05f, -0.3375f);
        glVertex2f( 0.05f, -0.3375f);
        glVertex2f( 0.0f,  -0.225f);
    glEnd();

    // Fill
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.05f, -0.3375f);
        glVertex2f( 0.05f, -0.3375f);
        glVertex2f( 0.0f,  -0.225f);
    glEnd();

    // ===== LEFT WING =====
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.05f, -0.525f);
        glVertex2f(-0.15f, -0.525f);
        glVertex2f(-0.05f, -0.4375f);
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.05f, -0.525f);
        glVertex2f(-0.15f, -0.525f);
        glVertex2f(-0.05f, -0.4375f);
    glEnd();

    // ===== RIGHT WING =====
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(0.05f, -0.525f);
        glVertex2f(0.15f, -0.525f);
        glVertex2f(0.05f, -0.4375f);
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.05f, -0.525f);
        glVertex2f(0.15f, -0.525f);
        glVertex2f(0.05f, -0.4375f);
    glEnd();


    // Flames (Outer)
    glColor3f(1.0f, 0.25f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.05f, -0.525f);
        glVertex2f(-0.08f, -0.56f);
        glVertex2f(-0.04f, -0.6f);
        glVertex2f(0.0f, -0.625f);
        glVertex2f(0.04f, -0.6f);
        glVertex2f(0.08f, -0.56f);
        glVertex2f(0.05f, -0.525f);
    glEnd();

    // Flames (Inner)
    glColor3f(1.0f, 0.816f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.03f, -0.525f);
        glVertex2f(0.0f, -0.58f);
        glVertex2f(0.03f, -0.525f);
    glEnd();

    glPopMatrix();

}

void drawRocket3() {
    glPushMatrix();

    glTranslatef(-0.7f, 0.15f, 0.0f);
    glRotatef(-135, 0.0f, 0.0f, 1.0f);
    glScalef(0.2f, 0.2f, 1.0f);

    glLineWidth(2.0f);  // Set border thickness

    // ===== BODY =====
    // Border
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.05f, -0.525f);
        glVertex2f( 0.05f, -0.525f);
        glVertex2f( 0.05f, -0.3375f);
        glVertex2f(-0.05f, -0.3375f);
    glEnd();

    // Fill
    glColor3f(0.663f, 0.663f, 0.663f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.05f, -0.525f);
        glVertex2f( 0.05f, -0.525f);
        glVertex2f( 0.05f, -0.3375f);
        glVertex2f(-0.05f, -0.3375f);
    glEnd();

    // ===== CONE =====
    // Border
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.05f, -0.3375f);
        glVertex2f( 0.05f, -0.3375f);
        glVertex2f( 0.0f,  -0.225f);
    glEnd();

    // Fill
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.05f, -0.3375f);
        glVertex2f( 0.05f, -0.3375f);
        glVertex2f( 0.0f,  -0.225f);
    glEnd();

    // ===== LEFT WING =====
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.05f, -0.525f);
        glVertex2f(-0.15f, -0.525f);
        glVertex2f(-0.05f, -0.4375f);
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(-0.05f, -0.525f);
        glVertex2f(-0.15f, -0.525f);
        glVertex2f(-0.05f, -0.4375f);
    glEnd();

    // ===== RIGHT WING =====
    glColor3f(0.0f, 0.0f, 0.0f);
    glBegin(GL_LINE_LOOP);
        glVertex2f(0.05f, -0.525f);
        glVertex2f(0.15f, -0.525f);
        glVertex2f(0.05f, -0.4375f);
    glEnd();

    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(0.05f, -0.525f);
        glVertex2f(0.15f, -0.525f);
        glVertex2f(0.05f, -0.4375f);
    glEnd();


    // Flames (Outer)
    glColor3f(1.0f, 0.25f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.05f, -0.525f);
        glVertex2f(-0.08f, -0.56f);
        glVertex2f(-0.04f, -0.6f);
        glVertex2f(0.0f, -0.625f);
        glVertex2f(0.04f, -0.6f);
        glVertex2f(0.08f, -0.56f);
        glVertex2f(0.05f, -0.525f);
    glEnd();

    // Flames (Inner)
    glColor3f(1.0f, 0.816f, 0.0f);
    glBegin(GL_POLYGON);
        glVertex2f(-0.03f, -0.525f);
        glVertex2f(0.0f, -0.58f);
        glVertex2f(0.03f, -0.525f);
    glEnd();

    glPopMatrix();

}



void drawBench(float x = -0.6f, float y = -0.4f, float scale = 0.4f) {
    glPushMatrix();

    // Move origin to (x, y), then scale entire bench
    glTranslatef(x, y, 0.0f);
    glScalef(scale, scale, 1.0f);

    // Color values
    float grayR = 0.8f, grayG = 0.8f, grayB = 0.8f;
    float orangeR = 0.96f, orangeG = 0.52f, orangeB = 0.29f;

    // Dimensions
    float legW = 0.025f, legH = 0.15f;
    float slatW = 0.4f, slatH = 0.035f, slatSpacing = 0.02f;
    float supportW = 0.02f;
    float seatY = legH;
    float backStartY = seatY + 0.04f;
    float supportH = slatH * 3 + slatSpacing * 2;

    // === Legs ===
    glColor3f(grayR, grayG, grayB);
    float legX[] = {0.0f, 0.1f, 0.25f, 0.35f};
    for (int i = 0; i < 4; i++) {
        float lx = legX[i];
        glBegin(GL_QUADS);
            glVertex2f(lx, 0.0f);
            glVertex2f(lx + legW, 0.0f);
            glVertex2f(lx + legW, legH);
            glVertex2f(lx, legH);
        glEnd();
    }

    // === Backrest Supports ===
    float supportX[] = {0.05f, 0.32f};
    glColor3f(grayR, grayG, grayB);
    for (int i = 0; i < 2; i++) {
        float sx = supportX[i];
        glBegin(GL_QUADS);
            glVertex2f(sx, backStartY);
            glVertex2f(sx + supportW, backStartY);
            glVertex2f(sx + supportW, backStartY + supportH);
            glVertex2f(sx, backStartY + supportH);
        glEnd();
    }

    // === Backrest Slats ===
    glColor3f(orangeR, orangeG, orangeB);
    for (int i = 0; i < 3; i++) {
        float by = backStartY + i * (slatH + slatSpacing);
        glBegin(GL_QUADS);
            glVertex2f(0.0f, by);
            glVertex2f(slatW, by);
            glVertex2f(slatW, by + slatH);
            glVertex2f(0.0f, by + slatH);
        glEnd();
    }

    // === Seat Slat (slanted) ===
    glBegin(GL_QUADS);
        glVertex2f(-0.01f, seatY);
        glVertex2f(slatW + 0.01f, seatY);
        glVertex2f(slatW, seatY + slatH);
        glVertex2f(0.0f, seatY + slatH);
    glEnd();

    // === Outlines ===
    glColor3f(0.0f, 0.0f, 0.0f);

    // Backrest Slats
    for (int i = 0; i < 3; i++) {
        float by = backStartY + i * (slatH + slatSpacing);
        glBegin(GL_LINE_LOOP);
            glVertex2f(0.0f, by);
            glVertex2f(slatW, by);
            glVertex2f(slatW, by + slatH);
            glVertex2f(0.0f, by + slatH);
        glEnd();
    }

    // Seat
    glBegin(GL_LINE_LOOP);
        glVertex2f(-0.01f, seatY);
        glVertex2f(slatW + 0.01f, seatY);
        glVertex2f(slatW, seatY + slatH);
        glVertex2f(0.0f, seatY + slatH);
    glEnd();

    // Legs
    for (int i = 0; i < 4; i++) {
        float lx = legX[i];
        glBegin(GL_LINE_LOOP);
            glVertex2f(lx, 0.0f);
            glVertex2f(lx + legW, 0.0f);
            glVertex2f(lx + legW, legH);
            glVertex2f(lx, legH);
        glEnd();
    }

    // Backrest Supports
    for (int i = 0; i < 2; i++) {
        float sx = supportX[i];
        glBegin(GL_LINE_LOOP);
            glVertex2f(sx, backStartY);
            glVertex2f(sx + supportW, backStartY);
            glVertex2f(sx + supportW, backStartY + supportH);
            glVertex2f(sx, backStartY + supportH);
        glEnd();
    }

    glPopMatrix();
}



void drawBackground() {
    // background
    glBegin(GL_QUADS);
        glColor3f(0.51f, 0.08, 0.0f);
        glVertex2f(-1.0f, 0.5625f);
        glVertex2f(1.0f, 0.5625f);

        glColor3f(0.831f, 0.333f, 0.078f);
        glVertex2f(1.0f, 0.0f);
        glVertex2f(-1.0f, 0.0f);

    glEnd();

    glBegin(GL_QUADS);
        glColor3f(0.443f, 0.404f, 0.078f);
        glVertex2f(-1.0f, 0.0f);
        glVertex2f(1.0f, 0.0f);

        glColor3f(0.443f, 0.404f, 0.078f);
        glVertex2f(1.0f, -0.5625f);
        glVertex2f(-1.0f, -0.5625f);

    glEnd();

    // road
    glColor3f(0.204f, 0.224f, 0.118f);
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, -0.073f);
        glVertex2f(1.0f, -0.073f);
        glVertex2f(1.0f, -0.213f);
        glVertex2f(-1.0f, -0.213f);
    glEnd();

    glColor3f(0.878f, 0.514f, 0.133f);
    glLineWidth(7.0f);
    glBegin(GL_LINES);
        glVertex2f(-1.0f, -0.073f);
        glVertex2f(1.0f, -0.073f);
    glEnd();

    //walking road

glColor3f(0.878f, 0.514f, 0.133f);
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
// Road
glColor3f(0.204f, 0.224f, 0.118f);
glBegin(GL_QUADS);
    glVertex2f(-1.0f, -0.073f);
    glVertex2f(1.0f, -0.073f);
    glVertex2f(1.0f, -0.213f);
    glVertex2f(-1.0f, -0.213f);
glEnd();


glColor3f(0.878f, 0.514f, 0.133f);
glLineWidth(7.0f);
glBegin(GL_LINES);
    glVertex2f(-1.0f, -0.073f);
    glVertex2f(1.0f, -0.073f);
glEnd();


    // Hills
    glColor3f(0.333f, 0.420f, 0.184f);
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

        float y = randAmp * sinf(frequency * 3.1416f * x) + 0.27;
        glVertex2f(x, y);
        glVertex2f(x, 0.0f);
    }
    glEnd();
}

void mergeComponents() {
    drawBackground();
    drawSun();
    cloud();
    drawTree();
    drawTree2();
    building1();
    building2();
    building3();
    building4();
    building5();
    drawLake();
    car(carPos, -0.1f, 0.7f);
truck(truckPos, -0.2f, 0.8f);

    drawSmallTree();
    if (showFires) {
    drawFireFlame(-0.45f, -0.05f, fireScale);
    drawFireFlame2(-0.1f, -0.05f, fireScale);
    drawFireFlame3(0.3f, -0.06f, fireScale);
    drawFireFlame4(0.85f, 0.08f, fireScale);
    drawFireFlame5(0.87f, -0.35f, fireScale);
    drawFireFlame6(0.05f, -0.5f, fireScale);
}
    drawJet();
    drawJet2();
    drawPlane();
    if (showRocket) {
    drawRocket();
}

    // === RENDER ROCKETS WITH ANIMATION ===
if (showRockets && !explodeRocket2) {
    glPushMatrix();
    glTranslatef(0.0f, rocket2Y, 0.0f);  // Apply animated Y position
    drawRocket2();
    glPopMatrix();
}

if (showRockets && !explodeRocket3) {
    glPushMatrix();
    glTranslatef(0.0f, rocket3Y, 0.0f);  // Apply animated Y position
    drawRocket3();
    glPopMatrix();
}

// === RENDER EXPLOSION EFFECTS ===
if (explodeRocket2) {
    drawExplosion(-0.3f, -0.213f, explosionRadius);
}
if (explodeRocket3) {
    drawExplosion(-0.7f, -0.213f, explosionRadius);
}

    drawBench();

}


//plane jets animation
void updateAnimation(int value) {
    jetSoundTimer += 16; // increase by ~16ms (60 FPS)

    // Start sound after 6 sec (6000 ms)
    if (jetSoundTimer >= 6000 && !jetSoundPlaying) {
        PlaySound("jet.wav", NULL, SND_FILENAME | SND_ASYNC);
        jetSoundPlaying = true;
    }

    // Stop sound after 12 sec total (6 sec of playing)
    if (jetSoundPlaying && jetSoundTimer >= 12000) {
        PlaySound(NULL, 0, 0); // stop sound
        jetSoundPlaying = false;
    }

    // === JET MOVEMENT ===
    if (jetPlaneOffsetX < 150.0f) {
        jetPlaneOffsetX += 0.5f;
    } else {
        startPlane = true;
    }

    // === PLANE MOVEMENT ===
    if (startPlane && planeOffsetX < 500.0f) {
        planeOffsetX += 1.5f;
    }

    glutPostRedisplay();
    glutTimerFunc(16, updateAnimation, 0);
}



//car truck animation
void updateVehicles(int value) {
    // Play sound once for 10 seconds
    if (!vehicleSoundPlayed) {
        PlaySound("traffic.wav", NULL, SND_FILENAME | SND_ASYNC);  // Replace with your .wav file
        vehicleSoundPlayed = true;
        vehicleSoundTimer = 0;
    }

    if (vehicleSoundPlayed && vehicleSoundTimer < 10000) {
        vehicleSoundTimer += 16;
    } else if (vehicleSoundTimer >= 10000) {
        PlaySound(NULL, NULL, 0); // Stop sound
    }

    // CAR MOVEMENT
    if (carState == 0) {
        carPos += 0.004f;
        if (carPos > 1.2f) {
            carPos = -1.2f;
            carState = 1;
        }
    } else if (carState == 1) {
        carPos += 0.004f;
        if (carPos >= -0.8f) {
            carPos = -0.8f;
            carState = 2;
        }
    }

    // TRUCK MOVEMENT
    if (truckState == 0) {
        truckPos -= 0.004f;
        if (truckPos < -1.2f) {
            truckPos = 1.2f;
            truckState = 1;
        }
    } else if (truckState == 1) {
        truckPos -= 0.004f;
        if (truckPos <= 0.7f) {
            truckPos = 0.7f;
            truckState = 2;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, updateVehicles, 0);
}


bool rocketSoundStarted = false;
//MISSILE ANIMATION
void updateRockets(int value) {
    if (!showRockets && value == 0) {
        showRockets = true;
        glutTimerFunc(16, updateRockets, 1);
        return;
    }

    if (showRockets && !explodeRocket2) {
        rocket2Y -= 0.005f;
        rocket3Y -= 0.005f;

        if (rocket2Y <= -0.213f) {
            rocket2Y = -0.213f;
            explodeRocket2 = true;
        }
        if (rocket3Y <= -0.213f) {
            rocket3Y = -0.213f;
            explodeRocket3 = true;
        }
    }

    // 💥 Play sound once when explosion starts
    if ((explodeRocket2 || explodeRocket3) && !rocketSoundStarted) {
        PlaySound(TEXT("Explosion.wav"), NULL, SND_FILENAME | SND_ASYNC);
        rocketSoundStarted = true;
    }

    if ((explodeRocket2 || explodeRocket3) && explosionRadius < 0.07f) {
        explosionRadius += 0.004f;
    }

    if (explodeRocket2 || explodeRocket3) {
        explosionTime += 16;
        if (explosionTime >= 2000) { // 2 seconds
            hideRocket2 = true;
            hideRocket3 = true;
            explosionRadius = 0.0f;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, updateRockets, 1);
}



// === Big MIISILE animation  ===
void updateRocketFall(int value) {
    if (!showRocket) {
        rocketTimer += 16;
        if (rocketTimer >= 20000) { // 20 seconds = 20000 ms
            showRocket = true;
            startRocketFall = true;
        }
    } else if (startRocketFall && rocketY > -0.21f) {
        rocketY -= 0.0015f; // Slow fall
    }

    glutPostRedisplay();
    glutTimerFunc(16, updateRocketFall, 0);
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
    glutCreateWindow("Scenario 2"); // Create window

    glutDisplayFunc(display);   // Register display callback
    glutReshapeFunc(reshape);   // Register reshape callback

    initGL();                   // Set initial OpenGL state

    glutTimerFunc(0, updateFire, 0);
    glutTimerFunc(0, updateVehicles, 0); // Start vehicle animation
    glutTimerFunc(8000, updateRockets, 0);
    glutTimerFunc(0, updateAnimation, 0);
    glutTimerFunc(0, updateRocketFall, 0);
    glutMainLoop();             // Start main loop
    return 0;
}
