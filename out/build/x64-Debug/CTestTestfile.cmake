# CMake generated Testfile for 
# Source directory: C:/git-repo/sentinex
# Build directory: C:/git-repo/sentinex/out/build/x64-Debug
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test([=[sentinex.example]=] "C:/git-repo/sentinex/out/build/x64-Debug/sentinex-test.exe")
set_tests_properties([=[sentinex.example]=] PROPERTIES  _BACKTRACE_TRIPLES "C:/git-repo/sentinex/CMakeLists.txt;87;add_test;C:/git-repo/sentinex/CMakeLists.txt;0;")
subdirs("_deps/doctest-build")
subdirs("_deps/rapidcheck-build")
