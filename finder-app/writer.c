#include <stdio.h>
#include <stdlib.h>
#include <syslog.h>

int main(int argc, char **argv) 
{
	if (argc != 3) 
	{
		//error if not enough arguments
		syslog(LOG_ERR, "Error: incorrect number of arguments!");
		exit(1);
	}

	FILE *fp;
	char *writeFile = argv[1];
	char *writeString = argv[2];

	fp = fopen(writeFile, "w");
	if (fp == NULL) 
	{
		//error if file could not be created
		syslog(LOG_ERR, "Error: could not create file!");
		exit(1);
	}
	
	fprintf(fp, "%s", writeString);

	syslog(LOG_DEBUG, "Writing %s to %s", writeString, writeFile);

	fclose(fp);

	return 0;
}

