#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<conio.h>


//ȫ�ֱ���
int position_x, position_y;//�ɻ�λ��
int position_vx, position_vy;//�ɻ��ٶ�
int width, high;//����Ϸ������ߣ���Ҫ�ط�i,j��֮��Ӧ
char isBegin, isEnd;//��ʼ���������Ľ����ж���־
int cmd_x, cmd_y;//��ʼ��������������λ��
int flag1;//����Ƿ��˳���־ 0���� 1����
int flag2;//��Ϸ�Ƿ������־ 0���� 1����
int enemy_x, enemy_y;//�л�����
int enemy_vx, enemy_vy;//�л��ٶ�
int bullet_x, bullet_y;//�ӵ�λ��
int bullet_vx, bullet_vy;//�ӵ��ٶ�
char input;//��Ϸ����
int blood;//Ѫ�� 
int blood_x,blood_y;//Ѫ����ʾλ�� 
int score;//�÷�
int score_x,score_y;//������ʾλ�� 
 
//��������


void startup();//��ʼ����������
void show();//��ʾ���溯��
void updateWithInput();//�û��������ݸ��º���
void updateWithoutInput();//���û����ݸ��º���
void begin();//��ʼ���溯��
void end();//�������溯��
void HideCursor();//���ع�꺯��   �������gotoxy()�����Ż����溯��
void gotoxy(int x,int y);//�Ϻ������ػ�����

//��������ʼ

int main(void) {
	startup();// ���ݳ�ʼ��
	while (flag1==0) {
		begin();
		while (flag2 == 0) {
			show();
			updateWithInput();
			updateWithoutInput();
		}
		end();
	}
	return 0;
}

void startup() {
	width = 30;
	high = 30;
	position_x = width / 2;
	position_y = high - 2;
	position_vx = 1;
	position_vy = 1;
	cmd_x = 11;
	cmd_y = 9;
	flag1 = 0;
	flag1 = 0;
	enemy_x = rand() % width;
	enemy_y = 0;
	enemy_vx = 0;
	enemy_vy = 1;
	bullet_vx = 0;
	bullet_vy = -1;
	blood = 3;
	blood_x = width+2;
	blood_y = high-2;
	score = 0;
	score_x = width+2;
	score_y = high-4; 
}
void show() {
	//system("cls"); //������������̫����
	gotoxy(0,0);  //������Ƶ���0��0�����൱�������ػ�
	HideCursor();//���ع��
	for (int j = 0; j <= high; j++) {
		for (int i = 0; i <= width+12; i++) {
			if (i == position_x && j == position_y && i > 0 && i < width && j>0 && j < high)
				printf("*");//��ӡ�ɻ�
			else if (i == 0 || i == width || j == 0 || j == high)
				printf("*");//��ӡ�߿�
			else if (i == enemy_x && j == enemy_y)
				printf("@");
			else if (i == bullet_x && j == bullet_y)
				printf("|");
			else if (i == blood_x && j ==blood_y )
				printf("BLOOD:%d",blood);
			else if (i == score_x && j == score_y) 
				printf("SCORE:%d",score);
			
			else
				printf(" ");//��ӡ����հ״�
		}
		printf("\n");//��һ��
	}
}
void updateWithInput() {
	if (_kbhit()) {
		
			input = _getch();
			switch (input) {
			case 'w': {
				if(position_y!=1)
				position_y = position_y - position_vy; 
			}
				break;
			case's': {
				if (position_y != high-1)
					position_y = position_y + position_vy; 
			}
				break;
			case'a': {
				if (position_x != 1)
					position_x = position_x - position_vx; 
			}
				break;
			case'd': {
				if (position_x != width-1)
					position_x = position_x + position_vx;
			}
				break;
			case' ': {
				bullet_x = position_x;
				bullet_y = position_y - 1;
			}
				   break;
			}
		}
}

void updateWithoutInput() {
	//�ӵ��ƶ�
	bullet_x = bullet_x + bullet_vx;
	bullet_y = bullet_y + bullet_vy;
	//�л��ƶ�
	enemy_x = enemy_x + enemy_vx;
	enemy_y = enemy_y + enemy_vy;
	//���е÷� 
	if(enemy_x == bullet_x&&(enemy_y == bullet_y||enemy_y == bullet_y-1))
	{
		score++;
		enemy_y = high;
	}
	
	//�л�ˢ��
	if(enemy_y == high)
	{
		 	enemy_x = rand() % width;
			enemy_y = 0;
    }
    
	//����ֵ�ж� 
	if(position_x == enemy_x && (position_y == enemy_y||position_y == enemy_y+1))
	{
		blood-=1;
		position_x = width / 2;
		position_y = high - 2;
		enemy_x = rand() % width;
		enemy_y = 0;
		if(blood <= 0)
			flag2 = 1;
		
	}
	
	
}

void begin() {
	system("mode con cols=51 lines=32");//����̨��С ��34 ��32
	HideCursor();
	for(int i=0;i<=width+13;i++)
		printf("-");
	gotoxy(cmd_x, cmd_y);
	printf("The Airship Destroyer");
	gotoxy(cmd_x+5, cmd_y+2);
	printf("Version  1.0");
	gotoxy(cmd_x+1, cmd_y+5);
	printf("(Enter n to start)");
	gotoxy(0, high);
	for (int i = 0; i <= width+13; i++)
		printf("-");
	isBegin = _getch();
	while (isBegin != 'n') {
		isBegin = _getch();
	}
	

}

void end() {
	//��Ϸ�˳�������ʾ   δ����
	system("cls");
	for (int i = 0; i <= width+13; i++)
		printf("-");
	gotoxy(cmd_x, cmd_y);
	printf("The Airship Destroyer");
	gotoxy(cmd_x + 5, cmd_y + 2);
	printf("Version  1.0");
	gotoxy(cmd_x + 1, cmd_y + 5);
	printf("(Enter n to restart or q to exit)");
	gotoxy(0, high);
	for (int i = 0; i <= width; i++)
		printf("-");
	isBegin = _getch();
	while ((isEnd != 'n')&&(isEnd != 'q')) {
		isEnd = _getch();
	}
	if (isEnd == 'n')//ʵ����Ϸ���¿�ʼ������˳�
		{
		flag1 = 0;
		flag2 = 0;
		}
	else if (isEnd == 'q') 
		flag1 = 1;	
}

void gotoxy(int x, int y) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(handle, pos);
}

void HideCursor() {
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };//0��ʾ���ع��
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
