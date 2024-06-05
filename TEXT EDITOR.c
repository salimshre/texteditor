// BUILDING A TEXT EDITOR IN C.
// https://viewsourcecode.org/snaptoken/kilo/02.enteringRawMode.html#disable-raw-mode-at-exit
// https://github.com/antirez/kilo/blob/master/kilo.c
//
//
#include<stdio.h>
#include<unistd.h> // For the read function
#include<termios.h>

struct ttermios orig_termios;

void disableRawMode(){
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode() {
	tcgetattr(STDIN_FILENO, &orig_termios);
	atexit(disableRawMode);


        struct termios raw= orig_termios;

    // Get the current terminal settings and store them in 'raw'
    tcgetattr(STDIN_FILENO, &raw);

    
    raw.c_lflag &= ~(ECHO);

    // Set the modified terminal settings
    // TCSAFLUSH ensures the changes are applied after all pending output is written
    // It also discards any unread input
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}


int main()
{
	enableRawMode();
	char c;
	 // Start the loop

	while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q' ){
		 // The loop body can be empty because the condition handles everything

	}



	return 0;
}

