#############################################################################
#                                                                           #
#              Makefile for building a MinGW IndentByFold.dll               #
#                                                                           #
#############################################################################

.SUFFIXES: .dll .o .c .cpp .rc .h

# For x64 build, ARCH=x86_64-w64-mingw32
ARCH = i686-w64-mingw32
CC = $(ARCH)-gcc
CXX = $(ARCH)-g++
AR = $(ARCH)-ar
RANLIB = $(ARCH)-ranlib
WINDRES = $(ARCH)-windres

# The general compiler flags
CFLAGS = -c -DUNICODE
# Enable almost all warnings
CFLAGS += -W -Wall
CXXFLAGS = $(CFLAGS)
LIBS = -static -lshlwapi -lgdi32 -lcomdlg32 -lcomctl32
LDFLAGS = -Wl,--out-implib,$(TARGET) -shared

# Default target is RELEASE, otherwise DEBUG=1
DEBUG ?= 0
ifeq ($(DEBUG), 1)
	# Add DEBUG define, debug info and specific optimizations
	CFLAGS += -D_DEBUG -g -O0
	CXXFLAGS += -D_DEBUG -g -O0
	# Add dependencies flags
	CFLAGS += -MMD -MP
	CXXFLAGS += -MMD -MP
else
	# Set the optimizations
	OPT = -fexpensive-optimizations -Os -O2
	# Strip the dll
	LDOPT = -s
endif

# Silent/verbose commands. For verbose output of commands set V=1
V ?= 0
ifeq ($(V), 0)
	SILENT = @
	V_CC = @echo [CC] $@;
	V_CXX = @echo [CXX] $@;
	V_RES = @echo [WINDRES] $@;
endif

.c.o:
	$(V_CC) $(CC) $(CFLAGS) -o $@ $<

.cpp.o:
	$(V_CXX) $(CXX) $(CXXFLAGS) -o $@ $<

.rc.o:
	$(V_RES) $(WINDRES) $(RESFLAGS) -o $@ -i $<

PROGRAM = IndentByFold
TARGET = $(PROGRAM).dll

now: $(TARGET)

all: clean now

PROGRAM_SRCS_CPP = \
	IBFMenu.cpp \
	IBFPlugin.cpp \
	IndentByFold.cpp \
	NppMessager.cpp \
	NppPlugin.cpp \
	NppPluginMenu.cpp \
	SciMessager.cpp \
	WaitCursor.cpp

PROGRAM_OBJS_CPP=$(PROGRAM_SRCS_CPP:.cpp=.o)

PROGRAM_RC=$(PROGRAM)_res.rc
PROGRAM_OBJS_RC=$(PROGRAM_RC:.rc=.o)

PROGRAM_DEP_CPP=$(PROGRAM_SRCS_CPP:.cpp=.d)

$(PROGRAM).dll: version_git.h $(PROGRAM_OBJS_CPP) $(PROGRAM_OBJS_RC)
	$(V_CXX) $(CXX) -o $@ $(PROGRAM_OBJS_CPP) $(PROGRAM_OBJS_RC) $(LDFLAGS) $(LIBS)

version_git.h:
	$(SILENT) ./version_git.sh

clean:
	@echo Cleaning
	$(SILENT) rm -f $(PROGRAM_OBJS_CPP) $(PROGRAM_OBJS_RC) $(PROGRAM_DEP_CPP) $(PROGRAM).dll $(PROGRAM).a version_git.h tags tags.sqlite

cppcheck:
	@echo Running cppcheck
	$(SILENT) cppcheck --quiet $(PROGRAM_SRCS_CPP)

### code dependencies ###

$(PROGRAM)_res.o: $(PROGRAM)_res.rc Version.h

-include $(PROGRAM_DEP_CPP)
