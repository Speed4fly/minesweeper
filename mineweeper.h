
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
	vector<vector<int>> map_data;
	vector<vector<int>> map_indicater;
	vector<vector<string>> map_display;
public:
	map4minesweeper() {

	}
	void map(int length,int difficulty) {
		srand((int)time(0));
		this->length = length;
		vector<int> tmp;
		vector<string> c_tmp;
			for (int index = 0; index < length; index++) {
				this->map_data.push_back(tmp);
				this->map_display.push_back(c_tmp);
				for (int sub_index = 0; sub_index < length; sub_index++) {
					this->map_display[index].push_back(".");
					if (rand() % 100 > difficulty) this->map_data[index].push_back(0);
					else this->map_data[index].push_back(1);
				}
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
				}
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
		}
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
		}

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
		}
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
		}
	}
	int click(int x, int y) {
		if (x >= this->length || y >= this->length) {
			cout << "��Ч����" << endl;
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
			cout << to_string(index) << ' ';
		}
		cout << endl;
		for (int index = 0; index < this->length; index++) {
			cout << "Line" << to_string(index) << "  ";
			for (int sub_index = 0; sub_index < this->length; sub_index++) {
				cout << this->map_display[index][sub_index] << ' ';
			}
			cout << endl;
		}
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
		}
		if (flag == 1)
			this->check40();
	}
	void show_bomb(){
		int wrong_flag = 0;
		for (int index = 0; index < this->length; index++) {
			for (int sub_index = 0; sub_index < this->length; sub_index++) {
				if (this->map_display[index][sub_index] == "!"&&this->map_data[index][sub_index]==0) {
					wrong_flag += 1;
				}
				if (this->map_data[index][sub_index] == 1) {
					if (this->map_display[index][sub_index] == "!") {
						this->map_display[index][sub_index] = "v";
					}
					else
						this->map_display[index][sub_index] = "X";
				}
				else
				{
					this->map_display[index][sub_index] = to_string(this->map_indicater[index][sub_index]);
				}
			}
		}
		this->display();
		cout << "������" << to_string(wrong_flag) << "����" << endl;
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
		}
		if (flag == 0) {
			return 1;
		}
		return 0;
	}
	void flag(int x, int y) {
		this->map_display[x][y] = "!";
	}
	
};
