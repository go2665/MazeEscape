#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <fstream>
#include "MazeEscape.h"
#include "PlayerData.h"

int main()
{
    InitializeMaze();
    MazeEscapeRun();
    ClearMaze();

    return 0;
}

const char* DirectoryName = ".\\Data\\";
int MazeWidth = 20;
int MazeHeight = 10;
int** Maze = nullptr;

void InitializeMaze()
{
	std::string Data;
	ReadMapFile("MapData.txt", Data);
	ParseMapData(Data);
}

void MazeEscapeRun()
{
	PlayerData Player;

	FindStartPosition(Player.CurrentPosition);

	printf("~~ Maze Escape ~~\n");

	while (true)
	{
		PrintMaze(Player.CurrentPosition);

		if (IsEnd(Player.CurrentPosition))
		{
			printf("Congratulations! You have escaped the maze!\n");
			break;
		}

		int MoveFlags = PrintAvailableMoves(Player.CurrentPosition);
		MoveDirection Direction = GetMoveInput(MoveFlags);
		switch (Direction)
		{
		case DirUp:
			Player.CurrentPosition.y--;
			break;
		case DirDown:
			Player.CurrentPosition.y++;
			break;
		case DirLeft:
			Player.CurrentPosition.x--;
			break;
		case DirRight:
			Player.CurrentPosition.x++;
			break;
		case DirNone:
		default:
			// Critical Error
			break;
		}
	}
}

void ClearMaze()
{
	if (Maze != nullptr)
	{
		for (int i = 0; i < MazeHeight; i++)
		{
			delete[] Maze[i];
			Maze[i] = nullptr;
		}
		delete[] Maze;
		Maze = nullptr;
	}
}

bool ReadMapFile(const char* MapFileName, std::string& OutDataString)
{
	char FilePath[256];
	strcpy(FilePath, DirectoryName);
	strcat(FilePath, MapFileName);

	std::ifstream InputFile(FilePath);
	if (!InputFile.is_open())
	{
		printf("File open FAIL!\n");
		printf("[%s] Check file path.\n", FilePath);
		return false;
	}

	OutDataString = std::string((std::istreambuf_iterator<char>(InputFile)),
		std::istreambuf_iterator<char>());

	return true;
}

bool ParseMapData(std::string& DataString)
{
	char Source[512];
	char* Current = Source;
	strcpy(Source, DataString.c_str());

	char* LinePtr = GetLine(&Current);

	int SizeNumbers[2] = { 0 };
	ParseLineData(LinePtr, 2, SizeNumbers);

	MazeWidth = SizeNumbers[0];
	MazeHeight = SizeNumbers[1];

	Maze = new int* [MazeHeight];
	for (int y = 0; y < MazeHeight; y++)
	{
		Maze[y] = new int[MazeWidth];
	}

	int HeightIndex = 0;
	while ((*Current) != '\0')
	{
		LinePtr = GetLine(&Current);
		ParseLineData(LinePtr, MazeWidth, Maze[HeightIndex]);
		HeightIndex++;

		if (HeightIndex >= MazeHeight)
			break;
	}

	return true;
}

int FindCharIndex(const char* TargetString, const char TargetCharacter)
{
	int Index = 0;
	bool IsFind = false;
	while (TargetString[Index] != '\0')
	{
		if (TargetString[Index] == TargetCharacter)
		{
			IsFind = true;
			break;
		}
		Index++;
	}

	if (!IsFind)
	{
		Index = -1;
	}
	return Index;
}

char* GetLine(char** InOutSource)
{
	char* Result = (*InOutSource);
	int Index = FindCharIndex((*InOutSource), '\n');
	if (Index == -1)
	{
		(*InOutSource) = (*InOutSource) + FindCharIndex((*InOutSource), '\0');
	}
	else
	{
		*((*InOutSource) + Index) = '\0';
		(*InOutSource) = (*InOutSource) + Index + 1;
	}

	return Result;
}

void ParseLineData(const char* LineData, int ArraySize, int* OutArray)
{
	const char* LinePointer = LineData;
	int SizeIndex = 0;
	while ((*LinePointer) != '\0')
	{
		int Result = 0;
		while ((*LinePointer) != ',' && (*LinePointer) != '\0')
		{
			Result = Result * 10 + (*LinePointer) - '0';
			LinePointer++;
		}
		OutArray[SizeIndex] = Result;
		SizeIndex++;

		if (ArraySize <= SizeIndex)	
			break;

		if (*LinePointer < '0' || *LinePointer > '9')
			LinePointer++;
	}
}

void PrintMaze(Position& position)
{
	for (int y = 0; y < MazeHeight; y++)
	{
		for (int x = 0; x < MazeWidth; x++)
		{
			if (position.x == x && position.y == y)
			{
				printf("P ");
			}
			else if (Maze[y][x] == Wall)
			{
				printf("# ");
			}
			else if (Maze[y][x] == Path)
			{
				printf(". ");
			}
			else if (Maze[y][x] == Start)
			{
				printf("S ");
			}
			else if (Maze[y][x] == End)
			{
				printf("E ");
			}
			else
			{
				// Critical Error. Map Data is Wrong.
			}
		}
		printf("\n");
	}
}

void FindStartPosition(Position& OutPosition)
{
	for (int y = 0; y < MazeHeight; y++)
	{
		for (int x = 0; x < MazeWidth; x++)
		{
			if (Maze[y][x] == Start)
			{
				OutPosition.x = x;
				OutPosition.y = y;
				return;
			}
		}
	}
	OutPosition.x = 0;
	OutPosition.y = 0;
}

int PrintAvailableMoves(Position& position)
{
	int MoveFlags = DirNone;

	printf("Select movable direction (w:Up a:Left s:Down d:Right):\n");
	if (!IsWall(position.x, position.y - 1))
	{
		printf("W(↑) ");
		MoveFlags |= DirUp;
	}
	if (!IsWall(position.x, position.y + 1))
	{
		printf("S(↓) ");
		MoveFlags |= DirDown;
	}
	if (!IsWall(position.x - 1, position.y))
	{
		printf("A(←) ");
		MoveFlags |= DirLeft;
	}
	if (!IsWall(position.x + 1, position.y))
	{
		printf("D(→) ");
		MoveFlags |= DirRight;
	}
	printf("\n");

	return MoveFlags;
}

bool IsWall(int X, int Y)
{
	bool isWall = false;
	if (Y < 0 || Y >= MazeHeight ||
		X < 0 || X >= MazeWidth ||
		Maze[Y][X] == Wall)
		isWall = true;
	return isWall;
}

bool IsEnd(Position& position)
{
	return Maze[position.y][position.x] == End;
}

MoveDirection GetMoveInput(int MoveFlags)
{
	char InputChar = 0;
	MoveDirection Direction = DirNone;

	while (true)
	{
		printf("Input direction : ");
		std::cin >> InputChar;

		if ((InputChar == 'w' || InputChar == 'W')
			&& (MoveFlags & DirUp) /*!= 0*/)
		{
			Direction = DirUp;
			break;
		}
		if ((InputChar == 's' || InputChar == 'S')
			&& (MoveFlags & DirDown) /*!= 0*/)
		{
			Direction = DirDown;
			break;
		}
		if ((InputChar == 'a' || InputChar == 'A')
			&& (MoveFlags & DirLeft) /*!= 0*/)
		{
			Direction = DirLeft;
			break;
		}
		if ((InputChar == 'd' || InputChar == 'D')
			&& (MoveFlags & DirRight) /*!= 0*/)
		{
			Direction = DirRight;
			break;
		}

		printf("Wrong input. Select movable direction.\n");
	}

	return Direction;
}
