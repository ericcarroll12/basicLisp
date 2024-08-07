PROJ=lisp
EXE=bin/${PROJ}.exe
SRC=src/${PROJ}.cpp
TEST=tests/test.cpp
HEADERS=src/AST.hpp src/IDEerror.hpp src/parser.hpp src/testcases.hpp src/token.hpp src/tokens.hpp
${EXE}:${SRC} ${HEADERS}
	g++ -g ${SRC} -o $@
	
run:${EXE}
	./${EXE} tests/input.l tests/output.s

interpreter:${EXE}
	./${EXE}

test:${TEST}
	g++ ${TEST} -lgtest_main -lgtest -o bin/test
	./bin/test

debug:${EXE}
	gdb --args ${EXE} input.l sort.s

clean:
	rm tests/*.txt ${EXE}