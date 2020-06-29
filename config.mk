# configuration of system

VERSION = 1.0

# installation
PREFIX ?= /usr/local
MANPREFIX = ${PREFIX}/share/man


# compiler related
CC = gcc
INCS= -I. -I./include -I/usr/include
CPPFLAGS =\
	-DVERSION=\"${VERSION}\"\
	-D_BSD_SOURCE\
	-D_DEFAULT_SOURCE\
	-D_POSIX_C_SOURCE=200809L
CFLAGS = -W -Wall -Werror -std=c99 -pedantic ${CPPFLAGS} ${INCS}\
	 -Wno-unused-result
# -Wno-unused-result -- issues with write to STDOUT, which I care little in
#  this case
LDFLAGS =
# for a future curses interface in a later day
#LDFLAGS = -lncurses -ltinfo
