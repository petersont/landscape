
CURRENT = run

OPTIMIZATION = -O9
DEBUG = -g0
ODEBUG = $(DEBUG)
OSTYPE = $(shell uname -msr)

OBJ_DIR = obj
SRC_DIR = visualizer

SDL_STATIC_LIBS = \
	-L/usr/local/lib \
	-lSDL2 \
	-lm \
	-liconv \
	-Wl,-framework,OpenGL \
	-Wl,-framework,ForceFeedback \
	-Wl,-framework,Cocoa \
	-Wl,-framework,Carbon -Wl,-framework,IOKit \
	-Wl,-framework,CoreAudio \
	-Wl,-framework,AudioToolbox \
	-Wl,-framework,AudioUnit

SDL_C_FLAGS = \
	-I/usr/local/include/SDL2 \
	-D_THREAD_SAFE

BIN = bin


ifeq ($(findstring Linux,$(OSTYPE)),Linux)
	GLFLAGS = -lGLU -lGL -L/usr/X11R6/lib/ -lXmu -lXi -lXext -lX11 -lXt -lpthread
	GLUTFLAGS = -lglut
endif

ifeq ($(findstring CYGWIN,$(OSTYPE)),CYGWIN)
	GLFLAGS = -L/usr/X11R6/lib -L/usr/lib/w32api -lglu32 -lopengl32 -lXm -lpthread
	GLUTFLAGS = -lglut32
endif

ifeq ($(findstring Darwin,$(OSTYPE)),Darwin)
	GLFLAGS = -framework Cocoa -framework QuartzCore -framework OpenGL
	GLUTFLAGS =  -framework GLUT
endif



CORE = \
	$(OBJ_DIR)/math3d.o \
	$(OBJ_DIR)/util.o \
	$(OBJ_DIR)/panapp.o \
	$(OBJ_DIR)/graphapp.o

run-glut: out.graph bin/glut-visualizer
	./bin/glut-visualizer out.graph

run-sdl: out.graph bin/sdl-visualizer
	./bin/sdl-visualizer out.graph

out.graph: landscape.py graph.py
	python landscape.py > out.graph

bin/glut-visualizer: $(CORE) $(SRC_DIR)/glut-main.cpp
	c++ $(DEBUG) $(OPTIMIZATION) $(CORE) $(SRC_DIR)/glut-main.cpp -o bin/glut-visualizer $(GLFLAGS) $(GLUTFLAGS)

bin/sdl-visualizer: sdl $(CORE) $(SRC_DIR)/sdl-main.cpp
	c++ $(DEBUG) $(OPTIMIZATION) $(CORE) \
		$(SRC_DIR)/sdl-main.cpp \
		$(SDL_C_FLAGS) \
		$(SDL_STATIC_LIBS) \
		-o bin/sdl-visualizer

## .o files

$(OBJ_DIR)/util.o: $(SRC_DIR)/util.cpp $(SRC_DIR)/util.h
	c++ $(ODEBUG) $(OPTIMIZATION) -c $(SRC_DIR)/util.cpp -o $(OBJ_DIR)/util.o

$(OBJ_DIR)/panapp.o: $(SRC_DIR)/panapp.cpp $(SRC_DIR)/panapp.h
	c++ $(ODEBUG) $(OPTIMIZATION) -c $(SRC_DIR)/panapp.cpp -o $(OBJ_DIR)/panapp.o

$(OBJ_DIR)/graphapp.o: $(SRC_DIR)/graphapp.cpp $(SRC_DIR)/graphapp.h
	c++ $(ODEBUG) $(OPTIMIZATION) -c $(SRC_DIR)/graphapp.cpp -o $(OBJ_DIR)/graphapp.o

$(OBJ_DIR)/math3d.o: $(SRC_DIR)/math3d.cpp $(SRC_DIR)/math3d.h
	c++ $(ODEBUG) $(OPTIMIZATION) -c $(SRC_DIR)/math3d.cpp -o $(OBJ_DIR)/math3d.o

## sdl

$(SRC_DIR)/sdl/Makefile: $(SRC_DIR)/sdl/configure
	cd $(SRC_DIR)/sdl && ./configure

sdl: $(SRC_DIR)/sdl/Makefile
	cd $(SRC_DIR)/sdl && make install

$(SRC_DIR)/sdl/configure:
	git submodule init
	git submodule update --recursive


clean:
	rm -f $(OBJ_DIR)/*.o
	rm bin/*
	rm *.graph
	rm *.pyc

