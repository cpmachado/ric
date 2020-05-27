# See LICENSE for details
# makefile for ric

include config.mk


# Files for distribution
PKGFILES = \
	LICENSE\
	Makefile\
	README.md\
	config.def.h\
	config.mk\
	man\
	src


# source files for libric
LIBRICSRC = \
	src/ric/hname.c\
	src/ric/nslook.c\
	src/ric/tcp_client.c\
	src/ric/tcp_server.c\
	src/ric/udp_client.c\
	src/ric/udp_server.c


# source files for ric
SRC = \
	src/ric.c\
	src/util.c


# object files for libric
LIBRICOBJ = ${LIBRICSRC:.c=.o}
LIBRIC = lib/libric.a


# object files for ric
OBJ = ${SRC:.c=.o}
BIN = ric


# object and output files
OUTFILES =\
	${BIN} ${OBJ}\
	${LIBRIC} ${LIBRICOBJ}\
	ric-${VERSION} ric-${VERSION}.tar.gz


all: ${BIN}
	@echo "all built"


clean:
	@echo cleaning
	@rm -rf ${OUTFILES}


options:
	@echo "CC        = ${CC}"
	@echo "CFLAGS    = ${CFLAGS}"
	@echo "CPPFLAGS  = ${CPPFLAGS}"
	@echo "LDFLAGS   = ${LDFLAGS}"
	@echo "OBJ       = ${OBJ}"
	@echo "BIN       = ${BIN}"
	@echo "LIBRICOBJ = ${LIBRICOBJ}"
	@echo "LIBRIC    = ${LIBRIC}"


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


# rules for compilation
.c.o:
	@echo CC -c $<
	@${CC} ${CFLAGS} -c -o $@ $<


# configuration for ric
config.h: config.def.h
	cp config.def.h config.h


# libric object files 
src/ric/hname.o: src/ric/hname.c
src/ric/nslook.o: src/ric/nslook.c
src/ric/tcp_client.o: src/ric/tcp_client.c
src/ric/tcp_server.o: src/ric/tcp_server.c
src/ric/udp_client.o: src/ric/udp_client.c
src/ric/udp_server.o: src/ric/udp_server.c


# ric program object files
src/ric.o: src/ric.c config.h include/ric.h
src/util.o: src/util.c config.h config.mk


# generate libric
lib/libric.a: ${LIBRICOBJ}
	@echo AR -o $@
	@mkdir -p lib
	@ar rcs $@ ${LIBRICOBJ}


# generate ric
ric: ${OBJ} ${LIBRIC}
	@echo CC -o $@
	@${CC} -o $@ ${OBJ} ${LIBRIC} ${LDFLAGS}


.PHONY: all clean dist install uninstall
