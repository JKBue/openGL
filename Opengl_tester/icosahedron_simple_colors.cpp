#include "common_opengl.h"

#define PHI 1.61803398875  // Golden Ratio
#define INV_PHI (1.0 / PHI)

GLfloat angle = 0.0f;

// Corrected Icosahedron vertices based on three mutually orthogonal golden rectangles
double vertices[12][3] = {
    {-1, PHI, 0}, {1, PHI, 0}, {-1, -PHI, 0}, {1, -PHI, 0},
    {0, -1, PHI}, {0, 1, PHI}, {0, -1, -PHI}, {0, 1, -PHI},
    {PHI, 0, -1}, {PHI, 0, 1}, {-PHI, 0, -1}, {-PHI, 0, 1}
};

// Corrected Icosahedron faces  10 triangles, ensuring correct connections)
int faces [20][3] = {
    {0, 11, 5}, {0, 5, 1}, {0, 1, 7}, {0, 7, 10}, {0, 10, 11},
    {1, 5, 9}, {5, 11, 4}, {11, 10, 2}, {10, 7, 6}, {7, 1, 8},
    {3, 9, 4}, {3, 4, 2}, {3, 2, 6}, {3, 6, 8}, {3, 8, 9},
    {4, 9, 5}, {2, 4, 11}, {6, 2, 10}, {8, 6, 7}, {9, 8, 1}
};

GLfloat colors[20][3] = {
    {1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {1, 1, 0},
    {1, 0, 1}, {0, 1, 1}, {0.5, 0.5, 0}, {0.5, 0, 0.5},
    {0, 0.5, 0.5}, {0.75, 0.25, 0}, {0.25, 0.75, 0}, {0, 0.25, 0.75},
    {1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {1, 1, 0},
    {1, 0, 1}, {0, 1, 1}, {0.5, 0.5, 0}, {0.5, 0, 0.5},
};

void reshape(int w, int h) {
    double aspect = double(w) / double(h);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspect, 1.0, 10.0);
    glMatrixMode(GL_MODELVIEW);
}

void idle() {
    angle += 2.0;
    if (angle >= 360.0f) {
        angle = 0.0f;
    }
    glutPostRedisplay();
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 7.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glRotated(angle, 1.0, 1.0, 0.0);

    for (int i = 0; i < 20; i++) {
        glBegin(GL_TRIANGLES);
        glColor3fv(colors[i]);

        for (int x = 0; x < 3; x++) {
            glVertex3dv(vertices[faces[i][x]]);
        }
        glEnd();
    }
    glutSwapBuffers();
}

void glut_icosahedron(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("Icosahedron");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutMainLoop();
}

int main(int argc, char* argv[]) {
    std::cout << "Starting program\n";
    glut_icosahedron(argc, argv);
    std::cout << "...program completed\n";
    return 0;
}
