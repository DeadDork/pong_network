#!/bin/bash

# Compiles an ncurses C file parameter, as doing this with make was getting really tricky for ncurses. Eventually, I'll take the time to understand make better, make a good Makefile, and deprecate this script.

################################################################################
# Functions
################################################################################

usage ()
{
	cat << EOF

make_ncurses.sh source_1.c [header_1.h source_2.c ... source_n-1.c header_n-1.h source_n.c header_n.h]

(Where source_x.[c|h] is a valid C file)

N.B. source_1 will be the name of the binary output. This gives you the flexibility to compile one binary with a lot of source files, or a binary from a single source file. However, it will not allow you to compile several binaries at the same time.

EOF
	exit 1
}

compile ()
{
	compiler='gcc'
	compiler_flags='-g -Wall -Wextra'
	linker_flags='-lncurses'
	output="-o $( echo $1 | sed 's/\(.*\)\.c/\1/' )"

	eval ${compiler} ${compiler_flags} ${output} "${@}" ${linker_flags}
}

################################################################################
# Main
################################################################################

# If no C program files are specified in the argument list.
[ $# -lt 1 ] && usage

# Compile all of the files in the argument list.
compile "${@}"

exit 0
