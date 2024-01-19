# COMPILER OPTIONS
CC ?= cc
PKGCONFIG = $(shell which pkg-config)
CFLAGS = -g -fvisibility=hidden -fPIC -shared -Iinclude
LIBS = -ldl

# FILE AND PROJECT NAMES
NAME = contorno
LIBTARGET = lib$(NAME).so 
PCTARGET = $(NAME).pc

# FILES
SOURCES = $(wildcard src/*.c)

# PATHS
PREFIX = /usr
PKGCONFIG_PATHS = $(shell $(PKGCONFIG) --variable pc_path pkg-config)
PKGCONFIG_PATHS_LIST := $(subst :, ,$(PKGCONFIG_PATHS:v%=%))
PKGCONFIG_PATH = $(word 1,$(PKGCONFIG_PATHS_LIST))

# PKGCONFIG FILE
define PCFILE
prefix=$(PREFIX)
exec_prefix=$${prefix}
includedir=$${prefix}/include
libdir=$${prefix}/lib

Name: $(NAME)
Version: 0.0
Description: Nice
Cflags: -I$${includedir}
Libs: -L$${libdir} -l$(NAME)
endef

# EXAMPLES
EXAMPLES_SOURCES = $(wildcard examples/*.c)
EXAMPLES = $(basename $(EXAMPLES_SOURCES))
EXAMPLE_CFLAGS = -g
EXAMPLE_LIBS = $(shell $(PKGCONFIG) --libs $(NAME))

# RULES
all: $(LIBTARGET) $(PCTARGET) 

clean:
	rm -f $(LIBTARGET) $(PCTARGET)
	rm -f $(EXAMPLES)
		
uninstall:
	rm -f $(word 1,$(PKGCONFIG_PATHS_LIST))/$(PCTARGET)
	rm -f $(PREFIX)/include/$(NAME).h
	rm -f $(PREFIX)/lib/$(LIBTARGET)

install: all $(PKGCONFIG_PATH)
	install $(PCTARGET) $(PKGCONFIG_PATH)/$(PCTARGET)
	install include/$(NAME).h $(PREFIX)/include/$(NAME).h
	install $(LIBTARGET) $(PREFIX)/lib/$(LIBTARGET)
	
examples: $(EXAMPLES)
	
$(LIBTARGET): $(SOURCES)
	$(CC) $(^) -o ${LIBTARGET} ${CFLAGS} ${LIBS}

$(PCTARGET):
	$(file > $@,$(PCFILE))
    
$(EXAMPLES): %: %.c
	$(CC) $< -o $@ ${EXAMPLE_CFLAGS} ${EXAMPLE_LIBS}

$(PKGCONFIG_PATH):
	mkdir -p $(PKGCONFIG_PATH)
        
.PHONY: clean uninstall install examples
