#include<iostream>
#include<string>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int ROW = 3;
const int COL = 3;
const int STEP = 6;

//先手1 后手-1
short Board[ROW][COL] = { 0 };
int Win[ROW][COL] = { 0 };
short SetBoard(int x, int y, short player) {
	int old = Board[x][y];
	Board[x][y] = player;
	return old;
}

void ResetBoard() {
	memset(Board, 0, sizeof Board);
}

short GetRowValue(short Board[ROW][COL], int row)
{
	short sum = 0;
	for (int j = 0; j < COL; j++) {
		sum += Board[row][j];
	}
	return sum;
}
short GetColValue(short Board[ROW][COL], int col)
{
	short sum = 0;
	for (int i = 0; i < ROW; i++) {
		sum += Board[i][col];
	}
	return sum;
}
short GetDiagonalValue(short Board[ROW][COL], bool dir)
{
	short sum = 0;
	if (dir) {
		for (int i = 0, j = 0; i < ROW&&j < COL; i++, j++) {
			sum += Board[i][j];
		}
	}
	else {
		for (int i = 0, j = 2; i < ROW&&j >= 0; i++, j--) {
			sum += Board[i][j];
		}
	}
	return sum;
}

bool NoEmpty() {
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			if (Board[i][j] == 0)return false;
		}
	}
	return true;
}
short WhoWin(short player) {
	short sum = 0;
	for (int i = 0; i < ROW; i++)
	{
		sum = GetRowValue(Board, i);
		if (sum == 3 && player == 1)return 1;
		else if (sum == -3 && player == -1)return -1;
	}
	sum = 0;
	for (int j = 0; j < COL; j++)
	{
		sum = GetColValue(Board, j);
		if (sum == 3 && player == 1)return 1;
		else if (sum == -3 && player == -1)return -1;
	}
	sum = 0;
	sum = GetDiagonalValue(Board, true);
	if (sum == 3 && player == 1)return 1;
	else if (sum == -3 && player == -1)return -1;
	sum = GetDiagonalValue(Board, false);
	if (sum == 3 && player == 1)return 1;
	else if (sum == -3 && player == -1)return -1;
	return 0;//平局
}

void SelectPoint(int &x, int &y, int &selectvalue) {
	static int X[] = { 0,0,2,2,0,1,1,2,1 };
	static int Y[] = { 0,2,0,2,1,0,2,1,1 };
	for (int i = 0; i < ROW*COL; i++) {
		if (Board[X[i]][Y[i]] == 0 && ((x == -1 && y == -1) || (selectvalue < Win[X[i]][Y[i]]))) {
			x = X[i];
			y = Y[i];
			selectvalue = Win[X[i]][Y[i]];
		}
	}
}

//判断该行是否安全
//返回安全级数
//3:绝对安全
//2:还算安全
//1:相当危险
int SafeRow(int row,short enemy) {
	short sum = GetRowValue(Board, row);
	short simbol = enemy > 0 ? 1 : -1;
	if (sum == 2*simbol)return 1;
	else if (sum == 1*simbol) {
		return 2;
	}
	else
		return 3;
}

int SafeCol(int col,short enemy) {
	short sum = GetColValue(Board, col);
	short simbol = enemy > 0 ? 1 : -1;
	if (sum == 2*simbol)return 1;
	else if (sum == 1*simbol) {
		return 2;
	}
	else
		return 3;
}

int SafeDiagonal(bool dir,short enemy) {
	short sum = 0;
	short simbol = enemy > 0 ? 1 : -1;
	sum = GetDiagonalValue(Board, dir);
	if (sum == 2*simbol)
		return 1;
	else if (sum == 1*simbol) {
		return 2;
	}
	else
		return 3;
}

void Battle_SelectPoint(int &x, int &y, int &value) {
	const short enemy = -1;
	const short self = 1;

	//查看自己是否有绝杀棋
	for (int i = 0; i < ROW; i++) {
		if (SafeRow(i, self) == 1) {
			x = i;
			for (int j = 0; j < COL; j++) {
				if (Board[x][j] == 0) {
					y = j;
					return;
				}
			}
		}
	}

	for (int j = 0; j < COL; j++) {
		if (SafeCol(j, self) == 1) {
			y = j;
			for (int i = 0; i < ROW; i++) {
				if (Board[i][y] == 0) {
					x = i;
					return;
				}
			}
		}
	}

	if (SafeDiagonal(true, self) == 1) {
		for (int i = 0, j = 0; i < ROW&&j < COL; i++, j++) {
			if (Board[i][j] == 0) {
				x = i;
				y = j;
				return;
			}
		}
	}
	if (SafeDiagonal(false, self) == 1) {
		for (int i = 0, j = 2; i < ROW&&j >= 0; i++, j--) {
			if (Board[i][j] == 0) {
				x = i;
				y = j;
				return;
			}
		}
	}

	//查看对手是否有绝杀棋
	for (int i = 0; i < ROW; i++) {
		if (SafeRow(i,enemy) == 1) {
			x = i;
			for (int j = 0; j < COL; j++) {
				if (Board[x][j] == 0) {
					y = j;
					return;
				}
			}
		}
	}
	for (int j = 0; j < COL; j++) {
		if (SafeCol(j, enemy) == 1) {
			y = j;
			for (int i = 0; i < ROW; i++) {
				if (Board[i][y] == 0) {
					x = i;
					return;
				}
			}
		}
	}

	if (SafeDiagonal(true,enemy) == 1) {
		for (int i = 0, j = 0; i < ROW&&j < COL; i++, j++) {
			if (Board[i][j] == 0) {
				x = i;
				y = j;
				return;
			}
		}
	}
	if (SafeDiagonal(false, enemy) == 1) {
		for (int i = 0, j = 2; i < ROW&&j >= 0; i++, j--) {
			if (Board[i][j] == 0) {
				x = i;
				y = j;
				return;
			}
		}
	}

	//按着训练结果选择下一步
	SelectPoint(x, y, value);
	return;
}

void InitLearning(int count) {
	const short first = 1;
	const short back = -1;
	int cnt = 0;
	do {
		/*system("cls");
		cout << "Current Board:" << endl;
		for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
		cout << Board[i][j] << " ";
		}
		cout << endl;
		}*/
		int ai_select_first_x = -1;
		int ai_select_first_y = -1;
		int ai_select_first_value = -2;
		Battle_SelectPoint(ai_select_first_x, ai_select_first_y, ai_select_first_value);
		SetBoard(ai_select_first_x, ai_select_first_y, first);
		int ai_select_x = -1;
		int ai_select_y = -1;
		int ai_select_value = -2;;
		Battle_SelectPoint(ai_select_x, ai_select_y, ai_select_value);
		SetBoard(ai_select_x, ai_select_y, back);
		if (WhoWin(1) == 1 || WhoWin(-1) == -1 || NoEmpty()) {
			if (WhoWin(1) == 1) {
				for (int i = 0; i < ROW; i++) {
					for (int j = 0; j < COL; j++) {
						if (Board[i][j] == first) {
							Win[i][j]++;
						}
					}
				}
			}
			else {
				for (int i = 0; i < ROW; i++) {
					for (int j = 0; j < COL; j++) {
						if (Board[i][j] == first) {
							Win[i][j]--;
						}
					}
				}
			}
			cnt++;
			ResetBoard();
		}
	} while (cnt <= count);
}

int main(void) {
	const short first = 1;
	const short back = -1;
	int x, y;
	int cnt = 0;
	//InitTraining
	InitLearning(1000000);
	//Battle
	cnt = 0;
	do {
		int ai_select_x = -1;
		int ai_select_y = -1;
		int ai_select_value = -2;
		Battle_SelectPoint(ai_select_x, ai_select_y, ai_select_value);
		SetBoard(ai_select_x, ai_select_y, first);
		system("cls");
		cout << "Current Board:" << endl;
		for (int i = 0; i < ROW; i++) {
			for (int j = 0; j < COL; j++) {
				cout << Board[i][j] << " ";
			}
			cout << endl;
		}
		if (WhoWin(1) == 1 || WhoWin(-1) == -1 || NoEmpty()) {
			if (WhoWin(-1) == -1) {
				for (int i = 0; i < ROW; i++) {
					for (int j = 0; j < COL; j++) {
						if (Board[i][j] == back)Win[i][j]++;
						if (Board[i][j] == first)Win[i][j]--;
					}
				}
			}
			system("cls");
			cout << "Current Board:" << endl;
			for (int i = 0; i < ROW; i++) {
				for (int j = 0; j < COL; j++) {
					cout << Board[i][j] << " ";
				}
				cout << endl;
			}
			system("pause");
			ResetBoard();
			continue;
			//break;
		}
		cout << "Yours:";
		cin >> x >> y;
		SetBoard(x, y, back);
	} while (true);
	system("cls");
	if (WhoWin(1) == 1)cout << "First Win" << endl;
	else if (WhoWin(-1) == -1)cout << "Back Win" << endl;
	else cout << "Draw" << endl;
	cout << "Current Board:" << endl;
	for (int i = 0; i < ROW; i++) {
		for (int j = 0; j < COL; j++) {
			cout << Board[i][j] << " ";
		}
		cout << endl;
	}
	ResetBoard();
	return 0;
}