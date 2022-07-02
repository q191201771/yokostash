#include <sys/time.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

uint64_t tick();

int main(int argc, char* argv[])
{
  int foreverFlag;
  uint64_t copySize, loopCount, i, start, end;
  uint64_t total = (uint64_t)4 * 1024 * 1024 * 1024; // 4 * G

  copySize = atoi(argv[1]);
  foreverFlag = atoi(argv[2]);

  loopCount = total / copySize;

  char *src = (char *)malloc(copySize);
  char *dst = (char *)malloc(copySize);


  for (; ; ) {

	start = tick();
	for (i = 0; i < loopCount; i++) {
    src[i%copySize] = (char)i;
//	  src[0] = (char)i;
	  memcpy(dst, src, copySize);
	}

	printf("copySize=%llu, loopCount=%llu, total=%llu MBytes\n", copySize, loopCount, total/1024/1024);
	end = tick();
	printf("cost:(total=%llu ms,single=%0.6f ms)\n", end-start, (float)(end-start)/loopCount);

	if (end == start) {
	  printf("rate:%0.2f MBytes/s\n", 0.0);
	} else {
	  printf("rate:%0.2f MBytes/s\n", (float)(copySize) * loopCount / 1024 / 1024 * 1000 / (end-start));
	}

	if (foreverFlag == 0) {
	  break;
	}
  }

  // 打印一点内容，避免被编译优化
  for (i = 0; i < 128; i++) {
    printf("%d", dst[i]);
  }
  printf("\n");
}

// tick
//
// @return 单位毫秒
//
// TODO(chef): 移入libchef中（或者新弄一个c的库） 202206
//
uint64_t tick() {
  struct timeval tv;
  gettimeofday(&tv, NULL);

//#ifdef __MACH__
  return (uint64_t)tv.tv_sec*1000 + (uint64_t)(tv.tv_usec)/1000;
//#endif

//  return (uint64_t)tv.tv_sec*1000 + (uint64_t)(tv.tv_usec)/1000000;
}