#include "parsing.h"

int read_file(char *file_name, VerticesMatrix **coordinates,
              IndicesArray **indices) {
  int status = PARSING_ERROR;
  FILE *obj = fopen(file_name, "r");
  if (obj) {
    char buffer[4096];
    status = PARSING_OK;
    while (fgets(buffer, sizeof(buffer), obj) && !status) {
      if (buffer[0] == 'v' && buffer[1] == ' ') {
        status = read_vertex(buffer, coordinates);
      } else if (buffer[0] == 'f' && buffer[1] == ' ') {
        status = read_faces(buffer, indices,
                            *coordinates ? (*coordinates)->rows : 0);
      }
    }
    fclose(obj);
  }
  return status;
}

int read_vertex(char *line, VerticesMatrix **coordinates) {
  int status = PARSING_ERROR;
  double vertex_coordinates[3];
  int read = sscanf(line, "v %lf %lf %lf", &vertex_coordinates[0],
                    &vertex_coordinates[1], &vertex_coordinates[2]);
  if (read == 3) status = push_matrix(coordinates, vertex_coordinates);
  return status;
}

int read_faces(char *line, IndicesArray **faces, int vertices) {
  int i = 2, line_length = strlen(line);
  int face_first = line_to_face(line + i, vertices);
  int status = push_array(faces, face_first);
  for (; i < line_length && !status; i++) {
    if (isdigit(line[i]) || line[i] == '-') {
      int face_second = line_to_face(line + i, vertices);
      while (line[i] && line[i] != ' ') i++;
      status = push_array(faces, face_second);
      if (!status) status = push_array(faces, face_second);
    }
  }
  if (!status) status = push_array(faces, face_first);
  if (status) remove_array(faces);
  return status;
}

int line_to_face(char *line, int vertices) {
  int face = strtol(line, NULL, 10) - 1;
  if (face < 0) face = vertices + face + 1;
  return face;
}

int push_matrix(VerticesMatrix **coordinates, double *vertices) {
  int status = PARSING_ERROR;
  if (!*coordinates) {
    *coordinates = calloc(1, sizeof(VerticesMatrix));
    (*coordinates)->matrix = calloc(3, sizeof(double));
    if ((*coordinates)->matrix) {
      set_matrix_row(*coordinates, vertices);
      (*coordinates)->rows = 1;
      status = PARSING_OK;
    } else {
      remove_matrix(coordinates);
    }
  } else {
    (*coordinates)->matrix =
        realloc((*coordinates)->matrix,
                ((*coordinates)->rows + 1) * 3 * sizeof(double));
    if ((*coordinates)->matrix) {
      set_matrix_row(*coordinates, vertices);
      (*coordinates)->rows++;
      status = PARSING_OK;
    } else {
      remove_matrix(coordinates);
    }
  }
  return status;
}

void set_matrix_row(VerticesMatrix *coordinates, double *vertices) {
  for (int i = coordinates->rows * 3, j = 0; j < 3; i++, j++) {
    coordinates->matrix[i] = vertices[j];
    if (fabs(vertices[j]) > coordinates->max_vertex)
      coordinates->max_vertex = vertices[j];
  }
}

void remove_matrix(VerticesMatrix **coordinates) {
  if (*coordinates) {
    if ((*coordinates)->matrix) free((*coordinates)->matrix);
    free(*coordinates);
    *coordinates = NULL;
  }
}

int push_array(IndicesArray **faces, unsigned int face) {
  int status = PARSING_ERROR;
  if (!*faces) {
    *faces = calloc(1, sizeof(IndicesArray));
    (*faces)->array = calloc(1, sizeof(unsigned int));
    if ((*faces)->array) {
      (*faces)->array[(*faces)->count] = face;
      (*faces)->count++;
      status = PARSING_OK;
    }
  } else {
    (*faces)->array =
        realloc((*faces)->array, ((*faces)->count + 1) * sizeof(unsigned int));
    if ((*faces)->array) {
      (*faces)->array[(*faces)->count] = face;
      (*faces)->count++;
      status = PARSING_OK;
    }
  }
  return status;
}

void remove_array(IndicesArray **faces) {
  if (*faces) {
    if ((*faces)->array) free((*faces)->array);
    free(*faces);
    *faces = NULL;
  }
}