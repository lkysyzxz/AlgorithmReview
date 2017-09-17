//#include<iostream>
//#include<string>
//#include<cstdio>
//#include<algorithm>
//#include<set>
//using namespace std;
//const int MAX_VALUE = 0x3f3f3f3f;
//const int MIN_VALUE = -0x3f3f3f3f;
//const int ROW = 3;
//const int COL = 3;
//struct POINT {
//	int x;
//	int y;
//};
//short board[ROW][COL] = { 0 };
//short GetRowValue(short Board[ROW][COL], int row)
//{
//	short sum = 0;
//	for (int j = 0; j < COL; j++) {
//		sum += Board[row][j];
//	}
//	return sum;
//}
//short GetColValue(short Board[ROW][COL], int col)
//{
//	short sum = 0;
//	for (int i = 0; i < ROW; i++) {
//		sum += Board[i][col];
//	}
//	return sum;
//}
//short GetDiagonalValue(short Board[ROW][COL], bool dir)
//{
//	short sum = 0;
//	if (dir) {
//		for (int i = 0, j = 0; i < ROW&&j < COL; i++, j++) {
//			sum += Board[i][j];
//		}
//	}
//	else {
//		for (int i = 0, j = 2; i < ROW&&j >= 0; i++, j--) {
//			sum += Board[i][j];
//		}
//	}
//	return sum;
//}
//short WhoWin(short player) {
//	short sum = 0;
//	for (int i = 0; i < ROW; i++)
//	{
//		sum = GetRowValue(board, i);
//		if (sum == 3 && player == 1)return 1;
//		else if (sum == -3 && player == -1)return -1;
//	}
//	sum = 0;
//	for (int j = 0; j < COL; j++)
//	{
//		sum = GetColValue(board, j);
//		if (sum == 3 && player == 1)return 1;
//		else if (sum == -3 && player == -1)return -1;
//	}
//	sum = 0;
//	sum = GetDiagonalValue(board, true);
//	if (sum == 3 && player == 1)return 1;
//	else if (sum == -3 && player == -1)return -1;
//	sum = GetDiagonalValue(board, false);
//	if (sum == 3 && player == 1)return 1;
//	else if (sum == -3 && player == -1)return -1;
//	return 0;//平局
//}
//
//short CopyBoard[ROW][COL];
//int HowWin(int player) {
//	for (int i = 0; i < ROW; i++) {
//		for (int j = 0; j < COL; j++) {
//			CopyBoard[i][j] = board[i][j];
//		}
//	}
//	int sum = 0;
//	int res = 0;
//	int zerocnt = 0;
//	for (int i = 0; i < ROW; i++) {
//		sum = GetRowValue(CopyBoard, i);
//		if (player == -1 && sum <= 0)sum = abs(sum);
//		else if (player == -1 && sum >= 0)continue;
//		switch (sum)
//		{
//		case 1:
//			zerocnt = 0;
//			for (int j = 0; j < COL; j++) {
//				if (CopyBoard[i][j] == 0)zerocnt++;
//			}
//			if (zerocnt == 2)res++;
//			break;
//		case 2:
//			res++;
//			break;
//		case 3:
//			res++;
//			break;
//		}
//	}
//	for (int j = 0; j < COL; j++) {
//		sum = GetColValue(CopyBoard, j);
//		if (player == -1 && sum <= 0)sum = abs(sum);
//		else if (player == -1 && sum >= 0)continue;
//		switch (sum)
//		{
//		case 1:
//			zerocnt = 0;
//			for (int i = 0; i < COL; i++) {
//				if (CopyBoard[i][j] == 0)zerocnt++;
//			}
//			if (zerocnt == 2)res++;
//			break;
//		case 2:
//			res++;
//			break;
//		case 3:
//			res++;
//			break;
//		}
//	}
//
//	sum = GetDiagonalValue(CopyBoard, true);
//	if (player == -1 && sum <= 0) {
//		sum = abs(sum);
//
//		switch (sum)
//		{
//		case 1:
//			zerocnt = 0;
//			for (int i = 0, j = 0; i < ROW; i++, j++) {
//				if (CopyBoard[i][j] == 0)zerocnt++;
//			}
//			if (zerocnt == 2)res++;
//			break;
//		case 2:
//			res++;
//			break;
//		case 3:
//			res++;
//			break;
//		}
//	}
//	sum = GetDiagonalValue(CopyBoard, false);
//	if (player == -1 && sum <= 0) {
//		sum = abs(sum);
//		switch (sum)
//		{
//		case 1:
//			zerocnt = 0;
//			for (int i = 0, j = 0; i < ROW; i++, j++) {
//				if (CopyBoard[i][j] == 0)zerocnt++;
//			}
//			if (zerocnt == 2)res++;
//			break;
//		case 2:
//			res++;
//			break;
//		case 3:
//			res++;
//			break;
//		}
//	}
//	return res;
//}
//
//int Evaluate() {
//	if (WhoWin(1) == 1)
//		return MAX_VALUE;
//	else if (WhoWin(-1) == -1)
//		return MIN_VALUE;
//	else {
//		int me = HowWin(1);
//		int enemy = HowWin(-1);
//		return(me - enemy);
//	}
//}
//
//POINT GetEmpty()
//{
//	for (int i = 0; i < ROW; i++) {
//		for (int j = 0; j < COL; j++) {
//			if (board[i][j] == 0)
//			{
//				return POINT{ i,j };
//			}
//		}
//	}
//	return POINT{ -1,-1 };
//}
//
//int GetEmptyCnt()
//{
//	int cnt = 0;
//	for (int i = 0; i < ROW; i++) {
//		for (int j = 0; j < COL; j++) {
//			if (board[i][j] == 0)cnt++;
//		}
//	}
//	return cnt;
//}
//
//int BoardValue[ROW][COL] = { 0 };
//int MIN_MAX_Search(int deep, int X, int Y, bool maxFlag, int player)
//{
//	int old = board[X][Y];
//
//	if (!deep)
//	{
//		board[X][Y] = player;
//		int value = Evaluate();
//		board[X][Y] = old;
//		return value;
//	}
//	int value = MIN_VALUE;
//	int res = MIN_VALUE;
//	if (maxFlag)
//	{
//		value = MIN_VALUE;
//		res = MIN_VALUE;
//		board[X][Y] = player;
//		for (int i = 0; i < ROW; i++) {
//			for (int j = 0; j < COL; j++) {
//				if (board[i][j] == 0) {
//					res = MIN_MAX_Search(deep - 1, i, j, !maxFlag, -player);
//					value = max(value, res);
//				}
//			}
//		}
//		board[X][Y] = old;
//	}
//	else if (!maxFlag)
//	{
//		value = MAX_VALUE;
//		res = MAX_VALUE;
//		board[X][Y] = player;
//		for (int i = 0; i < ROW; i++) {
//			for (int j = 0; j < COL; j++) {
//				if (board[i][j] == 0) {
//					res = MIN_MAX_Search(deep - 1, i, j, !maxFlag, -player);
//					value = min(res, value);
//				}
//			}
//		}
//		board[X][Y] = old;
//	}
//	return value;
//}
//
//
//
//int main()
//{
//	//board[0][0] = 1;
//	//board[0][2] = -1;
//	bool first = true;
//START:
//	system("cls");
//	cout << "当前棋盘" << endl;
//	for (int i = 0; i < ROW; i++) {
//		for (int j = 0; j < COL; j++) {
//			cout << board[i][j] << " ";
//		}
//		cout << endl;
//	}
//	POINT selectedPoint;
//	int value = MIN_VALUE;
//	//memset(BoardValue, 0, sizeof BoardValue);
//	if (first) {
//		selectedPoint.x = 0;
//		selectedPoint.y = 0;
//		first = false;
//	}
//	else
//	{
//		for (int i = 0; i < ROW; i++) {
//			for (int j = 0; j < COL; j++) {
//				if (board[i][j] == 0) {
//					POINT currentPoint = POINT{ i,j };
//
//					{
//						//查看这一步是否能取得胜利
//						board[i][j] = 1;
//						if (WhoWin(1) == 1) {
//							value = MAX_VALUE;
//							selectedPoint = currentPoint;
//							board[i][j] = 0;
//							break;
//						}
//						board[i][j] = 0;
//					}
//					int empCnt = GetEmptyCnt();
//					int deep;
//					if ((empCnt / 2) % 2 == 0)deep = empCnt / 2 + 1;
//					else deep = empCnt / 2;
//					
//					int res = MIN_MAX_Search(deep , i, j, true, 1);
//					if (res > value) {
//						selectedPoint = currentPoint;
//						value = res;
//					}
//				}
//			}
//			if (value == MAX_VALUE)
//				break;
//		}
//	}
//	board[selectedPoint.x][selectedPoint.y] = 1;
//	cout << "黑:(" << selectedPoint.x << "," << selectedPoint.y << ")" << endl;
//	if (WhoWin(1) == 1)
//	{
//		cout << "黑棋胜" << endl;
//		goto END;
//	}
//	if (GetEmpty().x == -1)
//		goto END;
//	cout << "你的落子:";
//	int x, y;
//	cin >> x >> y;
//	board[x][y] = -1;
//	if (WhoWin(-1) == -1)
//	{
//		cout << "白棋胜" << endl;
//		goto END;
//	}
//	if (GetEmpty().x != -1)
//		goto START;
//END:
//	system("cls");
//	cout << "当前棋盘" << endl;
//	for (int i = 0; i < ROW; i++) {
//		for (int j = 0; j < COL; j++) {
//			cout << board[i][j] << " ";
//		}
//		cout << endl;
//	}
//	cout << "---------------------\n";
//	cout << "棋盘分数" << endl;
//	for (int i = 0; i < ROW; i++) {
//		for (int j = 0; j < COL; j++) {
//			cout << BoardValue[i][j] << " ";
//		}
//		cout << endl;
//	}
//	return 0;
//}