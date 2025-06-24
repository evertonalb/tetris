EXEC=tetris.exe
INCLUDE="SDL3-3.2.10\x86_64-w64-mingw32\include"
LIB="SDL3-3.2.10\x86_64-w64-mingw32\lib"
COMPILE=gcc -I${INCLUDE} -L${LIB}

${EXEC}: main.o func.o
	${COMPILE} main.o func.o -lSDL3 -o ${EXEC}

main.o: main.c
	${COMPILE} main.c -c -o main.o

func.o: func.c
	${COMPILE} func.c -c -o func.o

clean:
	cmd /C del func.o main.o ${EXEC}