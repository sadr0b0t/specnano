mode1:
	gcc gcode_analyzer_test.c ../file_processing_method.c ../libanalyzer_full.a -lm

mode2:
	gcc gcode_analyzer_test.c ../file_processing_method.c ../libanalyzer.a ../libcommands.a -lm
	
mode3:
	gcc gcode_analyzer_test.c ../file_processing_method.c ../libanalyzer.a ../libgcommands.a ../libmcommands.a -lm

all:
	mode1
	
clean:
	rm -rf *~ *.out
