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
                 bool: [True, False]}

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
            z = getattr(obj, x[0])
            attr_types = self.obj_getset[attr[0]]
            for _type, vals in _iteritems(self.obj_types):
                if _type not in attr_types:
                    #print (attr[0], vals[0])
                    with self.assertRaises(TypeError):
                        setattr(obj, attr[0], vals[0])
                else:
                    for val in vals:
                        setattr(obj, attr[0], val)

            with self.assertRaises(TypeError):
                self.assertTrue(delattr(obj, x[0]), x[0])

            setattr(obj, attr[0], self.obj_types[self.obj_getset[attr[0]]])
            z = getattr(obj, attr[0])
            self.assertTrue(self.obj_types[self.obj_getset[attr[0]]] == z)

class DocUpdate_Test(BaseObjTestClass, unittest.TestCase):
    obj_getset = {"from": [str], "status": [str], "type": [str],
                  "version": [str], "id": [str], "title": [str],
                  "rights": [str], "summary": [str], "description": [str],
                  "solution": [str]}
    obj_data = [{}]

    def obj_constructor(self):
        return libunfo.DocUpdate()


if __name__ == "__main__":
    unittest.main()
