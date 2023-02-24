#include "../main.h"

dataStruct parser(char *filename) {
  dataStruct data;
  initialize_struct(&data);
  parsCount(filename, &data);
  parsVertexes(filename, &data);
  parsFacets(filename, &data);
  parsVal(&data);
  make_central(&data);
  resize_to_one(&data, 0.9);
  return data;
}

void initialize_struct(dataStruct *data) {
  data->countVertexes = 0;
  data->countFacets = 0;

  data->dataVertexes = NULL;
  data->dataFacets = NULL;

  data->minVertexesX = 0;
  data->maxVertexesX = 0;
  data->minVertexesY = 0;
  data->maxVertexesY = 0;
  data->minVertexesZ = 0;
  data->maxVertexesZ = 0;
}

/**
 * @brief This function calculates required data from file.obj.
 * When an input file is opend, the function checks is it empty or not, after it
function allocates memory for data and counts a number of Vertexes and Facets
and adds this data tu data struct.
 * @param filename - it is input file with Vertexes and Facets.
 * @param data - this is a struct with required data.
 * @return int - the function returns an execution status.
 */
int parsCount(char *filename, dataStruct *data) {
  int res = OK;
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    res = FAIL;
  } else {
    size_t BufSize = 2000;
    char *buf = (char *)calloc(BufSize, sizeof(char));
    while (getline(&buf, &BufSize, file) != -1) {
      if (buf[0] == 'v' && buf[1] == ' ') data->countVertexes++;
      for (int i = 0; buf[i] != '\n'; i++) {
        if (buf[0] == 'f' && buf[1] == ' ' && buf[i] == ' ')
          data->countFacets++;
      }
    }
    data->countVertexes *= 3;
    if (buf) free(buf);
    fclose(file);
  }
  return res;
}

/**
 * @brief This function finds vertexes in iput file and save them to double
 * array dataVertexes When an input file is opend, the function finds lines with
 * vertexes and save them to double array dataVertexes.
 * @param filename - it is input file with Vertexes and Facets.
 * @param data - this is a struct with required data.
 * @return int - the function returns an execution status.
 */

void parsVertexes(char *filename, dataStruct *data) {
  int idx = 0;
  FILE *file = fopen(filename, "r");
  data->dataVertexes =
      (double *)calloc(data->countVertexes + 1, sizeof(double));
  char *buf = NULL;
  size_t len = 0;
  ssize_t read;
  while ((read = getline(&buf, &len, file)) != -1) {
    if (buf[0] == 'v' && buf[1] == ' ') {
      int j = 0;
      char *ptr = strtok(buf, " v");
      while (ptr != NULL && j < 3) {
        data->dataVertexes[idx] = atof(ptr);
        ptr = strtok(NULL, " ");
        j++;
        idx++;
      }
    }
  }
  free(buf);
  fclose(file);
}

/**
 * @brief This function finds facets in iput file and save them to double array
 * dataVertexes When an input file is opend, the function finds lines with
 * facets and save them to int array dataFacets.
 * @param filename - it is input file with Vertexes and Facets.
 * @param data - this is a struct with required data.
 * @return int - the function returns an execution status.
 */

void parsFacets(char *filename, dataStruct *data) {
  int idx = 0;
  data->dataFacets = (int *)calloc(data->countFacets * 2 + 1, sizeof(int));
  int *bufInt = (int *)calloc(data->countFacets * 3, sizeof(int));
  char *buf = NULL;
  size_t len = 0;
  ssize_t read;
  FILE *file = fopen(filename, "r");
  while ((read = getline(&buf, &len, file)) != -1) {
    int lenBuf = strlen(buf);
    if (buf[0] == 'f' && buf[1] == ' ') {
      if (buf[lenBuf - 3] == ' ' && buf[lenBuf - 2] == '\r' &&
          buf[lenBuf - 1] == '\n') {
        buf[lenBuf - 3] = '\n';
      }
      if (buf[lenBuf - 2] == ' ' && buf[lenBuf - 1] == '\n') {
        buf[lenBuf - 2] = '\n';
      }
      short int flag = 0;
      char *pchF = strtok(buf, " f");
      int firstVal = atoi(pchF);

      while (pchF != NULL) {
        for (int k = 0; k < strlen(pchF); k++)
          if (pchF[k] == '\n') flag++;
        if (flag) {
          bufInt[idx] = atoi(pchF) - 1;
          idx++;
          bufInt[idx] = atoi(pchF) - 1;
          idx++;
          bufInt[idx] = firstVal - 1;
          idx++;
          bufInt[idx] = FLAG;
          idx++;
        } else {
          bufInt[idx] = atoi(pchF) - 1;
          idx++;
          bufInt[idx] = atoi(pchF) - 1;
          idx++;
        }
        pchF = strtok(NULL, " ");
      }
    }
  }

  for (int f = 0, j = 1; f <= data->countFacets * 2; j++, f++) {
    if (bufInt[j] != FLAG) data->dataFacets[f] = bufInt[j];
    if (bufInt[j] == FLAG) {
      j++;
      data->dataFacets[f] = bufInt[j];
      j++;
    }
  }
  free(buf);
  fclose(file);
  free(bufInt);
}

/**
 * @brief This is a function wich works with double array dataVertexes and
 * divides it to array with X coordinats, Y coordinats and Z coordinats. This is
 * a function wich works with double array dataVertexes and divides it to array
 * with X coordinats, Y coordinats and Z coordinats to continue a work with a
 * programm. After parcing it calls the function wich finds maximum and minimum
 * values in parced arrays.
 * @param data - this is a struct with required data.
 */

void parsVal(dataStruct *data) {
  double max = 0, min = 0;
  double *dataX = (double *)calloc(data->countVertexes / 3, sizeof(double));
  double *dataY = (double *)calloc(data->countVertexes / 3, sizeof(double));
  double *dataZ = (double *)calloc(data->countVertexes / 3, sizeof(double));
  int idx = 0;

  for (int i = 0; i < data->countVertexes; i += 3) {
    dataX[idx] = data->dataVertexes[i];
    dataY[idx] = data->dataVertexes[i + 1];
    dataZ[idx] = data->dataVertexes[i + 2];
    idx++;
  }

  findMaxMin(dataX, &max, &min, idx);
  data->maxVertexesX = max;
  data->minVertexesX = min;
  max = min = 0;

  findMaxMin(dataY, &max, &min, idx);
  data->maxVertexesY = max;
  data->minVertexesY = min;
  max = min = 0;

  findMaxMin(dataZ, &max, &min, idx);
  data->maxVertexesZ = max;
  data->minVertexesZ = min;
  max = min = 0;

  free(dataX);
  free(dataY);
  free(dataZ);
}

/**
 * @brief This is a function wich finds maximum value and minimum value in
 * double array. This is a function wich finds maximum value and minimum value
 * in double array.
 * @param str - input double data with values of X, Y or Z.
 * @param max - input value of maximum, wich will be changed after work of the
 * function.
 * @param min - input value of minimum, wich will be changed after work of the
 * function.
 * @param len - a length of input str.
 */

void findMaxMin(double *str, double *max, double *min, int len) {
  double mx = INT_MIN;
  double mn = INT_MAX;
  for (int i = 0; i < len - 1; i++) {
    if (mx < str[i]) {
      mx = str[i];
    }
    if (mn > str[i]) {
      mn = str[i];
    }
    *max = mx;
    *min = mn;
  }
}

/**
 * @brief This is a function wich cleans data struct after the work of the
 * programm. This is a function wich cleans data struct after the work of the
 * programm.
 * @param data - this is a struct with required data.
 */

void clearStruct(dataStruct *data) {
  data->countVertexes = 0;
  data->countFacets = 0;
  free(data->dataVertexes);
  free(data->dataFacets);
}
