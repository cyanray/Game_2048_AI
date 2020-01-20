#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <iomanip>
#include <math.h>
#include <algorithm>
#include <cstring>
using namespace std;

int __max_num = 0;
int __max_score = 0;
int __board[4][4] = { 0 };

void random()
{
	const static int size[] = { 2,2,2,2,2,2,2,2,2,4 };	// 2和4出现的概率分别是0.9和0.1
	int n = size[rand() % 10];
	while (true)
	{
		int x = rand() % 4;
		int y = rand() % 4;
		if (__board[x][y] == 0)
		{
			__board[x][y] = n;
			return;
		}
	}
}

int up(int board[4][4] = __board)
{
	int step_count = 0;
	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (board[x][y] == 0)
			{
				for (int t = y + 1; t < 4; t++)
				{
					if (board[x][t] != 0)
					{
						board[x][y] = board[x][t];
						board[x][t] = 0;
						++step_count;
						break;
					}
				}
			}
		}
	}

	for (int y = 0; y < 3; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (board[x][y] == 0)
			{
				board[x][y] = board[x][y + 1];
				board[x][y + 1] = 0;
				continue;
			}
			if (board[x][y] == board[x][y + 1])
			{
				board[x][y] *= 2;
				for (int ty = y + 1; ty < 3; ty++)
				{
					board[x][ty] = board[x][ty + 1];
				}
				board[x][3] = 0;
				++step_count;
				continue;
			}
		}
	}
	return step_count;
}

int down(int board[4][4] = __board)
{
	int step_count = 0;
	for (int y = 3; y >= 1; y--)
	{
		for (int x = 0; x < 4; x++)
		{
			if (board[x][y] == 0)
			{
				for (int t = y - 1; t >= 0; t--)
				{
					if (board[x][t] != 0)
					{
						board[x][y] = board[x][t];
						board[x][t] = 0;
						++step_count;
						break;
					}
				}
			}
		}
	}

	for (int y = 3; y >= 1; y--)
	{
		for (int x = 0; x < 4; x++)
		{
			if (board[x][y] == 0)
			{
				board[x][y] = board[x][y - 1];
				board[x][y - 1] = 0;
				continue;
			}
			if (board[x][y] == board[x][y - 1])
			{
				board[x][y] *= 2;
				for (int ty = y - 1; ty > 0; ty--)
				{
					board[x][ty] = board[x][ty - 1];
				}
				board[x][0] = 0;
				++step_count;
				continue;
			}
		}
	}
	return step_count;
}

int left(int board[4][4] = __board)
{
	int step_count = 0;
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			if (board[x][y] == 0)
			{
				for (int t = x + 1; t < 4; t++)
				{
					if (board[t][y] != 0)
					{
						board[x][y] = board[t][y];
						board[t][y] = 0;
						++step_count;
						break;
					}
				}
			}
		}
	}

	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			if (board[x][y] == 0)
			{
				board[x][y] = board[x + 1][y];
				board[x + 1][y] = 0;
				continue;
			}
			if (board[x][y] == board[x + 1][y])
			{
				board[x][y] *= 2;
				for (int tx = x + 1; tx < 3; tx++)
				{
					board[tx][y] = board[tx + 1][y];
				}
				board[3][y] = 0;
				++step_count;
				continue;
			}
		}
	}
	return step_count;
}

int right(int board[4][4] = __board)
{
	int step_count = 0;
	for (int x = 3; x >= 1; x--)
	{
		for (int y = 0; y < 4; y++)
		{
			if (board[x][y] == 0)
			{
				for (int t = x - 1; t >= 0; t--)
				{
					if (board[t][y] != 0)
					{
						board[x][y] = board[t][y];
						board[t][y] = 0;
						++step_count;
						break;
					}
				}
			}
		}
	}

	for (int x = 3; x >= 1; x--)
	{
		for (int y = 0; y < 4; y++)
		{
			if (board[x][y] == 0)
			{
				board[x][y] = board[x - 1][y];
				board[x - 1][y] = 0;
				continue;
			}
			if (board[x][y] == board[x - 1][y])
			{
				board[x][y] *= 2;
				for (int tx = x - 1; tx > 0; tx--)
				{
					board[tx][y] = board[tx - 1][y];
				}
				board[0][y] = 0;
				++step_count;
				continue;
			}
		}
	}
	return step_count;
}

int game_score(int board[4][4] = __board)
{
	int score = 0;
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			score += board[x][y];
		}
	}
	return score;
}


void display()
{
	system("CLS");
	int tScore = game_score();
	cout << "最大数值：" << __max_num << endl;
	cout << "最高得分：" << __max_score << endl;
	cout << "本局得分：" << tScore << endl;
	__max_score = max(__max_score, tScore);
	for (int y = 0; y < 4; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			setw(10);
			cout.setf(ios::right);
			cout << __board[x][y] << "\t";
			__max_num = max(__max_num, __board[x][y]);
		}
		cout << endl;
	}
}

void game_init()
{
	memset(__board, 0, sizeof(__board));
	srand(time(0));
	random();
	display();
}

bool game_over() {
	bool is_game_over = true;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			if (__board[i][j] == 0 || __board[i][j + 1] == 0 || __board[i][j] == __board[i][j + 1]) {
				is_game_over = false;
				break;
			}
		}
	}
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 3; i++) {
			if (__board[i][j] == 0 || __board[i + 1][j] == 0 || __board[i][j] == __board[i + 1][j]) {
				is_game_over = false;
				break;
			}
		}
	}
	return is_game_over;
}


double game_AI_score(int board[4][4])
{
	double result = 0;

	// 鼓励相同的数字在同一行（有助于尽早合并）
	for (int y = 0; y < 4; y++)
	{
		int maxt = 0, t = 0, i = 0;
		for (int x = 0; x < 4 - 1; x++)
		{
			i = x + 1;
			while (board[i++][y] == board[x][y]) ++t;
			maxt = max(maxt, t);
			x += t;
		}
		result += 1.0e2 * t;
	}


	// 打分权重，各个位置的打分权重不同才能使得大数字集中在一起
	const int weight[4][4] =
	{
		{255,127,63,63},
		{11,17,15,19},
		{0,0,0,0},
		{-3,-5,-7,-9}
	};

	double w_score = 0;
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			w_score += 1.0 * board[x][y] * weight[x][y];
		}
	}
	result += w_score;

	// 如果能让更多的空位出现，那么提供一定优势分数
	int zero_count = 0;
	for (int x = 0; x < 4; x++)
	{
		for (int y = 0; y < 4; y++)
		{
			if (board[x][y] == 0) ++zero_count;
		}
	}

	result += 100.0 * zero_count;
	return result;
}


char game_AI()
{
	const static char cmds[] = { 'w','a','s','d' };
	int cmd_best = 0;
	double score_max = 0;
	for (int i = 0; i < 4; i++)
	{
		int tboard[4][4];
		memcpy(tboard, __board, sizeof(tboard));
		int step_count = 1;
		double tScore = 0;
		switch (cmds[i])
		{
		case 'w':step_count = up(tboard); break;
		case 'a':step_count = left(tboard); break;
		case 's':step_count = down(tboard); break;
		case 'd':step_count = right(tboard); break;
		}
		// 这次移动不会有变化，跳过
		if (step_count == 0) continue;

		// 对移动后的局势评分
		tScore += game_AI_score(tboard);
		// 尽量多的合并/移动数字，可以提供优势
		tScore += step_count;

		if (tScore > score_max)
		{
			score_max = tScore;
			cmd_best = i;
		}

	}
	return cmds[cmd_best];
}


int main()
{

	ios::sync_with_stdio(false); cin.tie(0); cout.tie(0);

	game_init();
	while (true)
	{
		char cmd;
		//cin >> cmd;
		cmd = game_AI();

		int step_count = 1;
		switch (cmd)
		{
		case 'w':step_count = up(); break;
		case 'a':step_count = left(); break;
		case 's':step_count = down(); break;
		case 'd':step_count = right(); break;
		}

		if (step_count != 0)
		{
			random();
			display();
		}
		else
		{
			if (!game_over()) continue;
			cout << "游戏结束!" << endl;
			system("pause");
			game_init();
		}
	}
	return 0;
}