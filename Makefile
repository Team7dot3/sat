build:
# \
!IFDEF COMSPEC
# \
!IFDEF _TEST
# \
	cl /Wall /DDEBUG /D_DEBUG /D_ARM_WINAPI_PARTITION_DESKTOP_SDK_AVAILABLE=1 /DEBUG /Zi src\input.c src\solve.c test\unit_test.c test\unit_test_check_args.c test\unit_test_input_parser.c test\unit_test_solve.c /Febin\unit_test.exe /Fdbin\unit_test.pdb
# \
!ELSE
# \
!IFDEF _DEBUG
# \
	cl /Wall /DDEBUG /D_DEBUG /D_ARM_WINAPI_PARTITION_DESKTOP_SDK_AVAILABLE=1 /DEBUG /Zi src\main.c src\input.c src\solve.c /Febin\sat_solver.exe /Fdbin\sat_solver.pdb
# \
!ELSE
# \
	cl /Wall /D_ARM_WINAPI_PARTITION_DESKTOP_SDK_AVAILABLE=1 src\main.c src\input.c src\solve.c /Febin\sat_solver.exe
# \
!ENDIF
# \
!ENDIF
# \
!ELSE
# Linux Stuff
ifdef _TEST
	gcc -fmessage-length=0 -pedantic-errors -std=gnu99 -Werror -Wall -Wextra -Wwrite-strings -Winit-self -Wcast-align -Wcast-qual -Wpointer-arith -Wstrict-aliasing -Wformat=2 -Wmissing-include-dirs -Wno-unused-parameter -Wshadow -Wuninitialized -Wold-style-definition -m32 src/input.c src/solve.c test/unit_test.c test/unit_test_check_args.c test/unit_test_input_parser.c test/unit_test_solve.c -o bin/unit_test.o
else
ifdef _DEBUG
	gcc -fmessage-length=0 -pedantic-errors -std=gnu99 -Werror -Wall -Wextra -Wwrite-strings -Winit-self -Wcast-align -Wcast-qual -Wpointer-arith -Wstrict-aliasing -Wformat=2 -Wmissing-include-dirs -Wno-unused-parameter -Wshadow -Wuninitialized -Wold-style-definition -m32 -DDEBUG -g src/main.c src/input.c src/solve.c -o bin/sat_solver.o
else
	gcc -fmessage-length=0 -pedantic-errors -std=gnu99 -Werror -Wall -Wextra -Wwrite-strings -Winit-self -Wcast-align -Wcast-qual -Wpointer-arith -Wstrict-aliasing -Wformat=2 -Wmissing-include-dirs -Wno-unused-parameter -Wshadow -Wuninitialized -Wold-style-definition -m32 src/main.c src/input.c src/solve.c -o bin/sat_solver.o
endif
endif
# \
!ENDIF

rebuild: clean build

test: clean
	make build _TEST=1

debug: clean
	make build _DEBUG=1

#deftest: export TEST = 1

#defdebug: export DEBUG = 1

all: clean build

solve: clean build
# \
!IFDEF COMSPEC
# \
	bin\sat_solver.exe txt\input.txt
# \
!ELSE
#Linux Stuff
	bin/sat_solver.o txt/input.txt
#\
!ENDIF

testrun: test
# \
!IFDEF COMSPEC
# \
	bin\unit_test.exe
# \
!ELSE
	bin/unit_test.o
# \
!ENDIF

diff_test: clean build
# \
!IFDEF COMSPEC
# \
	bin\unit_test.exe
# \
!ELSE
#Linux Stuff
	python test/diff_test.py
# \
!ENDIF

clean:
# \
!IFDEF COMSPEC
# \
	del /f /s *.exe
# \
	del /f /s *.pdb
# \
	del /f /s *.obj
# \
	del /f /s *.idb
# \
	del /f /s *.ilk
# \
	del /f /s *.sdf
# \
!ELSE
#Linux Stuff
	rm -f bin/*.o
	rm -f *~
	rm -f .*~
	rm -f bin/*~
	rm -f src/*~
	rm -f txt/*~
# \
!ENDIF
