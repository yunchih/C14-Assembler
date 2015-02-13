all: assembler 

CPPFLAGS += -std=c++11 -g #-DDEBUG
OBJS = parser.o lexer.o main.o instructionTable.o operation.o
OBJDIR = bin
OUT_OBJS=$(addprefix $(OBJDIR)/,$(OBJS))

LexFile=lexer_with_table.l

parser.cpp parser.hpp: parser.y
	bison -d -t -v -W --debug parser.y -o parser.cpp

lexer.cpp: $(LexFile) parser.hpp
	flex -o lexer.cpp $(LexFile) 

$(OBJDIR)/operation.o: operation.cpp 
	g++ -c $(CPPFLAGS) -o $@ $<  
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
	rm -rf $(OBJDIR)/*.o parser.cpp parser.hpp lexer.cpp assembler preprocessor $(LexFile)


$(LexFile): preprocessor RunPreprocessor 
	
preprocessor: preprocessor.cpp
	g++ preprocessor.cpp -o preprocessor -g 
RunPreprocessor: preprocessor
	./preprocessor instructionTable.cpp lexer.l $(LexFile)

test: assembler
	./assembler test.asm

bash:
	sed -i 's/\(^ *op_table.*=\) *\(.*\);/\1 new Op( \2 , Format );/g' \
	instructionTable.cpp
	# pattern='\(^ *op_table.*=\) *\(.*\);' 
	# replacement='\1 new Op( \2 , Format );'
