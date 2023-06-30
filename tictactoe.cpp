#include <iostream>

class board {
private:
	int r = 3;
	int col = 3;
	char** Board;

	void init() {
		Board = new char* [r];
		for (int i = 0; i < r; i++)
		{
			Board[i] = new char[col];
		}
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < col; j++)
			{
				Board[i][j] = '.';
			}
		}
	}
public:
	board() {
		init();
	}
	
	void print() {
		std::cout << "  1 2 3" << std::endl;
		for (int i = 0; i < r; i++)
		{
			std::cout << i + 1 <<' ';
			for (int j = 0; j < col; j++)
			{
				std::cout << Board[i][j] << ' ';
			}
			std::cout << std::endl;
		}
	}

	bool operator () (int a,int b, char c) {
		if (a <= r && b <= col)
		{
			if (Board[a][b] ==  '.')
			{
				Board[a][b] = c;
				return true;
			}
			return false;
		}
		return false;
	}
	bool check() {
		for (int i = 0; i < r; i++)
		{
			if (Board[i][0] == Board[i][1] && Board[i][0] == Board[i][2] && Board[i][0] != '.')
			{
				print();
				std::cout << Board[i][0] << " wins" << std::endl;
				return false;
			}
			else if (Board[0][i] == Board[1][i] && Board[0][i] == Board[2][i] && Board[0][i] != '.') {
				print();
				std::cout << Board[0][i] << " wins" << std::endl;
				return false;
			}
		}
		if (Board[0][0] == Board[1][1] && Board[0][0] == Board[2][2] && Board[1][1] != '.')
		{
			print();
			std::cout << Board[2][2] << " wins" << std::endl;
			return false;
		}
		else if (Board[2][0] == Board[1][1] && Board[2][0] == Board[0][2] && Board[2][0] != '.') {
			print();
			std::cout << Board[2][0] << " wins" << std::endl;
			return false;
		}
		int count = 0;
		for (int i = 0; i < r; i++)
		{
			for (int j = 0; j < col; j++)
			{
				if (Board[i][j] == '.')
				{
					count++;
				}
			}
		}
		if (count == 0)
		{
			print();
			std::cout << "Draw" << std::endl;
			return false;
		}
		return true;
	}
};

void start() {
	std::cout << "Welcome to TicTacToe game!" << std::endl;
	std::cout << "How to play: enter cordinates which you would like to change to X or O" << std::endl;
	std::cout << "Game: game ends when a line or column or diagonalis X or O, or there isn't any free field" << std::endl;
	std::cout << "Rules: not allowed to use field more than 1 time" << std::endl;
	std::cout << "<------------------------------------------- GOOD LUCK ------------------------------------------->" << std::endl;
	std::cout << std::endl;
}

int main(){
	board B;
	int count = 1;
	char c;
	int x, y;
	start();
	while (B.check())
	{
		if (count % 2 == 1)
		{
			c = 'X';
		}
		else {
			c = 'O';
		}
		B.print();
		x = 5, y = 5;
		while (!B(x - 1, y - 1, c))
		{
			std::cout << c << ": ";
			std::cin >> x >> y;
			std::cout << std::endl;
		}
		count++;
	}
	return 0;
}