all:	clean sat solve

debug: 	clean sat_d solve

sat_d:	src/main.c
	gcc -fmessage-length=0 -pedantic-errors -std=gnu99 -Werror -Wall -Wextra -Wwrite-strings -Winit-self -Wcast-align -Wcast-qual -Wpointer-arith -Wstrict-aliasing -Wformat=2 -Wmissing-include-dirs -Wno-unused-parameter -Wshadow -Wuninitialized -Wold-style-definition -m32 -DDEBUG src/main.c src/input.c src/solve.c -o bin/sat_solver.o

sat:	src/main.c
	gcc -fmessage-length=0 -pedantic-errors -std=gnu99 -Werror -Wall -Wextra -Wwrite-strings -Winit-self -Wcast-align -Wcast-qual -Wpointer-arith -Wstrict-aliasing -Wformat=2 -Wmissing-include-dirs -Wno-unused-parameter -Wshadow -Wuninitialized -Wold-style-definition -m32 src/main.c src/input.c src/solve.c -o bin/sat_solver.o

solve:	bin/sat_solver.o txt/input.txt
	bin/sat_solver.o txt/input.txt

clean:
	rm -f bin/*.o bin/sat_solver.o;
	rm -f *~;
	rm -f bin/*~;
	rm -f src/*~;
	rm -f txt/*~

