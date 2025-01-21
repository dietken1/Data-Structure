#include <stdio.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#define MAX 50

int numCheck();
void getFirstStudent();

typedef struct Student{
	char name[MAX];
	int id;
	int scores[3];
	float average;
}Student;

void main(){
	Student students[MAX];
	int i = 0;
	while (i < MAX) {
		char n[MAX];
		printf("학생 이름 (exit 입력시 종료됩니다.): ");
		scanf("%s", n);
		if (strcmp(n, "exit") == 0){
			break;
		}
		strcpy(students[i].name, n);

		printf("ID: ");
		scanf("%d", &students[i].id);

		printf("수학 성적: ");
		students[i].scores[0] = numCheck();
		printf("과학 성적: ");
		students[i].scores[1] = numCheck();
		printf("영어 성적: ");
		students[i].scores[2] = numCheck();

		students[i].average = (students[i].scores[0] + students[i].scores[1] + students[i].scores[2]) / 3.0;
		i++;
	}
	printf("\n----------------------- 학생 정보 -----------------------\n");
	printf("| %-10s | %-5s | %-5s | %-5s | %-5s | %-7s |\n", "이름", "ID", "수학", "과학", "영어", "평균");
	printf("---------------------------------------------------------\n");
	for (int j = 0; j < i; j++) {
		printf("| %-10s | %-5d | %-5d | %-5d | %-5d | %-7.1f |\n",
			students[j].name, students[j].id,
			students[j].scores[0], students[j].scores[1],
			students[j].scores[2], students[j].average);
	}
	getFirstStudent(students, i);
}

/*성적을 입력받는 함수*/
int numCheck(){
	while (1) {
		int num = 0;
		scanf("%d", &num);
		if (num < 0 || num > 100) {
			printf("범위에 맞게 다시 입력해주세요.(0 ~ 100): ");
			continue;
		}
		return(num);
	}
}

/*최고성적의 학생을 구하는 함수*/
void getFirstStudent(Student students[], int cnt) {
	float maxAvg = 0;
	int num = 0;
	for (int i = 0; i < cnt; i++) {
		if (students[i].average > maxAvg) {
			maxAvg = students[i].average;
			num = i;
		}
	}
	printf("--------------------- 최고 점수 학생 ---------------------\n");
	printf("| %-10s | %-5d | %-5d | %-5d | %-5d | %-7.1f |\n",
		students[num].name, students[num].id,
		students[num].scores[0], students[num].scores[1],
		students[num].scores[2], students[num].average);
}
