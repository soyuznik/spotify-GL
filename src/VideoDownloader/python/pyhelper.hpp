#pragma once
//
//----- WARNING ----
//   ALWAYS INCLUDE THIS FILE FIRST
//   AND IF YOU START_PYTHON INSIDE A
//   FUNCTION ALWAYS INLINE IT
//   ELSE YOU WILL GET SOME RANDOM
//   ERRORS IN PYTHON HEADERS AND
//   YOU WILL START CRYING AND HAVE
//   NOT A SINGLE CLUE WHAT TO DO!!
//
//   ALSO IF YOU CANT COMPILE
//   BECAUSE OF FILESYSTEM UPDATE
//   C++ version to 17.
//   DEFINE PYSRCDIR AS THE DIR
//   WHERE ALL YOUR MODULES ARE
//   INSTALLED AND DONT FORGET
//   TO INCLUDE THE PYTHON .lib
//   and .dll
//
#include "Python.h"
#define PYSRCDIR "/python_libs/"
#define __pycall  inline



class CPyInstance
{
public:
	CPyInstance()
	{
		Py_Initialize();
    };

	~CPyInstance(){
		Py_Finalize();	
    };
};

#define PY_SSIZE_T_CLEAN
#include <conio.h>
#include <iostream>
#include <string>
#include <filesystem>

//set PATH to the script
__pycall void  __initialize_path(std::string path__) {
    using namespace std;
    std::filesystem::path path = std::filesystem::current_path();
    std::string _path = path.string();
    std::replace(_path.begin(), _path.end(), '\\', '/');;
    try {
        PyRun_SimpleString("import sys");
    }
    catch (...){
        cout << "[ERROR] -> INITIALIZE START PYTHON FIRST !\n";
        return;
    };
    PyRun_SimpleString((string("sys.path.append(\"") + _path + string(path__) + string("\")")).c_str());

    

    return;
};
// CALL THIS ONLY IN "inline" FUNCTIONS!!!!
#define START_PYTHON CPyInstance inst; __initialize_path(PYSRCDIR);
/// START PYTHON BEFORE RUN_PYTHON           or          RUN_PYTHONI
///                   |(without inline)\           |(run python inline (I))
#define RUN_PYTHON(x) PyRun_SimpleString(x);
#define RUN_PYTHONI(x) PyRun_SimpleString(#x);


