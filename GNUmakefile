name := GAGGSim
G4TARGET := $(name)
G4EXLIB := true

ifndef G4INSTALL
  G4INSTALL = ../../..
endif

COMMON_DIR = $(HOME)/common
LIB_DIR = $(HOME)/lib
EXTRA_INCLUDES = -I./ -I./include -I$(COMMON_DIR)

.PHONY: all
all: lib bin

include $(G4INSTALL)/config/architecture.gmk

CPPFLAGS += $(shell $(ROOTSYS)/bin/root-config --cflags) $(EXTRA_INCLUDES)
LDFLAGS  += $(shell $(ROOTSYS)/bin/root-config --libs)
CPPFLAGS  += -Wl,--no-as-needed -Woverloaded-virtual -Wno-shadow -Wno-unused-variable
LDFLAGS  += -Wl,--no-as-needed -Woverloaded-virtual -Wno-shadow -Wno-unused-variable
EXTRALIBS = -L$(LIB_DIR) -lCommandLineInterface

include $(G4INSTALL)/config/binmake.gmk

cleanup:
	rm -f *~ include/*~ src/*~
