C=gcc
CFLAGS=	-std=c99	-g
assembler:	assembler.o	code_generator.o	lexicalAnalysis.o	bitsOperation.o	meta.o	stringManipulation.o	tokenClassification.o
