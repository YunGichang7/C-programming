#include <stdio.h>			// 입출력을 위한 라이브러리
#include <Windows.h>		// 화면을 지우는 system("cls");를 쓰기 위한 라이브러리

#define MAX 100				// 단어, 문장의 최대 길이를 100으로 정의
const char DIC_FILE_NAME[] = "dictionary.txt";		// DIC_FILE_NAME 을 "dictionary.txt"로 정의
const char TOUR_FILE_NAME[] = "tour.txt";			// TOUR_FILE_NAMe 을 "tour.txt"로 정의

int insertDic(char* word);	// 단어장에 단어를 등록하는 함수
void viewDic();				// 단어장을 보여주는 함수
void viewTour();			// 자신의 여행 코스를 보여주는 함수

int main() {
	int menu;			// 메뉴 번호를 저장할 변수
	char word[MAX];		// 메뉴 1에서 단어를 입력받을 변수

	while (1) {			// 무한 반복문 (단 4를 입력받을 시 탈출)
		system("cls");	// 현재 콘솔 화면 지움
		printf("                    Close up!                   \n");
		printf("    ┌───────* 메뉴 *───────┐    \n");
		printf("    │ * 1.        단어장 등록            │    \n");
		printf("    │ * 2.        단어장 보기            │    \n");
		printf("    │ * 3.      나의 여행 코스           │    \n");
		printf("    │ * 4.           종료                │    \n");
		printf("    └──────────────────┘    \n");
		printf("\n");
		printf("메뉴 번호를 입력해 주세요 : ");
		scanf_s("%d", &menu);		// 메뉴 번호를 입력

		if (menu == 1) {		// 1번 메뉴
			system("cls");		// 현재 콘솔 화면 지움
			printf("등록할 단어를 입력해 주세요 : "); 
			while (getchar() != '\n');	// 이 과정은 제대로 된 입력을 받기 위해서 버퍼를 비우는 작업
			gets(word);		// word에 문자열(단어)를 입력
			if (insertDic(word) == 0)	// 단어를 입력하는 함수가 성공했을 경우
				printf("등록이 정상적으로 완료되었습니다!\n");
			else   // 단어를 입력하는 함수가 실패했을 경우
				printf("등록에 실패했습니다.\n");
			printf("M을 입력 시 초기 화면으로 돌아갑니다.\n");
			while (getchar() != 'M');	// M을 입력받을 때까지 동작하지 않음
		}
		else if (menu == 2) {	// 2번 메뉴
			system("cls");
			viewDic();			// 단어장을 보여주는 함수를 호출
			printf("M을 입력 시 초기 화면으로 돌아갑니다.\n");
			while (getchar() != 'M');
		}
		else if (menu == 4) {	// 3번 메뉴
			system("cls");		
			viewTour();			// 자신의 여행 코스를 보여주는 함수를 호출
			printf("M을 입력 시 초기 화면으로 돌아갑니다.\n");
			while (getchar() != 'M');
		}
		else if (menu == 5) {	// 4번 메뉴
			system("cls");
			break;			// 무한 반복문을 탈출
		}
		else {			// 메뉴 번호가 잘못되었을 경우
			printf("잘못된 메뉴 번호입니다. 다시 입력해 주세요.\n");
		}
	}
	printf("프로그램을 종료합니다.\n");
	return 0;
}

int insertDic(char* word) {		// 단어장에 단어를 등록하는 함수
	FILE* dicFile = fopen_s(DIC_FILE_NAME, "a");		// dicFile에다가 DIC_FILE_NAME의 이름의 파일을 여는 과정. "a"는 이어쓰기 모드
	if (dicFile != NULL) {		//파일 읽는 데에 성공했을 경우
		fputs(word, dicFile);	// dicFile에다가 word를 쓰는 작업
		fputs("\n", dicFile);	// 개행문자를 쓰는 작업
		fclose(dicFile);		// 파일을 닫음
		return 0;				// 제대로 수행됐을 경우 0을 반환
	}
	else
		return -1;				// 파일 열기에 실패했을 경우 -1을 반환
}
void viewDic() {	// 단어장을 보여주는 함수
	FILE* dicFile = fopen_s(DIC_FILE_NAME, "r");	// 파일을 여는 과정. "r"은 읽기 모드
	char str[MAX];			//파일에서 읽은 문자열을 저장할 배열
	if (dicFile != NULL) {	//파일 읽는 데에 성공했을 경우
		while (fgets(str, sizeof(str), dicFile) != NULL) {		// 파일에서 str로 문자열을 읽어오는 과정. 파일을 모두 읽을 때까지 반복
			puts(str);		//화면에 문자열을 출력
		}
		printf("\n");
	}
	else       // 파일 읽는 데에 실패했을 경우
		printf("파일을 불러오는 데에 실패했습니다.\n");
}
void viewTour() {	// 추천 관광 명소를 보여주는 함수
	FILE* tourFile = fopen(TOUR_FILE_NAME, "r");
	char str[MAX];
	if (tourFile != NULL) {		// 파일 읽는 데에 성공했을 경우
		while (fgets(str, sizeof(str), tourFile) != NULL) {		// 파일에서 str로 문자열을 읽어오는 과정. 파일을 모두 읽을 때까지 반복
			puts(str);		//화면에 문자열을 출력
		}
		printf("\n");
	}
	else        // 파일 읽는 데에 실패했을 경우
		printf("파일을 불러오는 데에 실패했습니다.\n");
}