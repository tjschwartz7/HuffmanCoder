
#include "HuffmanTree.h"


int main(int argc, char* argv[])
{
	FILE* file;
	if (argc >= 2)
	{
		fopen_s(&file, argv[1], "rw");
	}
	else
	{
		cout << "Please input a file\n";
		return -1;
	}

	return 0;
}