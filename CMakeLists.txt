cmake_minimum_required(VERSION 3.10)


project(htmltdcnt VERSION 0.2)
add_subdirectory(src)

install(TARGETS htmltdcnt DESTINATION bin)

enable_testing()
add_test(NAME test1 COMMAND htmltdcnt --version)

