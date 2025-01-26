# See LICENSE for details
# makefile for ric

.PHONY: all clean dist install uninstall
.DEFAULT: all

include config.mk

PKGFILES = \
	CPPLINT.cfg\
	LICENSE\
	Makefile\
	README.md\
	config.mk\
	doc\
	man\
	src

SRC_DIR = src
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin
DIST_DIR = $(BUILD_DIR)/dist
DIST_BASE_DIR = ric-$(VERSION)

LIBRIC_SRC_DIR = src/ric
LIBRIC_OBJ_DIR = $(BUILD_DIR)/obj/ric
LIBRIC_SRC = $(wildcard $(LIBRIC_SRC_DIR)/*.c)
LIBRIC_OBJ = $(patsubst $(LIBRIC_SRC_DIR)/%.c,$(LIBRIC_OBJ_DIR)/%.o, $(LIBRIC_SRC))
LIBRIC_BIN = $(BUILD_DIR)/libric.a

SRC = $(wildcard $(SRC_DIR)/*.c)
OBJ = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o, $(SRC))
BIN = $(BIN_DIR)/ric


all: $(BIN)
	@echo "ric built"

clean:
	@echo cleaning
	@rm -rf $(BUILD_DIR)

lint:
	@cppcheck --check-level=exhaustive $(SRC_DIR) include
	@cpplint --recursive $(SRC_DIR) include

options:
	@echo "ric compilation flags"
	@echo "VERSION    = $(VERSION)"
	@echo "CC         = $(CC)"
	@echo "CFLAGS     = $(CFLAGS)"
	@echo "CPPFLAGS   = $(CPPFLAGS)"
	@echo "LDFLAGS    = $(LDFLAGS)"
	@echo "LIBRIC_SRC = $(LIBRIC_SRC)"
	@echo "LIBRIC_OBJ = $(LIBRIC_OBJ)"
	@echo "LIBRIC_BIN = $(LIBRIC_BIN)"
	@echo "SRC        = $(SRC)"
	@echo "OBJ        = $(OBJ)"
	@echo "BIN        = $(BIN)"


dist:
	mkdir -p $(DIST_DIR)/$(DIST_BASE_DIR)
	cp -r $(PKGFILES) $(DIST_DIR)/$(DIST_BASE_DIR)
	cd $(DIST_DIR); \
	tar -cz  -f $(DIST_BASE_DIR).tar.gz $(DIST_BASE_DIR); \
	zip -r $(DIST_BASE_DIR).zip $(DIST_BASE_DIR)

install: ric
	@echo installing executable file to $(PREFIX)/bin
	@mkdir -p $(PREFIX)/bin
	@cp -f $(BIN) $(PREFIX)/bin
	@chmod 755 $(PREFIX)/bin/ric

uninstall:
	@echo removing executable file from $(PREFIX)/bin
	@rm -f $(PREFIX)/bin/ric

config.h: config.def.h
	cp $< $@

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBRIC_OBJ_DIR):
	mkdir -p $(LIBRIC_OBJ_DIR)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(LIBRIC_BIN): $(LIBRIC_OBJ) | $(BUILD_DIR)
	ar rcs $@ $^

$(BIN): $(OBJ) $(LIBRIC_BIN) | $(BIN_DIR)
	$(CC) -o $@ $^ $(LDFLAGS)
	
$(LIBRIC_OBJ_DIR)/%.o: $(LIBRIC_SRC_DIR)/%.c | $(LIBRIC_OBJ_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR) config.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c -o $@ $<

