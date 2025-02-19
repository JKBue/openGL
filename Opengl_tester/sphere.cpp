#include "common_opengl.h"

//------------------------------------------------------------------------------------------------------------------------
// display segment through sphere
//
void display_sphere() {
  glClear(GL_COLOR_BUFFER_BIT);  glColor3f(1.0, 0.0, 0.0);  glLoadIdentity();
//  glutSolidSphere(5.0, 20.0, 20.0);    // experiment with uncommenting ONE line at a time
//  glutSolidSphere(5.0, 20, 20);
  glutSolidSphere(1.1, 20, 20);
//  glutSolidSphere(1.0, 20, 20);
//    glutSolidSphere(0.8, 80, 80);
  glFlush();
}

void myInit() {
  glClearColor(1.0, 1.0, 1.0, 1.0);  glColor3f(1.0, 0.0, 0.0);  glMatrixMode(GL_PROJECTION);  glLoadIdentity();
//  gluOrtho2D(0.0, 499.0, 0.0, 499.0);
//  gluOrtho2D(-5.0, 5.0, -5.0, 5.0);
  gluOrtho2D(-1.1, 1.1, -1.1, 1.1);
//  gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

  glMatrixMode(GL_MODELVIEW);
}

void glut_sphere(int argc,char* argv[]) {
//   GLUquadric* qobj = gluNewQuadric();   
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  glutInitWindowSize(500, 500);  glutCreateWindow("pendulum");    glutDisplayFunc(display_sphere);
  myInit();
  glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
  glutMainLoop();
}


int main ( int argc, char *argv[] ) {
  std::cout << "Starting program\n";
  
  glut_sphere(argc, argv);

  std::cout << "...program completed\n";
  return 0;
}
