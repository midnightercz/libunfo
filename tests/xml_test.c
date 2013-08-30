#include "../src/h/unfo_parse.h"

#include <check.h>

START_TEST(test_xml) {
    UNFO_ParseData *parse_data;
    char *xmlstr1, *xmlstr2;
    signed char ret;

    UNFO_Log *log = (UNFO_Log*)unfo_object_create(&UNFO_Log_ObjInfo, NULL);
    parse_data = unfo_parse_data_create("UTF-8");

    ret = unfo_parse_file("update-short.xml.gz", "utf-8", parse_data);
    ck_assert(ret != -1);
    xmlstr1 = unfo_doc_xml_str(parse_data->unfo_doc, "utf-8", log);
    unfo_doc_xml_f(parse_data->unfo_doc, "generated.xml", "UTF-8", log);
    unfo_parse_data_destroy(parse_data);

    parse_data = unfo_parse_data_create("UTF-8");
    ret = unfo_parse_file("generated.xml", "utf-8", parse_data);
    xmlstr2 = unfo_doc_xml_str(parse_data->unfo_doc, "utf-8", log);
    unfo_parse_data_destroy(parse_data);

    ck_assert_msg(strcmp(xmlstr1, xmlstr2) == 0,
                  "generated xml strings should be identical");
} END_TEST

Suite* basic_suite(void) {
    Suite *s = suite_create("basic tests");
    TCase *tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_xml);
    tcase_set_timeout(tc_core, 10);
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

