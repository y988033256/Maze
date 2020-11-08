#include<iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <vector>
//#include <windows.h>


using namespace std;

vector<char**> record;

void sleep() 
{
	for (long i = 0; i < 500000000; i++)     
	{
		;
	}
}
int randomnumber()
{
	return (rand() % 2);
}
char** maze(int length, int width, int exit, int player)
{
	char** mazewall = new char* [length];    /// ÒªÉ¾³ý£¡£¡£¡
	for (int i = 0; i < length; ++i)
		mazewall[i] = new char[width];
	for (int i = 0; i < length; i++)      // mazewall 
	{
		for (int j = 0; j < width; j++) {
			mazewall[i][j] = 'X';
		}
	}
	for (int i = 1; i < length - 1; i++) // random mazewall 
	{
		for (int j = 1; j < width - 1; j++) {
			int number = randomnumber();
			if (number == 1)
			{
				mazewall[i][j] = ' ';
			}
			else
			{
				mazewall[i][j] = 'X';
			}
		}
	}
	for (int i = 0; i < exit; i++) {   // exit e 
		mazewall[0][i + 1] = 'E';
	}

	mazewall[length / 2][width / 2] = 'F';      //   centre F
	mazewall[length / 2 + 1][width / 2 + 1] = ' ';   //    3x3 centre space 
	mazewall[length / 2 - 1][width / 2 - 1] = ' ';   //    3x3 centre space 
	mazewall[length / 2][width / 2 + 1] = ' ';   //    3x3 centre space 
	mazewall[length / 2][width / 2 - 1] = ' ';   //    3x3 centre space 
	mazewall[length / 2 + 1][width / 2] = ' ';   //    3x3 centre space 
	mazewall[length / 2 - 1][width / 2] = ' ';   //    3x3 centre space 
	mazewall[length / 2 + 1][width / 2 - 1] = ' ';   //    3x3 centre space 
	mazewall[length / 2 - 1][width / 2 + 1] = ' ';   //    3x3 centre space 

	 

	for (int i = 1; i < length / 2; i++) {   // vertical roads
		mazewall[i][1] = ' ';
		mazewall[i][width / 2] = ' ';
	}
	for (int i = 1; i < width / 2; i++) {   // horizontal roads	
		mazewall[1][i] = ' ';
		mazewall[length / 2][i] = ' ';
	}
	
	for (int i = 0; i < player; i++) {   // player 
		mazewall[1][i + 1] = 'P';
	}
	return mazewall;
}

void showMazeWall(char** mazewall, int length, int width)
{
	for (int i = 0; i < length; ++i)   //  generate maze
	{
		for (int j = 0; j < width; ++j)
		{
			cout << mazewall[i][j];
		}
		cout << endl;
	}
}

void showMazewalls(vector<char**> li, int length, int width)
{
	for (int y = 0; y < length; y++)
	{
		for (int i = 0; i < li.size(); i++) {
			char* row = li[i][y];
			row[width] = 0;
			cout << row << '\t';
		}
		cout << endl;
	}
}

void readfile()
{
	char* mazewall;

	ifstream myfile("maze.txt");//, std::ios::binary | std::ios::in);

	if (myfile.is_open())
	{
		
		cout << endl;
		myfile.seekg(0, std::ios::end);
		int len = myfile.tellg();
		myfile.seekg(0, std::ios::beg);
		mazewall = new char[len];
		myfile.read(mazewall, len);
		int i = 0;
		for (; i < len; i++)
			if (mazewall[i] < 0)
				break;
		mazewall[i] = 0;
		cout << mazewall;
		delete[]mazewall;
		cout << endl;
		cout << "Read file completed" << endl;
		cout << "" << endl;
		myfile.close();
	}
	else
	{
		cout << "Couldn't open the file!" << endl;
	}
}

int InputInteger(int min, int max, char* warning)
{
	int inputNumber;
	do
	{
		cout << endl;
		cout << warning << endl;
		cin >> inputNumber;
		if (!cin.fail() && inputNumber >= min && inputNumber <= max)
			break;
		cout << endl;
		cout << "Please enter a valid integer in Range (" << min << " - " << max << "): " << endl;
		cin.clear(); // clear the cin flag bit
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear cin stream
	} while (1);
	return inputNumber;
}

char** mazeCopy(char** mazewall, int length, int width)
{
	char** new_mazewall = new char* [length];
	for (int i = 0; i < length; ++i)
		new_mazewall[i] = new char[width];

	for (int i = 0; i < length; i++)      // mazewall 
	{
		for (int j = 0; j < width; j++)
			new_mazewall[i][j] = mazewall[i][j];
	}

	return(new_mazewall);
}

void saveRecord(int length, int width)
{
	char** mazewall;
	ofstream outputfile;
	outputfile.exceptions(ifstream::badbit);
	try {
		outputfile.open("maze.txt");
		int len = record.size();

		for (int l = 0; l < len; l++)
		{
			mazewall = record[l];
			for (int i = 0; i < length; i++)
			{
				for (int j = 0; j < width; j++)
					outputfile << mazewall[i][j];
				outputfile << endl;
			}

			outputfile << endl;
		}
	}
	catch (const ifstream::failure& e) {
		cout << "Exception opening/reading file";
	}
	outputfile.close();
}

void play() 
{
	if (record.size())
		record.clear();
	int length = InputInteger(10, 50, new char[] {"Enter the length of the maze: "});
	int width = InputInteger(10, 50, new char[] {"Enter the width of the maze: "});
	int exit = InputInteger(1, 2, new char[] {"Enter the number of exits for the maze(No more than 2): "});
	int player = InputInteger(1, 2, new char[] {"Enter the number of player for the maze(No more than 2): "});
	int numberofmaze = InputInteger(1, 5, new char[] {"Enter the number of maze you want to generate(No more than 5): "});
	vector<char**> li;
	
	for (int i = 0; i < numberofmaze; i++)
		li.push_back(maze(length, width, exit, player));

	showMazewalls(li, length, width);

	int Choice = InputInteger(1, numberofmaze, new char[] {"Enter your Choice of the maze: "});
	char** mazewall = li[Choice - 1];
	showMazeWall(mazewall, length, width);
	
	vector<char*> p1path;

	for (char i = 1; i < length / 2; i++)    // vertical roads
		p1path.push_back(new char[] {i, 1});

	for (char i = 1; i < width / 2; i++)    // horizontal roads	
		p1path.push_back(new char[] {char(length / 2), i});

	vector<char*> p2path;
	for (char i = 1; i < width / 2; i++) {   // horizontal roads	
		p2path.push_back(new char[] {1, i});
	}
	for (char i = 1; i < length / 2; i++) {   // vertical roads
		p2path.push_back(new char[] {i, char(width / 2)});
	}

	showMazeWall(mazewall, length, width);

	char P1X = 1;
	char P1Y = 1;
	char P2X = 1;
	char P2Y = 2;
	cout << endl;
	cout << "Go!!!" << endl;
	cout << endl;
	bool exitflag = false;

	int p1 = p1path.size();
	int p2 = p2path.size();
	int bs = p1 > p2 ? p1 : p2;

	sleep();
	for (int i = 1; i < bs; i++)
	{
		if (i < p1)  // p1 self movement 
		{
			cout << endl;
			mazewall[P1Y][P1X] = ' ';
			P1X = p1path[i][1];
			P1Y = p1path[i][0];
			mazewall[P1Y][P1X] = 'P';
			record.push_back(mazeCopy(mazewall, length, width));
			showMazeWall(record.back(), length, width);
			sleep();
		}
		if (player == 2) // p2 self movement 
		{		
			if (i < p2)
			{
				cout << endl;
				mazewall[P2Y][P2X] = ' ';
				P2X = p2path[i][1];
				P2Y = p2path[i][0];
				mazewall[P2Y][P2X] = 'P';
				record.push_back(mazeCopy(mazewall, length, width));
				showMazeWall(record.back(), length, width);
				sleep();
			}
		}
	}
	cout << endl;
	saveRecord(length, width);
	cout << "File saved" << endl;	
	cout << endl;
}

int main(){	
	   
		srand((unsigned)time(NULL));
		cout << " **************************************************************** " << endl;
		cout << " **************************************************************** " << endl;
		cout << " **                                                            ** " << endl;
		cout << " **                                                            ** " << endl;
		cout << " **                                                            ** " << endl;
		cout << " **                          THE MAZE                          ** " << endl;
		cout << " **                                                            ** " << endl;
		cout << " **                                                            ** " << endl;
		cout << " **                                                            ** " << endl;
		cout << " **************************************************************** " << endl;
		cout << " **************************************************************** " << endl;
		cout << endl;
		cout << " _________________________________________________________________" << endl;
		cout << endl;
		
		while (true) {
			char option[10];
			cout << " 1) New Game " << endl;
			cout << " 2) Open the previous game" << endl;
			cout << " 3) Quit" << endl;
			cout << endl;
			cout << "Enter the option number: " << endl;
			cin >> option;
			switch (option[0])
			{
			case '1':
				play();
				break;
			case '2':
				readfile();
				break;
			case '3':
				exit(1);
			default:
				cout << "Please enter a valid integer in Range (1 - 3)" << endl;
			}
		}
}