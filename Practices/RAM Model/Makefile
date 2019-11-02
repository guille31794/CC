CXX = g++
CXXFLAGS = -std=c++98 -Wall -O3

EXES = program power power-power
OBJS = ${EXES:=.o} binary-function.o

%: %.o
	${CXX} ${LDFLAGS} -o $@ $^

all: ${EXES}

power power-power: binary-function.o

${OBJS}: ram.h

clean:
	${RM} ${EXES} ${OBJS} core *~
