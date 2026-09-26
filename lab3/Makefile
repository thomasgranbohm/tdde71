FLAGS = -std=c++17 -Wall -Wextra -pedantic -Weffc++ -Wold-style-cast -g
OBJS = expression.o operand.o operator.o postfix.o
TEST_OBJS = test_main.o node_test.o expression_test.o

# $(var) ger värdet av variabeln
# $@ refererar till målet och $^ till beroenden
lab3: $(OBJS) main.o
	g++ $(FLAGS) -o $@ $^

test: $(OBJS) $(TEST_OBJS)
	g++ $(FLAGS) -o $@ $^

# % är en wildcard , $< refererar till första beroendet
%.o: %.cpp %.hpp
	g++ $(FLAGS) -c $<

# detta är en regel som inte skapar en fil
.PHONY: clean
clean:
	rm *.o lab3