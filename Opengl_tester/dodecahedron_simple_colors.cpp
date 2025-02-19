#include "common_opengl.h"

#define phi 1.618033989
#define psi 0.618033989
#define PI 3.1415926535

GLfloat angle = 0.0f;

int faces[12][5] = {
    {0, 16, 2, 10, 8}, {0, 8, 4, 14, 12}, {16, 17, 1, 12, 0}, {1, 9, 11, 3, 17},
    {1, 12, 14, 5, 9}, {2, 13, 15, 6, 10}, {13, 3, 17, 16, 2}, {3, 11, 7, 15, 13},
    {4, 8, 10, 6, 18}, {14, 5, 19, 18, 4}, {5, 19, 7, 11, 9}, {15, 7, 19, 18, 6}
};

double points[20][3] = {
    {1, 1, 1}, {1, 1, -1}, {1, -1, 1}, {1, -1, -1}, {-1, 1, 1}, {-1, 1, -1}, {-1, -1, 1}, {-1, -1, -1},
    {0, psi, phi}, {0, psi, -phi}, {0, -psi, phi}, {0, -psi, -phi},
    {psi, phi, 0}, {psi, -phi, 0}, {-psi, phi, 0}, {-psi, -phi, 0},
    {phi, 0, psi}, {phi, 0, -psi}, {-phi, 0, psi}, {-phi, 0, -psi}
};

GLfloat colors[12][3] = {
    {1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {1, 1, 0},
    {1, 0, 1}, {0, 1, 1}, {0.5, 0.5, 0}, {0.5, 0, 0.5},
    {0, 0.5, 0.5}, {0.75, 0.25, 0}, {0.25, 0.75, 0}, {0, 0.25, 0.75}
};

void reshape(int w, int h){
    double aspect = double(w) / double(h);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glScalef(0.5, 0.5, 0.5);
    gluPerspective(45.0, aspect, 1.0, 20.0);
    glMatrixMode(GL_MODELVIEW);
}

void idle(){
    angle += 2.0;
    if (angle >= 360.0f) angle = 0.0f;
    glutPostRedisplay();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 7.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glRotated(angle, 1.0, 1.0, 0.0);

    for (int i = 0; i < 12; i++) {
        glColor3fv(colors[i]);
        glBegin(GL_POLYGON);
        for (int x = 0; x < 5; x++)
            glVertex3dv(points[faces[i][x]]);
        glEnd();

        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_LINE_STRIP);
        for (int x = 0; x < 5; x++)
            glVertex3dv(points[faces[i][x]]);
        glVertex3dv(points[faces[i][0]]);
        glEnd();
    }
    glutSwapBuffers();
}

void glut_dodecahedron(int argc, char* argv[]) { 
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("Dodecahedron");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutMainLoop();
}

int main ( int argc, char *argv[] ) {
  std::cout << "Starting program...";

  glut_dodecahedron(argc, argv);

  std::cout << "...program completed\n";
  return 0;
}
