#include "glwidget.h"

glwidget::glwidget(QWidget *parent) : QOpenGLWidget{parent} {}
void glwidget::initializeGL() {
  //    glLoadIdentity();
  //    initializeOpenGLFunctions();
  //    glMatrixMode(GL_MODELVIEW);
  //    glEnable(GL_DEPTH_TEST);
  //    glTranslatef(0,0,-3);
}
void glwidget::resizeGL(int w, int h) { glViewport(0, 0, w, h); }
void glwidget::paintGL() {
  glLoadIdentity();

  glClearColor(BackR / 100, BackG / 100, BackB / 100, 0.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnableClientState(GL_VERTEX_ARRAY);

  glColor3d(LineR / 100, LineG / 100, LineB / 100);

  glMatrixMode(GL_PROJECTION);
  glOrtho(-1, 1, -1, 1, -1, 1);

  if (parallel == true) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1, 1, -1, 1, -1, 1);
  }

  if (central == true) {
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1, 1, 2, 6);
    glTranslatef(0, 0, -3);
  }
  update();

  // придаем усиленное верчение коровы мышкой
  glRotatef(xRot, 1, 0, 0);
  glRotatef(yRot, 0, 1, 0);

  //  glVertexPointer(3, GL_DOUBLE, 0, vertex_arr);
  //  glDrawElements(GL_LINES, facets_len, GL_UNSIGNED_INT, facets_arr);

  if (LineType != 0) {
    glEnable(GL_LINE_STIPPLE);  // рисование пунктиром
    glLineStipple(1, 0x00F0);
  } else {
    glDisable(GL_LINE_STIPPLE);  // возврат линий
  }
  update();

  glLineWidth(Width_Line);

  glVertexPointer(3, GL_DOUBLE, 0, vertex_arr);
  glDrawElements(GL_LINES, facets_len, GL_UNSIGNED_INT, facets_arr);

  if (VertType == 0) {
    glPointSize(0);
  } else if (VertType == 1) {
    glEnable(GL_POINT_SMOOTH);
    glPointSize(size_vertice);

    glColor3d(VertR / 100, VertG / 100, VertB / 100);

    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_POINTS, 0, vertex_len);

    glDisableClientState(GL_VERTEX_ARRAY);
  } else if (VertType == 2) {
    glDisable(GL_POINT_SMOOTH);
    glPointSize(size_vertice);

    glColor3d(VertR / 100, VertG / 100, VertB / 100);

    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawArrays(GL_POINTS, 0, vertex_len);
    glDisableClientState(GL_VERTEX_ARRAY);
  }
  update();

  glDisable(GL_POINT_SMOOTH);
  glDisable(GL_LINE_STIPPLE);
  glDisableClientState(GL_VERTEX_ARRAY);
}

void glwidget::mousePressEvent(QMouseEvent *mo) { mPos = mo->pos(); }

void glwidget::mouseMoveEvent(QMouseEvent *mo) {
  xRot = 0.9 / M_PI * (mo->pos().y() - mPos.y());
  yRot = 0.9 / M_PI * (mo->pos().x() - mPos.x());
  update();
}
