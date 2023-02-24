#ifndef Viewer_v1_H_
#define Viewer_v1_H_
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OK 0
#define FAIL 1
#define FLAG INT_MAX

typedef struct dataStruct {
  int countVertexes;
  int countFacets;

  double* dataVertexes;
  int* dataFacets;

  double minVertexesX;
  double maxVertexesX;
  double minVertexesY;
  double maxVertexesY;
  double minVertexesZ;
  double maxVertexesZ;
} dataStruct;

dataStruct parser(char* filename);
void initialize_struct(dataStruct* data);
int parsCount(char* filename, dataStruct* data);
void parsVertexes(char* filename, dataStruct* data);
void parsFacets(char* filename, dataStruct* data);
void parsVal(dataStruct* data);
void findMaxMin(double* str, double* max, double* min, int len);
void clearStruct(dataStruct* data);

void make_central(dataStruct* data);
double find_D_max(dataStruct* data);
void resize_to_one(dataStruct* data, double size_value);
void move_form(dataStruct* data, double* shift);
void resize_form_more(dataStruct* data, double zoom, int current_zoom_l,
                      int current_zoom_m);
void resize_form_less(dataStruct* data, double zoom, int current_zoom_l,
                      int current_zoom_m);
void rotate_form(dataStruct* data, double* rotate);
void reset_move_by_axis(dataStruct* data, int* reset_move);
void reset_zoom(dataStruct* data, double size_value);

#endif  //  Viewer_v1_H
