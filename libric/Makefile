# See LICENSE for details

.PHONY: all clean
.DEFAULT: all

include config.mk

SRC = ${wildcard *.c}
OBJ = ${SRC:.c=.o}
DEP = ${SRC:.c=.d}
BIN = libric.a


all: ${BIN}
	@echo "libric built"


clean:
	@echo cleaning
	@rm -rf ${OBJ} ${DEP} ${BIN}


options:
	@echo "libric compilation flags"
	@echo "CC        = ${CC}"
	@echo "CFLAGS    = ${CFLAGS}"
	@echo "CPPFLAGS  = ${CPPFLAGS}"
	@echo "OUTPUT_OPTION = ${OUTPUT_OPTION}"
	@echo "LDFLAGS   = ${LDFLAGS}"


# configuration for ric
config.h: config.def.h
	cp config.def.h config.h


libric.a: ${OBJ}
	ar rcs $@ ${OBJ}


-include ${DEP}
