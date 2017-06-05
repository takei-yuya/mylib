ACLOCAL_AMFLAGS=-I m4

AM_CFLAGS= -Wall -g -O0
AM_CXXFLAGS= -Wall -g -O0

EXTRA_DIST= .gitignore m4/.gitignore cpplint.py CPPLINT.cfg
cpp_sources=

include_HEADERS=
include_HEADERS+= src/utf8.hpp
cpp_sources+=$(include_HEADERS)

bin_PROGRAMS=
bin_PROGRAMS+= bins/space_separator
bins_space_separator_SOURCES= src/space_separator.cpp
cpp_sources+=$(bins_space_separator_SOURCES)

lib_LTLIBRARIES=
lib_LTLIBRARIES+= objs/lib0946.la
objs_lib0946_la_SOURCES= src/lib0946.cpp

check_LTLIBRARIES=
check_LTLIBRARIES+= objs/libgtest.la
objs_libgtest_la_SOURCES= \
  gtest/gtest-all.cc \
  gtest/gtest_main.cc \
  gtest/gtest.h
objs_libgtest_la_LIBADD= -lpthread

check_PROGRAMS=
check_PROGRAMS+= tests/utf8_test
tests_utf8_test_SOURCES= src/utf8_test.cpp
tests_utf8_test_LDADD= -lpthread objs/libgtest.la
cpp_sources+=$(tests_utf8_test_SOURCES)

TESTS= $(check_PROGRAMS)

check-local:
	$(top_srcdir)/cpplint.py $(cpp_sources)
