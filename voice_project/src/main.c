#include <stdio.h>
#include "voicectl.h"

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include "draw.h"
#include <stdlib.h>
#include <linux/input.h>
#include "touch.h"
#include "bmp.h"
#include <unistd.h>





int main(int argc,char*argv[])
{



	//语音识别
	voicectl(argv[1]);
	

	return 0;
}