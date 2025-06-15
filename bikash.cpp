#include <GL/glut.h>
#include <math.h>
#include <iostream>

using namespace std;

bool isNight = false;
bool isRaining = false;
int car1X = 0;     // Starting X position of car 1 (left to right)
int car2X = 1180;  // Starting X position of car 2 (right to left, assuming car width ~100)

bool isMoving = false; // Is the cars moving or stopped

float scaleX = 2.0f / 1280.0f;
float scaleY = 1.125f / 720.0f;
float offsetX = -1.0f;
float offsetY = -0.5625f;

float normX(float x) { return x * scaleX + offsetX; }
float normY(float y) { return y * scaleY + offsetY; }

#define VTX(x, y) glVertex2f(normX(x), normY(y))

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -0.5625, 0.5625);
}

void Circle(float centerX, float centerY, float radius, float rColor, float gColor, float bColor) {
    glColor3f(rColor, gColor, bColor);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float pi = 3.1416;
        float angle = (i * 2 * pi) / 180;
        float x = radius * cos(angle);
        float y = radius * sin(angle);
        VTX(centerX + x, centerY + y);
    }
    glEnd();
}

void Rectangle(float x, float y, float width, float height, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    VTX(x, y);
    VTX(x + width, y);
    VTX(x + width, y + height);
    VTX(x, y + height);
    glEnd();
}

void Tree(float x, float y) {
    // Trunk color changes a bit for night (darker)
    if (isNight) {
        Rectangle(x, y, 20, 50, 0.3f, 0.15f, 0.04f); // darker brown
    } else {
        Rectangle(x, y, 20, 50, 0.545f, 0.271f, 0.075f); // original brown
    }

    // Leaves color changes for night (darker greens)
    if (isNight) {
        Circle(x + 10, y + 60, 30, 0.0f, 0.2f, 0.0f);
        Circle(x - 10, y + 50, 25, 0.0f, 0.25f, 0.0f);
        Circle(x + 30, y + 50, 25, 0.0f, 0.25f, 0.0f);
        Circle(x + 10, y + 80, 25, 0.0f, 0.3f, 0.0f);
    } else {
        Circle(x + 10, y + 60, 30, 0.0f, 0.5f, 0.0f);
        Circle(x - 10, y + 50, 25, 0.0f, 0.6f, 0.0f);
        Circle(x + 30, y + 50, 25, 0.0f, 0.6f, 0.0f);
        Circle(x + 10, y + 80, 25, 0.0f, 0.7f, 0.0f);
    }
}

void drawTreeNorm(int x, int y) {
    // Temporarily push matrix to scale/translate for normalization
    glPushMatrix();
    glTranslatef(normX(x), normY(y), 0.0f);
    glScalef(1.0f / 1280.0f * 2.0f, 1.0f / 720.0f * 1.125f, 1.0f);
    Tree(0, 0); // draw at origin in normalized space
    glPopMatrix();
}


void Sky() {
    if (isNight) {
        glColor3ub(10, 10, 50); // dark blue
        glBegin(GL_QUADS);
        glVertex2f(-1.0f, normY(360));
        glVertex2f(1.0f, normY(360));
        glVertex2f(1.0f, 1.0f);
        glVertex2f(-1.0f, 1.0f);
        glEnd();

        float cx = normX(1100), cy = normY(600), radius = 0.05f;
        int segments = 50;
        glColor3ub(255, 255, 255);
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);
        for (int i = 0; i <= segments; i++) {
            float theta = 2.0f * M_PI * i / segments;
            glVertex2f(cx + radius * cos(theta), cy + radius * sin(theta));
        }

        glEnd();
    } else {
        glColor3ub(135, 206, 235); // sky blue
        glBegin(GL_QUADS);
        glVertex2f(-1.0f, normY(360));
        glVertex2f(1.0f, normY(360));
        glVertex2f(1.0f, 1.0f);
        glVertex2f(-1.0f, 1.0f);
        glEnd();

        // Sun
        float cx = normX(1100), cy = normY(600), radius = 0.05f;
        int segments = 50;
        glColor3ub(255, 223, 0);
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(cx, cy);
        for (int i = 0; i <= segments; i++) {
            float theta = 2.0f * M_PI * i / segments;
            glVertex2f(cx + radius * cos(theta), cy + radius * sin(theta));
        }
        glEnd();
    }
}



void drawModernBuilding1(int x, int y) {
    Rectangle(x, y, 60, 180, 0.1f, 0.1f, 0.3f);
    for (int i = 10; i < 170; i += 20) {
        Rectangle(x + 5, y + i, 50, 10, 0.3f, 0.7f, 1.0f);
    }
}

void drawModernBuilding2(int x, int y) {
    Rectangle(x, y, 80, 240, 0.3f, 0.2f, 0.5f);
    for (int i = 15; i < 70; i += 20) {
        Rectangle(x + i, y + 20, 10, 200, 0.6f, 0.9f, 1.0f);
    }
}

void drawModernBuilding3(int x, int y) {
    Rectangle(x, y, 60, 70, 0.5f, 0.5f, 0.5f);
    Rectangle(x, y + 70, 60, 80, 0.2f, 0.6f, 0.8f);
}

float cloudOffsetX = 0.0f; // Global variable

void Cloud() {
    int coords[][2] = {
        {32, 630}, {74, 630}, {116, 630}, {74, 650},
        {212, 675}, {254, 675}, {296, 675}, {254, 695},
        {712, 675}, {754, 675}, {796, 675}, {754, 695},
        {912, 655}, {954, 655}, {996, 655}, {954, 675}
    };
    for (int i = 0; i < 16; ++i) {
        float x = coords[i][0] + cloudOffsetX;
        float y = coords[i][1];
        // Wrap clouds around the screen width (1280)
        if (x > 1280) x -= 1280;
        Circle(x, y, 30, 0.90, 0.90, 0.90);
    }
}


void updateClouds(int value) {
    cloudOffsetX += 0.5f; // Speed of clouds
    if (cloudOffsetX > 1280) cloudOffsetX -= 1280; // Wrap around
    glutPostRedisplay(); // Request redraw
    glutTimerFunc(30, updateClouds, 0); // Call again after 30ms
}


void Mountains() {
    for (int i = 0; i < 1280; i += 120) {
        glBegin(GL_TRIANGLES);
        if (isNight) {
            glColor3f(0.05f, 0.20f, 0.05f);  // darker green for night
        } else {
            glColor3f(0.0f, 0.50f, 0.0f);    // normal green for day
        }
        VTX(i, 450);
        VTX(i + 120, 450);
        VTX(i + 60, 504);
        glEnd();
    }
}

void Building(float x, float y) {
    int floors = 7;
    float floorHeight = 27;
    float buildingWidth = 96;
    float buildingHeight = floors * floorHeight;

    // Building base color changes for day/night
    if (isNight) {
        // Darker building color at night
        Rectangle(x, y, buildingWidth, buildingHeight, 0.1f, 0.1f, 0.3f);
    } else {
        // Lighter building color during day
        Rectangle(x, y, buildingWidth, buildingHeight, 0.7f, 0.7f, 0.7f);
    }

    // Window colors — lighter during day, dimmer at night
    float winR = isNight ? 0.3f : 0.6f;
    float winG = isNight ? 0.4f : 0.85f;
    float winB = isNight ? 0.5f : 0.95f;

    for (int i = 1; i < floors; i++) {
        float winY = y + i * floorHeight + 5;
        Rectangle(x + 10, winY, 20, 20, winR, winG, winB);
        Rectangle(x + 66, winY, 20, 20, winR, winG, winB);

        // Window frame color: dark always
        glColor3f(0.1f, 0.1f, 0.1f);
        glBegin(GL_LINE_LOOP);
        VTX(x + 5, winY + 25);
        VTX(x + buildingWidth - 5, winY + 25);
        VTX(x + buildingWidth - 5, winY + 22);
        VTX(x + 5, winY + 22);
        glEnd();
    }


    if (isNight) {
        Rectangle(x + 38, y, 20, 30, 0.2f, 0.15f, 0.1f);  // Darker door at night
        Rectangle(x - 5, y + buildingHeight, buildingWidth + 10, 10, 0.1f, 0.1f, 0.3f); // Dark base
    } else {
        Rectangle(x + 38, y, 20, 30, 0.3f, 0.2f, 0.1f);  // Normal door
        Rectangle(x - 5, y + buildingHeight, buildingWidth + 10, 10, 0.212f, 0.271f, 0.310f); // Normal base
    }
}


void drawLake(int cx, int cy, float radiusX, float radiusY) {

    if (isNight) {
        glColor3f(0.05f, 0.1f, 0.2f); // Darker blue at night
    } else {
        glColor3f(0.2f, 0.6f, 1.0f);  // Bright blue in day
    }


    glBegin(GL_POLYGON);
    for (int i = 0; i <= 360; i++) {
        float angle = i * M_PI / 180.0;
        float x = cx + cos(angle) * radiusX;
        float y = cy + sin(angle) * radiusY;
        VTX(x, y);
    }
    glEnd();

    // Outline of the lake
    glColor3f(isNight ? 0.08f : 0.1f, isNight ? 0.2f : 0.3f, isNight ? 0.3f : 0.5f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i <= 360; i++) {
        float angle = i * M_PI / 180.0;
        float x = cx + cos(angle) * radiusX;
        float y = cy + sin(angle) * radiusY;
        VTX(x, y);
    }
    glEnd();
}


float normX(int x) {
    return (float)x / 1280.0f * 2.0f - 1.0f;
}

// Normalize pixel y to [-0.5625, 0.5625]
float normY(int y) {
    return (float)y / 720.0f * 1.125f - 0.5625f;
}

void drawBench(int x, int y) {
    // Bench seat (wood)
    glColor3f(0.6f, 0.3f, 0.0f); // Brown
    glBegin(GL_POLYGON);
    glVertex2f(normX(x), normY(y));
    glVertex2f(normX(x + 80), normY(y));
    glVertex2f(normX(x + 80), normY(y + 10));
    glVertex2f(normX(x), normY(y + 10));
    glEnd();

    // Bench backrest (wood)
    glBegin(GL_POLYGON);
    glVertex2f(normX(x), normY(y + 20));
    glVertex2f(normX(x + 80), normY(y + 20));
    glVertex2f(normX(x + 80), normY(y + 30));
    glVertex2f(normX(x), normY(y + 30));
    glEnd();

    // Left leg (metal)
    glColor3f(0.3f, 0.3f, 0.3f); // Dark gray
    glBegin(GL_POLYGON);
    glVertex2f(normX(x + 5), normY(y - 15));
    glVertex2f(normX(x + 10), normY(y - 15));
    glVertex2f(normX(x + 10), normY(y));
    glVertex2f(normX(x + 5), normY(y));
    glEnd();

    // Right leg (metal)
    glBegin(GL_POLYGON);
    glVertex2f(normX(x + 70), normY(y - 15));
    glVertex2f(normX(x + 75), normY(y - 15));
    glVertex2f(normX(x + 75), normY(y));
    glVertex2f(normX(x + 70), normY(y));
    glEnd();

    // Backrest support bars
    glBegin(GL_POLYGON);
    glVertex2f(normX(x + 5), normY(y + 10));
    glVertex2f(normX(x + 10), normY(y + 10));
    glVertex2f(normX(x + 10), normY(y + 20));
    glVertex2f(normX(x + 5), normY(y + 20));
    glEnd();

    glBegin(GL_POLYGON);
    glVertex2f(normX(x + 70), normY(y + 10));
    glVertex2f(normX(x + 75), normY(y + 10));
    glVertex2f(normX(x + 75), normY(y + 20));
    glVertex2f(normX(x + 70), normY(y + 20));
    glEnd();
}

void Ground() {
    // Ground base color
    glColor3ub(isNight ? 40 : 50, isNight ? 40 : 205, isNight ? 40 : 50);
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -0.5625f);
    glVertex2f(1.0f, -0.5625f);
    glVertex2f(1.0f, normY(220));
    glVertex2f(-1.0f, normY(220));
    glEnd();

    // Draw tree
    if (false) {
        drawTreeNorm(50, 75);
        drawTreeNorm(100, 75);
        drawTreeNorm(200, 70);
        drawTreeNorm(50, 0);
        drawTreeNorm(150, 0);
        drawTreeNorm(200, 0);
        drawTreeNorm(600, 20);
        drawTreeNorm(650, 10);
        drawTreeNorm(1120,10);
        drawTreeNorm(1190,20);
    } else {

        Tree(50, 75);
        Tree(100, 75);
        Tree(200, 70);
        Tree(50, 0);
        Tree(150, 0);
        Tree(200, 0);
        Tree(600, 20);
        Tree(650, 10);
        Tree(1120,10);
        Tree(1190,20);
    }

    drawLake(900, 100, 180, 90);
}



void Windows(int x, int y)
{
    glColor3ub(162, 162, 162);
    glBegin(GL_QUADS);
    glVertex2f(normX(x), normY(y));
    glVertex2f(normX(x + 60), normY(y));
    glVertex2f(normX(x + 60), normY(y + 70));
    glVertex2f(normX(x), normY(y + 70));
    glEnd();

    glColor3ub(0, 0, 0);
    glBegin(GL_QUADS);
    glVertex2f(normX(x + 7), normY(y + 7));
    glVertex2f(normX(x + 27), normY(y + 7));
    glVertex2f(normX(x + 27), normY(y + 33));
    glVertex2f(normX(x + 7), normY(y + 33));
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(normX(x + 33), normY(y + 7));
    glVertex2f(normX(x + 54), normY(y + 7));
    glVertex2f(normX(x + 54), normY(y + 33));
    glVertex2f(normX(x + 33), normY(y + 33));
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(normX(x + 7), normY(y + 40));
    glVertex2f(normX(x + 27), normY(y + 40));
    glVertex2f(normX(x + 27), normY(y + 63));
    glVertex2f(normX(x + 7), normY(y + 63));
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(normX(x + 33), normY(y + 40));
    glVertex2f(normX(x + 54), normY(y + 40));
    glVertex2f(normX(x + 54), normY(y + 63));
    glVertex2f(normX(x + 33), normY(y + 63));
    glEnd();
}

void Upperside() {
    glBegin(GL_QUADS);
    if (isNight) {
        glColor3f(0.0f, 0.15f, 0.0f);  // Darker green for night
    } else {
        glColor3f(0.0f, 0.50f, 0.0f);  // Bright green for day
    }
    glVertex2f(normX(0), normY(320));
    glVertex2f(normX(1280), normY(320));
    glVertex2f(normX(1280), normY(450));
    glVertex2f(normX(0), normY(450));
    glEnd();

    // For buildings
    if (isNight) {
        Building(460, 320);
        drawModernBuilding1(570, 320);
        drawModernBuilding1(220, 320);
        drawModernBuilding2(650, 320);
        drawModernBuilding3(750, 320);
    } else {
        Building(460, 320);
        drawModernBuilding1(570, 320);
        drawModernBuilding1(220, 320);
        drawModernBuilding2(650, 320);
        drawModernBuilding3(750, 320);
    }
}

void PoliceBox(int r, int g, int b)
{
    int windowsXf = 840; // Shift windows by 430 units
    glColor3ub(70, 53, 31);

    glBegin(GL_QUADS);
    glVertex2f(normX(840), normY(470));
    glVertex2f(normX(1250), normY(470));
    glVertex2f(normX(1250), normY(320));
    glVertex2f(normX(840), normY(320));
    glEnd();

    glColor3ub(0, 0, 0); // Dark brown or black
    glBegin(GL_QUADS);
    glVertex2f(normX(836), normY(470));
    glVertex2f(normX(1250), normY(470));
    glVertex2f(normX(1250), normY(485));
    glVertex2f(normX(836), normY(485));
    glEnd();

    for (int i = 2; i >= 0; i--)
    {
        windowsXf += 90;
        Windows(windowsXf, 350);
    }
}

void Building1() {
    // Base
    glColor3ub(isNight ? 80 : 245, isNight ? 70 : 231, isNight ? 60 : 158);
    glBegin(GL_QUADS);
    glVertex2f(normX(5), normY(320));
    glVertex2f(normX(155), normY(320));
    glVertex2f(normX(155), normY(580));
    glVertex2f(normX(5), normY(580));
    glEnd();

    // Roof
    glColor3ub(isNight ? 60 : 175, isNight ? 40 : 65, isNight ? 40 : 50);
    glBegin(GL_QUADS);
    glVertex2f(normX(5), normY(580));
    glVertex2f(normX(170), normY(580));
    glVertex2f(normX(155), normY(615));
    glVertex2f(normX(5), normY(615));
    glEnd();

    // Window stripes
    glColor3ub(isNight ? 30 : 0, isNight ? 30 : 0, isNight ? 30 : 0);
    glBegin(GL_QUADS);
    glVertex2f(normX(5), normY(499));
    glVertex2f(normX(155), normY(499));
    glVertex2f(normX(155), normY(507));
    glVertex2f(normX(5), normY(507));
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(normX(5), normY(525));
    glVertex2f(normX(155), normY(525));
    glVertex2f(normX(155), normY(530));
    glVertex2f(normX(5), normY(530));
    glEnd();

    // Vertical window separators
    glBegin(GL_QUADS);
    for (float x = 3; x <= 155; x += 10) {
        glVertex2f(normX((int)x), normY(499));
        glVertex2f(normX((int)(x+3)), normY(499));
        glVertex2f(normX((int)(x+3)), normY(530));
        glVertex2f(normX((int)x), normY(530));
    }
    glEnd();

    // Small windows
    glColor3ub(isNight ? 40 : 95, isNight ? 90 : 190, isNight ? 90 : 180);
    int wx[] = {17, 59, 101};
    for (int i = 0; i < 3; i++) {
        glBegin(GL_QUADS);
        glVertex2f(normX(wx[i]), normY(445));
        glVertex2f(normX(wx[i]+30), normY(445));
        glVertex2f(normX(wx[i]+30), normY(475));
        glVertex2f(normX(wx[i]), normY(475));
        glEnd();
    }

    wx[0] = 32; wx[1] = 89;
    for (int i = 0; i < 2; i++) {
        glBegin(GL_QUADS);
        glVertex2f(normX(wx[i]), normY(540));
        glVertex2f(normX(wx[i]+30), normY(540));
        glVertex2f(normX(wx[i]+30), normY(570));
        glVertex2f(normX(wx[i]), normY(570));
        glEnd();
    }
}


void Building2() {
    glColor3ub(138, 79, 195);
    glBegin(GL_QUADS);
    glVertex2f(normX(5), normY(320));
    glVertex2f(normX(55), normY(320));
    glVertex2f(normX(55), normY(420));
    glVertex2f(normX(5), normY(400));
    glEnd();

    glColor3ub(151, 102, 209);
    glBegin(GL_QUADS);
    glVertex2f(normX(55), normY(320));
    glVertex2f(normX(155), normY(320));
    glVertex2f(normX(155), normY(420));
    glVertex2f(normX(55), normY(420));
    glEnd();

    glColor3ub(77, 60, 102);
    glBegin(GL_QUADS);
    glVertex2f(normX(5), normY(400));
    glVertex2f(normX(55), normY(420));
    glVertex2f(normX(58), normY(415));
    glVertex2f(normX(5), normY(395));
    glEnd();

    glColor3ub(77, 60, 102);
    glBegin(GL_QUADS);
    glVertex2f(normX(60), normY(420));
    glVertex2f(normX(155), normY(420));
    glVertex2f(normX(155), normY(415));
    glVertex2f(normX(60), normY(415));
    glEnd();

    glColor3ub(166, 200, 196);
    glBegin(GL_QUADS);
    glVertex2f(normX(25), normY(350));
    glVertex2f(normX(45), normY(350));
    glVertex2f(normX(45), normY(370));
    glVertex2f(normX(25), normY(370));
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(normX(67), normY(348));
    glVertex2f(normX(97), normY(348));
    glVertex2f(normX(97), normY(373));
    glVertex2f(normX(67), normY(373));
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(normX(117), normY(348));
    glVertex2f(normX(147), normY(348));
    glVertex2f(normX(147), normY(373));
    glVertex2f(normX(117), normY(373));
    glEnd();
}

void drawParabolicWindow(int x, int y, int width, int height, int segments) {
    float cx = x + width / 2.0f; // Center X for the curve
    float cy = y + height;        // Top of the rectangle (vertical position)

    glBegin(GL_QUADS);
    glVertex2f(normX(x), normY(y));
    glVertex2f(normX(x + width), normY(y));
    glVertex2f(normX(x + width), normY((int)cy));
    glVertex2f(normX(x), normY((int)cy));
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(normX((int)cx), normY((int)cy)); // Top-center of the curve
    for (int i = 0; i <= segments; i++) {
        float t = (float)i / segments; // t ranges from 0 to 1
        float px = x + t * width;      // Horizontal position from x to x+width
        float py = cy + (height / 2.0f) * 0.5f * (4 * t * (1 - t));
        glVertex2f(normX((int)px), normY((int)py));
    }
    glEnd();
}

void Building3() {
    glColor3ub(180, 91, 40);
    glBegin(GL_QUADS);
    glVertex2f(normX(145), normY(320));
    glVertex2f(normX(215), normY(320));
    glVertex2f(normX(215), normY(565));
    glVertex2f(normX(145), normY(565));
    glEnd();

    glColor3ub(0, 0, 0);
    glBegin(GL_QUADS);
    glVertex2f(normX(145), normY(565));
    glVertex2f(normX(215), normY(565));
    glVertex2f(normX(215), normY(570));
    glVertex2f(normX(145), normY(570));
    glEnd();

    glColor3ub(0, 0, 0);
    glBegin(GL_QUADS);
    glVertex2f(normX(145), normY(320));
    glVertex2f(normX(215), normY(320));
    glVertex2f(normX(215), normY(340));
    glVertex2f(normX(145), normY(340));
    glEnd();

    glColor3ub(0, 0, 0);
    glBegin(GL_QUADS);
    glVertex2f(normX(155), normY(570));
    glVertex2f(normX(180), normY(570));
    glVertex2f(normX(180), normY(585));
    glVertex2f(normX(155), normY(585));
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(normX(167), normY(585));
    glVertex2f(normX(172), normY(585));
    glVertex2f(normX(172), normY(650));
    glVertex2f(normX(167), normY(650));
    glEnd();

    glColor3ub(0, 0, 0);
    glBegin(GL_QUADS);
    glVertex2f(normX(188), normY(570));
    glVertex2f(normX(205), normY(570));
    glVertex2f(normX(205), normY(585));
    glVertex2f(normX(188), normY(585));
    glEnd();

    glColor3ub(0, 0, 0);
    glBegin(GL_QUADS);
    glVertex2f(normX(193), normY(585));
    glVertex2f(normX(201), normY(585));
    glVertex2f(normX(201), normY(620));
    glVertex2f(normX(193), normY(620));
    glEnd();

    int windowWidth = 20;
    int windowHeight = 25;
    int segments = 40;

    glColor3ub(113, 42, 24);
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 2; j++) {
            int x = 155 + j * 30;
            int y = 350 + i * 50;
            drawParabolicWindow(x, y, windowWidth, windowHeight, segments);
        }
    }

    glColor3ub(255, 209, 143); // Border color
    for (int i = 0; i < 3; ++i) {
        int y = 350 + i * 50 + windowHeight;
        glBegin(GL_QUADS);
        glVertex2f(normX(145), normY(y + 10));
        glVertex2f(normX(215), normY(y + 10));
        glVertex2f(normX(215), normY(y + 15));
        glVertex2f(normX(145), normY(y + 15));
        glEnd();
    }
}


void School() {
    // Day/night base wall
    glColor3ub(isNight ? 30 : 70, isNight ? 60 : 152, isNight ? 100 : 254);
    glBegin(GL_QUADS);
    glVertex2f(normX(287), normY(320));
    glVertex2f(normX(438), normY(320));
    glVertex2f(normX(438), normY(400));
    glVertex2f(normX(287), normY(400));
    glEnd();

    // Upper building roof segment
    glColor3ub(isNight ? 20 : 63, isNight ? 50 : 144, isNight ? 80 : 244);
    glBegin(GL_QUADS);
    glVertex2f(normX(293), normY(420));
    glVertex2f(normX(433), normY(420));
    glVertex2f(normX(433), normY(500));
    glVertex2f(normX(293), normY(500));
    glEnd();

    // Roof trim
    glColor3ub(isNight ? 10 : 0, isNight ? 40 : 58, isNight ? 60 : 100);
    glBegin(GL_QUADS);
    glVertex2f(normX(288), normY(500));
    glVertex2f(normX(438), normY(500));
    glVertex2f(normX(438), normY(515));
    glVertex2f(normX(288), normY(515));
    glEnd();

    // Window divider bands
    glColor3ub(isNight ? 10 : 37, isNight ? 40 : 88, isNight ? 70 : 135);
    glBegin(GL_QUADS);
    glVertex2f(normX(288), normY(400));
    glVertex2f(normX(438), normY(400));
    glVertex2f(normX(438), normY(408));
    glVertex2f(normX(288), normY(408));
    glEnd();

    glBegin(GL_QUADS);
    glVertex2f(normX(288), normY(408));
    glVertex2f(normX(438), normY(408));
    glVertex2f(normX(438), normY(420));
    glVertex2f(normX(288), normY(420));
    glEnd();

    // Second‑floor parabolic windows
    glColor3ub(isNight ? 90 : 170, isNight ? 90 : 144, isNight ? 90 : 80);
    for (int i = 0; i < 3; i++) {
        drawParabolicWindow(313 + 40*i, 425, 20, 25, 20);
        drawParabolicWindow(313 + 40*i, 465, 20, 25, 20);
    }

    // First‑floor rectangular windows
    glColor3ub(isNight ? 60 : 95, isNight ? 100 : 180, isNight ? 90 : 165);
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            int x = 318 + 60*i;
            int y = 325 + 40*j;
            glBegin(GL_QUADS);
            glVertex2f(normX(x), normY(y));
            glVertex2f(normX(x + 33), normY(y));
            glVertex2f(normX(x + 33), normY(y + 27));
            glVertex2f(normX(x), normY(y + 27));
            glEnd();
        }
    }
}


void drawCar(int x, int y) {
    glColor3f(isNight ? 0.3f : 0.8f, isNight ? 0.0f : 0.0f, isNight ? 0.0f : 0.0f);
    glBegin(GL_POLYGON);
    glVertex2f(normX(x), normY(y));
    glVertex2f(normX(x+100), normY(y));
    glVertex2f(normX(x+100), normY(y+30));
    glVertex2f(normX(x), normY(y+30));
    glEnd();

    glColor3f(isNight ? 0.4f : 0.9f, isNight ? 0.05f : 0.1f, isNight ? 0.05f : 0.1f);
    glBegin(GL_POLYGON);
    glVertex2f(normX(x+20), normY(y+30));
    glVertex2f(normX(x+80), normY(y+30));
    glVertex2f(normX(x+65), normY(y+50));
    glVertex2f(normX(x+35), normY(y+50));
    glEnd();

    glColor3f(isNight ? 0.1f : 0.3f, isNight ? 0.3f : 0.6f, isNight ? 0.3f : 1.0f);
    glBegin(GL_POLYGON);
    glVertex2f(normX(x+38), normY(y+34));
    glVertex2f(normX(x+62), normY(y+34));
    glVertex2f(normX(x+58), normY(y+46));
    glVertex2f(normX(x+42), normY(y+46));
    glEnd();

    glColor3f(isNight ? 0.05f : 0.1f, isNight ? 0.05f : 0.1f, isNight ? 0.05f : 0.1f);
    float r = 10.0f;
    int seg = 20;
    float cxl = x + 20, cyl = y - 5;
    glBegin(GL_TRIANGLE_FAN);
    for(int i=0;i<=seg;i++){
        float th=2*M_PI*i/seg;
        glVertex2f(normX((int)(cxl + r*cos(th))), normY((int)(cyl + r*sin(th))));
    }
    glEnd();

    float cxr = x + 80, cyr = y - 5;
    glBegin(GL_TRIANGLE_FAN);
    for(int i=0;i<=seg;i++){
        float th=2*M_PI*i/seg;
        glVertex2f(normX((int)(cxr + r*cos(th))), normY((int)(cyr + r*sin(th))));
    }
    glEnd();
}

void update(int value) {
    if (isMoving) {
        car1X += 5;     // move car 1 rightwards
        car2X -= 5;     // move car 2 leftwards

        // Reset positions to create continuous loop
        if (car1X > 1280) car1X = -100;   // reset after going off screen (left to right)
        if (car2X < -100) car2X = 1280;   // reset after going off screen (right to left)

        glutPostRedisplay();
    }
    glutTimerFunc(30, update, 0);  // call update every 30 ms
}

void Highway() {
    glColor3f(isNight ? 0.1f : 0.0f, isNight ? 0.1f : 0.20f, isNight ? 0.1f : 0.20f);
    glBegin(GL_QUADS);
    glVertex2f(normX(0), normY(220));
    glVertex2f(normX(1280), normY(220));
    glVertex2f(normX(1280), normY(320));
    glVertex2f(normX(0), normY(320));
    glEnd();

    for (int i = 100; i < 1280; i += 200) {
        glColor3f(isNight ? 0.6f : 1.0f, isNight ? 0.6f : 1.0f, isNight ? 0.2f : 0.0f);
        glBegin(GL_QUADS);
        glVertex2f(normX(i), normY(265));
        glVertex2f(normX(i+100), normY(265));
        glVertex2f(normX(i+100), normY(270));
        glVertex2f(normX(i), normY(270));
        glEnd();
    }
}


void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'n':
        case 'N':
            isNight = true;
            glutPostRedisplay();
            break;
        case 'd':
        case 'D':
            isNight = false;
            glutPostRedisplay();
            break;
        case 'g':  // start moving
        case 'G':
            isMoving = true;
            break;
        case 'l':  // stop moving
        case 'L':
            isMoving = false;
            break;
    }
}


void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    Sky();
    Cloud();
    Ground();
    drawBench(300, 100);
    Highway();
    Mountains();
    Upperside();
    School();
    Building1();
    Building2();
    Building3();
    PoliceBox(99,100,71);

    drawCar(car1X, 280);         // car moving left to right
    drawCar(car2X, 250);         // car moving right to left

    glFlush();
    glutSwapBuffers();

    cout<<"'D' for day"<<endl;
    cout<<"'N' for night"<<endl;
    cout<<"'G' to move the car"<<endl;
    cout<<"'L' to stop the car"<<endl;
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(1280, 720);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("City Scenario");
    init();

    glutDisplayFunc(display);
    glutTimerFunc(0, updateClouds, 0);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(30, update, 0);

    glutMainLoop();

    return 0;
}


