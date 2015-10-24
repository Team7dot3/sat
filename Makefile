all:	clean	make

make:	main.c
	gcc -fmessage-length=0 -pedantic-errors -std=gnu99 -Werror -Wall -Wextra -Wwrite-strings -Winit-self -Wcast-align -Wcast-qual -Wpointer-arith -Wstrict-aliasing -Wformat=2 -Wmissing-include-dirs -Wno-unused-parameter -Wshadow -Wuninitialized -Wold-style-definition -m32 main.c input.c solve.c -o sat_solver

clean:
	rm -f *.o sat_solver
