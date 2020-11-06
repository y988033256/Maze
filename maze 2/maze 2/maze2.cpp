#include<iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int randomnumber()
{
	int i;
	i = rand() % 2;
	return i;
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

	for (int i = 0; i < length; ++i)   //  generate maze
	{
		for (int j = 0; j < width; ++j)
		{
			cout << mazewall[i][j];
		}
		cout << endl;
	}
	return mazewall;
}
void writefile(int length, int width, char** mazewall)
{
	ofstream outputfile;
	outputfile.exceptions(ifstream::badbit);
	try {
		outputfile.open("maze.txt");
		for (int i = 0; i < length; i++)
		{
			for (int j = 0; j < width; j++)
			{
				outputfile << mazewall[i][j];
			}
			outputfile << '\n';
		}
	}
	catch (const ifstream::failure& e) {
		cout << "Exception opening/reading file";
	}
	outputfile.close();
	
	
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
		
	}
	else
	{
		cout << "Couldn't open the file!" << endl;
	}
	myfile.close();
	
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




int main(){	
	int option;
	while (true) {

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
		cout << " 1) New Game " << endl;
		cout << " 2) Open the previous game" << endl;
		cout << " 3) Quit" << endl;
		cout << endl;

		cout << "Enter the option number: " << endl;
		cin >> option;
		switch (option)
		{
		case 1:

		case 2:
			readfile();
		case 3:
			exit(1);
		}
		
		int length = InputInteger(10, 50, new char[] {"Enter the length of the maze: "});
		int width = InputInteger(10, 50, new char[] {"Enter the width of the maze: "});
		int exit = InputInteger(1, 2, new char[] {"Enter the number of exits for the maze(No more than 2): "});
		int player = InputInteger(1, 2, new char[] {"Enter the number of player for the maze(No more than 2): "});
		writefile(length, width, maze(length, width, exit, player));
		cout << " _________________________________________________________________" << endl;
		
	}
}