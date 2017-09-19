#############################################################################
#                                                                           #
#              Makefile for building a MinGW IndentByFold.dll               #
#                                                                           #
#############################################################################

.SUFFIXES: .dll .o .c .cpp .rc .h

ARCH = i686-w64-mingw32
CC = $(ARCH)-gcc
CXX = $(ARCH)-g++
AR = $(ARCH)-ar
RANLIB = $(ARCH)-ranlib
WINDRES = $(ARCH)-windres

#
CFLAGS = -c -O2 -DUNICODE -mtune=i686 -MMD -MP
CXXFLAGS = $(CFLAGS) -W -Wall -gstabs -mwindows
RESFLAGS = -O coff
LIBS = -static -lshlwapi -lgdi32 -lcomdlg32 -lcomctl32
LDFLAGS = -Wl,--out-implib,$(TARGET) -shared

.c.o:
	$(CC) $(CFLAGS) -o $@ $<

.cpp.o:
	$(CXX) $(CXXFLAGS) -o $@ $<

.rc.o:
	$(WINDRES) $(RESFLAGS) -o $@ -i $<

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
	$(CXX) -o $@ $(PROGRAM_OBJS_CPP) $(PROGRAM_OBJS_RC) $(LDFLAGS) $(LIBS)

version_git.h:
	$(SILENT) ./version_git.sh

clean:
	rm -f $(PROGRAM_OBJS_CPP) $(PROGRAM_OBJS_RC) $(PROGRAM_DEP_CPP) $(PROGRAM).dll $(PROGRAM).a tags tags.sqlite

cppcheck:
	cppcheck --quiet $(PROGRAM_SRCS_CPP)

### code dependencies ###

$(PROGRAM)_res.o: $(PROGRAM)_res.rc Version.h

-include $(PROGRAM_DEP_CPP)
