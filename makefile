draw:main.c draw.c
	arm-linux-gcc main.c draw.c -o draw

touch:main.c touch.c
	arm-linux-gcc main.c touch.c -o touch

dir:main.c touch.c
	arm-linux-gcc main.c touch.c -o dir

color:main.c touch.c draw.c
	arm-linux-gcc main.c touch.c draw.c -o color

image:main.c bmp.c draw.c
	arm-linux-gcc main.c bmp.c draw.c -o image

char:main.c  draw.c
	arm-linux-gcc main.c draw.c -o char

album:main.c draw.c touch.c bmp.c
	arm-linux-gcc main.c draw.c touch.c bmp.c -o album