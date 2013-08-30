import _libpyunfo as libunfo
import unittest
import inspect
import sys

if sys.version_info[0] == 2:
    def _iteritems(obj):
        return obj.iteritems()
else:
    def _iteritems(obj):
        return obj.items()


class BaseObjTestClass(object):

    obj_types = {str: ["some string 1", "test string", "another str",
                       "short string", "ss", "long string string string",
                       "ls"],
                 int: [-1000,2,0,1000],
                 bool: [True, False],
                 libunfo.DocUpdates: [libunfo.DocUpdates(name="update1")],
                 libunfo.DocRefs: [libunfo.DocRefs(title="ref1")],
                 libunfo.DocColls: [libunfo.DocColls(name="update1")],
                 libunfo.DocPkgs: [libunfo.DocPkgs(name="pkg1")]}

    def obj_constructor(self, *args, **kwargs):
        raise NotImplemented

    def test_create(self):
        obj = self.obj_constructor(**self.obj_data[0])

    #@unittest.skip("")
    def test_getset(self):
        obj = self.obj_constructor(**self.obj_data[0])
        data_desc = []
        for x in inspect.getmembers(obj.__class__):
            if (inspect.isdatadescriptor(x[1]) or\
                inspect.isgetsetdescriptor(x[1]) or\
               inspect.ismemberdescriptor(x[1])) and not x[0].startswith("__"):
                data_desc.append(x)

        for attr in data_desc:
            #z = getattr(obj, x[0])
            attr_types = self.obj_getset[attr[0]]
            for _type, vals in _iteritems(self.obj_types):
                if _type not in attr_types:
                    with self.assertRaises(TypeError):
                        setattr(obj, attr[0], vals[0])
                else:
                    for val in vals:
                        setattr(obj, attr[0], val)

            with self.assertRaises(TypeError):
                self.assertTrue(delattr(obj, x[0]), x[0])

            setattr(obj, attr[0], self.obj_types[self.obj_getset[attr[0]][0]][0])
            z = getattr(obj, attr[0])
            self.assertTrue(self.obj_types[self.obj_getset[attr[0]][0]][0] == z)

    #@unittest.skip("")
    def test_list_props(self):
        obj = self.obj_constructor(**self.obj_data[0])
        for member, v in _iteritems(self.obj_list_members):
            _list = getattr(obj, member)
            for x in v:
                _list.append(x)
            for pos, val in zip(range(0, len(v)), v):
                self.assertTrue(_list[pos] == val)

class Doc_Test(BaseObjTestClass, unittest.TestCase):
    obj_getset = {"updates": [libunfo.DocUpdates]}
    obj_data = [{}]
    obj_list_members = {"updates": [libunfo.DocUpdate(id="update1"),
                                    libunfo.DocUpdate(id="update2")]}

    def obj_constructor(self, *args, **kwargs):
        return libunfo.Doc(*args, **kwargs)

class DocUpdate_Test(BaseObjTestClass, unittest.TestCase):
    obj_getset = {"from": [str], "status": [str], "type": [str],
                  "version": [str], "id": [str], "title": [str],
                  "rights": [str], "summary": [str], "description": [str],
                  "solution": [str],
                  "collections": [libunfo.DocColls],
                  "references": [libunfo.DocRefs]}
    obj_data = [{}]
    obj_list_members = {"references": [libunfo.DocRef(id="ref1"),
                                       libunfo.DocRef(id="ref2")],
                        "collections": [libunfo.DocColl(name="col1"),
                                        libunfo.DocColl(name="col2")]}

    def obj_constructor(self, *args, **kwargs):
        return libunfo.DocUpdate(*args, **kwargs)

class DocRef_Test(BaseObjTestClass, unittest.TestCase):
    obj_getset = {"url": [str], "type": [str], "title": [str], "id": [str]}
    obj_data = [{}]
    obj_list_members = {}

    def obj_constructor(self, *args, **kwargs):
        return libunfo.DocRef(*args, **kwargs)

class DocColl_Test(BaseObjTestClass, unittest.TestCase):
    obj_getset = {"name": [str], "short": [str], "packages": [libunfo.DocPkgs]}
    obj_data = [{}]
    obj_list_members = {"packages": [libunfo.DocPkg(name="pkg1"),
                                     libunfo.DocPkg(name="pkg2")]}

    def obj_constructor(self, *args, **kwargs):
        return libunfo.DocColl(*args, **kwargs)

class DocPkg_Test(BaseObjTestClass, unittest.TestCase):
    obj_getset = {"name": [str], "version": [str], "release": [str],
                  "epoch": [str], "arch": [str], "src": [str],
                  "filename": [str], "sum":[str], "sumtype": [str]}
    obj_data = [{}]
    obj_list_members = {}

    def obj_constructor(self, *args, **kwargs):
        return libunfo.DocPkg(*args, **kwargs)

class BaseListTestClass(object):
    list_type = None
    item_type = None
    items_data = []
    items_extra_data = []

    def test_basic(self):
        listobj = self.list_type()
        item = self.item_type(**self.items_data[0])
        listobj.append(item)
        self.assertTrue(listobj[0] == item)
        self.assertTrue(len(listobj) == 1)
        del listobj[0]
        self.assertTrue(len(listobj) == 0)
        with self.assertRaises(IndexError):
            listobj[0]
        listobj.append(item)
        self.assertTrue(listobj[0] == item)
        self.assertTrue(len(listobj) == 1)
        with self.assertRaises(IndexError):
            listobj[1]

    #@unittest.skip("")
    def test_append(self):
        listobj = self.list_type()
        for x in self.items_data:
            listobj.append(self.item_type(**x))
        for x in range(0, len(self.items_data)):
            self.assertTrue(listobj[x] == self.item_type(**self.items_data[x]))

    #@unittest.skip("")
    def test_slice(self):
        listobj = self.list_type()
        for x in self.items_data:
            listobj.append(self.item_type(**x))

        sublist = listobj[0:3]
        self.assertTrue(len(sublist) == 3)
        for x,y in zip(sublist, listobj):
            self.assertTrue(x == y)
        sublist = listobj[3:6]
        self.assertTrue(len(sublist) == 3)
        for x,y in zip(range(0,3),range(3,6)):
            self.assertTrue(sublist[x] == listobj[y])
        sublist = listobj[len(self.items_data): len(self.items_data)+2]
        self.assertTrue(len(sublist) == 0)
        sublist = listobj[len(self.items_data)-2: len(self.items_data)+2]
        self.assertTrue(len(sublist) == 2)

        sublist = listobj[0:6:2]
        self.assertTrue(len(sublist) == 3)
        for x,y in zip(range(0,3), range(0,6,2)):
            self.assertTrue(sublist[x] == listobj[y])

    #@unittest.skip("")
    def test_clear(self):
        listobj = self.list_type()
        for x in self.items_data:
            listobj.append(self.item_type(**x))
        listobj.clear()
        self.assertTrue(len(listobj) == 0)
        with self.assertRaises(IndexError):
            listobj[0]
        for x in self.items_data:
            listobj.append(self.item_type(**x))
        self.assertTrue(len(listobj) == len(self.items_data))

    @unittest.skip("TODO")
    def test_concat(self):
        listobj1 = self.list_type()
        for x in self.items_data[0:4]:
            listobj1.append(self.item_type(**x))
            for k, vals in _iteritems(self.items_extra_data):
                for val in vals[0:3]:
                    self.items_extra_data_setter[k](getattr(listobj1[-1], k),
                                                    val)
        listobj2 = self.list_type()
        listobj = listobj1 + listobj2
        self.assertTrue(listobj == listobj1)
        listobj = listobj2 + listobj1
        self.assertTrue(listobj == listobj1)

        return

        listobj2 = self.list_type()
        for x in self.items_data[3:]:
            listobj2.append(self.item_type(**x))
            for k,vals in _iteritems(self.items_extra_data):
                for val in vals[3:]:
                    self.items_extra_data_setter[k](getattr(listobj2[-1], k),
                                                    val)
        listobj = listobj1 + listobj2
        #print listobj
        self.assertTrue(len(listobj) == len(self.items_data))
        item = listobj[3]
        for k, vals in _iteritems(self.items_extra_data):
            tmpobj = self.item_type()
            for val in vals:
                self.items_extra_data_setter[k](getattr(tmpobj,k), val)
            if type(getattr(item,k)) == libcomps.IdList:
                self.assertTrue(self.items_extra_data_cmp[k](
                                    getattr(item, k),
                                    getattr(tmpobj, k)))


class DocUpdates_Test(BaseListTestClass, unittest.TestCase):
    list_type = libunfo.DocUpdates
    item_type = libunfo.DocUpdate
    items_data = [{"id": "update1"},
                       {"id": "update2"},
                       {"id": "update3"},
                       {"id": "update4"},
                       {"id": "update5"},
                       {"id": "update6"},
                       {"id": "update7"},
                       {"id": "update8"},
                       {"id": "update9"},
                       {"id": "update10"}]

class DocRefs_Test(BaseListTestClass, unittest.TestCase):
    list_type = libunfo.DocRefs
    item_type = libunfo.DocRef
    items_data = [{"title": "reference1"},
                  {"title": "reference2"},
                  {"title": "reference2"},
                  {"title": "reference3"},
                  {"title": "reference4"},
                  {"title": "reference5"},
                  {"title": "reference6"},
                  {"title": "reference7"},
                  {"title": "reference8"},
                  {"title": "reference9"},
                  {"title": "reference10"}]

class DocColls_Test(BaseListTestClass, unittest.TestCase):
    list_type = libunfo.DocColls
    item_type = libunfo.DocColl
    items_data = [{"short": "collection1"},
                  {"short": "collection"},
                  {"short": "collection3"},
                  {"short": "collection4"},
                  {"short": "collection5"},
                  {"short": "collection6"},
                  {"short": "collection7"},
                  {"short": "collection8"},
                  {"short": "collection9"},
                  {"short": "collection10"}]

class DocPkgs_Test(BaseListTestClass, unittest.TestCase):
    list_type = libunfo.DocPkgs
    item_type = libunfo.DocPkg
    items_data = [{"name": "package11"},
                  {"name": "package12"},
                  {"name": "package13"},
                  {"name": "package14"},
                  {"name": "package15"},
                  {"name": "package16"},
                  {"name": "package17"},
                  {"name": "package18"},
                  {"name": "package19"},
                  {"name": "package110"}]

class Doc_Test(unittest.TestCase):
    def test_parse(self):
        doc = libunfo.Doc()
        ret = doc.fromxml_f("update-short.xml")
        doc.xml_f("update-short-gen.xml")
        doc2 = libunfo.Doc()
        ret = doc2.fromxml_f("update-short-gen.xml")
        self.assertTrue(doc == doc2)

    def test_parse1(self):
        print "test parse1"
        doc = libunfo.Doc()
        ret = doc.fromxml_f("update-short1.xml.gz")
        self.assertTrue(ret == -1)
        ret = doc.fromxml_gzf("update-short1.xml.gz")
        self.assertTrue(ret != -1)
        doc.xml_f("update-short-gen1.xml")
        doc2 = libunfo.Doc()
        ret = doc2.fromxml_f("update-short-gen1.xml")
        self.assertTrue(doc == doc2)

if __name__ == "__main__":
    unittest.main()
