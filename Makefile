# See LICENSE for details
# makefile for ric

.PHONY: all clean dist install uninstall
.DEFAULT: all

VERSION = 1.0
LIBRIC_DIR = ./libric
LIBRIC = ${LIBRIC_DIR}/libric.a
INC = -I${LIBRIC_DIR}/include

include config.mk


# Files for distribution
PKGFILES = \
	LICENSE\
	Makefile\
	README.md\
	config.def.h\
	config.mk\
	doc\
	include\
	libric\
	man\
	ric.c\
	util.c


SRC = ${wildcard *.c}
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}
BIN = ric


all: ${BIN}
	@echo "ric built"


clean:
	@echo cleaning
	@rm -rf ${OBJ} ${DEP} ${BIN} *.tar.gz
	@make -C ${LIBRIC_DIR} clean


options:
	@echo "ric compilation flags"
	@echo "CC        = ${CC}"
	@echo "CFLAGS    = ${CFLAGS}"
	@echo "CPPFLAGS  = ${CPPFLAGS}"
	@echo "OUTPUT_OPTION = ${OUTPUT_OPTION}"
	@echo "LDFLAGS   = ${LDFLAGS}"


dist: clean
	mkdir -p ric-${VERSION}
	cp -r ${PKGFILES} ric-${VERSION}
	tar -cz  -f ric-${VERSION}.tar.gz ric-${VERSION}
	rm -r ric-${VERSION}


install: ric
	@echo installing executable file to ${PREFIX}/bin
	@mkdir -p ${PREFIX}/bin
	@cp -f ${BIN} ${PREFIX}/bin
	@chmod 755 ${PREFIX}/bin/ric
	@echo installing manual page to ${MANPREFIX}/man1
	@mkdir -p ${MANPREFIX}/man1
	@cp man/ric.1 ${MANPREFIX}/man1/ric.1
	@chmod 644 ${MANPREFIX}/man1/ric.1


uninstall:
	@echo removing executable file from ${PREFIX}/bin
	@rm -f ${PREFIX}/bin/ric ${MANPREFIX}/man1/ric.1


config.h: config.def.h
	cp config.def.h config.h


${LIBRIC}:
	make -C ${LIBRIC_DIR}


ric: ${OBJ} ${LIBRIC}

-include ${DEP}
