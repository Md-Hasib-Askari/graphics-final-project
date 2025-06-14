#include <windows.h>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include <cmath>
#include <ctime>
#include <vector>

#define PI 3.14159265

using namespace std;

// Global Functions
void renderBitmapString(float x, float y, float z, void *font, char *string) {
    char *c;
    glRasterPos3f(x, y,z);
    for (c=string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

// Window dimensions
int windowWidth = 1280;
int windowHeight = 720;

// Data Structures

// 1. Particles
struct Particle {
    float x, y;
    float r, g, b;
    std::vector<float> angles;
    float radius;
};

// 2. Points
struct Point {
    double x;
    double y;
};

// 3. Color
struct Color {
    float r;
    float g;
    float b;
};

class SceneManager {
public:
    static bool scene1Sound;
    static bool scene2Sound;
    static bool scene3Sound;
    static bool scene4Sound;
    static bool scene5Sound;

    static void resetSound(int sceneIdx) {
        scene1Sound = false;
        scene2Sound = false;
        scene3Sound = false;
        scene4Sound = false;
        scene5Sound = false;

        switch (sceneIdx) {
        case 1: scene1Sound = true; break;
        case 2: scene2Sound = true; break;
        case 3: scene3Sound = true; break;
        case 4: scene4Sound = true; break;
        case 5: scene5Sound = true; break;
        default: break;
        }
    }
};

class Scene1 : SceneManager {
public:
    GLfloat cloudPosition1 = 0.0f;
    GLfloat cloudPosition2=0.0;
    GLfloat cloudPosition3=0.0;
    GLfloat cloudSpeed = 0.005f;
    GLfloat car1Position=0.0f;
    GLfloat car1Speed=0.07f;
    GLfloat busPosition=0.0f;
    GLfloat busSpeed=0.07f;
    GLfloat i = 0.0f;

    GLfloat wheelRadius1 = 0.04f;
    GLfloat wheelRadius2 = 0.01f;

    bool pause = false;

    static Scene1* instance;

    void sound() {
        if (scene1Sound) {
            PlaySound(TEXT("background.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
        }
    }

    void circle(GLfloat x, GLfloat y, GLfloat radius)
    {
        int triangleAmount = 500;
        GLfloat twicePi = 2.0f * PI;

        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y); // center of circle

        for (int i = 0; i <= triangleAmount; i++) {
            glVertex2f(
                x + (radius * cos(i * twicePi / triangleAmount)),
                y + (radius * sin(i * twicePi / triangleAmount))
            );
        }
        glEnd();
    }
    void update(int value)
    {
        cout << "Updating scene..." << endl;
        //cloud
        if(cloudPosition1 > 2.02f)
        {
            cloudPosition1 = -0.58f;

        }
        cloudPosition1 += cloudSpeed;

        if(cloudPosition2 > 1.52f)
        {
        cloudPosition2 = -1.08f;
        }
        cloudPosition2 += cloudSpeed;

        if(cloudPosition3 > 0.97)
        {
        cloudPosition3 = -1.53f;

        }
        cloudPosition3 += cloudSpeed;

        if(car1Position > 1.80)
            car1Position = -1.0f;

        car1Position += car1Speed;

        i += (car1Speed / wheelRadius1) * (180.0f / 3.1416f);

        if(busPosition<-1.90) {
                busPosition=1.0f;
        }
        busPosition-=busSpeed;

        i += (busSpeed / wheelRadius1) * (180.0f / 3.1416f);

        if (!pause) {
            glutPostRedisplay();
            glutTimerFunc(100, Scene1::updateWrapper, 0);
        }
    }
    void car1()
    {
        glBegin(GL_POLYGON);
        glColor3f(0.772f, 0.502f, 0.082f);
        glVertex2f(-0.679, -0.203);
        glVertex2f(-0.720, -0.202);
        glVertex2f(-0.740, -0.190);
        glVertex2f(-0.742, -0.111);
        glVertex2f(-0.708, -0.040);
        glVertex2f(-0.678, 0);
        glVertex2f(-0.65, 0);
        glVertex2f(-0.614, 0);
        glVertex2f(-0.561, 0);
        glVertex2f(-0.531, -0.013);
        glVertex2f(-0.506, -0.045);
        glVertex2f(-0.491, -0.067);
        glVertex2f(-0.479, -0.078);
        glVertex2f(-0.448, -0.082);
        glVertex2f(-0.421, -0.118);
        glVertex2f(-0.417, -0.167);
        glVertex2f(-0.417, -0.192);
        glVertex2f(-0.443, -0.201);
        glEnd();

        //car window
        glBegin(GL_POLYGON);
        glColor3f(0.114f, 0.325f, 0.329f);
        glVertex2f(-0.620 , -0.081);
        glVertex2f(-0.692, -0.084);
        glVertex2f(-0.695, -0.081);
        glVertex2f(-0.677, -0.0390);
        glVertex2f(-0.662, -0.022);
        glVertex2f(-0.629, -0.014);
        glVertex2f(-0.621, -0.014);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.114f, 0.325f, 0.329f);
        glVertex2f(-0.516, -0.084);
        glVertex2f(-0.605, -0.084);
        glVertex2f(-0.606, -0.006);
        glVertex2f(-0.584, -0.0094);
        glVertex2f(-0.558 , -0.022);
        glVertex2f(-0.539, -0.039);
        glVertex2f(-0.520, -0.067);
        glEnd();
    }

    void busWindow(float x, float y) {
        glBegin(GL_POLYGON);
        glColor3f(0.114f, 0.325f, 0.329f);
        glVertex2f(x+0.252, y-0.162);
        glVertex2f(x+0.321, y-0.161);
        glVertex2f(x+ 0.321,y-0.0836);
        glVertex2f(x+0.315, y-0.070);
        glVertex2f(x+0.257, y-0.0709);
        glVertex2f(x+0.252, y-0.0809);
        glEnd();
    }
    
    void bus() {
        glBegin(GL_POLYGON);
        glColor3f(0.345f, 0.667f, 0.686f);
        glVertex2f(0.205, -0.270 );
        glVertex2f(0.843, -0.270);
        glVertex2f(0.841, -0.067);
        glVertex2f(0.824, -0.020);
        glVertex2f(0.230, -0.028);
        glVertex2f(0.205, -0.063);
        glEnd();

        //bus window
        glBegin(GL_POLYGON);
        glColor3f(0.114f, 0.325f, 0.329f);
        glVertex2f(0.205, -0.078);
        glVertex2f(0.227, -0.078);
        glVertex2f(0.235, -0.083);
        glVertex2f(0.235, -0.148);
        glVertex2f(0.231, -0.162);
        glVertex2f(0.205, -0.162);
        glEnd();

        busWindow(0,0);
        busWindow(0.0817, 0);
        busWindow(0.0817+0.0817 , 0);
        busWindow(0.0817+0.0817+0.0817 , 0);
        busWindow(0.3268 , 0);
        busWindow(0.3268+0.0817, 0);
        busWindow(0.3268+0.0817+0.0817 , 0);

        //light
        glBegin(GL_POLYGON);
        glColor3f(0.8235f, 0.6431f, 0.1961f);
        glVertex2f(0.207, -0.220);
        glVertex2f(0.226, -0.220);
        glVertex2f(0.232, -0.228);
        glVertex2f(0.233, -0.237);
        glVertex2f(0.232, -0.245);
        glVertex2f(0.227, -0.250);
        glVertex2f(0.207, -0.251);
        glEnd();
    }

    void drawCloud(GLfloat offsetX, GLfloat offsetY) {
        glColor3f(1.0f, 1.0f, 1.0f);
        circle(-0.85f + offsetX, 0.80f + offsetY, 0.07f);
        circle(-0.77f + offsetX, 0.82f + offsetY, 0.09f);
        circle(-0.69f + offsetX, 0.81f + offsetY, 0.07f);
        circle(-0.89f + offsetX, 0.74f + offsetY, 0.08f);
        circle(-0.80f + offsetX, 0.76f + offsetY, 0.10f);
        circle(-0.70f + offsetX, 0.75f + offsetY, 0.08f);
        circle(-0.62f + offsetX, 0.74f + offsetY, 0.07f);
        circle(-0.85f + offsetX, 0.69f + offsetY, 0.07f);
        circle(-0.74f + offsetX, 0.70f + offsetY, 0.09f);
        circle(-0.66f + offsetX, 0.69f + offsetY, 0.07f);
    }

    void cloudAnimation() {
        glPushMatrix();
        glTranslatef(cloudPosition1, 0.0f, 0.0f);
            drawCloud(0,0);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(cloudPosition2, 0.0f, 0.0f);
            drawCloud(0.5f, -0.13f);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(cloudPosition3, 0.0f, 0.0f);
            drawCloud(0.95,0.10);
        glPopMatrix();
        //glFlush();
    }

    void carAnimation() {
        glPushMatrix();
        glTranslatef(car1Position, 0.0f, 0.0f);
            car1();

            glPushMatrix();
            glTranslatef(-0.68f, -0.183f, 0.0f);
            glRotatef(i, 0.0, 0.0, 1.0);
                glColor3f(0.114f, 0.325f, 0.329f);
                circle(0.0f, 0.0f, wheelRadius1);
                glColor3f(0.133f, 0.392f, 0.412f);
                circle(0.0f, 0.0f, wheelRadius2);

                glColor3f(1.0f, 1.0f, 1.0f);
                glBegin(GL_LINES);
                    glLineWidth(5.0f);
                    glVertex2f(0.0f, 0.0f);
                    glVertex2f(wheelRadius1, 0.0f);
                glEnd();
            glPopMatrix();

            glPushMatrix();
            glTranslatef(-0.48f, -0.183f, 0.0f);
            glRotatef(i, 0.0, 0.0, 1.0);
                glColor3f(0.114f, 0.325f, 0.329f);
                circle(0.0f, 0.0f, wheelRadius1);
                glColor3f(0.133f, 0.392f, 0.412f);
                circle(0.0f, 0.0f, wheelRadius2);
                glColor3f(1.0f, 1.0f, 1.0f);
                glBegin(GL_LINES);
                    glLineWidth(5.0f);
                    glVertex2f(0.0f, 0.0f);
                    glVertex2f(wheelRadius1, 0.0f);
                glEnd();
            glPopMatrix();
        glPopMatrix();
    }

    void busAnimation() {
        glPushMatrix();
        glTranslatef(busPosition, 0.0f, 0.0f);
            bus();
            glPushMatrix();
                glTranslatef(0.309f, -0.260f, 0.0f);   // চাকার পজিশনে নিয়ে যাওয়া
                glRotatef(i, 0.0f, 0.0f, 1.0f);        // ঘুরানো

                glColor3f(0.114f, 0.325f, 0.329f);
                circle(0.0f, 0.0f, wheelRadius1);  // বাইরের চাকা

                glColor3f(0.133f, 0.392f, 0.412f);
                circle(0.0f, 0.0f, wheelRadius2);  // ভেতরের ছোট চাকা

                glColor3f(1.0f, 1.0f, 1.0f);
                glBegin(GL_LINES);
                    glLineWidth(5.0f);
                    glVertex2f(0.0f, 0.0f);
                    glVertex2f(wheelRadius1, 0.0f);
                glEnd();
            glPopMatrix();

            glPushMatrix();
                glTranslatef(0.700f, -0.260f, 0.0f);
                glRotatef(i, 0.0f, 0.0f, 1.0f);

                glColor3f(0.114f, 0.325f, 0.329f);
                circle(0.0f, 0.0f, wheelRadius1);

                glColor3f(0.133f, 0.392f, 0.412f);
                circle(0.0f, 0.0f, wheelRadius2);

                glColor3f(1.0f, 1.0f, 1.0f);
                glBegin(GL_LINES);
                    glLineWidth(5.0f);
                    glVertex2f(0.0f, 0.0f);
                    glVertex2f(wheelRadius1, 0.0f);
                glEnd();

            glPopMatrix();
        glPopMatrix();
    }

    void hill() {
        //1st part
        glBegin(GL_POLYGON);
        glColor3f(0.3098f, 0.5333f, 0.1882f);

        glVertex2f(-1,0);
        glVertex2f(-1, 0.37);
        glVertex2f(-0.80, 0.50);
        glVertex2f(-0.62,0.40 );
        glVertex2f(-0.60, 0);
        glVertex2f(-0.615, 0.242);
        glVertex2f(-0.43, 0.53);
        glVertex2f(-0.29, 0.314);
        glVertex2f(-0.27, 0.07);
        glVertex2f(-0.20, 0.5);
        glVertex2f(0.049, 0.5);
        glVertex2f(0,0);
        glEnd();

        //2nd part
        glBegin(GL_POLYGON);
        glColor3f(0.3098f, 0.5333f, 0.1882f);
        glVertex2f(0,0);
        glVertex2f(0.049, 0.5);
        glVertex2f(0.126, 0.5);
        glVertex2f(0.18, 0.40);
        glVertex2f(0.21, 0.25);
        glVertex2f(0.224, 0.080);
        glVertex2f(0.331,0.435);
        glVertex2f(0.40, 0.50);
        glVertex2f(0.45, 0.385);
        glVertex2f(0.472, 0.130);
        glVertex2f(0.493, 0.0030);
        glVertex2f(0.61, 0.33);
        glVertex2f(0.73, 0.50);
        glVertex2f(0.87, 0.35);
        glVertex2f(0.90, 0.404);
        glVertex2f(0.965, 0.404);
        glVertex2f(1, 0.24);
        glVertex2f(1,0);
        glEnd();
    }

    void tree1() {
        glBegin(GL_POLYGON);
        glColor3f(0.0627f, 0.3569f, 0.1882f);
        glVertex2f(-0.86, 0.31);
        glVertex2f(-0.92, 0.22);
        glVertex2f(-0.811, 0.22);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.0627f, 0.3569f, 0.1882f);
        glVertex2f(-0.923, 0.148);
        glVertex2f(-0.797, 0.145);
        glVertex2f(-0.8588, 0.276);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.0627f, 0.3569f, 0.1882f);
        glVertex2f(-0.936, 0.064);
        glVertex2f(-0.790, 0.060);
        glVertex2f(-0.861, 0.22);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.3490f, 0.2745f, 0.1137f);
        glVertex2f(-0.87, 0.069);
        glVertex2f(-0.85, 0.069);
        glVertex2f(-0.85, 0);
        glVertex2f(-0.87, 00);
        glEnd();
    }

    void buildingWindow(float x, float y) {
        glBegin(GL_POLYGON);
            glColor3f(0.2157f, 0.2667f, 0.1922f);  // Polygon color
            glVertex2f(x - 0.747f, y + 0.427f);  // Vertex 1
            glVertex2f(x - 0.715f, y + 0.427f);  // Vertex 2
            glVertex2f(x - 0.715f, y + 0.371f);  // Vertex 3
            glVertex2f(x - 0.747f, y + 0.371f);  // Vertex 4
        glEnd();
    }

    void building1() {
        glBegin(GL_POLYGON);
        glColor3f(0.7294f, 0.5765f, 0.2f);
        glVertex2f(-0.784, 0.00);
        glVertex2f(-0.784, 0.47);
        glVertex2f(-0.530, 0.47);
        glVertex2f(-0.530, 00);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.5294f, 0.4471f, 0.1725f);
        glVertex2f(-0.530, 00);
        glVertex2f(-0.468, 0);
        glVertex2f(-0.468, 0.454);
        glVertex2f(-0.530, 0.47);
        glEnd();

        buildingWindow(0.0, 0.0);
        buildingWindow(0, -0.114);
        buildingWindow(0, -0.223);
        buildingWindow(0,-0.343);

        buildingWindow(0.076, 0);
        buildingWindow(0.076,-0.114);
        buildingWindow(0.076, -0.225);
        buildingWindow(0.076, -0.343);

        buildingWindow(0.147,0);
        buildingWindow(0.147,-0.114);
        buildingWindow(0.147,-0.225);
        buildingWindow(0.147, -0.343);
    }

    void building2Window(float x, float y) {
        glBegin(GL_POLYGON);
        glColor3f(0.231f, 0.255f, 0.192f);
        glVertex2f(x+0.486, y+0.308);
        glVertex2f(x+0.519, y+0.308);
        glVertex2f(x+0.519, y+0.249);
        glVertex2f(x+0.486, y+0.249);
        glEnd();
    }

    void building2() {
        glBegin(GL_POLYGON);
        glColor3f(0.604f, 0.406f, 0.176f);
        glVertex2f(0.45, 0.00);
        glVertex2f(0.45, 0.35);
        glVertex2f(0.676, 0.35);
        glVertex2f(0.676, 0.00);
        glEnd();
        building2Window(0,0);
        building2Window(0.064,0);
        building2Window(0.123,0);
        building2Window(0, -0.104);
        building2Window(0.064,-0.104);
        building2Window(0.123,-0.104);
        building2Window(0, -0.196);
        building2Window(0.064,-0.196);
        building2Window(0.123,-0.196);
    }

    void building3Window(float x, float y) {
        glBegin(GL_POLYGON);
        glColor3f(0.263f, 0.249f, 0.125f);
        glVertex2f(x+ 0.711, y+0.443);
        glVertex2f(x+0.711, y+0.391);
        glVertex2f(x+0.753, y+0.391);
        glVertex2f(x+0.753,y+0.443);
        glEnd();
    }

    void building3() {
        glBegin(GL_POLYGON);
        glColor3f(0.839f, 0.706f, 0.224f);
        glVertex2f(0.678, 0.00);
        glVertex2f(0.678, 0.471);
        glVertex2f(0.868, 0.471);
        glVertex2f(0.868, 00);
        glEnd();
        building3Window(0,0);
        building3Window(0.083, 0);
        building3Window(0, -0.104);
        building3Window(0.083, -0.104);
    }

    void tree2() {
        glBegin(GL_POLYGON);
        glColor3f(0.0627f, 0.3569f, 0.1882f);
        glVertex2f(-0.419, 0.298);
        glVertex2f(-0.473, 0.201);
        glVertex2f(-0.364, 0.196);
        glEnd();
        glBegin(GL_POLYGON);
        glColor3f(0.0627f, 0.3569f, 0.1882f);
        glVertex2f(-0.486, 0.132);
        glVertex2f(-0.356, 0.130);
        glVertex2f(-0.420, 0.240);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.0627f, 0.3569f, 0.1882f);
        glVertex2f(-0.490, 0.069);
        glVertex2f(-0.351, 0.069);
        glVertex2f(-0.418, 0.199);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.3490f, 0.2745f, 0.1137f);
        glVertex2f(-0.430, 0.068);
        glVertex2f(-0.409, 0.072);
        glVertex2f(-0.409, 0.00);
        glVertex2f(-0.431, 0.00);
        glEnd();
    }

    void bigTree() {
        glBegin(GL_POLYGON);
        glColor3f(0.071f, 0.373f, 0.220f);
        glVertex2f(0.108, 0.086);
        glVertex2f(0.088,  0.089);
        glVertex2f(0.070, 0.104);
        glVertex2f(0.060, 0.131);
        glVertex2f(0.0606, 0.159);
        glVertex2f(0.044, 0.160);
        glVertex2f(0.026, 0.193);
        glVertex2f(0.025, 0.225);
        glVertex2f(0.042, 0.247);
        glVertex2f(0.057, 0.26);
        glVertex2f(0.068, 0.257);
        glVertex2f(0.075, 0.291);
        glVertex2f(0.090, 0.317);
        glVertex2f(0.107, 0.326);
        glVertex2f(0.123, 0.325);
        glVertex2f(0.140, 0.318);
        glVertex2f(0.151, 0.306);
        glVertex2f(0.166, 0.321);
        glVertex2f(0.181, 0.328);
        glVertex2f(0.194, 0.329);
        glVertex2f(0.207, 0.327);
        glVertex2f(0.218, 0.320);
        glVertex2f(0.229, 0.308);
        glVertex2f(0.237, 0.297);
        glVertex2f(0.251, 0.315);
        glVertex2f(0.265, 0.329);
        glVertex2f(0.2771, 0.324);
        glVertex2f(0.291, 0.324);
        glVertex2f(0.304, 0.312);
        glVertex2f(0.311, 0.297);
        glVertex2f(0.3244, 0.316);
        glVertex2f(0.3388, 0.326);
        glVertex2f(0.352, 0.335);
        glVertex2f(0.368, 0.326);
        glVertex2f(0.383, 0.318);
        glVertex2f(0.389, 0.306);
        glVertex2f(0.400, 0.284);
        glVertex2f(0.413, 0.312);
        glVertex2f(0.429, 0.316);
        glVertex2f(0.443, 0.301);
        glVertex2f(0.456, 0.290);
        glVertex2f(0.461, 0.257);
        glVertex2f(0.461, 0.232);
        glVertex2f(0.460, 0.199);
        glVertex2f(0.458, 0.177);
        glVertex2f(0.450, 0.150);
        glVertex2f(0.438, 0.1410);
        glVertex2f(0.417, 0.142);
        glVertex2f(0.412, 0.119);
        glVertex2f(0.40, 0.1);
        glVertex2f(0.376, 0.097);
        glVertex2f(0.367, 0.098);
        glVertex2f(0.339, 0.0911);
        glVertex2f(0.315, 0.105);
        glVertex2f(0.305, 0.09);
        glVertex2f(0.287, 0.087);
        glVertex2f(0.268, 0.091);
        glVertex2f(0.253, 0.0911);
        glVertex2f(0.242, 0.110);
        glVertex2f(0.235, 0.120);
        glVertex2f(0.230, 0.101);
        glVertex2f(0.223, 0.094);
        glVertex2f(0.213, 0.092);
        glVertex2f(0.200, 0.088);
        glVertex2f(0.184, 0.0911);
        glVertex2f(0.172, 0.100);
        glVertex2f(0.159, 0.127);
        glVertex2f(0.154, 0.113);
        glVertex2f(0.15, 0.1);
        glVertex2f(0.136, 0.089);
        glVertex2f(0.124, 0.089);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.349f, 0.274f, 0.125f);
        glVertex2f(0.105, 00);
        glVertex2f(0.128, 0.00);
        glVertex2f(0.12, 0.25);
        glVertex2f(0.113, 0.252);
        glVertex2f(0.111, 0.082);
        glVertex2f(0.106, 0.011);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.349f, 0.274f, 0.125f);
        glVertex2f(0.11, 0.11);
        glVertex2f(0.0833, 0.142);
        glVertex2f(0.081, 0.154);
        glVertex2f(0.086, 0.154);
        glVertex2f(0.110, 0.124);
        glVertex2f(0.121, 0.127);
        glVertex2f(0.126, 0.135);
        glVertex2f(0.145, 0.152);
        glVertex2f(0.150, 0.153);
        glVertex2f(0.150, 0.148);
        glVertex2f(0.124, 0.120);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.349f, 0.274f, 0.125f);
        glVertex2f(0.112, 0.174);
        glVertex2f(0.082, 0.204);
        glVertex2f(0.0769, 0.219);
        glVertex2f(0.085, 0.219);
        glVertex2f(0.112, 0.190);
        glVertex2f(0.121, 0.200);
        glVertex2f(0.144, 0.234);
        glVertex2f(0.154, 0.236);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.349f, 0.274f, 0.125f);
        glVertex2f(0.18, 0.00);
        glVertex2f(0.204, 0.00);
        glVertex2f(0.194, 0.255);
        glVertex2f(0.186, 0.258);
        glVertex2f(0.187, 0.083);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.349f, 0.274f, 0.125f);
        glVertex2f(0.188, 0.159);
        glVertex2f(0.153, 0.187);
        glVertex2f(0.153, 0.198);
        glVertex2f(0.187, 0.172);
        glVertex2f(0.197, 0.206);
        glVertex2f(0.22, 0.24);
        glVertex2f(0.228, 0.239);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.349f, 0.274f, 0.125f);
        glVertex2f(0.199, 0.135);
        glVertex2f(0.22, 0.163);
        glVertex2f(0.229, 0.164);
        glVertex2f(0.201, 0.116);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.349f, 0.274f, 0.125f);
        glVertex2f(0.264, 0.00);
        glVertex2f(0.285, 0.00);
        glVertex2f(0.28, 0.14);
        glVertex2f(0.278, 0.251);
        glVertex2f(0.270, 0.171);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.349f, 0.274f, 0.125f);
        glVertex2f(0.267, 0.104);
        glVertex2f(0.234, 0.138);
        glVertex2f(0.238, 0.151);
        glVertex2f(0.268, 0.121);
        glVertex2f(0.298, 0.162);
        glVertex2f(0.307, 0.162);
        glVertex2f(0.288, 0.1200);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.349f, 0.274f, 0.125f);
        glVertex2f(0.27, 0.171);
        glVertex2f(0.245, 0.195);
        glVertex2f(0.242, 0.206);
        glVertex2f(0.248, 0.208);
        glVertex2f(0.269, 0.185);
        glVertex2f(0.279, 0.205);
        glVertex2f(0.304, 0.236);
        glVertex2f(0.312,0.236);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.349f, 0.274f, 0.125f);
        glVertex2f(0.341, 0.0);
        glVertex2f(0.364, 0.00);
        glVertex2f(0.357, 0.252);
        glVertex2f(0.348, 0.252);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.349f, 0.274f, 0.125f);
        glVertex2f(0.346, 0.126);
        glVertex2f(0.319, 0.154);
        glVertex2f(0.315, 0.162);
        glVertex2f(0.326, 0.160);
        glVertex2f(0.345, 0.139);
        glVertex2f(0.360, 0.152);
        glVertex2f(0.386, 0.178);
        glVertex2f(0.395, 0.181);
        glVertex2f(0.36, 0.14);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.349f, 0.274f, 0.125f);
        glVertex2f(0.347, 0.182);
        glVertex2f(0.316, 0.209);
        glVertex2f(0.311, 0.21);
        glVertex2f(0.32, 0.22);
        glVertex2f(0.345, 0.196);
        glVertex2f(0.3518, 0.211);
        glVertex2f(0.377, 0.238);
        glVertex2f(0.385, 0.242);
        glVertex2f(0.358, 0.199);
        glEnd();
    }

    void house () {
        glBegin(GL_POLYGON);
        glColor3f(0.694f, 0.431f, 0.094f);
    //  glColor3f(0.651f, 0.439f, 0.160f);
        glVertex2f(-0.318, 0.00);
        glVertex2f(-0.319, 0.125);
        glVertex2f(-0.241, 0.238);
        glVertex2f(-0.160, 0.121);
        glVertex2f(-0.160, 0.00);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.651f, 0.439f, 0.160f);
        glVertex2f(-0.160, 0.00);
        glVertex2f(0,0);
        glVertex2f(0, 0.119);
        glVertex2f(-0.075, 0.240);
        glVertex2f(-0.160, 0.121);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.298f, 0.257f, 0.122f);
        glVertex2f(-0.346, 0.124);
        glVertex2f(-0.32, 0.12);
        glVertex2f(-0.24, 0.23);
        glVertex2f(-0.24, 0.27);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.298f, 0.257f, 0.122f);
        glVertex2f(-0.24, 0.23);
        glVertex2f(-0.16, 0.119);
        glVertex2f(-0.16, 0.157);
        glVertex2f(-0.24, 0.27);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.298f, 0.257f, 0.122f);
        glVertex2f(-0.16, 0.119);
        glVertex2f(-0.075, 0.233);
        glVertex2f(-0.075, 0.277);
        glVertex2f(-0.16, 0.157);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.298f, 0.257f, 0.122f);
        glVertex2f(-0.077, 0.236);
        glVertex2f(0.00, 0.122);
        glVertex2f(0.022, 0.122);
        glVertex2f(-0.075, 0.273);
        glEnd();

        //door
        glBegin(GL_POLYGON);
        glColor3f(0.298f, 0.257f, 0.122f);
        glVertex2f(-0.272, 0.00);
        glVertex2f(-0.272, 0.095);
        glVertex2f(-0.256, 0.116);
        glVertex2f(-0.239, 0.122);
        glVertex2f(-0.226, 0.118);
        glVertex2f(-0.214, 0.106);
        glVertex2f(-0.208, 0.090);
        glVertex2f(-0.208, 0.00);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.298f, 0.257f, 0.122f);
        glVertex2f(-0.107, 0.00);
        glVertex2f(-0.107, 0.09);
        glVertex2f(-0.090, 0.119);
        glVertex2f(-0.074, 0.122);
        glVertex2f(-0.055, 0.113);
        glVertex2f(-0.045, 0.093);
        glVertex2f(-0.045, 0.0);
        glEnd();
    }

    void house2Window(float x, float y) {
        glBegin(GL_POLYGON);
        glColor3f(0.227f, 0.565f, 0.654f);
        glVertex2f(x+0.60, y+0.020);
        glVertex2f(x+ 0.686, y+0.020);
        glVertex2f(x+ 0.686, y+0.10);
        glVertex2f(x+0.60, y+0.10);
        glEnd();
    }

    void house2() {
        glBegin(GL_POLYGON);
        glColor3f(0.047f, 0.349f, 0.439f);
        glVertex2f(0.557, 0.00);
        glVertex2f(0.557, 0.124);
        glVertex2f(1, 0.124);
        glVertex2f(1,0);
        glEnd();

        //window
        house2Window(0,0);
        house2Window(0.10,0);
        house2Window(0.20, 0);
        house2Window(0.30, 0);

        glBegin(GL_POLYGON);
        glColor3f(0.063f, 0.294f, 0.345f);
        glVertex2f(0.540, 0.144);
        glVertex2f(0.540, 0.120);
        glVertex2f(1, 0.120);
        glVertex2f(1, 0.144);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.380f, 0.302f, 0.165f);
        glVertex2f(0.540, 0.135);
        glVertex2f(1, 0.135);
        glVertex2f(1, 0.228);
        glVertex2f(0.979, 0.252);
        glVertex2f(0.637, 0.252);
        glEnd();
    }

    void poll(float x, float y) {
        glBegin(GL_POLYGON);
        glColor3f(0.4118f, 0.2902f, 0.0941f);
        glVertex2f(x-0.676, y-0.521);
        glVertex2f(x-0.449, y-0.521);
        glVertex2f(x-0.442, y-0.520);
        glVertex2f(x-0.439, y-0.481);
        glVertex2f(x-0.443, y-0.465);
        glVertex2f(x-0.675, y-0.465);
        glVertex2f(x-0.682, y-0.468);
        glVertex2f(x-0.684, y-0.511);
        glVertex2f(x-0.684, y-0.522);
        glEnd();
    }

    void grass(float x, float y) {
        glBegin(GL_POLYGON);
        glColor3f(0.0549f, 0.3765f, 0.1490f);
        glVertex2f(x-0.338, y-0.519);
        glVertex2f(x-0.320, y-0.520);
        glVertex2f(x-0.305, y-0.500);
        glVertex2f(x-0.303, y-0.484);
        glVertex2f(x-0.310 , y-0.481);
        glVertex2f(x-0.320, y-0.50);
        glVertex2f(x-0.323, y-0.464);
        glVertex2f(x-0.328, y-0.453);
        glVertex2f(x-0.329, y-0.462);
        glVertex2f(x-0.334, y-0.486);
        glVertex2f(x-0.335, y-0.495);
        glVertex2f(x-0.350, y-0.476);
        glVertex2f(x-0.354, y-0.476);
        glVertex2f(x-0.354, y-0.487);
        glEnd();
    }

    void roadsidetree() {
        glBegin(GL_POLYGON);
        glColor3f(0.1019f, 0.4000f, 0.1412f);
        glVertex2f(1, -1);
        glVertex2f(0.660, -1);
        glVertex2f(0.659, -0.971);
        glVertex2f(0.665, -0.917);
        glVertex2f(0.683, -0.860);
        glVertex2f(0.710, -0.840);
        glVertex2f(0.735, -0.820);
        glVertex2f(0.759, -0.819);
        glVertex2f(0.777, -0.770);
        glVertex2f(0.786, -0.715);
        glVertex2f(0.804, -0.665);
        glVertex2f(0.832, -0.630);
        glVertex2f(0.866, -0.619);
        glVertex2f(0.884, -0.625);
        glVertex2f(0.902, -0.646);
        glVertex2f(0.912, -0.669);
        glVertex2f(0.911, -0.573);
        glVertex2f(0.927, -0.514);
        glVertex2f(0.961, -0.464);
        glVertex2f(0.99, -0.448);
        glVertex2f(1, -0.448);
        glEnd();
    }

    void park() {
        glBegin(GL_POLYGON);
        glColor3f(0.3019f, 0.5373f, 0.1451f);
        glVertex2f(-0.870 , -0.573);
        glVertex2f(-0.893, -0.577);
        glVertex2f(-0.923, -0.586);
        glVertex2f(-0.940, -0.593);
        glVertex2f(-0.942,  -0.609);
        glVertex2f(-0.923, -0.622);
        glVertex2f(-0.808, -0.627);
        glVertex2f(-0.772, -0.613);
        glVertex2f(-0.772, -0.591);
        glEnd();
        //tree
        glBegin(GL_POLYGON);
        glColor3f(0.0980f, 0.4039f, 0.1412f);
        glVertex2f(-0.868, -0.457);
        glVertex2f(-0.875, -0.457);
        glVertex2f(-0.858, -0.452);
        glVertex2f(-0.892, -0.447);
        glVertex2f(-0.901, -0.446);
        glVertex2f(-0.907, -0.427);
        glVertex2f(-0.912, -0.417);
        glVertex2f(-0.914, -0.403);
        glVertex2f(-0.92, -0.40);
        glVertex2f(-0.928, -0.397);
        glVertex2f(-0.935, -0.393);
        glVertex2f(-0.941, -0.381);
        glVertex2f(-0.947, -0.367);
        glVertex2f(-0.951, -0.350);
        glVertex2f(-0.954, -0.335);
        glVertex2f(-0.952, -0.320);
        glVertex2f(-0.960, -0.312);
        glVertex2f(-0.966, -0.298);
        glVertex2f(-0.970, -0.278);
        glVertex2f(-0.972, -0.251);
        glVertex2f(-0.969, -0.218);
        glVertex2f(-0.962, -0.196);
        glVertex2f(-0.952, -0.176);
        glVertex2f(-0.943, -0.158);
        glVertex2f(-0.931, -0.148);
        glVertex2f(-0.922, -0.144);
        glVertex2f(-0.913, -0.149);
        glVertex2f(-0.917, -0.123);
        glVertex2f(-0.913, -0.101);
        glVertex2f(-0.906, -0.083);
        glVertex2f(-0.899, -0.0688);
        glVertex2f(-0.889, -0.054);
        glVertex2f(-0.876, -0.042);
        glVertex2f(-0.864, -0.040);
        glVertex2f(-0.854, -0.041);
        glVertex2f(-0.843, -0.049);
        glVertex2f(-0.836, -0.058);
        glVertex2f(-0.828, -0.069);
        glVertex2f(-0.822, -0.080);
        glVertex2f(-0.817, -0.094);
        glVertex2f(-0.812, -0.104);
        glVertex2f(-0.810, -0.115);
        glVertex2f(-0.809, -0.125);
        glVertex2f(-0.807, -0.140);
        glVertex2f(-0.807, -0.151);
        glVertex2f(-0.80, -0.150);
        glVertex2f(-0.793, -0.152);
        glVertex2f(-0.785, -0.156);
        glVertex2f(-0.780, -0.166);
        glVertex2f(-0.774, -0.179);
        glVertex2f(-0.767, -0.193);
        glVertex2f(-0.761, -0.211);
        glVertex2f(-0.757, -0.230);
        glVertex2f(-0.756, -0.247);
        glVertex2f(-0.755, -0.263);
        glVertex2f(-0.756, -0.278);
        glVertex2f(-0.758, -0.290);
        glVertex2f(-0.763, -0.306);
        glVertex2f(-0.769,-0.316);
        glVertex2f(-0.766, -0.342);
        glVertex2f(-0.769, -0.358);
        glVertex2f(-0.773, -0.376);
        glVertex2f(-0.781, -0.393);
        glVertex2f(-0.789, -0.406);
        glVertex2f(-0.798, -0.413);
        glVertex2f(-0.806, -0.413);
        glVertex2f(-0.809, -0.426);
        glVertex2f(-0.814, -0.431);
        glVertex2f(-0.822, -0.440);
        glVertex2f(-0.830, -0.450);
        glVertex2f(-0.840, -0.450);
        glVertex2f(-0.846, -0.454);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.3608f, 0.2980f, 0.1686f);
        glVertex2f(-0.873, -0.600);
        glVertex2f(-0.844, -0.602);
        glVertex2f(-0.853, -0.351);
        glVertex2f(-0.828, -0.286);
        glVertex2f(-0.8334, -0.261);
        glVertex2f(-0.852, -0.312);
        glVertex2f(-0.854, -0.244);
        glVertex2f(-0.859, -0.223);
        glVertex2f(-0.865, -0.239);
        glVertex2f(-0.865, -0.334);
        glVertex2f(-0.898, -0.277);
        glVertex2f(-0.903, -0.2949);
        glVertex2f(-0.863, -0.3711);
        glEnd();

        //bench
        glBegin(GL_POLYGON);
        glColor3f(0.2980f, 0.5333f, 0.1412f);
        glVertex2f(-0.695,-0.630);
        glVertex2f(-0.463, -0.642);
        glVertex2f(-0.441, -0.641);
        glVertex2f(-0.424, -0.644);
        glVertex2f(-0.409, -0.655);
        glVertex2f(-0.416, -0.672);
        glVertex2f(-0.424, -0.644);
        glVertex2f(-0.409, -0.655);
        glVertex2f(-0.416, -0.672);
        glVertex2f(-0.677, -0.674);
        glVertex2f(-0.693, -0.675);
        glVertex2f(-0.703, -0.664);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.2863f, 0.2392f, 0.1019f);
        glVertex2f(-0.672, -0.662);
        glVertex2f(-0.664, -0.661);
        glVertex2f(-0.662, -0.617);
        glVertex2f(-0.661, -0.584);
        glVertex2f(-0.672, -0.582);
        glVertex2f(-0.675, -0.617);
        glVertex2f(-0.675, -0.644);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.2863f, 0.2392f, 0.1019f);
        glVertex2f(-0.461, -0.582);
        glVertex2f(-0.461, -0.652);
        glVertex2f(-0.460, -0.66);
        glVertex2f(-0.451, -0.6605);
        glVertex2f(-0.448, -0.648);
        glVertex2f(-0.450, -0.582);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.4157f, 0.2902f, 0.0941f);
        glVertex2f(-0.692, -0.584);
        glVertex2f(-0.432, -0.583);
        glVertex2f(-0.420, -0.583);
        glVertex2f(-0.417, -0.563);
        glVertex2f(-0.423, -0.552);
        glVertex2f(-0.694, -0.554);
        glVertex2f(-0.703, -0.556);
        glVertex2f(-0.706, -0.567);
        glVertex2f(-0.703, -0.580);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.2863f, 0.2392f, 0.1019f);
        glVertex2f(-0.668, -0.553);
        glVertex2f(-0.657, -0.553);
        glVertex2f(-0.656, -0.521);
        glVertex2f(-0.667, -0.520);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.2863f, 0.2392f, 0.1019f);
        glVertex2f(-0.465, -0.552);
        glVertex2f(-0.455, -0.552);
        glVertex2f(-0.456, -0.521);
        glVertex2f(-0.465, -0.519);
        glEnd();

        poll(0,0);

        glBegin(GL_POLYGON);
        glColor3f(0.2863f, 0.2392f, 0.1019f);
        glVertex2f(-0.667, -0.465);
        glVertex2f(-0.658, -0.465);
        glVertex2f(-0.658, -0.4449);
        glVertex2f(-0.667, -0.4449);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.2863f, 0.2392f, 0.1019f);
        glVertex2f(-0.469, -0.465);
        glVertex2f(-0.457, -0.465);
        glVertex2f(-0.457, -0.4449);
        glVertex2f(-0.469, -0.4449);
        glEnd();
        poll(0.00, 0.072);
        grass(0,0);
        grass(0, -0.21);
        grass(-0.406,-0.212);
        roadsidetree();
    }

    void roadLine(float x, float y) {
        glBegin(GL_POLYGON);
        glColor3f(0.851f, 0.717f, 0.361f);
        glVertex2f(x+(-0.386), y+(-0.204));
        glVertex2f(x+(-0.283), y+(-0.204));
        glVertex2f(x+(-0.283), y+(-0.223));
        glVertex2f(x+(-0.386), y+(-0.223));
        glEnd();
    } 

    void roaAndPark() {
        glBegin(GL_POLYGON);
        glColor3f(0.419f, 0.588f, 0.149f);
        glVertex2f(-1,0);
        glVertex2f(-1, -0.067);
        glVertex2f(1, -0.067);
        glVertex2f(1,0);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.854f, 0.710f, 0.357f);
        glVertex2f(-1, -0.067);
        glVertex2f(-0.997,-0.113);
        glVertex2f(1, -0.113);
        glVertex2f(1, -0.067);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.110f, 0.270f, 0.212f);
        glVertex2f(-0.997,-0.113);
        glVertex2f(-1, -0.318);
        glVertex2f(1, -0.318);
        glVertex2f(1, -0.113);
        glEnd();
        roadLine(0,0);
        roadLine(0.227,0);
        roadLine(0.454, 0);

        //park
        glBegin(GL_POLYGON);
        glColor3f(0.419f, 0.580f, 0.149f);
        glVertex2f(-1, -0.318);
        glVertex2f(-1, -1);
        glVertex2f(1, -1);
        glVertex2f(1, -0.321);
        glEnd();

        //parkRoad
        glBegin(GL_POLYGON);
        glColor3f(0.854f, 0.710f, 0.361f);
        glVertex2f(-0.352, -1);
        glVertex2f(-0.130, -1);
        glVertex2f(0.051, -0.505);
        glVertex2f(0.068, -0.392);
        glVertex2f(0.068, -0.324);
        glVertex2f(-0.060, -0.324);
        glVertex2f(-0.037, -0.358);
        glVertex2f(-0.040, -0.402);
        glEnd();

        //waterleak
        glBegin(GL_POLYGON);
        glColor3f(0.292f, 0.639f, 0.720f);
        glVertex2f(0.376, -0.550);
        glVertex2f(0.40, -0.57);
        glVertex2f(0.430, -0.60);
        glVertex2f(0.456, -0.630);
        glVertex2f(0.467, -0.652);
        glVertex2f(0.471, -0.674);
        glVertex2f(0.477, -0.7077);
        glVertex2f(0.4911, -0.727);
        glVertex2f(0.545, -0.758);
        glVertex2f(0.610, -0.768);
        glVertex2f(0.669, -0.768);
        glVertex2f(0.757, -0.765);
        glVertex2f(1, -0.80);
        glVertex2f(1, -0.551);
        glVertex2f(0.913, -0.516);
        glVertex2f(0.77, -0.495);
        glVertex2f(0.652, -0.483);
        glVertex2f(0.571, -0.488);
        glVertex2f(0.425, -0.507);
        glEnd();

        glBegin(GL_POLYGON);
        glColor3f(0.125f, 0.475f, 0.549f);
        glVertex2f(0.384, -0.560);
        glVertex2f(0.370, -0.537);
        glVertex2f(0.40, -0.5);
        glVertex2f(0.510, -0.469);
        glVertex2f(0.738, -0.465);
        glVertex2f(0.882, -0.483);
        glVertex2f(0.941, -0.495);
        glVertex2f(0.922, -0.530);
        glVertex2f(0.832, -0.513);
        glVertex2f(0.731, -0.499);
        glVertex2f(0.636, -0.497);
        glVertex2f(0.558, -0.502);
        glVertex2f(0.467, -0.516);
        glEnd();

        //CAR1
        carAnimation();
        busAnimation();
        park();
    }

    void sun() {
        glColor3f(1.0f, 0.3f, 0.0f);
        circle(0.61,0.76, 0.085);

        glBegin(GL_LINES);
        glColor3f(1.0f, 0.3f, 0.0f);
        glVertex2f(0.617, 0.762);
        glVertex2f(0.39,0.73);
        glEnd();
        glBegin(GL_LINES);
        glColor3f(1.0f, 0.3f, 0.0f);
        glVertex2f(0.617, 0.762);
        glVertex2f(0.844, 0.73);
        glEnd();
        glBegin(GL_LINES);
        glColor3f(1.0f, 0.3f, 0.0f);
        glVertex2f(0.617, 0.762);
        glVertex2f(0.43, 0.96);

        glEnd();
        glBegin(GL_LINES);
        glColor3f(1.0f, 0.3f, 0.0f);
        glVertex2f(0.617, 0.762);
        glVertex2f(0.80, 0.50);
        glEnd();
            glBegin(GL_LINES);
        glColor3f(1.0f, 0.3f, 0.0f);
        glVertex2f(0.617, 0.762);
        glVertex2f(0.60, 0.48);
        glEnd();
            glBegin(GL_LINES);
        glColor3f(1.0f, 0.3f, 0.0f);
        glVertex2f(0.612, 1);
        glVertex2f(0.617, 0.762);
        glEnd();
            glBegin(GL_LINES);
        glColor3f(1.0f, 0.3f, 0.0f);
        glVertex2f(0.617, 0.762);
        glVertex2f(0.45, 0.53);
        glEnd();
        glBegin(GL_LINES);
        glColor3f(1.0f, 0.3f, 0.0f);
        glVertex2f(0.77, 1);
        glVertex2f(0.617, 0.762);
        glEnd();
    }

    void backGroundSky() {
        glBegin(GL_POLYGON);
        glColor3f(0.3216f, 0.6902f, 0.7412f);
        //total limit
        glVertex2f(-1,0);
        glVertex2f(1, 0);
        glVertex2f(1,1);
        glVertex2f(-1,1);
        glEnd();

        sun();
        cloudAnimation();
        //sun();
        hill();
        tree1();
        building1();
        tree2();
        house();
        bigTree();
        building2();
        building3();
        house2();
    }

    // Display callback
    void display() {
        glClear(GL_COLOR_BUFFER_BIT); // Clear the screen
        
        glPushMatrix();
        glScalef(1.0f, 1.0f, 1.0f);
        glScalef(1.0f, 0.5625f, 1.0f);
            //sky blue back groud
            glColor3f(0.196f, 0.643f, 0.659f);
            glBegin(GL_POLYGON);
                glVertex2f(-1,-1);
                glVertex2f(-1,1);
                glVertex2f(1,1);
                glVertex2f(1,-1);
            glEnd();
            backGroundSky();
            roaAndPark();
        glPopMatrix();

        glFlush();
        glutSwapBuffers(); // Swap buffers (double buffering)
    }

    void SceneInfoDisplay() {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
        glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer (background)

        glColor3f(1.0f, 1.0f, 1.0f);
        renderBitmapString(-0.155f, 0.05f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Ashes and Echoes");
        renderBitmapString(-0.17f, -0.05f, 0.0f, GLUT_BITMAP_HELVETICA_18, "Scene 1:Peaceful vibrations");

        glFlush(); // Render now
        glutSwapBuffers();
    }

    void changeDisplay(unsigned char key, int x, int y) {
        if (key == 27) { // Escape key
            exit(0);
        } else if (key == 'D' ||  key == 'd') {
            cout << "D key pressed" << endl;
            pause = false; // Set pause to false
            glutDisplayFunc(Scene1::displayWrapper);

            sound();

            glutTimerFunc(100, Scene1::updateWrapper, 0);
        } else if (key == 'A' || key == 'a')  {
            PlaySound(NULL, NULL, SND_ASYNC | SND_PURGE);
            glutDisplayFunc(Scene1::SceneInfoWrapper);
            pause = true; // Set pause to true
        }
        glutPostRedisplay();
    }

    static void SceneInfoWrapper() {
        if (instance == nullptr) {
            cerr << "Scene1 instance is not initialized, SceneInfoDisplay cannot be called\n" << endl;
            return;
        }
        instance->SceneInfoDisplay();
    }
    static void displayWrapper() {
        if (instance == nullptr) {
            cerr << "Scene1 instance is not initialized, display cannot be called\n" << endl;
            return;
        }
        instance->display();
    }
    static void changeDisplayWrapper(unsigned char key, int x, int y) {
        if (instance == nullptr) {
            cerr << "Scene1 instance is not initialized, changeDisplay cannot be called\n" << endl;
            return;
        }
        instance->changeDisplay(key, x, y);
    }
    static void updateWrapper(int value) {
        if (instance == nullptr) {
            cerr << "Scene1 instance is not initialized, update cannot be called\n" << endl;
            return;
        }
        instance->update(value);
    }
};

class Scene3 : SceneManager {
public:
    // Member variables (formerly global)
    // Sound Control
    bool soundPlayed = false;
    bool soundAlarm = false;
    bool nukeSoundPlayed = false;

    // Animation Speed Control
    float xCloud1Speed = 0.001f;
    float xCloud2Speed = 0.0005f;
    float xCloud3Speed = 0.0016f;
    float sdxMCloudsSpeed = 0.001f;
    float sdyMCloudsSpeed = 0.001f;
    float MCloudShakeSpeed = 0.0002f;
    float nukeSpeed = 0.0005f;
    float backgroundShakeSpeed = 0.0005f;
    float dxParticlesSpeed = 0.0002f;
    float dyParticlesSpeed = 0.0005f;
    float dyBuilding1Speed = 0.0001f;
    float dyBuilding2Speed = 0.00005f;
    float rotateBuilding1Speed = 0.005f;
    float rotateBuilding2Speed = 0.003f;

    // Transformation - Cloud
    float dxCloud1 = 0.0f, dyCloud1 = 0.0f;
    float dxCloud2 = 0.0f, dyCloud2 = 0.0f;
    float dxCloud3 = 0.0f, dyCloud3 = 0.0f;

    // Transformation - Marshmallow Cloud
    bool initVars = false;
    bool toggleMClouds = false;
    float dxMClouds = 0.0f, dyMClouds = 0.0f;
    float sdxMClouds = 0.1f, sdyMClouds = 0.1f;

    // Transformation - Grass
    float dxGrass = 0.0f, dyGrass = 0.0f;

    // Transformation - Buildings
    float rotateBuilding1 = 0.0f, dxBuilding1 = 0.0f, dyBuilding1 = 0.0f;
    float rotateBuilding2 = 0.0f, dxBuilding2 = 0.0f, dyBuilding2 = 0.0f;

    // Transformation - Background
    bool shakeBackground = false;
    bool toggleBackground = false;
    float dxBackground = 0.0f, dyBackground = 0.0f;

    // Transformation - Nuke
    float dyNuke = 0.0f;
    bool toggleNuke = true;

    // Transformation - Particles
    bool resetParticles = false;
    float dxParticles = 0.0f, dyParticles = 0.0f;
    bool initParticles = true;
    const int NUM_PARTICLES1 = 10;
    const int NUM_PARTICLES2 = 50;
    const int MIN_SIDES = 5;
    const int MAX_SIDES = 6;
    const float MIN_RADIUS = 0.02f;
    const float MAX_RADIUS = 0.025f;
    vector<Particle> particles1;
    vector<Particle> particles2;
    Point mClouds[3][20];

    // Singleton instance for GLUT callbacks
    static Scene3* instance;

    // Utils
    // Static timer callback for playSound
    static void playSoundTimer(int value) {
        instance->playSound(value);
    }

    void playSound(int value) {
        if (!scene3Sound) { return; }
        switch (value) {
        case 0:
            PlaySound(NULL, NULL, SND_PURGE); // Stop any previous sound
            PlaySound(TEXT("drop.wav"), NULL, SND_FILENAME | SND_ASYNC);
            break;
        case 1:
            PlaySound(NULL, NULL, SND_PURGE); // Stop any previous sound
            PlaySound(TEXT("blast.wav"), NULL, SND_FILENAME | SND_ASYNC);
            break;
        case 2:
            PlaySound(NULL, NULL, SND_PURGE); // Stop any previous sound
            PlaySound(TEXT("alarm.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
            break;
        default:
            break;
        }
    }

    // void renderBitmapString(float x, float y, float z, void *font, char *string)
    // {
    //     char *c;
    //     glRasterPos3f(x, y,z);
    //     for (c=string; *c != '\0'; c++)
    //     {
    //         glutBitmapCharacter(font, *c);
    //     }
    // }

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

    float randomFloat(float min, float max) {
        return min + (float) ((rand()) / (float) (RAND_MAX / (max - min)));
    }


    // Drawing Functions
    void drawNuke() {
        glBegin(GL_POLYGON);
            glColor3f(0.510f, 0.584f, 0.345f);  // #829558
            glVertex2f(-0.249f, 0.419f);
            glVertex2f(-0.242f, 0.419f);

            glColor3f(0.302f, 0.357f, 0.180f);  // #4D5B2E
            glVertex2f(-0.242f, 0.413f);
            glVertex2f(-0.249f, 0.413f);
        glEnd();

        glBegin(GL_POLYGON);
            glColor3f(0.510f, 0.584f, 0.345f);  // #829558
            glVertex2f(-0.238f, 0.395f);
            glVertex2f(-0.253f, 0.395f);

            glColor3f(0.302f, 0.357f, 0.180f);  // #4D5B2E
            glVertex2f(-0.264f, 0.401f);
            glVertex2f(-0.264f, 0.421f);

            glColor3f(0.510f, 0.584f, 0.345f);  // #829558
            glVertex2f(-0.249f, 0.413f);
            glVertex2f(-0.242f, 0.413f);

            glColor3f(0.302f, 0.357f, 0.180f);  // #4D5B2E
            glVertex2f(-0.227f, 0.421f);
            glVertex2f(-0.227f, 0.401f);
        glEnd();

        glBegin(GL_POLYGON);
            glColor3f(0.302f, 0.357f, 0.180f);  // #4D5B2E
            glVertex2f(-0.227f, 0.333f);
            glVertex2f(-0.265f, 0.333f);

            glColor3f(0.510f, 0.584f, 0.345f);  // #829558
            glVertex2f(-0.265f, 0.369f);
            glVertex2f(-0.253f, 0.395f);

            glColor3f(0.302f, 0.357f, 0.180f);  // #4D5B2E
            glVertex2f(-0.238f, 0.395f);
            glVertex2f(-0.227f, 0.369f);
        glEnd();

        drawFilledCurve(-0.246f, 0.333f, 0.019f, 0, 360);

        drawFilledCurve(-0.246f, 0.419f, 0.0034f, 0, 360);

        glColor3f(1.0f, 1.0f, 1.0f); // white
        drawFilledCurve(-0.246f, 0.351f, 0.015f, 0, 60);
        drawFilledCurve(-0.246f, 0.351f, 0.015f, 120, 180);
        drawFilledCurve(-0.246f, 0.351f, 0.015f, 240, 300);
        glColor3f(0.0f, 0.0f, 0.0f); // black
        drawFilledCurve(-0.246f, 0.351f, 0.0034f, 0, 360);
        glColor3f(1.0f, 1.0f, 1.0f); // white
        drawFilledCurve(-0.246f, 0.351f, 0.002f, 0, 360);
    }

    void generateParticles(float xMin, float xMax, float yMin, float yMax, float NUM_PARTICLES, vector<Particle>& particles) {
        // 1748421639
        // 1748421869
        srand(1748421869);
        // cout << time(0) << endl;

        // generate particles on road
        for (int i = 0; i < NUM_PARTICLES; ++i) {
            Particle p;
            p.x = randomFloat(xMin, xMax);
            p.y = randomFloat(yMin, yMax);
            p.radius = randomFloat(MIN_RADIUS, MAX_RADIUS);
            int sides = rand() % (MAX_SIDES - MIN_SIDES + 1) + MIN_SIDES;

            // Random angles for a broken shape
            for (int j = 0; j < sides; ++j) {
                float angle = randomFloat(0.3f, 2 * PI);
                p.angles.push_back(angle);
            }

            particles.push_back(p);
        }
    }

    void addParticles(vector<Particle>& particles, Color& color) {
        glColor3f(color.r, color.g, color.b); // #2D0D00
        for (const Particle& p : particles) {
            glBegin(GL_POLYGON);
            for (float angle : p.angles) {
                float randRadius = p.radius * randomFloat(0.7f, 1.3f);
                float x = p.x + cos(angle) * randRadius;
                float y = p.y + sin(angle) * randRadius;
                glVertex2f(x, y);
            }
            glEnd();
        }
    }

    void drawParticles() {
        // 1748421639
        // 1748421869
        srand(1748421869);
        // cout << time(0) << endl;

        // generate particles on road
        if (initParticles) {
            generateParticles(-0.5f, 0.5f, -0.2f, -0.15f, NUM_PARTICLES1, particles1);
            generateParticles(-0.8f, 0.8f, -.8f, -0.25f, NUM_PARTICLES2, particles2);
            initParticles = false;
        }

        // draw particles
        Color c1 = { 0.901f, 0.212f, 0.016f };
        Color c2 = { 0.176f, 0.051f, 0.0f };
        addParticles(particles1, c1);
        glPushMatrix();
        glTranslatef(dxParticles, dyParticles, 0);
            addParticles(particles2, c2);
        glPopMatrix();
    }

    void drawLake() {
        // #541504
        glColor3f(0.329f, 0.078f, 0.016f);
        glBegin(GL_POLYGON);
            glVertex2f(0.420f, -0.343f);
            glVertex2f(0.403f, -0.322f);
            glVertex2f(0.424f, -0.307f);
            glVertex2f(0.497f, -0.294f);
            glVertex2f(0.630f, -0.285f);
            glVertex2f(0.788f, -0.290f);
            glVertex2f(0.880f, -0.300f);
            glVertex2f(0.962f, -0.335f);
            glVertex2f(0.880f, -0.318f);
            glVertex2f(0.786f, -0.306f);
            glVertex2f(0.659f, -0.301f);
            glVertex2f(0.583f, -0.303f);
            glVertex2f(0.505f, -0.310f);
            glVertex2f(0.448f, -0.319f);
            glVertex2f(0.424f, -0.327f);
            glVertex2f(0.420f, -0.343f);
        glEnd();

        // #3E220D
        glColor3f(0.243f, 0.137f, 0.051f);
        glBegin(GL_POLYGON);
            glVertex2f(0.962f, -0.335f);
            glVertex2f(0.880f, -0.318f);
            glVertex2f(0.786f, -0.306f);
            glVertex2f(0.659f, -0.301f);
            glVertex2f(0.583f, -0.303f);
            glVertex2f(0.505f, -0.310f);
            glVertex2f(0.448f, -0.319f);
            glVertex2f(0.424f, -0.327f);
            glVertex2f(0.420f, -0.343f);
            glVertex2f(0.510f, -0.362f);
            glVertex2f(0.522f, -0.370f);
            glVertex2f(0.523f, -0.380f);
            glVertex2f(0.507f, -0.392f);
            glVertex2f(0.510f, -0.399f);
            glVertex2f(0.543f, -0.410f);
            glVertex2f(0.620f, -0.420f);
            glVertex2f(0.775f, -0.424f);
            glVertex2f(0.962f, -0.335f);
        glEnd();
    }

    void brokenBus() {
        glColor3f(0.901f, 0.212f, 0.016f);
        glBegin(GL_POLYGON);
            glVertex2f(0.378f, -0.128f);
            glVertex2f(0.369f, -0.092f);
            glVertex2f(0.412f, -0.005f);
            glVertex2f(0.892f, -0.094f);
            glVertex2f(0.921f, -0.149f);
            glVertex2f(0.871f, -0.238f);
            glVertex2f(0.809f, -0.236f);
            glVertex2f(0.505f, -0.174f);
            glVertex2f(0.378f, -0.128f);
        glEnd();

        // windows
        glColor3f(0.1647f, 0.0510f, 0.0000f);
        glBegin(GL_QUADS);

            glVertex2f(0.838f, -0.191f);
            glVertex2f(0.884f, -0.11f);
            glVertex2f(0.900f, -0.150f);
            glVertex2f(0.860f, -0.213f);

            glVertex2f(0.823f, -0.106f);
            glVertex2f(0.857f, -0.114f);
            glVertex2f(0.832f, -0.162f);
            glVertex2f(0.796f, -0.156f);

            glVertex2f(0.757f, -0.095f);
            glVertex2f(0.807f, -0.106f);
            glVertex2f(0.777f, -0.150f);
            glVertex2f(0.737f, -0.140f);

            glVertex2f(0.673f, -0.078f);
            glVertex2f(0.742f, -0.091f);
            glVertex2f(0.718f, -0.140f);
            glVertex2f(0.653f, -0.127f);

            glVertex2f(0.600f, -0.066f);
            glVertex2f(0.657f, -0.079f);
            glVertex2f(0.636f, -0.124f);
            glVertex2f(0.578f, -0.108f);

            glVertex2f(0.531f, -0.052f);
            glVertex2f(0.585f, -0.064f);
            glVertex2f(0.562f, -0.105f);
            glVertex2f(0.515f, -0.096f);

            glVertex2f(0.477f, -0.043f);
            glVertex2f(0.516f, -0.050f);
            glVertex2f(0.499f, -0.094f);
            glVertex2f(0.459f, -0.086f);

            glVertex2f(0.425f, -0.028f);
            glVertex2f(0.462f, -0.039f);
            glVertex2f(0.437f, -0.109f);
            glVertex2f(0.387f, -0.116f);

            glVertex2f(0.399f, -0.027f);
            glVertex2f(0.410f, -0.026f);
            glVertex2f(0.388f, -0.075f);
            glVertex2f(0.376f, -0.074f);

        glEnd();


        // wheels
        glColor3f(0.1647f, 0.0510f, 0.0000f);
        drawFilledCurve(0.47f, -0.155f, 0.04f, -30, 180);
        drawFilledCurve(0.705f, -0.219f, 0.04f, -10, 170);

        glColor3f(0.1725f, 0.0549f, 0.0118f);
        drawFilledCurve(0.47f, -0.155f, 0.03f);
        drawFilledCurve(0.705f, -0.219f, 0.03f);


        glColor3f(0.3608f, 0.0627f, 0.0039f);
        drawFilledCurve(0.47f, -0.155f, 0.015f);
        drawFilledCurve(0.705f, -0.219f, 0.015f);
    }

    void brokenCar() {

        // shadow
        glColor3f(0.1647f, 0.0510f, 0.0000f);
        drawFilledEllipse(-0.589f, -0.152f, 0.19f, 0.0183f);

        glColor3f(0.901f, 0.212f, 0.016f);
        glBegin(GL_POLYGON);
            glVertex2f(-0.768437f, -0.125288f);
            glVertex2f(-0.759077f, -0.085766f);
            glVertex2f(-0.685653f, -0.043708f);
            glVertex2f(-0.590504f, -0.033366f);
            glVertex2f(-0.549824f, -0.043708f);
            glVertex2f(-0.509834f, -0.067840f);
            glVertex2f(-0.437438f, -0.076803f);
            glVertex2f(-0.416754f, -0.090593f);
            glVertex2f(-0.407101f, -0.123688f);
            glVertex2f(-0.440886f, -0.148509f);
            glVertex2f(-0.476049f, -0.149199f);
            glVertex2f(-0.680137f, -0.142304f);
            glVertex2f(-0.749085f, -0.135409f);
        glEnd();

        // windows
        glColor3f(0.1647f, 0.0510f, 0.0000f);
        glBegin(GL_QUADS);
            glVertex2f(-0.7041f, -0.0806f);
            glVertex2f(-0.6842f, -0.0544f);
            glVertex2f(-0.6469f, -0.0485f);
            glVertex2f(-0.6507f, -0.0865f);

            glVertex2f(-0.6350f, -0.0488f);
            glVertex2f(-0.5824f, -0.0592f);
            glVertex2f(-0.5587f, -0.0901f);
            glVertex2f(-0.6370f, -0.0883f);

            glVertex2f(-0.5714f, -0.0567f);
            glVertex2f(-0.5498f, -0.0437f);
            glVertex2f(-0.5042f, -0.0762f);
            glVertex2f(-0.5361f, -0.0875f);
        glEnd();

        // wheels
        glColor3f(0.1647f, 0.0510f, 0.0000f);
        drawFilledCurve(-0.513f, -0.147f, 0.04f, 0, 180);
        drawFilledCurve(-0.715f, -0.143f, 0.04f, 0, 170);

        glColor3f(0.1725f, 0.0549f, 0.0118f);
        drawFilledCurve(-0.513f, -0.144f, 0.03f);
        drawFilledCurve(-0.715f, -0.143f, 0.03f);


        glColor3f(0.3608f, 0.0627f, 0.0039f);
        drawFilledCurve(-0.513f, -0.144f, 0.015f);
        drawFilledCurve(-0.715f, -0.143f, 0.015f);
    }

    void marshCloud() {
        glColor3f(0.25f, 0.06f, 0.01f);
        glBegin(GL_POLYGON);
            glVertex2f(-0.0591f, -0.0695f);
            glVertex2f(0.0889f, -0.0702f);
            glVertex2f(0.1217f, 0.3257f);
            glVertex2f(-0.1045f, 0.3349f);
            glVertex2f(-0.0653f, 0.1018f);
        glEnd();

        glColor3f(0.929f, 0.165f, 0.0f);
        glBegin(GL_POLYGON);
            glVertex2f(-0.0539f, -0.0892f);
            glVertex2f(-0.0548f, 0.1909f);
            glVertex2f(-0.0266f, 0.0990f);
            glVertex2f(-0.0224f, 0.1562f);
            glVertex2f(-0.0141f, 0.1101f);
            glVertex2f(0.0759f, -0.0931f);
        glEnd();
        glBegin(GL_POLYGON);
            glVertex2f(0.0759f, -0.0931f);
            glVertex2f(-0.0266f, 0.0990f);
            glVertex2f(-0.0087f, 0.2219f);
            glVertex2f(0.0322f, 0.2265f);
            glVertex2f(0.0408f, 0.1033f);
            glVertex2f(0.0529f, 0.1764f);
            glVertex2f(0.0569f, 0.1430f);
            glVertex2f(0.0742f, 0.2092f);
        glEnd();

        glColor3f(0.9804f, 0.6627f, 0.0f);
        glBegin(GL_POLYGON);
            glVertex2f(-0.0489125268f, -0.0919743524f);
            glVertex2f(-0.0319801809f, 0.0854121291f);
            glVertex2f(-0.0118226262f, 0.0313898824f);
            glVertex2f(-0.0005343955f, 0.1112137991f);
            glVertex2f(0.0655823839f, -0.0855239349f);
        glEnd();
        glBegin(GL_POLYGON);
            glVertex2f(0.0655823839f, -0.0855239349f);
            glVertex2f(0.0470374336f, 0.0837995247f);
            glVertex2f(0.0309113898f, 0.0467096240f);
            glVertex2f(0.0212357635f, 0.1434658866f);
            glVertex2f(0.0075286263f, 0.0821869203f);
        glEnd();

        glColor3f(0.2431f, 0.0549f, 0.0039f);
        drawFilledCurve(-0.289f, 0.3f, 0.07);
        drawFilledCurve(-0.229f, 0.253f, 0.07);
        drawFilledCurve(-0.135f, 0.233f, 0.07);
        drawFilledCurve(0.0f, 0.275f, 0.07);
        drawFilledCurve(0.099f, 0.282f, 0.07);
        drawFilledCurve(0.159f, 0.233f, 0.07);
        drawFilledCurve(0.265f, 0.258f, 0.07);
        drawFilledCurve(0.3f, 0.3f, 0.07);

        glPushMatrix();
        glTranslatef(0.02, 0.02, 0);
            glColor3f(0.7725f, 0.1451f, 0.0f);
            drawFilledCurve(-0.289f, 0.3f, 0.07);
            drawFilledCurve(-0.229f, 0.253f, 0.07);
            drawFilledCurve(-0.135f, 0.233f, 0.07);
            drawFilledCurve(0.0f, 0.275f, 0.07);
            drawFilledCurve(0.099f, 0.282f, 0.07);
            drawFilledCurve(0.159f, 0.233f, 0.07);
            drawFilledCurve(0.265f, 0.258f, 0.07);
            drawFilledCurve(0.3f, 0.3f, 0.07);
        glPopMatrix();

        glColor3f(0.952f, 0.251f, 0.0f);
        drawFilledCurve(-0.258f, 0.37f, 0.07);
        drawFilledCurve(-0.195f, 0.413f, 0.07);
        drawFilledCurve(0.2f, 0.4f, 0.07);
        drawFilledCurve(0.262f, 0.349f, 0.07);

        glColor3f(0.705f, 0.078f, 0.000f); // #B41400 (brown)
        for (int i = 0; i < 20; i++) {
            double x = mClouds[0][i].x;
            double y = mClouds[0][i].y;
            drawFilledCurve(x, y, 0.07);
        }

        glColor3f(0.984f, 0.733f, 0.106f); // #F9BB1A (yellow)
        for (int i = 0; i < 20; i++) {
            double x = mClouds[1][i].x;
            double y = mClouds[1][i].y;
            drawFilledCurve(x, y, 0.07);

        }

        glColor3f(0.992f, 0.278f, 0.008f); // #FC4702 (red)
        for (int i = 0; i < 20; i++) {
            double x = mClouds[2][i].x;
            double y = mClouds[2][i].y;
            drawFilledCurve(x, y, 0.07);
               // 0.4548
            if (mClouds[0][i].y > 0.4548) {
                cout << "Cloud 0 y: " << mClouds[0][i].y << endl;
            }
        }

        glColor3f(0.2235f, 0.0392f, 0.0f);
        drawFilledCurve(-0.224514f, -0.103923f, 0.05);
        drawFilledCurve(-0.179434f, -0.064775f, 0.05);
        drawFilledCurve(-0.108256f, -0.032744f, 0.08);
        drawFilledCurve(0.117142f, 0.0f, 0.05, -50, 180);
        drawFilledCurve(0.187134f, -0.035117f, 0.05);
        drawFilledCurve(0.250008f, -0.082569f, 0.05);

        glColor3f(0.9647f, 0.1961f, 0.0f);
        drawFilledCurve(-0.224514f, -0.11, 0.04);
        drawFilledCurve(-0.179434f, -0.07, 0.04);
        drawFilledCurve(-0.108256f, -0.04, 0.07);
        drawFilledCurve(0.117142f, 0.0f, 0.04);
        drawFilledCurve(0.187134f, -0.04f, 0.04);
        drawFilledCurve(0.250008f, -0.09f, 0.04);

        glColor3f(0.9882f, 0.6863f, 0.0235f);
        drawFilledCurve(-0.082f, -0.061f, 0.07);
        drawFilledCurve(-0.022f, -0.075f, 0.04);
        drawFilledCurve(0.04f, -0.054f, 0.06);
        drawFilledCurve(0.12f, -0.051f, 0.06);


        glColor3f(0.5686f, 0.0745f, 0.0f);
        drawFilledCurve(-0.1456f, -0.1070f, 0.04);
        drawFilledCurve(-0.0806f, -0.0869f, 0.04);
        drawFilledCurve(0.1285f, -0.1008f, 0.04);
        drawFilledCurve(0.2f, -0.1f, 0.04);
        drawFilledCurve(0.2478f, -0.1117f, 0.04);


        glColor3f(0.690f, 0.078f, 0.004f);
        drawFilledCurve(-0.2766f, -0.1423f, 0.04);
        drawFilledCurve(-0.2187f, -0.1320f, 0.04);
        drawFilledCurve(-0.1462f, -0.1364f, 0.04);
        drawFilledCurve(-0.0810f, -0.1298f, 0.04);
        drawFilledCurve(-0.0210f, -0.1159f, 0.04);
        drawFilledCurve(0.0399f, -0.1269f, 0.04);
        drawFilledCurve(0.1094f, -0.1159f, 0.04);
        drawFilledCurve(0.1673f, -0.1240f, 0.04);
        drawFilledCurve(0.2076f, -0.1210f, 0.04);
        drawFilledCurve(0.2567f, -0.1298f, 0.04);

        glColor3f(0.23f, 0.06f, 0.0f);
        glBegin(GL_POLYGON);
            glVertex2f(-0.320f, -0.129f);
            glVertex2f(-0.323f, -0.190f);
            glVertex2f(0.277f, -0.187f);
            glVertex2f(0.378f, -0.122f);
        glEnd();
    }

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

    void drawCloud1(const vector<Color>& colors = {}) {

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

    void drawCloud2() {
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

        glColor3f(0.180f, 0.059f, 0.012f);
        glBegin(GL_POLYGON);
            glVertex2f(-0.477f, 0.131f);
            glVertex2f(-0.434f, 0.109f);
            glVertex2f(-0.523f, -0.060f);
            glVertex2f(-0.567f, -0.046f);
        glEnd();

        glBegin(GL_POLYGON);
            glVertex2f(-0.559f, -0.060f);
            glVertex2f(-0.426f, 0.071f);
            glVertex2f(-0.371f, 0.025f);
            glVertex2f(-0.529f, -0.077f);
        glEnd();

        glBegin(GL_POLYGON);
            glVertex2f(-0.533f, -0.065f);
            glVertex2f(-0.384f, 0.029f);
            glVertex2f(-0.338f, -0.021f);
            glVertex2f(-0.457f, -0.089f);
        glEnd();

        glBegin(GL_POLYGON);
            glVertex2f(-0.553f, -0.085f);
            glVertex2f(-0.400f, -0.100f);
            glVertex2f(-0.450f, 0.100f);
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

    void drawRoad() {
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

        // lake
        drawLake();

        // tree
        glColor3f(0.141f, 0.047f, 0.0f);
        drawFilledCurve(0.7f, -0.6f, 0.12f);
        drawFilledCurve(0.8146f, -0.4705f, 0.12f);
        drawFilledCurve(0.9430f, -0.4119f, 0.12f);

        glBegin(GL_POLYGON);
            glVertex2f(0.7440f, -0.5787f);
            glVertex2f(1.0050f, -0.5911f);
            glVertex2f(1.0018f, -0.4377f);
        glEnd();
    }

    void mergeComponents() {
        drawBackground();

        // clouds
        glPushMatrix();
        glTranslatef(dxCloud1, dyCloud1, 0);
            drawCloud1();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(1.2, -0.05, 0);
            glPushMatrix();
            glTranslatef(dxCloud2, dyCloud2, 0);
                drawCloud1();
            glPopMatrix();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.7, -0.1, 0);
            glPushMatrix();
            glTranslatef(dxCloud3, dyCloud3, 0);
                drawCloud2();
            glPopMatrix();
        glPopMatrix();

        // trees
        drawTree1();
        drawTree2();

        glPushMatrix();
        glTranslatef(0.48, 0.33, 0);
        drawTree3();
        glPopMatrix();

        // buildings
        glPushMatrix();
        glRotatef(rotateBuilding1, 0, 0, 1);
        glTranslatef(dxBuilding1, dyBuilding1, 0);
            brokenBuilding1();
        glPopMatrix();

        glPushMatrix();
        glRotatef(rotateBuilding2, 0, 0, 1);
        glTranslatef(dxBuilding2, dyBuilding2, 0);
            brokenBuilding3();
            brokenBuilding2();
        glPopMatrix();

        brokenBuilding4();

        glPushMatrix();
        glTranslatef(0.24, 0, 0);
            brokenBuilding4();
        glPopMatrix();

        // road
        drawRoad();

        // trees
        drawTree3();


        // marshmallow cloud
        if (!toggleNuke) {
            glPushMatrix();
            glTranslatef(0, 0, 0);
            glTranslatef(0, -0.2f, 0);
            glScalef(sdxMClouds, sdyMClouds, 0);
            glTranslatef(0, 0.2f, 0);
            glTranslatef(dxMClouds, dyMClouds, 0);
                marshCloud();
            glPopMatrix();
        }

        // vehicles
        brokenCar();
        brokenBus();

        // Particles
        glPushMatrix();
        glTranslatef(dxParticles, dyParticles, 0.0f);
            drawParticles();
        glPopMatrix();

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

        // broken fence
        drawBrokenFence();

        // grass
        vector<Color> cloudGrass = {
            { 0.153f, 0.047f, 0.000f }
        };
        glPushMatrix();
        glTranslatef(0, -0.9, 0);
            drawCloud1(cloudGrass);
        glPopMatrix();

        drawSmallGrass();
        glPushMatrix();
        glTranslatef(0.3, 0.15, 0);
            drawSmallGrass();
        glPopMatrix();

        // nuke
        // change: 0.2 -> -0.51
        // glTranslatef(0.25f, -0.51f, 0.0f);
        if (toggleNuke) {
            glPushMatrix();
            glTranslatef(0.0f, dyNuke, 0.0f);
                glPushMatrix();
                glTranslatef(0.25f, 0.2f, 0.0f);
                    drawNuke();
                glPopMatrix();
            glPopMatrix();
        }
    }

    // Display 1 callback
    void display1()
    {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Background color
        glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer (background)

        glColor4f(0.0f, 0.0f, 0.0f, 1.0f); // Set text color to black
        glBegin(GL_QUADS);
            glVertex2f(-1.0f, -1.0f); // Bottom left
            glVertex2f(1.0f, -1.0f);  // Bottom right
            glVertex2f(1.0f, 1.0f);   // Top right
            glVertex2f(-1.0f, 1.0f);  // Top left
        glEnd();

        glColor3f(1.0f, 1.0f, 1.0f);

        renderBitmapString(-0.19f, 0.05f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Ashes and Echoes");
        renderBitmapString(-0.17f, -0.05f, 0.0f, GLUT_BITMAP_HELVETICA_18, "Scene 3: The Fall");
        renderBitmapString(-0.18f, -0.15f, 0.0f, GLUT_BITMAP_HELVETICA_12, "Created by: Md Hasib Askari");
        renderBitmapString(-0.18f, -0.5f, 0.0f, GLUT_BITMAP_HELVETICA_12, "Press 'Right Arrow' to continue");


        glutSwapBuffers(); // Swap buffers (double buffering)
        glFlush(); // Render now
    }

    // Display callback
    void display2() {
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Background color
        glClear(GL_COLOR_BUFFER_BIT); // Clear the screen

        glPushMatrix();
        glTranslatef(dxBackground, dyBackground, 0.0f); //  shake background
            mergeComponents(); // Merge all the components into 1 scene
        glPopMatrix();
        // drawPlane(); // Draw the plane

        glutSwapBuffers(); // Swap buffers (double buffering)
    }

    // variables for marshmallow cloud
    void initVariables() {
        if (!initVars) {
            // random generated circles
            float minX = -0.20;
            float maxX = 0.3138;
            float minY = 0.2927;
            float maxY = 0.4548;

            srand(1748270319); // seed

            // rand() / RAND_MAX -> random value between 0 - 1

            // yellow, orange circles
            for (int i=0; i<3; i++) {
                for (int j=0; j<20; j++) {
                    float x = minX + (rand() / (float)RAND_MAX) * (maxX - minX);
                    float y = minY + (rand() / (float)RAND_MAX) * (maxY - minY);
                    mClouds[i][j].x = x;
                    mClouds[i][j].y = y;
                    // cout << "mClouds[" << i << "][" << j << "] = (" << x << ", " << y << ")" << endl;
                }
            }

            // shades
            for (int j=0; j<20; j++) {
                float x = minX + (rand() / (float)RAND_MAX) * (maxX - minX);
                float y = minY + (rand() / (float)RAND_MAX) * (3.0 - minY);
                mClouds[3][j].x = x;
                mClouds[3][j].y = y;
            }
            initVars = true; // Set to true to avoid re-initialization
        }
    }

    void update() {
        // =====> Clouds
        dxCloud1 += xCloud1Speed; // Move clouds to the right
        if (dxCloud1 > 2.0f) {
            dxCloud1 = -0.5f; // Reset position when it goes off screen
        }
        // cout << "dxCloud1: " << dxCloud1 << endl;

        dxCloud2 -= xCloud2Speed; // Move clouds to the left
        if (dxCloud2 < -2.0f) {
            dxCloud2 = 0.5f; // Reset position when it goes off screen
        }
        // cout << "dxCloud2: " << dxCloud2 << endl << endl;

        dxCloud3 += xCloud3Speed; // Move clouds to the right
        if (dxCloud3 > 1.4f) {
            dxCloud3 = -0.9f; // Reset position when it goes off screen
        }
        // cout << "dxCloud3: " << dxCloud3 << endl;

        if (toggleNuke) {
            // =====> Nuke
            if (!nukeSoundPlayed) {
                playSound(0);

                nukeSoundPlayed = true; // Play sound only once
            }

            dyNuke -= nukeSpeed; // Move nuke down
            if (dyNuke <= -0.71f) {
                toggleNuke = false; // Toggle to false to reset position
            }
        } else {
            if (!soundPlayed) {
                glutTimerFunc(0, Scene3::playSoundTimer, 1);
                glutTimerFunc(10000, Scene3::playSoundTimer, 2);
                soundPlayed = true;
            }


            // =====> marshmallow cloud
            if (sdxMClouds < 1.7f) {
                shakeBackground = true;
                sdxMClouds += sdxMCloudsSpeed; // Move marshmallow cloud to the right
                sdyMClouds += sdyMCloudsSpeed; // Move marshmallow cloud to the right
                // cout << "sdxMClouds: " << sdxMClouds << ", sdyMClouds: " << sdyMClouds << endl;
            } else {
                shakeBackground = false;
                if (toggleMClouds) {
                    dxMClouds = MCloudShakeSpeed; // Reset position when it goes off screen
                    dyMClouds = MCloudShakeSpeed; // Reset position when it goes off screen
                    toggleMClouds = false; // Toggle to false to reset position
                } else {
                    dxMClouds = -MCloudShakeSpeed; // Reset position when it goes off screen
                    dyMClouds = -MCloudShakeSpeed; // Reset position when it goes off screen
                    toggleMClouds = true; // Toggle to true to reset position
                }
            }

            // =====> shake background
            if (shakeBackground) {
                if (toggleBackground) {
                    dxBackground = backgroundShakeSpeed;
                    dyBackground = backgroundShakeSpeed;
                    toggleBackground = false;
                } else {
                    dxBackground = -backgroundShakeSpeed;
                    dyBackground = -backgroundShakeSpeed;
                    toggleBackground = true;
                }
            }

            // =====> Particles
            if (!resetParticles) {
                dxParticles += dxParticlesSpeed; // Move particles to the right
                dyParticles += dyParticlesSpeed; // Move particles down
            }

            if (dxParticles > 0.05f || dyParticles > 0.05f) {
                resetParticles = true; // Reset particles
            }

            if (resetParticles && (dxParticles > 0.0f && dyParticles > 0.0f)) {
                dxParticles -= (dxParticlesSpeed - 0.0001f);
                dyParticles -= (dyParticlesSpeed - 0.0002f);
            }
            cout << "dxParticles: " << dxParticles << ", dyParticles: " << dyParticles << endl;

            // =====> buildings collapse
            if (dyBuilding1 > -0.08f) {
                dyBuilding1 -= dyBuilding1Speed; // Move building down
                rotateBuilding1 -= rotateBuilding1Speed; // Rotate building
            }
            if (dyBuilding2 > -0.07f) {
                dyBuilding2 -= dyBuilding2Speed; // Move building down
                rotateBuilding2 += rotateBuilding2Speed; // Rotate building
            }
        }

        glutPostRedisplay(); // Request a redraw
    }

    void handleKey(unsigned char key, int x, int y) {
        // printf("Key pressed: %c at (%d, %d)\n", key, x, y);

        if (key == 27) { // Escape key
            exit(0); // Exit the program
        } else if (key == 'd' || key == 'D') {
            glutDisplayFunc(Scene3::display2Wrapper);
            glutIdleFunc(Scene3::updateWrapper);
            glutPostRedisplay();
        } else if (key == 'a' || key == 'A') {
            glutDisplayFunc(Scene3::display1Wrapper);
            PlaySound(NULL, NULL, SND_ASYNC | SND_PURGE);
            glutIdleFunc(NULL);
            glutPostRedisplay();
        } else if (key == 'w' || key == 'W') {
            increaseSpeed(); // Increase speeds
        } else if (key == 's' || key == 'S') {
            decreaseSpeed();
        }
    }

    void increaseSpeed() {
        // Increase speeds
        // Increase speeds with maximum limits
        xCloud1Speed = min(0.01f, xCloud1Speed + 0.001f);
        xCloud2Speed = min(0.01f, xCloud2Speed + 0.001f);
        xCloud3Speed = min(0.01f, xCloud3Speed + 0.001f);
        sdxMCloudsSpeed = min(0.01f, sdxMCloudsSpeed + 0.001f);
        sdyMCloudsSpeed = min(0.01f, sdyMCloudsSpeed + 0.001f);
        nukeSpeed = min(0.01f, nukeSpeed + 0.001f);
        dxParticlesSpeed = min(0.001f, dxParticlesSpeed + 0.0001f);
        dyParticlesSpeed = min(0.001f, dyParticlesSpeed + 0.0001f);
        dyBuilding1Speed = min(0.001f, dyBuilding1Speed + 0.0001f);
        dyBuilding2Speed = min(0.001f, dyBuilding2Speed + 0.0001f);
    }

    void decreaseSpeed() {
        // Decrease speeds with minimum limits
        xCloud1Speed = max(0.001f, xCloud1Speed - 0.001f);
        xCloud2Speed = max(0.001f, xCloud2Speed - 0.001f);
        xCloud3Speed = max(0.001f, xCloud3Speed - 0.001f);
        sdxMCloudsSpeed = max(0.001f, sdxMCloudsSpeed - 0.001f);
        sdyMCloudsSpeed = max(0.001f, sdyMCloudsSpeed - 0.001f);
        nukeSpeed = max(0.001f, nukeSpeed - 0.001f);
        dxParticlesSpeed = max(0.0001f, dxParticlesSpeed - 0.0001f);
        dyParticlesSpeed = max(0.0001f, dyParticlesSpeed - 0.0001f);
        dyBuilding1Speed = max(0.0001f, dyBuilding1Speed - 0.0001f);
        dyBuilding2Speed = max(0.0001f, dyBuilding2Speed - 0.0001f);
    }


    // Entry point (static methods) - Singleton pattern
    static void display1Wrapper() { 
        if (instance == nullptr) {
            cerr << "Scene3 instance is not initialized, display1 cannot be called!" << endl;
            return;
        }
        instance->display1(); 
    }
    static void display2Wrapper() { 
        if (instance == nullptr) {
            cerr << "Scene3 instance is not initialized, display2 cannot be called!" << endl;
            return;
        }
        instance->display2(); 
    }
    static void updateWrapper() { 
        if (instance == nullptr) {
            cerr << "Scene3 instance is not initialized, update cannot be called!" << endl;
            return;
        }
        instance->update(); 
    }
    static void handleKeyWrapper(unsigned char key, int x, int y) { 
        if (instance == nullptr) {
            cerr << "Scene3 instance is not initialized, handleKey cannot be called!" << endl;
            return;
        }
        instance->handleKey(key, x, y); 
    }

};

class Scene4 : SceneManager {
public:
    //Global variables
    // animation control
    bool pause = false;

    //cloud
    GLfloat cloudPosition = 0.0f;
    GLfloat cloudSpeed = 0.005f;

    //Smoke1
    float smoke1Speed = 0.005f;

    float minXSmoke1 = -0.374f;

    float minYSmoke1 = 0.101f;
    float maxYSmoke1 = 0.472f;

    vector<float> XSmoke1 = {-0.374f,-0.338f,-0.316f,-0.298f,-0.260f,-0.210f,-0.215f,-0.247f,-0.292f,-0.288f,-0.406f,-0.438f,-0.471f,-0.521f,-0.540f,-0.537f,-0.572f,-0.619f,-0.677f,-0.726f,-0.765f,-0.769f,-0.741f,-0.709f,-0.665f,-0.618f,-0.595f,-0.417f,-0.434f,-0.429f,-0.403f,-0.357f,-0.397f,-0.356f,-0.330f,-0.338f,-0.259f,-0.308f,-0.255f,-0.206f,-0.236f,-0.315f,-0.452f,-0.500f,-0.694f,-0.600f,-0.569f,-0.277f,-0.248f};

    vector<float> YSmoke1 = {0.101f,0.124f,0.162f,0.208f,0.253f,0.259f,0.209f,0.167f,0.134f,0.103f,0.116f,0.149f,0.188f,0.192f,0.220f,0.267f,0.320f,0.349f,0.344f,0.346f,0.325f,0.296f,0.307f,0.309f,0.312f,0.314f,0.276f,0.242f,0.276f,0.272f,0.317f,0.316f,0.356f,0.347f,0.368f,0.423f,0.420f,0.455f,0.472f,0.427f,0.440f,0.411f,0.236f,0.150f,0.326f,0.300f,0.286f,0.182f,0.217f};

    vector<float> tempXSmoke1 = {-0.374f,-0.338f,-0.316f,-0.298f,-0.260f,-0.210f,-0.215f,-0.247f,-0.292f,-0.288f,-0.406f,-0.438f,-0.471f,-0.521f,-0.540f,-0.537f,-0.572f,-0.619f,-0.677f,-0.726f,-0.765f,-0.769f,-0.741f,-0.709f,-0.665f,-0.618f,-0.595f,-0.417f,-0.434f,-0.429f,-0.403f,-0.357f,-0.397f,-0.356f,-0.330f,-0.338f,-0.259f,-0.308f,-0.255f,-0.206f,-0.236f,-0.315f,-0.452f,-0.500f,-0.694f,-0.600f,-0.569f,-0.277f,-0.248f};

    vector<float> tempYSmoke1 = {0.101f,0.124f,0.162f,0.208f,0.253f,0.259f,0.209f,0.167f,0.134f,0.103f,0.116f,0.149f,0.188f,0.192f,0.220f,0.267f,0.320f,0.349f,0.344f,0.346f,0.325f,0.296f,0.307f,0.309f,0.312f,0.314f,0.276f,0.242f,0.276f,0.272f,0.317f,0.316f,0.356f,0.347f,0.368f,0.423f,0.420f,0.455f,0.472f,0.427f,0.440f,0.411f,0.236f,0.150f,0.326f,0.300f,0.286f,0.182f,0.217f};

    //Smoke2
    float smoke2Speed = 0.005f;

    float minXSmoke2 = 0.173f;

    float minYSmoke2 = 0.07f;
    float maxYSmoke2 = 0.324f;

    vector<float> XSmoke2 = {0.173f, 0.207f, 0.239f, 0.278f, 0.246f, 0.301f, 0.295f, 0.335f, 0.307f, 0.376f, 0.362f, 0.177f, 0.270f, 0.266f, 0.217f, 0.328f, 0.317f};
    vector<float> YSmoke2 = {0.098f, 0.144f, 0.166f, 0.197f, 0.220f, 0.235f, 0.253f, 0.270f, 0.298f, 0.294f, 0.324f, 0.127f, 0.159f, 0.257f, 0.183f, 0.239f, 0.330f};

    vector<float> tempXSmoke2 = {0.173f, 0.207f, 0.239f, 0.278f, 0.246f, 0.301f, 0.295f, 0.335f, 0.307f, 0.376f, 0.362f, 0.177f, 0.270f, 0.266f, 0.217f, 0.328f, 0.317f};
    vector<float> tempYSmoke2 = {0.098f, 0.144f, 0.166f, 0.197f, 0.220f, 0.235f, 0.253f, 0.270f, 0.298f, 0.294f, 0.324f, 0.127f, 0.159f, 0.257f, 0.183f, 0.239f, 0.330f};

    //Building 1 Smoke
    float Building1SmokeSpeed = 0.005f;

    float minXBuilding1Smoke = -0.549f;

    float minYBuilding1Smoke = 0.143f;
    float maxYBuilding1Smoke = 0.230f;

    vector<float> XBuilding1Smoke = {-0.549f,-0.557f,-0.558f,-0.534f,-0.539f,-0.492f,-0.454f,-0.475f,-0.524f,-0.552f};
    vector<float> YBuilding1Smoke = {0.143f,0.165f,0.191f,0.202f,0.128f,0.111f,0.104f,0.071f,0.121f,0.230f};

    vector<float> tempXBuilding1Smoke = {-0.549f,-0.557f,-0.558f,-0.534f,-0.539f,-0.492f,-0.454f,-0.475f,-0.524f,-0.552f};
    vector<float> tempYBuilding1Smoke = {0.143f,0.165f,0.191f,0.202f,.128f,0.111f,0.104f,0.071f,0.121f,0.230f};

    //House 1 Smoke
    float House1SmokeXposition = 0.0f;
    float House1SmokeYposition = 0.0f;
    float House1SmokeSpeed = 0.005f;

    float minXHouse1Smoke = 0.800;

    float minYHouse1Smoke = 0.150f;
    float maxYHouse1Smoke = 0.282f;

    vector<float> XHouse1Smoke = {0.767f,0.802f,0.844f,0.947f,0.864f,0.954f,0.915f,0.988f};
    vector<float> YHouse1Smoke = {0.135f,0.197f,0.175f,0.182f,0.249f,0.281f,0.231f,0.227f};

    vector<float> tempXHouse1Smoke = {0.767f,0.802f,0.844f,0.947f,0.864f,0.954f,0.915f,0.988f};
    vector<float> tempYHouse1Smoke = {0.135f,0.197f,0.175f,0.182f,0.249f,0.281f,0.231f,0.227f};

    // Scene4 instance
    static Scene4* instance;



    /* Handler for window-repaint event. Call back when the window first appears and
    whenever the window needs to be re-painted. */
    // void renderBitmapString(float x, float y, float z, void *font, char *string)
    // {
    //     char *c;
    //     glRasterPos3f(x, y,z);
    //     for (c=string; *c != '\0'; c++)
    //     {
    //         glutBitmapCharacter(font, *c);
    //     }
    // }

    //Circle
    void drawCircle(float x, float y, float radius, int triangleAmount, float r, float g, float b)
    {

        GLfloat twicePi = 2.0f * PI;

        glColor3f(r,g,b);

        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(x, y); // center of circle
            for(int i = 0; i <= triangleAmount;i++)
            {
                float angle = i *  twicePi / triangleAmount;
                glVertex2f( x + (radius * cos(angle)), y + (radius * sin(angle)));
            }

        glEnd();
    }

    //Half Circle
    void drawHalfCircle(float x, float y, float radius, int triangleAmount, float r, float g, float b)
    {

        glColor3f(r,g,b);

        glBegin(GL_TRIANGLE_FAN);
            glVertex2f(x, y); // center of circle
            for(int i = 0; i <= triangleAmount;i++)
            {
                float angle = i *  PI / triangleAmount;
                glVertex2f( x + (radius * cos(angle)), y + (radius * sin(angle)));
            }

        glEnd();
    }

    //Wave
    void drawWave(float frequency, float hight, float shift, float r, float g, float b)
    {
        glColor3f(r,g,b);
        glBegin(GL_TRIANGLE_STRIP);

        for (float x = -1.0f; x <= 1.0f; x += 0.01f)
        {
            int loop = (int)floorf((x + shift + 1.0f) * frequency / 2.0f);

            srand(loop * 16339 + 53753);

            float randAmp = ((rand() % 1000) / 1000.0f) * hight;
            randAmp += ((rand() % 500) / 1000.0f) * hight;

            if (randAmp > hight) randAmp = hight;

            float y = randAmp * sinf(frequency * 3.1416f * (x + shift)) + 0.2;

            glVertex2f(x, y);
            glVertex2f(x, 0.0f);
        }
        glEnd();
    }

    //Cloud
    void draw_Middle_Cloud(float x, float y, float radius)
    {
        float r = 243.0f/255.0f;
        float g = 225.0f/255.0f;
        float b = 147.0f/255.0f;
        float triangles = 100;

        drawCircle(x, y, radius, triangles, r, g, b);
        drawCircle(x+0.055f, y-0.01f, radius-0.01f, triangles, r, g, b);
        drawCircle(x+0.09f, y-0.035f, radius-0.013f, triangles, r, g, b);
        drawCircle(x-0.06f, y-0.02f, radius-0.012f, triangles, r, g, b);
        drawCircle(x-0.093f, y-0.04f, radius-0.02f, triangles, r, g, b);
        drawCircle(x-0.108f, y-0.05f, radius-0.028f, triangles, r, g, b);

        drawHalfCircle(x, y-0.064f, radius+0.01, triangles, r, g, b);
        drawHalfCircle(x+0.055f, y-0.064f, radius-0.01f, triangles, r, g, b);
        drawHalfCircle(x+0.06f, y-0.064f, radius-0.013f, triangles, r, g, b);
        drawHalfCircle(x-0.06f, y-0.064f, radius-0.012f, triangles, r, g, b);
        drawHalfCircle(x-0.088f, y-0.064f, radius-0.02f, triangles, r, g, b);

    }

    void draw_Left_Cloud(float x, float y, float radius)
    {
        float r = 243.0f/255.0f;
        float g = 225.0f/255.0f;
        float b = 147.0f/255.0f;
        float triangles = 100;

        drawCircle(x, y, radius, triangles, r, g, b);
        drawCircle(x+0.055f, y-0.01f, radius-0.01f, triangles, r, g, b);
        drawCircle(x+0.09f, y-0.034f, radius-0.013f, triangles, r, g, b);
        drawCircle(x-0.06f, y-0.02f, radius-0.012f, triangles, r, g, b);
        drawCircle(x-0.093f, y-0.04f, radius-0.02f, triangles, r, g, b);
        drawCircle(x-0.11f, y-0.049f, radius-0.028f, triangles, r, g, b);

        drawHalfCircle(x, y-0.0685f, radius+0.01, triangles, r, g, b);
        drawHalfCircle(x+0.055f, y-0.0685f, radius-0.01f, triangles, r, g, b);
        drawHalfCircle(x+0.06f, y-0.0688f, radius-0.013f, triangles, r, g, b);
        drawHalfCircle(x-0.06f, y-0.0685f, radius-0.012f, triangles, r, g, b);
        drawHalfCircle(x-0.088f, y-0.0685f, radius-0.02f, triangles, r, g, b);

    }

    void draw_Right_Cloud(float x, float y, float radius)
    {
        float r = 243.0f/255.0f;
        float g = 225.0f/255.0f;
        float b = 147.0f/255.0f;
        float triangles = 100;

        drawCircle(x, y, radius, triangles, r, g, b);
        drawCircle(x+0.055f, y-0.01f, radius-0.01f, triangles, r, g, b);
        drawCircle(x+0.09f, y-0.036f, radius-0.013f, triangles, r, g, b);
        drawCircle(x-0.055f, y-0.03f, radius-0.012f, triangles, r, g, b);
        drawCircle(x-0.093f, y-0.04f, radius-0.02f, triangles, r, g, b);
        drawCircle(x-0.108f, y-0.05f, radius-0.028f, triangles, r, g, b);

        drawHalfCircle(x, y-0.061f, radius+0.02f, triangles, r, g, b);
        drawHalfCircle(x+0.055f, y-0.061f, radius, triangles, r, g, b);
        drawHalfCircle(x+0.06f, y-0.061f, radius, triangles, r, g, b);
        drawHalfCircle(x-0.06f, y-0.061f, radius, triangles, r, g, b);
        drawHalfCircle(x-0.088f, y-0.061f, radius-0.02f, triangles, r, g, b);

    }

    //Side Road
    void drawSideRoad()
    {
        glColor3f(205.0f/255.0f, 179.0f/255.0f, 82.0f/255.0f);
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
    }

    //Hills
    void drawHill()
    {
        drawWave(2.5f, 0.12f, 0.6f, 93.0f/255.0f, 130.0f/255.0f, 13.0f/255.0f);
        drawWave(3.0f, 0.19f, 0.2f, 97.0f/255.0f, 135.0f/255.0f, 14.0f/255.0f);
    }

    //Sun
    void drawSun(float sx, float sy, float sradius)
    {
        drawCircle(sx, sy, sradius, 100, 232.0f/255.0f, 173.0f/255.0f, 17.0f/255.0f);

        int sunRays = 10;
        float rayInterval = 360/sunRays;

        glBegin(GL_LINES);
        for (int i = 0; i < 360; i += rayInterval)
        {
            float angle = 2 * PI * i / 360.0;

            float x1 = sx + (sradius + 0.01) * cos(angle);
            float y1 = sy + (sradius + 0.01) * sin(angle);
            float x2 = sx + (sradius + 0.08) * cos(angle);
            float y2 = sy + (sradius + 0.08) * sin(angle);

            glVertex2f(x1, y1);
            glVertex2f(x2, y2);
        }
        glEnd();
    }


    //All Clouds
    void drawCloud()
    {
        glPushMatrix();
        glTranslatef(cloudPosition, 0.0f, 0.0f);
            draw_Middle_Cloud(0.0f, 0.46f, 0.042f);
            draw_Left_Cloud(-0.7f, 0.48f, 0.048f);
            draw_Right_Cloud(0.8f, 0.42f, 0.038f);
        glPopMatrix();
    }

    //Main Ground
    void drawGround()
    {
        glColor3f(111.0f/255.0f, 133.0f/255.0f, 11.0f/255.0f);
        glBegin(GL_POLYGON);
        glVertex2f(-1.0f, 0.03f);
        glVertex2f( -1.0f, -0.5625f);
        glColor3f(112.0f/255.0f, 140.0f/255.0f, 8.0f/255.0f);
        glVertex2f( 1.0f, -0.5625f);
        glVertex2f( 1.0f, 0.03f);

        glEnd();
    }

    //Main Road
    void drawRoad()
    {
        glColor3f(38.0f/255.0f, 66.0f/255.0f, 28.0f/255.0f);
        glBegin(GL_POLYGON);

        glVertex2f( -1.0f, -0.20f);
        glVertex2f( 1.0f, -0.20f);
        glVertex2f(1.0f, -0.070f);
        glVertex2f( -1.0f, -0.070f);

        glEnd();
    }

    //Ground Right side Corner
    void drawShrub1()
    {
        float r = 51.0f/255.0f;
        float g = 97.0f/255.0f;
        float b = 11.0f/255.0f;


        drawCircle(0.964f, -0.443f, 0.042f, 100, r,g,b);
        drawCircle(0.875f, -0.428f, 0.055f, 100, r,g,b);
        drawCircle(0.784f, -0.387f, 0.060f, 100, r,g,b);
        drawCircle(0.707f, -0.460f, 0.060f, 100, r,g,b);
        drawCircle(0.626f, -0.480f, 0.059f, 100, r,g,b);
        drawCircle(0.555f, -0.532f, 0.035f, 100, r,g,b);

        glBegin(GL_POLYGON);
        glVertex2f(1.0f, -1.0f);
        glVertex2f(1.0f, -0.443f);
        glVertex2f(0.964f, -0.443f);
        glVertex2f(0.875f, -0.428f);
        glVertex2f(0.784f, -0.387f);
        glVertex2f(0.707f, -0.460f);
        glVertex2f(0.626f, -0.480f);
        glVertex2f(0.555f, -0.528f);
        glVertex2f(0.555f, -1.0f);
        glEnd();

        r = 46.0f/255.0f;
        g = 86.0f/255.0f;
        b = 11.0f/255.0f;

        glPushMatrix();
        glScalef(0.9f, 0.9f, 0.9f);
        glTranslatef(0.15f, -0.12f, 0.0f);

        drawCircle(0.964f, -0.443f, 0.042f, 100, r,g,b);
        drawCircle(0.875f, -0.428f, 0.055f, 100, r,g,b);
        drawCircle(0.784f, -0.387f, 0.060f, 100, r,g,b);
        drawCircle(0.707f, -0.460f, 0.060f, 100, r,g,b);
        drawCircle(0.626f, -0.480f, 0.059f, 100, r,g,b);
        drawCircle(0.555f, -0.532f, 0.035f, 100, r,g,b);

        glBegin(GL_POLYGON);
        glVertex2f(1.0f, -1.0f);
        glVertex2f(1.0f, -0.443f);
        glVertex2f(0.964f, -0.443f);
        glVertex2f(0.875f, -0.428f);
        glVertex2f(0.784f, -0.387f);
        glVertex2f(0.707f, -0.460f);
        glVertex2f(0.626f, -0.480f);
        glVertex2f(0.555f, -0.528f);
        glVertex2f(0.555f, -1.0f);
        glEnd();

        glPopMatrix();
    }

    //Behind the right side house
    void drawShrub2()
    {
        float r = 51.0f/255.0f;
        float g = 97.0f/255.0f;
        float b = 11.0f/255.0f;


        drawCircle(0.974f, 0.159f, 0.026f, 100, r,g,b);
        drawCircle(0.932f, 0.179f, 0.029f, 100, r,g,b);
        drawCircle(0.887f, 0.197f, 0.039f, 100, r,g,b);
        drawCircle(0.824f, 0.189f, 0.027f, 100, r,g,b);
        drawCircle(0.772f, 0.176f, 0.033f, 100, r,g,b);
        drawCircle(0.731f, 0.164f, 0.016f, 100, r,g,b);
        drawCircle(0.685f, 0.146f, 0.039f, 100, r,g,b);

        glBegin(GL_POLYGON);
        glVertex2f(1.0f, 0.159f);
        glVertex2f(0.932f, 0.179f);
        glVertex2f(0.887f, 0.197f);
        glVertex2f(0.824f, 0.189f);
        glVertex2f(0.772f, 0.176f);
        glVertex2f(0.731f, 0.164f);
        glVertex2f(0.646f, 0.146f);
        glVertex2f(0.646f, 0.040f);
        glVertex2f(1.0f, 0.040f);
        glEnd();
    }

    //Infront of all buildings
    void drawShrub3()
    {
        float r = 51.0f/255.0f;
        float g = 97.0f/255.0f;
        float b = 11.0f/255.0f;

        drawHalfCircle(-1.0f, 0.006f, 0.019f, 100, r,g,b);
        drawHalfCircle(-0.957f, 0.006f, 0.028f, 100, r,g,b); //O
        drawHalfCircle(-0.910f, 0.001f, 0.023f, 100, r,g,b); //P


        glBegin(GL_POLYGON);
        glVertex2f(-1.0f, 0.006f);
        glVertex2f(-0.933f, 0.001f);
        glVertex2f(-0.910f, 0.001f);
        glVertex2f(-0.929f, 0.006f);
        glEnd();
    }

    void drawShrub4()
    {
        float r = 51.0f/255.0f;
        float g = 97.0f/255.0f;
        float b = 11.0f/255.0f;

        drawHalfCircle(-0.915f, -0.020f, 0.018f, 100, r,g,b); //Q
        drawHalfCircle(-0.885f, -0.018f, 0.021f, 100, r,g,b); //R
        drawHalfCircle(-0.855f, -0.026f, 0.016f, 100, r,g,b); //S


        glBegin(GL_POLYGON);
        glVertex2f(-0.839f, -0.026f);
        glVertex2f(-0.839f, -0.032f);
        glVertex2f(-0.874f, -0.032f);
        glVertex2f(-0.933f, -0.029f);
        glVertex2f(-0.933f, -0.020f);
        glVertex2f(-0.864f, -0.018f);
        glEnd();
    }

    void drawShrub5()
    {
        float r = 51.0f/255.0f;
        float g = 97.0f/255.0f;
        float b = 11.0f/255.0f;

        drawHalfCircle(-0.707f, -0.031f, 0.018f, 100, r,g,b); //T
        drawHalfCircle(-0.681f, -0.032f, 0.030f, 100, r,g,b); //U
        drawHalfCircle(-0.634f, -0.024f, 0.020f, 100, r,g,b); //V
        drawHalfCircle(-0.602f, -0.029f, 0.014f, 100, r,g,b); //W
        drawHalfCircle(-0.585f, -0.035f, 0.007f, 100, r,g,b); //Z


        glBegin(GL_POLYGON);
        glVertex2f(-0.725f, -0.031f);
        glVertex2f(-0.725f, -0.034f);
        glVertex2f(-0.578f, -0.035f);
        glVertex2f(-0.588f, -0.029f);
        glVertex2f(-0.616f, -0.029f);
        glVertex2f(-0.614f, -0.024f);
        glVertex2f(-0.654f, -0.024f);
        glVertex2f(-0.651f, -0.032f);
        glEnd();
    }

    void drawShrub6()
    {
        float r = 51.0f/255.0f;
        float g = 97.0f/255.0f;
        float b = 11.0f/255.0f;

        drawHalfCircle(-0.534f, -0.023f, 0.015f, 100, r,g,b); //A1
        drawHalfCircle(-0.508f, -0.032f, 0.017f, 100, r,g,b); //B1


        glBegin(GL_POLYGON);
        glVertex2f(-0.549f, -0.023f);
        glVertex2f(-0.550f, -0.031f);
        glVertex2f(-0.491f, -0.032f);
        glVertex2f(-0.519f, -0.023f);
        glEnd();
    }

    void drawShrub7()
    {
        float r = 51.0f/255.0f;
        float g = 97.0f/255.0f;
        float b = 11.0f/255.0f;

        drawHalfCircle(-0.418f, -0.038f, 0.014f, 100, r,g,b); //C1
        drawHalfCircle(-0.394f, -0.036f, 0.018f, 100, r,g,b); //D1
        drawHalfCircle(-0.360f, -0.028f, 0.023f, 100, r,g,b); //E1
        drawHalfCircle(-0.322f, -0.024f, 0.017f, 100, r,g,b); //F1
        drawHalfCircle(-0.272f, -0.027f, 0.034f, 100, r,g,b); //I1
        drawHalfCircle(-0.222f, -0.034f, 0.024f, 100, r,g,b); //J1


        glBegin(GL_POLYGON);
        glVertex2f(-0.432f, -0.038f);
        glVertex2f(-0.198f, -0.034f);
        glVertex2f(-0.238f, -0.027f);
        glVertex2f(-0.306f, -0.027f);
        glVertex2f(-0.305f, -0.024f);
        glVertex2f(-0.339f, -0.024f);
        glVertex2f(-0.337f, -0.028f);
        glVertex2f(-0.383f, -0.028f);
        glVertex2f(-0.376f, -0.036f);
        glVertex2f(-0.412f, -0.036f);
        glEnd();
    }

    void drawShrub8()
    {
        float r = 51.0f/255.0f;
        float g = 97.0f/255.0f;
        float b = 11.0f/255.0f;
        glColor3f(r, g, b);

        glBegin(GL_POLYGON);
        glVertex2f(0.044f, -0.074f); //U11
        glVertex2f(0.095f, -0.075f); //V11
        glVertex2f(0.083f, -0.060f); //W11
        glVertex2f(0.080f, -0.060f); //Z11
        glVertex2f(0.076f, -0.058f); //A12
        glVertex2f(0.074f, -0.058f); //B12
        glVertex2f(0.069f, -0.057f); //C12
        glVertex2f(0.065f, -0.060f); //D12
        glVertex2f(0.062f, -0.061f); //E12
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(0.160f, -0.074f); //F12
        glVertex2f(0.205f, -0.074f); //G12
        glVertex2f(0.194f, -0.064f); //H12
        glVertex2f(0.191f, -0.063f); //I12
        glVertex2f(0.188f, -0.062f); //J12
        glVertex2f(0.184f, -0.063f); //K12
        glVertex2f(0.180f, -0.063f); //L12
        glVertex2f(0.176f, -0.063f); //M12
        glVertex2f(0.174f, -0.064f); //N12
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(0.206f, -0.063f); //O12
        glVertex2f(0.248f, -0.065f); //P12
        glVertex2f(0.245f, -0.060f); //Q12
        glVertex2f(0.242f, -0.057f); //R12
        glVertex2f(0.238f, -0.053f); //S12
        glVertex2f(0.233f, -0.050f); //T12
        glVertex2f(0.227f, -0.049f); //U12
        glVertex2f(0.223f, -0.050f); //V12
        glVertex2f(0.217f, -0.053f); //W12
        glVertex2f(0.212f, -0.057f); //Z12
        glEnd();
    }

    //Sky
    void drawSky()
    {
        glColor3f(98.0/255.0f, 180.0/255.0f, 168.0/255.0f);
        glBegin(GL_POLYGON);

        glVertex2f( -1.0f, 0.5625f);
        glVertex2f( 1.0f, 0.5625f);
        //glColor3f(98.0/255.0f, 150.0/255.0f, 180.0/255.0f);
        glVertex2f( 1.0f, 0.03f);
        glVertex2f(-1.0f, 0.03f);

        glEnd();
    }

    //Building Window
    void drawBuildingWindow(float x, float y, bool windowLine_x, bool windowLine_y, float r, float g, float b)
    {
        //Shadow Color
        float r_S = 25.0f/255.0f;
        float g_S = 43.0f/255.0f;
        float b_S = 22.0f/255.0f;

        glColor3f(r_S,g_S,b_S);
        glBegin(GL_POLYGON);

        glVertex2f(x + -0.031f, y + 0.09f); //E4
        glVertex2f(x + 0.030f, y + 0.09f);  //F4
        glVertex2f(x + 0.030f, y + 0.054f); //G4
        glVertex2f(x + -0.031f, y + 0.054f); //H4

        glEnd();


        //Building Color
        float r_B = r;
        float g_B = g;
        float b_B = b;

        if(windowLine_x)
        {
            glColor3f(r_B, g_B, b_B);
            glLineWidth(2.0f);
            glBegin(GL_LINES);


            glVertex2f(x + -0.031f, y + 0.0716f);
            glVertex2f(x + 0.030f, y + 0.0716f);

            glEnd();
        }

        if(windowLine_y)
        {
            glColor3f(r_B, g_B, b_B);
            glLineWidth(2.0f);
            glBegin(GL_LINES);

            glVertex2f(x + -0.01f, y + 0.09f);
            glVertex2f(x + -0.01f, y + 0.054f);

            glEnd();
        }
    }

    //Building Broken Part
    void drawBuildingInnerBrokenPart(float x, float y)
    {
        //Shadow Color
        float r_S = 25.0f/255.0f;
        float g_S = 43.0f/255.0f;
        float b_S = 22.0f/255.0f;

        glColor3f(r_S,g_S,b_S);
        glBegin(GL_POLYGON);

        glVertex2f(x + -0.011f, y + 0.187f); //M4
        glVertex2f(x + -0.005f, y + 0.186f); //N4
        glVertex2f(x + -0.006f, y + 0.186f); //O4
        glVertex2f(x + 0.005f, y + 0.18f);  //P4
        glVertex2f(x + 0.005f, y + 0.176f); //Q4
        glVertex2f(x + 0.001f, y + 0.17f);  //R4
        glVertex2f(x + -0.008f, y + 0.17f); //S4
        glVertex2f(x + -0.010f, y + 0.165f); //T4
        glVertex2f(x + -0.006f, y + 0.161f); //U4
        glVertex2f(x + -0.010f, y + 0.154f); //V4
        glVertex2f(x + -0.011f, y + 0.144f); //W4
        glVertex2f(x + -0.016f, y + 0.135f); //Z4
        glVertex2f(x + -0.029f, y + 0.149f); //A5
        glVertex2f(x + -0.040f, y + 0.144f); //B5
        glVertex2f(x + -0.047f, y + 0.159f); //C5
        glVertex2f(x + -0.038f, y + 0.171f); //D5
        glVertex2f(x + -0.044f, y + 0.18f);  //E5
        glVertex2f(x + -0.037f, y + 0.187f); //F5
        glVertex2f(x + -0.031f, y + 0.187f); //G5
        glVertex2f(x + -0.031f, y + 0.195f); //H5
        glVertex2f(x + -0.026f, y + 0.201f); //I5
        glVertex2f(x + -0.022f, y + 0.197f); //J5
        glVertex2f(x + -0.019f, y + 0.197f); //K5
        glVertex2f(x + -0.018f, y + 0.203f); //L5
        glVertex2f(x + -0.012f, y + 0.194f); //M5

        glEnd();
    }

    //Building 1 Smoke
    void drawBuilding1Smoke()
    {
        float r = 89.0f/255.0f;
        float g = 111.0f/255.0f;
        float b = 72.0f/255.0f;

        drawCircle(XBuilding1Smoke[0], YBuilding1Smoke[0], 0.011f, 100, r, g, b); //Q
        drawCircle(XBuilding1Smoke[1], YBuilding1Smoke[1], 0.017f, 100, r, g, b); //R
        drawCircle(XBuilding1Smoke[2], YBuilding1Smoke[2], 0.015f, 100, r, g, b); //S
        drawCircle(XBuilding1Smoke[3], YBuilding1Smoke[3], 0.019f, 100, r, g, b); //T
        drawCircle(XBuilding1Smoke[4], YBuilding1Smoke[4], 0.012f, 100, r, g, b); //U
        drawCircle(XBuilding1Smoke[5], YBuilding1Smoke[5], 0.029f, 100, r, g, b); //V
        drawCircle(XBuilding1Smoke[6], YBuilding1Smoke[6], 0.035f, 100, r, g, b); //W
        drawCircle(XBuilding1Smoke[7], YBuilding1Smoke[7], 0.016f, 100, r, g, b); //Z
        drawCircle(XBuilding1Smoke[8], YBuilding1Smoke[8], 0.009f, 100, r, g, b); //A1
        drawCircle(XBuilding1Smoke[9], YBuilding1Smoke[9], 0.026f, 100, r, g, b); //B1
    }

    //Building
    void drawBuilding1(float x, float y, float r, float g, float b)
    {
        //Broken Part Color
        float r_S = 25.0f/255.0f;
        float g_S = 43.0f/255.0f;
        float b_S = 22.0f/255.0f;

        //Building Middle Line
        glColor3f(r_S,g_S,b_S);
        glLineWidth(0.05f);
        glBegin(GL_LINE_STRIP);

        glVertex2f(x + -0.077f, y + 0.0f); //E3
        glVertex2f(x + -0.077f, y + 0.142f); //F3
        glVertex2f(x + -0.059f, y + 0.159f); //G3
        glVertex2f(x + -0.067f, y + 0.17f); //H3
        glVertex2f(x + -0.054f, y + 0.18f); //I3
        glVertex2f(x + -0.061f, y + 0.186f); //J3
        glVertex2f(x + -0.075f, y + 0.188f); //K3
        glVertex2f(x + -0.076f, y + 0.266f); //L3
        glVertex2f(x + -0.060f, y + 0.275f); //M3
        glVertex2f(x + -0.078f, y + 0.281f); //T1

        glEnd();


        //Building Right Side Broken Part
        glColor3f(r_S,g_S,b_S);
        glBegin(GL_POLYGON);

        glVertex2f(x + 0.175f, y + 0.305f); //S2
        glVertex2f(x + 0.171f, y + 0.332f); //R2
        glVertex2f(x + 0.227f, y + 0.293f); //T2
        glVertex2f(x + 0.2155f, y + 0.274f); //U2
        glVertex2f(x + 0.2159f, y + 0.266f); //V2
        glVertex2f(x + 0.226f, y + 0.26f); //W2
        glVertex2f(x + 0.234f, y + 0.245f); //Z2
        glVertex2f(x + 0.223f, y + 0.224f); //Z
        glVertex2f(x + 0.222f, y + 0.198f); //A1
        glVertex2f(x + 0.201f, y + 0.214f); //B1
        glVertex2f(x + 0.175f, y + 0.214f); //C1
        glVertex2f(x + 0.1651f, y + 0.237f); //D1
        glVertex2f(x + 0.1555f, y + 0.273f); //E1
        glVertex2f(x + 0.1251f, y + 0.257f); //F1
        glVertex2f(x + 0.1251f, y + 0.296f); //G1
        glVertex2f(x + 0.113f, y + 0.334f); //H1
        glVertex2f(x + 0.122f, y + 0.377f); //I1
        glVertex2f(x + 0.122f, y + 0.413f); //A3
        glVertex2f(x + 0.132f, y + 0.413f); //B3
        glVertex2f(x + 0.153f, y + 0.393f); //C3
        glVertex2f(x + 0.1851f, y + 0.347f); //D3

        glEnd();

        //Building Left Side Broken Part
        glBegin(GL_POLYGON);

        glVertex2f(x + -0.197f, y + 0.341f); //N3
        glVertex2f(x + -0.183f, y + 0.362f); //O3
        glVertex2f(x + -0.167f, y + 0.344f); //P3
        glVertex2f(x + -0.151f, y + 0.353f); //Q3
        glVertex2f(x + -0.134f, y + 0.333f); //R3
        glVertex2f(x + -0.123f, y + 0.342f); //S3
        glVertex2f(x + -0.100f, y + 0.287f); //T3
        glVertex2f(x + -0.113f, y + 0.294f); //U1
        glVertex2f(x + -0.137f, y + 0.283f); //V1
        glVertex2f(x + -0.156f, y + 0.302f); //W1
        glVertex2f(x + -0.180f, y + 0.297f); //Z1
        glVertex2f(x + -0.213f, y + 0.309f); //A2
        glVertex2f(x + -0.241f, y + 0.345f); //B2
        glVertex2f(x + -0.242f, y + 0.416f); //C2
        glVertex2f(x + -0.231f, y + 0.412f); //U3
        glVertex2f(x + -0.220f, y + 0.406f); //V3
        glVertex2f(x + -0.209f, y + 0.376f); //W3
        glVertex2f(x + -0.183f, y + 0.362f); //O3

        glEnd();

        //Building Upper Broken Part
        glBegin(GL_POLYGON);

        glVertex2f(x + 0.032f, y + 0.433f); //Z3
        glVertex2f(x + 0.051f, y + 0.445f); //A4
        glVertex2f(x + 0.079f, y + 0.424f); //B4
        glVertex2f(x + 0.058f, y + 0.421f); //L1
        glVertex2f(x + 0.0452f, y + 0.4002f); //M1
        glVertex2f(x + 0.018f, y + 0.421f); //N1
        glVertex2f(x + -0.006f, y + 0.417f); //O1
        glVertex2f(x + 0.013f, y + 0.425f); //C4
        glVertex2f(x + 0.024f, y + 0.44f); //D4

        glEnd();


        //Smoke
        glPushMatrix();
        glScalef(1.25f, 1.25f, 1.25f);
        glTranslatef(0.205f, 0.02f, 0.0f);

            drawBuilding1Smoke();

        glPopMatrix();


        //Building Main Shape
        glColor3f(r, g, b);
        glBegin(GL_POLYGON);

        glVertex2f(x + 0.002f, y + 0.0f); //Q2
        glVertex2f(x + 0.266f, y + 0.0f); //T
        glVertex2f(x + 0.266f, y + 0.237f); //U
        glVertex2f(x + 0.249f, y + 0.217f); //V
        glVertex2f(x + 0.244f, y + 0.249f); //W
        glVertex2f(x + 0.223f, y + 0.224f); //Z
        glVertex2f(x + 0.222f, y + 0.198f); //A1
        glVertex2f(x + 0.201f, y + 0.214f); //B1
        glVertex2f(x + 0.175f, y + 0.214f); //C1
        glVertex2f(x + 0.1651f, y + 0.237f); //D1
        glVertex2f(x + 0.1555f, y + 0.273f); //E1
        glVertex2f(x + 0.1251f, y + 0.257f); //F1
        glVertex2f(x + 0.1251f, y + 0.296f); //G1
        glVertex2f(x + 0.113f, y + 0.334f); //H1
        glVertex2f(x + 0.122f, y + 0.377f); //I1
        glVertex2f(x + 0.122f, y + 0.429f); //J1
        glVertex2f(x + 0.094f, y + 0.429f); //K1
        glVertex2f(x + 0.058f, y + 0.421f); //L1
        glVertex2f(x + 0.0452f, y + 0.4002f); //M1
        glVertex2f(x + 0.018f, y + 0.421f); //N1
        glVertex2f(x + -0.006f, y + 0.417f); //O1
        glVertex2f(x + -0.022f, y + 0.44f); //P1
        glVertex2f(x + -0.073f, y + 0.413f); //Q1
        glVertex2f(x + -0.073f, y + 0.329f); //R1
        glVertex2f(x + -0.065f, y + 0.302f); //S1
        glVertex2f(x + -0.078f, y + 0.281f); //T1
        glVertex2f(x + -0.113f, y + 0.294f); //U1
        glVertex2f(x + -0.137f, y + 0.283f); //V1
        glVertex2f(x + -0.156f, y + 0.302f); //W1
        glVertex2f(x + -0.18f, y + 0.297f); //Z1
        glVertex2f(x + -0.213f, y + 0.309f); //A2
        glVertex2f(x + -0.241f, y + 0.345f); //B2
        glVertex2f(x + -0.242f, y + 0.416f); //C2
        glVertex2f(x + -0.266f, y + 0.416f); //D2
        glVertex2f(x + -0.266f, y + 0.000f); //S

        glEnd();


        //Window
        drawBuildingWindow(x + -0.15f, y + 0.0f, false, false, r, g, b);
        drawBuildingWindow(x + 0.05f, y + 0.0f, false, true, r, g, b);
        drawBuildingWindow(x + 0.2f, y + 0.0f, false, true, r, g, b);

        drawBuildingWindow(x + -0.15f, y + 0.07f, true, true, r, g, b);
        drawBuildingWindow(x + 0.05f, y + 0.07f, true, true, r, g, b);
        drawBuildingWindow(x + 0.2f, y + 0.07f, false, false, r, g, b);

        drawBuildingWindow(x + -0.15f, y + 0.14f, false, true, r, g, b);
        drawBuildingWindow(x + 0.05f, y + 0.14f, false, true, r, g, b);

        drawBuildingWindow(x + -0.15f, y + 0.21f, true, false, r, g, b);
        drawBuildingWindow(x + 0.05f, y + 0.21f, false, false, r, g, b);

        drawBuildingWindow(x + 0.05f, y + 0.28f, false, true, r, g, b);


        //Inner Broken Part
        drawBuildingInnerBrokenPart(x + 0.0f, y + 0.0f);
        drawBuildingInnerBrokenPart(x + 0.08f, y + 0.11f);
        drawBuildingInnerBrokenPart(x + 0.22f, y - 0.01f);


    }

    void drawBuilding2(float x, float y, float r, float g, float b)
    {
    //Building Main Shape
        glColor3f(r, g, b);
        glBegin(GL_POLYGON);

        glVertex2f(x + 0.084f, y + 0.0f); //Q2
        glVertex2f(x + 0.266f, y + 0.0f); //T
        glVertex2f(x + 0.266f, y + 0.237f); //U

        glVertex2f(x + 0.267f, y + 0.371f); //C1
        glVertex2f(x + 0.249f, y + 0.4009f); //D1
        glVertex2f(x + 0.216f, y + 0.4f); //F1
        glVertex2f(x + 0.182f, y + 0.391f); //G1
        glVertex2f(x + 0.177f, y + 0.416f); //H1

        glVertex2f(x + 0.122f, y + 0.429f); //J1
        glVertex2f(x + 0.094f, y + 0.429f); //K1
        glVertex2f(x + 0.058f, y + 0.421f); //L1
        glVertex2f(x + 0.0452f, y + 0.4002f); //M1
        glVertex2f(x + 0.018f, y + 0.421f); //N1
        glVertex2f(x + -0.006f, y + 0.417f); //O1
        glVertex2f(x + -0.022f, y + 0.44f); //P1
        glVertex2f(x + -0.073f, y + 0.413f); //Q1
        glVertex2f(x + -0.073f, y + 0.329f); //R1
        glVertex2f(x + -0.065f, y + 0.302f); //S1
        glVertex2f(x + -0.078f, y + 0.281f); //T1
        glVertex2f(x + -0.060f, y + 0.275f); //M3
        glVertex2f(x + -0.076f, y + 0.266f); //L3
        glVertex2f(x + -0.075f, y + 0.188f); //K3
        glVertex2f(x + -0.061f, y + 0.186f); //J3
        glVertex2f(x + -0.054f, y + 0.18f); //I3
        glVertex2f(x + -0.067f, y + 0.17f); //H3
        glVertex2f(x + -0.059f, y + 0.159f); //G3
        glVertex2f(x + -0.077f, y + 0.142f); //F3
        glVertex2f(x + -0.077f, y + 0.0f); //E3
        glEnd();


        //Broken Part Color
        float r_S = 25.0f/255.0f;
        float g_S = 43.0f/255.0f;
        float b_S = 22.0f/255.0f;

        glColor3f(r_S,g_S,b_S);

        //Building Right Side Broken Part
        glBegin(GL_POLYGON);


        glVertex2f(x + 0.249f, y + 0.4009f); //D1
        glVertex2f(x + 0.267f, y + 0.371f); //C1

        glVertex2f(x + 0.264f, y + 0.425f); //S2
        glVertex2f(x + 0.234f, y + 0.418f); //D3
        glVertex2f(x + 0.208f, y + 0.426f); //C3

        glVertex2f(x + 0.177f, y + 0.416f); //H1
        glVertex2f(x + 0.182f, y + 0.391f); //G1
        glVertex2f(x + 0.216f, y + 0.4f); //F1

        glEnd();


        //Building Upper Broken Part
        glBegin(GL_POLYGON);

        glVertex2f(x + 0.032f, y + 0.433f); //Z3
        glVertex2f(x + 0.051f, y + 0.445f); //A4
        glVertex2f(x + 0.079f, y + 0.424f); //B4
        glVertex2f(x + 0.058f, y + 0.421f); //L1
        glVertex2f(x + 0.0452f, y + 0.4002f); //M1
        glVertex2f(x + 0.018f, y + 0.421f); //N1
        glVertex2f(x + -0.006f, y + 0.417f); //O1
        glVertex2f(x + 0.013f, y + 0.425f); //C4
        glVertex2f(x + 0.024f, y + 0.44f); //D4

        glEnd();



        //Window
        drawBuildingWindow(x + 0.02f, y + 0.0f, false, true, r, g, b);
        drawBuildingWindow(x + 0.18f, y + 0.0f, false, true, r, g, b);

        drawBuildingWindow(x + 0.02f, y + 0.07f, true, true, r, g, b);
        drawBuildingWindow(x + 0.18f, y + 0.07f, false, false, r, g, b);

        drawBuildingWindow(x + 0.02f, y + 0.14f, false, true, r, g, b);
        drawBuildingWindow(x + 0.18f, y + 0.14f, false, true, r, g, b);

        drawBuildingWindow(x + 0.02f, y + 0.21f, true, true, r, g, b);
        drawBuildingWindow(x + 0.18f, y + 0.21f, false, false, r, g, b);

        drawBuildingWindow(x + 0.02f, y + 0.28f, false, true, r, g, b);
        drawBuildingWindow(x + 0.18f, y + 0.28f, false, true, r, g, b);



        //Inner Broken Part
        drawBuildingInnerBrokenPart(x + 0.06f, y + 0.06f);
        drawBuildingInnerBrokenPart(x + 0.22f, y - 0.035f);


    }

    void drawHouse1(float x, float y)
    {
        //Right
        glColor3f(34.0f/255.0f, 81.0f/255.0f, 63.0f/255.0f);
        glBegin(GL_POLYGON);

        glVertex2f(x + 0.874f, y + -0.023f); //P
        glVertex2f(x + 1.0f, y + -0.015f); //S
        glVertex2f(x + 1.0f, y + 0.113f); //T
        glVertex2f(x + 0.850f, y + 0.1084f); //U
        glVertex2f(x + 0.518f, y + 0.1087f); //V
        glVertex2f(x + 0.519f, y + -0.023f); //O

        glEnd();


        //Front
        glColor3f(49.0f/255.0f, 92.0f/255.0f, 73.0f/255.0f);
        glBegin(GL_POLYGON);

        glVertex2f(x + 0.519f, y + -0.023f); //O
        glVertex2f(x + 0.874f, y + -0.023f); //P
        glVertex2f(x + 0.874f, y + 0.093f); //Q
        glVertex2f(x + 0.519f, y + 0.093f); //R

        glEnd();


        //Front Roof Top
        glColor3f(70.0f/255.0f, 63.0f/255.0f, 7.0f/255.0f);
        glBegin(GL_POLYGON);

        glVertex2f(x + 0.850f, y + 0.1084f); //U
        glVertex2f(x + 0.507f, y + 0.1087f); //A1
        glVertex2f(x + 0.608f, y + 0.224f); //W
        glVertex2f(x + 0.931f, y + 0.224f); //Z

        glEnd();


        //Roof Top Right Side
        glColor3f(31.0f/255.0f, 65.0f/255.0f, 32.0f/255.0f);
        glBegin(GL_POLYGON);

        glVertex2f(x + 0.850f, y + 0.1084f); //U
        glVertex2f(x + 1.0f, y + 0.113f); //T
        glVertex2f(x + 1.0f, y + 0.134f); //B1
        glVertex2f(x + 0.931f, y + 0.224f); //Z

        glEnd();


        //Window Color
        float rW = 29.0f/255.0f;
        float gW = 67.0f/255.0f;
        float bW = 46.0f/255.0f;
        glColor3f(rW, gW, bW);

        //Front Left Window
        glBegin(GL_POLYGON);

        glVertex2f(x + 0.546f, y + 0.075f); //C1
        glVertex2f(x + 0.590f, y + 0.075f); //D1
        glVertex2f(x + 0.590f, y + 0.019f); //E1
        glVertex2f(x + 0.546f, y + 0.019f); //F1

        glEnd();


        //Front Right Window
        glBegin(GL_POLYGON);

        glVertex2f(x + 0.792f, y + 0.075f); //O1
        glVertex2f(x + 0.847f, y + 0.075f); //P1
        glVertex2f(x + 0.847f, y + 0.019f); //K1
        glVertex2f(x + 0.792f, y + 0.019f); //R1

        glEnd();


        //Front Door
        glBegin(GL_POLYGON);

        glVertex2f(x + 0.656f, y + 0.075f); //G1
        glVertex2f(x + 0.712f, y + 0.075f); //H1
        glVertex2f(x + 0.712f, y + -0.023f); //I1
        glVertex2f(x + 0.656f, y + -0.023f); //J1

        glEnd();


        //Right Side Left  Window
        glBegin(GL_POLYGON);

        glVertex2f(x + 0.903f, y + 0.075f); //S1
        glVertex2f(x + 0.931f, y + 0.075f); //T1
        glVertex2f(x + 0.931f, y + 0.021f); //U1
        glVertex2f(x + 0.903f, y + 0.02f); //V1

        glEnd();


        //Right Side Right  Window
        glBegin(GL_POLYGON);

        glVertex2f(x + 0.951f, y + 0.075f); //W1
        glVertex2f(x + 0.979f, y + 0.075f); //Z1
        glVertex2f(x + 0.979f, y + 0.021f); //A2
        glVertex2f(x + 0.951f, y + 0.02f); //B2

        glEnd();



        //Broken Part Color
        float r_S = 25.0f/255.0f;
        float g_S = 43.0f/255.0f;
        float b_S = 22.0f/255.0f;

        //Broken Part
        glColor3f(r_S, g_S, b_S);
        glBegin(GL_POLYGON);

        glVertex2f(x + 0.509f, y + 0.110f); //O
        glVertex2f(x + 0.556f, y + 0.167f); //P
        glVertex2f(x + 0.569f, y + 0.167f); //Q
        glVertex2f(x + 0.579f, y + 0.171f); //R
        glVertex2f(x + 0.584f, y + 0.162f); //S
        glVertex2f(x + 0.592f, y + 0.162f); //T
        glVertex2f(x + 0.597f, y + 0.154f); //U
        glVertex2f(x + 0.599f, y + 0.148f); //V
        glVertex2f(x + 0.607f, y + 0.148f); //W
        glVertex2f(x + 0.609f, y + 0.140f); //Z
        glVertex2f(x + 0.616f, y + 0.135f); //A1
        glVertex2f(x + 0.621f, y + 0.133f); //B1
        glVertex2f(x + 0.633f, y + 0.128f); //C1
        glVertex2f(x + 0.624f, y + 0.120f); //D1
        glVertex2f(x + 0.614f, y + 0.117f); //E1
        glVertex2f(x + 0.603f, y + 0.121f); //F1
        glVertex2f(x + 0.603f, y + 0.113f); //G1
        glVertex2f(x + 0.594f, y + 0.109f); //H1

        glEnd();


        glBegin(GL_POLYGON);

        glVertex2f(x + 0.758f, y + 0.210f); //J1
        glVertex2f(x + 0.75f, y + 0.2f); //K1
        glVertex2f(x + 0.764f, y + 0.199f); //L1
        glVertex2f(x + 0.775f, y + 0.189f); //M1
        glVertex2f(x + 0.8f, y + 0.2f); //N1
        glVertex2f(x + 0.818f, y + 0.195f); //O1
        glVertex2f(x + 0.829f, y + 0.215f); //P1
        glVertex2f(x + 0.818f, y + 0.224f); //Q1
        glVertex2f(x + 0.755f, y + 0.224f); //I1

        glEnd();




    }

    void drawHouse2(float x, float y)
    {
        //Front
        glColor3f(78.0f/255.0f, 66.0f/255.0f, 6.0f/255.0f);
        glBegin(GL_POLYGON);

        glVertex2f(x + 0.144f, y + 0.0018f); //M
        glVertex2f(x + 0.347f, y + 0.0018f); //O
        glVertex2f(x + 0.347f, y + 0.09f); //P
        glVertex2f(x + 0.248f, y + 0.197f); //Q
        glVertex2f(x + 0.143f, y + 0.09f); //R

        glEnd();


        //Roof Top
        glColor3f(41.0f/255.0f, 65.0f/255.0f, 14.0f/255.0f);
        glBegin(GL_POLYGON);

        glVertex2f(x + 0.248f, y + 0.187f); //T
        glVertex2f(x + 0.352f, y + 0.075f); //U
        glVertex2f(x + 0.369f, y + 0.090f); //V
        glVertex2f(x + 0.248f, y + 0.218f); //W
        glVertex2f(x + 0.122f, y + 0.090f); //Z
        glVertex2f(x + 0.137f, y + 0.075f); //S

        glEnd();

        //Window Color
        glColor3f(62.0f/255.0f, 61.0f/255.0f, 7.0f/255.0f);

        //Left Window
        glBegin(GL_POLYGON);

        glVertex2f(x + 0.184f, y + 0.092f); //A1
        glVertex2f(x + 0.232f, y + 0.092f); //B1
        glVertex2f(x + 0.232f, y + 0.042f); //C1
        glVertex2f(x + 0.184f, y + 0.042f); //D1

        glEnd();

        //Right Window
        glBegin(GL_POLYGON);

        glVertex2f(x + 0.259f, y + 0.092f); //E1
        glVertex2f(x + 0.304f, y + 0.092f); //F1
        glVertex2f(x + 0.304f, y + 0.041f); //G1
        glVertex2f(x + 0.259f, y + 0.041f); //H1

        glEnd();

    }

    void drawHouse3(float x, float y)
    {
        //Front
        glColor3f(83.0f/255.0f, 78.0f/255.0f, 12.0f/255.0f);
        glBegin(GL_POLYGON);

        glVertex2f(x + 0.034f, y + 0.163f); //S1
        glVertex2f(x + 0.034f, y + 0.020f); //T1
        glVertex2f(x + 0.199f, y + 0.020f); //U1
        glVertex2f(x + 0.199f, y + 0.161f); //V1
        glVertex2f(x + 0.113f, y + 0.244f); //W1

        glEnd();


        //Roof Top
        glColor3f(41.0f/255.0f, 65.0f/255.0f, 14.0f/255.0f);
        glBegin(GL_POLYGON);

        glVertex2f(x + 0.111f, y + 0.228f); //M1
        glVertex2f(x + 0.191f, y + 0.152f); //L1
        glVertex2f(x + 0.203f, y + 0.166f); //K1
        glVertex2f(x + 0.111f, y + 0.257f); //J1
        glVertex2f(x + 0.021f, y + 0.166f); //I1
        glVertex2f(x + 0.033f, y + 0.151f); //N1

        glEnd();


        //Window
        glColor3f(54.0f/255.0f, 71.0f/255.0f, 19.0f/255.0f);
        glBegin(GL_POLYGON);

        glVertex2f(x + 0.092f, y + 0.168f); //O1
        glVertex2f(x + 0.129f, y + 0.168f); //P1
        glVertex2f(x + 0.129f, y + 0.122f); //Q1
        glVertex2f(x + 0.092f, y + 0.122f); //R1

        glEnd();

    }

    void drawHouse4(float x, float y)
    {
        //Front
        glColor3f(112.0f/255.0f, 84.0f/255.0f, 10.0f/255.0f);
        glBegin(GL_POLYGON);

        glVertex2f(x + 0.072f, y + 0.083f); //F2
        glVertex2f(x + 0.072f, y + 0.002f); //G2
        glVertex2f(x + -0.061f, y + 0.002f); //H2
        glVertex2f(x + -0.061f, y + 0.083f); //I2
        glVertex2f(x + -0.0009f, y + 0.185f); //J2

        glEnd();


        //Roof Top
        glColor3f(51.0f/255.0f, 62.0f/255.0f, 10.0f/255.0f);
        glBegin(GL_POLYGON);

        glVertex2f(x + -0.001f, y + 0.172f); //Z1
        glVertex2f(x + 0.077f, y + 0.068f); //A2
        glVertex2f(x + 0.102f, y + 0.068f); //B2
        glVertex2f(x + -0.001f, y + 0.206f); //C2
        glVertex2f(x + -0.093f, y + 0.070f); //D2
        glVertex2f(x + -0.066f, y + 0.071f); //E2

        glEnd();


        //Window
        glColor3f(69.0f/255.0f, 66.0f/255.0f, 7.0f/255.0f);
        glBegin(GL_POLYGON);

        glVertex2f(x + -0.019f, y + 0.090f); //K2
        glVertex2f(x + 0.024f, y + 0.090f); //L2
        glVertex2f(x + 0.024f, y + 0.046f); //M2
        glVertex2f(x + -0.019f, y + 0.046f); //N2

        glEnd();

    }

    void drawHouse5(float x, float y)
    {
        //Front
        glColor3f(153.0f/255.0f, 98.0f/255.0f, 8.0f/255.0f);
        glBegin(GL_POLYGON);

        glVertex2f(x + -0.202f, y + 0.116f); //U2
        glVertex2f(x + -0.120f, y + 0.216f); //V2
        glVertex2f(x + -0.029f, y + 0.116f); //W2
        glVertex2f(x + -0.029f, y + 0.006f); //Z2
        glVertex2f(x + -0.202f, y + 0.006f); //A3

        glEnd();


        //Roof Top
        glColor3f(108.0f/255.0f, 83.0f/255.0f, 4.0f/255.0f);
        glBegin(GL_POLYGON);

        glVertex2f(x + -0.120f, y + 0.203f); //O2
        glVertex2f(x + -0.050f, y + 0.122f); //P2
        glVertex2f(x + -0.038f, y + 0.139f); //Q2
        glVertex2f(x + -0.120f, y + 0.236f); //R2
        glVertex2f(x + -0.234f, y + 0.095f); //S2
        glVertex2f(x + -0.208f, y + 0.095f); //T2

        glEnd();


        //Window
        glColor3f(84.0f/255.0f, 72.0f/255.0f, 8.0f/255.0f);
        glBegin(GL_POLYGON);

        glVertex2f(x + -0.161f, y + 0.026f); //B3
        glVertex2f(x + -0.089f, y + 0.026f); //C3
        glVertex2f(x + -0.089f, y + 0.079f); //D3
        glVertex2f(x + -0.161f, y + 0.079f); //E3

        glEnd();

        drawHalfCircle(-0.125f, 0.079f, 0.036f, 100, 84.0f/255.0f, 72.0f/255.0f, 8.0f/255.0f);

    }

    //All Buildings
    void drawBuildings()
    {
        //
        glPushMatrix();
        glScalef(0.75f, 0.75f, 0.75f);
        glTranslatef(-0.3f, 0.0f, 0.0f);

            drawBuilding1(-0.6f, -0.04f, 176.0f/255.0f, 144.0f/255.0f, 23.0f/255.0f);

        glPopMatrix();

        //
        glPushMatrix();
        glScalef(0.65f, 0.65f, 0.65f);
        glTranslatef(0.38f, 0.04f, 0.0f);

            drawBuilding2(0.36f, -0.04f, 76.0f/255.0f, 106.0f/255.0f, 58.0f/255.0f);

        glPopMatrix();

        //Shrubs
        glPushMatrix();
        glTranslatef(1.1f, 0.03f, 0.0f);
            drawShrub5();
        glPopMatrix();

        //
        glPushMatrix();
        glScalef(0.75f, 0.75f, 0.75f);

        glPushMatrix();
        glTranslatef(0.34f, 0.0f, 0.0f);

            drawHouse1(0.0f, -0.03f);

        glPopMatrix();

        //
        glPushMatrix();
        glTranslatef(0.2f, -0.04f, 0.0f);

            drawHouse3(0.0f, 0.0f);
            drawHouse2(0.0f, 0.0f);
            drawHouse5(0.0f, 0.0f);
            drawHouse4(0.0f, 0.0f);

        glPopMatrix();


        //
        glPushMatrix();
        glScalef(0.65f, 0.65f, 0.65f);
        glTranslatef(-0.6f, 0.0f, 0.0f);

            drawHouse3(0.0f, 0.0f);
            drawHouse2(0.0f, 0.0f);
            drawHouse5(0.0f, 0.0f);
            drawHouse4(0.0f, 0.0f);

        glPopMatrix();

        glPopMatrix();

    }

    //Trees
    void drawTree1()
    {
        glColor3f(78.0f/255.0f, 73.0f/255.0f, 4.0f/255.0f);
        glBegin(GL_POLYGON);
        glVertex2f(-0.892, 0.002);
        glVertex2f(-0.868, 0.002);
        glVertex2f(-0.868, 0.075);
        glVertex2f(-0.892, 0.075);
        glEnd();

        //Tree Leafs
        glColor3f(36.0f/255.0f, 85.0f/255.0f, 19.0f/255.0f);
        glBegin(GL_TRIANGLES);
        glVertex2f(-0.880,0.188);
        glVertex2f(-0.940, 0.116);
        glVertex2f(-0.821, 0.116);

        glVertex2f(-0.880,0.161);
        glVertex2f(-0.940,0.075);
        glVertex2f(-0.821,0.075);

        glVertex2f(-0.880,0.129);
        glVertex2f(-0.940,0.039);
        glVertex2f(-0.821,0.039);
        glEnd();

    }

    void drawTree2()
    {
        //Tree Shadow
        glPushMatrix();
        glScalef(1.0f, 0.3f, 1.0f);
        glTranslatef(0.0f, -0.8f, 0.0f);

        drawCircle(-0.881f, -0.342f, 0.075f, 100, 73.0f/255.0f, 109.0f/255.0f, 11.0f/255.0f);

        glPopMatrix();

        // Tree Leafs
        glColor3f(38.0f/255.0f, 88.0f/255.0f, 15.0f/255.0f);

        drawCircle(-0.932f, -0.178f, 0.047f, 100, 38.0f/255.0f, 88.0f/255.0f, 15.0f/255.0f);
        drawCircle(-0.890f, -0.214f, 0.067f, 100, 38.0f/255.0f, 88.0f/255.0f, 15.0f/255.0f);
        drawCircle(-0.843f, -0.208f, 0.053f, 100, 38.0f/255.0f, 88.0f/255.0f, 15.0f/255.0f);
        drawCircle(-0.880f, -0.140f, 0.051f, 100, 38.0f/255.0f, 88.0f/255.0f, 15.0f/255.0f);


        glColor3f(79.0f/255.0f, 71.0f/255.0f, 6.0f/255.0f);
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

    void drawFlowerLeafs()
    {
        glColor3f(40.0f/255.0f, 84.0f/255.0f, 0.10f/255.0f);

        glBegin(GL_POLYGON);
        glVertex2f(0.531f,-0.348f); //O
        glVertex2f(0.521f,-0.425f); //P
        glVertex2f(0.531f,-0.425f); //Q
        glVertex2f(0.534f,-0.331f); //R
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(0.499f,-0.425f); //I1
        glVertex2f(0.493f,-0.419f); //J1
        glVertex2f(0.488f,-0.415f); //K1
        glVertex2f(0.483f,-0.408f); //L1
        glVertex2f(0.479f,-0.402f); //M1
        glVertex2f(0.476f,-0.394f); //N1
        glVertex2f(0.476f,-0.388f); //Z1
        glVertex2f(0.475f,-0.382f); //A2
        glVertex2f(0.476f,-0.374f); //B2
        glVertex2f(0.483f,-0.380f); //C2
        glVertex2f(0.487f,-0.385f); //D2
        glVertex2f(0.491f,-0.390f); //E2
        glVertex2f(0.494f,-0.395f); //F2
        glVertex2f(0.496f,-0.400f); //G2
        glVertex2f(0.499f,-0.406f); //H2
        glVertex2f(0.501f,-0.410f); //I2
        glVertex2f(0.505f,-0.415f); //J2
        glVertex2f(0.521f,-0.425f); //P
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(0.506f,-0.388f); //A4
        glVertex2f(0.502f,-0.402f); //K2
        glVertex2f(0.501f,-0.396f); //L2
        glVertex2f(0.499f,-0.390f); //M2
        glVertex2f(0.497f,-0.386f); //N2
        glVertex2f(0.496f,-0.381f); //O2
        glVertex2f(0.494f,-0.377f); //P2
        glVertex2f(0.492f,-0.373f); //Q2
        glVertex2f(0.489f,-0.366f); //S2
        glVertex2f(0.486f,-0.361f); //T2
        glVertex2f(0.483f,-0.355f); //U2
        glVertex2f(0.491f,-0.358f); //V2
        glVertex2f(0.498f,-0.362f); //W2
        glVertex2f(0.503f,-0.367f); //Z2
        glVertex2f(0.506f,-0.372f); //A3
        glVertex2f(0.509f,-0.377f); //B3
        glVertex2f(0.511f,-0.381f); //C3
        glVertex2f(0.513f,-0.386f); //D3
        glVertex2f(0.516f,-0.391f); //E3
        glVertex2f(0.518f,-0.395f); //F3
        glVertex2f(0.520f,-0.400f); //G3
        glVertex2f(0.523f,-0.407f); //H3
        glVertex2f(0.521f,-0.425f); //P
        glVertex2f(0.505f,-0.415f); //J2
        glVertex2f(0.501f,-0.410f); //I2
        glVertex2f(0.502f,-0.402f); //K2
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(0.564f,-0.376f); //B4
        glVertex2f(0.581f,-0.368f); //J3
        glVertex2f(0.567f,-0.367f); //K3
        glVertex2f(0.565f,-0.368f); //L3
        glVertex2f(0.563f,-0.368f); //M3
        glVertex2f(0.560f,-0.370f); //N3
        glVertex2f(0.557f,-0.371f); //O3
        glVertex2f(0.554f,-0.374f); //P3
        glVertex2f(0.551f,-0.376f); //Q3
        glVertex2f(0.548f,-0.380f); //R3
        glVertex2f(0.544f,-0.385f); //S3
        glVertex2f(0.540f,-0.390f); //T3
        glVertex2f(0.537f,-0.393f); //U3
        glVertex2f(0.536f,-0.397f); //V3
        glVertex2f(0.535f,-0.400f); //W3
        glVertex2f(0.532f,-0.405f); //Z3
        glVertex2f(0.531f,-0.425f); //Q
        glVertex2f(0.544f,-0.425f); //S
        glVertex2f(0.547f,-0.422f); //T
        glVertex2f(0.551f,-0.418f); //U
        glVertex2f(0.554f,-0.415f); //V
        glVertex2f(0.556f,-0.412f); //W
        glVertex2f(0.559f,-0.407f); //Z
        glVertex2f(0.561f,-0.401f); //A1
        glVertex2f(0.563f,-0.396f); //B1
        glVertex2f(0.565f,-0.389f); //C1
        glVertex2f(0.568f,-0.383f); //D1
        glVertex2f(0.571f,-0.378f); //E1
        glVertex2f(0.574f,-0.374f); //F1
        glVertex2f(0.578f,-0.370f); //I3
        glVertex2f(0.581f,-0.368f); //J3
        glEnd();
    }

    void drawFlower(float cx, float cy, float centerRedius, float petalLength, int petalCount)
    {
        drawFlowerLeafs();

        //Flower
        for (int i = 0; i < petalCount; i++)
        {
            float angle = 2 * PI * i / petalCount;

            float x = cx + petalLength * cos(angle);
            float y = cy + petalLength * sin(angle);

            drawCircle(x, y, petalLength, 100, 230.0f/255.0f, 172.0f/255.0f, 12.0f/255.0f);
        }

        drawCircle(cx, cy, centerRedius, 100, 133.0f/255.0f, 104.0f/255.0f, 0.0f/255.0f);

    }

    void drawTree()
    {
        drawTree1();

        glPushMatrix();
        glScalef(0.65f, 0.65f, 0.65f);
        glTranslatef(1.1f, 0.35f, 0.0f);
        drawTree2();
        glPopMatrix();


        glPushMatrix();
        glScalef(0.68f, 0.68f, 0.68f);
        glTranslatef(0.8f, 0.0f, 0.0f);
        drawTree1();
        glPopMatrix();


        glPushMatrix();
        glScalef(0.9f, 0.9f, 0.9f);
        glTranslatef(-0.09f, 0.02f, 0.0f);
        drawTree2();
        glPopMatrix();
    }

    void drawShrubs()
    {
        drawShrub1();
        drawShrub4();

        glPushMatrix();
        glTranslatef(0.15f, 0.0f, 0.0f);
            drawShrub5();
        glPopMatrix();


        glPushMatrix();
        glScalef(0.65f, 0.65f, 0.65f);
        glTranslatef(0.005f, 0.02f, 0.0f);
            drawShrub5();
        glPopMatrix();


        glPushMatrix();
        glScalef(0.65f, 0.65f, 0.65f);
        glTranslatef(0.005f, 0.02f, 0.0f);
            drawShrub6();
            drawShrub7();
        glPopMatrix();


        glPushMatrix();
        glScalef(0.6f, 0.6f, 0.6f);
        glTranslatef(0.57f, 0.02f, 0.0f);
            drawShrub5();
        glPopMatrix();


        glPushMatrix();
        glScalef(0.6f, 0.6f, 0.6f);
        glTranslatef(-0.5f, 0.022f, 0.0f);
            drawShrub8();
        glPopMatrix();


        glPushMatrix();
        glTranslatef(0.51f, -0.005f, 0.0f);
            drawShrub6();
            drawShrub7();
        glPopMatrix();


        glPushMatrix();
        glTranslatef(1.3f, -0.002f, 0.0f);
            drawShrub4();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.28f, 0.022f, 0.0f);
            drawShrub8();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(1.1f, -0.005f, 0.0f);
            drawShrub6();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.725f, 0.007f, 0.0f);
            drawShrub8();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(1.5f, -0.018f, 0.0f);
            drawShrub5();
        glPopMatrix();



    }

    //Ground Left Side Corner
    void drawGroundCorner()
    {
        glColor3f(56.0f/255.0f, 70.0f/255.0f, 11.0f/255.0f);
        glBegin(GL_POLYGON);

        glVertex2f(-0.863f, -0.484f); //P1
        glVertex2f(-1.000f, -0.562f); //D
        glVertex2f(-0.525f, -0.562f); //O
        glVertex2f(-0.499f, -0.541f); //P
        glVertex2f(-0.556f, -0.526f); //Q
        glVertex2f(-0.570f, -0.520f); //R
        glVertex2f(-0.586f, -0.512f); //S
        glVertex2f(-0.595f, -0.505f); //T
        glVertex2f(-0.561f, -0.490f); //U
        glVertex2f(-0.554f, -0.490f); //V
        glVertex2f(-0.546f, -0.488f); //W
        glVertex2f(-0.518f, -0.474f); //Z
        glVertex2f(-0.527f, -0.462f); //A1
        glVertex2f(-0.669f, -0.458f); //B1
        glVertex2f(-0.719f, -0.432f); //C1
        glVertex2f(-0.726f, -0.404f); //D1
        glVertex2f(-0.752f, -0.396f); //E1
        glVertex2f(-0.759f, -0.391f); //F1
        glVertex2f(-0.764f, -0.387f); //G1
        glVertex2f(-0.776f, -0.376f); //H1
        glVertex2f(-0.810f, -0.377f); //I1
        glVertex2f(-0.817f, -0.376f); //J1
        glVertex2f(-0.823f, -0.375f); //K1
        glVertex2f(-0.830f, -0.371f); //L1
        glVertex2f(-0.837f, -0.366f); //M1
        glVertex2f(-0.883f, -0.317f); //N1
        glVertex2f(-0.920f, -0.340f); //O1
        glVertex2f(-1.000f, -0.287f); //M
        glVertex2f(-1.000f, -0.562f); //D

        glEnd();


        //Particles
        glColor3f(85.0f/255.0f, 85.0f/255.0f, 13.0f/255.0f);
        glBegin(GL_POLYGON);

        glVertex2f(-0.978f, -0.402f); //P1
        glVertex2f(-0.949f, -0.374f); //Q1
        glVertex2f(-0.943f, -0.371f); //R1
        glVertex2f(-0.937f, -0.368f); //S1
        glVertex2f(-0.932f, -0.369f); //T1
        glVertex2f(-0.930f, -0.373f); //U1
        glVertex2f(-0.908f, -0.395f); //V1
        glVertex2f(-0.906f, -0.397f); //W1
        glVertex2f(-0.907f, -0.399f); //Z1
        glVertex2f(-0.910f, -0.403f); //A2
        glVertex2f(-0.914f, -0.405f); //B2
        glVertex2f(-0.919f, -0.408f); //C2
        glVertex2f(-0.926f, -0.410f); //D2
        glVertex2f(-0.933f, -0.412f); //E2
        glVertex2f(-0.945f, -0.412f); //F2
        glVertex2f(-0.954f, -0.410f); //G2
        glVertex2f(-0.963f, -0.409f); //H2
        glVertex2f(-0.973f, -0.405f); //I2

        glEnd();


        //
        glColor3f(85.0f/255.0f, 85.0f/255.0f, 13.0f/255.0f);
        glBegin(GL_POLYGON);

        glVertex2f(-0.879f, -0.392f); //J2
        glVertex2f(-0.879f, -0.384f); //K2
        glVertex2f(-0.875f, -0.380f); //L2
        glVertex2f(-0.869f, -0.377f); //M2
        glVertex2f(-0.861f, -0.377f); //N2
        glVertex2f(-0.852f, -0.377f); //O2
        glVertex2f(-0.846f, -0.379f); //P2
        glVertex2f(-0.839f, -0.384f); //Q2
        glVertex2f(-0.831f, -0.388f); //R2
        glVertex2f(-0.823f, -0.397f); //S2
        glVertex2f(-0.815f, -0.406f); //T2
        glVertex2f(-0.814f, -0.413f); //U2
        glVertex2f(-0.815f, -0.421f); //V2
        glVertex2f(-0.816f, -0.425f); //W2
        glVertex2f(-0.824f, -0.426f); //Z2
        glVertex2f(-0.834f, -0.424f); //A3
        glVertex2f(-0.846f, -0.420f); //B3
        glVertex2f(-0.855f, -0.417f); //C3
        glVertex2f(-0.864f, -0.414f); //D3
        glVertex2f(-0.872f, -0.410f); //E3
        glVertex2f(-0.875f, -0.401f); //F3
        glVertex2f(-0.877f, -0.396f); //G3

        glEnd();


        //
        glColor3f(85.0f/255.0f, 85.0f/255.0f, 13.0f/255.0f);
        glBegin(GL_POLYGON);

        glVertex2f(-0.738f, -0.441f); //H3
        glVertex2f(-0.717f, -0.462f); //I3
        glVertex2f(-0.715f, -0.466f); //J3
        glVertex2f(-0.715f, -0.470f); //K3
        glVertex2f(-0.715f, -0.481f); //L3
        glVertex2f(-0.716f, -0.485f); //M3
        glVertex2f(-0.721f, -0.487f); //N3
        glVertex2f(-0.733f, -0.490f); //O3
        glVertex2f(-0.760f, -0.490f); //P3
        glVertex2f(-0.778f, -0.487f); //Q3
        glVertex2f(-0.782f, -0.486f); //R3
        glVertex2f(-0.786f, -0.485f); //S3
        glVertex2f(-0.791f, -0.485f); //T3
        glVertex2f(-0.797f, -0.485f); //U3
        glVertex2f(-0.815f, -0.481f); //V3
        glVertex2f(-0.817f, -0.478f); //W3
        glVertex2f(-0.816f, -0.472f); //Z3
        glVertex2f(-0.810f, -0.467f); //B4
        glVertex2f(-0.804f, -0.463f); //C4
        glVertex2f(-0.801f, -0.454f); //D4
        glVertex2f(-0.782f, -0.441f); //E4
        glVertex2f(-0.788f, -0.437f); //F4
        glVertex2f(-0.783f, -0.434f); //G4
        glVertex2f(-0.779f, -0.433f); //H4
        glVertex2f(-0.769f, -0.432f); //I4
        glVertex2f(-0.750f, -0.432f); //J4
        glVertex2f(-0.745f, -0.433f); //K4
        glVertex2f(-0.743f, -0.435f); //L4

        glEnd();


        //
        glColor3f(85.0f/255.0f, 85.0f/255.0f, 13.0f/255.0f);
        glBegin(GL_POLYGON);

        glVertex2f(-0.657f, -0.501f); //M4
        glVertex2f(-0.633f, -0.521f); //N4
        glVertex2f(-0.633f, -0.526f); //O4
        glVertex2f(-0.636f, -0.529f); //P4
        glVertex2f(-0.640f, -0.530f); //Q4
        glVertex2f(-0.643f, -0.531f); //R4
        glVertex2f(-0.678f, -0.532f); //S4
        glVertex2f(-0.682f, -0.530f); //T4
        glVertex2f(-0.685f, -0.526f); //U4
        glVertex2f(-0.686f, -0.522f); //V4
        glVertex2f(-0.687f, -0.518f); //W4
        glVertex2f(-0.685f, -0.512f); //Z4
        glVertex2f(-0.670f, -0.500f); //A5
        glVertex2f(-0.664f, -0.499f); //B5
        glVertex2f(-0.660f, -0.500f); //C5

        glEnd();


        //
        glColor3f(85.0f/255.0f, 85.0f/255.0f, 13.0f/255.0f);
        glBegin(GL_POLYGON);
        glVertex2f(-0.840f, -0.520f); //D5
        glVertex2f(-0.826f, -0.509f); //E5
        glVertex2f(-0.821f, -0.509f); //F5
        glVertex2f(-0.817f, -0.511f); //G5
        glVertex2f(-0.789f, -0.528f); //H5
        glVertex2f(-0.789f, -0.532f); //I5
        glVertex2f(-0.793f, -0.540f); //J5
        glVertex2f(-0.800f, -0.540f); //K5
        glVertex2f(-0.827f, -0.541f); //L5
        glVertex2f(-0.833f, -0.539f); //M5
        glVertex2f(-0.837f, -0.534f); //N5

        glEnd();


        //
        glColor3f(85.0f/255.0f, 85.0f/255.0f, 13.0f/255.0f);
        glBegin(GL_POLYGON);

        glVertex2f(-0.894f, -0.485f); //O5
        glVertex2f(-0.889f, -0.474f); //P5
        glVertex2f(-0.881f, -0.469f); //Q5
        glVertex2f(-0.872f, -0.468f); //R5
        glVertex2f(-0.854f, -0.483f); //S5
        glVertex2f(-0.854f, -0.490f); //T5
        glVertex2f(-0.895f, -0.491f); //U5

        glEnd();


        //
        glColor3f(85.0f/255.0f, 85.0f/255.0f, 13.0f/255.0f);
        glBegin(GL_POLYGON);

        glVertex2f(-0.978f, -0.492f); //V5
        glVertex2f(-0.957f, -0.476f); //W5
        glVertex2f(-0.947f, -0.476f); //Z5
        glVertex2f(-0.923f, -0.492f); //A6
        glVertex2f(-0.912f, -0.502f); //B6
        glVertex2f(-0.911f, -0.507f); //C6
        glVertex2f(-0.915f, -0.512f); //D6
        glVertex2f(-0.940f, -0.520f); //E6
        glVertex2f(-0.978f, -0.506f); //F6
        glVertex2f(-0.983f, -0.501f); //G6
        glVertex2f(-0.983f, -0.494f); //H6

        glEnd();
    }

    //Road Fractures
    void drawCrackedRoad()
    {
        //Side Road
        glColor3f(46.0f/255.0f, 75.0f/255.0f, 32.0f/255.0f);
        glBegin(GL_POLYGON);
        glVertex2f(-0.309f, -0.562f); //P
        glVertex2f(-0.261f, -0.562f); //Q
        glVertex2f(-0.221f, -0.510f); //R
        glVertex2f(-0.243f, -0.493f); //S
        glEnd();


        glBegin(GL_POLYGON);
        glVertex2f(-0.221f, -0.510f); //R
        glVertex2f(-0.205f, -0.507f); //T
        glVertex2f(-0.150f, -0.450f); //U
        glVertex2f(-0.183f, -0.456f); //V
        glVertex2f(-0.216f, -0.486f); //W
        glVertex2f(-0.243f, -0.493f); //S
        glEnd();


        glBegin(GL_POLYGON);
        glVertex2f(-0.200f, -0.450f); //Z
        glVertex2f(-0.167f, -0.403f); //A1
        glVertex2f(-0.150f, -0.400f); //B1
        glVertex2f(-0.106f, -0.362f); //C1
        glVertex2f(-0.105f, -0.368f); //D1
        glVertex2f(-0.130f, -0.396f); //E1
        glVertex2f(-0.169f, -0.441f); //F1
        glVertex2f(-0.150f, -0.450f); //U
        glVertex2f(-0.183f, -0.456f); //V
        glEnd();


        glBegin(GL_POLYGON);
        glVertex2f(-0.214f, -0.562f); //G1
        glVertex2f(-0.175f, -0.562f); //H1
        glVertex2f(-0.157f, -0.519f); //I1
        glVertex2f(-0.165f, -0.501f); //J1
        glEnd();


        glBegin(GL_POLYGON);
        glVertex2f(-0.157f, -0.519f); //I1
        glVertex2f(-0.165f, -0.501f); //J1
        glVertex2f(-0.147f, -0.494f); //L1
        glVertex2f(-0.128f, -0.501f); //K1
        glEnd();


        glBegin(GL_POLYGON);
        glVertex2f(-0.147f, -0.494f); //L1
        glVertex2f(-0.128f, -0.501f); //K1
        glVertex2f(-0.115f, -0.471f); //M1
        glVertex2f(-0.122f, -0.459f); //N1
        glEnd();


        glBegin(GL_POLYGON);
        glVertex2f(-0.115f, -0.471f); //M1
        glVertex2f(-0.122f, -0.459f); //N1
        glVertex2f(-0.081f, -0.436f); //P1
        glVertex2f(-0.060f, -0.434f); //O1
        glEnd();


        glBegin(GL_POLYGON);
        glVertex2f(-0.081f, -0.436f); //P1
        glVertex2f(-0.060f, -0.434f); //O1
        glVertex2f(-0.065f, -0.415f); //Q1
        glVertex2f(-0.085f, -0.415f); //R1
        glEnd();


        glBegin(GL_POLYGON);
        glVertex2f(-0.065f, -0.415f); //Q1
        glVertex2f(-0.085f, -0.415f); //R1
        glVertex2f(-0.060f, -0.380f); //T1
        glVertex2f(-0.056f, -0.397f); //S1
        glEnd();


        glBegin(GL_POLYGON);
        glVertex2f(-0.060f, -0.380f); //T1
        glVertex2f(-0.056f, -0.397f); //S1
        glVertex2f(0.0f, -0.380f); //U1
        glVertex2f(-0.011f, -0.371f); //V1
        glEnd();


        //Main Road
        glColor3f(17.0f/255.0f, 51.0f/255.0f, 17.0f/255.0f);

        //Left Fracture
        glBegin(GL_POLYGON);
        glVertex2f(-0.656f, -0.106f); //R
        glVertex2f(-0.627f, -0.126f); //S
        glVertex2f(-0.633f, -0.127f); //T
        glVertex2f(-0.656f, -0.114f); //U
        glVertex2f(-0.692f, -0.111f); //P
        glVertex2f(-0.687f, -0.106f); //Q
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.604f, -0.111f); //V
        glVertex2f(-0.555f, -0.110f); //W
        glVertex2f(-0.550f, -0.114f); //Z
        glVertex2f(-0.553f, -0.117f); //A1
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.550f, -0.114f); //Z
        glVertex2f(-0.555f, -0.110f); //W
        glVertex2f(-0.527f, -0.090f); //B1
        glVertex2f(-0.525f, -0.096f); //C1
        glVertex2f(-0.534f, -0.110f); //D1
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.485f, -0.094f); //E1
        glVertex2f(-0.527f, -0.090f); //B1
        glVertex2f(-0.525f, -0.096f); //C1
        glVertex2f(-0.495f, -0.099f); //G1
        glVertex2f(-0.487f, -0.101f); //F1
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.485f, -0.094f); //E1
        glVertex2f(-0.487f, -0.101f); //F1
        glVertex2f(-0.476f, -0.112f); //I1
        glVertex2f(-0.467f, -0.105f); //H1
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.476f, -0.112f); //I1
        glVertex2f(-0.467f, -0.105f); //H1
        glVertex2f(-0.414f, -0.106f); //J1
        glVertex2f(-0.418f, -0.113f); //K1
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.414f, -0.106f); //J1
        glVertex2f(-0.418f, -0.113f); //K1
        glVertex2f(-0.414f, -0.124f); //M1
        glVertex2f(-0.407f, -0.115f); //L1
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.414f, -0.124f); //M1
        glVertex2f(-0.407f, -0.115f); //L1
        glVertex2f(-0.394f, -0.107f); //N1
        glVertex2f(-0.382f, -0.124f); //O1
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.394f, -0.107f); //N1
        glVertex2f(-0.382f, -0.124f); //O1
        glVertex2f(-0.372f, -0.127f); //P1
        glVertex2f(-0.365f, -0.118f); //Q1
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.352f, -0.125f); //U1
        glVertex2f(-0.362f, -0.114f); //V1
        glVertex2f(-0.365f, -0.118f); //Q1
        glVertex2f(-0.372f, -0.127f); //P1
        glVertex2f(-0.375f, -0.133f); //R1
        glVertex2f(-0.304f, -0.135f); //S1
        glVertex2f(-0.303f, -0.125f); //T1
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.304f, -0.135f); //S1
        glVertex2f(-0.303f, -0.125f); //T1
        glVertex2f(-0.286f, -0.107f); //W1
        glVertex2f(-0.278f, -0.109f); //Z1
        glVertex2f(-0.285f, -0.140f); //A2
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.264f, -0.102f); //B2
        glVertex2f(-0.286f, -0.107f); //W1
        glVertex2f(-0.278f, -0.109f); //Z1
        glVertex2f(-0.244f, -0.109f); //D2
        glVertex2f(-0.245f, -0.107f); //C2
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.244f, -0.109f); //D2
        glVertex2f(-0.245f, -0.107f); //C2
        glVertex2f(-0.220f, -0.110f); //E2
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.285f, -0.140f); //A2
        glVertex2f(-0.275f, -0.150f); //F2
        glVertex2f(-0.247f, -0.137f); //G2
        glVertex2f(-0.260f, -0.129f); //H2
        glVertex2f(-0.283f, -0.129f); //I2
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.275,-0.150); //F2
        glVertex2f(-0.247,-0.137); //G2
        glVertex2f(-0.193,-0.137); //J2
        glVertex2f(-0.187,-0.140); //K2
        glVertex2f(-0.185,-0.151); //L2
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.185,-0.151); //L2
        glVertex2f(-0.134,-0.152); //M2
        glVertex2f(-0.186,-0.145); //N2
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.193,-0.137); //J2
        glVertex2f(-0.187,-0.140); //K2
        glVertex2f(-0.168,-0.131); //O2
        glVertex2f(-0.169,-0.125); //P2
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.168,-0.131); //O2
        glVertex2f(-0.169,-0.125); //P2
        glVertex2f(-0.136,-0.131); //Q2
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.651,-0.176); //R2
        glVertex2f(-0.698,-0.216); //S2
        glVertex2f(-0.693,-0.231); //T2
        glVertex2f(-0.624,-0.177); //U2
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.754,-0.233); //V2
        glVertex2f(-0.698,-0.216); //S2
        glVertex2f(-0.693,-0.231); //T2
        glVertex2f(-0.730,-0.238); //Z2
        glVertex2f(-0.744,-0.249); //W2
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.744,-0.249); //W2
        glVertex2f(-0.766,-0.268); //A3
        glVertex2f(-0.708,-0.268); //B3
        glVertex2f(-0.730,-0.238); //Z2
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.517,-0.167); //C3
        glVertex2f(-0.494,-0.163); //D3
        glVertex2f(-0.490,-0.170); //E3
        glVertex2f(-0.496,-0.176); //F3
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.496,-0.176); //F3
        glVertex2f(-0.490,-0.170); //E3
        glVertex2f(-0.474,-0.168); //G3
        glVertex2f(-0.468,-0.177); //H3
        glVertex2f(-0.476,-0.182); //I3
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.468,-0.177); //H3
        glVertex2f(-0.476,-0.182); //I3
        glVertex2f(-0.366,-0.186); //K3
        glVertex2f(-0.379,-0.182); //J3
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.379,-0.186); //L3
        glVertex2f(-0.380,-0.195); //M3
        glVertex2f(-0.392,-0.216); //N3
        glVertex2f(-0.419,-0.184); //O3
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.380,-0.195); //M3
        glVertex2f(-0.392,-0.216); //N3
        glVertex2f(-0.380,-0.212); //Q3
        glVertex2f(-0.368,-0.200); //P3
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.392,-0.216); //N3
        glVertex2f(-0.429,-0.219); //R3
        glVertex2f(-0.414,-0.223); //S3
        glVertex2f(-0.332,-0.228); //T3
        glVertex2f(-0.337,-0.221); //U3
        glVertex2f(-0.380,-0.212); //Q3
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.429,-0.219); //R3
        glVertex2f(-0.414,-0.223); //S3
        glVertex2f(-0.393,-0.246); //W3
        glVertex2f(-0.459,-0.248); //V3
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.332,-0.228); //T3
        glVertex2f(-0.337,-0.221); //U3
        glVertex2f(-0.322,-0.210); //Z3
        glVertex2f(-0.302,-0.211); //A4
        glVertex2f(-0.277,-0.234); //B4
        glVertex2f(-0.319,-0.236); //C4
        glEnd();






        //Right Fracture
        glPushMatrix();
        glTranslatef(0.5f, 0.0f, 0.0f);


        glBegin(GL_POLYGON);
        glVertex2f(-0.656f, -0.106f); //R
        glVertex2f(-0.627f, -0.126f); //S
        glVertex2f(-0.633f, -0.127f); //T
        glVertex2f(-0.656f, -0.114f); //U
        glVertex2f(-0.692f, -0.111f); //P
        glVertex2f(-0.687f, -0.106f); //Q
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.604f, -0.111f); //V
        glVertex2f(-0.555f, -0.110f); //W
        glVertex2f(-0.550f, -0.114f); //Z
        glVertex2f(-0.553f, -0.117f); //A1
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.550f, -0.114f); //Z
        glVertex2f(-0.555f, -0.110f); //W
        glVertex2f(-0.527f, -0.090f); //B1
        glVertex2f(-0.525f, -0.096f); //C1
        glVertex2f(-0.534f, -0.110f); //D1
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.485f, -0.094f); //E1
        glVertex2f(-0.527f, -0.090f); //B1
        glVertex2f(-0.525f, -0.096f); //C1
        glVertex2f(-0.495f, -0.099f); //G1
        glVertex2f(-0.487f, -0.101f); //F1
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.485f, -0.094f); //E1
        glVertex2f(-0.487f, -0.101f); //F1
        glVertex2f(-0.476f, -0.112f); //I1
        glVertex2f(-0.467f, -0.105f); //H1
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.476f, -0.112f); //I1
        glVertex2f(-0.467f, -0.105f); //H1
        glVertex2f(-0.414f, -0.106f); //J1
        glVertex2f(-0.418f, -0.113f); //K1
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.414f, -0.106f); //J1
        glVertex2f(-0.418f, -0.113f); //K1
        glVertex2f(-0.414f, -0.124f); //M1
        glVertex2f(-0.407f, -0.115f); //L1
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.414f, -0.124f); //M1
        glVertex2f(-0.407f, -0.115f); //L1
        glVertex2f(-0.394f, -0.107f); //N1
        glVertex2f(-0.382f, -0.124f); //O1
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.394f, -0.107f); //N1
        glVertex2f(-0.382f, -0.124f); //O1
        glVertex2f(-0.372f, -0.127f); //P1
        glVertex2f(-0.365f, -0.118f); //Q1
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.352f, -0.125f); //U1
        glVertex2f(-0.362f, -0.114f); //V1
        glVertex2f(-0.365f, -0.118f); //Q1
        glVertex2f(-0.372f, -0.127f); //P1
        glVertex2f(-0.375f, -0.133f); //R1
        glVertex2f(-0.304f, -0.135f); //S1
        glVertex2f(-0.303f, -0.125f); //T1
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.304f, -0.135f); //S1
        glVertex2f(-0.303f, -0.125f); //T1
        glVertex2f(-0.286f, -0.107f); //W1
        glVertex2f(-0.278f, -0.109f); //Z1
        glVertex2f(-0.285f, -0.140f); //A2
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.264f, -0.102f); //B2
        glVertex2f(-0.286f, -0.107f); //W1
        glVertex2f(-0.278f, -0.109f); //Z1
        glVertex2f(-0.244f, -0.109f); //D2
        glVertex2f(-0.245f, -0.107f); //C2
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.244f, -0.109f); //D2
        glVertex2f(-0.245f, -0.107f); //C2
        glVertex2f(-0.220f, -0.110f); //E2
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.285f, -0.140f); //A2
        glVertex2f(-0.275f, -0.150f); //F2
        glVertex2f(-0.247f, -0.137f); //G2
        glVertex2f(-0.260f, -0.129f); //H2
        glVertex2f(-0.283f, -0.129f); //I2
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.275,-0.150); //F2
        glVertex2f(-0.247,-0.137); //G2
        glVertex2f(-0.193,-0.137); //J2
        glVertex2f(-0.187,-0.140); //K2
        glVertex2f(-0.185,-0.151); //L2
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.185,-0.151); //L2
        glVertex2f(-0.134,-0.152); //M2
        glVertex2f(-0.186,-0.145); //N2
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.193,-0.137); //J2
        glVertex2f(-0.187,-0.140); //K2
        glVertex2f(-0.168,-0.131); //O2
        glVertex2f(-0.169,-0.125); //P2
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.168,-0.131); //O2
        glVertex2f(-0.169,-0.125); //P2
        glVertex2f(-0.136,-0.131); //Q2
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.517,-0.167); //C3
        glVertex2f(-0.494,-0.163); //D3
        glVertex2f(-0.490,-0.170); //E3
        glVertex2f(-0.496,-0.176); //F3
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.496,-0.176); //F3
        glVertex2f(-0.490,-0.170); //E3
        glVertex2f(-0.474,-0.168); //G3
        glVertex2f(-0.468,-0.177); //H3
        glVertex2f(-0.476,-0.182); //I3
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.468,-0.177); //H3
        glVertex2f(-0.476,-0.182); //I3
        glVertex2f(-0.366,-0.186); //K3
        glVertex2f(-0.379,-0.182); //J3
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.379,-0.186); //L3
        glVertex2f(-0.380,-0.195); //M3
        glVertex2f(-0.392,-0.216); //N3
        glVertex2f(-0.419,-0.184); //O3
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.380,-0.195); //M3
        glVertex2f(-0.392,-0.216); //N3
        glVertex2f(-0.380,-0.212); //Q3
        glVertex2f(-0.368,-0.200); //P3
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.392,-0.216); //N3
        glVertex2f(-0.429,-0.219); //R3
        glVertex2f(-0.414,-0.223); //S3
        glVertex2f(-0.332,-0.228); //T3
        glVertex2f(-0.337,-0.221); //U3
        glVertex2f(-0.380,-0.212); //Q3
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.429,-0.219); //R3
        glVertex2f(-0.414,-0.223); //S3
        glVertex2f(-0.393,-0.246); //W3
        glVertex2f(-0.459,-0.248); //V3
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(-0.332,-0.228); //T3
        glVertex2f(-0.337,-0.221); //U3
        glVertex2f(-0.322,-0.210); //Z3
        glVertex2f(-0.302,-0.211); //A4
        glVertex2f(-0.277,-0.234); //B4
        glVertex2f(-0.319,-0.236); //C4
        glEnd();



        glPopMatrix();

    }

    void drawRightSideVerticleFracture()
    {
        glColor3f(17.0f/255.0f, 51.0f/255.0f, 17.0f/255.0f);

        glBegin(GL_POLYGON);
        glVertex2f(0.935f, -0.100f); //O
        glVertex2f(0.886f, -0.117f); //P
        glVertex2f(0.913f, -0.117f); //Q
        glVertex2f(0.952f, -0.100f); //R
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(0.913f, -0.117f); //Q
        glVertex2f(0.923f, -0.123f); //S
        glVertex2f(0.907f, -0.126f); //T
        glVertex2f(0.899f, -0.121f); //U
        glVertex2f(0.886f, -0.117f); //P
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(0.923f, -0.123f); //S
        glVertex2f(0.907f, -0.126f); //T
        glVertex2f(0.902f, -0.127f); //V
        glVertex2f(0.940f, -0.130f); //W
        glVertex2f(0.957f, -0.129f); //Z
        glVertex2f(0.967f, -0.125f); //A1
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(0.957f, -0.129f); //Z
        glVertex2f(0.940f, -0.130f); //W
        glVertex2f(0.952f, -0.143f); //B1
        glVertex2f(0.961f, -0.153f); //C1
        glVertex2f(0.981f, -0.153f); //D1
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(0.952f, -0.143f); //B1
        glVertex2f(0.961f, -0.153f); //C1
        glVertex2f(0.933f, -0.171f); //F1
        glVertex2f(0.913f, -0.170f); //E1
        glEnd();

        glBegin(GL_POLYGON);
        glVertex2f(0.933f, -0.171f); //F1
        glVertex2f(0.918f, -0.170f); //G1
        glVertex2f(0.932f, -0.180f); //H1
        glVertex2f(0.942f, -0.180f); //I1
        glEnd();

    }

    void drawBrokenParticles()
    {
        glColor3f(81.0f/255.0f, 86.0f/255.0f, 20.0f/255.0f);
        glBegin(GL_POLYGON);
        glVertex2f(-0.791f, -0.365f); //H1
        glVertex2f(-0.755f, -0.338f); //I1
        glVertex2f(-0.746f, -0.337f); //J1
        glVertex2f(-0.713f, -0.362f); //K1
        glVertex2f(-0.730f, -0.370f); //L1
        glVertex2f(-0.770f, -0.370f); //M1
        glEnd();


        glBegin(GL_POLYGON);
        glVertex2f(-0.515f, -0.399f); //N1
        glVertex2f(-0.494f, -0.380f); //Z1
        glVertex2f(-0.491f, -0.379f); //A2
        glVertex2f(-0.489f, -0.378f); //B2
        glVertex2f(-0.486f, -0.379f); //C2
        glVertex2f(-0.485f, -0.381f); //D2
        glVertex2f(-0.462f, -0.398f); //E2
        glVertex2f(-0.471f, -0.400f); //F2
        glVertex2f(-0.472f, -0.402f); //G2
        glVertex2f(-0.500f, -0.403f); //H2
        glVertex2f(-0.500f, -0.400f); //I2
        glEnd();

        glPushMatrix();
        glTranslatef(-0.08f, 0.0f, 0.0f);
            glColor3f(85.0f/255.0f, 91.0f/255.0f, 27.0f/255.0f);
            glBegin(GL_POLYGON);
            glVertex2f(-0.477f, -0.343f); //J2
            glVertex2f(-0.412f, -0.296f); //K2
            glVertex2f(-0.403f, -0.296f); //L2
            glVertex2f(-0.370f, -0.287f); //M2
            glVertex2f(-0.354f, -0.274f); //N2
            glVertex2f(-0.258f, -0.285f); //O2
            glVertex2f(-0.268f, -0.293f); //P2
            glVertex2f(-0.311f, -0.297f); //Q2
            glVertex2f(-0.334f, -0.306f); //S2
            glVertex2f(-0.310f, -0.326f); //T2
            glVertex2f(-0.327f, -0.341f); //U2
            glEnd();

            glColor3f(40.0f/255.0f, 67.0f/255.0f, 23.0f/255.0f);
            glBegin(GL_POLYGON);
            glVertex2f(-0.413f, -0.285f); //V2
            glVertex2f(-0.404f, -0.282f); //W2
            glVertex2f(-0.402f, -0.278f); //Z2
            glVertex2f(-0.391f, -0.278f); //A3
            glVertex2f(-0.360f, -0.300f); //B3
            glVertex2f(-0.367f, -0.302f); //C3
            glVertex2f(-0.387f, -0.314f); //D3
            glEnd();

            glColor3f(85.0f/255.0f, 91.0f/255.0f, 27.0f/255.0f);
            glBegin(GL_POLYGON);
            glVertex2f(-0.315f, -0.243f); //E3
            glVertex2f(-0.291f, -0.226f); //F3
            glVertex2f(-0.272f, -0.243f); //G3
            glEnd();
        glPopMatrix();


        glPushMatrix();
        glTranslatef(0.15f, 0.0f, 0.0f);
            glColor3f(87.0f/255.0f, 89.0f/255.0f, 27.0f/255.0f);
            glBegin(GL_POLYGON);
            glVertex2f(-0.196f, -0.522f); //H3
            glVertex2f(-0.142f, -0.524f); //I3
            glVertex2f(-0.165f, -0.504f); //J3
            glVertex2f(-0.169f, -0.503f); //K3
            glVertex2f(-0.172f, -0.502f); //L3
            glVertex2f(-0.174f, -0.502f); //M3
            glVertex2f(-0.176f, -0.504f); //N3
            glEnd();

            glColor3f(72.0f/255.0f, 79.0f/255.0f, 25.0f/255.0f);
            glBegin(GL_POLYGON);
            glVertex2f(-0.062f, -0.503f); //O3
            glVertex2f(-0.046f, -0.483f); //P3
            glVertex2f(-0.031f, -0.483f); //Q3
            glVertex2f(-0.007f, -0.500f); //R3
            glVertex2f(-0.017f, -0.501f); //S3
            glVertex2f(-0.018f, -0.504f); //T3
            glEnd();

            glColor3f(82.0f/255.0f, 86.0f/255.0f, 23.0f/255.0f);
            glBegin(GL_POLYGON);
            glVertex2f(-0.167f, -0.448f); //U3
            glVertex2f(-0.088f, -0.450f); //V3
            glVertex2f(-0.087f, -0.439f); //W3
            glVertex2f(-0.046f, -0.439f); //Z3
            glVertex2f(-0.046f, -0.412f); //A4
            glVertex2f(-0.083f, -0.392f); //B4
            glVertex2f(-0.088f, -0.391f); //C4
            glVertex2f(-0.096f, -0.393f); //D4
            glVertex2f(-0.102f, -0.398f); //E4
            glVertex2f(-0.126f, -0.424f); //F4
            glVertex2f(-0.129f, -0.428f); //G4
            glVertex2f(-0.134f, -0.431f); //H4
            glVertex2f(-0.139f, -0.431f); //I4
            glVertex2f(-0.144f, -0.432f); //J4
            glVertex2f(-0.156f, -0.432f); //K4
            glEnd();

            glBegin(GL_POLYGON);
            glVertex2f(0.105f, -0.494f); //A5
            glVertex2f(0.156f, -0.464f); //B5
            glVertex2f(0.198f, -0.496f); //C5
            glEnd();
        glPopMatrix();


        glPushMatrix();
        glTranslatef(0.05f, 0.0f, 0.0f);
            glColor3f(85.0f/255.0f, 90.0f/255.0f, 32.0f/255.0f);
            glBegin(GL_POLYGON);
            glVertex2f(-0.800f, -0.160f); //E6
            glVertex2f(-0.715f, -0.159f); //F6
            glVertex2f(-0.763f, -0.139f); //G6
            glVertex2f(-0.775f, -0.139f); //H6
            glEnd();
        glPopMatrix();


        glPushMatrix();
        glTranslatef(0.45f, 0.03f, 0.0f);
            glColor3f(90.0f/255.0f, 91.0f/255.0f, 33.0f/255.0f);
            glBegin(GL_POLYGON);
            glVertex2f(-0.072f, -0.123f); //L6
            glVertex2f(-0.037f, -0.112f); //M6
            glVertex2f(-0.021f, -0.126f); //N6
            glEnd();

            glBegin(GL_POLYGON);
            glVertex2f(-0.010f, -0.145f); //O6
            glVertex2f(0.033f, -0.146f); //P6
            glVertex2f(0.020f, -0.135f); //Q6
            glVertex2f(0.005f, -0.134f); //R6
            glEnd();
        glPopMatrix();



        glPushMatrix();
        glTranslatef(-0.15f, 0.02f, 0.0f);
            glColor3f(90.0f/255.0f, 91.0f/255.0f, 33.0f/255.0f);
            glBegin(GL_POLYGON);
            glVertex2f(0.078f, -0.186f); //S6
            glVertex2f(0.064f, -0.164f); //T6
            glVertex2f(0.030f, -0.171f); //U6
            glVertex2f(0.028f, -0.176f); //V6
            glVertex2f(0.031f, -0.182f); //W6
            glVertex2f(0.043f, -0.190f); //Z6
            glEnd();

            glBegin(GL_POLYGON);
            glVertex2f(0.089f, -0.162f); //A7
            glVertex2f(0.114f, -0.146f); //B7
            glVertex2f(0.129f, -0.166f); //C7
            glVertex2f(0.093f, -0.167f); //D7
            glEnd();
        glPopMatrix();


        glPushMatrix();
        glTranslatef(0.25f, 0.035f, 0.0f);
            glColor3f(83.0f/255.0f, 91.0f/255.0f, 29.0f/255.0f);
            glBegin(GL_POLYGON);
            glVertex2f(0.542f, -0.345f); //N5
            glVertex2f(0.586f, -0.347f); //O5
            glVertex2f(0.607f, -0.341f); //P5
            glVertex2f(0.583f, -0.316f); //Q5
            glVertex2f(0.577f, -0.314f); //R5
            glVertex2f(0.569f, -0.314f); //S5
            glVertex2f(0.563f, -0.317f); //T5
            glEnd();
        glPopMatrix();


        glPushMatrix();
        glTranslatef(0.2f, 0.015f, 0.0f);

            glColor3f(81.0f/255.0f, 81.0f/255.0f, 19.0f/255.0f);
            glBegin(GL_POLYGON);
            glVertex2f(0.256f, -0.233f); //S10
            glVertex2f(0.290f, -0.198f); //T10
            glVertex2f(0.380f, -0.200f); //U10
            glVertex2f(0.361f, -0.233f); //V10
            glEnd();

            glBegin(GL_POLYGON);
            glVertex2f(0.430f, -0.250f); //C11
            glVertex2f(0.442f, -0.238f); //B11
            glVertex2f(0.464f, -0.209f); //A11
            glVertex2f(0.435f, -0.210f); //Z10
            glVertex2f(0.380f, -0.200f); //U10
            glVertex2f(0.361f, -0.233f); //V10
            glVertex2f(0.350f, -0.249f); //W10
            glEnd();

            glBegin(GL_POLYGON);
            glVertex2f(0.623f, -0.239f); //D11
            glVertex2f(0.594f, -0.202f); //E11
            glVertex2f(0.473f, -0.198f); //F11
            glVertex2f(0.464f, -0.209f); //A11
            glVertex2f(0.442f, -0.238f); //B11
            glEnd();

            glBegin(GL_POLYGON);
            glVertex2f(0.509f, -0.264f); //G11
            glVertex2f(0.540f, -0.238f); //H11
            glVertex2f(0.480f, -0.238f); //I11
            glEnd();

            glBegin(GL_POLYGON);
            glVertex2f(0.611f, -0.224f); //J11
            glVertex2f(0.720f, -0.220f); //K11
            glVertex2f(0.688f, -0.194f); //L11
            glVertex2f(0.613f, -0.194f); //T11
            glVertex2f(0.594f, -0.202f); //E11
            glEnd();

            glBegin(GL_POLYGON);
            glVertex2f(0.841f, -0.194f); //M11
            glVertex2f(0.841f, -0.115f); //N11
            glVertex2f(0.628f, -0.115f); //O11
            glVertex2f(0.665f, -0.132f); //P11
            glVertex2f(0.580f, -0.144f); //Q11
            glVertex2f(0.601f, -0.182f); //R11
            glVertex2f(0.571f, -0.194f); //S11
            glEnd();



            /////




            glColor3f(83.0f/255.0f, 91.0f/255.0f, 29.0f/255.0f);

            glBegin(GL_POLYGON);
            glVertex2f(0.429f, -0.291f); //U5
            glVertex2f(0.454f, -0.274f); //V5
            glVertex2f(0.459f, -0.273f); //W5
            glVertex2f(0.456f, -0.273f); //Z5
            glVertex2f(0.469f, -0.276f); //A6
            glVertex2f(0.496f, -0.291f); //B6
            glVertex2f(0.482f, -0.292f); //C6
            glVertex2f(0.476f, -0.295f); //D6
            glEnd();

            glBegin(GL_POLYGON);
            glVertex2f(-0.271f, -0.147f); //I6
            glVertex2f(-0.262f, -0.141f); //J6
            glVertex2f(-0.259f, -0.148f); //K6
            glEnd();

            glBegin(GL_POLYGON);
            glVertex2f(0.078f, -0.186f); //S6
            glVertex2f(0.064f, -0.164f); //T6
            glVertex2f(0.030f, -0.171f); //U6
            glVertex2f(0.028f, -0.176f); //V6
            glVertex2f(0.031f, -0.182f); //W6
            glVertex2f(0.043f, -0.190f); //Z6
            glEnd();

            glBegin(GL_POLYGON);
            glVertex2f(0.073f, -0.209f); //E7
            glVertex2f(0.101f, -0.190f); //F7
            glVertex2f(0.124f, -0.211f); //G7
            glVertex2f(0.099f, -0.227f); //H7
            glEnd();


            glBegin(GL_POLYGON);
            glVertex2f(0.166f, -0.161f); //N7
            glVertex2f(0.184f, -0.147f); //O7
            glVertex2f(0.216f, -0.158f); //P7
            glEnd();

            glBegin(GL_POLYGON);
            glVertex2f(0.209f, -0.201f); //Q7
            glVertex2f(0.206f, -0.196f); //R7
            glVertex2f(0.233f, -0.178f); //S7
            glVertex2f(0.247f, -0.178f); //T7
            glVertex2f(0.264f, -0.197f); //U7
            glVertex2f(0.235f, -0.200f); //V7
            glVertex2f(0.230f, -0.203f); //W7
            glEnd();

            glBegin(GL_POLYGON);
            glVertex2f(0.304f, -0.177f); //Z7
            glVertex2f(0.326f, -0.161f); //A8
            glVertex2f(0.347f, -0.177f); //B8
            glEnd();

            glBegin(GL_POLYGON);
            glVertex2f(0.559f, -0.231f); //G9
            glVertex2f(0.586f, -0.231f); //H9
            glVertex2f(0.585f, -0.226f); //I9
            glVertex2f(0.583f, -0.221f); //J9
            glVertex2f(0.580f, -0.220f); //K9
            glVertex2f(0.571f, -0.220f); //L9
            glEnd();


            glColor3f(77.0f/255.0f, 80.0f/255.0f, 17.0f/255.0f);
            glBegin(GL_POLYGON);
            glVertex2f(0.149f, -0.220f); //I7
            glVertex2f(0.202f, -0.219f); //J7
            glVertex2f(0.198f, -0.208f); //K7
            glVertex2f(0.183f, -0.196f); //L7
            glVertex2f(0.172f, -0.194f); //M7
            glEnd();


            glColor3f(115.0f/255.0f, 114.0f/255.0f, 38.0f/255.0f);
            glBegin(GL_POLYGON);
            glVertex2f(0.396f, -0.200f); //C8
            glVertex2f(0.416f, -0.193f); //D8
            glVertex2f(0.446f, -0.208f); //E8
            glVertex2f(0.437f, -0.219f); //F8
            glVertex2f(0.420f, -0.220f); //G8
            glVertex2f(0.406f, -0.231f); //H8
            glVertex2f(0.398f, -0.234f); //I8
            glVertex2f(0.387f, -0.234f); //J8
            glVertex2f(0.379f, -0.232f); //K8
            glVertex2f(0.361f, -0.224f); //L8
            glVertex2f(0.367f, -0.216f); //M8
            glVertex2f(0.361f, -0.213f); //N8
            glVertex2f(0.355f, -0.211f); //O8
            glVertex2f(0.348f, -0.212f); //P8
            glVertex2f(0.336f, -0.200f); //Q8
            glVertex2f(0.344f, -0.189f); //R8
            glVertex2f(0.356f, -0.183f); //S8
            glVertex2f(0.364f, -0.181f); //T8
            glVertex2f(0.373f, -0.180f); //U8
            glEnd();

            glBegin(GL_POLYGON);
            glVertex2f(0.456f, -0.208f); //V8
            glVertex2f(0.487f, -0.222f); //W8
            glVertex2f(0.494f, -0.223f); //Z8
            glVertex2f(0.500f, -0.220f); //A9
            glVertex2f(0.516f, -0.210f); //B9
            glVertex2f(0.489f, -0.189f); //C9
            glVertex2f(0.484f, -0.187f); //D9
            glVertex2f(0.473f, -0.187f); //E9
            glVertex2f(0.462f, -0.194f); //F9
            glEnd();

            glBegin(GL_POLYGON);
            glVertex2f(0.697f, -0.199f); //M9
            glVertex2f(0.676f, -0.179f); //N9
            glVertex2f(0.649f, -0.200f); //O9
            glEnd();

            glBegin(GL_POLYGON);
            glVertex2f(0.665f, -0.165f); //P9
            glVertex2f(0.687f, -0.167f); //Q9
            glVertex2f(0.679f, -0.155f); //R9
            glEnd();

            glBegin(GL_POLYGON);
            glVertex2f(0.539f, -0.156f); //S9
            glVertex2f(0.576f, -0.128f); //T9
            glVertex2f(0.603f, -0.164f); //U9
            glVertex2f(0.578f, -0.170f); //V9
            glVertex2f(0.556f, -0.181f); //W9
            glVertex2f(0.532f, -0.181f); //Z9
            glVertex2f(0.527f, -0.176f); //A10
            glVertex2f(0.516f, -0.177f); //B10
            glVertex2f(0.525f, -0.161f); //C10
            glEnd();

            glBegin(GL_POLYGON);
            glVertex2f(0.471f, -0.136f); //D10
            glVertex2f(0.493f, -0.125f); //E10
            glVertex2f(0.510f, -0.138f); //F10
            glEnd();

            glBegin(GL_POLYGON);
            glVertex2f(0.436f, -0.123f); //G10
            glVertex2f(0.410f, -0.122f); //H10
            glVertex2f(0.422f, -0.116f); //I10
            glEnd();

            glBegin(GL_POLYGON);
            glVertex2f(0.586f, -0.168f); //J10
            glVertex2f(0.607f, -0.182f); //K10
            glVertex2f(0.631f, -0.182f); //L10
            glVertex2f(0.648f, -0.172f); //M10
            glVertex2f(0.631f, -0.160f); //N10
            glVertex2f(0.620f, -0.156f); //O10
            glVertex2f(0.610f, -0.154f); //P10
            glVertex2f(0.602f, -0.154f); //Q10
            glVertex2f(0.596f, -0.155f); //R10
            glEnd();

        glPopMatrix();

    }

    //Warnings
    void WaringBoard()
    {
        //Stand Shadow
        glPushMatrix();
        glScalef(1.0f, 0.3f, 1.0f);
        glTranslatef(0.0f, -0.925f, 0.0f);

        drawCircle(-0.5695f, -0.399f, 0.05f, 100, 73.0f/255.0f, 109.0f/255.0f, 11.0f/255.0f);

        glPopMatrix();

        //stand
        glColor3f(43.0f/255.0f, 69.0f/255.0f, 15.0f/255.0f);
        glBegin(GL_POLYGON);
        glVertex2f(-0.578f,-0.399f);
        glVertex2f(-0.561f,-0.399f);
        glVertex2f(-0.561f,-0.299f);
        glVertex2f(-0.578f,-0.299f);

        glEnd();

        //Board
        glColor3f(124.0f/255.0f, 100.0f/255.0f, 2.0f/255.0f);
        glBegin(GL_TRIANGLES);
        glVertex2f(-0.569f,-0.160f);
        glVertex2f(-0.660f,-0.312f);
        glVertex2f(-0.479f,-0.312f);

        glEnd();

        glPushMatrix();
        glScalef(0.87f, 0.87f, 0.87f);
        glTranslatef(-0.085f, -0.04f, 0.0f);

        glColor3f(236.0f/255.0f, 171.0f/255.0f, 11.0f/255.0f);
        glBegin(GL_TRIANGLES);
        glVertex2f(-0.569f,-0.160f);
        glVertex2f(-0.660f,-0.312f);
        glVertex2f(-0.479f,-0.312f);

        glEnd();
        glPopMatrix();


        //Sign
        glColor3f(45.0f/255.0f, 73.0f/255.0f, 26.0f/255.0f);
        glBegin(GL_POLYGON);
        glVertex2f(-0.575f,-0.218f);
        glVertex2f(-0.563f,-0.218f);
        glVertex2f(-0.563f,-0.263f);
        glVertex2f(-0.575f,-0.263f);

        glEnd();

        drawHalfCircle(-0.5685f, -0.218f, 0.0065f, 100, 45.0f/255.0f, 73.0f/255.0f, 26.0f/255.0f);
        drawCircle(-0.5685f, -0.263f, 0.0065f, 100, 45.0f/255.0f, 73.0f/255.0f, 26.0f/255.0f);


        drawCircle(-0.5685f, -0.280f, 0.0065f, 100, 45.0f/255.0f, 73.0f/255.0f, 26.0f/255.0f);

    }

    void WaringBarrier()
    {
        //Barrier Shadow
        glPushMatrix();
        glScalef(1.0f, 0.12f, 1.0f);
        glTranslatef(0.0f, -3.05f, 0.0f);

        drawCircle(0.290, -0.417, 0.17f, 100, 73.0f/255.0f, 109.0f/255.0f, 11.0f/255.0f);

        glPopMatrix();

        //Barrier
        glColor3f(205.0f/255.0f, 179.0f/255.0f, 82.0f/255.0f);
        glBegin(GL_POLYGON);

        glVertex2f(0.120f, -0.257f); //M
        glVertex2f(0.460f, -0.257f); //O
        glVertex2f(0.460f, -0.330f); //P
        glVertex2f(0.120f, -0.330f); //Q

        glEnd();


        glColor3f(148.0f/255.0f, 90.0f/255.0f, 8.0f/255.0f);
        glBegin(GL_POLYGON);
        glVertex2f(0.171f, -0.257f); //S
        glVertex2f(0.214f, -0.257f); //T
        glVertex2f(0.172f, -0.330f); //U
        glVertex2f(0.129f, -0.330f); //R

        glEnd();


        glPushMatrix();
        glTranslatef(0.08f, 0.0f, 0.0f);

        glBegin(GL_POLYGON);
        glVertex2f(0.171f, -0.257f); //S
        glVertex2f(0.214f, -0.257f); //T
        glVertex2f(0.172f, -0.330f); //U
        glVertex2f(0.129f, -0.330f); //R

        glEnd();
        glPopMatrix();


        glPushMatrix();
        glTranslatef(0.16f, 0.0f, 0.0f);

        glBegin(GL_POLYGON);
        glVertex2f(0.171f, -0.257f); //S
        glVertex2f(0.214f, -0.257f); //T
        glVertex2f(0.172f, -0.330f); //U
        glVertex2f(0.129f, -0.330f); //R

        glEnd();
        glPopMatrix();


        glPushMatrix();
        glTranslatef(0.24f, 0.0f, 0.0f);

        glBegin(GL_POLYGON);
        glVertex2f(0.171f, -0.257f); //S
        glVertex2f(0.214f, -0.257f); //T
        glVertex2f(0.172f, -0.330f); //U
        glVertex2f(0.129f, -0.330f); //R

        glEnd();
        glPopMatrix();

        //Left Stand
        glColor3f(65.0f/255.0f, 71.0f/255.0f, 12.0f/255.0f);
        glBegin(GL_POLYGON);
        glVertex2f(0.145f, -0.330f); //R
        glVertex2f(0.163f, -0.330f); //U
        glVertex2f(0.148f, -0.417f); //T
        glVertex2f(0.130f, -0.417f); //S

        glEnd();

        glColor3f(46.0f/255.0f, 60.0f/255.0f, 10.0f/255.0f);
        glBegin(GL_POLYGON);
        glVertex2f(0.163f, -0.330f); //U
        glVertex2f(0.181f, -0.330f); //Z
        glVertex2f(0.190f, -0.402f); //W
        glVertex2f(0.172f, -0.402f); //V

        glEnd();

        //Right Stand
        glColor3f(65.0f/255.0f, 71.0f/255.0f, 12.0f/255.0f);
        glBegin(GL_POLYGON);
        glVertex2f(0.430f, -0.330f); //R
        glVertex2f(0.412f, -0.330f); //U
        glVertex2f(0.427f, -0.417f); //T
        glVertex2f(0.445f, -0.417f); //S

        glEnd();

        glColor3f(46.0f/255.0f, 60.0f/255.0f, 10.0f/255.0f);
        glBegin(GL_POLYGON);
        glVertex2f(0.412f, -0.330f); //U
        glVertex2f(0.394f, -0.330f); //Z
        glVertex2f(0.385f, -0.402f); //V
        glVertex2f(0.403f, -0.402f); //W

        glEnd();


    }

    //Hole
    void drawHole()
    {
        glColor3f(41.0f/255.0f, 37.0f/255.0f, 24.0f/255.0f);
        glBegin(GL_POLYGON);

        glVertex2f(-0.021f, -0.280f); //Q
        glVertex2f(0.052f, -0.368f); //R
        glVertex2f(0.052f, -0.380f); //S
        glVertex2f(0.100f, -0.366f); //T
        glVertex2f(0.128f, -0.363f); //U
        glVertex2f(0.197f, -0.365f); //V
        glVertex2f(0.169f, -0.345f); //W
        glVertex2f(0.219f, -0.332f); //Z
        glVertex2f(0.317f, -0.340f); //A1
        glVertex2f(0.260f, -0.317f); //B1
        glVertex2f(0.250f, -0.308f); //C1
        glVertex2f(0.304f, -0.292f); //D1
        glVertex2f(0.323f, -0.281f); //E1
        glVertex2f(0.389f, -0.274f); //F1
        glVertex2f(0.366f, -0.271f); //G1
        glVertex2f(0.320f, -0.271f); //H1
        glVertex2f(0.311f, -0.262f); //I1
        glVertex2f(0.319f, -0.253f); //J1
        glVertex2f(0.337f, -0.247f); //K1
        glVertex2f(0.245f, -0.221f); //L1
        glVertex2f(0.272f, -0.208f); //M1
        glVertex2f(0.246f, -0.205f); //N1
        glVertex2f(0.229f, -0.207f); //O1
        glVertex2f(0.199f, -0.206f); //P1
        glVertex2f(0.172f, -0.201f); //Q1
        glVertex2f(0.190f, -0.188f); //R1
        glVertex2f(0.174f, -0.188f); //S1
        glVertex2f(0.159f, -0.195f); //T1
        glVertex2f(0.084f, -0.190f); //U1
        glVertex2f(0.078f, -0.186f); //V1
        glVertex2f(0.057f, -0.192f); //W1
        glVertex2f(0.009f, -0.189f); //Z1
        glVertex2f(0.014f, -0.179f); //A2
        glVertex2f(-0.035f, -0.176f); //B2
        glVertex2f(-0.049f, -0.180f); //C2
        glVertex2f(-0.135f, -0.183f); //D2
        glVertex2f(-0.122f, -0.194f); //E2
        glVertex2f(-0.140f, -0.2f); //F2
        glVertex2f(-0.200f, -0.2f); //G2
        glVertex2f(-0.186f, -0.207f); //H2
        glVertex2f(-0.199f, -0.212f); //I2
        glVertex2f(-0.246f, -0.211f); //J2
        glVertex2f(-0.233f, -0.220f); //K2
        glVertex2f(-0.253f, -0.226f); //L2
        glVertex2f(-0.285f, -0.226f); //M2
        glVertex2f(-0.300f, -0.228f); //N2
        glVertex2f(-0.293f, -0.234f); //O2
        glVertex2f(-0.280f, -0.24f); //P2
        glVertex2f(-0.290f, -0.251f); //Q2
        glVertex2f(-0.309f, -0.259f); //R2
        glVertex2f(-0.322f, -0.263f); //S2
        glVertex2f(-0.315f, -0.266f); //T2
        glVertex2f(-0.305f, -0.278f); //U2
        glVertex2f(-0.308f, -0.285f); //V2
        glVertex2f(-0.344f, -0.293f); //W2
        glVertex2f(-0.335f, -0.297f); //Z2
        glVertex2f(-0.322f, -0.296f); //A3
        glVertex2f(-0.293f, -0.304f); //B3
        glVertex2f(-0.269f, -0.320f); //C3
        glVertex2f(-0.311f, -0.335f); //D3
        glVertex2f(-0.256f, -0.332f); //E3
        glVertex2f(-0.210f, -0.343f); //F3
        glVertex2f(-0.243f, -0.359f); //G3
        glVertex2f(-0.125f, -0.361f); //H3
        glVertex2f(-0.100f, -0.38f); //I3
        glVertex2f(-0.081f, -0.368f); //J3
        glVertex2f(0.004f, -0.386f); //K3
        glVertex2f(0.052f, -0.368f); //R

        glEnd();


        //Hole Shadow
        //Shadow Upper Color
        float r_S_U = 85.0f/255.0f;
        float g_S_U = 34.0f/255.0f;
        float b_S_U = 21.0f/255.0f;

        //Shadow Lower Color
        float r_S_L = 49.0f/255.0f;
        float g_S_L = 42.0f/255.0f;
        float b_S_L = 22.0f/255.0f;


        glColor3f(r_S_U, g_S_U, b_S_U);
        glBegin(GL_POLYGON);
        glVertex2f(0.172f, -0.201f); //Q1
        glVertex2f(0.199f, -0.206f); //P1
        glColor3f(r_S_L, g_S_L, b_S_L);
        glVertex2f(0.153f, -0.288f); //L3
        glEnd();


        glColor3f(r_S_U, g_S_U, b_S_U);
        glBegin(GL_POLYGON);
        glVertex2f(0.245f, -0.221f); //L1
        glVertex2f(0.263f, -0.226f); //M3
        glColor3f(r_S_L, g_S_L, b_S_L);
        glVertex2f(0.225f, -0.293f); //N3
        glEnd();


        glColor3f(r_S_U, g_S_U, b_S_U);
        glBegin(GL_POLYGON);
        glVertex2f(0.214f, -0.267f); //O1
        glVertex2f(0.215f, -0.290f); //P3
        glColor3f(r_S_L, g_S_L, b_S_L);
        glVertex2f(0.195f, -0.321f); //Q3
        glEnd();


        glColor3f(r_S_U, g_S_U, b_S_U);
        glBegin(GL_POLYGON);
        glVertex2f(0.247f, -0.334f); //R3
        glVertex2f(0.317f, -0.340f); //A1
        glColor3f(r_S_L, g_S_L, b_S_L);
        glVertex2f(0.260f, -0.317f); //B1
        glEnd();


        glColor3f(r_S_U, g_S_U, b_S_U);
        glBegin(GL_POLYGON);
        glVertex2f(0.323f, -0.281f); //E1
        glVertex2f(0.389f, -0.274f); //F1
        glVertex2f(0.366f, -0.271f); //G1
        glVertex2f(0.320f, -0.271f); //H1
        glVertex2f(0.315f, -0.286f); //S3
        glEnd();


        glColor3f(r_S_U, g_S_U, b_S_U);
        glBegin(GL_POLYGON);
        glVertex2f(0.161f, -0.364f); //T3
        glVertex2f(0.197f, -0.365f); //V
        glVertex2f(0.169f, -0.345f); //W
        glEnd();


        glColor3f(r_S_U, g_S_U, b_S_U);
        glBegin(GL_POLYGON);
        glVertex2f(-0.200f, -0.360f); //U3
        glVertex2f(-0.210f, -0.343f); //F3
        glVertex2f(-0.243f, -0.359f); //G3
        glEnd();


        glColor3f(r_S_U, g_S_U, b_S_U);
        glBegin(GL_POLYGON);
        glVertex2f(-0.290f, -0.251f); //Q2
        glVertex2f(-0.280f, -0.24f); //P2
        glVertex2f(-0.263f, -0.288f); //V3
        glColor3f(r_S_L, g_S_L, b_S_L);
        glVertex2f(-0.255f, -0.294f); //W3
        glVertex2f(-0.245f, -0.334f); //Z3
        glVertex2f(-0.256f, -0.332f); //E3
        glColor3f(r_S_U, g_S_U, b_S_U);
        glVertex2f(-0.269f, -0.320f); //C3
        glVertex2f(-0.293f, -0.304f); //B3
        glVertex2f(-0.305f, -0.278f); //U2
        glVertex2f(-0.315f, -0.266f); //T2
        glVertex2f(-0.309f, -0.259f); //R2
        glEnd();


        glColor3f(r_S_U, g_S_U, b_S_U);
        glBegin(GL_POLYGON);
        glVertex2f(-0.253f, -0.226f); //L2
        glVertex2f(-0.233f, -0.220f); //K2
        glColor3f(r_S_L, g_S_L, b_S_L);
        glVertex2f(-0.224f, -0.272f); //A4
        glEnd();


        glColor3f(r_S_U, g_S_U, b_S_U);
        glBegin(GL_POLYGON);
        glVertex2f(-0.180f, -0.26f); //W4
        glVertex2f(-0.186f, -0.207f); //H2
        glVertex2f(-0.174f, -0.254f); //B4
        glVertex2f(-0.174f, -0.261f); //C4
        glVertex2f(-0.170f, -0.270f); //D4
        glColor3f(r_S_L, g_S_L, b_S_L);
        glVertex2f(-0.150f, -0.324f); //E4
        glVertex2f(-0.150f, -0.332f); //F4
        glVertex2f(-0.179f, -0.291f); //G4
        glColor3f(r_S_U, g_S_U, b_S_U);
        glVertex2f(-0.185f, -0.282f); //H4
        glVertex2f(-0.187f, -0.273f); //I4
        glVertex2f(-0.190f, -0.263f); //J4
        glVertex2f(-0.195f, -0.237f); //K4
        glVertex2f(-0.196f, -0.229f); //L4
        glVertex2f(-0.199f, -0.212f); //I2
        glVertex2f(-0.186f, -0.207f); //H2

        glEnd();


        glColor3f(r_S_U, g_S_U, b_S_U);
        glBegin(GL_POLYGON);
        glVertex2f(-0.122f, -0.194f); //E2
        glVertex2f(-0.140f, -0.2f); //F2
        glColor3f(r_S_L, g_S_L, b_S_L);
        glVertex2f(-0.114f, -0.273f); //M4
        glEnd();


        glColor3f(r_S_U, g_S_U, b_S_U);
        glBegin(GL_POLYGON);
        glVertex2f(-0.049f, -0.180f); //C2
        glVertex2f(-0.075f, -0.181f); //O4
        glColor3f(r_S_L, g_S_L, b_S_L);
        glVertex2f(-0.066f, -0.267f); //N4
        glEnd();


        glColor3f(r_S_U, g_S_U, b_S_U);
        glBegin(GL_POLYGON);
        glVertex2f(-0.009f, -0.230f); //P4
        glVertex2f(-0.016f, -0.251f); //R4
        glColor3f(r_S_L, g_S_L, b_S_L);
        glVertex2f(-0.004f, -0.284f); //Q4
        glEnd();


        glColor3f(r_S_U, g_S_U, b_S_U);
        glBegin(GL_POLYGON);
        glVertex2f(0.094f, -0.267f); //V4
        glVertex2f(0.090f, -0.222f); //S4
        glVertex2f(0.076f, -0.277f); //T4
        glColor3f(r_S_L, g_S_L, b_S_L);
        glVertex2f(0.078f, -0.308f); //U4
        glEnd();
    }




    //House 1 Smoke
    void drawHouse1Smoke()
    {
        float r = 89.0f/255.0f;
        float g = 111.0f/255.0f;
        float b = 72.0f/255.0f;

        drawCircle(XHouse1Smoke[0], YHouse1Smoke[0], 0.036f, 100, r, g, b); //S
        drawCircle(XHouse1Smoke[1], YHouse1Smoke[1], 0.051f, 100, r, g, b); //U
        drawCircle(XHouse1Smoke[2], YHouse1Smoke[2], 0.052f, 100, r, g, b); //V
        drawCircle(XHouse1Smoke[3], YHouse1Smoke[3], 0.057f, 100, r, g, b); //W
        drawCircle(XHouse1Smoke[4], YHouse1Smoke[4], 0.048f, 100, r, g, b); //Z
        drawCircle(XHouse1Smoke[5], YHouse1Smoke[5], 0.059f, 100, r, g, b); //A1
        drawCircle(XHouse1Smoke[6], YHouse1Smoke[6], 0.050f, 100, r, g, b); //B1
        drawCircle(XHouse1Smoke[7], YHouse1Smoke[7], 0.032f, 100, r, g, b); //C1

        glPushMatrix();
        glTranslatef(House1SmokeXposition, House1SmokeYposition, 0.0f);
            glBegin(GL_POLYGON);
            glVertex2f(0.753f, 0.105f); //T
            glVertex2f(0.719f, 0.066f); //D1
            glVertex2f(0.718f, 0.074f); //E1
            glVertex2f(0.718f, 0.082f); //F1
            glVertex2f(0.719f, 0.088f); //G1
            glVertex2f(0.721f, 0.095f); //H1
            glVertex2f(0.726f, 0.102f); //I1
            glVertex2f(0.730f, 0.107f); //J1
            glVertex2f(0.735f, 0.111f); //K1
            glVertex2f(0.739f, 0.114f); //L1
            glVertex2f(0.797f, 0.144f); //M1
            glVertex2f(0.815f, 0.138f); //N1
            glVertex2f(0.814f, 0.131f); //Z1
            glVertex2f(0.810f, 0.131f); //A2
            glVertex2f(0.811f, 0.131f); //B2
            glVertex2f(0.809f, 0.129f); //C2
            glVertex2f(0.807f, 0.128f); //D2
            glVertex2f(0.805f, 0.127f); //E2
            glVertex2f(0.804f, 0.125f); //F2
            glVertex2f(0.802f, 0.122f); //G2
            glVertex2f(0.801f, 0.119f); //H2
            glVertex2f(0.799f, 0.116f); //I2
            glVertex2f(0.798f, 0.112f); //J2
            glVertex2f(0.797f, 0.108f); //K2
            glVertex2f(0.795f, 0.104f); //L2
            glVertex2f(0.793f, 0.101f); //M2
            glVertex2f(0.791f, 0.097f); //N2
            glVertex2f(0.788f, 0.092f); //O2
            glVertex2f(0.784f, 0.092f); //P2
            glVertex2f(0.780f, 0.090f); //Q2
            glVertex2f(0.775f, 0.088f); //S2
            glVertex2f(0.769f, 0.086f); //T2
            glVertex2f(0.761f, 0.086f); //U2
            glVertex2f(0.758f, 0.085f); //V2
            glVertex2f(0.753f, 0.084f); //W2
            glVertex2f(0.747f, 0.082f); //Z2
            glVertex2f(0.743f, 0.080f); //A3
            glVertex2f(0.738f, 0.077f); //B3
            glVertex2f(0.733f, 0.074f); //C3
            glVertex2f(0.729f, 0.071f); //D3
            glVertex2f(0.726f, 0.070f); //E3
            glVertex2f(0.723f, 0.068f); //F3
            glVertex2f(0.719f, 0.066f); //D1
            glEnd();
        glPopMatrix();


    }

    //Smoke
    void drawSmoke1()
    {
        float r = 89.0f/255.0f;
        float g = 111.0f/255.0f;
        float b = 72.0f/255.0f;

        drawCircle(XSmoke1[0] , YSmoke1[0] , 0.019f, 100, r, g, b); //O
        drawCircle(XSmoke1[1] , YSmoke1[1] , 0.026f, 100, r, g, b); //P
        drawCircle(XSmoke1[2] , YSmoke1[2] , 0.023f, 100, r, g, b); //Q
        drawCircle(XSmoke1[3] , YSmoke1[3] , 0.027f, 100, r, g, b); //R
        drawCircle(XSmoke1[4] , YSmoke1[4] , 0.032f, 100, r, g, b); //S
        drawCircle(XSmoke1[5] , YSmoke1[5] , 0.028f, 100, r, g, b); //T
        drawCircle(XSmoke1[6] , YSmoke1[6] , 0.030f, 100, r, g, b); //U
        drawCircle(XSmoke1[7] , YSmoke1[7] , 0.031f, 100, r, g, b); //V
        drawCircle(XSmoke1[8] , YSmoke1[8] , 0.028f, 100, r, g, b); //W
        drawCircle(XSmoke1[9] , YSmoke1[9] , 0.029f, 100, r, g, b); //Z
        drawCircle(XSmoke1[10], YSmoke1[10], 0.021f, 100, r, g, b); //A1
        drawCircle(XSmoke1[11], YSmoke1[11], 0.027f, 100, r, g, b); //B1
        drawCircle(XSmoke1[12], YSmoke1[12], 0.035f, 100, r, g, b); //C1
        drawCircle(XSmoke1[13], YSmoke1[13], 0.018f, 100, r, g, b); //D1
        drawCircle(XSmoke1[14], YSmoke1[14], 0.023f, 100, r, g, b); //E1
        drawCircle(XSmoke1[15], YSmoke1[15], 0.035f, 100, r, g, b); //F1
        drawCircle(XSmoke1[16], YSmoke1[16], 0.031f, 100, r, g, b); //I1
        drawCircle(XSmoke1[17], YSmoke1[17], 0.040f, 100, r, g, b); //J1
        drawCircle(XSmoke1[18], YSmoke1[18], 0.022f, 100, r, g, b); //K1
        drawCircle(XSmoke1[19], YSmoke1[19], 0.030f, 100, r, g, b); //L1
        drawCircle(XSmoke1[20], YSmoke1[20], 0.021f, 100, r, g, b); //M1
        drawCircle(XSmoke1[21], YSmoke1[21], 0.024f, 100, r, g, b); //N1
        drawCircle(XSmoke1[22], YSmoke1[22], 0.016f, 100, r, g, b); //Z1
        drawCircle(XSmoke1[23], YSmoke1[23], 0.020f, 100, r, g, b); //A2
        drawCircle(XSmoke1[24], YSmoke1[24], 0.025f, 100, r, g, b); //B2
        drawCircle(XSmoke1[25], YSmoke1[25], 0.022f, 100, r, g, b); //C2
        drawCircle(XSmoke1[26], YSmoke1[26], 0.025f, 100, r, g, b); //D2
        drawCircle(XSmoke1[27], YSmoke1[27], 0.023f, 100, r, g, b); //E2
        drawCircle(XSmoke1[28], YSmoke1[28], 0.028f, 100, r, g, b); //F2
        drawCircle(XSmoke1[29], YSmoke1[29], 0.019f, 100, r, g, b); //G2
        drawCircle(XSmoke1[30], YSmoke1[30], 0.031f, 100, r, g, b); //H2
        drawCircle(XSmoke1[31], YSmoke1[31], 0.032f, 100, r, g, b); //I2
        drawCircle(XSmoke1[32], YSmoke1[32], 0.026f, 100, r, g, b); //J2
        drawCircle(XSmoke1[33], YSmoke1[33], 0.028f, 100, r, g, b); //K2
        drawCircle(XSmoke1[34], YSmoke1[34], 0.030f, 100, r, g, b); //L2
        drawCircle(XSmoke1[35], YSmoke1[35], 0.030f, 100, r, g, b); //M2
        drawCircle(XSmoke1[36], YSmoke1[36], 0.041f, 100, r, g, b); //N2
        drawCircle(XSmoke1[37], YSmoke1[37], 0.031f, 100, r, g, b); //O2
        drawCircle(XSmoke1[38], YSmoke1[38], 0.032f, 100, r, g, b); //P2
        drawCircle(XSmoke1[39], YSmoke1[39], 0.024f, 100, r, g, b); //Q2
        drawCircle(XSmoke1[40], YSmoke1[40], 0.023f, 100, r, g, b); //S2
        drawCircle(XSmoke1[41], YSmoke1[41], 0.023f, 100, r, g, b); //T2
        drawCircle(XSmoke1[42], YSmoke1[42], 0.022f, 100, r, g, b); //U2
        drawCircle(XSmoke1[43], YSmoke1[43], 0.039f, 100, r, g, b); //V2
        drawCircle(XSmoke1[44], YSmoke1[44], 0.014f, 100, r, g, b); //W2
        drawCircle(XSmoke1[45], YSmoke1[45], 0.008f, 100, r, g, b); //Z2
        drawCircle(XSmoke1[46], YSmoke1[46], 0.012f, 100, r, g, b); //A3
        drawCircle(XSmoke1[47], YSmoke1[47], 0.032f, 100, r, g, b); //B3
        drawCircle(XSmoke1[48], YSmoke1[48], 0.033f, 100, r, g, b); //C3

    }

    void drawSmoke2()
    {
        float r = 89.0f/255.0f;
        float g = 111.0f/255.0f;
        float b = 72.0f/255.0f;


        drawCircle(XSmoke2[0] , YSmoke2[0] , 0.029f, 100, r, g, b); //G3
        drawCircle(XSmoke2[1] , YSmoke2[1] , 0.030f, 100, r, g, b); //H3
        drawCircle(XSmoke2[2] , YSmoke2[2] , 0.027f, 100, r, g, b); //I3
        drawCircle(XSmoke2[3] , YSmoke2[3] , 0.034f, 100, r, g, b); //J3
        drawCircle(XSmoke2[4] , YSmoke2[4] , 0.037f, 100, r, g, b); //K3
        drawCircle(XSmoke2[5] , YSmoke2[5] , 0.022f, 100, r, g, b); //L3
        drawCircle(XSmoke2[6] , YSmoke2[6] , 0.025f, 100, r, g, b); //M3
        drawCircle(XSmoke2[7] , YSmoke2[7] , 0.027f, 100, r, g, b); //N3
        drawCircle(XSmoke2[8] , YSmoke2[8] , 0.027f, 100, r, g, b); //O3
        drawCircle(XSmoke2[9] , YSmoke2[9] , 0.025f, 100, r, g, b); //P3
        drawCircle(XSmoke2[10], YSmoke2[10], 0.038f, 100, r, g, b); //Q3
        drawCircle(XSmoke2[10], YSmoke2[10], 0.011f, 100, r, g, b); //R3
        drawCircle(XSmoke2[10], YSmoke2[10], 0.008f, 100, r, g, b); //S3
        drawCircle(XSmoke2[10], YSmoke2[10], 0.010f, 100, r, g, b); //T3
        drawCircle(XSmoke2[10], YSmoke2[10], 0.017f, 100, r, g, b); //U3
        drawCircle(XSmoke2[10], YSmoke2[10], 0.012f, 100, r, g, b); //V3
        drawCircle(XSmoke2[10], YSmoke2[10], 0.010f, 100, r, g, b); //W3


    }


    void sound()
    {
        if (!scene4Sound) { return; }
        PlaySound(TEXT("fire.wav"), NULL, SND_ASYNC | SND_FILENAME | SND_LOOP);
    }



    void update()
    {

        //cloud
        if(cloudPosition > 1.0)
            cloudPosition = -1.0f;
        cloudPosition += cloudSpeed;


        //Building 1 Smoke
        bool flagBuilding1Smoke = false;
        for(int i=0; i<YBuilding1Smoke.size(); i++)
        {
            if(YBuilding1Smoke[i]>maxYBuilding1Smoke)
            {
                XBuilding1Smoke[i]=minXBuilding1Smoke;
                YBuilding1Smoke[i]=minYBuilding1Smoke;
                flagBuilding1Smoke = true;
            }
            else
            {
                if(flagBuilding1Smoke)
                {
                    float dx = tempXBuilding1Smoke[i] - XBuilding1Smoke[i];
                    float dy = tempYBuilding1Smoke[i] - YBuilding1Smoke[i];

                    float dist = sqrt(dx*dx + dy*dy);


                    XBuilding1Smoke[i] += Building1SmokeSpeed * dx / dist;
                    YBuilding1Smoke[i] += Building1SmokeSpeed * dy / dist;
                }

                XBuilding1Smoke[i]+=Building1SmokeSpeed;
                YBuilding1Smoke[i]+=Building1SmokeSpeed;

            }
        }


        //smoke1
        bool flagSmoke1 = false;
        for(int i=0; i<YSmoke1.size(); i++)
        {
            if(YSmoke1[i]>maxYSmoke1)
            {
                XSmoke1[i]=minXSmoke1;
                YSmoke1[i]=minYSmoke1;
                flagSmoke1 = true;
            }
            else
            {
                if(flagSmoke1)
                {
                    float dx = tempXSmoke1[i] - XSmoke1[i];
                    float dy = tempYSmoke1[i] - YSmoke1[i];

                    float dist = sqrt(dx*dx + dy*dy);

                    XSmoke1[i] += smoke1Speed * dx / dist;
                    YSmoke1[i] += smoke1Speed * dy / dist;
                }

                XSmoke1[i]+=smoke1Speed;
                YSmoke1[i]+=smoke1Speed;

            }
        }


        //smoke2
        bool flagSmoke2 = false;
        for(int i=0; i<YSmoke2.size(); i++)
        {
            if(YSmoke2[i]>maxYSmoke2)
            {
                XSmoke2[i]=minXSmoke2;
                YSmoke2[i]=minYSmoke2;
                flagSmoke2 = true;
            }
            else
            {
                if(flagSmoke2)
                {
                    float dx = tempXSmoke2[i] - XSmoke2[i];
                    float dy = tempYSmoke2[i] - YSmoke2[i];

                    float dist = sqrt(dx*dx + dy*dy);

                    XSmoke2[i] += smoke2Speed * dx / dist;
                    YSmoke2[i] += smoke2Speed * dy / dist;
                }

                XSmoke2[i]+=smoke2Speed;
                YSmoke2[i]+=smoke2Speed;

            }
        }


        cout << "Updating Scene 4: Memory Pulse" << endl;
        // glutPostRedisplay();
        if (!pause) {
            glutTimerFunc(200, Scene4::updateWrapper, 0);
            // glutIdleFunc(Scene4::updateWrapper);
            glutPostRedisplay();
        }
    }

    void Idle()
    {
        glutPostRedisplay();//// marks the current window as needing to be redisplayed
    }


    void display()
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
        glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer (background)

        drawSky();

        drawSun(0.440f, 0.410f, 0.06f);

        drawCloud();

        drawGround();

        drawHill();

        drawSideRoad();

        drawRoad();

        drawShrub3();

        drawTree();

        drawShrub2();

        drawSmoke1();

        drawSmoke2();

        glPushMatrix();
        glTranslatef(1.40f, 0.0f, 0.0f);
            drawBuilding1Smoke();
        glPopMatrix();

        drawBuildings();

        drawHouse1Smoke();

        drawCrackedRoad();

        drawFlower(0.53f, -0.32f, 0.015, 0.019f, 6.0f);

        drawHole();

        drawGroundCorner();

        drawBrokenParticles();

        drawRightSideVerticleFracture();

        WaringBoard();

        WaringBarrier();

        drawShrubs();




        glFlush(); // Render now
        glutSwapBuffers(); // Swap buffers (double buffering)

    }

    void SceneInfoDisplay()
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
        glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer (background)


        glColor3f(1.0f, 1.0f, 1.0f);

        renderBitmapString(-0.155f, 0.05f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Ashes and Echoes");
        renderBitmapString(-0.17f, -0.05f, 0.0f, GLUT_BITMAP_HELVETICA_18, "Scene 4: Memory Pulse");


        glFlush(); // Render now
        glutSwapBuffers(); // Swap buffers (double buffering)

    }


    void changeDisplay(unsigned char key, int x, int y) {
        if (key == 27) { // Escape key
            exit(0);
        } else if (key == 'D' ||  key == 'd') {
            cout << "D key pressed" << endl;
            pause = false; // Set pause to false
            glutDisplayFunc(Scene4::displayWrapper);

            sound();

            glutTimerFunc(100, Scene4::updateWrapper, 0);
        } else if (key == 'A' || key == 'a')  {
            PlaySound(NULL, NULL, SND_ASYNC | SND_PURGE);
            glutDisplayFunc(Scene4::SceneInfoDisplayWrapper);
            pause = true; // Set pause to true
        }
        glutPostRedisplay(); // Request a redraw of the current window
    }

    // static methods
    static void IdleWrapper() {
        if (instance == nullptr) {
            cerr << "Scene4 instance is null, cannot call Idle." << endl;
            return;
        } 
        instance->Idle();
     }
    static void displayWrapper() { 
        if (instance == nullptr) {
            cerr << "Scene4 instance is null, cannot call display." << endl;
            return;
        }
        instance->display();
    }
    static void changeDisplayWrapper(unsigned char key, int x, int y) { 
        if (instance == nullptr) {
            cerr << "Scene4 instance is null, cannot call changeDisplay." << endl;
            return;
        }
        instance->changeDisplay(key, x, y); 
    }
    static void SceneInfoDisplayWrapper() { 
        if (instance == nullptr) {
            cerr << "Scene4 instance is null, cannot call SceneInfoDisplay." << endl;
            return;
        }
        instance->SceneInfoDisplay(); 
    }
    static void updateWrapper() {
        if (instance == nullptr) {
            cerr << "Scene4 instance is null, cannot call update." << endl;
            return;
        } 
        instance->update(); 
    }
    static void updateWrapper(int value) { 
        if (instance == nullptr) {
            cerr << "Scene4 instance is null, cannot call update." << endl;
            return;
        }
        instance->update(); 
    }
};


bool SceneManager::scene1Sound = false;
bool SceneManager::scene2Sound = false;
bool SceneManager::scene3Sound = false;
bool SceneManager::scene4Sound = false;
bool SceneManager::scene5Sound = false;

Scene1* Scene1::instance = nullptr;
// Scene2* Scene2::instance = nullptr;
Scene3* Scene3::instance = nullptr;
Scene4* Scene4::instance = nullptr;
// Scene5* Scene5::instance = nullptr;

void displayScene(int sceneKey) {
    cout << "Displaying Scene: " << sceneKey << endl;
    SceneManager::resetSound(sceneKey); // turn on sound for only current scene
    cout << "Scene 1 Sound " << SceneManager::scene1Sound << endl;
    cout << "Scene 2 Sound " << SceneManager::scene2Sound << endl;
    cout << "Scene 3 Sound " << SceneManager::scene3Sound << endl;
    cout << "Scene 4 Sound " << SceneManager::scene4Sound << endl;
    cout << "Scene 5 Sound " << SceneManager::scene5Sound << endl;

    switch (sceneKey) {
    case 1:
        // Rename the window
        glutSetWindowTitle("Scene 1: Peaceful Vibrations");

        // Set up the scene
        static Scene1 scene1;
        if (Scene1::instance == nullptr) { // Only set the instance if it's not already set
            Scene1::instance = &scene1;
        } else {
            cout << "Scene1 instance already exists, not reinitializing." << endl;
            Scene1::instance->pause = false; // Resume the scene if it was paused
        }

        // Register callbacks
        glutDisplayFunc(Scene1::SceneInfoWrapper); // Register display callback handler for window re-paint
        glutKeyboardFunc(Scene1::changeDisplayWrapper);

        break;
    case 2:
        glutSetWindowTitle("Scene 2: Flash");
        break;
    case 3:
        // Rename the window
        glutSetWindowTitle("Scene 3: The Fall");

        // Set up the scene
        static Scene3 scene3;
        if (Scene3::instance == nullptr) {
            Scene3::instance = &scene3; // Set the instance only if it's not already set
        } else {
            cout << "Scene3 instance already exists, not reinitializing." << endl;
        }

        // cout << "Scene 3: The Fall " << sizeof scene3 << endl;
        if (Scene3::instance != nullptr) {
            Scene3::instance->initVariables(); // Initialize variables only if the instance is not null
        }

        // Register callbacks
        glutDisplayFunc(Scene3::display1Wrapper);
        glutKeyboardFunc(Scene3::handleKeyWrapper);

        break;
    case 4:
        // Rename the window
        glutSetWindowTitle("Scene 4: Memory Pulse");

        // Set up the scene
        static Scene4 scene4;
        if (Scene4::instance == nullptr) { // Only set the instance if it's not already set
            Scene4::instance = &scene4;
        } else {
            cout << "Scene4 instance already exists, not reinitializing." << endl;
            Scene4::instance->pause = false; // Resume the scene if it was paused
        }
        cout << "Scene 4: Memory Pulse " << sizeof scene4 << endl;

        glutDisplayFunc(Scene4::SceneInfoDisplayWrapper); // Register display callback handler for window re-paint
        // glutIdleFunc(Scene4::IdleWrapper);
        glutKeyboardFunc(Scene4::changeDisplayWrapper); // Register special key callback handler

        break;
    case 5:
        glutSetWindowTitle("Scene 5: New Light");
        break;
    default:
        break;
    }
}

int sceneKey = 0; // Global variable to track the scene
void changeScene(int key, int x, int y) {

    if (key == GLUT_KEY_RIGHT) {
        sceneKey++;
        sceneKey = min(sceneKey, 5);

        PlaySound(NULL, NULL, SND_ASYNC | SND_PURGE);
        glutIdleFunc(NULL); // Stop the idle function if it was running
        glutKeyboardFunc(NULL); // Clear the keyboard function to avoid conflicts
        // Reset the scene display
        displayScene(sceneKey);

    } else if (key == GLUT_KEY_LEFT) {
        sceneKey--;
        sceneKey = max(sceneKey, 1);

        PlaySound(NULL, NULL, SND_ASYNC | SND_PURGE);
        glutIdleFunc(NULL); // Stop the idle function if it was running
        glutKeyboardFunc(NULL); // Clear the keyboard function to avoid conflicts
        // Reset the scene display
        displayScene(sceneKey);

        if (Scene1::instance != nullptr) {
            Scene1::instance->pause = true; // Pause the scene when going back
        }
        if (Scene4::instance != nullptr) {
            Scene4::instance->pause = true;
        }
    }
    // pause any scene that is not the current one
    if (sceneKey != 1 && Scene1::instance != nullptr) {
        Scene1::instance->pause = true; // Pause Scene 1
    }
    if (sceneKey != 4 && Scene4::instance != nullptr) {
        Scene4::instance->pause = true; // Pause Scene 4
    }
    glutPostRedisplay(); // Request a redraw of the current window
}

void mainScene() {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Background color
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer (background)

    glColor4f(0.0f, 0.0f, 0.0f, 1.0f); // Set text color to black
    glBegin(GL_QUADS);
        glVertex2f(-1.0f, -1.0f); // Bottom left
        glVertex2f(1.0f, -1.0f);  // Bottom right
        glVertex2f(1.0f, 1.0f);   // Top right
        glVertex2f(-1.0f, 1.0f);  // Top left
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f);

    // renderBitmapString(-0.19f, 0.05f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Ashes and Echoes");
    // renderBitmapString(-0.17f, -0.05f, 0.0f, GLUT_BITMAP_HELVETICA_18, "Scene 3: The Fall");
    // renderBitmapString(-0.18f, -0.15f, 0.0f, GLUT_BITMAP_HELVETICA_12, "Created by: Md Hasib Askari");
    // renderBitmapString(-0.18f, -0.5f, 0.0f, GLUT_BITMAP_HELVETICA_12, "Press 'Right Arrow' to continue");


    glFlush(); // Render now

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

int main(int argc, char** argv) {
    // Initialize GLUT and create the window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Ashes and Echoes");

    // Control Scene
    glutDisplayFunc(mainScene);
    glutSpecialFunc(changeScene);
    glutReshapeFunc(reshape);

    // Start the main loop
    glutMainLoop();
    return 0;
}
