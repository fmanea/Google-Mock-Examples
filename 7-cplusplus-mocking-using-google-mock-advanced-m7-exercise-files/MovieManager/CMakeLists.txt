cmake_minimum_required(VERSION 2.8.9)
project (GOOGLETEST)

file(GLOB SOURCES_TEST MovieDataFetcher/*.cpp MovieDataDetcherTests/*.cpp)
file(GLOB SOURCES_REAL MovieDataFetcher/*.cpp MovieDataFetcherRunner/*.cpp)
#find_package (PkgConfig REQUIRED)
#pkg_check_modules (GTEST REQUIRED gtest)
#if (GTEST_FOUND)
#  message(STATUS "gtest include path:    "  ${GTEST_INCLUDE_DIRS})
#  include_directories(${GTEST_INCLUDE_DIRS})
#endif (GTEST_FOUND)

INCLUDE_DIRECTORIES(thirdparty/include/)
LINK_DIRECTORIES(thirdparty/lib)
#For the shared library:
set ( PROJECT_LINK_LIBS libcurl.so libgmock.a libgtest.a libpthread.so)

add_executable(runtest ${SOURCES_TEST})
target_include_directories(runtest PUBLIC MovieDataDetcherTests MovieDataFetcher)
target_compile_options(runtest PUBLIC -std=c++11)
target_link_libraries(runtest ${PROJECT_LINK_LIBS} )
install(TARGETS runtest DESTINATION /bin)

add_executable(runReal ${SOURCES_REAL})
target_include_directories(runReal PUBLIC MovieDataDetcherRunner MovieDataFetcher)
target_compile_options(runReal PUBLIC -std=c++11)
target_link_libraries(runReal ${PROJECT_LINK_LIBS} )
install(TARGETS runReal DESTINATION /bin)
