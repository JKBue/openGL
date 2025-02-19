#include "common_opengl.h"

void resize(int width, int height) {
  const float ar = (float) width / (float) height;
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);  glLoadIdentity();  glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
  glMatrixMode(GL_MODELVIEW);   glLoadIdentity() ;
}

void display_solids() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glColor3d(1, 0, 0);
  glPushMatrix();  glTranslated(0.0, 1.8, -6);                                      glutSolidSphere(1, 50, 50);       glPopMatrix();
  glPushMatrix();  glTranslated(-1.5, -1.2, -6);                                    glutWireSphere(1, 16, 16);        glPopMatrix();
  glPushMatrix();  glTranslated(-2.7, 1.2, -6);   glRotated(-20.0, 0.0, 0.0, 0.0);  glutWireIcosahedron();            glPopMatrix();
  glPushMatrix();  glTranslated(2.7, 1.2, -6);                                      glutWireTorus(0.4, 0.6, 12, 12);  glPopMatrix();
  glPushMatrix();  glTranslated(1.5, -1.2, -6);   glRotated(-30.0, 0.0, 0.0, 0.0);  glutWireTeapot(1.1);              glPopMatrix();
  glutSwapBuffers();
}

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };  const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };  const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };
const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };  const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };  const GLfloat high_shininess[] = { 100.0f };


void glut_many_solids(int argc, char* argv[]) {
  glutInit(&argc, argv);          glutInitWindowSize(640,480);
  glutInitWindowPosition(10,10);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

  glutCreateWindow("Programming Techniques - 3D Spheres");

  glutReshapeFunc(resize);
  glutDisplayFunc(display_solids);

  glClearColor(1,1,1,1);
  glEnable(GL_CULL_FACE);  glCullFace(GL_BACK);  glEnable(GL_DEPTH_TEST);      glDepthFunc(GL_LESS);
  glEnable(GL_LIGHT0);  glEnable(GL_NORMALIZE);  glEnable(GL_COLOR_MATERIAL);  glEnable(GL_LIGHTING);

  glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
  glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);   glLightfv(GL_LIGHT0, GL_POSITION, light_position);

  glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);   glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
  glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);  glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

  glutMainLoop();
}

int main ( int argc, char *argv[] ) {
  std::cout << "Starting program\n";

    glut_many_solids(argc, argv);

  std::cout << "...program completed\n";
  return 0;
}