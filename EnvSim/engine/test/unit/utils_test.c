//     Project: ossm
//      Module: utils / test
// Description: Unit test for module utils
//
// History:
// - J. Kastner, 07.09.15: initial version

#include <check.h>
#include <stdio.h>
#include "utils.h"

START_TEST(test_ossm_utils_write_str) {
    char buf[4096];
    int buflen = 4096;
    char *next = buf;

    next = ossm_utils_write_str(next,&buflen,"a simple string");
    ck_assert_int_eq(4096-15,buflen);

    next = ossm_utils_write_str(next,&buflen,", buflen=%d",buflen);
    ck_assert_int_eq(4096-15-13,buflen);

    ck_assert_str_eq("a simple string, buflen=4081",buf);

  } END_TEST


START_TEST(test_ossm_utils_list_cons) {
    char *e1 = "e1";
    char *e2 = "e2";

    ossm_utils_list_Entry *list = NULL;
    list = ossm_utils_list_cons(list,e1);
    ck_assert_str_eq("e1",list->data);
    ck_assert(list->tail == NULL);

    list = ossm_utils_list_cons(list,e2);
    ck_assert_str_eq("e2",list->data);
    ck_assert_str_eq("e1",list->tail->data);
    ck_assert(list->tail->tail == NULL);

  } END_TEST


bool toulf1(void* data) { return strcmp("e2",(char*)data) != 0; }
bool toulf2(void* data) { return strcmp("e3",(char*)data) != 0; }

START_TEST(test_ossm_utils_list_filter) {
    char *e1 = "e1";
    char *e2 = "e2";
    char *e3 = "e3";

    ossm_utils_list_Entry *list = NULL;
    list = ossm_utils_list_cons(list,e1);
    list = ossm_utils_list_cons(list,e2);
    list = ossm_utils_list_cons(list,e3);

    list = ossm_utils_list_filter(list,toulf1);
    ck_assert_str_eq("e3",list->data);
    ck_assert_str_eq("e1",list->tail->data);
    ck_assert(list->tail->tail == NULL);


    list = ossm_utils_list_filter(list,toulf2);
    ck_assert_str_eq("e1",list->data);
    ck_assert(list->tail == NULL);

  } END_TEST


TCase* tc_utils() {
  TCase *tc = tcase_create("utils");

  tcase_add_test(tc, test_ossm_utils_write_str);
  tcase_add_test(tc, test_ossm_utils_list_cons);
  tcase_add_test(tc, test_ossm_utils_list_filter);

  return tc;
}
