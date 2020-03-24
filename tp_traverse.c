#include <Python.h>


/* Append obj to list; return true if error (out of memory), false if OK. */
static int
referentsvisit(PyObject *obj, PyObject *list)
{
    return PyList_Append(list, obj) < 0;
}

static PyObject *
tp_traverse(PyObject *self, PyObject *obj)
{
    PyObject *result = PyList_New(0);
    if (result == NULL)
        return NULL;

    traverseproc traverse;
    traverse = Py_TYPE(obj)->tp_traverse;
    if (! traverse)
        Py_RETURN_NONE;
    if (traverse(obj, (visitproc)referentsvisit, result)) {
        Py_DECREF(result);
        return NULL;
    }
    return result;
}



static PyMethodDef TpTraverseMethods[] = {
    {"tp_traverse", (PyCFunction)tp_traverse, METH_O, ""},
    {NULL, NULL, 0, NULL}
};


PyMODINIT_FUNC
inittp_traverse(void)
{
    PyObject* m;
    m = Py_InitModule("tp_traverse", TpTraverseMethods);
    if (m == NULL)
        return;
}
