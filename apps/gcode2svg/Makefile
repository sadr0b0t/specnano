GCODE_HOME=../../gcode

SOURCE_FILES=gcode2svg.c \
        ${GCODE_HOME}/src/file_processing_method.c \
        ${GCODE_HOME}/src/gcode.c \
        ${GCODE_HOME}/src/G_commands.c \
        ${GCODE_HOME}/src/M_commands.c \
        ${GCODE_HOME}/g01/src/g01.c

self_test:
	gcc ${SOURCE_FILES}

all:
	self_test

clean:
	rm -rf *~ *.out

