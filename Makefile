LIBS += -L/usr/local/lib/
INCLUDES += -I/usr/local/include/
LDFLAGS += -lglfw3
CPPFLAGS += -fdiagnostics-color=auto -std=c++11 -g
FRAMEWORKS = -framework OpenGL -framework Cocoa -framework IOKit
CXX = g++-4.9

hello: main.cpp Main.hpp gen/fs1.c gen/vs1.c
	$(CXX) -o hello $(CPPFLAGS) $(FRAMEWORKS) $(INCLUDES) $(LIBS) main.cpp $(LDFLAGS)

gen/fs1.c: fs1.fs
	toolchain/escape <$< >$@

gen/vs1.c: vs1.vs
	toolchain/escape <$< >$@