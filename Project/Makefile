CC = arm-linux-gcc # 指定编译器
ELF = ./BIN/main   # 指定生成的可执行文件及路径
SRC = $(wildcard ./SRC/*.c) # 匹配查找所有的.c文件
CONFIG = -D_LINUX -lm -I./INC -L./LIB   -mfloat-abi=softfp -mfpu=neon -ftree-vectorize # 编译配置

# 生成可执行文件
$(ELF): $(SRC)
	$(CC) $(SRC) -o $(ELF) $(CONFIG) -lpthread

# 清理生成的文件
clean:
	rm -f $(ELF)
