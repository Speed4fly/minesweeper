
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
	vector<vector<int>> map_data;//�洢������λ��
	vector<vector<int>> map_indicater;//�˴�ÿ�����������־���������Χ�׵�����
	vector<vector<string>> map_display;//Ϊ�û�չʾ��������ʽ
public:
	map4minesweeper() {

	}
	void map(int length,int difficulty) {
		srand((int)time(0));//��ʼ���������
		this->length = length;//�洢���̴�С����
		vector<int> tmp;
		vector<string> c_tmp;
			for (int index = 0; index < length; index++) {
				this->map_data.push_back(tmp);//��ʼ������
				this->map_display.push_back(c_tmp);//��ʼ����ʾ��
				for (int sub_index = 0; sub_index < length; sub_index++) {
					this->map_display[index].push_back(".");
					if (rand() % 100 > difficulty) this->map_data[index].push_back(0);
					else this->map_data[index].push_back(1);
				}//��ʼ��������0����ȫ��1��������
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
				}//����ÿ��������Χ�׵�����������map_indicater
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
		}//����x,y�����·�������ֱ��ɨ�赽��Χ����
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
		}//����x,y�����Ϸ�������ֱ��ɨ�赽��Χ����

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
		}//����x,y�����󷽵�����ֱ��ɨ�赽��Χ����
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
		}//����x,y�����ҷ�������ֱ��ɨ�赽��Χ����
	}
	int click(int x, int y) {
		if (x >= this->length || y >= this->length) {//�ж������Ƿ񳬳����̷�Χ
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
			cout << to_string(index) << " ";//�������ָʾ��������
		}
		cout << "\n" << endl;
		for (int index = 0; index < this->length; index++) {
			cout << "Line" << to_string(index) << "  ";//�������ָʾ��������
			for (int sub_index = 0; sub_index < this->length; sub_index++) {
				cout << this->map_display[index][sub_index] << ' ';
			}
			cout << endl;
		}//�������
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
		}//����Ƿ��п����Զ�ɨ������꣬��������ɨ�衣�Զ�ɨ����֪��Χû���׵�����δɨ������ꡣ
		if (flag == 1)
			this->check40();//�ݹ����޷��Զ�ɨ��
	}
	void show_bomb(){
		int wrong_flag = 0;
		for (int index = 0; index < this->length; index++) {
			for (int sub_index = 0; sub_index < this->length; sub_index++) {
				if (this->map_display[index][sub_index] == "!"&&this->map_data[index][sub_index]==0) {
					wrong_flag += 1;
				}
				if (this->map_data[index][sub_index] == 1) {
					if (this->map_display[index][sub_index] == "!") {//�� �����ǵ���
						this->map_display[index][sub_index] = "v";//v ��������ȷ����
					}
					else
						this->map_display[index][sub_index] = "X";//X����δ��ǵ���
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
		}//�ж����п�ɨ��ķ��������Ƿ��Ѿ���ɨ����ɡ���������������ɨ�裨�����Ѿ���ȫ��������Ϊɨ�׳ɹ�
		if (flag == 0) {
			return 1;
		}
		return 0;
	}
	void flag(int x, int y) {
		this->map_display[x][y] = "!";//�����������
	}
	
};
