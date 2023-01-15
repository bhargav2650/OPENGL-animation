#define GL_SILENCE_DEPRECATION
#define _USE_MATH_DEFINES
#include <stdlib.h>
#include <stdio.h>
#include<iostream>
#include <glut.h>
#include<string>
#include<sstream>
#include<time.h>
#include<math.h>
#include<cmath>
#include<chrono>
#include<thread>
#include<glm/glm.hpp>
#include<vector>
#include<fstream>
#include<windows.graphics.h>
GLuint index;
using namespace std;
float x[] = { (float)rand()/RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX };
float y[] = { (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX };
float z[] = { (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX };
float colorarm[786];
float position1x = 0;
float position1y = 0;
float position1z = 0;
float position2x = 0;
float position2y = 0;
float position2z = 0;
float position3x = 0;
float position3y = 0;
float position3z = 0;
float scale1 = 5;
float scale2 = 1;
float scale3 = 1;
float r1y=0, r2y=0, r3y = 0;
float r1x = 0, r2x = 0, r3x = 0;
float r1z = 0, r2z = 0, r3z = 0;
int r1 = 0;
int r2 = 0;
int r3 = 0;
float angt = 0;
float angp = 0;
float ang1r = 0;
float ang1s = M_PI_2;
float ang2r = M_PI_2;
float ang2s = M_PI_2;
float ang3r = M_PI_4;
float ang3s = M_PI_2;
bool checkclicked1 = false, checkclicked2 = false, checkclicked3 = false;
float scalecone = 1;
//printing SRN and Name
void disptext(int x, int y, int z, string str)
{
    glRasterPos3f(x, y, z);
    int len = (int)str.length();
    for (int i = 0; i < len; i++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
    }
};
//Mouse click event handling
void onclick(int button, int state, int x, int y) {
    if (state != GLUT_DOWN)
        return;
    GLfloat window_width = glutGet(GLUT_WINDOW_WIDTH);
    GLfloat window_height = glutGet(GLUT_WINDOW_HEIGHT);
    glReadPixels(x, window_height - y + 1, 1, 1, GL_STENCIL_INDEX, GL_INT, &index);
    printf("stencil index %u\n", index);
    if (index == 1)
    {
        checkclicked1 = !checkclicked1;
    }
    else if (index == 2)
    {
        checkclicked2 = !checkclicked2;
    }
    else if(index==3)
    {
        checkclicked3 = !checkclicked3;
    }
    glutPostRedisplay();
}
//colloision between the objects handling
void colloide(int i, int j)
{
    if (i == 1 && j == 2)
    {
        ang1r = (((float)rand() / RAND_MAX) * 360);
        ang1r *= M_PI / 180;
        ang1s = (((float)rand() / RAND_MAX) * 360);
        ang1s *= M_PI / 180;
        ang2r = (((float)rand() / RAND_MAX) * 360);
        ang2r *= M_PI / 180;
        ang2s = (((float)rand() / RAND_MAX) * 360);
        ang2s *= M_PI / 180;
        position1x += 0.5 * sin(ang1s) * cos(ang1r);
        position1y += 2 * sin(ang1s) * sin(ang1r);
        position1z += 2 * cos(ang1s);
        position2x += 2 * sin(ang2s) * cos(ang2r);
        position2y += 2 * sin(ang2s) * sin(ang2r);
        position2z += 2 * cos(ang2s);

    }
    else if (i == 1 && j == 3)
    {
        ang1r = (((float)rand() / RAND_MAX) * 360);
        ang1r *= M_PI / 180;
        ang1s = (((float)rand() / RAND_MAX) * 360);
        ang1s *= M_PI / 180;
        ang3r = (((float)rand() / RAND_MAX) * 360);
        ang3r *= M_PI / 180;
        ang3s = (((float)rand() / RAND_MAX) * 360);
        ang3s *= M_PI / 180;
        position1x += 2 * sin(ang1s) * cos(ang1r);
        position1y += 2 * sin(ang1s) * sin(ang1r);
        position1z += 2 * cos(ang1s);
        position3x += 2 * sin(ang3s) * cos(ang3r);
        position3y += 2 * sin(ang3s) * sin(ang3r);
        position3z += 2 * cos(ang3s);
    }
    else
    {
        ang2r = (((float)rand() / RAND_MAX) * 360);
        ang2r *= M_PI / 180;
        ang2s = (((float)rand() / RAND_MAX) * 360);
        ang2s *= M_PI / 180;
        ang3r = (((float)rand() / RAND_MAX) * 360);
        ang3r *= M_PI / 180;
        ang3s = (((float)rand() / RAND_MAX) * 360);
        ang3s *= M_PI / 180;
        position3x += 2 * sin(ang3s) * cos(ang3r);
        position3y += 2 * sin(ang3s) * sin(ang3r);
        position3z += 2 * cos(ang3s);
        position2x += 2 * sin(ang2s) * cos(ang2r);
        position2y += 2 * sin(ang2s) * sin(ang2r);
        position2z += 2 * cos(ang2s);
    }
}
//cross product for normals
void cross(float a, float b, float c, float d, float e, float f, float g, float h, float i)
{
    float a1 = a - d;
    float b1 = b - e;
    float c1 = c - f;
    float d1 = g - d;
    float e1 = h - e;
    float f1 = i - f;
    float vect_A[] = { a1,b1,c1 };
    float vect_B[] = { d1,e1,f1 };
    float crp[3];
    crp[0] = vect_A[1] * vect_B[2] - vect_A[2] * vect_B[1];
    crp[1] = vect_A[2] * vect_B[0] - vect_A[0] * vect_B[2];
    crp[2] = vect_A[0] * vect_B[1] - vect_A[1] * vect_B[0];
    double normal = sqrt(crp[0] * crp[0] + crp[1] * crp[1] + crp[2] * crp[2]);
    glNormal3f(crp[0] / normal, crp[1] / normal, crp[2] / normal);
}
void setMaterial(GLfloat ambientR, GLfloat ambientG, GLfloat ambientB, GLfloat diffuseR, GLfloat diffuseG, GLfloat diffuseB, GLfloat specularR, GLfloat specularG, GLfloat specularB, int shine);
void cone_custom();
void tetrahedron();
void arm_custom();
void cylinder_custom();
float camx = 0, camy = 0, camz =20;
float upx = 0, upy = 1, upz = 0;
float lox = 0, loy = 0, loz = 0;
//rotation for camera in theta angle spherical coordinates
void camerarottheta(float x) 
{
    angt -= x;
    camx = 20 * sin(angt) * cos(angp);
    camy = 20 * sin(angt) * sin(angp);
    camz = 20 * cos(angt);
}
//rotation for camera in theta angle spherical coordinates
void cameraphi(float z) 
{
    angp -= z;
    camx = 20 * sin(angt) * cos(angp);
    camy = 20 * sin(angt) * sin(angp);
    camz = 20 * cos(angt);
}
//keyboard press event handling function
void pressKeys(unsigned char key, int cursor_x, int cursor_y) {
    //key for camera rotation
    switch (key) 
    {
    case 'A':
    case 'a':
        camerarottheta(-0.05);
        break;
    case 'D':
    case 'd':
        camerarottheta(0.05);
        break;
    case 'W':
    case 'w':
        cameraphi(0.1);
        break;
    case 'S':
    case 's':
        cameraphi(-0.1);
        break;
    //keys for scaling
    case 'M':
    case 'm':
        if (checkclicked3 == true)
        {
                if (scale1 < 20)
                {
                    scale1 += 0.2;
                }
        }
        if (checkclicked1 == true)
        {
            if (scale2 < 15)
            {
                scale2 += 0.2;
            }
        }
        if (checkclicked2 == true)
        {
                if(scale3 < 2.6)
                {
                    scale3 += 0.2;
                }
        }
        break;
    case 'N':
    case 'n':
        if (checkclicked3 == true)
        {
            if (scale1 >1)
            {
                scale1 -= 0.2;
            }
        }
        if (checkclicked1 == true)
        {
            if (scale2 > 1)
            {
                scale2 -= 0.2;
            }
        }
        if (checkclicked2 == true)
        {
            if (scale3 > 1)
            {
                scale3 -= 0.2;
            }
        }
        break;
    //keys for translation
    case 'I':
    case 'i':
        if (checkclicked3 == true)
        {
            if (((position1x * position1x) + (position1y * position1y) + (position1z * position1z)) < 380)
            {
                position1y += 0.2;
            }
        }
        if (checkclicked1 == true)
        {
            if (((position2x * position2x) + (position2y * position2y) + (position2z * position2z)) < 380)
            {
                position2y += 0.2;
            }
        }
        if (checkclicked2 == true)
        {
            if (((position3x * position3x) + (position3y * position3y) + (position3z * position3z)) < 380)
            {
                position3y += 0.2;
            }
        }
        break;
    case 'K':
    case 'k':
        if (checkclicked3 == true)
        {
            if (((position1x * position1x) + (position1y * position1y) + (position1z * position1z)) < 380)
            {
                position1y -= 0.2;
            }
        }
        if (checkclicked1 == true)
        {
            if (((position2x * position2x) + (position2y * position2y) + (position2z * position2z)) < 380)
            {
                position2y -= 0.2;
            }
        }
        if (checkclicked2 == true)
        {
            if (((position3x * position3x) + (position3y * position3y) + (position3z * position3z)) < 380)
            {
                position3y -= 0.2;
            }
        }
        break;
    case 'J':
    case 'j':
        if (checkclicked3 == true)
        {
            if (((position1x * position1x) + (position1y * position1y) + (position1z * position1z)) < 380)
            {
                position1x -= 0.2;
            }
        }
        if (checkclicked1 == true)
        {
            if (((position2x * position2x) + (position2y * position2y) + (position2z * position2z)) < 380)
            {
                position2x -= 0.2;
            }
        }
        if (checkclicked2 == true)
        {
            if (((position3x * position3x) + (position3y * position3y) + (position3z * position3z)) < 380)
            {
                position3x -= 0.2;
            }
        }
        break;
    case 'L':
    case 'l':
        if (checkclicked3 == true)
        {
            if (((position1x * position1x) + (position1y * position1y) + (position1z * position1z)) < 380)
            {
                position1x += 0.2;
            }
        }
        if (checkclicked1 == true)
        {
            if (((position2x * position2x) + (position2y * position2y) + (position2z * position2z)) < 380)
            {
                position2x += 0.2;
            }
        }
        if (checkclicked2 == true)
        {
            if (((position3x * position3x) + (position3y * position3y) + (position3z * position3z)) < 380)
            {
                position3x += 0.2;
            }
        }
        break;
    case 'O':
    case 'o':
        if (checkclicked3 == true)
        {
            if (((position1x * position1x) + (position1y * position1y) + (position1z * position1z)) < 380)
            {
                position1z -= 0.2;
            }
        }
        if (checkclicked1 == true)
        {
            if (((position2x * position2x) + (position2y * position2y) + (position2z * position2z)) < 380)
            {
                position2z -= 0.2;
            }
        }
        if (checkclicked2 == true)
        {
            if (((position3x * position3x) + (position3y * position3y) + (position3z * position3z)) < 380)
            {
                position3z -= 0.2;
            }
        }
        break;
    case 'P':
    case 'p':
        if (checkclicked3 == true)
        {
            if (((position1x * position1x) + (position1y * position1y) + (position1z * position1z)) < 380)
            {
                position1z += 0.2;
            }
        }
        if (checkclicked1 == true)
        {
            if (((position2x * position2x) + (position2y * position2y) + (position2z * position2z)) < 380)
            {
                position2z += 0.2;
            }
        }
        if (checkclicked2 == true)
        {
            if (((position3x * position3x) + (position3y * position3y) + (position3z * position3z)) < 380)
            {
                position3z += 0.2;
            }
        }
        break;
    //keys for rotation about axes
    case 'Y':
    case 'y':
        if (checkclicked3 == true)
        {
            r1y += 0.5;
        }
        if (checkclicked1 == true)
        {
            r2y += 0.5;
        }
        if (checkclicked2 == true)
        {
            r3y += 0.5;
        }
        break;
    case 'X':
    case 'x':
        if (checkclicked3 == true)
        {
            r1x += 0.5;
        }
        if (checkclicked1 == true)
        {
            r2x += 0.5;
        }
        if (checkclicked2 == true)
        {
            r3x += 0.5;
        }
        break;
    case 'Z':
    case 'z':
        if (checkclicked3 == true)
        {
            r1z += 0.5;
        }
        if (checkclicked1 == true)
        {
            r2z += 0.5;
        }
        if (checkclicked2 == true)
        {
            r3z += 0.5;
        }
        break;
        glutPostRedisplay();
    }
}
//lighting of objects
void initLight()
{
    GLfloat ambient[] = { 2, 1, 1, 1 };
    GLfloat diffuse[] = { 2, 0.5, 0.5 };
    GLfloat specular[] = { 30, 20, 20 };
    GLfloat position[] = { 30,20,20,1 };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glLightfv(GL_LIGHT0, GL_POSITION, position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);

    glEnable(GL_COLOR_MATERIAL);
}
void timer(int);
//reading from stl file for coordinates into csv file
void readf(string fname, vector<vector<float>>& points, vector<vector<int>>& connect, vector<vector<float>>& normal)
{
    // vector<vector<float>> points ;
    // vector<vector<int>> connect ;
    // vector<vector<float>> normal ;
    vector<float> row;
    string line, word;

    ifstream file;
    file.open(fname);
    if (file.is_open())
    {
        while (getline(file, line))
        {
            row.clear();

            stringstream str(line);

            int count = 0;
            while (getline(str, word, ','))
            {
                //float data = stod(word);
                float data;
                stringstream ss;
                if (word != "")
                {
                    ss << word;
                    ss >> data;
                    row.push_back(data);
                }
                else

                    row.push_back(0);

            }
            vector<float> temp1 = { row[0],row[1],row[2] };
            points.push_back(temp1);
            temp1 = { row[3],row[4],row[5] };
            vector<int>temp1int(temp1.begin(), temp1.end());
            connect.push_back(temp1int);
            temp1 = { row[6],row[7],row[8] };
            normal.push_back(temp1);

        }
        points[0][0] = -0.22745657;

    }
    else
        cout << "Could not open the file\n";
    file.close();
    for (int i = points.size() - 1; i >= 0; i--)
    {
        vector<float> vect = { 0,0,0 };
        if (points[i] == vect)
        {
            points.pop_back();
        }
    }
}
// house object rendering
void house_custom()
{
    cone_custom();
    cylinder_custom();
    return;
}
// display function to display the objects
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_STENCIL_TEST);
    glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
    glClear(GL_STENCIL_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    //    glLoadIdentity();
    //    gluPerspective(80, 1, 0.5, 50);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    setMaterial(0.2, 0.2, 0.2, 0.3, 0.3, 0.3, 0.4, 0.4, 0.4, 40);
    //    glRotatef(3, 0,0,1);
    glStencilMask(0xFF);
    glColor3f(z[0], z[1], z[0]);
    gluLookAt(camx, camy, camz, lox, loy, loz, upx, upy, upz);
    glTranslatef(0,0,0);
    glutWireSphere(20, 10, 10);
    //glRotatef(0.01,0,1,0);
    //glRotatef(3,0,-1,-1);
    disptext(5, 5, 5, "Made By BHARGAV M V");
    disptext(5, 3, 5, "PES1UG20CS660");
    glPushMatrix();
    glTranslatef(position2x, position2y, position2z);
    glClear(GL_STENCIL_BUFFER_BIT);
    glStencilFunc(GL_ALWAYS, 1, 0xFF);
    glStencilMask(0xFF);
    glEnable(GL_DEPTH_TEST);
    glScalef(scale2, scale2, scale2);
    setMaterial(1, 1, 1, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 10);
    glRotatef(r2y, 0, 1, 0);
    glRotatef(r2x, 1, 0, 0); 
    glRotatef(r2z, 0, 0, 1);
    tetrahedron();
    glPopMatrix();
    glPushMatrix();
    setMaterial(1, 1, 1, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 10);
    glTranslatef(position3x, position3y, position3z);
    //glClear(GL_STENCIL_BUFFER_BIT);
    glStencilFunc(GL_ALWAYS, 2, 0xFF);
    glStencilMask(0xFF);
    glScalef(scale3, scale3, scale3);
    glRotatef(r3y, 0, 1, 0);
    glRotatef(r3x, 1, 0, 0);
    glRotatef(r3z, 0, 0, 1);
    house_custom();
    glPopMatrix();
    glPushMatrix();
    setMaterial(1, 1, 1, 0.5, 0.5, 0.5, 0.5, 0.5, 0.5, 10);
    glTranslatef(position1x, position1y, position1z);
    glScalef(scale1,scale1,scale1);
    glRotatef(r1y, 0, 1, 0);
    glRotatef(r1x, 1, 0, 0);
    glRotatef(r1z, 0, 0, 1);
    //glClear(GL_STENCIL_BUFFER_BIT);
    glStencilFunc(GL_ALWAYS, 3, 0xFF);
    glStencilMask(0xFF);
    arm_custom();
    glPopMatrix();
    glFlush();
    glutSwapBuffers();
}
int main(int argc, char* argv[])
{
    
    for (int i = 0; i < 786; i++)
    {
        colorarm[i] = (float)rand() / RAND_MAX;
    }
    glutInit(&argc, argv);
    glutInitWindowSize(1000, 1000);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH |GLUT_STENCIL);
    glutCreateWindow("ARVR ASSIGNMENT PES1UG20CS660");
    glEnable(GL_DEPTH_TEST);
    //    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    //    glClearColor(1, 1, 1, 0);
    initLight();
    glutKeyboardFunc(processNormalKeys);
    glutDisplayFunc(display);
    //glutIdleFunc(animation);
    glutTimerFunc(500,timer,0);
    glutKeyboardFunc(pressKeys);
    glutMouseFunc(onclick);
    glMatrixMode(GL_PROJECTION); // Select Projection Matrix
    glLoadIdentity();
    gluPerspective(90, 1, 0.5,900);
    glPointSize(1);
    glutMainLoop();
}
//lghting of material
void setMaterial(
    GLfloat ambientR, GLfloat ambientG, GLfloat ambientB,
    GLfloat diffuseR, GLfloat diffuseG, GLfloat diffuseB,
    GLfloat specularR, GLfloat specularG, GLfloat specularB,
    int shine)
{
    ///create "vectors" from the values for the light
    GLfloat ambient[] = { ambientR, ambientG, ambientB };
    GLfloat diffuse[] = { diffuseR, diffuseG, diffuseB };
    GLfloat specular[] = { specularR, specularG, specularB };

    glMaterialfv(GL_FRONT, GL_AMBIENT, ambient); //sets how ambience should work for the material
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse); //sets how diffuse should work for the material
    glMaterialfv(GL_FRONT, GL_SPECULAR, specular); //sets how specular should work for the material
    glMaterialf(GL_FRONT, GL_SHININESS, shine);
}
//rendering cone
void cone_custom()
{
    float deg = 0;
    srand(0);
    float prevX = 2, prevZ = 0;
    int i = 0;
    int r = 2; //radius of the circle which is at the bottom of the cone
    for (; deg < 360;)
    {
        if (i == 0)
        {
            prevX = r * cos(deg);
            prevZ = r * sin(deg);
            i++;
            deg += 0.1;
            continue;
        }
        glBegin(GL_TRIANGLES);
        glColor3f(1, 1, 1);
        glVertex3f(0, 8, 0);
        glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
        glVertex3f(prevX, 5, prevZ);
        glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
        glVertex3f(r * cos(deg), 5, r * sin(deg));
        cross(0, 8, 0, prevX, 5, prevZ, r * cos(deg), 5, r * sin(deg));
        glEnd();
        prevX = r * cos(deg);
        prevZ = r * sin(deg);
        deg += 0.2;
    }
}
//reading and rendering triangles from points in csv file
void arm_custom()
{
    vector<vector<float>> pointsbd;
    vector<vector<int>> connectbd;
    vector<vector<float>> normalbd;
    readf("C:/Users/Bhargav/OneDrive/Desktop/Assignment__PES1UG20CS660/Bhagi.csv", pointsbd, connectbd, normalbd);

    cout << "\n \n \n";
    srand((unsigned int)time(NULL));
    int count = 0;
    for (int i = 0; i < connectbd.size(); i++)
    {
        glBegin(GL_TRIANGLES);

        glColor3f(colorarm[i], colorarm[i+1], colorarm[i+2]);
        count = 0;
        glNormal3f(normalbd[i][0], normalbd[i][1], normalbd[i][2]);
        glVertex3f(pointsbd[connectbd[i][0] - 1][0],
            pointsbd[connectbd[i][0] - 1][1],
            pointsbd[connectbd[i][0] - 1][2]
        );

        glVertex3f(pointsbd[connectbd[i][1] - 1][0],
            pointsbd[connectbd[i][1] - 1][1],
            pointsbd[connectbd[i][1] - 1][2]
        );

        glVertex3f(pointsbd[connectbd[i][2] - 1][0],
            pointsbd[connectbd[i][2] - 1][1],
            pointsbd[connectbd[i][2] - 1][2]);
        glEnd();
    }
    glFlush();
}
//rendering tetrahedron
void tetrahedron()
{
    
    glBegin(GL_TRIANGLES);
    //front triangle
    glColor3f(x[0],x[1],x[2]);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    cross(0, 1, 0, -1, -1, 0, 1, -1, 0);

    //right side triangle
    glColor3f(y[0], y[1], y[2]);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -1.0f, -1.0f);
    cross(1, -1, 0, 0, 1, 0, 0, -1, -1);

    //left side triangle
    glColor3f(z[0], z[1], z[2]);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glVertex3f(0.0f, 1.0f, 0.0f);
    glVertex3f(0.0f, -1.0f, -1.0f);
    cross(-1, -1, 0, 0, 1, 0, 0, -1, -1);

    //bottom triangle
    glColor3f(x[1], x[0], x[2]);
    glVertex3f(-1.0f, -1.0f, 0.0f);
    glVertex3f(1.0f, -1.0f, 0.0f);
    glVertex3f(0.0f, -1.0f, -1.0f);
    cross(-1, -1, 0, 1, -1, 0, 0, -1, -1);
    glEnd();
    //RDU
}
//rendering cylinder
void cylinder_custom()
{
    float deg = 0;
    srand(0);
    float prevX = 2, prevZ = 0;
    int i = 0;
    float r = 1.8; //radius of the circle which is at the bottom of the cone
    for (; deg < 360;)
    {
        if (i == 0)
        {
            prevX = r * cos(deg);
            prevZ = r * sin(deg);
            i++;
            deg += 0.1;
            continue;
        }
        glBegin(GL_TRIANGLES);
        glColor3f(1, 1, 1);
        glVertex3f((r * cos(deg) + prevX) / 2, 5, (r * sin(deg) + prevZ) / 2);
        glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
        glVertex3f(prevX, 0, prevZ);
        glColor3f((float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX);
        glVertex3f(r * cos(deg), 0, r * sin(deg));
        cross((r * cos(deg) + prevX) / 2, 5, (r * sin(deg) + prevZ) / 2, prevX, 0, prevZ, r * cos(deg), 0, r * sin(deg));
        glEnd();
        prevX = r * cos(deg);
        prevZ = r * sin(deg);
        deg += 0.1;
    }
}
//function to handle the random motion of the objects and the colloision of the objects on the surface of the sphere
void timer(int)
{
    glutPostRedisplay();
    glutTimerFunc(500/30,timer,0);
    //if (((position1x*position1x)+(position1y*position1y)+(position1z*position1z))<100)
    //{
    //   position1x += 0.5*sin(ang1s) * cos(ang1r);
    //   position1y += 0.5*sin(ang1s) * sin(ang1r);
    //   position1z += 0.5 * cos(ang1s);
    //   
    //}
    //else 
    //{
    //    srand((unsigned int)time(NULL));
    //    ang1r += (((float)rand() / RAND_MAX) * 180)+90;
    //    ang1s += (((float)rand() / RAND_MAX) * 180) + 90;
    //    /*if (sin(ang1r) < 0)
    //        ang1s *= -1;*/
    //        position1x += 0.5 * sin(ang1s) * cos(ang1r);
    //        position1y += 0.5 * sin(ang1s) * sin(ang1r);
    //        position1z += 0.5 * cos(ang1s);
    //    
    //    //printf("%f %f %f %f", position1x, position1y, position1z, ((position1x * position1x) + (position1y * position1y) + (position1z * position1z)));
    //}
    if (((position1x * position1x) + (position1y * position1y) + (position1z * position1z)) < 380)//handling motion for arm
    {
        if (checkclicked3 == false)
        {
            {
                if ((((position1x - position2x) * (position1x - position2x)) + ((position1y - position2y) * (position1y - position2y)) + ((position1z - position2z) * (position1z - position2z))) < 10)
                {
                    colloide(1, 2);
                }
                else if ((((position1x - position3x) * (position1x - position3x)) + ((position1y - position3y) * (position1y - position3y)) + ((position1z - position3z) * (position1z - position3z))) < 10)
                {
                    colloide(1, 3);
                }
                else
                {
                    position1x += 0.5 * sin(ang1s) * cos(ang1r);
                    position1y += 0.5 * sin(ang1s) * sin(ang1r);
                    position1z += 0.5 * cos(ang1s);
                }
            }
        }
    }
    else//when object colloides with the surface of the sphere
    {
        float x3, y3, z3;
        if (r1 == 0)
        {
            srand((unsigned int)time(NULL));
            ang1r = (((float)rand() / RAND_MAX) * 180) + 90 + (180 * ang1r / M_PI);
            ang1r *= M_PI / 180;
            ang1s = (((float)rand() / RAND_MAX) * 360);
            ang1s *= M_PI / 180;
            r1 = 1;
        }
        x3 = 1 * sin(ang1s) * cos(ang1r) + position1x;
        y3 =  1 * sin(ang1s) * sin(ang1r) + position1y;
        z3 = 1 * cos(ang1s) + position1z;
        if (x3 * x3 + y3 * y3 + z3 * z3 > ((position1x * position1x) + (position1y * position1y) + (position1z * position1z)))
        {
            r1 = 0;
        }
        else
        {
            position1x = x3;
            position1y = y3;
            position1z = z3;
        }
    }
    if (((position2x * position2x) + (position2y * position2y) + (position2z * position2z)) < 380)//handling tetrahedron motion
    {
        if (checkclicked1 == false)
        {
            if ((((position2x - position3x) * (position2x - position3x)) + ((position2y - position3y) * (position2y - position3y)) + ((position2z - position3z) * (position2z - position3z))) < 10)
            {
                colloide(2, 3);
            }
            else
            {
                position2x += 0.5 * sin(ang2s) * cos(ang2r);
                position2y += 0.5 * sin(ang2s) * sin(ang2r);
                position2z += 0.5 * cos(ang2s);
            }
        }
    }
    else//when object colloides with the surface of the sphere
    {
        float x3, y3, z3;
        if (r2 == 0)
        {
            ang2r = (((float)rand() / RAND_MAX) * 180) + 90 + (180 * ang2r / M_PI);
            ang2r *= M_PI / 180;
            ang2s = (((float)rand() / RAND_MAX) * 360);
            ang2s *= M_PI / 180;
            r2 = 1;
        }
        x3 = 1 * sin(ang2s) * cos(ang2r) + position2x;
        y3 = 1 * sin(ang2s) * sin(ang2r) + position2y;
        z3 = 1 * cos(ang2s) + position2z;
        if (x3 * x3 + y3 * y3 + z3 * z3 > ((position2x * position2x) + (position2y * position2y) + (position2z * position2z)))
        {
            r2 = 0;
        }
        else
        {
            position2x = x3;
            position2y = y3;
            position2z = z3;
        }
    }
    if (((position3x * position3x) + (position3y * position3y) + (position3z * position3z)) < 380)//handling cylindrical house motion
    {
        if (checkclicked2 == false)
        {
            position3x += 0.5 * sin(ang3s) * cos(ang3r);
            position3y += 0.5 * sin(ang3s) * sin(ang3r);
            position3z += 0.5 * cos(ang3s);
        }
    }
    else//when object colloides with the surface of the sphere
    {
        float x3, y3, z3;
        if (r3 == 0)
        {
            ang3r = (((float)rand() / RAND_MAX) * 180) + 90 + (180 * ang3r / M_PI);
            ang3r *= M_PI / 180;
            ang3s = (((float)rand() / RAND_MAX) * 360);
            ang3s *= M_PI / 180;
            r3 = 1;
        }
        x3 = 1 * sin(ang3s) * cos(ang3r)+position3x;
        y3= 1 * sin(ang3s) * sin(ang3r) +position3y;
        z3= 1 * cos(ang3s)+position3z;
        if (x3 * x3 + y3 * y3 + z3 * z3 > ((position3x * position3x) + (position3y * position3y) + (position3z * position3z)))
        {
            r3 = 0;
        }
        else
        {
            position3x = x3;
            position3y = y3;
            position3z = z3;
        }
        //{
    //    srand((unsigned int)time(NULL));
    //    ang1r += (((float)rand() / RAND_MAX) * 180)+90;
    //    ang1s += (((float)rand() / RAND_MAX) * 180) + 90;
    //    /*if (sin(ang1r) < 0)
    //        ang1s *= -1;*/
    //        position1x += 0.5 * sin(ang1s) * cos(ang1r);
    //        position1y += 0.5 * sin(ang1s) * sin(ang1r);
    //        position1z += 0.5 * cos(ang1s);
    //    
    //    //printf("%f %f %f %f", position1x, position1y, position1z, ((position1x * position1x) + (position1y * position1y) + (position1z * position1z)));
    //}
    }
}