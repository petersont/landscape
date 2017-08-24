
CURRENT = run

OPTIMIZATION = -O9
DEBUG = -g0
ODEBUG = $(DEBUG)
OSTYPE = $(shell uname -msr)

OBJ_DIR = obj
SRC_DIR = visualizer

ifeq ($(findstring Linux,$(OSTYPE)),Linux)
	GLFLAGS = -lglut -lGLU -lGL -L/usr/X11R6/lib/ -lXmu -lXi -lXext -lX11 -lXt -lpthread
endif

ifeq ($(findstring CYGWIN,$(OSTYPE)),CYGWIN)
	GLFLAGS = -L/usr/X11R6/lib -L/usr/lib/w32api -lglut32 -lglu32 -lopengl32 -lXm -lpthread
endif

ifeq ($(findstring Darwin,$(OSTYPE)),Darwin)
	GLFLAGS = -framework Cocoa -framework QuartzCore -framework GLUT -framework OpenGL
endif

CORE = \
	$(OBJ_DIR)/math3d.o \
	$(OBJ_DIR)/util.o \
	$(OBJ_DIR)/panapp.o \
	$(OBJ_DIR)/graphapp.o

run: out.graph vis.exe
	./vis.exe out.graph

out.graph: landscape.py graph.py
	python landscape.py > out.graph

vis.exe: $(CORE) $(SRC_DIR)/visualizer.cpp
	c++ $(DEBUG) $(OPTIMIZATION) $(CORE) $(SRC_DIR)/visualizer.cpp -o vis.exe $(GLFLAGS)


## .o files

$(OBJ_DIR)/util.o: $(SRC_DIR)/util.cpp $(SRC_DIR)/util.h
	c++ $(ODEBUG) $(OPTIMIZATION) -c $(SRC_DIR)/util.cpp -o $(OBJ_DIR)/util.o

$(OBJ_DIR)/panapp.o: $(SRC_DIR)/panapp.cpp $(SRC_DIR)/panapp.h
	c++ $(ODEBUG) $(OPTIMIZATION) -c $(SRC_DIR)/panapp.cpp -o $(OBJ_DIR)/panapp.o

$(OBJ_DIR)/graphapp.o: $(SRC_DIR)/graphapp.cpp $(SRC_DIR)/graphapp.h
	c++ $(ODEBUG) $(OPTIMIZATION) -c $(SRC_DIR)/graphapp.cpp -o $(OBJ_DIR)/graphapp.o

$(OBJ_DIR)/math3d.o: $(SRC_DIR)/math3d.cpp $(SRC_DIR)/math3d.h
	c++ $(ODEBUG) $(OPTIMIZATION) -c $(SRC_DIR)/math3d.cpp -o $(OBJ_DIR)/math3d.o


clean:
	rm -f $(OBJ_DIR)/*.o
	rm vis.exe
	rm *.graph
	rm *.pyc

