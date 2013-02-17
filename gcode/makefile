all:
	gcc -o G_commands.o -c ./src/G_commands.c
	gcc -o M_commands.o -c ./src/M_commands.c
	gcc -o analyzer.o -c ./src/gcode.c
	
	ar rc libgcommands_call.a G_commands.o
	ar rc libmcommands_call.a M_commands.o
	ar rc libcommands_call.a G_commands.o M_commands.o
	ar rc libanalyzer.a analyzer.o
	ar rc libanalyzer_full.a analyzer.o G_commands.o M_commands.o
		
clean:
	rm -rf *~ *.o
