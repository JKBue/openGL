#include "common_opengl.h" 



#define ColoredVertex(c,v) do{glColor3fv(c);glVertex3fv(v);}while(0)
#define WIDTH 400
#define HEIGHT 400

GLfloat angle = 0.0f;

float square_root(float x) { return (float) sqrt(x); }



GLfloat x_rot, y_rot, z_rot;
//GLdouble size = 10.0;
GLdouble size = 1.1;  // og 1.1

float xpos = -1.0, ypos = -1.0, zpos = -1.0;
int x = 1;
float r = 1.0, g = 0.0, b = 0.0;
bool xrotating = false, yrotating = true, zrotating = false; // og ftf
float rot_delta = 0.3;
float pos_delta = 0.01;
int color_changes = 0;
float phi = 0.0;


//------------------------------------------------
float rand_color() { return rand() % 9 / 8.0; }

//------------------------------------------------
void idle_teapot(void) {
  x_rot += rot_delta;  y_rot += rot_delta;  z_rot += rot_delta;

  ++color_changes;
  if (color_changes % 100 == 0) {
    r = rand_color();
    g = rand_color();
    b = rand_color();
    
  }

//  if (xpos <= 1) { xpos += pos_delta;  ypos += pos_delta; }
//  else { xpos = ypos = -1; }
  
//  xpos = 4 * cos(phi);   ypos = 4 * sin(phi);   phi += 0.1;
//   ypos = 4 * cos(phi);   zpos = 4 * sin(phi);   phi += 0.1;
 zpos = 4 * cos(phi);   ypos = 4 * sin(phi);   phi += 0.1; // changed xpos to ypos
  glutPostRedisplay();
}

//------------------------------------------------
void display_teapot(void) {
  glMatrixMode(GL_MODELVIEW);
  glClear(GL_COLOR_BUFFER_BIT);  // clear the drawing buffer
  glLoadIdentity();
  glTranslatef(xpos, ypos, -5.0);
  glColor3f(r, g, b);

  // og code
  glRotatef(x_rot, 1.0, 0.0, 0.0);
  glRotatef(y_rot, 0.0, 1.0, 0.0);
  glRotatef(z_rot, 0.0, 0.0, 1.0);

  // changed code for local rotation
  //glRotatef(x_rot, -0.6, 0.0, 0.1);
  //glRotatef(y_rot, 0.0, -0.5, 0.0);
  //glRotatef(z_rot, 0.2, 0.4, 0.0);

  float scale = 0.8;
  glScalef(scale, scale, scale);
  glutWireTeapot(size);
  
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  glPushMatrix();
  GLfloat color[] = {r, g, b, 1.0};  glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
  glutWireTeapot(1.1);  glPopMatrix();  glutSwapBuffers();

  usleep(10000);

}

void glut_rot_teapot(int argc, char* argv[]) {
  glutInit(&argc, argv);
  glutInitWindowSize(800, 800);
  glutCreateWindow("Teapot");
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

  glClearColor(0.0, 0.0, 0.0, 1.0);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  GLfloat lightZeroPosition[] = {10.0, 4.0, 10.0, 1.0};   GLfloat lightZeroColor[] = {0.8, 1.0, 0.8, 1.0};
  glLightfv(GL_LIGHT0, GL_POSITION, lightZeroPosition);  glLightfv(GL_LIGHT0, GL_DIFFUSE, lightZeroColor);
  glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.1);     glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.05);  glEnable(GL_LIGHT0);
  glutDisplayFunc(display_teapot);
  glMatrixMode(GL_PROJECTION);  gluPerspective(100.0, 1.0, 1.0, 40.0);  glMatrixMode(GL_MODELVIEW);  gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);
  glPushMatrix();  //glutMainLoop();

  glutDisplayFunc(display_teapot);
  glutIdleFunc(idle_teapot);
  glutMainLoop();
}


int main ( int argc, char *argv[] ) {
  std::cout << "Starting program\n";
    glut_rot_teapot(argc, argv);

  std::cout << "...program completed\n";
  return 0;
}
