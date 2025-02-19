#include "common_opengl.h"


void display_sphere_shaded() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  glPushMatrix();
  GLfloat color[] = {1.0, 0.0, 0.0, 1.0};  glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
  glutSolidSphere(2, 20, 20);  glPopMatrix();  glutSwapBuffers();
}

void glut_sphere_shaded(int argc, char* argv[]) {
  glutInit(&argc, argv);  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);  glutInitWindowSize(400, 400);  glutCreateWindow("Sphere");
  glClearColor(0.0, 0.0, 0.0, 1.0);  glShadeModel(GL_SMOOTH);  glEnable(GL_CULL_FACE);  glEnable(GL_DEPTH_TEST);  glEnable(GL_LIGHTING);
  GLfloat lightZeroPosition[] = {10.0, 4.0, 10.0, 1.0};   GLfloat lightZeroColor[] = {0.8, 1.0, 0.8, 1.0};
                    // green tinged
  glLightfv(GL_LIGHT0, GL_POSITION, lightZeroPosition);  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightZeroColor);
  glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.1);     glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.05);  glEnable(GL_LIGHT0);
  glutDisplayFunc(display_sphere_shaded);
  glMatrixMode(GL_PROJECTION);  gluPerspective(40.0, 1.0, 1.0, 40.0);  glMatrixMode(GL_MODELVIEW);  gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
  glPushMatrix();  glutMainLoop();
}

int main ( int argc, char *argv[] ) {
  std::cout << "Starting program\n";
 
  glut_sphere_shaded(argc, argv);
 
  std::cout << "...program completed\n";
  return 0;
}
