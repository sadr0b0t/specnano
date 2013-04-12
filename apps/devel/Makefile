GCODE_HOME=../../gcode

SOURCE_FILES=gcode_test.c\
        ${GCODE_HOME}/test/test.c \
        ${GCODE_HOME}/test/gcode_analyzer_test.c \
        ${GCODE_HOME}/test/g01_test.c \
        ${GCODE_HOME}/src/file_processing_method.c \
        ${GCODE_HOME}/src/gcode.c ${GCODE_HOME}/src/G_commands.c \
        ${GCODE_HOME}/src/M_commands.c \
        ${GCODE_HOME}/g01/src/g01.c \
        ${GCODE_HOME}/g02/src/g02.c	\
        ${GCODE_HOME}/g03/src/g03.c	

self_test:
	gcc ${SOURCE_FILES} -lm

all:
	self_test
	
clean:
	rm -rf *~ *.out *.exe

