CC=						gcc
FLAGS=					-Wall -Wextra -std=c11 -Werror -std=c11 -std=c99 -pedantic -g
SRCS=					Back/parser.c Back/affine.c Back/tests.c
OBJ= 					Back/test
GCOV_FLAGS=             -fprofile-arcs -ftest-coverage -lgcov
RM = 					rm -rf
OS= 					$(shell uname)
var=					$(shell pkg-config --cflags --libs check)

ifeq ($(OS), Darwin)
	TEST_LIBS=			-lcheck
else
	TEST_LIBS=			-lcheck -lsubunit -pthread -lrt -lm -D_GNU_SOURCE
endif

all: install check gcov_report

test: clean
	$(CC) $(SRCS) $(TEST_LIBS) $(var) -o $(OBJ)
	./Back/test

install: uninstall
	mkdir build
	cd build && cmake build ../3dviewer
	make -C ./build/
	cp -rf build/3dviewer.app $(HOME)/Desktop/3dviewer.app 
	open $(HOME)/Desktop/3dviewer.app 


uninstall:
	$(RM) rm -rf build/

clean: uninstall
	$(RM) *.o *.a *.so *.gcda *.gcno *.gch rep.info *.html *.css *.tar.gz \
	$(OBJ) Back/report 3dVDir *.txt doxygen/html test.info test.dSYM  ../.clang-format

dvi:
	cd doxygen && ./doxygen Doxyfile && open html/index.html

dist: clean
	mkdir 3dVDir
	cp Back/*.c 3dVDir
	cp *.h 3dVDir
	cp ./3dviewer/CMakeLists.txt 3dVDir
	cp ./3dviewer/*.cpp 3dVDir
	cp ./3dviewer/*.ui 3dVDir
	cp Makefile 3dVDir
	tar -czf 3dVArh.tar.gz 3dVDir/
	$(RM) 3dVDir

gcov_report: clean
	$(CC) $(var) -o $(OBJ) $(SRCS) $(GCOV_FLAGS)  $(TEST_LIBS)
	./Back/test
	lcov -t "gcov_report" -o $(OBJ).info -c -d .
	genhtml -o Back/report $(OBJ).info
	open Back/report/index.html
	$(RM) $(OBJ)
	$(RM) Back/test.info
	$(RM) *.gcno
	$(RM) *.gcda

check:
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config */*.c *.h
	cp ../materials/linters/.clang-format ../.clang-format
	clang-format -i Back/*.c
	clang-format -n Back/*.c
	clang-format -i *.h
	clang-format -n *.h
	clang-format -i 3dviewer/*.cpp
	clang-format -n 3dviewer/*.cpp
	clang-format -i 3dviewer/*.h
	clang-format -n 3dviewer/*.h



