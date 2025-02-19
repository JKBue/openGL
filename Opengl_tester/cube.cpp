#include "common_opengl.h"


//===============================================================================
// rotating colored cube
//
//  This is the include statement I need for Mac OS X.
//
GLfloat vertices[][3] = {
  { -1.0, -1.0, -1.0 },
  {  1.0, -1.0, -1.0 },
  {  1.0,  1.0, -1.0 },
  { -1.0,  1.0, -1.0 },
  { -1.0, -1.0,  1.0 },
  {  1.0, -1.0,  1.0 },
  {  1.0,  1.0,  1.0 },
  { -1.0,  1.0,  1.0 } };

GLfloat normals[][3] = {
  { -1.0, -1.0, -1.0 },
  {  1.0, -1.0, -1.0 },
  {  1.0,  1.0, -1.0 },
  { -1.0,  1.0, -1.0 },
  { -1.0, -1.0,  1.0 },
  {  1.0, -1.0,  1.0 },
  {  1.0,  1.0,  1.0 },
  { -1.0,  1.0,  1.0 } };

GLfloat colors[][3] = {
  { 0.0, 0.0, 0.0 },
  { 1.0, 0.0, 0.0 },
  { 1.0, 1.0, 0.0 },
  { 0.0, 1.0, 0.0 },
  { 0.0, 0.0, 1.0 },
  { 1.0, 0.0, 1.0 },
  { 1.0, 1.0, 1.0 },
  { 0.0, 1.0, 1.0 } };

static GLint axis = 2;
static GLfloat theta[3] = { 0.0, 0.0, 0.0 };

//****************************************************************************80
//    Edward Angel
//    COLORCUBE defines the 6 faces of the color cube object.
//
//****************************************************************************80
//    POLYGON defines the colors, vertices and normals for a quadrilateral.
//
void polygon ( int a, int b, int c, int d ) {
  glBegin ( GL_POLYGON );

  glColor3fv ( colors[a] );   glNormal3fv ( normals[a] );   glVertex3fv ( vertices[a] );
  glColor3fv ( colors[b] );   glNormal3fv ( normals[b] );   glVertex3fv ( vertices[b] );
  glColor3fv ( colors[c] );   glNormal3fv ( normals[c] );   glVertex3fv ( vertices[c] );
  glColor3fv ( colors[d] );   glNormal3fv ( normals[d] );   glVertex3fv ( vertices[d] );

  glEnd ( );
}

void colorcube ( ) {
  polygon ( 0, 3, 2, 1 );      polygon ( 2, 3, 7, 6 );      polygon ( 0, 4, 7, 3 );
  polygon ( 1, 2, 6, 5 );      polygon ( 4, 5, 6, 7 );      polygon ( 0, 1, 5, 4 );
}

//****************************************************************************80
//    DISPLAY generates the graphics output.
//
void display ( ) {
  glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );   glLoadIdentity ( );
  glRotatef ( theta[0], 1.0, 0.0, 0.0 );   glRotatef ( theta[1], 0.0, 1.0, 0.0 );   glRotatef ( theta[2], 0.0, 0.0, 1.0 );
  colorcube();   glFlush ( );   glutSwapBuffers ( );
}

//****************************************************************************80
//    MOUSE determines the response to mouse input.
//
void mouse ( int btn, int state, int x, int y ) {
  std::cout << "Mouse function entered -- axis value is: " << axis << "\n";
  if ( btn == GLUT_LEFT_BUTTON && state == GLUT_DOWN ) { ++axis; }
  if ( btn == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN ) { ++axis; }
  if ( btn == GLUT_RIGHT_BUTTON && state == GLUT_DOWN ) { ++axis; }
  axis %= 3;
}

//****************************************************************************80
//    MYRESHAPE determines the window mapping.
//
void myReshape ( int w, int h ) {
  glViewport ( 0, 0, w, h );
  glMatrixMode ( GL_PROJECTION );
  glLoadIdentity ( );

  if ( w <= h ) {
    glOrtho (
      -2.0, 2.0,
      -2.0 * ( GLfloat ) h / ( GLfloat ) w, 2.0 * ( GLfloat ) h / ( GLfloat ) w,
      -10.0, 10.0 );
  } else {
    glOrtho (
      -2.0 * ( GLfloat ) h / ( GLfloat ) w, 2.0 * ( GLfloat ) h / ( GLfloat ) w,
      -2.0, 2.0,
      -10.0, 10.0 );
  }
  glMatrixMode ( GL_MODELVIEW );
}

//****************************************************************************80
//    SPINCUBE adjusts the angle of rotation and redisplays the picture.
//
void spinCube ( ) {
  std::cout << "entered spinCube()...\n";
//  theta[axis] = theta[axis] + 0.020;
  theta[axis] += 1.0;
  if ( 360.0 < theta[axis] ) {
    theta[axis] = theta[axis] - 360.0;
  }
  glutPostRedisplay ( );
  std::cout << "\t\texiting spinCube()...\n\n";
}

//****************************************************************************80
//    This program constructs a cube, each of whose vertices is given a
//    different color, and displays the cube.  The cube rotates slowly
//    about the X, Y or Z axis.  Each time the user clicks the mouse, the
//    "next" axis is used for rotation.
//
void rotating_cube(int argc, char* argv[]) {
  glutInit ( &argc, argv );
  glutInitDisplayMode ( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH );
  glutInitWindowSize ( 500, 500 );
  glutInitWindowPosition ( 0, 0 );
  glutCreateWindow ( "Rotating cube" );
  glutReshapeFunc ( myReshape );
  glutDisplayFunc ( display );
  glutIdleFunc ( spinCube );
  glutMouseFunc ( mouse );

//  Enable hidden surface removal.
  glEnable ( GL_DEPTH_TEST );
  glutMainLoop ( );

  std::cout << "axis: " << axis << "\n";
}


int main ( int argc, char *argv[] ) {
  std::cout << "Starting program\n";
 
    rotating_cube(argc, argv);
 
  std::cout << "...program completed\n";
  return 0;
}