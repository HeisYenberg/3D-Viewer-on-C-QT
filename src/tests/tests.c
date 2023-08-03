#include "tests.h"

int main() {
  int failed = 0;
  Suite *s21_3dViewer_test[] = {test_matrix(), test_parsing(),
                                test_transformations(), NULL};

  for (int i = 0; s21_3dViewer_test[i] != NULL; i++) {
    SRunner *sr = srunner_create(s21_3dViewer_test[i]);

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_run_all(sr, CK_NORMAL);

    failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }
  printf("========= FAILED: %d =========\n", failed);

  return 0;
}

START_TEST(push_matrix_1) {
  VerticesMatrix *matr = NULL;
  double vertex_coordinates[3] = {1.0, 2.0, 3.0};
  push_matrix(&matr, vertex_coordinates);
  ck_assert_double_eq(1.0, matr->matrix[0]);
  ck_assert_double_eq(2.0, matr->matrix[1]);
  ck_assert_double_eq(3.0, matr->matrix[2]);
  ck_assert_double_eq(3.0, matr->max_vertex);

  ck_assert_int_eq(1, matr->rows);
  remove_matrix(&matr);
}
END_TEST

START_TEST(push_matrix_2) {
  VerticesMatrix *matr = NULL;
  double vertex_coordinates[3] = {1.0, 2.0, 3.0};
  push_matrix(&matr, vertex_coordinates);
  ck_assert_double_eq(1.0, matr->matrix[0]);
  ck_assert_double_eq(2.0, matr->matrix[1]);
  ck_assert_double_eq(3.0, matr->matrix[2]);
  ck_assert_double_eq(3.0, matr->max_vertex);

  ck_assert_int_eq(1, matr->rows);
  remove_matrix(&matr);
}
END_TEST

Suite *test_matrix(void) {
  Suite *s = suite_create("\033[45m-=push_matrix_tc=-\033[0m");
  TCase *tc = tcase_create("push_matrix_tc");

  tcase_add_test(tc, push_matrix_1);
  tcase_add_test(tc, push_matrix_2);

  suite_add_tcase(s, tc);
  return s;
}

START_TEST(read_file_1) {
  char *filename = "../data-samples/alf.obj";
  VerticesMatrix *matr = NULL;
  IndicesArray *arr = NULL;
  int res = read_file(filename, &matr, &arr);

  ck_assert_int_eq(0, res);
  remove_matrix(&matr);
  remove_array(&arr);
}
END_TEST

START_TEST(read_file_2) {
  char *filename = "../data-samples/alf";
  VerticesMatrix *matr = NULL;  // = {{1, 2, 3}, 1, 3};
  IndicesArray *arr = NULL;
  int res = read_file(filename, &matr, &arr);

  ck_assert_int_eq(1, res);
}
END_TEST

Suite *test_parsing(void) {
  Suite *s = suite_create("\033[45m-=parsing_tc=-\033[0m");
  TCase *tc = tcase_create("parsing_tc");

  tcase_add_test(tc, read_file_1);
  tcase_add_test(tc, read_file_2);

  suite_add_tcase(s, tc);
  return s;
}

START_TEST(move_1) {
  VerticesMatrix *matr = NULL;
  double vertex_coordinates[3] = {1.0, 2.0, 3.0};
  push_matrix(&matr, vertex_coordinates);
  translate_matrix(matr, 1.0, 2.0, 3.0);
  ck_assert_double_eq(2.0, matr->matrix[0]);
  ck_assert_double_eq(4.0, matr->matrix[1]);
  ck_assert_double_eq(6.0, matr->matrix[2]);

  remove_matrix(&matr);
}
END_TEST

START_TEST(scale_2) {
  VerticesMatrix *matr = NULL;
  double vertex_coordinates[3] = {1.0, 2.0, 3.0};
  push_matrix(&matr, vertex_coordinates);
  scale_matrix(matr, 2.0);
  ck_assert_double_eq(2.0, matr->matrix[0]);
  ck_assert_double_eq(4.0, matr->matrix[1]);
  ck_assert_double_eq(6.0, matr->matrix[2]);

  remove_matrix(&matr);
}
END_TEST

START_TEST(rotate_x_3) {
  VerticesMatrix *matr = NULL;
  double vertex_coordinates[3] = {1.0, 2.0, 3.0};
  push_matrix(&matr, vertex_coordinates);
  rotate_x(matr, 2.0);
  ck_assert_double_eq_tol(1.0, matr->matrix[0], 1e-5);
  ck_assert_double_eq_tol(2.10348, matr->matrix[1], 1e-5);
  ck_assert_double_eq_tol(2.92837, matr->matrix[2], 1e-5);

  remove_matrix(&matr);
}
END_TEST

START_TEST(rotate_y_4) {
  VerticesMatrix *matr = NULL;
  double vertex_coordinates[3] = {1.0, 2.0, 3.0};
  push_matrix(&matr, vertex_coordinates);
  rotate_y(matr, 1.5);
  ck_assert_double_eq_tol(1.07819, matr->matrix[0], 1e-5);
  ck_assert_double_eq_tol(2.0, matr->matrix[1], 1e-5);
  ck_assert_double_eq_tol(2.9728, matr->matrix[2], 1e-5);

  remove_matrix(&matr);
}
END_TEST

START_TEST(rotate_z_5) {
  VerticesMatrix *matr = NULL;
  double vertex_coordinates[3] = {1.0, 2.0, 3.0};
  push_matrix(&matr, vertex_coordinates);
  rotate_z(matr, 1.5);
  ck_assert_double_eq_tol(1.05201, matr->matrix[0], 1e-5);
  ck_assert_double_eq_tol(1.97314, matr->matrix[1], 1e-5);
  ck_assert_double_eq_tol(3.0, matr->matrix[2], 1e-5);

  remove_matrix(&matr);
}
END_TEST

Suite *test_transformations(void) {
  Suite *s = suite_create("\033[45m-=transformations_tc=-\033[0m");
  TCase *tc = tcase_create("transformations_tc");

  tcase_add_test(tc, move_1);
  tcase_add_test(tc, scale_2);
  tcase_add_test(tc, rotate_x_3);
  tcase_add_test(tc, rotate_y_4);
  tcase_add_test(tc, rotate_z_5);

  suite_add_tcase(s, tc);
  return s;
}