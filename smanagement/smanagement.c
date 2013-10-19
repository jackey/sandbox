#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <locale.h>
#include <wchar.h>
#include "smanagement.h"

int main(int argc, char **argv) {
	student s1 = {
		"2013100710001",
		25,
		"陈子文",
		"432425198802246211"
	};
	add_student(s1);

	student s2 = {
		"2013100710002",
		23,
		"李秀",
		"432425199008156211"
	};
	add_student(s2);

	//del_student(s1);
	init();

	return 0;
}

int add_student(student s) {
	printf("adding new student: %s.\n", s.name);
	int ret;
	struct stat dir_stat;
	ret = stat(DATA_DIR, &dir_stat);
	if (ret != 0) {
		if (errno == ENOENT) {
			fprintf(stderr, "directory is not exist.\n");
			ret = mkdir(DATA_DIR, 0777);
			if (ret != 0) {
				fprintf(stderr, "unknown error happened.\r\n");
			}
			else {
				printf("trying to create directory.\n");
			}
		}
	}

	// Get the data that need to be stored.
	char s_buf[STUDENT_BUF_LEN];
	sprintf(s_buf, "%s:%d:%s:%s", s.xj, s.age, s.name, s.shfz);

	// Create the data file into DATA_DIR
	char new_data_file_name[sizeof(s.xj) + DATA_DIR_LEN];
	sprintf(new_data_file_name, "./data/%s", s.xj);
	FILE *new_data_file;
	new_data_file = fopen(new_data_file_name, "w+");
	if (!new_data_file) {
		printf("create new data file failed. please make sure there's write permission on data dir\n");
		return -1;
	}
	fputs(s_buf, new_data_file);
	fclose(new_data_file);

	printf("%s has been added.\n", s.name);
	return 0;
}

int del_student(student s) {
	printf("deleting student %s.\n", s.name);

	char s_path[sizeof(s.xj) + DATA_DIR_LEN];
	data_path(s, s_path);
	int ret = unlink(s_path);
	if (ret != 0) {
		printf("error happened when remove student: %s\n", s.name);
		return -1;
	}
	printf("%s student has been deleted.\n", s.name);
	return 0;
}

void data_path(student s, char path[]) {
	sprintf(path, "./data/%s", s.xj);
}

int init() {
	int len;
	DIR *data_dir;
	data_dir = opendir(DATA_DIR);
	if (!data_dir) {
		fprintf(stderr, "error happened when open %s", DATA_DIR);
		return -1;
	}
	struct dirent *dir_entity = readdir(data_dir);
	if (dir_entity == NULL) {
		fprintf(stderr, "error happened when read dir %s\n", DATA_DIR);
		return -1;
	}
	char data_files[MAX_STUDENT];
	while (dir_entity != NULL) {
		char *name = dir_entity->d_name;
		if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0) {
			// If filename is "." or "..", ignore it.
		}
		else {
			len = (member_size(student, xj) + DATA_DIR_LEN ) * sizeof(char);
			char content[STUDENT_BUF_LEN];
			char *data_file_name = (char *) malloc(len);
			memcpy(data_file_name, "./data/", 7);
			memcpy(data_file_name + 7, name, strlen(name) + 1);
			FILE *data_file = fopen(data_file_name, "r");
			if (!data_file) {
				fprintf(stderr, "error happened when read file: %s", name);
				return -1;
			}
			fgets(content, STUDENT_BUF_LEN, data_file);
			char *token = strtok(content, ":");
			printf("%s\n", token);
			char *token2;
			while (NULL != token2 = strtok(NULL, ":")) {
				printf("%s\n", token2);
			}
			int i;
			for (i = 0; content[i] != '\0'; i++) {
				int utf8_char_len = UTF8_CHAR_LEN(content[i]);
				char *p;
				if (utf8_char_len > 1) {
					char word[4]; // Max size of utf-8
					memcpy(word, (content + i), utf8_char_len); 
					i += utf8_char_len - 1;
				}
				else {
					char c = content[i];
					p = &c;
				}
				printf("%c", *p);
			}
			fclose(data_file);
		}

		dir_entity = readdir(data_dir);
	}
}