PROJ=lisp
EXE=bin/${PROJ}.exe
SRC=${PROJ}.cpp
TEST=tests/test.cpp
HEADERS=AST.hpp IDEerror.hpp parser.hpp testcases.hpp token.hpp tokens.hpp
${EXE}:${SRC} ${HEADERS}
	g++ -g ${SRC} -o $@
	
run:${EXE}
	./${EXE} tests/input.l tests/output.s

interpreter:${EXE}
	./${EXE}

test:${TEST}
	g++ ${TEST} -lgtest_main -lgtest -o tests/test
	./tests/test

debug:${EXE}
	gdb --args ${EXE} input.l sort.s

clean:
	rm tests/*.txt ${EXE}