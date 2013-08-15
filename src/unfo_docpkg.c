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

