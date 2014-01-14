/**
 * @author Andre Anjos <andre.anjos@idiap.ch>
 * @date Mon 13 Jan 2014 17:25:32 CET
 *
 * @brief Implementation of the Linear Activation function
 */

#define XBOB_MACHINE_MODULE
#include <xbob.machine/api.h>

PyDoc_STRVAR(s_linearactivation_str,
    XBOB_EXT_MODULE_PREFIX ".LinearActivation");

PyDoc_STRVAR(s_linearactivation_doc,
"LinearActivation([C=1.0]) -> new LinearActivation\n\
\n\
Computes :math:`f(z) = C \\cdot z` as activation function.\n\
\n\
The constructor builds a new linear activation function\n\
with a given constant. Don't use this if you just want to\n\
set constant to the default value (1.0). In such a case,\n\
prefer to use the more efficient :py:class:`IdentityActivation`.\n\
");

static int PyBobMachineLinearActivation_init
(PyBobMachineLinearActivationObject* self, PyObject* args, PyObject* kwds) {

  /* Parses input arguments in a single shot */
  static const char* const_kwlist[] = {0};
  static char** kwlist = const_cast<char**>(const_kwlist);

  double C = 1.0;

  if (!PyArg_ParseTupleAndKeywords(args, kwds, "|d", kwlist, &C)) return -1;

  try {
    self->base = new bob::machine::LinearActivation(C);
  }
  catch (std::exception& ex) {
    PyErr_SetString(PyExc_RuntimeError, ex.what());
  }
  catch (...) {
    PyErr_Format(PyExc_RuntimeError, "cannot create new object of type `%s' - unknown exception thrown", s_linearactivation_str);
  }

  self->parent.base = self->base;

  if (PyErr_Occurred()) return -1;

  return 0;

}

static void PyBobMachineLinearActivation_delete
(PyBobMachineLinearActivationObject* self) {

  delete self->base;
  self->parent.base = 0;
  self->base = 0;
  self->parent.ob_type->tp_free((PyObject*)self);

}

PyDoc_STRVAR(s_C_str, "C");
PyDoc_STRVAR(s_C_doc,
"The multiplication factor for the linear function (read-only)"
);

static PyObject* PyBobMachineLinearActivation_C
(PyBobMachineLinearActivationObject* self) {

  return Py_BuildValue("d", self->base->C());

}

static PyGetSetDef PyBobMachineLinearActivation_getseters[] = {
    {
      s_C_str,
      (getter)PyBobMachineLinearActivation_C,
      0,
      s_C_doc,
      0
    },
    {0}  /* Sentinel */
};

PyTypeObject PyBobMachineLinearActivation_Type = {
    PyObject_HEAD_INIT(0)
    0,                                                  /*ob_size*/
    0,                                                  /*tp_name*/
    sizeof(PyBobMachineLinearActivationObject),         /*tp_basicsize*/
    0,                                                  /*tp_itemsize*/
    (destructor)PyBobMachineLinearActivation_delete,    /*tp_dealloc*/
    0,                                                  /*tp_print*/
    0,                                                  /*tp_getattr*/
    0,                                                  /*tp_setattr*/
    0,                                                  /*tp_compare*/
    0,                                                  /*tp_repr*/
    0,                                                  /*tp_as_number*/
    0,                                                  /*tp_as_sequence*/
    0,                                                  /*tp_as_mapping*/
    0,                                                  /*tp_hash */
    0,                                                  /*tp_call*/
    0,                                                  /*tp_str*/
    0,                                                  /*tp_getattro*/
    0,                                                  /*tp_setattro*/
    0,                                                  /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE,           /*tp_flags*/
    s_linearactivation_doc,                             /* tp_doc */
    0,		                                              /* tp_traverse */
    0,		                                              /* tp_clear */
    0,                                                  /* tp_richcompare */
    0,		                                              /* tp_weaklistoffset */
    0,		                                              /* tp_iter */
    0,		                                              /* tp_iternext */
    0,                                                  /* tp_methods */
    0,                                                  /* tp_members */
    PyBobMachineLinearActivation_getseters,             /* tp_getset */
    0,                                                  /* tp_base */
    0,                                                  /* tp_dict */
    0,                                                  /* tp_descr_get */
    0,                                                  /* tp_descr_set */
    0,                                                  /* tp_dictoffset */
    (initproc)PyBobMachineLinearActivation_init,        /* tp_init */
    0,                                                  /* tp_alloc */
    0,                                                  /* tp_new */
};