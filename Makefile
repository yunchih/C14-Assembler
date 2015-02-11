all: assembler 

CPPFLAGS = -std=c++11 -g -DDEBUG
OBJS = parser.o lexer.o main.o instructionTable.o
OBJDIR = bin
OUT_OBJS=$(addprefix $(OBJDIR)/,$(OBJS))

parser.cpp parser.hpp: parser.y
	bison -d -t -v -W --debug parser.y -o parser.cpp

lexer.cpp: lexer.l parser.hpp
	flex -o lexer.cpp lexer.l 

$(OBJDIR)/instructionTable.o: instructionTable.cpp 
	g++ -c $(CPPFLAGS) -o $@ $<  
$(OBJDIR)/main.o: main.cpp $(OBJDIR)/parser.o $(OBJDIR)/instructionTable.o
	g++ -c $(CPPFLAGS) -o $@ $<  
$(OBJDIR)/lexer.o: lexer.cpp parser.hpp $(OBJDIR)/instructionTable.o
	g++ -c $(CPPFLAGS) -o $@ $<  
$(OBJDIR)/parser.o: parser.cpp $(OBJDIR)/lexer.o identifier.hpp $(OBJDIR)/instructionTable.o
	g++ -c $(CPPFLAGS) -o $@ $< 

assembler: $(OUT_OBJS) 
	g++ -o $@ $(OUT_OBJS) 

clean:
	rm -rf $(OBJDIR)/*.o parser.cpp parser.hpp lexer.cpp assembler


