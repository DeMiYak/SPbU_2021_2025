#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include"../Task6/replace.h"

int main(int argc, char* argv[])
{	
	if (argc == 1) {
		std::cout << "Fatal error: infile not found.\nTry the following:" <<
			">Task6.2.exe <Input name> [Output name]" << std::endl;
		exit(1);
	}

	char outfile[BUFFER_SIZE];
	if (argc == 2){
		std::cout << "Outfile not found in command-line. Enter outfile name: ";
		std::cin >> outfile;
	}

	if (argc >= 3) strcpy(outfile, argv[2]);

	FILE* ofile, *ifile;
	
	ifile = fopen(argv[1], "r");
	if (!ifile) {
		std::cout << "Error: nonexisting infile in command-line.";
		exit(1);
	}
	fclose(ifile);

	ofile = fopen(outfile, "r");
	// if ofile exist
	while (ofile) {

		// if ofile exist
		fclose(ofile);
		// Rewriting file at request
		std::cout << "Rewrite file? (Y/N): ";
		
		char temp;
		std::cin >> temp;
		if (toupper(temp) == 'Y') break;
		std::cin.get();

		std::cout << "\nEnter new outfile name: ";
		std::cin >> outfile;
		ofile = fopen(outfile, "r");
	}

	ofile = fopen(outfile, "w");
	ifile = fopen(argv[1], "r");
	char tempAr[BUFFER_SIZE];
	int count = 0;
	while (fgets(tempAr, BUFFER_SIZE, ifile)) {
		starReplace(tempAr, count);
		fputs(tempAr, ofile);
	}
	fclose(ifile);
	fclose(ofile);
	std::cout << "Successful transition.\n";
	std::cout << "count = " << count << std::endl;
	return 0;
}