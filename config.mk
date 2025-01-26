# configuration of system
# NOTE: Set version before including

VERSION = 1.0.0

# installation
PREFIX ?= /usr/local
MANPREFIX = ${PREFIX}/share/man

CC       = gcc
INC     += -I. -I./include -I/usr/include
CFLAGS  += -W -Wall -Werror -std=c99 -pedantic -Wno-unused-result ${INC}
CPPFLAGS =\
	-DVERSION=\"${VERSION}\"\
	-D_BSD_SOURCE\
	-D_DEFAULT_SOURCE\
	-D_POSIX_C_SOURCE=200809L
LDFLAGS = -lc
