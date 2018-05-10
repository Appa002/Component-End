# Component-End
A Library to create web backends using native c++ code. 

This is a modified version of my Native-Backend project.

## Librarys
This project uses boost.asio, boos.test

## Naming conventions
### Header files
* Headers end in .h.
* Headers are grouped into logical groups
* The full path of headers is ``/header/native-backend/{logical group}/{name}``

For instance the header ``TextProcessor.h`` in the logical group parser is stored at ``/header/native-backend/parser/TextProcessor.h``
### Source files
* Souce files end in .cpp
* The location of the source file mirrors the location of the header file
* Therefor the above mentioned header parser.h would have its source file at ``/source/native-backend/parser/parser.cpp``

### Tests
* Unit Tests are stored in the ``/tests`` directory.
* The location of a test is ``/tests/{logical group}/{name of source file without .cpp}/``
* Every source file gets its one folder as you can see
* In that folder are two files a CMakeLists.txt and a tests.cpp file
* The tests.cpp file contains all unit tests with a test suit with the name ``{logical group}_{name of source file without .cpp}_tests_{optinaly any name in case one file has more than one test suit}``

For instance the tests for ``TextProcessor`` are stored in ``/tests/parser/TextProcessor/tests.cpp`` that file contains a test suit called ``parser_TextProcessor_tests``
