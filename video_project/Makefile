CC          = arm-linux-gcc #指定编译器
ELF         = ./BIN/main    #指定生成的可执行文件及路径
SRC         = $(wildcard ./SRC/*.c) #匹配查找所有的.c文件
CONFIG      = -D_LINUX -lm -I./INC -L./LIB -lapi_v4l2_arm -mfloat-abi=softfp -mfpu=neon -ftree-vectorize #删除 -ljpeg
OBJ         = $(patsubst %.c,%.o,$(SRC)) #把所有的SRC中的.c 替换成.o

$(ELF): $(OBJ)
	$(CC) $^ -o $@ $(CONFIG) -lpthread

%.o: %.c
	$(CC) $< -o $@ -c $(CONFIG)

clean:
	$(RM) $(ELF) $(OBJ)
