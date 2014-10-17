AC_INIT([eggs], [0.1], [eanger@gmail.com])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_SRCDIR([src/main.cpp])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AC_CONFIG_MACRO_DIR([m4])
AM_PROG_AR

AC_PROG_CXX
AC_LANG([C++])
AX_CXX_COMPILE_STDCXX_11

LT_INIT

# sfml
AC_ARG_WITH([sfml-include-path],
			[AS_HELP_STRING([--with-sfml-include-path],
							[location of the SFML headers])],
			[SFML_CFLAGS="-I$withval"],
			[SFML_CFLAGS=""])
AC_SUBST([SFML_CFLAGS])

AC_ARG_WITH([sfml-lib-path],
			[AS_HELP_STRING([--with-sfml-lib-path],
							[location of the sfml libraries])],
			[SFML_LIB_DIR="-L$withval"],
			[SFML_LIB_DIR=""])
AC_SUBST([SFML_LIB_DIR])

AC_CONFIG_HEADERS([config/config.h])
AC_CONFIG_FILES([Makefile src/Makefile])
AC_OUTPUT
