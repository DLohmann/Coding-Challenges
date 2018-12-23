
SOURCES := $(shell echo $(./)*.cpp)
DEPENDS = $(SOURCES:.cpp=.d)
OBJECTS = $(SOURCES:.cpp=.o)
OS = $(shell uname) # For Mac OS detection (by Rolando Yanez, Raymond Harris)
PROGRAM = max_points

#######################################################################

# OPTFLAGS = -g  # for debug
OPTFLAGS = -g
CC       = g++
CFLAGS   = -w -std=c++14 $(OPTFLAGS)

# Glut and OpenGL library flags
#ifeq ($(strip $(OS)),Darwin)
#	LDFLAGS = -framework GLUT -framework OpenGL
#else
#	LDFLAGS = -lGL -lglut
#endif
LDFLAGS =

#######################################################################

all: $(PROGRAM)

$(PROGRAM):$(OBJECTS)
	$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $@

clean:
	$(RM) $(OBJECTS) $(DEPENDS)
	$(RM) $(PROGRAM)
	$(RM) *~

#######################################################################

%.o: %.cpp
	$(CC) -c $(CFLAGS) $< -o $@

%.d: %.cpp
	$(CC) -MM $(CFLAGS) $< > $@

#######################################################################

ifneq ($(MAKECMDGOALS),clean)
-include $(DEPENDS)
endif

#######################################################################
