#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS




typedef struct Account
{                                        //linked list
	int account; //계좌번호 10자리 5자리는 은행 5자리는 00001부터
	char name[15]; //예금주
	int password; //비밀번호
	unsigned long long int balance; //잔액

	struct Account* next; //다음 노드 주소를 저장
}Account;

//Account* tail = NULL;
int n = 0;

void Exit(Account* FirstMember) //프로그램을 종료하며 파일에 저장
{
	FILE* save = fopen("file.txt", "wt");
	if (FirstMember != NULL)
	{

		FirstMember = FirstMember->next;
		while (FirstMember->next != NULL)
		{
			Account* al = FirstMember;

			fprintf(save, "%s\t %d\t %d\t %llu\n", al->name, al->account, al->password, al->balance);
			FirstMember = FirstMember->next;
		}
		fprintf(save, "%s\t %d\t %d\t %llu", FirstMember->name, FirstMember->account, FirstMember->password, FirstMember->balance);

		fclose(save);
		free(FirstMember);
	}
	else
		printf("오류");
}

Account* Load(Account* FirstMember) //프로그램 시작하며 파일데이터를 불러옴
{
	//Account* tail = initialize();
	FILE* load = fopen("file.txt", "rt");
	if (load != NULL)
	{
		Account* curr = NULL;
		while (feof(load) == 0) //끝에서 0아닌 값 리턴
		{
			curr = calloc(1, sizeof(Account));
			curr->next = NULL;
			fscanf(load, "%s\t %d\t %d\t %llu\n", &curr->name, &curr->account, &curr->password, &curr->balance);

			if (FirstMember == NULL)
			{
				FirstMember = curr;
			}
			else
			{
				Account* temp = FirstMember;
				while (temp->next != NULL)
				{
					temp = temp->next;
				}
				temp->next = curr;
			}
		}
		fclose(load);
		return curr;
	}
	return NULL;
}

int makeAccount(Account* target)//계좌번호 비밀번호 예금주 금액을 입력 받고 리스트에 저장      순서 바꿔야함
{

	int a = 1234500000;
	Account* newNode = malloc(sizeof(Account));

	int account; //계좌번호 10자리 5자리는 은행 5자리는 00001부터
	int password; //비밀번호
	int passwordConfirm;//비밀번호확인
	unsigned long long int balance = 0; //잔액
	account = a + n;

	printf("예금주를 입력해 주세요: \n");
	scanf("%s", newNode->name, sizeof(newNode->name));
	printf("4자리 숫자 비밀번호를 입력해 주세요: \n");
	scanf("%i", &password);
	printf("비밀번호를 다시 입력해 주세요: \n");
	scanf("%i", &passwordConfirm);
	while (password != passwordConfirm)
	{
		printf("다시 입력한 비밀번호가 일치하지 않습니다. 비밀번호를 다시 입력해 주세요: \n");
		scanf("%i", &passwordConfirm);
	}
	printf("입금할 금액을 입력해 주세요: \n");

	scanf("%llu", &balance);
	printf("계좌가 생성되었습니다.\n계좌번호는 %i 입니다.\n\n", account);
	newNode->account = account;
	newNode->password = password;
	newNode->balance = balance;
	newNode->next = NULL;
	n = n + 1;

	if (target == NULL)
		target = newNode;
	else
	{
		Account* tail = target;

		while (tail->next != NULL)
		{
			tail = tail->next;
		}

		tail->next = newNode;

	}


	return n;
}

Account* accountSearch(Account* node, int a) //계좌번호로 검색
{
	if (node == NULL)
	{
		printf("오류\n");
		return NULL;
	}
	Account* curr = node->next;
	while (curr != NULL)
	{
		if (curr->account == a)
			return curr;
		curr = curr->next;
	}
	printf("계좌가 없습니다.\n");
	return NULL;
}

void checkBalance(Account* target) //잔액조회
{
	Account* curr;
	int a;
	int p;
	printf("계좌번호를 입력해 주세요: \n");
	scanf("%i", &a);
	printf("비밀번호를 입력해 주세요: \n");
	scanf("%i", &p);
	curr = accountSearch(target, a);
	if (curr == NULL)
	{
		printf("없는 계좌입니다. 입금을 종료합니다.\n\n");
		return;
	}
	while (curr->password != p)
	{
		printf("입력한 비밀번호가 일치하지 않습니다. 비밀번호를 다시 입력해 주세요: \n");
		scanf("%i", &p);
	}
	printf("잔액은 %llu 원 입니다.\n\n", curr->balance);
}

void deposit(Account* target) //입금
{
	Account* curr;
	int a;
	unsigned long long b;
	printf("계좌번호를 입력해 주세요: \n");
	scanf("%i", &a);
	printf("입금할 금액을 입력해 주세요: \n");
	scanf("%llu", &b);
	curr = accountSearch(target, a);
	if (curr == NULL)
	{
		printf("없는 계좌입니다. 입금을 종료합니다.\n\n");
		return;
	}
	curr->balance = curr->balance + b;
	printf("%llu원이 입금되었습니다.\n\n", b);
}

void withdraw(Account* target) //출금
{
	Account* curr;
	int a;
	int p;
	unsigned long long b;
	printf("계좌번호를 입력해 주세요: \n");
	scanf("%i", &a);
	printf("출금할 금액을 입력해 주세요: \n");
	scanf("%llu", &b);
	printf("비밀번호를 입력해 주세요: \n");
	scanf("%i", &p);
	curr = accountSearch(target, a);
	if (curr == NULL)
	{
		printf("없는 계좌입니다. 입금을 종료합니다.\n\n");
		return;
	}                                    //예외 금액부족 처리
	while (curr->password != p)
	{
		printf("입력한 비밀번호가 일치하지 않습니다. 비밀번호를 다시 입력해 주세요: \n");
		scanf("%i", &p);
	}
	if (b > curr->balance)
	{
		printf("잔액이 부족합니다. 출금을 종료합니다.\n\n");
		return;
	}
	curr->balance = curr->balance - b;
	printf("%llu원이 출금되었습니다.\n\n", b);
	return;
}

void send(Account* target) //송금
{
	Account* curr;
	int account1;//본인계좌
	unsigned long long int b = 0;//보낼금액
	int p;//비밀번호
	int account2;//상대계좌
	char name[15];
	printf("본인의 계좌번호를 입력해 주세요: \n");
	scanf("%i", &account1);
	printf("비밀번호를 입력해 주세요: \n");
	scanf("%i", &p);
	curr = accountSearch(target, account1);
	if (curr == NULL)
	{
		printf("없는 계좌입니다. 입금을 종료합니다.\n\n");
		return;
	}
	while (curr->password != p)
	{
		printf("입력한 비밀번호가 일치하지 않습니다. 비밀번호를 다시 입력해 주세요: \n");
		scanf("%i", &p);
	}
	printf("보낼 금액을 입력해 주세요: \n");
	scanf("%llu", &b);
	if (b > curr->balance)
	{
		printf("잔액이 부족합니다. 송금을 종료합니다.\n\n");
		return;
	}
	curr->balance = curr->balance - b;
	printf("받을 계좌번호를 입력해 주세요: \n");
	scanf("%i", &account2);
	printf("받을 계좌 예금주를 입력해 주세요: \n");
	scanf("%s", name, sizeof(name));


	curr = accountSearch(target, account2);
	if (curr == NULL)
	{
		printf("없는 계좌입니다. 입금을 종료합니다.\n\n");
		curr->balance = curr->balance + b;
		return;
	}
	char a = strcmp(name, curr->name);
	while (a != 0)
	{
		printf("입력한 예금주와 계좌번호가 일치하지 않습니다. 받을 계좌의 예금주를 다시 입력해 주세요: \n");
		scanf("%s", name, sizeof(name));
		a = strcmp(name, curr->name);
	}

	curr->balance = curr->balance + b;
	printf("보낸 금액은 %llu 원 입니다.\n\n", b);
	return;
}



int main()
{
	Account* head = calloc(1, sizeof(Account));
	head->next = NULL;
	Account* curr = head->next;
	Account* Node = Load(head);                     //duplication avoid by accountnumber-123450000n


	while (Node->account - (1234500000 + n) > 0)
	{
		n = n + 1;
	}
	n = n + 1;

	char s;
	while (1)
	{
		printf("--------------------------------------\n은행 서비스\n");
		printf("원하시는 서비스의 번호를 입력해주세요.\n(1. 계좌생성, 2. 잔액조회, 3. 입금, 4. 출금, 5. 송금, 6. 종료)\n");
		scanf("%hhi", &s);

		if (s == 1)
			makeAccount(head);
		else
		{
			if (s == 2)
				checkBalance(head);
			else
			{

				if (s == 3)
					deposit(head);
				else
				{

					if (s == 4)
						withdraw(head);
					else
					{

						if (s == 5)
							send(head);
						else
						{
							Exit(head);
							break;
						}
					}
				}
			}
		}
	}


	while (curr != NULL)
	{

		free(curr);

	}
	free(head);
	return 0;
}
