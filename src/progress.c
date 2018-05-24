#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "interop.h"
#include "progress.h"

void progress_init(void)
{
	printf("\n\n");
}

static void draw(const char *name, long offset, long count)
{
	if(count == 0){
		printf("%s skip\n", name);
		return;
	}
	const int barnum = 100 / 5;
	int persent = (offset * 100) / count;
	char bar[barnum + 3 + 1];
	char *t = bar;
	int i;
	assert(persent <= 100);
	printf("%s 0x%06x/0x%06x ", name, (int)offset, (int)count);
	*t++ = '|';
	for(i = 0; i < persent / 5; i++){
		if(i == barnum / 2){
			*t++ = '|';
		}
		*t++ = '#';
	}
	for(; i < barnum; i++){
		if(i == barnum / 2){
			*t++ = '|';
		}
		*t++ = ' ';
	}
	*t++ = '|';
	*t = '\0';
	puts(bar);
}
void progress_draw(long program_offset, long program_count, long charcter_offset, long charcter_count)
{
	if(0){
		printf("\x1b[2A\x1b[35D");
	}else{
	#ifndef __linux__
		HANDLE c;
		CONSOLE_SCREEN_BUFFER_INFO info;
		c = GetStdHandle(STD_OUTPUT_HANDLE);
		if(GetConsoleScreenBufferInfo(c, &info) == 0){
			//command.com, cygwin shell, mingw shell
			printf("\x1b[2A\x1b[35D");
		}else{
			//cmd.exe
			info.dwCursorPosition.X = 0;
			info.dwCursorPosition.Y -= 2;
			SetConsoleCursorPosition(c, info.dwCursorPosition);
		}
	#else
		printf("\x1b[2A\x1b[35D");
	#endif//__linux__
	}
	draw("program memory ", program_offset, program_count);
	draw("charcter memory", charcter_offset, charcter_count);
	fflush(stdout);
}
