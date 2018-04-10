#include <python_action_node.h>
#include <Python.h>

PyObject *python_state_;
PyObject *python_tick_fn_, *python_halt_fn_, *python_finalize_fn_; //TODO Figure out why if It cannot find Python.h in the header

BT::PythonActionNode::PythonActionNode(std::string name, std::string filename, BlackBoardCmd *blackboard_cmd) : BT::ActionNode::ActionNode(name)
{
    filename_ = filename;
    //std::string filename_wout_extension = filename;

    blackboard_cmd_ = blackboard_cmd;

    // Initializing the python api
    Py_Initialize();

    // PyUnicode_FromString wants the filename without extension .py
    std::string filename_wout_extension = filename.substr(0, filename.size() - 3);
    const char *cstr = filename_wout_extension.c_str();

    // creating python module. Needed to know from which script call the functions tick, halt, etc.
    PyObject *python_module = PyUnicode_FromString((char *)cstr);
    python_state_ = PyImport_Import(python_module);

    // creating the PyObject related to the functions in the python script.
    PyObject *python_init_fn = PyObject_GetAttrString(python_state_, (char *)"init");
    python_tick_fn_ = PyObject_GetAttrString(python_state_, (char *)"tick");
    python_halt_fn_ = PyObject_GetAttrString(python_state_, (char *)"halt");
    python_finalize_fn_ = PyObject_GetAttrString(python_state_, (char *)"finalize");

    // calling the function init in the python script with empty argument
    PyObject *empty_args = PyTuple_New(0);
    PyObject_CallObject(python_init_fn, empty_args);
}

BT::ReturnStatus BT::PythonActionNode::Tick()
{
    set_status(BT::RUNNING);
    // calling the function tick in the python script with empty argument
    PyObject *empty_args = PyTuple_New(0);
    PyObject *python_result = PyObject_CallObject(python_tick_fn_, empty_args);

    // parsing the final return from the python script. The python script has to return True (Success) or False (Failure).
    // The Running status is taken for granted while running the script

    bool has_succeeded = PyObject_IsTrue(python_result);

    if (has_succeeded)
    {
        set_status(BT::SUCCESS);
        return BT::SUCCESS;
    }
    else
    {
        set_status(BT::FAILURE);
        return BT::FAILURE;
    }
}

void BT::PythonActionNode::Halt()
{
    // calling the function finalize in the python script with empty argument
    PyObject *empty_args = PyTuple_New(0);
    PyObject *python_result = PyObject_CallObject(python_halt_fn_, empty_args);
}
void BT::PythonActionNode::Finalize()
{
    // calling the function finalize in the python script with empty argument
    PyObject *empty_args = PyTuple_New(0);
    PyObject *python_result = PyObject_CallObject(python_finalize_fn_, empty_args);

    // Finalizing the python api
    Py_Finalize();
}
