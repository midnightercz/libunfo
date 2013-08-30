#include "h/unfo_docpkg.h"

void unfo_doc_pkg_create(UNFO_DocPkg* docpkg, UNFO_Object **args){
    (void)args;
    docpkg->attrs = unfo_rtree_create(&__unfo_str_clone,
                                      &__unfo_str_clone, &free);
}
UNFO_CREATE_u(doc_pkg, UNFO_DocPkg)

UNFO_DocPkg* unfo_doc_pkg_copy(UNFO_DocPkg *docpkg) {
    UNFO_DocPkg *ret;
    ret = (UNFO_DocPkg*) unfo_object_copy((UNFO_Object*)docpkg);
    return ret;
}
UNFO_COPY_u(doc_pkg, UNFO_DocPkg)

void unfo_doc_pkg_destroy(UNFO_DocPkg *docpkg){
    unfo_rtree_destroy(docpkg->attrs);
}
UNFO_DESTROY_u(doc_pkg, UNFO_DocPkg)

char* unfo_doc_pkg_str(UNFO_DocPkg *obj) {
    char *ret, *tmp;
    int len;
    const int wrap = strlen("<UNFO_DocPkg >");
    static const char *attrs[] = {"name", "version", "release", "epoch",
                                  "arch", "src", "filename", "sum", "sumtype"};
    tmp = attrs2str(obj->attrs, attrs, 9);
    len = strlen(tmp);
    ret = malloc(sizeof(char) * (len + wrap + 1));
    sprintf(ret, "<UNFO_DocPkg %s>", tmp);
    free(tmp);
    return ret;
}

char* unfo_doc_pkg_str_u(UNFO_Object *obj) {
    return unfo_doc_pkg_str((UNFO_DocPkg*)obj);
}

signed char unfo_doc_pkg_cmp(UNFO_DocPkg* pkg1, UNFO_DocPkg *pkg2){
    static const char *attrs[] = {"name", "version", "release", "epoch",
                                  "arch", "src", "filename", "sum", "sumtype"};
    static int attrs_len = 9;
    int i;
    char *tmp1, *tmp2;

    for (i = 0; i < attrs_len; i++) {
        tmp1 = unfo_rtree_get(pkg1->attrs, attrs[i]);
        tmp2 = unfo_rtree_get(pkg2->attrs, attrs[i]);
        if (!__unfo_strcmp(tmp1, tmp2)) {
            printf("pkg differ %s %s|\n", tmp1, tmp2);
            return 0;
        }
    }
    return 1;
}
UNFO_CMP_u(doc_pkg, UNFO_DocPkg)

UNFO_GETSET_ATTR(UNFO_DocPkg, doc_pkg, name)
UNFO_GETSET_ATTR(UNFO_DocPkg, doc_pkg, version)
UNFO_GETSET_ATTR(UNFO_DocPkg, doc_pkg, release)
UNFO_GETSET_ATTR(UNFO_DocPkg, doc_pkg, epoch)
UNFO_GETSET_ATTR(UNFO_DocPkg, doc_pkg, arch)
UNFO_GETSET_ATTR(UNFO_DocPkg, doc_pkg, src)
UNFO_GETSET_ATTR(UNFO_DocPkg, doc_pkg, filename)
UNFO_GETSET_ATTR(UNFO_DocPkg, doc_pkg, sum)
UNFO_GETSET_ATTR(UNFO_DocPkg, doc_pkg, sumtype)

UNFO_ObjectInfo UNFO_DocPkg_ObjInfo = {
    .obj_size = sizeof(UNFO_DocPkg),
    .constructor = &unfo_doc_pkg_create_u,
    .destructor = &unfo_doc_pkg_destroy_u,
    .deep_copy = &unfo_doc_pkg_copy_u,
    .to_str = &unfo_doc_pkg_str_u,
    .obj_cmp = &unfo_doc_pkg_cmp_u
};

void unfo_doc_pkg_xml(UNFO_Object *obj, xmlTextWriterPtr writer) {
    const char *val;

    xmlTextWriterStartElement(writer, BAD_CAST "package");
    val = unfo_doc_pkg_name_get((UNFO_DocPkg*)obj);
    xmlTextWriterWriteAttribute(writer, BAD_CAST "name", BAD_CAST val);
    val = unfo_doc_pkg_version_get((UNFO_DocPkg*)obj);
    xmlTextWriterWriteAttribute(writer, BAD_CAST "version", BAD_CAST val);
    val = unfo_doc_pkg_release_get((UNFO_DocPkg*)obj);
    xmlTextWriterWriteAttribute(writer, BAD_CAST "release", BAD_CAST val);
    val = unfo_doc_pkg_epoch_get((UNFO_DocPkg*)obj);
    xmlTextWriterWriteAttribute(writer, BAD_CAST "epoch", BAD_CAST val);
    val = unfo_doc_pkg_arch_get((UNFO_DocPkg*)obj);
    xmlTextWriterWriteAttribute(writer, BAD_CAST "arch", BAD_CAST val);
    val = unfo_doc_pkg_src_get((UNFO_DocPkg*)obj);
    xmlTextWriterWriteAttribute(writer, BAD_CAST "src", BAD_CAST val);
    xmlTextWriterStartElement(writer, BAD_CAST "filename");
    val = unfo_doc_pkg_filename_get((UNFO_DocPkg*)obj);
    xmlTextWriterWriteString(writer, BAD_CAST val);
    xmlTextWriterEndElement(writer);
    xmlTextWriterStartElement(writer, BAD_CAST "sum");
    val = unfo_doc_pkg_sumtype_get((UNFO_DocPkg*)obj);
    xmlTextWriterWriteAttribute(writer, BAD_CAST "type", BAD_CAST val);
    val = unfo_doc_pkg_sum_get((UNFO_DocPkg*)obj);
    xmlTextWriterWriteString(writer, BAD_CAST val);
    xmlTextWriterEndElement(writer);

    xmlTextWriterEndElement(writer);
}
