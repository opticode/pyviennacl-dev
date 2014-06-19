#include <iostream>
#include <typeinfo>

#include "viennacl.h"

PYVCL_SUBMODULE(vector_int);
PYVCL_SUBMODULE(vector_long);
PYVCL_SUBMODULE(vector_uint);
PYVCL_SUBMODULE(vector_ulong);
PYVCL_SUBMODULE(vector_float);
PYVCL_SUBMODULE(vector_double);

PYVCL_SUBMODULE(dense_matrix_int);
PYVCL_SUBMODULE(dense_matrix_long);
PYVCL_SUBMODULE(dense_matrix_uint);
PYVCL_SUBMODULE(dense_matrix_ulong);
PYVCL_SUBMODULE(dense_matrix_float);
PYVCL_SUBMODULE(dense_matrix_double);

PYVCL_SUBMODULE(structured_matrices);

PYVCL_SUBMODULE(compressed_matrix);
PYVCL_SUBMODULE(coordinate_matrix);
PYVCL_SUBMODULE(ell_matrix);
PYVCL_SUBMODULE(hyb_matrix);

PYVCL_SUBMODULE(preconditioners);
PYVCL_SUBMODULE(direct_solvers);
PYVCL_SUBMODULE(iterative_solvers);

PYVCL_SUBMODULE(extra_functions);
PYVCL_SUBMODULE(eig);
PYVCL_SUBMODULE(bandwidth_reduction);

PYVCL_SUBMODULE(scheduler);
PYVCL_SUBMODULE(platform_support);
PYVCL_SUBMODULE(opencl_support);

/*******************************
  Python module initialisation
 *******************************/
void translate_string_exception(const char* e)
{
  // Use the Python 'C' API to set up an exception object
  PyErr_SetString(PyExc_RuntimeError, e);
}

BOOST_PYTHON_MODULE(_viennacl)
{
  // specify that this module is actually a package
  bp::object package = bp::scope();
  package.attr("__path__") = "_viennacl";

  bp::register_exception_translator<const char*>            
    (&translate_string_exception);                            

  np::initialize();

  // TODO: integrate version into build process
  bp::scope().attr("__version__") = bp::object("1.5.2");

  bp::def("backend_finish", vcl::backend::finish);

#define EXPORT_SCALAR_CLASS(TYPE)                                       \
  bp::class_<vcl::scalar<TYPE> >("scalar_" #TYPE)                       \
    .def(bp::init<TYPE>())                                              \
    .def(bp::init<vcl::scalar<TYPE> >())                                \
    .def("to_host", &vcl_scalar_to_host<TYPE>)

  EXPORT_SCALAR_CLASS(int);
  EXPORT_SCALAR_CLASS(uint);
  EXPORT_SCALAR_CLASS(long);
  EXPORT_SCALAR_CLASS(ulong);
  EXPORT_SCALAR_CLASS(float);
  EXPORT_SCALAR_CLASS(double);

  bp::class_<vcl::range>("range",
                         bp::init<vcl::vcl_size_t, vcl::vcl_size_t>());
  bp::class_<vcl::slice>("slice",
                         bp::init<vcl::vcl_size_t, vcl::vcl_size_t, vcl::vcl_size_t>());

  export_vector_int();
  export_vector_long();
  export_vector_uint();
  export_vector_ulong();
  export_vector_float();
  export_vector_double();

  export_dense_matrix_int();
  export_dense_matrix_long();
  export_dense_matrix_uint();
  export_dense_matrix_ulong();
  export_dense_matrix_float();
  export_dense_matrix_double();

  export_structured_matrices();

  export_compressed_matrix();
  export_coordinate_matrix();
  export_ell_matrix();
  export_hyb_matrix();
 
  export_preconditioners();
  export_direct_solvers();
  export_iterative_solvers();

  export_extra_functions();
  export_eig();
  //export_bandwidth_reduction();

  export_scheduler();
  export_platform_support();
  export_opencl_support();
  
}

