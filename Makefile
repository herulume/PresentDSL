CFLAGS = -Wall -Wextra -O2 -march=native -D_GNU_SOURCE
CC     = gcc



ifeq ($(OS),Windows_NT)
	@echo "Doesn't run on Windoze."
	exit
endif

parser:
	@flex ./src/pdsl.l
	@yacc -d -v ./src/pdsl.y
	$(CC) $(CFLAGS) y.tab.c -o slides
	@rm lex.yy.c y.output y.tab.c y.tab.h
	@mkdir bin
	@mv slides bin

clean:
	@echo "Cleaning..."
	@echo ""
	@cat .art/maid.ascii
	@rm -rf bin
	@echo ""
	@echo "...all done!"
