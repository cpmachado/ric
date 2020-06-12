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
LIBRICOBJ = ${LIBRICSRC:src/ric/%.c=lib/ric/%.o}
LIBRIC = lib/libric.a


# object files for ric
OBJ = ${SRC:src/%.c=lib/%.o}
BIN = ric


# object and output files
OUTFILES =\
	${BIN} lib\
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


# configuration for ric
config.h: config.def.h
	cp config.def.h config.h


# build out directories
lib:
	@echo Creating lib
	@mkdir lib

lib/ric:
	@echo Creating lib/ric
	@mkdir -p lib/ric


# rules for compilation

lib/%.o: src/%.c config.h | lib
	@echo CC -c $<
	@${CC} ${CFLAGS} -c -o $@ $<

lib/ric/%.o: src/ric/%.c | lib/ric
	@echo CC -c $<
	@${CC} ${CFLAGS} -c -o $@ $<



# libric object files 
lib/ric/hname.o: src/ric/hname.c
lib/ric/nslook.o: src/ric/nslook.c
lib/ric/tcp_client.o: src/ric/tcp_client.c
lib/ric/tcp_server.o: src/ric/tcp_server.c
lib/ric/udp_client.o: src/ric/udp_client.c
lib/ric/udp_server.o: src/ric/udp_server.c

# ric program object files
lib/ric.o: src/ric.c include/ric.h include/util.h
lib/util.o: src/util.c config.mk


# generate libric
lib/libric.a: ${LIBRICOBJ} | lib
	@echo Making static libric
	@echo AR -o $@
	@ar rcs $@ ${LIBRICOBJ}


# generate ric
ric: ${OBJ} ${LIBRIC}
	@echo Making ric
	@echo CC -o $@
	@${CC} -o $@ ${OBJ} ${LIBRIC} ${LDFLAGS}


.PHONY: all clean dist install uninstall
