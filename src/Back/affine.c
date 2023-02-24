#include "../main.h"

/**
 * @brief This in a function wich move the form to the center of the field from
 * the coordinate axes. This in a function wich move the form to the center of
 * the field from the coordinate axes. It calculates step of the moving and then
 * moves the form to the center of coordinate axes.
 * @param data - this is a struct with required data.
 */
void make_central(dataStruct *data) {
  double centrlVertexesX = 0, centrlVertexesY = 0, centrlVertexesZ = 0;

  centrlVertexesX =
      data->minVertexesX + (data->maxVertexesX - data->minVertexesX) / 2;
  centrlVertexesY =
      data->minVertexesY + (data->maxVertexesY - data->minVertexesY) / 2;
  centrlVertexesZ =
      data->minVertexesZ + (data->maxVertexesZ - data->minVertexesZ) / 2;

  for (int i = 0; i < data->countVertexes; i += 3) {
    data->dataVertexes[i] -= centrlVertexesX;
    data->dataVertexes[i + 1] -= centrlVertexesY;
    data->dataVertexes[i + 2] -= centrlVertexesZ;
  }
}

/**
 * @brief This is a function wich finds maximum distance between points along
 * the coordinate axis This is a function wich finds maximum distance between
 * points along the coordinate axis. Finds maximum by X axis, Y axis and Z axis.
 * After it finds maximum of them.
 * @param data - this is a struct with required data.
 * @return double - maximum distence by axis.
 */
double find_D_max(dataStruct *data) {
  double D_max = 0.0, tmp_x = 0.0, tmp_y = 0.0, tmp_z = 0.0;
  tmp_x = data->maxVertexesX - data->minVertexesX;
  tmp_y = data->maxVertexesY - data->minVertexesY;
  tmp_z = data->maxVertexesZ - data->minVertexesZ;

  if (tmp_x > D_max) D_max = tmp_x;
  if (tmp_y > D_max) D_max = tmp_y;
  if (tmp_z > D_max) D_max = tmp_z;

  return D_max;
}

/**
 * @brief This is a function that makes a form smaller to show it ti user n full
 * size. This is a function that makes a form smaller. It resize the form from
 * -1 to one by X, by Y and by Z.
 * @param data - this is a struct with required data.
 * @param size_value - a value to what the programm should resize form.
 */

void resize_to_one(dataStruct *data, double size_value) {
  double D_max = find_D_max(data);
  double scale = size_value * (size_value) / D_max;

  for (int i = 0; i < data->countVertexes; i++) {
    data->dataVertexes[i] *= scale;
  }
  parsVal(data);
}

/**
 * @brief This is a function wich moves form.
 * This is a function wich moves form.
 * If the function gets value in shif[0] - it moves form from right to left and
 * from left to right by X axis. If the function gets value in shif[1] - it
 * moves form from up to down and from down to up by Y axis. If the function
 * gets value in shif[3] - it moves form from forward to back and from back to
 * forward by Z axis.
 * @param data - this is a struct with required data.
 * @param shift -  an array with data. shift[0] - move by X, shift[1] - move by
 * Y, shift[2] - move by Z.
 */
void move_form(dataStruct *data, double *shift) {
  if (shift[0] != 0) {
    for (int i = 0; i < data->countVertexes; i += 3)
      data->dataVertexes[i] += shift[0];
  }
  if (shift[1] != 0) {
    for (int i = 1; i < data->countVertexes; i += 3)
      data->dataVertexes[i] += shift[1];
  }
  if (shift[2] != 0) {
    for (int i = 2; i < data->countVertexes; i += 3)
      data->dataVertexes[i] += shift[2];
  }
}

/**
 * @brief This is a function wich resize form.
 * This is a function wich resize form, makes it smaller.
 * @param data - this is a struct with required data.
 * @param zoom - value to what we want to resize.
 */
void resize_form_more(dataStruct *data, double zoom, int current_zoom_l,
                      int current_zoom_m) {
  for (int i = 0; i < (data->countVertexes + current_zoom_l); i++) {
    data->dataVertexes[i] *= zoom;
    current_zoom_m++;
  }
  current_zoom_l = 0;
}

/**
 * @brief This is a function wich resize form.
 * This is a function wich resize form, makes it smaller.
 * @param data - this is a struct with required data.
 * @param zoom - value to what we want to resize.
 */
void resize_form_less(dataStruct *data, double zoom, int current_zoom_l,
                      int current_zoom_m) {
  for (int i = 0; i < (data->countVertexes + current_zoom_m); i++) {
    data->dataVertexes[i] /= zoom;
    current_zoom_l++;
  }
  current_zoom_m = 0;
}

/**
 * @brief This a function wich rotates form.
 * This a function wich rotates form.
 * If the function gets value in rotate[0] - it rotates form by X axis.
 * If the function gets value in rotate[1] - it rotates form by Y axis.
 * If the function gets value in rotate[3] - it rotates form by Z axis.
 * @param data - this is a struct with required data.
 * @param rotate - array with data. Rotate[0] - it rotates form by X axis,
 * rotate[1] - it rotates form by Y axis, rotate[2] - it rotates form by Z axis.
 */
void rotate_form(dataStruct *data, double *rotate) {
  double tmp_arr[3] = {0, 0, 0};
  if (rotate[0] != 0) {
    for (int i = 0; i < data->countVertexes; i += 3) {
      for (int j = 0; j < 3; j++) tmp_arr[j] = data->dataVertexes[i + j];
      data->dataVertexes[i + 1] =
          tmp_arr[1] * cos(rotate[0]) - tmp_arr[2] * sin(rotate[0]);
      data->dataVertexes[i + 2] =
          tmp_arr[1] * sin(rotate[0]) + tmp_arr[2] * cos(rotate[0]);
    }
  }
  if (rotate[1] != 0) {
    for (int i = 0; i < data->countVertexes; i += 3) {
      for (int j = 0; j < 3; j++) tmp_arr[j] = data->dataVertexes[i + j];
      data->dataVertexes[i] =
          tmp_arr[0] * cos(rotate[1]) + tmp_arr[2] * sin(rotate[1]);
      data->dataVertexes[i + 2] =
          -tmp_arr[0] * sin(rotate[1]) + tmp_arr[2] * cos(rotate[1]);
    }
  }
  if (rotate[2] != 0) {
    for (int i = 0; i < data->countVertexes; i += 3) {
      for (int j = 0; j < 3; j++) tmp_arr[j] = data->dataVertexes[i + j];
      data->dataVertexes[i] =
          tmp_arr[0] * cos(rotate[2]) - tmp_arr[1] * sin(rotate[2]);
      data->dataVertexes[i + 1] =
          tmp_arr[0] * sin(rotate[2]) + tmp_arr[1] * cos(rotate[2]);
    }
  }
}

/**
 * @brief This is a function wich moves form to start position.
 * This is a function wich moves form to start position. If reset_move[0] != 0
 * it moves form to centr of the X-axis, if reset_move[1] != 0 it moves form to
 * centr of the Y-axis, if reset_move[2] != 0 it moves form to centr of the
 * Z-axis
 * @param data - this is a struct with required data.
 * @param shift -  an array with data. reset_move[0] - move by X, reset_move[1]
 * - move by Y, reset_move[2] - move by Z.
 */
void reset_move_by_axis(dataStruct *data, int *reset_move) {
  double max = 0, min = 0, central = 0;
  int idx = 0;
  if (reset_move[0] != 0) {
    double *dataX = (double *)calloc(data->countVertexes / 3, sizeof(double));
    for (int i = 0; i < data->countVertexes; i += 3, idx++) {
      dataX[idx] = data->dataVertexes[i];
    }
    findMaxMin(dataX, &max, &min, idx);
    data->maxVertexesX = max;
    data->minVertexesX = min;
    free(dataX);
    central =
        data->minVertexesX + (data->maxVertexesX - data->minVertexesX) / 2;
    for (int i = 0; i < data->countVertexes; i += 3) {
      data->dataVertexes[i] -= central;
    }
  }
  if (reset_move[1] != 0) {
    double *dataY = (double *)calloc(data->countVertexes / 3, sizeof(double));
    for (int i = 1; i < data->countVertexes; i += 3, idx++) {
      dataY[idx] = data->dataVertexes[i];
    }
    findMaxMin(dataY, &max, &min, idx);
    data->maxVertexesZ = max;
    data->minVertexesZ = min;
    free(dataY);
    central =
        data->minVertexesZ + (data->maxVertexesZ - data->minVertexesZ) / 2;
    for (int i = 0; i < data->countVertexes; i += 3) {
      data->dataVertexes[i + 1] -= central;
    }
  }
  if (reset_move[2] != 0) {
    double *dataZ = (double *)calloc(data->countVertexes / 3, sizeof(double));
    for (int i = 2; i < data->countVertexes; i += 3, idx++) {
      dataZ[idx] = data->dataVertexes[i];
    }
    findMaxMin(dataZ, &max, &min, idx);
    data->maxVertexesZ = max;
    data->minVertexesZ = min;
    free(dataZ);
    central =
        data->minVertexesZ + (data->maxVertexesZ - data->minVertexesZ) / 2;
    for (int i = 0; i < data->countVertexes; i += 3) {
      data->dataVertexes[i + 2] -= central;
    }
  }
}

/**
 * @brief This is a funcktion wich reset zoom after changing;
 * This is a function that makes a form smaller to show it ti user n full
 * size. This is a function that makes a form smaller. It resize the form from
 * -1 to one by X, by Y and by Z.
 * @param data - this is a struct with required data.
 * @param size_value - a value to what the programm should resize form.
 */
void reset_zoom(dataStruct *data, double size_value) {
  parsVal(data);
  double D_max = find_D_max(data);
  double scale = size_value * (size_value) / D_max;

  for (int i = 0; i < data->countVertexes; i++) {
    data->dataVertexes[i] *= scale;
  }
  parsVal(data);
}

//     printf("\ncentrlVertexesY = %f  +  (%f  -  %f)  /2 \n",
//     data->minVertexesZ, data->maxVertexesZ,  data->minVertexesZ);
//
//     printf("\ncentrlVertexesX  %lf", centrlVertexesX);
//     printf("\ncentrlVertexesY %lf", centrlVertexesY);
//     printf("\ncentrlVertexesZ  %lf\n", centrlVertexesZ);

//     printf("\nscale = %f  *  (%f  - * -1) /  %f \n", size_value,
//     size_value,  D_max); printf("\nscale = %f\n \n ", scale);
