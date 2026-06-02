CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -I.
LDLIBS = -lcsfml-graphics -lcsfml-window -lcsfml-system -lm

all: testLine

testLine: turtlec.c examples/triangle_fractal_1.c turtlec.h
	$(CC) $(CFLAGS) turtlec.c examples/triangle_fractal_1.c -o triangle_fractal_1 $(LDLIBS)

clean:
	rm -f testLine
