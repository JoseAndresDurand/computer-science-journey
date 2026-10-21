CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I.
LDLIBS = -lcsfml-graphics -lcsfml-window -lcsfml-system -lm

all: testLine

testLine: turtlec.c examples/levy_curve_1.c turtlec.h
	$(CC) $(CFLAGS) turtlec.c examples/levy_curve_1.c -o levy_curve_1 $(LDLIBS)

clean:
	rm -f testLine
