// Functions comes here.

#include "colors.h"

#define MAX 64
#define MAXLINE 2048
#define FILESIZE 1024

FILE *file; // original
FILE *output; // temp output

const char database[] = "students.txt";

char add_new_student_menu(void);
char adding_ch(void);
char remove_student(void);
char list_all_students(void);
char find_student(unsigned char *keyword);
void cleantime(void);

typedef struct students
{
	char firstname[MAX];
	char lastname[MAX];
	char email[MAX];
	char tel[15];

} Students;

Students student[128];

void cleantime() {
    while(getchar() != '\n');
}

char add_new_student_menu(void)
{
	char ch;

	system("clear");
	printf(" __________________________________________\n");
	printf("/     		                           \\\n");
	printf("|       %sAdding new student section%s         |\n", cyan, normal);
	printf("\\                                          /\n");
	printf("  -----------------------------------------\n");
	printf("\n");
	printf("Don't forget. There can be maximum 20 students in class.\n\n");

	do
	{
		printf("Do you want to add new student? (Y/n)\n");
		scanf(" %c", &ch);

		if(ch == 'Y')
		{
			adding_ch();
			exit(0);
		}

		else if(ch == 'n')
		{
			printf("Have a nice day!\n");
			exit(0);
		}

	} while(ch != 'Y');
	return ch;
}



char adding_ch(void)
{
	int i = 1, j;

	char ch;

	file = fopen(database, "w");
	if(file == NULL)
	{
		fprintf(stderr, "I can't open file for write.\n");
		return -1;
	}

	loop:do
	{
		if(i > 20)
		{
			printf("Class is full.\n");
			exit(1);
		}
		printf("Adding %d. student\n", i);
		while(getchar() != '\n');

		printf("Firstname: ");
		fgets(student[i].firstname, 128, stdin);

		printf("Lastname: ");
		fgets(student[i].lastname, 128, stdin);

		printf("Email: ");
		fgets(student[i].email, 128, stdin);

		printf("Phone: ");
		fgets(student[i].tel, 15, stdin);

		printf("\nWould you like to add next student? (Y/n)\n");
		scanf("%c", &ch);

		if(ch == 'n' || ch == 'N')
		{
			printf("Students created and saved into database.\n");
			printf("[%s+%s] Saving...\n\n", green, normal);
			sleep(1);

			for(j = 1; j <= i; j++)
			{
				printf("ID: %d\n", j);
				printf("Firstname: %s", student[j].firstname);
				printf("Lastname: %s", student[j].lastname);
				printf("Email: %s", student[j].email);
				printf("Phone: %s\n", student[j].tel);

				strtok(student[j].firstname, "\n");
				strtok(student[j].lastname, "\n");
				strtok(student[j].email, "\n");
				strtok(student[j].tel, "\n");

				fprintf(file, "%d: ", j);
				fprintf(file, "%s ", student[j].firstname); // and save it to students.txt file
				fprintf(file, "%s ", student[j].lastname);
				fprintf(file, "%s ", student[j].email);
				fprintf(file, "%s\n", student[j].tel);		
			}
			printf("Students saved!\n");
			exit(0);
			fclose(file);
		}

		i++;

	} while(ch == 'Y');
	goto loop;

	return 0;
}

char list_all_students()
{
	char buffer[FILESIZE];

	system("clear");
	printf(" __________________________________________\n");
	printf("/     		                           \\\n");
	printf("|       %sAll students in this class%s         |\n", cyan, normal);
	printf("\\                                          /\n");
	printf("  -----------------------------------------\n");
	printf("\n");

	file = fopen(database, "r");
	if(file == NULL)
	{
		fprintf(stderr, "Failed, while opening file.\n");
		return -1;
	}

	while(fgets(buffer, sizeof(buffer), file) != NULL)
	{
		strtok(buffer, "\n"); // because of damned fgets and its newline
		printf("%s\n", buffer);
	}
	printf("\n");
	fclose(file);
	return 0;
}


char find_student(unsigned char *keyword)
{
	char line[MAXLINE];

	system("clear");
	printf(" __________________________________________\n");
	printf("/     		                           \\\n");
	printf("|\t%sFind student using keyword%s          |\n", cyan, normal);
	printf("\\__________________________________________/\n");
	printf("\n");

	char *ptr;

	file = fopen(database, "r");
	if(file == NULL)
	{
		fprintf(stderr, "Failed, while opening file.\n");
		return -1;
	}

	while(fgets(line, sizeof(line), file) != NULL)
	{
		if((ptr = strstr(line, keyword)) != NULL)
		{
			printf("%s", line);
			return 0;
		}	
	}

	fclose(file);
	return 0;
}


char remove_student()
{
	const char temp[] = "out.txt";

	char line[MAXLINE];
	char o[MAXLINE];
	char del;

	file = fopen(database, "r");
	if(file == NULL)
	{
		fprintf(stderr, "Failed, while opening file for reading.\n");
		return -1;
	}

	output = fopen(temp, "w");
	if(output == NULL)
	{
		fprintf(stderr, "Failed, while opening file for write.\n");
		return -1;
	}

	printf("\n");
	system("cat students.txt"); // phuck it

	printf("\nEnter ID of the student, you'd like to delete from class: ");
	scanf("%c", &del);

	while((fgets(line, sizeof(line), file)) != NULL)
	{
		if(*line == del) // if the 'line' will include our number
			continue; // then ignore it and continue

		if(sscanf(line, "%s", o) == 1)
			fprintf(output, "%s", line);
	}

	fclose(file);
	fclose(output);

	remove(database);
	rename("out.txt", database);

	return 0;
}
