#include "transformations.h"

void rotate_x(VerticesMatrix *data, double angle) {
  angle *= M_PI / 180;  // rad
  for (int i = 0; i < data->rows; i++) {
    double tempy = data->matrix[3 * i + 1];
    double tempz = data->matrix[3 * i + 2];
    data->matrix[3 * i + 1] = tempy * cos(angle) + tempz * sin(angle);
    data->matrix[3 * i + 2] = -tempy * sin(angle) + tempz * cos(angle);
  }
}

void rotate_y(VerticesMatrix *data, double angle) {
  angle *= M_PI / 180;
  for (int i = 0; i < data->rows; i++) {
    double tempx = data->matrix[3 * i];
    double tempz = data->matrix[3 * i + 2];
    data->matrix[3 * i] = tempx * cos(angle) + tempz * sin(angle);
    data->matrix[3 * i + 2] = -tempx * sin(angle) + tempz * cos(angle);
  }
}
void rotate_z(VerticesMatrix *data, double angle) {
  angle *= M_PI / 180;
  for (int i = 0; i < data->rows; i++) {
    double tempx = data->matrix[3 * i];
    double tempy = data->matrix[3 * i + 1];
    data->matrix[3 * i] = tempx * cos(angle) + tempy * sin(angle);
    data->matrix[3 * i + 1] = -tempx * sin(angle) + tempy * cos(angle);
  }
}

void scale_matrix(VerticesMatrix *V, double scl) {
  for (int i = 0; i < V->rows; i++) {
    V->matrix[3 * i] = V->matrix[3 * i] * scl;
    V->matrix[3 * i + 1] = V->matrix[3 * i + 1] * scl;
    V->matrix[3 * i + 2] = V->matrix[3 * i + 2] * scl;
  }
}

void translate_matrix(VerticesMatrix *data, double move_x, double move_y,
                      double move_z) {
  for (int i = 0; i < data->rows; i++) {
    data->matrix[3 * i] = data->matrix[3 * i] + move_x;
    data->matrix[3 * i + 1] = data->matrix[3 * i + 1] + move_y;
    data->matrix[3 * i + 2] = data->matrix[3 * i + 2] + move_z;
  }
}