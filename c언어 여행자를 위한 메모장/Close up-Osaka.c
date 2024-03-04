#include <stdio.h>			// ������� ���� ���̺귯��
#include <Windows.h>		// ȭ���� ����� system("cls");�� ���� ���� ���̺귯��

#define MAX 100				// �ܾ�, ������ �ִ� ���̸� 100���� ����
const char DIC_FILE_NAME[] = "dictionary.txt";		// DIC_FILE_NAME �� "dictionary.txt"�� ����
const char TOUR_FILE_NAME[] = "tour.txt";			// TOUR_FILE_NAMe �� "tour.txt"�� ����

int insertDic(char* word);	// �ܾ��忡 �ܾ ����ϴ� �Լ�
void viewDic();				// �ܾ����� �����ִ� �Լ�
void viewTour();			// �ڽ��� ���� �ڽ��� �����ִ� �Լ�

int main() {
	int menu;			// �޴� ��ȣ�� ������ ����
	char word[MAX];		// �޴� 1���� �ܾ �Է¹��� ����

	while (1) {			// ���� �ݺ��� (�� 4�� �Է¹��� �� Ż��)
		system("cls");	// ���� �ܼ� ȭ�� ����
		printf("                    Close up!                   \n");
		printf("    ����������������* �޴� *����������������    \n");
		printf("    �� * 1.        �ܾ��� ���            ��    \n");
		printf("    �� * 2.        �ܾ��� ����            ��    \n");
		printf("    �� * 3.      ���� ���� �ڽ�           ��    \n");
		printf("    �� * 4.           ����                ��    \n");
		printf("    ����������������������������������������    \n");
		printf("\n");
		printf("�޴� ��ȣ�� �Է��� �ּ��� : ");
		scanf_s("%d", &menu);		// �޴� ��ȣ�� �Է�

		if (menu == 1) {		// 1�� �޴�
			system("cls");		// ���� �ܼ� ȭ�� ����
			printf("����� �ܾ �Է��� �ּ��� : "); 
			while (getchar() != '\n');	// �� ������ ����� �� �Է��� �ޱ� ���ؼ� ���۸� ���� �۾�
			gets(word);		// word�� ���ڿ�(�ܾ�)�� �Է�
			if (insertDic(word) == 0)	// �ܾ �Է��ϴ� �Լ��� �������� ���
				printf("����� ���������� �Ϸ�Ǿ����ϴ�!\n");
			else   // �ܾ �Է��ϴ� �Լ��� �������� ���
				printf("��Ͽ� �����߽��ϴ�.\n");
			printf("M�� �Է� �� �ʱ� ȭ������ ���ư��ϴ�.\n");
			while (getchar() != 'M');	// M�� �Է¹��� ������ �������� ����
		}
		else if (menu == 2) {	// 2�� �޴�
			system("cls");
			viewDic();			// �ܾ����� �����ִ� �Լ��� ȣ��
			printf("M�� �Է� �� �ʱ� ȭ������ ���ư��ϴ�.\n");
			while (getchar() != 'M');
		}
		else if (menu == 4) {	// 3�� �޴�
			system("cls");		
			viewTour();			// �ڽ��� ���� �ڽ��� �����ִ� �Լ��� ȣ��
			printf("M�� �Է� �� �ʱ� ȭ������ ���ư��ϴ�.\n");
			while (getchar() != 'M');
		}
		else if (menu == 5) {	// 4�� �޴�
			system("cls");
			break;			// ���� �ݺ����� Ż��
		}
		else {			// �޴� ��ȣ�� �߸��Ǿ��� ���
			printf("�߸��� �޴� ��ȣ�Դϴ�. �ٽ� �Է��� �ּ���.\n");
		}
	}
	printf("���α׷��� �����մϴ�.\n");
	return 0;
}

int insertDic(char* word) {		// �ܾ��忡 �ܾ ����ϴ� �Լ�
	FILE* dicFile = fopen_s(DIC_FILE_NAME, "a");		// dicFile���ٰ� DIC_FILE_NAME�� �̸��� ������ ���� ����. "a"�� �̾�� ���
	if (dicFile != NULL) {		//���� �д� ���� �������� ���
		fputs(word, dicFile);	// dicFile���ٰ� word�� ���� �۾�
		fputs("\n", dicFile);	// ���๮�ڸ� ���� �۾�
		fclose(dicFile);		// ������ ����
		return 0;				// ����� ������� ��� 0�� ��ȯ
	}
	else
		return -1;				// ���� ���⿡ �������� ��� -1�� ��ȯ
}
void viewDic() {	// �ܾ����� �����ִ� �Լ�
	FILE* dicFile = fopen_s(DIC_FILE_NAME, "r");	// ������ ���� ����. "r"�� �б� ���
	char str[MAX];			//���Ͽ��� ���� ���ڿ��� ������ �迭
	if (dicFile != NULL) {	//���� �д� ���� �������� ���
		while (fgets(str, sizeof(str), dicFile) != NULL) {		// ���Ͽ��� str�� ���ڿ��� �о���� ����. ������ ��� ���� ������ �ݺ�
			puts(str);		//ȭ�鿡 ���ڿ��� ���
		}
		printf("\n");
	}
	else       // ���� �д� ���� �������� ���
		printf("������ �ҷ����� ���� �����߽��ϴ�.\n");
}
void viewTour() {	// ��õ ���� ��Ҹ� �����ִ� �Լ�
	FILE* tourFile = fopen(TOUR_FILE_NAME, "r");
	char str[MAX];
	if (tourFile != NULL) {		// ���� �д� ���� �������� ���
		while (fgets(str, sizeof(str), tourFile) != NULL) {		// ���Ͽ��� str�� ���ڿ��� �о���� ����. ������ ��� ���� ������ �ݺ�
			puts(str);		//ȭ�鿡 ���ڿ��� ���
		}
		printf("\n");
	}
	else        // ���� �д� ���� �������� ���
		printf("������ �ҷ����� ���� �����߽��ϴ�.\n");
}