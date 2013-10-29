LIBS += -L/usr/local/lib/ -L/opt/X11/lib/
INCLUDES += -I/usr/local/include/ -I/opt/X11/include/
LDFLAGS += -lglfw3
CPPFLAGS += -fdiagnostics-color=auto -std=c++11 -g
FRAMEWORKS = -framework OpenGL -framework Cocoa -framework IOKit
CXX = clang++

hello: main.cpp Main.hpp gen/fs1.c gen/vs1.c
	$(CXX) -o hello $(CPPFLAGS) $(FRAMEWORKS) $(INCLUDES) $(LIBS) main.cpp $(LDFLAGS)

gen/fs1.c: fs1.fs
	toolchain/escape <$< >$@

gen/vs1.c: vs1.vs
	toolchain/escape <$< >$@