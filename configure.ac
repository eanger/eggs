AC_INIT([eggs], [0.1], [eanger@gmail.com])
AC_CONFIG_AUX_DIR([config])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AC_CONFIG_MACRO_DIR([m4])
AM_PROG_AR

AC_PROG_CXX
AC_LANG([C++])
AX_CXX_COMPILE_STDCXX_11

LT_INIT

# ncursesw

AC_ARG_WITH([ncursesw-include-path],
			[AS_HELP_STRING([--with-ncursesw-include-path],
							[location of the ncursesw headers, defaults to /usr/include/ncursesw])],
			[NCURSESW_CFLAGS="-I$withval"],
			[NCURSESW_CFLAGS='-I/usr/include/ncursesw'])
AC_SUBST([NCURSESW_CFLAGS])

AC_ARG_WITH([ncursesw-lib-path],
			[AS_HELP_STRING([--with-ncursesw-lib-path],
							[location of the ncursesw libraries])],
			[NCURSESW_LIBS="-L$withval -lncursesw"],
			[NCURSESW_LIBS='-lncursesw'])
AC_SUBST([NCURSESW_LIBS])

# panelw
AC_ARG_WITH([panelw-include-path],
			[AS_HELP_STRING([--with-panelw-include-path],
							[location of the panelw headers, defaults to /usr/include/ncursesw])],
			[NCURSESW_CFLAGS="-I$withval"],
			[NCURSESW_CFLAGS='-I/usr/include/ncursesw'])
AC_SUBST([NCURSESW_CFLAGS])

AC_ARG_WITH([panelw-lib-path],
			[AS_HELP_STRING([--with-panelw-lib-path],
							[location of the panelw libraries])],
			[PANELW_LIBS="-L$withval -lpanelw"],
			[PANELW_LIBS='-lpanelw'])
AC_SUBST([PANELW_LIBS])

AC_CONFIG_HEADERS([config/config.h])
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
