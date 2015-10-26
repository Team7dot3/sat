all:	clean sat solve

debug: 	clean sat_d solve

sat_d:	src/main.c
	gcc -fmessage-length=0 -pedantic-errors -std=gnu99 -Werror -Wall -Wextra -Wwrite-strings -Winit-self -Wcast-align -Wcast-qual -Wpointer-arith -Wstrict-aliasing -Wformat=2 -Wmissing-include-dirs -Wno-unused-parameter -Wshadow -Wuninitialized -Wold-style-definition -m32 -DDEBUG src/main.c src/input.c src/solve.c -o bin/sat_solver.o

sat:	src/main.c
	gcc -fmessage-length=0 -pedantic-errors -std=gnu99 -Werror -Wall -Wextra -Wwrite-strings -Winit-self -Wcast-align -Wcast-qual -Wpointer-arith -Wstrict-aliasing -Wformat=2 -Wmissing-include-dirs -Wno-unused-parameter -Wshadow -Wuninitialized -Wold-style-definition -m32 src/main.c src/input.c src/solve.c -o bin/sat_solver.o

solve:	bin/sat_solver.o txt/input.txt
	bin/sat_solver.o txt/input.txt

sat_t:	test/unit_test.c	
	gcc -fmessage-length=0 -pedantic-errors -std=gnu99 -Werror -Wall -Wextra -Wwrite-strings -Winit-self -Wcast-align -Wcast-qual -Wpointer-arith -Wstrict-aliasing -Wformat=2 -Wmissing-include-dirs -Wno-unused-parameter -Wshadow -Wuninitialized -Wold-style-definition -m32 -DDEBUG src/input.c src/solve.c test/unit_test.c test/unit_test_check_args.c test/unit_test_input_parser.c test/unit_test_solve.c -o bin/unit_test.o

test:	clean sat_t
	bin/unit_test.o

clean:
	rm -f bin/*.o;
	rm -f *~;
	rm -f .*~;
	rm -f bin/*~;
	rm -f src/*~;
	rm -f txt/*~

