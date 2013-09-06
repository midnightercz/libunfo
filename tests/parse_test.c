#include "../src/h/unfo_parse.h"

#include <check.h>

START_TEST(test_parse) {
    UNFO_ParseData *parse_data;
    parse_data = unfo_parse_data_create("UTF-8");
    unfo_parse_data_destroy(parse_data);
} END_TEST

START_TEST(test_parse1) {
    UNFO_ParseData *parse_data;
    signed char ret;

    parse_data = unfo_parse_data_create("UTF-8");

    ret = unfo_parse_file("updateinfo1.xml.gz", "utf-8", parse_data);
    ck_assert_msg(ret == -1, "Shouldn't successfuly parse updateinfo1.xml.gz"
                             "as uncompressed xml");

    unfo_parse_data_destroy(parse_data);

} END_TEST

START_TEST(test_parse2) {
    UNFO_ParseData *parse_data;
    signed char ret;
    UNFO_DocUpdate *update;
    UNFO_DocColl *collection;

    parse_data = unfo_parse_data_create("UTF-8");

    ret = unfo_parse_gzfile("update-short.xml.gz", "utf-8", parse_data);
    unfo_log_print(parse_data->log);
    ck_assert_msg(ret == 1, "updateinfo1.xml.gz should be successfuly parsed"
                             "as compressed xml");


    ck_assert_msg(parse_data->unfo_doc->updates->len == 2, "Parsed doc should"
                  "contains 2 updates. Have %d",
                   parse_data->unfo_doc->updates->len);

    update = (UNFO_DocUpdate*)parse_data->unfo_doc->updates->first->unfo_obj;
    ck_assert_msg(update->refs->len == 2,
                  "First parsed update should contains 2 references. Have %d",
                   update->refs->len);
    ck_assert_msg(update->colls->len == 1,
                  "First parsed update should contains 1 collection. Have %d",
                   update->colls->len);
    collection = (UNFO_DocColl*)update->colls->first->unfo_obj;
    ck_assert_msg(collection->pkgs->len == 4,
                  "First parsed collection should contains 4 packages. Have %d",
                   collection->pkgs->len);


    update = (UNFO_DocUpdate*)parse_data->unfo_doc->updates->first->next->unfo_obj;
    ck_assert_msg(update->refs->len == 5,
                  "Second parsed update should contains 5 references. Have %d",
                   update->refs->len);
    ck_assert_msg(update->colls->len == 1,
                  "Second parsed update should contains 1 collection. Have %d",
                   update->colls->len);
    collection = (UNFO_DocColl*)update->colls->first->unfo_obj;
    ck_assert_msg(collection->pkgs->len == 1,
                  "Second parsed collection should contains 4 packages. Have %d",
                   collection->pkgs->len);

    UNFO_Log *log = (UNFO_Log*)unfo_object_create(&UNFO_Log_ObjInfo, NULL);
    unfo_doc_xml_f(parse_data->unfo_doc, "generated.xml", "UTF-8", log);

    unfo_object_destroy((UNFO_Object*)log);
    unfo_parse_data_destroy(parse_data);

} END_TEST

Suite* basic_suite(void) {
    Suite *s = suite_create("basic tests");
    TCase *tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_parse);
    tcase_add_test(tc_core, test_parse1);
    tcase_add_test(tc_core, test_parse2);
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
    return (!failed) ? EXIT_SUCCESS: EXIT_FAILURE;
}

