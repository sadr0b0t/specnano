mode1:
	gcc gcode_analyzer_test.c ../src/file_processing_method.c ../libanalyzer_full.a ../g01/g01.c -lm

mode2:
	gcc gcode_analyzer_test.c ../src/file_processing_method.c ../libanalyzer.a ../libcommands.a ../g01/g01.c -lm
	
mode3:
	gcc gcode_analyzer_test.c ../src/file_processing_method.c ../libanalyzer.a ../libgcommands.a ../libmcommands.a ../g01/g01.c -lm

all:
	mode1
	
clean:
	rm -rf *~ *.out
