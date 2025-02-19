#include "common_opengl.h"

GLfloat angle = 0.0f;

float square_root(float x) { return (float) sqrt(x); }

void display_tetra(void) {
  static int list = 0;
  if (list == 0) {
    // If the display list does not exist, create
    GLfloat
      PointA[] = { 0.5f, -square_root(6.0f) / 12, -square_root(3.0f) / 6 },
      PointB[] = { -0.5f, -square_root(6.0f) / 12, -square_root(3.0f) / 6 },
      PointC[] = { 0.0f, -square_root(6.0f) / 12, square_root(3.0f) / 3 },
      PointD[] = { 0.0f, square_root(6.0f) / 4,0 };
    GLfloat
      ColorR[] = { 1, 0, 0 },
      ColorG[] = { 0, 1, 0 },
      ColorB[] = { 0, 0, 1 },
      ColorY[] = { 1, 1, 0 };
    list = glGenLists(1);
    glNewList(list, GL_COMPILE);
    glBegin(GL_TRIANGLES);
    //plane ABC
    ColoredVertex(ColorR,PointA);  ColoredVertex(ColorG, PointB);  ColoredVertex(ColorB, PointC);
    // flat ACD
    ColoredVertex(ColorR, PointA);  ColoredVertex(ColorB, PointC);  ColoredVertex(ColorY, PointD);
    // Plane CBD
    ColoredVertex(ColorB, PointC);  ColoredVertex(ColorG, PointB);  ColoredVertex(ColorY, PointD);
    // Plane BAD
    ColoredVertex(ColorG, PointB);  ColoredVertex(ColorR, PointA);  ColoredVertex(ColorY, PointD);
    glEnd();
    glEndList();
    glEnable(GL_DEPTH_TEST);
  }
  // A display list has been created, which will be called each time a regular tetrahedron is drawn
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glPushMatrix();  glRotatef(angle, 1, 0.5, 0);  glCallList(list);  glPopMatrix();  glutSwapBuffers();
}

void idle_tetrahedron(void) {
  ++angle;
  if (angle >= 360.0f) { angle = 0.0f; }
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  display_tetra();
}

void rotate_tetra(int argc, char* argv[]) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
  glutInitWindowPosition(200, 200);
  glutInitWindowSize(WIDTH, HEIGHT);
  glutCreateWindow("OpenGL Window");
  glutDisplayFunc(&display_tetra);

  glutIdleFunc(&idle_tetrahedron);
  glutMainLoop();
}


int main ( int argc, char *argv[] ) {
  std::cout << "Starting program\n";
  
  rotate_tetra(argc, argv);

  std::cout << "...program completed\n";
  return 0;
}

