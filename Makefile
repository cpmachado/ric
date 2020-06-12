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


# source files for tests
TEST_SRC= \
	test/hname_test.c

# object files for libric
LIBRICOBJ = ${LIBRICSRC:src/ric/%.c=lib/ric/%.o}
LIBRIC = lib/libric.a

# object files for ric
OBJ = ${SRC:src/%.c=lib/%.o}
BIN = ric

# object files for libric for testing
# - has debug symbols
# - has performance information
LIBRICOBJ_DEBUG = ${LIBRICSRC:src/ric/%.c=lib/debug/ric/%.o}
LIBRIC_DEBUG = lib/debug/libric.a


# object files for test
TEST_OBJ = ${TEST_SRC:test/%.c=lib/debug/%.o}
TEST_BIN = hname_test



# object and output files
OUTFILES =\
	${BIN} lib\
	${TEST_BIN}\
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

lib/debug:
	@echo Creating lib/debug
	@mkdir -p lib/debug

lib/debug/ric:
	@echo Creating lib/debug/ric
	@mkdir -p lib/debug/ric

# rules for compilation

lib/%.o: src/%.c config.h | lib
	@echo CC -c $<
	@${CC} ${CFLAGS} -c -o $@ $<

lib/ric/%.o: src/ric/%.c | lib/ric
	@echo CC -c $<
	@${CC} ${CFLAGS} -c -o $@ $<

lib/debug/%.o: test/%.c | lib/debug
	@echo CC -c $<
	@${CC} ${CFLAGS} -c -o $@ $<

lib/debug/ric/%.o: src/ric/%.c | lib/debug/ric
	@echo CC -c $<
	@${CC} ${CFLAGS} -g -pg -c -o $@ $<


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


# libric object files for debug
lib/debug/ric/hname.o: src/ric/hname.c
lib/debug/ric/nslook.o: src/ric/nslook.c
lib/debug/ric/tcp_client.o: src/ric/tcp_client.c
lib/debug/ric/tcp_server.o: src/ric/tcp_server.c
lib/debug/ric/udp_client.o: src/ric/udp_client.c
lib/debug/ric/udp_server.o: src/ric/udp_server.c


# generate libric with debug
lib/debug/libric.a: ${LIBRICOBJ_DEBUG} | lib/debug
	@echo Making static libric with debug information
	@echo AR -o $@
	@ar rcs $@ ${LIBRICOBJ_DEBUG}


# test object files
lib/debug/hname_test.o: test/hname_test.c include/ric.h


# generate tests
hname_test: ${TEST_OBJ} ${LIBRIC_DEBUG}
	@echo Making $@
	@echo CC -o $@
	@${CC} -o $@ ${TEST_OBJ} ${LIBRIC_DEBUG} ${LDFLAGS} -pg


.PHONY: all clean dist install uninstall
