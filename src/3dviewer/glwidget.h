#ifndef GLWIDGET_H
#define GLWIDGET_H
#define GL_SILENCE_DEPRECATION

#include <QMouseEvent>
#include <QOpenGLWidget>
#include <QWidget>

#define RGB_MIN 1
#define RGB_MAX 255

class glwidget : public QOpenGLWidget {
  Q_OBJECT
 public:
  int vertex_len;
  int facets_len;
  double *vertex_arr;
  int *facets_arr;
  double minVerX;
  double maxVerX;
  double minVerY;
  double maxVerY;
  double minVerZ;
  double maxVerZ;
  double MaxVert;
  double MinVert;
  int LineType;
  float Width_Line;
  int central = false;
  int parallel = false;
  int VertType = 0;
  float size_vertice;

  float BackR;
  float BackG;
  float BackB;

  float LineR = 100;
  float LineG = 100;
  float LineB = 100;

  float VertR;
  float VertG;
  float VertB;

  float LineWidth;
  int LineTypeIndex;
  int VertTypeIndex;
  float VertScale;
  int projection_type;

  explicit glwidget(QWidget *parent = nullptr);

 private:
  float xRot, yRot, zRot;
  QPoint mPos;
  void mousePressEvent(QMouseEvent *) override;
  void mouseMoveEvent(QMouseEvent *) override;

 signals:
 protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
};

#endif  // GLWIDGET_H
