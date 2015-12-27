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
