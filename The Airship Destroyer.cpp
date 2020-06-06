#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>
#include<conio.h>


//全局变量
int position_x, position_y;//飞机位置
int width, high;//主游戏界面宽、高，必要地方i,j于之对应


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
	begin();
	startup();// 数据初始化
	while (1) {
		show();
		updateWithInput();
		updateWithoutInput();
	}
	end();
	return 0;
}

void startup() {
	width = 20;
	high = 30;
	position_x = width / 2;
	position_y = high - 2;
}
void show() {
	//system("cls"); //清屏函数闪屏太严重
	gotoxy(0,0);  //将光标移到（0，0），相当于清屏重画
	for (int j = 0; j <= high; j++) {
		for (int i = 0; i <= width; i++) {
			if (i == position_x && j == position_y)
				printf("*");//打印飞机
			else if (i == 0 || i == width || j == 0 || j == high)
				printf("*");//打印边框
			else
				printf(" ");//打印其余空白处
		}
		printf("\n");//下一行
	}
}
void updateWithInput() {

}

void updateWithoutInput() {

}

void begin() {

}

void end() {

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