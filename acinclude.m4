
AC_DEFUN([AX_PROTOBUF],
[
	AC_ARG_WITH([protobuf], AC_HELP_STRING([--with-protobuf=DIR], [enable protobuf support]))

	PROTOBUF_INCLUDES=""
	PROTOBUF_LIBS=""
	PROTOBUF_COMPILER="protoc"

	have_protobuf=false

	if test "x$with_protobuf" != "x" ; then

		AC_MSG_CHECKING([for protobuf headers])

		protobuf_path=""

		for path in "$with_protobuf" /usr/local /usr /opt ; do
			if test -r "$path/include/google/protobuf/descriptor.h" ; then
				protobuf_path=$path
				break
			fi
		done

		if test -n "$protobuf_path" ; then
			AC_MSG_RESULT([found])

			PROTOBUF_INCLUDES="-I$protobuf_path/include"
			if test "$FORCE_STATIC_LINK" = "yes" ; then
				PROTOBUF_LIBS="$protobuf_path/lib/libprotobuf.a"
			else
				PROTOBUF_LIBS="-L$protobuf_path/lib -lprotobuf"
			fi

			AC_MSG_CHECKING([for protobuf compiler])

			if test -x "$protobuf_path/bin/protoc" ; then
				AC_MSG_RESULT([found])
				PROTOBUF_COMPILER="$protobuf_path/bin/protoc"
				have_protobuf=true
			else
				AC_MSG_RESULT([not found])
			fi
		else
			AC_MSG_RESULT([not found])
		fi
	fi

	which $PROTOBUF_COMPILER 1>/dev/null 2>&1
	if test $? -ne 0; then
		AC_MSG_ERROR([Could not find protoc compiler.])
	fi

	AM_CONDITIONAL(ENABLE_PROTOBUF, test "x$have_protobuf" = "xtrue")

	AC_SUBST([PROTOBUF_LIBS])
	AC_SUBST([PROTOBUF_INCLUDES])
	AC_SUBST([PROTOBUF_COMPILER])

])
