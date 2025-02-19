#include "common_opengl.h"

GLfloat angle = 0.0f;

int faces[12][4] = {
    { 0, 1, 3, 2 }, { 2, 3, 13, 4 }, { 4, 13, 11, 12 }, { 12, 11, 10, 8 },
    { 8, 10, 7, 6 }, { 6, 7, 1, 0 }, { 0, 5, 4, 2 }, { 5, 8, 6, 0 },
    { 8, 5, 4, 12 }, { 11, 9, 7, 10 }, { 7, 1, 3, 9 }, { 9, 3, 13, 11 }
};

double points[14][3] = {
    {0, 0, -4}, {2, -2, -2}, {-2, -2, -2}, {0, -4, 0},
    {-4, 0, 0}, {-2, 2, -2}, {2, 2, -2}, {4, 0, 0},
    {0, 4, 0}, {2, -2, 2}, {2, 2, 2}, {0, 0, 4},
    {-2, 2, 2}, {-2, -2, 2}
};

GLfloat colors[12][3] = {
    {0, 0.5, 0.5}, {0, 0, 1}, {0.25, 0.75, 0}, {0, 0.25, 0.75},
    {1, 0, 0}, {0, 1, 0}, {0.75, 0.25, 0}, {1, 1, 0},
    {1, 0, 1}, {0, 1, 1}, {0.5, 0.5, 0}, {0.5, 0, 0.5},
};

void reshape(int w, int h) {
    double aspect = double(w) / double(h);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, aspect, 1.0, 20.0);
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
    gluLookAt(0.0, 0.0, 11.0, 0.0, 0.0, 0.0, 0.0, 4.0, 0.0);
    glRotated(angle, 1.0, 1.0, 0.0);

    for (int i = 0; i < 12; i++) {
        glBegin(GL_QUADS);
        for (int x = 0; x < 5; x++) {
            // glColor3f((float)x / 3.0, 1.0 - (float)x / 3.0, 0.3 + ((float)(i % 3) / 3.0) * 0.7);
            if (i % 3 == 0) { 
                glColor3f((float)x / 3.0, 1.0 - (float)x / 4.0, ((float)(i % 5)));
            } else if (i % 3 == 1) { 
                glColor3f((float)x, 1.0 - (float)x / 3.0, ((float)(i % 5) / 5.0));
            } else if (i % 3 == 2) {
                glColor3f((float)x / 5.0, 1.0 - (float)x, ((float)(i % 5) / 2.0));
            } else if (i % 3 == 3) { 
                glColor3f((float)x / 2.0, 1.0 - (float)x / 5.0, ((float)(i % 5) / 4.0));
            } else { 
                glColor3f((float)x / 4.0, 1.0 - (float)x / 2.0, (float)(i % 5) / 3.0);
            }
            glVertex3dv(points[faces[i][x]]);
        }
        glEnd();

        glColor3f(0.0, 0.0, 0.0);
        glBegin(GL_LINE_STRIP);
        for (int x = 0; x < 5; x++) {
            glVertex3dv(points[faces[i][x]]);
        }
        glVertex3dv(points[faces[i][0]]);
        glEnd();
    }
    glutSwapBuffers();
}

void glut_dodecahedron(int argc, char* argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Rhombus Dodecahedron");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(idle);
    glutMainLoop();
}

int main(int argc, char* argv[]) {
    std::cout << "Starting program\n";
    glut_dodecahedron(argc, argv);
    std::cout << "...program completed\n";
    return 0;
}


/*#include <GL/glut.h>
#include <cmath>


// Rotation angle for animation
float angle = 0.0f;

// Function to define the vertices of the rhombic dodecahedron
void drawRhombicDodecahedron() {
    GLfloat vertices[14][3] = {
        {0, 0, -4}, {2, -2, -2}, {-2, -2, 2}, {0, -4, 0},
        {-4, 0, 0}, {-2, 2, -2}, {2, 2, -2}, {4, 0, 0},
        {0, 4, 0}, {2, -2, 2}, {2, 2, 2}, {0, 0, 4},
        {-2, 2, 2}, {-2, -2, 2}
    };

    GLint faces[12][4] = {
        { 0, 1, 3, 2 }, { 2, 3, 13, 4 }, { 4, 13, 11, 12 }, { 12, 11, 10, 8 },
        { 8, 10, 7, 6 }, { 6, 7, 1, 0 }, { 0, 5, 4, 2 }, { 5, 8, 6, 0 },
        { 8, 5, 4, 12 }, { 11, 9, 7, 10 }, { 7, 1, 3, 9 }, { 9, 3, 13, 11 }
    };

    // Colors for each face
    GLfloat colors[12][3] = {
        {1, 0, 0}, {0, 1, 0}, {0, 0, 1}, {1, 1, 0},
        {1, 0, 1}, {0, 1, 1}, {0.5, 0.5, 0}, {0.5, 0, 0.5},
        {0, 0.5, 0.5}, {0.75, 0.25, 0}, {0.25, 0.75, 0}, {0, 0.25, 0.75}
    };

    glBegin(GL_QUADS);
    for (int i = 0; i < 12; i++) {
        // Set the color for each face
        glColor3fv(colors[i]);

        // Draw the four vertices of each face
        for (int j = 0; j < 4; j++) {
            glVertex3fv(vertices[faces[i][j]]);
        }
    }
    glEnd();
}

// Function to initialize OpenGL settings
void initOpenGL() {
    glClearColor(0.0, 0.0, 0.0, 1.0);  // Set the background color to black
    glEnable(GL_DEPTH_TEST);  // Enable depth testing for 3D rendering
}

// Function to handle the window's display event
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // Clear the screen and depth buffer

    glLoadIdentity();  // Reset the model-view matrix

    // Position the camera
    glTranslatef(0.0f, 0.0f, -5.0f);

    // Apply continuous rotation around X and Y axes
    glRotatef(angle, 1.0f, 1.0f, 0.0f);

    drawRhombicDodecahedron();  // Draw the shape

    glutSwapBuffers();  // Swap the front and back buffers to display the rendered image
}

// Function to handle window resizing
void reshape(int w, int h) {
    double aspect = double(w) / double(h);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glScalef(0.5, 0.5, 0.5);
    gluPerspective(45.0, aspect, 1.0, 20.0);  // Set up the perspective projection
    glMatrixMode(GL_MODELVIEW);
}

// Function to update the rotation angle
void update(int value) {
    angle += 2.0f;  // Increase the rotation angle
    if (angle > 360) {
        angle -= 360;  // Keep the angle in the 0-360 range
    }

    glutPostRedisplay();  // Redraw the window
    glutTimerFunc(16, update, 0);  // Call update every 16 milliseconds (~60 FPS)
}

// Main function to set up the OpenGL window and start rendering
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  // Set display mode
    glutInitWindowSize(800, 600);  // Set window size
    glutCreateWindow("Rhombic Dodecahedron");  // Create the window with the specified title

    initOpenGL();  // Initialize OpenGL settings

    // Register callbacks
    glutDisplayFunc(display);  // Set the display function
    glutReshapeFunc(reshape);  // Set the reshape function
    glutTimerFunc(25, update, 0);  // Set the update timer function

    glutMainLoop();  // Enter the main event loop
    return 0;
}
    */
