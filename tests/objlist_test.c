#include "../src/h/unfo_objlist.h"
#include "../src/h/unfo_obj.h"
#include "objlist_test.h"

#include <string.h>
#include <check.h>

typedef struct {
    UNFO_Object_HEAD
    char *name;
} TestObj;

void testobj_destroy_u(UNFO_Object * obj) {
    free(((TestObj*)obj)->name);
    //free(obj);
}

void testobj_create(UNFO_Object *uobj, UNFO_Object **args) {
    if (args && args[0]) {

    }
    ((TestObj*)uobj)->name = NULL;
}

void testobj_set_name(TestObj *testobj, char *name) {
    testobj->name = malloc(sizeof(char)*(strlen(name)+1));
    strcpy(testobj->name, name);
}


signed char testobj_cmp(UNFO_Object* obj1, UNFO_Object *obj2) {
   return strcmp(((TestObj*)obj1)->name, ((TestObj*)obj2)->name) == 0;
}

UNFO_ObjectInfo TestObj_ObjInfo =  {
    .obj_size = sizeof(TestObj),
    .constructor = &testobj_create,
    .destructor = &testobj_destroy_u,
    .obj_cmp = &testobj_cmp
};

START_TEST(test_objlist_mmtest) {
    UNFO_ObjList *list;
    UNFO_Object *testobj, *backup;

    list = (UNFO_ObjList*)unfo_object_create(&UNFO_ObjList_ObjInfo, NULL);
    testobj = unfo_object_create(&TestObj_ObjInfo, NULL);
    testobj_set_name((TestObj*)testobj, "test1");
    unfo_objlist_append(list, testobj);
    backup = unfo_object_copy(testobj);

    unfo_object_destroy(testobj);
    unfo_object_destroy((UNFO_Object*)list);

    printf("%s\n", ((TestObj*)backup)->name);

    unfo_object_destroy(testobj);

}END_TEST

START_TEST(test_objlist_append) {
    UNFO_ObjList *list;
    UNFO_Object *testobj;
    char *names[] = {"test1", "test2", "test3", "test4", "test5"};
    list = (UNFO_ObjList*)unfo_object_create(&UNFO_ObjList_ObjInfo, NULL);

    for (unsigned int x = 0; x < 5; x++) {
        testobj = unfo_object_create(&TestObj_ObjInfo, NULL);
        testobj_set_name((TestObj*)testobj, names[x]);
        unfo_objlist_append(list, testobj);
        unfo_object_destroy(testobj);
    }

    for (unsigned int x = 0; x < 5; x++) {
        testobj = unfo_objlist_get(list, x);
        ck_assert(testobj != NULL);
        ck_assert(strcmp(((TestObj*)testobj)->name, names[x])==0);
        unfo_object_destroy(testobj);
    }
    unfo_object_destroy((UNFO_Object*)list);
}END_TEST

START_TEST(test_objlist_insert) {
    UNFO_ObjList *list;
    UNFO_Object *testobj;
    char *names[] = {"test1", "test2", "test3", "test4", "test5", "test6"};
    unsigned pos[] = {0, 1, 3, 2, 4, 1};
    int rets[] = {1, 1, 0, 1, 0, 1};
    int pos2[] = {0, 5, 1, 3, -1, -1};
    list = (UNFO_ObjList*)unfo_object_create(&UNFO_ObjList_ObjInfo, NULL);
    int z;

    for (unsigned int x = 0; x < 6; x++) {
        testobj = unfo_object_create(&TestObj_ObjInfo, NULL);
        testobj_set_name((TestObj*)testobj, names[x]);
        z = unfo_objlist_insert_at(list, pos[x], testobj);
        ck_assert(z == rets[x]);
        unfo_object_destroy(testobj);
    }

    for (unsigned int x = 0; x < list->len; x++) {
        //if (pos2[x] == -1) continue;
        testobj = unfo_objlist_get(list, x);
        unfo_object_destroy(testobj);
        //printf("pos %d\n", pos2[x]);
        ck_assert(testobj != NULL);
        ck_assert(strcmp(((TestObj*)testobj)->name, names[pos2[x]])==0);
    }
    unfo_object_destroy((UNFO_Object*)list);
}END_TEST

START_TEST(test_objlist_sublist) {
    UNFO_ObjList *list, *list2, *list3;
    UNFO_Object *testobj1, *testobj2;
    char *names[] = {"test1", "test2", "test3", "test4", "test5", "test6",
                     "test7", "test8", "test9", "test10"};

    list = (UNFO_ObjList*)unfo_object_create(&UNFO_ObjList_ObjInfo, NULL);
    for (unsigned int x = 0; x < 10; x++) {
        testobj1 = unfo_object_create(&TestObj_ObjInfo, NULL);
        testobj_set_name((TestObj*)testobj1, names[x]);
        unfo_objlist_append(list, testobj1);
        unfo_object_destroy(testobj1);
    }
    list2 = unfo_objlist_sublist_it(list->first, NULL);
    ck_assert_msg(list2->len == 10, "%d != 10", list2->len);
    for (unsigned int x = 0; x < 10; x++) {
        testobj1 = unfo_objlist_get(list, x);
        testobj2 = unfo_objlist_get(list2, x);
        ck_assert(strcmp(((TestObj*)testobj1)->name,
                         ((TestObj*)testobj2)->name) == 0);
        unfo_object_destroy(testobj1);
        unfo_object_destroy(testobj2);
    }
    list3 = unfo_objlist_sublist_it(list->first, list->first);
    ck_assert(list3->len == 0);
    unfo_object_destroy((UNFO_Object*)list2);
    unfo_object_destroy((UNFO_Object*)list3);

    list2 = unfo_objlist_sublist_indexed(list, 2, 6);
    ck_assert(list2->len == 4);
    for (unsigned int x = 2; x < 6; x++) {
        testobj1 = unfo_objlist_get(list, x);
        testobj2 = unfo_objlist_get(list2, x-2);
        ck_assert(strcmp(((TestObj*)testobj1)->name,
                         ((TestObj*)testobj2)->name) == 0);
        unfo_object_destroy(testobj1);
        unfo_object_destroy(testobj2);
    }
    list3 = unfo_objlist_sublist_it_step(list->first, NULL, 2);
    for (unsigned int x = 0; x < 10; x+=2) {
        testobj1 = unfo_objlist_get(list, x);
        testobj2 = unfo_objlist_get(list3, x/2);
        ck_assert(strcmp(((TestObj*)testobj1)->name,
                         ((TestObj*)testobj2)->name) == 0);
        unfo_object_destroy(testobj1);
        unfo_object_destroy(testobj2);
    }
    unfo_object_destroy((UNFO_Object*)list);
    unfo_object_destroy((UNFO_Object*)list2);
    unfo_object_destroy((UNFO_Object*)list3);
}END_TEST

START_TEST(test_objlist_remove) {
    UNFO_ObjList *list;
    UNFO_Object *testobj1;
    char *names[] = {"test1", "test2", "test3", "test4", "test5", "test6",
                     "test7", "test8", "test9", "test10"};
    int ret;

    list = (UNFO_ObjList*)unfo_object_create(&UNFO_ObjList_ObjInfo, NULL);
    for (unsigned int x = 0; x < 10; x++) {
        testobj1 = unfo_object_create(&TestObj_ObjInfo, NULL);
        testobj_set_name((TestObj*)testobj1, names[x]);
        unfo_objlist_append(list, testobj1);
        unfo_object_destroy(testobj1);
    }
    ret = unfo_objlist_remove_at(list, 0);
    ck_assert(ret == 1);
    testobj1 = unfo_objlist_get(list, 0);
    ck_assert_msg(strcmp(((TestObj*)testobj1)->name, "test2") == 0,
                  "zero item should be 'test2' instead of '%s'",
                   ((TestObj*)testobj1)->name);
    unfo_object_destroy(testobj1);

    ret = unfo_objlist_remove_at(list, 8);
    ck_assert(ret == 1);
    testobj1 = unfo_objlist_get(list, 8);
    ck_assert_msg(testobj1 == NULL,
                  "8th item should be NULL");
    unfo_object_destroy(testobj1);
    unfo_object_destroy((UNFO_Object*)list);
}END_TEST

Suite* basic_suite(void) {
    Suite *s = suite_create("basic tests");
    TCase *tc_core = tcase_create("Core");
    tcase_add_test(tc_core, test_objlist_mmtest);
    tcase_add_test(tc_core, test_objlist_append);
    tcase_add_test(tc_core, test_objlist_insert);
    tcase_add_test(tc_core, test_objlist_sublist);
    tcase_add_test(tc_core, test_objlist_remove);
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

