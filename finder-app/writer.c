#include <stdio.h>
#include <sys/syslog.h>
#include <string.h>

int main(int argc, char *argv[]) {
	// open syslog
	openlog("writer", LOG_PID|LOG_CONS, LOG_USER);

	// check that there are the correct number of parameters
	if (argc != 3) {
		syslog(LOG_ERR, "Error: Invalid number of parameters.");
		closelog();
		return 1;
	}

	// check that the write string is specified
	if (strlen(argv[2]) == 0) {
		syslog(LOG_ERR, "Error: No write string specified.");
		closelog();
		return 1;
	}

	// open the file
	FILE *fp = fopen(argv[1], "w");
	if (fp == NULL) {
		syslog(LOG_ERR, "Error: Unable to open file.");
		closelog();
		return 1;
	}

	// log the write statement
	syslog(LOG_DEBUG, "Writing %s to %s.", argv[2], argv[1]);

	// write the string
	fputs(argv[2], fp);

	// close the file
	fclose(fp);

	// close syslog
	closelog();

	return 0;
}
