PROJ=lisp
EXE=${PROJ}.exe
SRC=${PROJ}.cpp
HEADERS=AST.hpp IDEerror.hpp parser.hpp testcases.hpp token.hpp tokens.hpp
${EXE}:${SRC} ${HEADERS}
	g++ -g ${SRC} -o $@
	
run:${EXE}
	./${EXE} tests/input.l tests/output.s
	gcc tests/output.s -o tests/sort
	./tests/sort

test:${EXE}
	./${EXE} test

debug:${EXE}
	gdb --args ${EXE} input.l sort.s

clean:
	rm tests/*.txt ${EXE}