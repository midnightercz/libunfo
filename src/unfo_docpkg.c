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
    .deep_copy = &unfo_doc_pkg_copy_u
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
