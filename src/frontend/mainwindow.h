#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColorDialog>
#include <QDir>
#include <QFileDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QTimer>

#include "qgifimage.h"
#include "rendering.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

 private slots:
  void on_pathButton_clicked();
  void on_backgroundColorButton_clicked();
  void on_verticesColorButton_clicked();
  void on_edgesColorButton_clicked();
  void on_verticesWidth_valueChanged(double arg1);
  void on_edgesWidth_valueChanged(double arg1);
  void on_parallelRButtons_clicked();
  void on_centralRButton_clicked();
  void on_noneInVertices_clicked();
  void on_circleInVertices_clicked();
  void on_squareInVertices_clicked();
  void on_solidType_clicked();
  void on_dashedType_clicked();
  void on_recordButton_clicked();
  void gif_creator();
  void on_screenButton_clicked();
  void on_lowerScaleButton_clicked();
  void on_hiegherScaleButton_clicked();
  void on_rotateDownX_clicked();
  void on_rotateUpX_clicked();
  void on_rotateDownY_clicked();
  void on_rotateUpY_clicked();
  void on_rotateDownZ_clicked();
  void on_rotateUpZ_clicked();
  void on_translateDownX_clicked();
  void on_translateUpX_clicked();
  void on_translateDownY_clicked();
  void on_translateUpY_clicked();
  void on_translateDownZ_clicked();
  void on_translateUpZ_clicked();

 private:
  Ui::MainWindow *ui;
  QTimer *timer;
  QImage image;
  QGifImage *gif;
  int frame_count;
  void getColorPicker(int *red, int *green, int *blue, int *alpha);
};
#endif  // MAINWINDOW_H
