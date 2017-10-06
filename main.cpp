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
	{
		if ( i < vec.size() )
			std::cout << vec[i] << "\t";
		else
			std::cout << "(" << vec[i] << ")" << "\t";
	}
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
	MyVector<int> vec1;
	//
	std::cout << "-----\n" << std::endl;
	
	//test 01b ...check sizes
	std::cout << "Checking Size..." << std::endl;
	std::cout << "Size:\t\t" << vec1.size() << std::endl;
	std::cout << "Capacity:\t" << vec1.capacity() << std::endl;
	//
	std::cout << "-----\n" << std::endl;
	
	//test 02a ...populating
	std::cout << "Populating..." << std::endl;
	for (int i = vec1.size(); i < vec1.capacity(); ++i)
		vec1.push_back( i );
	//
	std::cout << "-----\n" << std::endl;
	
	//test 02b ...indexing
	print_data<int>( vec1, "2b" );			//calls operator[]
	
	//test 03a ...emplace_back, emplace
	std::cout << "Emplacement..." << std::endl;
	vec1.emplace_back( 100 );
	print_data<int>( vec1, "3a.1" );
	vec1.emplace( &vec1[vec1.size()/2], 100 );
	print_data<int>( vec1, "3a.2" );
	//
	std::cout << "-----\n" << std::endl;
	
	//test 04a ...copy semantics
	std::cout << "Copy Semantics..." << std::endl;
	MyVector<int> vec2( vec1 );				//copy constructor
	print_data<int>( vec1, "4a.1 - vec1" );
	print_data<int>( vec2, "4a.1 - vec2" );
	vec1.emplace_back( 200 );
	vec2 = vec1;							//assignment
	print_data<int>( vec1, "4a.2 - vec1" );
	print_data<int>( vec2, "4a.2 - vec2" );
	//
	std::cout << "-----\n" << std::endl;
	
	//test 04b ...move semantics
	std::cout << "Move Semantics..." << std::endl;
	MyVector<int> vec3( vec1 );				//move constructor
	print_data<int>( vec1, "4b.1 - vec1" );
	print_data<int>( vec2, "4b.1 - vec2" );
	print_data<int>( vec3, "4b.1 - vec3" );
	vec2[0] = 300;
	vec3 = vec2;							//copy assignment
	print_data<int>( vec1, "4b.2 - vec1" );
	print_data<int>( vec2, "4b.2 - vec2" );
	print_data<int>( vec3, "4b.2 - vec3" );
	//
	std::cout << "-----\n" << std::endl;
	
}

