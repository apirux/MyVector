// main.cpp
//
// -- Coding practice assignment #1
// -- Implement a simple vector (container)
//
// Apirux Boontherawara
//

#include <iostream>
//#include <stdexcept>
//
#include "MyVector.h"

////////////////
// TESTING... //
////////////////

int main()
{
	//begin test...
	std::cout << "\nMyVector Tests" << std::endl;
	std::cout << "-----\n" << std::endl;
	
	//test 01a ...construct
	std::cout << "Constructing..." << std::endl;
	MyVector<int> vec;
	//
	std::cout << "-----\n" << std::endl;
	
	//test 01b ...check sizes
	std::cout << "Checking Size..." << std::endl;
	std::cout << "Size:\t\t" << vec.size() << std::endl;
	std::cout << "Max Size:\t" << vec.max_size() << std::endl;
	//
	std::cout << "-----\n" << std::endl;
	
	//test 02a ...populating
	std::cout << "Populating..." << std::endl;
	for (int i = vec.size(); i < vec.max_size(); ++i)
		vec.push_back( i );
	//
	std::cout << "-----\n" << std::endl;
	
	//test 02b ...indexing
	std::cout << "Data:" << std::endl;
	for (int i = 0; i < vec.max_size(); ++i)
		std::cout << vec[i] << "\t";
	//
	std::cout << "\n-----\n" << std::endl;
	
	
}

