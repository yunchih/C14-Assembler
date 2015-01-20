CFLAGS=	-std=c99	-g	-DDEBUG
CC=gcc

all:	assembler 

assembler:	assembler.o	code_generator.o	lexicalAnalysis.o	bitsOperation.o	meta.o	stringManipulation.o	tokenClassification.o
	gcc $(CFLAGS)	assembler.o	code_generator.o	lexicalAnalysis.o	bitsOperation.o	meta.o	stringManipulation.o	tokenClassification.o	-o	assembler	

assembler.o: assembler.c	debug.h	unitTests.c
	gcc	$(CFLAGS)	-c	assembler.c	-o	assembler.o
code_generator.o: code_generator.c	debug.h	unitTests.c
	gcc 	$(CFLAGS)	-c	code_generator.c	-o	code_generator.o
lexicalAnalysis.o: lexicalAnalysis.c	debug.h	unitTests.c
	gcc 	$(CFLAGS)	-c	lexicalAnalysis.c	-o	lexicalAnalysis.o
bitsOperation.o: bitsOperation.c	debug.h	unitTests.c
	gcc 	$(CFLAGS)	-c	bitsOperation.c	-o	bitsOperation.o
stringManipulation.o: meta.h	stringManipulation.c	debug.h	unitTests.c
	gcc 	$(CFLAGS)	-c	stringManipulation.c	-o	stringManipulation.o
tokenClassification.o: tokenClassification.c	debug.h	unitTests.c
	gcc 	$(CFLAGS)	-c	tokenClassification.c	-o	tokenClassification.o
meta.o: meta.c	debug.h	unitTests.c
	gcc 	$(CFLAGS)	-c	meta.c	-o	meta.o

#---Unit Test----------------------------------------------

test:	unitTest

unitTest: unitTests.o	debug.h 	code_generator.o	lexicalAnalysis.o	bitsOperation.o	meta.o	stringManipulation.o	tokenClassification.o	
	gcc $(CFLAGS)	unitTests.o	code_generator.o	lexicalAnalysis.o	bitsOperation.o	meta.o	stringManipulation.o	tokenClassification.o	-o	unitTest	
unitTests.o: unitTests.c	debug.h
	gcc $(CFLAGS) unitTests.c	-c	-o	unitTests.o

clean:
	rm -f *.o

