

#include <iostream>
#include <string>

#include <cstdlib>
#include <ctime>
#include <vector>

#include "check_value.h"
#include "print_table_score.h"
#include "save_table_score.h"
#include "work_with_result.h"


int main(int argc, char** argv)
{
	// Arguments
	int DEFAULT_MAX_VALUE {200};
	int parameter_level = 0;
	int parameter_value = 0; int MAX_VALUE{150};
	const std::string high_scores_filename = "high_scores.txt";


	if (argc <= 1) {
		std::cout << std::endl;
		std::cout << "If you want to set the MAX number, start the program with the parameter" << std::endl;
		std::cout << "Example '-max 42' " << std::endl;
		std::cout << "At this launch, the program will create its own secret number " << std::endl;
		std::cout << std::endl;

	}
	if (argc >= 2) {
		std::string arg1_value{ argv[1] };

		if (arg1_value == "-max") 
		{
			// We've detected the '-parameter' argument. And we extect that after this argument there is a value:
			if (argc < 3) {
				std::cout << "Wrong usage! The argument '-max' requires some value!" << std::endl;
				return -1;
			}

			// We need to parse the string to the int value
			parameter_value = std::stoi(argv[2]);

			std::cout << ">guess_the_number -max " << parameter_value << std::endl;
			std::cout << std::endl;

		}
		
		if (arg1_value == "-level") 
		{
			// We've detected the '-parameter' argument. And we extect that after this argument there is a value:
			if (argc < 3) {
				std::cout << "Wrong usage! The argument '-level' requires some value!" << std::endl;
				return -1;
			}
			
			// We need to parse the string to the int value
			parameter_level = std::stoi(argv[2]);
		
			switch (parameter_level)
			{
			case 1:
				MAX_VALUE= 10;
				break;
			case 2:
				MAX_VALUE= 50;
				break;
			case 3:
				MAX_VALUE= 100;
				break;
			default:
				MAX_VALUE= 200;
				break;
			}

			std::cout << ">guess_the_number -level " << parameter_level << std::endl;
			std::cout << std::endl;

		}
		
		if (arg1_value == "-table")
		{
			std::cout << ">guess_the_number -table " << std::endl;
			std::cout << std::endl;

			print_table_score(high_scores_filename);// Read the high score file and print all results
			exit(1);
		}

	}

	
	// Ask about name
	std::cout << "Hi! Enter your name, please:" << std::endl;
	std::string user_name;
	std::cin >> user_name;

	int max_value = DEFAULT_MAX_VALUE;

	if(parameter_value!=0) max_value =parameter_value;
	if (parameter_level != 0) max_value = MAX_VALUE;

	srand(static_cast<int>(time(NULL)));
	const int random_value = std::rand() % max_value;
	std::cout << ">guess_the_number " << random_value << std::endl;


	std::cout << "Hi "
		<< user_name
		<< ";) Secret number is selected in range (1,"
		<< max_value
		<< ")"
		<< std::endl;

	int attempts_count{ 0};

	attempts_count = check_value(random_value);
	// update table result
	std::vector<std::pair<std::string, int>> score_table;
	
	// update table with new result
	score_table= Best_result (high_scores_filename, user_name,attempts_count);

	// Write new high score to the records table
	save_table_score(high_scores_filename,score_table);

	// Read the high score file and print all results
	print_table_score(high_scores_filename);


	return 0;
}