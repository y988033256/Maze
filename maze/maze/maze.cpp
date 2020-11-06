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

char** maze(int length, int width, int exit)
{
	char** mazewall = new char* [length];
	for (int i = 0; i < length; ++i)
		mazewall[i] = new char[width];
	for (int i = 0; i < length; i++) 
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
	for (int i = 1; i < length / 2; i++) {   // vertical roads
		mazewall[i][1] = 'o';
		mazewall[i][width / 2] = 'o';
	}
	for (int i = 1; i < width / 2; i++) {   // horizontal roads	
		mazewall[1][i] = 'o';
		mazewall[length / 2][i] = 'o';
	}

	mazewall[length / 2][width / 2] = 'S';      //   centre S
	mazewall[length / 2 + 1][width / 2 + 1] = ' ';   //    3x3 centre space 
	mazewall[length / 2 - 1][width / 2 - 1] = ' ';   //    3x3 centre space 
	mazewall[length / 2][width / 2 + 1] = ' ';   //    3x3 centre space 
	mazewall[length / 2][width / 2 - 1] = 'o';
	mazewall[length / 2 + 1][width / 2] = ' ';   //    3x3 centre space 
	mazewall[length / 2 - 1][width / 2] = 'o';
	mazewall[length / 2 + 1][width / 2 - 1] = ' ';   //    3x3 centre space 
	mazewall[length / 2 - 1][width / 2 + 1] = ' ';   //    3x3 centre space 

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
		cout << "Read file completed" << endl;
		cout << endl;
		myfile.seekg(0, std::ios::end);
		int len = myfile.tellg();
		myfile.seekg(0, std::ios::beg);
		mazewall = new char[len];
		myfile.read(mazewall, len);
		mazewall[len-1]= '\0';
		cout << mazewall;
		delete[]mazewall;
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
		
		cout <<  warning << endl;
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

int main() 
{	
	srand((unsigned)time(NULL));
	int length = InputInteger(10, 50, new char[] {"Enter the length of the maze: "});
	int width = InputInteger(10, 50, new char[] {"Enter the width of the maze: "});
	int exit = InputInteger(1, 2, new char[] {"Enter the number of exits for the maze(No more than 2): "});	
	writefile(length, width, maze( length,  width, exit));
	cout <<"______________________________________________________________________________________"<< endl;
	readfile();
}




