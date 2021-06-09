
#include "stdlib.h"
#include<vector>
#include<iostream>
#include<string>
#include<time.h>


using namespace std;
class map4minesweeper {
private:
	int length{};
	//int difficulty;
	vector<vector<int>> map_data;//存储雷所在位置
	vector<vector<int>> map_indicater;//此处每个坐标内数字均代表其周围雷的数量
	vector<vector<string>> map_display;//为用户展示的雷区样式
public:
	map4minesweeper() {

	}
	void map(int length,int difficulty) {
		srand((int)time(0));//初始化随机种子
		this->length = length;//存储棋盘大小备用
		vector<int> tmp;
		vector<string> c_tmp;
			for (int index = 0; index < length; index++) {
				this->map_data.push_back(tmp);//初始化雷区
				this->map_display.push_back(c_tmp);//初始化显示区
				for (int sub_index = 0; sub_index < length; sub_index++) {
					this->map_display[index].push_back(".");
					if (rand() % 100 > difficulty) this->map_data[index].push_back(0);
					else this->map_data[index].push_back(1);
				}//初始化雷区，0代表安全，1代表有雷
			}
			for (int index = 0; index < length; index++) {
				this->map_indicater.push_back(tmp);
				for (int sub_index = 0; sub_index < length; sub_index++) {
					int sum = 0;
					for (int x = index - 1; x < index + 2; x++) {
						for (int y = sub_index - 1; y < sub_index + 2; y++) {
							if (x >= 0 && x < length && y >= 0 && y < length) sum += this->map_data[x][y];

						}
					}
					sum -= this->map_data[index][sub_index];
					this->map_indicater[index].push_back(sum);
				}//计算每个坐标周围雷的数量并存入map_indicater
		}
	}
	void cleary(int x, int y) {
		int sub_index = y;
		while (sub_index>=0)
		{
			if (this->map_indicater[x][sub_index] == 0) {
				this->map_display[x][sub_index] = to_string(this->map_indicater[x][sub_index]);
				sub_index -= 1;
			}
			else {
				this->map_display[x][sub_index] = to_string(this->map_indicater[x][sub_index]);
				break;
			}
		}//清理x,y坐标下方的雷区直至扫描到周围有雷
		sub_index = y + 1;
		while (sub_index < this->length)
		{
			if (this->map_indicater[x][sub_index] == 0) {
				this->map_display[x][sub_index] = to_string(this->map_indicater[x][sub_index]);
				sub_index += 1;
			}
			else {
				this->map_display[x][sub_index] = to_string(this->map_indicater[x][sub_index]);
				break;
			}
		}//清理x,y坐标上方的雷区直至扫描到周围有雷

	}
	void clear(int x, int y) {
		int index = x;
		while (index>=0)
		{
			if (this->map_indicater[index][y] == 0) {
				this->map_display[index][y] = to_string(this->map_indicater[index][y]);
				this->cleary(index, y);
				index -= 1;
			}
			else {
				this->map_display[index][y] = to_string(this->map_indicater[index][y]);
				break;
			}
		}//清理x,y坐标左方的雷区直至扫描到周围有雷
		index = x + 1;
		while (index >this->length)
		{
			if (this->map_indicater[index][y] == 0) {
				this->map_display[index][y] = to_string(this->map_indicater[index][y]);
				this->cleary(index, y);
				index += 1;
			}
			else {
				this->map_display[index][y] = to_string(this->map_indicater[index][y]);
				break;
			}
		}//清理x,y坐标右方的雷区直至扫描到周围有雷
	}
	int click(int x, int y) {
		if (x >= this->length || y >= this->length) {//判断输入是否超出棋盘范围
			cout << "无效坐标" << endl;
			return 1;
		}
		else {
			if (this->map_data[x][y] == 0) {
				this->clear(x, y);
				return 1;
			}
			else
				return 0;
		}
	}
	void display() {
		cout << "LINE   ";
		for (int index = 0; index < this->length; index++) {
			cout << to_string(index) << " ";//输出棋盘指示器横坐标
		}
		cout << "\n" << endl;
		for (int index = 0; index < this->length; index++) {
			cout << "Line" << to_string(index) << "  ";//输出棋盘指示器纵坐标
			for (int sub_index = 0; sub_index < this->length; sub_index++) {
				cout << this->map_display[index][sub_index] << ' ';
			}
			cout << endl;
		}//输出棋盘
	}
	void check40() {
		int flag = 0;
		for (int index = 0; index < this->length; index++) {
			for (int sub_index = 0; sub_index < this->length; sub_index++) {
				if (this->map_display[index][sub_index] == ".") {
					for (int x = index - 1; x < index + 2; x++) {
						for (int y = sub_index - 1; y < sub_index + 2; y++) {
							if (x >= 0 && x < this->length && y >= 0 && y < this->length) {
								if (this->map_display[x][y] == "0") {
									this->map_display[index][sub_index] = to_string(this->map_indicater[index][sub_index]);
									flag = 1;
								}
							}
						}
					}
				}
			}
		}//检查是否有可以自动扫描的坐标，若有则将其扫描。自动扫描已知周围没有雷但是尚未扫描的坐标。
		if (flag == 1)
			this->check40();//递归至无法自动扫描
	}
	void show_bomb(){
		int wrong_flag = 0;
		for (int index = 0; index < this->length; index++) {
			for (int sub_index = 0; sub_index < this->length; sub_index++) {
				if (this->map_display[index][sub_index] == "!"&&this->map_data[index][sub_index]==0) {
					wrong_flag += 1;
				}
				if (this->map_data[index][sub_index] == 1) {
					if (this->map_display[index][sub_index] == "!") {//！ 代表标记的雷
						this->map_display[index][sub_index] = "v";//v 代表标记正确的雷
					}
					else
						this->map_display[index][sub_index] = "X";//X代表未标记的雷
				}
				else
				{
					this->map_display[index][sub_index] = to_string(this->map_indicater[index][sub_index]);
				}
			}
		}
		this->display();
		cout << "错误标记" << to_string(wrong_flag) << "个。" << endl;
	}
	int is_success() {
		int flag = 0;
		for (int index = 0; index < this->length; index++) {
			for (int sub_index = 0; sub_index < this->length; sub_index++) {
				if (this->map_data[index][sub_index] == 0&& this->map_display[index][sub_index] == ".") {
					flag = 1;
					break;
				}
			}
		}//判断所有可扫描的非雷坐标是否已经被扫描完成。如果无雷坐标均被扫描（代表已经安全），则认为扫雷成功
		if (flag == 0) {
			return 1;
		}
		return 0;
	}
	void flag(int x, int y) {
		this->map_display[x][y] = "!";//标记雷区功能
	}
	
};
