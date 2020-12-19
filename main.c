#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>

struct termios orig_attributes;

void disableRaw(){
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_attributes);
}

int enableRaw(){
	tcgetattr(STDIN_FILENO, &orig_attributes);
	struct termios raw = orig_attributes;

	atexit(disableRaw);
	raw.c_iflag &= ~(IXON);
	raw.c_oflag &= ~(OPOST);
	raw.c_lflag &= ~(ECHO | ICANON | ISIG);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void print(char c){
	switch(c){
	case 10:
		printf("\r\n");
		break;
	case 8:
	case 127:
		printf("\b \b");
		break;
	default:
		printf("%c",c);

	}
}

int main()
{
	int state = 1;
	enableRaw();
	char c = 'a';
	unsigned int a = 0;
	perror("states");
	while(1)
	{
		read(STDIN_FILENO, &c, 1);
		perror("read");
		if (state)
			print(c);
		else if (c == 'q')
			break;

		if(iscntrl(c) && c == 27){
			state = 0;
		} else if(c == 'i' && state == 0){
			state = 1;
		}
		fflush(stdout);
	}

	return 0;
}
