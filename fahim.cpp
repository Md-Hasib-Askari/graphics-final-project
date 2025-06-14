#include <windows.h>

#include <GL/glut.h>
#include <math.h>
#include <iostream>

#define PI 3.14159265358979323846
#include <windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

using namespace std;

// Window size
int windowWidth = 1280;
int windowHeight = 720;

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
void sound()
{
    PlaySound("mixkit-urban-park-and-traffic-2932.wav", NULL, SND_ASYNC|SND_FILENAME|SND_LOOP);

}
void initGL()
 {
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Background color
}
void renderBitmapString(float x, float y, float z, void *font, const char *string)
{
    const char *c;
    glRasterPos3f(x, y, z);
    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
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

    //cloud
    if(cloudPosition1 > 2.02f)
    {
        cloudPosition1 = -0.58f;

    }
    cloudPosition1 += cloudSpeed;
   // cout << cloudPosition1 << endl;


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

   if(busPosition<-1.90)
   {
        busPosition=1.0f;
   }
    busPosition-=busSpeed;

     i += (busSpeed / wheelRadius1) * (180.0f / 3.1416f);




    glutPostRedisplay();
    glutTimerFunc(100, update, 0);



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
void busWindow(float x, float y)
{
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
void bus()
{

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


void cloudAnimation()
{
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
void carAnimation()
{
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





    glPopMatrix();


}
void busAnimation()
{
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
    glPopMatrix();


}
void hill()
{
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
    //glVertex2f(-0.052, 0.50);
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
void tree1()
{

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
void buildingWindow(float x, float y)
{
    glBegin(GL_POLYGON);
        glColor3f(0.2157f, 0.2667f, 0.1922f);  // Polygon color
        glVertex2f(x - 0.747f, y + 0.427f);  // Vertex 1
        glVertex2f(x - 0.715f, y + 0.427f);  // Vertex 2
        glVertex2f(x - 0.715f, y + 0.371f);  // Vertex 3
        glVertex2f(x - 0.747f, y + 0.371f);  // Vertex 4
    glEnd();
}


void building1()
{

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
void building2Window(float x, float y)

{
    glBegin(GL_POLYGON);
    glColor3f(0.231f, 0.255f, 0.192f);
    glVertex2f(x+0.486, y+0.308);
    glVertex2f(x+0.519, y+0.308);
    glVertex2f(x+0.519, y+0.249);
    glVertex2f(x+0.486, y+0.249);
    glEnd();


}
void building2()
{
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
void building3Window(float x, float y)
{
    glBegin(GL_POLYGON);
    glColor3f(0.263f, 0.249f, 0.125f);
    glVertex2f(x+ 0.711, y+0.443);
    glVertex2f(x+0.711, y+0.391);
    glVertex2f(x+0.753, y+0.391);
    glVertex2f(x+0.753,y+0.443);
    glEnd();

}
void building3()
{

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
void tree2()
{
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
void bigTree()
{

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


void house ()
{
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
    //glEnd();

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
void house2Window(float x, float y)
{

    glBegin(GL_POLYGON);
    glColor3f(0.227f, 0.565f, 0.654f);
    glVertex2f(x+0.60, y+0.020);
    glVertex2f(x+ 0.686, y+0.020);
    glVertex2f(x+ 0.686, y+0.10);
    glVertex2f(x+0.60, y+0.10);
    glEnd();
}
void house2()
{

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
void poll(float x, float y)
{
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
void grass(float x, float y)
{
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
void roadsidetree()
{
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
void park()
{
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
void roadLine(float x, float y)
{

    glBegin(GL_POLYGON);
    glColor3f(0.851f, 0.717f, 0.361f);
    glVertex2f(x+(-0.386), y+(-0.204));
    glVertex2f(x+(-0.283), y+(-0.204));
    glVertex2f(x+(-0.283), y+(-0.223));
    glVertex2f(x+(-0.386), y+(-0.223));
    glEnd();

}
void roaAndPark()
{


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
    glBegin(GL_POLYGON);\
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

void sun()
{
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
void backGroundSky()
{

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


// Initialization

void Idle()
{
    glutPostRedisplay();//// marks the current window as needing to be redisplayed
}



// Display callback
void display() {
    glClear(GL_COLOR_BUFFER_BIT); // Clear the screen
    //sky blue back groud
    glBegin(GL_POLYGON);
   glColor3f(0.196f, 0.643f, 0.659f);
   glVertex2f(-1,-1);
   glVertex2f(-1,1);
   glVertex2f(1,1);
   glVertex2f(1,-1);

    glEnd();
   backGroundSky();
   roaAndPark();
    glFlush();
    glutSwapBuffers(); // Swap buffers (double buffering)
}


void SceneInfoDisplay()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT); // Clear the color buffer (background)


    glColor3f(1.0f, 1.0f, 1.0f);

    renderBitmapString(-0.155f, 0.05f, 0.0f, GLUT_BITMAP_TIMES_ROMAN_24, "Ashes and Echoes");
    renderBitmapString(-0.17f, -0.05f, 0.0f, GLUT_BITMAP_HELVETICA_18, "Scene 1:Peaceful vibrations");




    glFlush(); // Render now
    glutSwapBuffers();

}
void changeDisplay(int key, int x, int y)
{
    glutPostRedisplay();
    switch(key)
    {
        case GLUT_KEY_RIGHT:

            cout << "Right clicked\n";
            glutDisplayFunc(display);
            sound();
	        glutTimerFunc(100, update, 0);
            break;
    }

}




// Window resize callback
void reshape(int width, int height)
{
    windowWidth = width;
    windowHeight = height;
    glViewport(0, 0, windowWidth, windowHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1, 1, -1, 1); // Orthographic 2D projection
    glMatrixMode(GL_MODELVIEW);
}


// Entry point
int main(int argc, char** argv)
{
    glutInit(&argc, argv);                      // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);// Double buffer, RGB mode
    glutInitWindowSize(windowWidth, windowHeight);
    glutCreateWindow("Scene 1"); // Create window

    glutReshapeFunc(reshape);   // Register reshape callback

    initGL();
                   // Set initial OpenGL state
    glutDisplayFunc(SceneInfoDisplay); // Register display callback handler for window re-paint
    glutIdleFunc(Idle);
    glutSpecialFunc(changeDisplay);
    glutMainLoop();
    return 0;
}
