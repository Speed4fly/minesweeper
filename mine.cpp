// mine.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "mineweeper.h"
#include<iostream>
using namespace std;

int main() {
	int x, y, difficulty, length, mode;
	cout << "输入游戏难度(小于100的十进制整数)，来作为生成雷的概率。" << endl;
	cin >> difficulty;
	cout << "输入游戏棋盘宽度，推荐用小于10的整数。" << endl;
	cin >> length;
	map4minesweeper m;//新建扫雷游戏对象
	m.map(length, difficulty);//初始化扫雷游戏，输入雷区大小和难度
	while (true)
	{	
		system("cls");
		m.check40();//检查是否仍有可以自动扫描的点位
		if (m.is_success() == 1) {
			cout << "SUCCESS!" << endl;
			m.show_bomb();
			system("pause");
			return 0;
		}
		
		m.display();//展示目前雷区样式
		cout << "输入探测模式：\n0:扫描(若扫描点有雷则直接爆炸)\n1:标记为地雷" << endl;
		cin >> mode;
		cout << "输入想要探测的坐标(空格分割)。" << endl;
		cin >> x >> y;
		if (mode == 1) {
			m.flag(y, x);//标记潜在雷区
		}
		else {
			if (m.click(y, x) == 0) {//返回值为0代表触及地雷
				cout << "BOOM!" << endl;
				m.show_bomb();
				system("pause");
				return 0;
			}
		}
		


	}
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
