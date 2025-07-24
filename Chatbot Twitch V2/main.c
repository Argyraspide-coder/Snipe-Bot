#include <Python.h>

int wmain(int argc, wchar_t **argv)
{
    PyStatus status;
    PyConfig config;
    PyConfig_InitIsolatedConfig(&config);
    status = Py_InitializeFromConfig(&config);
    if (PyStatus_Exception(status)) {
        PyConfig_Clear(&config);
        if (PyStatus_IsExit(status)) {
            return status.exitcode;
        }
        Py_ExitStatusException(status);
        return -1;
    }

    // CPython is now initialised

    int exitCode = -1;
    PyObject *module = PyImport_ImportModule("Snipebot");
    if (module) {
        // Pass any more arguments here
        PyObject *result = PyObject_CallMethod(module, "main", NULL);
        if (result) {
            exitCode = 0;
            Py_DECREF(result);
        }
        Py_DECREF(module);
    }
    if (exitCode != 0) {
        PyErr_Print();
    }
    Py_Finalize();
    return exitCode;
}