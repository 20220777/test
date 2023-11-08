#include <stdio.h>
#include <stdlib.h>
#include <string.h>
	

	/*
	typedef struct {

		char* buff;
		int component;
		int* end;
		int* tol;


	}project;
	*/


int main() {


	/******************************************************************
	// #1. Basic

	int aa[1024];
	int* p;
	int i;
	p = aa;

	for (i = 0; i < sizeof(aa) / sizeof(int); i++) {
		p[i] = i;

	}

	for (i = 0; i < sizeof(aa)/sizeof(int); i++) {
		printf("p[%d] = %d\n", i,*(p + i));
	}
******************************************************************/




	/*
	// #2. 역순 출력

	int aa[1024];
	int* p;
	int i;
	int size;
	p = aa;

	size = sizeof(aa) / sizeof(int);

	for (i = size - 1; i >= 0; i--) {
		*(p + size - i - 1) = i;
	}

	int k;

	for (k = 0; k < 1024; k++) {
		printf("p[%d] = %d\n", k, *(p + k));
	}
	*/

	/*
	// #3. malloc 함수 이용

	int* p;
	int num;

	printf("배열 생성 개수 : ");
	scanf("%d", &num);

	p = (int*)malloc(sizeof(int) * num);


	int i = 0;
	while (1) {
		*(p + i) = i;
		i++;

		if (i == num)
			break;

	}

	for (i = 0; i < num; i++) {
		printf("p[%d] = %d\n", i, *(p+i));
	}

	free(p);
	*/



	/*
	// #4. 배열 내용 입력 -> 출력 -> 정렬
	int* p;
	int num;
	int temp;

	printf("배열 생성 개수 : ");
	scanf("%d", &num);

	p = (int*)malloc(sizeof(int) * num);


	puts("\n-------배열 내용 입력-------\n");

	int i = 0;
	while (1) {

		printf("p[%d] = ", i);
		scanf("%d", p + i);

		i++;

		if (i == num)
			break;

	}

	puts("\n-------배열 내용 확인-------\n");

	for (i = 0; i < num; i++) {
		printf("p[%d] = %d\n", i, *(p + i));
	}

	puts("\n-------배열 내용 정렬-------\n");

	for (i = 0; i < num-1; i++) {
		for (int k = i + 1; k < num; k++) {
			if (*(p + i) > *(p + k)) {
				temp = *(p + i);
				*(p + i) = *(p + k);
				*(p + k) = temp;
			}
		}
	}

	for (i = 0; i < num; i++) {
		printf("p[%d] = %d\n", i, *(p + i));

	}

	free(p);
	*/

	/*
	// 구조체 연습
	project* pj = malloc(sizeof(project));

	printf("만들 배열 개수 : ");
	scanf("%d", &pj->component);

	pj->buff = malloc(sizeof(int) * (pj->component));
	pj->tol = malloc(sizeof(int) * (pj->component));

	int i;

	for (i = 0; i < pj->component; i++) {
		sprintf(pj->buff, "%d", i);
	}


	for (i = 0; i < pj->component; i++) {
		if (i == 0)
			pj->tol[i] = strtol(pj->buff, &pj->end, 10);
		else if (i == pj->component)
			pj->tol[i] = strtol(pj->end, NULL, 10);
		else if (i > 0 && i < pj->component)
			pj->tol[i] = strtol(pj->end, &pj->end, 10);
	}

	for (i = 0; i < pj->component; i++) {
		printf("p[%d] = %d\n", i, *pj->tol + i);
	}


	free(pj);
	free(pj->buff);
	free(pj->component);
	*/


	char* string;
	int size, length;
	int i;
	int bcnt, scnt, icnt, pcnt;
	int buffer;


	buffer = 'a' - 'A';
	bcnt = scnt = icnt = pcnt = 0;

	printf("문장 길이 : ");
	scanf("%d", &length);
	string = (char*)calloc(length, sizeof(char));

	printf("\n문자열 입력 : ");
	scanf("%s", string);

	size = strlen(string);

	printf("\n거꾸로 출력 : ");
	for (i = size - 1; i >= 0; i--) {
		printf("%c", *(string + i));
	}

	for (i = 0; i < size; i++) {
		if (*(string + i) >= 'A' && *(string + i) <= 'Z')
		{
			bcnt++;
		}
		else if (*(string + i) >= 'a' && *(string + i) <= 'z')
		{
			scnt++;
		}
		else if (*(string + i) >= '0' && *(string + i) <= '9')
		{
			icnt++;
		}
		else if ((*(string + i) >= '!' && *(string + i) <= '/') || (*(string + i) >= ':' && *(string + i) <= '@'))
		{
			pcnt++;
		}
	}

	printf("\n\n대문자 : %d, 소문자 : %d, 숫자 : %d, 특수문자 : %d\n", bcnt, scnt, icnt, pcnt);


	printf("\n대소문자 변환 : ");

	for (i = 0; i < size; i++) {
		if (*(string + i) >= 'A' && *(string + i) <= 'Z')
		{
			*(string + i) += buffer;
		}
		else if (*(string + i) >= 'a' && *(string + i) <= 'z')
		{
			*(string + i) -= buffer;
		}
		else if (*(string + i) >= '0' && *(string + i) <= '9')
		{
			string[i] = *(string + i);
		}
		else if ((*(string + i) >= '!' && *(string + i) <= '/') || (*(string + i) >= ':' && *(string + i) <= '@'))
		{
			string[i] = *(string + i);
		}

		printf("%c", string[i]);
	}

	for (i = 0; i < size; i++) {
		if (*(string + i) >= 'A' && *(string + i) <= 'Z')
		{
			*(string + i) += buffer;
		}
		else if (*(string + i) >= 'a' && *(string + i) <= 'z')
		{
			*(string + i) -= buffer;
		}
		else if (*(string + i) >= '0' && *(string + i) <= '9')
		{
			string[i] = *(string + i);
		}
		else if ((*(string + i) >= '!' && *(string + i) <= '/') || (*(string + i) >= ':' && *(string + i) <= '@'))
		{
			string[i] = *(string + i);
		}

	}

	char* compare;
	int to;

	compare = (char*)calloc(length, sizeof(char));

	printf("\n\n비교할 문장을 입력하세요 : ");
	scanf("%s", compare);

	to = strcmp(string, compare);

	switch (to) {
	case 0: printf("\n두 문장은 같습니다.\n"); break;
	case 1: printf("\n두 문장은 다릅니다.\n"); break;
	case -1: printf("\n두 문장은 다릅니다.\n"); break;
	}
	

	int temp;
	printf("\n문장 정렬하기 : ");
	for (i = 0; i < size - 1; i++) {
		for (int k = i + 1; k < size; k++) {
			if (*(string + i) > *(string + k)) {
				temp = *(string + i);
				*(string + i) = *(string + k);
				*(string + k) = temp;
			}
		}
	}
	for (i = 0; i < size; i++) {
		printf("%c", *(string + i));
	}
	
	

	char ch;

	printf("\n\n단어의 갯수는? [단어 입력] : ");
	scanf(" %c", &ch);

	int component = 0;

	while (string != '\0') {
		string = strchr(string + 1, ch);
		component++;
	}

	printf("\n%c는 %d개 입니다.\n", ch, component - 1);


	
	

}

	

	

