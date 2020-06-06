#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<conio.h>


//全局变量
int position_x, position_y;//飞机位置
int position_vx, position_vy;//飞机速度
int width, high;//主游戏界面宽、高，必要地方i,j于之对应
char isBegin, isEnd;//开始与结束界面的结束判定标志
int cmd_x, cmd_y;//开始与结束界面的文字位置
int flag1;//软件是否退出标志 0继续 1结束
int flag2;//游戏是否结束标志 0继续 1结束
int enemy_x, enemy_y;//敌机坐标
int enemy_vx, enemy_vy;//敌机速度
int bullet_x, bullet_y;//子弹位置
int bullet_vx, bullet_vy;//子弹速度
char input;//游戏输入
int blood;//血量 
int blood_x,blood_y;//血量显示位置 
int score;//得分
int score_x,score_y;//分数显示位置 
 
//函数声明


void startup();//初始化变量函数
void show();//显示界面函数
void updateWithInput();//用户输入数据更新函数
void updateWithoutInput();//非用户数据更新函数
void begin();//开始界面函数
void end();//结束界面函数
void HideCursor();//隐藏光标函数   和下面的gotoxy()都是优化界面函数
void gotoxy(int x,int y);//较好清屏重画函数

//主函数开始

int main(void) {
	startup();// 数据初始化
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
	//system("cls"); //清屏函数闪屏太严重
	gotoxy(0,0);  //将光标移到（0，0），相当于清屏重画
	HideCursor();//隐藏光标
	for (int j = 0; j <= high; j++) {
		for (int i = 0; i <= width+12; i++) {
			if (i == position_x && j == position_y && i > 0 && i < width && j>0 && j < high)
				printf("*");//打印飞机
			else if (i == 0 || i == width || j == 0 || j == high)
				printf("*");//打印边框
			else if (i == enemy_x && j == enemy_y)
				printf("@");
			else if (i == bullet_x && j == bullet_y)
				printf("|");
			else if (i == blood_x && j ==blood_y )
				printf("BLOOD:%d",blood);
			else if (i == score_x && j == score_y) 
				printf("SCORE:%d",score);
			
			else
				printf(" ");//打印其余空白处
		}
		printf("\n");//下一行
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
	//子弹移动
	bullet_x = bullet_x + bullet_vx;
	bullet_y = bullet_y + bullet_vy;
	//敌机移动
	enemy_x = enemy_x + enemy_vx;
	enemy_y = enemy_y + enemy_vy;
	//击中得分 
	if(enemy_x == bullet_x&&(enemy_y == bullet_y||enemy_y == bullet_y-1))
	{
		score++;
		enemy_y = high;
	}
	
	//敌机刷新
	if(enemy_y == high)
	{
		 	enemy_x = rand() % width;
			enemy_y = 0;
    }
    
	//生命值判定 
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
	system("mode con cols=51 lines=32");//控制台大小 宽34 高32
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
	//游戏退出界面显示   未改完
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
	if (isEnd == 'n')//实现游戏重新开始与结束退出
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
	CONSOLE_CURSOR_INFO cursor_info = { 1,0 };//0表示隐藏光标
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
}
