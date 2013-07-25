set(libunfo_SRC unfo.c unfo_doc.c unfo_docupdate.c unfo_objlist.c unfo_obj.c
                unfo_mm.c)
set(libunfo_HEAD unfo.h unfo_doc.h unfo_docupdate.h unfo_objlist.h unfo_obj.h
                unfo_mm.h)

add_library(unfo SHARED ${libunfo_SRC})
