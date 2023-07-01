#include <iostream>
#include <ctime>

class board {
public:
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
		if (a < r && b < col && a >= 0 && b >= 0)
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
	~board() {
		for (int i = 0; i < r; i++)
		{
			delete[] Board[i];
		}
		delete[] Board;
	}
};


bool start() {
	char choice = '.';
	bool result{};
	std::cout << "Welcome to TicTacToe game!" << std::endl;
	std::cout << "How to play: enter cordinates which you would like to change to X or O" << std::endl;
	std::cout << "Game: game ends when a line or column or diagonalis X or O, or there isn't any free field" << std::endl;
	std::cout << "Rules: not allowed to use field more than 1 time" << std::endl;
	while (choice != 'O' && choice != 'X')
	{
		std::cout << "Choose: X or O" << std::endl;
		std::cin >> choice;
		if (choice == 'X')
		{
			result = true;
		}
		else if (choice == 'O') {
			result = false;
		}
	} 
	std::cout << "<------------------------------------------- GOOD LUCK ------------------------------------------->" << std::endl;
	std::cout << std::endl;
	return result;
}

bool minimaxWin(board& obj, char c) {
	for (int i = 0; i < obj.r; i++) //horizontal
	{
		if (obj.Board[i][0] == c && obj.Board[i][1] == c && obj.Board[i][2] == '.' )
		{
			obj.Board[i][2] = c;
			return true;
		}
		else if (obj.Board[i][0] == c && obj.Board[i][2] == c && obj.Board[i][1] == '.' ) {
			obj.Board[i][1] = c;
			return true;
		}
		else if (obj.Board[i][1] == c && obj.Board[i][2] == c && obj.Board[i][0] == '.') {
			obj.Board[i][0] = c;
			return true;
		}
	}
	for (int i = 0; i < obj.r; i++) //vertical
	{
		if (obj.Board[0][i] == c && obj.Board[1][i] == c && obj.Board[2][i] == '.')
		{
			obj.Board[2][i] = c;
			return true;
		}
		else if (obj.Board[0][i] == c && obj.Board[2][i] == c && obj.Board[1][i] == '.') {
			obj.Board[1][i] = c;
			return true;
		}
		else if (obj.Board[1][i] == c && obj.Board[2][i] == c && obj.Board[0][i] == '.') {
			obj.Board[0][i] = c;
			return true;
		}
	}
	if (obj.Board[0][0] == c && obj.Board[1][1] == c && obj.Board[2][2] == '.')
	{
		obj.Board[2][2] = c;
		return true;
	}
	else if (obj.Board[1][1] == c && obj.Board[2][2] == c && obj.Board[0][0] == '.') {
		obj.Board[0][0] = c;
		return true;
	}
	else if (obj.Board[0][0] == c && obj.Board[2][2] == c && obj.Board[1][1] == '.') {
		obj.Board[1][1] = c;
		return true;
	}

	if (obj.Board[2][0] == c && obj.Board[0][2] == c && obj.Board[1][1] == '.')
	{
		obj.Board[1][1] = c;
		return true;
	}
	else if (obj.Board[1][1] == c && obj.Board[2][0] == c && obj.Board[0][2] == '.') {
		obj.Board[0][2] = c;
		return true;
	}
	else if (obj.Board[1][1] == c && obj.Board[0][2] == c && obj.Board[2][0] == '.') {
		obj.Board[2][0] = c;
		return true;
	}

	return false;
}

bool minimaxCounter(board& obj, char c, char op) {
	for (int i = 0; i < obj.r; i++) //horizontal
	{

		if (obj.Board[i][0] == c && obj.Board[i][1] == c && obj.Board[i][2] == '.')
		{
			obj.Board[i][2] = op;
			return true;
		}
		else if (obj.Board[i][0] == c && obj.Board[i][2] == c && obj.Board[i][1] == '.') {
			obj.Board[i][1] = op;
			return true;
		}
		else if (obj.Board[i][1] == c && obj.Board[i][2] == c && obj.Board[i][0] == '.') {
			obj.Board[i][0] = op;
			return true;
		}
	}
	for (int i = 0; i < obj.r; i++) //vertical
	{

		if (obj.Board[0][i] == c && obj.Board[1][i] == c && obj.Board[2][i] == '.')
		{
			obj.Board[2][i] = op;
			return true;
		}
		else if (obj.Board[0][i] == c && obj.Board[2][i] == c && obj.Board[1][i] == '.') {
			obj.Board[1][i] = op;
			return true;
		}
		else if (obj.Board[1][i] == c && obj.Board[2][i] == c && obj.Board[0][i] == '.') {
			obj.Board[0][i] = op;
			return true;
		}
	}

	if (obj.Board[0][0] == c && obj.Board[1][1] == c && obj.Board[2][2] == '.')
	{
		obj.Board[2][2] = op;
		return true;
	}
	else if (obj.Board[1][1] == c && obj.Board[2][2] == c && obj.Board[0][0] == '.') {
		obj.Board[0][0] = op;
		return true;
	}
	else if (obj.Board[0][0] == c && obj.Board[2][2] == c && obj.Board[1][1] == '.') {
		obj.Board[1][1] = op;
		return true;
	}

	if (obj.Board[2][0] == c && obj.Board[0][2] == c && obj.Board[1][1] == '.')
	{
		obj.Board[1][1] = op;
		return true;
	}
	else if (obj.Board[1][1] == c && obj.Board[2][0] == c && obj.Board[0][2] == '.') {
		obj.Board[0][2] = op;
		return true;
	}
	else if (obj.Board[1][1] == c && obj.Board[0][2] == c && obj.Board[2][0] == '.') {
		obj.Board[2][0] = op;
		return true;
	}

	return false;
}



int main(){
	srand(time(0));
	board B;
	char c,op;
	int x, y;
	int count;
	int turn = 1;
	int free = 9;
	if (start())
	{
		count = 1;
	}
	else {
		count = 2;
	}
	while (B.check())
	{
		if (turn % 2 == 1)
		{
			c = 'X';
			op = 'O';
		}
		else {
			c = 'O';
			op = 'X';
		}
		B.print();
		std::cout << std::endl;
		x = 5;
		y = 5;
			
		if (count % 2 == 1)
		{
			while (!B(x - 1, y - 1, c))
			{
				std::cout << c << ": ";
				std::cin >> x >> y;
				std::cout << std::endl;
			}
		}
		else {
			if (!minimaxWin(B, c))
			{
				if (!minimaxCounter(B,op,c)) {
					if (free != 1)
					{
						while (!B(x - 1, y - 1, c))
						{
							x = rand() % 3;
							y = rand() % 3;
						}
					}
					else {
						for (int i = 0; i < B.r; i++)
						{
							for (int j = 0; j < B.col; j++)
							{
								if (B.Board[i][j] == '.')
								{
									B.Board[i][j] = c;
								}
							}
						}
					}
				}
			}
		}
		free--;
		count++;
		turn++;
	}
	return 0;
}
