#include "../src/h/unfo_log.h"
#include "../src/h/unfo_obj.h"

#include <string.h>
#include <check.h>

START_TEST(test_log) {
    UNFO_Log *log;
    UNFO_Num *num1, *num2, *num3;
    UNFO_Str *ustr;

    log = (UNFO_Log*) unfo_object_create(&UNFO_Log_ObjInfo, NULL);

    num1 = unfo_num(1);
    num2 = unfo_num(10);
    num3 = unfo_num(100);
    ustr = unfo_str("some string");

    unfo_log_error(log, LOG_TEST_CODE1, 2, num1, num2);
    unfo_log_error(log, LOG_TEST_CODE2, 3, ustr, num1, num2);
    unfo_log_error(log, LOG_TEST_CODE3, 2, num1, num2);
    unfo_log_error(log, LOG_TEST_CODE4, 1, ustr);
    unfo_log_error(log, LOG_TEST_CODE5, 4, ustr, num1, num2, num3);
    //unfo_log_error(log, LOG_TEST_CODE6, 2, num1, num2);
    unfo_log_print(log);

    unfo_object_destroy((UNFO_Object*)num1);
    unfo_object_destroy((UNFO_Object*)num2);
    unfo_object_destroy((UNFO_Object*)num3);
    unfo_object_destroy((UNFO_Object*)ustr);
    unfo_object_destroy((UNFO_Object*)log);
} END_TEST

Suite* basic_suite(void) {
    Suite *s = suite_create("basic tests");
    TCase *tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_log);
    suite_add_tcase(s, tc_core);
    return s;
}

int main(int argc, char *argv[]) {
    (void) argc;
    (void) argv;

    int failed;

    Suite *s = basic_suite();
    SRunner *sr = srunner_create(s);
    srunner_run_all(sr, CK_NORMAL);

    failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (failed) ? EXIT_SUCCESS: EXIT_FAILURE;
}

