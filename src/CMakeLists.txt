set(libunfo_SRC unfo.c unfo_doc.c unfo_docupdate.c unfo_objlist.c unfo_obj.c
                unfo_mm.c unfo_hslist.c unfo_dict.c unfo_docref.c unfo_docpkg.c
                unfo_doccoll.c
                unfo_utils.c)
set(libunfo_HEAD unfo.h unfo_doc.h unfo_docupdate.h unfo_objlist.h unfo_obj.h
                unfo_mm.h unfo_hslist.h unfo_dict.h unfo_docref.h unfo_docpkg.h
                unfo_doccoll.h
                unfo_utils.h)

add_library(unfo SHARED ${libunfo_SRC})
