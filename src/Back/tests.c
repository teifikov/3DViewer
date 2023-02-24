#include <check.h>

#include "../main.h"

dataStruct data;

START_TEST(countVertexes) {
  parsCount("Back/TestObj/testFile_1.obj", &data);
  ck_assert_int_eq(8, data.countVertexes / 3);
  clearStruct(&data);
}
END_TEST

START_TEST(countFacets) {
  parsCount("Back/TestObj/testFile_1.obj", &data);
  ck_assert_int_eq(36, data.countFacets);
  clearStruct(&data);
}
END_TEST

START_TEST(dataVertexes) {
  char fname[] = "Back/TestObj/testFile_1.obj";
  double V[22] = {-0.405,   -0.405000, 0.405000,  0.405000,  -0.405000,
                  0.405000, -0.405000, 0.405000,  0.405000,  0.405000,
                  0.405000, 0.405000,  -0.405000, 0.405000,  -0.405000,
                  0.405000, 0.405000,  -0.405000, -0.405000, -0.405000,
                  -0.405000};
  data = parser(fname);
  for (int i = 1; i < data.countVertexes - 2; i++) {
    ck_assert_double_eq(V[i - 1], data.dataVertexes[i - 1]);
  }
  clearStruct(&data);
}
END_TEST

START_TEST(dataFacets) {
  char fname[] = "Back/TestObj/testFile_1.obj";
  int F[36] = {0, 1, 1, 2, 2, 0, 2, 1, 1, 3, 3, 2, 2, 3, 3, 4, 4, 2,
               4, 3, 3, 5, 5, 4, 4, 5, 5, 6, 6, 4, 6, 5, 5, 7, 7, 6};
  data = parser(fname);
  for (int i = 0; i < data.countFacets; i++) {
    ck_assert_int_eq(F[i], data.dataFacets[i]);
  }
  clearStruct(&data);
}
END_TEST

START_TEST(moveForm) {
  char fname[] = "Back/TestObj/testFile_2.obj";
  double arr[24] = {5.000000, 4.595000, 5.405000, 5.000000, 4.595000, 5.405000,
                    5.000000, 5.405000, 5.405000, 5.000000, 5.405000, 5.405000,
                    5.000000, 5.405000, 4.595000, 5.000000, 5.405000, 4.595000,
                    5.000000, 4.595000, 4.595000, 5.000000, 4.595000, 4.595000};
  data = parser(fname);
  make_central(&data);

  double shift[3] = {5, 5, 5};
  move_form(&data, shift);

  for (int i = 0; i < 24; i++) {
    ck_assert_double_eq_tol(arr[i], data.dataVertexes[i], 1e-6);
  }
  clearStruct(&data);
}
END_TEST

START_TEST(Dmax) {
  char fname[] = "Back/TestObj/testFile_2.obj";
  data = parser(fname);
  double D_max = find_D_max(&data);
  ck_assert_double_eq(0.81, D_max);
}
END_TEST

START_TEST(rotateForm) {
  char fname[] = "Back/TestObj/testFile_2.obj";
  double arr[24] = {0.188773,  0.538366,  0.050759,  0.188773,  0.538366,
                    0.050759,  -0.486554, 0.192563,  -0.232883, -0.486554,
                    0.192563,  -0.232883, -0.188773, -0.538366, -0.050759,
                    -0.188773, -0.538366, -0.050759, 0.486554,  -0.192563,
                    0.232883,  0.486554,  -0.192563, 0.232883};
  data = parser(fname);

  double rotate_arr[3] = {1, 2, 3};
  rotate_form(&data, rotate_arr);

  for (int i = 0; i < data.countVertexes; i++) {
    ck_assert_double_eq_tol(arr[i], data.dataVertexes[i], 1e-6);
  }
  clearStruct(&data);
}
END_TEST

START_TEST(resetAxis) {
  char fname[] = "Back/TestObj/testFile_2.obj";
  double arr[24] = {0.188773,  0.538366,  0.050759,  0.188773,  0.538366,
                    0.050759,  -0.486554, 0.192563,  -0.232883, -0.486554,
                    0.192563,  -0.232883, -0.188773, -0.538366, -0.050759,
                    -0.188773, -0.538366, -0.050759, 0.486554,  -0.192563,
                    0.232883,  0.486554,  -0.192563, 0.232883};
  data = parser(fname);

  double rotate_arr[3] = {1, 2, 3};
  rotate_form(&data, rotate_arr);

  int res_move[3] = {1, 2, 3};
  reset_move_by_axis(&data, res_move);

  for (int i = 0; i < data.countVertexes; i++) {
    ck_assert_double_eq_tol(arr[i], data.dataVertexes[i], 1e-6);
  }
  clearStruct(&data);
}
END_TEST

START_TEST(resizeMoreLess) {
  char fname[] = "Back/TestObj/testFile_2.obj";
  double arr[24] = {0.339792,  0.969059,  0.091366,  0.339792,  0.969059,
                    0.091366,  -0.875797, 0.346613,  -0.419190, -0.875797,
                    0.346613,  -0.419190, -0.339792, -0.969059, -0.091366,
                    -0.339792, -0.969059, -0.091366, 0.875797,  -0.346613,
                    0.419190,  0.875797,  -0.346613, 0.419190};
  data = parser(fname);

  double rotate_arr[3] = {1, 2, 3};
  rotate_form(&data, rotate_arr);

  int res_move[3] = {1, 2, 3};
  reset_move_by_axis(&data, res_move);

  resize_form_less(&data, 0.5, 0, 0);
  resize_form_more(&data, 0.9, 0, 0);

  for (int i = 0; i < data.countVertexes; i++) {
    ck_assert_double_eq_tol(arr[i], data.dataVertexes[i], 1e-6);
  }
  clearStruct(&data);
}
END_TEST

START_TEST(resetZoom) {
  char fname[] = "Back/TestObj/testFile_2.obj";
  double arr[24] = {0.848552,  2.420000,  0.228165,  0.848552,  2.420000,
                    0.228165,  -2.187100, 0.865586,  -1.046830, -2.187101,
                    0.865586,  -1.046829, -0.848552, -2.420000, -0.228165,
                    -0.848552, -2.420000, -0.228165, 2.187101,  -0.865586,
                    1.046829,  2.187100,  -0.865586, 1.046830};
  data = parser(fname);

  double rotate_arr[3] = {1, 2, 3};
  rotate_form(&data, rotate_arr);

  int res_move[3] = {1, 2, 3};
  reset_move_by_axis(&data, res_move);

  resize_form_less(&data, 0.5, 0, 0);
  resize_form_more(&data, 0.9, 0, 0);

  reset_zoom(&data, 2.2);

  for (int i = 0; i < data.countVertexes; i++) {
    ck_assert_double_eq_tol(arr[i], data.dataVertexes[i], 1e-6);
  }
  clearStruct(&data);
}
END_TEST

START_TEST(EmptyFile) {
  int res = parsCount("", &data);
  ck_assert_int_eq(1, res);
  clearStruct(&data);
}
END_TEST

int main(void) {
  Suite* s1 = suite_create("BackTests");
  TCase* tc = tcase_create("Core");
  SRunner* sr = srunner_create(s1);
  int nf;

  suite_add_tcase(s1, tc);
  tcase_add_test(tc, countVertexes);
  tcase_add_test(tc, countFacets);
  tcase_add_test(tc, dataVertexes);
  tcase_add_test(tc, dataFacets);
  tcase_add_test(tc, moveForm);
  tcase_add_test(tc, Dmax);
  tcase_add_test(tc, rotateForm);
  tcase_add_test(tc, resetAxis);
  tcase_add_test(tc, resizeMoreLess);
  tcase_add_test(tc, EmptyFile);
  tcase_add_test(tc, resetZoom);

  srunner_run_all(sr, CK_ENV);
  nf = srunner_ntests_failed(sr);
  srunner_free(sr);

  return nf == 0 ? 0 : 1;
}
