.PHONY: all clean

DPREDEF= -D_FILE_OFFSET_BITS=64 -D__WXMSW__
INCLUDE= -I/mingw64/lib/wx/include/msw-unicode-static-3.3/ \
	-I/mingw64/include/wx-3.3/

RCINCLUDE= -I/mingw64/include/wx-3.3/

WX_CXXFLAGS= -Wall -Wundef -Wunused-parameter -Wno-ctor-dtor-privacy \
 -Woverloaded-virtual -O2

CXXFLAGS= $(DPREDEF) $(INCLUDE) $(WX_CXXFLAGS)

#LDFLAGS_GUI= -mwindows
LDFLAGS= $(LDFLAGS_GUI)

OBJS= main.o resource.o
LIBS= -lwx_mswu_core-3.3  -lwx_baseu-3.3 --static -lpng -lz -lwxregexu-3.3\
 -lz -lrpcrt4 -loleaut32 -lole32 -luuid -lcurl -luxtheme -lwinspool -lwinmm\
 -lshell32 -lshlwapi -lcomctl32 -lcomdlg32 -ladvapi32 -lversion -lws2_32\
 -lgdi32 -loleacc -lwinhttp   -lz -lrpcrt4 -loleaut32 -lole32 -luuid -lcurl\
 -luxtheme -lwinspool -lwinmm -lshell32 -lshlwapi -lcomctl32 -lcomdlg32\
 -ladvapi32 -lversion -lws2_32 -lgdi32 -loleacc -lwinhttp 

all: wxWdgTest.exe
	
clean:
	$(RM) *.o
	$(RM) *.exe

wxWdgTest.exe: $(OBJS)
	g++ $^ $(LDFLAGS) $(LIBS) -o $@

.cpp.o:
	g++ $< $(CXXFLAGS) $(INCLUDE) -c -o $@ 

resource.o: resource.rc
	windres -i $< $(RCINCLUDE) -o $@
	
