draw:main.c draw.c
	arm-linux-gcc main.c draw.c -o draw

touch:main.c touch.c
	arm-linux-gcc main.c touch.c -o touch

dir:main.c touch.c
	arm-linux-gcc main.c touch.c -o dir