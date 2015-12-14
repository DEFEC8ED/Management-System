#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "core.c"
#include "colors.h"

void menu(char *name);

int main(int argc, char *argv[])
{
	unsigned char *k;

	if(argc < 2)
	{
		menu(argv[0]);
	}

	if(!strncmp(argv[1], "--Add", 5))
	{
		add_new_student_menu();
	}

	else if(!strncmp(argv[1], "--List", 6))
	{
		list_all_students();
	}

	else if(!strncmp(argv[1], "--Find", 6))
	{
		k = argv[2];
		find_student(k);
	}

	else if(!strncmp(argv[1], "--Delete", 8))
	{
		remove_student();
	}

	else
	{
		fprintf(stderr, "Probably wrong command. Please, try it again.\n");
		exit(EXIT_FAILURE);
	}

	return 0;
}

void menu(char *name)
{
	system("clear");
	printf(" __________________________________________\n");
	printf("/     		                           \\\n");
	printf("|      Student management system v1.0      |\n");
	printf("\\                                          /\n");
	printf("  -----------------------------------------\n");
	printf("\n");
	printf("%sUsage:%s %s <Commands>\n\n", cyan, normal, name);
	printf("%sCommands:%s\n\n", cyan, normal);

	printf("\t%s--Add%s\t\t\tAdd new student to system.\n\n", cyan, normal);
	printf("\t%s--List%s\t\t\tList all students from system.\n\n", cyan, normal);
	printf("\t%s--Find%s <Keyword>\tShow student by virtue of its ID or name.\n\n", cyan, normal);
	printf("\t%s--Delete%s\t\tDelete student by virtue of its ID.\n\n", cyan, normal);

    // Maybe later...
	/* printf("\t%s--Best%s\t\t\tPrint student with the best average of all subjects.\n\n", red, normal);
	printf("\t%s--Av%s\t\t\tPrint average of all subjects from this class.\n\n", red, normal); */
  	
	exit(EXIT_SUCCESS);
}
