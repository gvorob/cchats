#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#include "util.h"

#define PROMPT_SIZE 512

static char prompt[PROMPT_SIZE];

int _getline(char *in, int bytestoread) {
	int count;
	count = read(STDIN_FD, in, bytestoread);
	
	if(count == -1){
		printf("%d\n", STDIN_FD);
		err(-1, "_getline failed");
	}
	else if(count == 0) 
		errx(-1, "stdin read 0");
	else if(in[count - 1] != '\n') {
		do {
			count = read(STDIN_FD, in, bytestoread);
			if(count == -1)
				errx(-1, "Error after buffer overflow");	
		} while (in[count - 1] != '\n');
		return -1;
	}

	in[count - 1] = '\0';
	return 0;
}

void print_prompt() {
	if(getcwd(prompt, sizeof(prompt)) == NULL) {
		errx(-1, "Path too long\n");
	}

	printf("%s>", prompt);
	fflush(stdout);
}

void print_help() {
	printf("Type 'help' for help\n");
	printf("Type 'cd' to change directory\n");
	printf("Any other commands will be run from /bin/\n");

	printf("This shell handles >, 2>, &>, >>, 2>>, &>>,");
	printf(" and <, as well as pipes and semicolons\n");
}
