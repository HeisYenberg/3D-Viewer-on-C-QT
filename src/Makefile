OS := $(shell uname)
CC = -Wall -Werror -Wextra
FLAGS = -lcheck -lpthread -fprofile-arcs

ifeq ($(OS),Darwin)
	FLAGS += -ftest-coverage
	OPEN_CMD = open
	OPEN_APP = $(OPEN_CMD) 
	APP = 3DViwerV1.0.app
else
	FLAGS += -lm -lrt -L/usr/bin/ld -lsubunit -ftest-coverage
	OPEN_CMD = xdg-open
	OPEN_APP = ./
	APP = 3DViwerV1.0
endif

all: clean install open

install: clean
	cd frontend && qmake6 && make && make clean

uninstall:
	cd frontend && rm -rf Makefile ../$(APP) frontend.pro.user .qmake.stash .qtc_clangd .tmp

open:
	$(OPEN_APP)$(APP)

dvi:
	$(OPEN_CMD) README.md

dist: clean install
	cd .. && tar -czvf src/3DViwerV1.0.tar.gz src

test: clean
	gcc $(CC) tests/tests.c backend/*.c $(FLAGS) -lgcov -coverage -o test
	./test

gcov_report: clean
	gcc $(CC) tests/tests.c backend/*.c $(FLAGS) -o test
	./test
	lcov -t "./test"  -o report.info --no-external -c -d .
	genhtml -o report report.info
	$(OPEN_CMD) ./report/index.html

	rm -rf *.gcno *gcda *.gco

rebuild: clean install open

clean: uninstall
	rm -rf *.o *.a test
	rm -rf *.gcno *gcda *.gcov gcov
	rm -rf report report.info
	rm -rf 3DViwerV1.0.tar.gz