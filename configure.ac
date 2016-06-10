AC_PREREQ([2.64])
AC_INIT([meter-plugin], [1.0])
AC_CONFIG_SRCDIR([src/main.c])
# Store the auxiliary build tools (e.g., install-sh, config.sub, config.guess)
# in this dir (build-aux)
# AC_CONFIG_AUX_DIR([build-aux])
AC_PROG_CC
AC_CHECK_LIB(m, floor)
AC_PROG_INSTALL
# Init automake, and specify this program use relaxed structures.
# i.e. this program doesn't follow the gnu coding standards, and doesn't have
# ChangeLog, COPYING, AUTHORS, INSTALL, README etc. files.
# AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AM_INIT_AUTOMAKE([subdir-objects])
AC_CONFIG_FILES([Makefile])
AC_OUTPUT
