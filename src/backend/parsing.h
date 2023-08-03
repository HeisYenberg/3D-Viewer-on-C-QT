#ifndef PARSING_H
#define PARSING_H

#include "transformations.h"

enum parsing_status { PARSING_OK, PARSING_ERROR };

typedef struct indices_array {
  int *array;
  int count;
} IndicesArray;

int read_file(char *file_name, VerticesMatrix **coordinates,
              IndicesArray **faces);
int read_vertex(char *line, VerticesMatrix **coordinates);
int read_faces(char *line, IndicesArray **faces, int vertices);
int line_to_face(char *line, int vertices);
int push_matrix(VerticesMatrix **coordinates, double *vertices);
void set_matrix_row(VerticesMatrix *coordinates, double *vertices);
void remove_matrix(VerticesMatrix **coordinates);
int push_array(IndicesArray **faces, unsigned int face);
void remove_array(IndicesArray **faces);

#endif  // PARSING_H