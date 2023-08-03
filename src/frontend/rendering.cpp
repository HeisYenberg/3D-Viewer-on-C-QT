#include "rendering.h"

#include <math.h>
#include <stdio.h>

Rendering::Rendering(QWidget *parent) : QOpenGLWidget(parent) {
  loadSettings();
}

Rendering::~Rendering() {
  saveSettings();
  remove_matrix(&V);
  remove_array(&F);
}

void Rendering::initializeGL() {
  glEnable(GL_DEPTH_TEST);
  glLoadIdentity();
}

void Rendering::resizeGL(int w, int h) { glViewport(0, 0, w, h); }

void Rendering::paintGL() {
  glClearColor(style.backRed, style.backGreen, style.backBlue, style.backAlfa);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  if (V && F) {
    setProjection();
    glRotatef(xRot, 1, 0, 0);
    glRotatef(yRot, 0, 1, 0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_DOUBLE, 0, V->matrix);
    drawLines();
    drawPoints();
    glDisableClientState(GL_VERTEX_ARRAY);
  }
  update();
}

void Rendering::clearRender() {
  remove_matrix(&V);
  remove_array(&F);
  update();
}

void Rendering::start_read_file(char *str) {
  read_file(str, &V, &F);
  initializeGL();
  update();
}

void Rendering::scale(double scl) {
  if (V) scale_matrix(V, scl);
  update();
}

void Rendering::rotate(double x, double y, double z) {
  if (V) {
    rotate_x(V, x);
    rotate_y(V, y);
    rotate_z(V, z);
  }
}

void Rendering::mousePressEvent(QMouseEvent *mouse) {
  start_x = mouse->pos().x();
  start_y = mouse->pos().y();
}

void Rendering::mouseMoveEvent(QMouseEvent *mouse) {
  if (mouse->buttons() & Qt::LeftButton) {
    yRot = yRot + (mouse->pos().x() - start_x);
    xRot = xRot + (mouse->pos().y() - start_y);
  } else if (mouse->buttons() & Qt::RightButton) {
    x_trans = x_trans + (mouse->pos().x() - start_x) / 200 * V->max_vertex;
    y_trans = y_trans - (mouse->pos().y() - start_y) / 200 * V->max_vertex;
  }
  start_x = mouse->pos().x();
  start_y = mouse->pos().y();
  update();
}

void Rendering::wheelEvent(QWheelEvent *event) {
  float step = event->angleDelta().y() / 100;
  float scaleF = 1.0 + (step * 0.1);
  scale(scaleF);
  update();
}

void Rendering::saveSettings() {
  QSettings settings("Setting", "3D_Viewer");

  settings.setValue("backAlfa", style.backAlfa);
  settings.setValue("backBlue", style.backBlue);
  settings.setValue("backGreen", style.backGreen);
  settings.setValue("backRed", style.backRed);
  settings.setValue("edgedAlfa", style.edgeAlfa);
  settings.setValue("edgedBlue", style.edgeBlue);
  settings.setValue("edgedGreen", style.edgeGreen);
  settings.setValue("edgedRed", style.edgeRed);
  settings.setValue("vertexBlue", style.vertexBlue);
  settings.setValue("vertexGreen", style.vertexGreen);
  settings.setValue("vertexRed", style.vertexRed);
  settings.setValue("vertexAlfa", style.vertexAlfa);
  settings.setValue("vertexWidth", style.vertexWidth);
  settings.setValue("lineWidth", style.lineWidth);
  settings.setValue("projectionType", style.projectionType);
  settings.setValue("vertexType", style.vertexType);
  settings.setValue("edgeType", style.edgeType);
  settings.sync();
}

void Rendering::loadSettings() {
  QSettings settings("Setting", "3D_Viewer");

  style.backAlfa = settings.value("backAlfa", 1.0f).toFloat();
  style.backBlue = settings.value("backBlue", 0.451f).toFloat();
  style.backGreen = settings.value("backGreen", 0.451f).toFloat();
  style.backRed = settings.value("backRed", 0.451f).toFloat();
  style.edgeAlfa = settings.value("edgedAlfa", 0.0f).toFloat();
  style.edgeBlue = settings.value("edgedBlue", 0.0f).toFloat();
  style.edgeGreen = settings.value("edgedGreen", 0.0f).toFloat();
  style.edgeRed = settings.value("edgedRed", 0.0f).toFloat();
  style.vertexBlue = settings.value("vertexBlue", 0.0f).toFloat();
  style.vertexGreen = settings.value("vertexGreen", 0.0f).toFloat();
  style.vertexRed = settings.value("vertexRed", 0.0f).toFloat();
  style.vertexAlfa = settings.value("vertexAlfa", 0.0f).toDouble();
  style.vertexWidth = settings.value("vertexWidth", 0.0f).toDouble();
  style.lineWidth = settings.value("lineWidth", 0.0f).toFloat();
  style.projectionType = settings.value("projectionType", 0.0f).toInt();
  style.vertexType = settings.value("vertexType", 0.0f).toInt();
  style.edgeType = settings.value("edgeType", 0.0f).toInt();
}

void Rendering::setProjection() {
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  double drawRange = V->max_vertex * 2;
  if (!style.projectionType) {
    glOrtho(-drawRange, drawRange, -drawRange, drawRange, -drawRange,
            drawRange * 5);
  } else {
    float fov = 60.0 * M_PI / 180;
    float heapHeight = drawRange / (2 * tan(fov / 2));
    glFrustum(-drawRange, drawRange, -drawRange, drawRange, heapHeight,
              drawRange * 5);
    glTranslated(0, 0, -heapHeight * 3);
  }
  glTranslated(x_trans, y_trans, 0);
}

void Rendering::drawLines() {
  glColor4f(style.edgeRed, style.edgeGreen, style.edgeBlue, style.edgeAlfa);
  glEnable(GL_LINE_STIPPLE);
  if (style.edgeType) {
    glLineStipple(1, 0x00ff);
  } else {
    glLineStipple(0, 0xffff);
  }
  glLineWidth(style.lineWidth);
  glDrawElements(GL_LINES, F->count, GL_UNSIGNED_INT, F->array);
  glDisable(GL_LINE_STIPPLE);
}

void Rendering::drawPoints() {
  if (style.vertexType)
    glPointSize(style.vertexWidth);
  else
    glPointSize(0.00000001);
  glColor4f(style.vertexRed, style.vertexGreen, style.vertexBlue,
            style.vertexAlfa);
  if (style.vertexType == 1) glEnable(GL_POINT_SMOOTH);
  glDrawArrays(GL_POINTS, 0, V->rows);
  if (style.vertexType == 1) glDisable(GL_POINT_SMOOTH);
}

void Rendering::move(double value_x, double value_y, double value_z) {
  if (V) translate_matrix(V, value_x, value_y, value_z);
  update();
}
