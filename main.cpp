// main.cpp
//
// -- Coding practice assignment #1
// -- Implement a simple vector (container)
//
// Apirux Boontherawara
//

#include <iostream>			// cout, endl
#include <string>			// string, to_string
//#include <stdexcept>
//
#include "MyVector.h"

////////////////
// TESTING... //
////////////////

// print_data()		...helper
// assumes: 'T' is a printable type
template < typename T >
void print_data( const MyVector<T>& vec, std::string setID = "" )
{
	//default set-ID ...if applicable
	setID = (setID == "") ? setID : (" " + setID);
	
	//print
	std::cout << "Data" << setID << ":" << std::endl;
	for (int i = 0; i < vec.capacity(); ++i)
		std::cout << vec[i] << "\t";
	//
	std::cout << "\n-----\n" << std::endl;
}
//
template < typename T >
void print_data( const MyVector<T>& vec, int setID )
{ return print_data<T>( vec, std::to_string(setID) ); }

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
	std::cout << "Capacity:\t" << vec.capacity() << std::endl;
	//
	std::cout << "-----\n" << std::endl;
	
	//test 02a ...populating
	std::cout << "Populating..." << std::endl;
	for (int i = vec.size(); i < vec.capacity(); ++i)
		vec.push_back( i );
	//
	std::cout << "-----\n" << std::endl;
	
	//test 02b ...indexing
	print_data<int>( vec, 1 );			//calls operator[]
	
	//test 03a ...emplace_back, emplace
	std::cout << "Emplacement..." << std::endl;
	vec.emplace_back( 100 );
	print_data<int>( vec, "2a" );
	vec.emplace( &vec[vec.size()/2], 100 );
	print_data<int>( vec, "2b" );
	//
	std::cout << "-----\n" << std::endl;
}

