#ifndef SMANAGEMENT
#define SMANAGEMENT

typedef struct {
	char xj[50]; // Xueji
	short int age;
	char name[30];
	char shfz[20];
} student;

typedef int bool;

#define DATA_DIR "./data"
#define STUDENT_BUF_LEN sizeof(student) + 4
#define DATA_DIR_LEN sizeof(DATA_DIR) + 10
#define MAX_STUDENT 2000 // Max student that system can handle.
#define member_size(type, member) sizeof(((type *)0)->member)
#define UTF8_CHAR_LEN( byte ) ((( 0xE5000000 >> (( byte >> 3 ) & 0x1e )) & 3 ) + 1)

static student s_list[MAX_STUDENT];

int add_student(student);

int del_student(student);

void data_path(student, char []);

// init data array
int init();

#endif