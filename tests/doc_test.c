#include "../src/h/unfo_objlist.h"
#include "../src/h/unfo_obj.h"
#include "../src/h/unfo_doc.h"
#include "../src/h/unfo_docupdate.h"
#include "../src/h/unfo_docref.h"
#include "../src/h/unfo_docpkg.h"
#include "../src/h/unfo_doccoll.h"
#include "doc_test.h"

#include <string.h>
#include <check.h>

START_TEST(test_doc) {
    UNFO_Doc *doc;
    doc = (UNFO_Doc*)unfo_object_create(&UNFO_Doc_ObjInfo, NULL);
    unfo_object_destroy((UNFO_Object*)doc);
}END_TEST

START_TEST(test_doc_update) {
    UNFO_DocUpdate *docupdate;
    char *tmp;

    int (*setters[])(UNFO_DocUpdate*, const char*) = {
        &unfo_doc_update_from_set,
        &unfo_doc_update_status_set,
        &unfo_doc_update_type_set,
        &unfo_doc_update_version_set,
        &unfo_doc_update_id_set,
        &unfo_doc_update_title_set,
        &unfo_doc_update_rights_set,
        &unfo_doc_update_summary_set,
        &unfo_doc_update_description_set,
        &unfo_doc_update_solution_set,
        NULL
    };

    char* (*getters[])(UNFO_DocUpdate*) = {
        &unfo_doc_update_from_get,
        &unfo_doc_update_status_get,
        &unfo_doc_update_type_get,
        &unfo_doc_update_version_get,
        &unfo_doc_update_id_get,
        &unfo_doc_update_title_get,
        &unfo_doc_update_rights_get,
        &unfo_doc_update_summary_get,
        &unfo_doc_update_description_get,
        &unfo_doc_update_solution_get,
        NULL
    };
    docupdate = (UNFO_DocUpdate*)unfo_object_create(&UNFO_DocUpdate_ObjInfo,
                                                    NULL);
    for (int i=0; setters[i]; i++) {
        setters[i](docupdate, "test val");
    }

    for (int i=0; getters[i]; i++) {
        tmp = getters[i](docupdate);
        ck_assert(strcmp(tmp, "test val") == 0);
    }
    char *str = unfo_object_tostr((UNFO_Object*)docupdate);
    free(str);

    unfo_object_destroy((UNFO_Object*)docupdate);
} END_TEST


START_TEST(test_doc_pkg) {
    UNFO_DocPkg *docpkg;
    char *tmp;

    int (*setters[])(UNFO_DocPkg*, const char*) = {
        &unfo_doc_pkg_name_set,
        &unfo_doc_pkg_version_set,
        &unfo_doc_pkg_release_set,
        &unfo_doc_pkg_epoch_set,
        &unfo_doc_pkg_src_set,
        &unfo_doc_pkg_filename_set,
        &unfo_doc_pkg_sum_set,
        NULL
    };

    char* (*getters[])(UNFO_DocPkg*) = {
        &unfo_doc_pkg_name_get,
        &unfo_doc_pkg_version_get,
        &unfo_doc_pkg_release_get,
        &unfo_doc_pkg_epoch_get,
        &unfo_doc_pkg_src_get,
        &unfo_doc_pkg_filename_get,
        &unfo_doc_pkg_sum_get,
        NULL
    };
    docpkg = (UNFO_DocPkg*)unfo_object_create(&UNFO_DocPkg_ObjInfo, NULL);
    for (int i=0; setters[i]; i++) {
        setters[i](docpkg, "test val");
    }

    for (int i=0; getters[i]; i++) {
        tmp = getters[i](docpkg);
        ck_assert(strcmp(tmp, "test val") == 0);
    }
    unfo_object_destroy((UNFO_Object*)docpkg);
} END_TEST

START_TEST(test_doc_ref) {
    UNFO_DocRef *docref;
    char *tmp;

    int (*setters[])(UNFO_DocRef*, const char*) = {
        &unfo_doc_ref_url_set,
        &unfo_doc_ref_type_set,
        &unfo_doc_ref_title_set,
        NULL
    };

    char* (*getters[])(UNFO_DocRef*) = {
        &unfo_doc_ref_url_get,
        &unfo_doc_ref_type_get,
        &unfo_doc_ref_title_get,
        NULL
    };
    docref = (UNFO_DocRef*)unfo_object_create(&UNFO_DocRef_ObjInfo, NULL);
    for (int i=0; setters[i]; i++) {
        setters[i](docref, "test val");
    }

    for (int i=0; getters[i]; i++) {
        tmp = getters[i](docref);
        ck_assert(strcmp(tmp, "test val") == 0);
    }
    unfo_object_destroy((UNFO_Object*)docref);
} END_TEST

START_TEST(test_doc_coll) {
    UNFO_DocColl *doccoll;
    char *tmp;

    int (*setters[])(UNFO_DocColl*, const char*) = {
        &unfo_doc_coll_short_set,
        &unfo_doc_coll_name_set,
        NULL
    };

    char* (*getters[])(UNFO_DocColl*) = {
        &unfo_doc_coll_short_get,
        &unfo_doc_coll_name_get,
        NULL
    };
    doccoll = (UNFO_DocColl*)unfo_object_create(&UNFO_DocColl_ObjInfo, NULL);
    for (int i=0; setters[i]; i++) {
        setters[i](doccoll, "test val");
    }

    for (int i=0; getters[i]; i++) {
        tmp = getters[i](doccoll);
        ck_assert(strcmp(tmp, "test val") == 0);
    }
    unfo_object_destroy((UNFO_Object*)doccoll);
} END_TEST



Suite* basic_suite(void) {
    Suite *s = suite_create("basic tests");
    TCase *tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_doc);
    tcase_add_test(tc_core, test_doc_update);
    tcase_add_test(tc_core, test_doc_pkg);
    tcase_add_test(tc_core, test_doc_ref);
    tcase_add_test(tc_core, test_doc_coll);
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
