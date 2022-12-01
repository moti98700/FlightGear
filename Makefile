
CC = g++
OBJS = Database.cpp Commands.cpp Client.cpp Lexer.cpp  Parser.cpp ShuntingYard.cpp Server.cpp Main.cpp WhileCommand.cpp CalculateExpression.cpp 
CFLAGS = -pthread

main:	
	
	$(CC) -o main $(OBJS) $(CFLAGS)