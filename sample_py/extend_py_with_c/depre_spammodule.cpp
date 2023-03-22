/*
 * @Author: avert-win
 * @Date: 2022-06-29 16:37:34
 * @LastEditTime: 2022-06-29 19:09:02
 * @FilePath: /ProgramDaily/extend_py_with_c/depre_spammodule.cpp
 * @Description: Extending Python with C or C++(deprecated).
 *      All the object-creating functions must deal with exceptions,
 *      you can do it completely explicitly by yourself if you need,
 *      and even define a type of exception.
 * @LastEditors: avert-win
 */
#define PY_SSIZE_T_CLEAN
// you must include Python.h first to avoid error in pre-preocess.
#include<python3.6m/Python.h>
#include<iostream>

/**
 * c function to be called in python script always has two arguments,
 * args are pointer to a tuple consist of arguments, self is object pointer.
 * 
 * PyArg_ParseTuple() checks the argument types and converts them to C values.
 * PyLong_FromLong() transform a C int to Python int object.
 */
static PyObject *
spam_system(PyObject *self, PyObject *args)
{
    // you don't need to allocate for parsing arguments.
    // use spiral rule to determine whether the pointer are mutable or not.
    const char *command;        
    int sts;
    if(!PyArg_ParseTuple(args, "s", &command))
        return NULL
    sts = system(command);
    return PyLong_FromLong(sts);
}

/**
 * to return None in python, use Py_INCREF and increase the reference count first.
 */
static PyObject *
do_nothing(PyObject *self, PyObject *args)
{
    Py_INCREF(Py_None);
    return Py_None;
}

/**
 * @brief this is to be passed to the module's initialization function.
 * 
 */
static struct PyModuleDef spammodule = 
{
    PyModuleDef_HEAD_INIT,
    "spam",     // name of module
    spam_doc,   // module documentation
    -1,
    SpamMethods
}

/**
 * @brief when python program imports the module for the first time, this function is called.
 * The name must be PyInit_module, where `module` is the name of module.
 * This is also the only one that is not static item in the module file.
 */
PyMODINIT_FUNC
PyInit_spam(void)
{
    return PyModule_Create(&spammodule);
}