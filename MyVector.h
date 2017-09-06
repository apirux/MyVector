// MyVector.cpp
//
// -- Coding practice assignment #1
// -- Implement a simple vector (container)
//
// Apirux Boontherawara
//

#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <stdexcept>
//

typedef unsigned int uint;

template < class T >
class MyVector
{
	///////////////
	// CONSTANTS //
	///////////////
	
	
	// ------------------------------------------------------------ //
	
	////////////
	// BASICS //
	////////////
	
	public:
		
		// Constructor ...default
		MyVector( uint sz = 10 )
		{
			//init array
			_size = 0;
			_max_size = sz;
			_array = new T[ _max_size ];
		}
		
		// Destructor
		~MyVector()
		{
			//array deletion
			delete[] _array;
		}
		
		// operator= ...assignment
		MyVector<T>& operator=( const MyVector<T>& myVec )
		{
			//early exit ...self assignment
			if ( this == &myVec )
				return *this;
			
			//free old memory
			delete[] _array;
			
			//init new values
			_size = myVec.size();
			_max_size = myVec.max_size();
			_array = new T[ _max_size ];
			
			//copy elements
			for ( uint i = 0; i < _size; ++i )
				_array[i] = myVec[i];
			
			return *this;
		}
		
	// ------------------------------------------------------------ //
	
	///////////////
	// FUNCTIONS //
	///////////////
	
	public:
		
		// size()
		uint size() const { return _size; }
		
		// max_size()
		uint max_size() const { return _max_size; }
		
		// capacity()
		uint capacity() const { return _max_size * sizeof(T); }
		
		// empty()
		bool empty() const { return ( _size == 0 ); }
		
		// resize()
		void resize( uint newSize )
		{
			//grow capacity ...if applicable
			if ( newSize > _max_size )
				_resize_array( newSize );		//helper
			
			//shrink case
			while ( newSize < _size )
				pop_back();
			
			//expand case
			while ( newSize > _size )
				push_back( T() );
		}
		
		// shrink_to_fit()
		void shrink_to_fit()
		{
			//early-exit
			if ( _size < _max_size )
				_resize_array( _size );
		}
		
		// reserve()
		void reserve( uint sz )
		{
			//grow capacity ...if applicable
			if ( _max_size < sz )
				_resize_array( sz );
		}
		
		
		// operator[] ...indexing
		T& operator[]( uint index ) const { return _array[ index ]; }
		
		// at()
		T& at( uint index ) const
		{
			//bounds checking
			if ( index >= _size )
				throw std::out_of_range( "Invalid index ...via at()" );
			
			return _array[ index ];
		}
		
		// front()
		T& front() const { return _array[0]; }
		
		// back()
		T& back() const { return _array[ _size ]; }
		
		
		// push_back()
		void push_back( const T& val )
		{
			//grow capacity ...if applicable
			if ( _size == _max_size )
				_resize_array( _max_size * 2 );
			
			//add new element
			_array[ _size ] = val;
			++_size;
		}
		
		// pop_back()
		void pop_back()
		{
			//remove last element
			_array[ _size - 1 ].~T();
			--_size;
		}
		
		// insert()
		T* insert( T* position, T val, uint n = 1 )
		{
			//variables
			uint posIndex = position - _array;		//index of insert position
			
			//grow capacity ...if applicable
			if ( (_size + n) > _max_size )
			{
				//local vars
				uint new_max_sz = _max_size;
				
				//double target size until sufficient
				while ( (_size + n) > new_max_sz )
					new_max_sz *= 2;
				
				//grow capacity
				_resize_array( new_max_sz );
			}
			
			//shift elements ...after position
			for ( uint i = _size - 1; i > posIndex; --i )
				_array[i + n] = _array[i];
			
			//insert new elements
			for ( uint i = posIndex; i < posIndex + n; ++i )
				_array[i] = val;
			
			return ( _array + posIndex );
		}
		
		// erase()
		T* erase( T* first, T* last = NULL )
		{
			//variables
			uint firstIndex = first - _array;		//index of first erased
			uint lastIndex = ( last == NULL ) ? _size : ( last - _array );
				//NOTE:		Erase covers [fist, last), so last is not erased.
			
			//shift remaining elements ...after last
			for ( uint i = 0; i < _size - lastIndex; ++i )
				_array[ firstIndex + i ] = _array[ lastIndex + i ];
			
			//remove excess elements
			for ( uint i = 0; i < last - first; ++i )
				pop_back();
			
			return first;
		}
		
		// swap()
		void swap( MyVector<T>& myVec )
		{
			//triangle swap
			T* temp = _array;
			_array = myVec._array;
			myVec._array = temp;
		}
		
		// clear()
		void clear()
		{
			while ( _size > 0 )
				pop_back();
		}
		
		// operator== ...equal to
		bool operator==( const MyVector<T>& myVec ) const
		{
			//early exit ...self comparison
			if ( this == &myVec )
				return true;
			
			//compare size
			if ( _size != myVec._size )
				return false;
			
			//compare elements
			for ( uint i = 0; i < _size; ++i )
			{
				if ( _array[i] != myVec._array[i] )
					return false;
			}
			
			return true;
		}
		
		// operator!= ...unequal to
		bool operator!=( const MyVector<T>& myVec ) const { return !(*this == myVec); }
		
		// operator< ...less than
		bool operator<( const MyVector<T>& myVec ) const
		{
			//variables
			bool is_shorter = ( _size < myVec._size );		//for if all match
			uint num_comparisons = ( is_shorter ) ? _size : myVec._size;
			
			//compare elements
			for ( uint i = 0; i < num_comparisons; ++i )
			{
				if ( _array[i] < myVec._array[i] )
					return true;
				if ( myVec._array[i] < _array[i] )
					return false;
			}
			
			return is_shorter;
				//NOTE:		If elements match, the shorter array is lesser
		}
		
		// operator<= ...less or equal to
		bool operator<=( const MyVector<T>& myVec ) const { return !( myVec < *this ); }
		
		// operator> ...greater than
		bool operator>( const MyVector<T>& myVec ) const { return !( myVec < *this ); }
		
		// operator>= ...greater or equal to
		bool operator>=( const MyVector<T>& myVec ) const { return !( *this < myVec ); }
		
	
	// ------------------------------------------------------------ //
	
	/////////////
	// HELPERS //
	/////////////
	
	private:
		
		// _resize_array()
		void _resize_array( uint newSize )
		{
			//variables
			T* arr = new T[ newSize ];			//new array
			
			//copy elements to new array ...truncate if applicable
			_size = ( _size < newSize ) ? _size : newSize;
			for ( uint i = 0; i < _size; ++i )
				arr[i] = _array[i];
			
			//assign new array ...after freeing old memory
			delete[] _array;
			_array = arr;
			
			//update max size
			_max_size = newSize;
		}
	
	// ------------------------------------------------------------ //
	
	///////////////
	// VARIABLES //
	///////////////
	
	private:
		T* _array;				//array of T-obj's
		uint _size;				//num elements
		uint _max_size;			//max elements without expanding
		
	
	// ------------------------------------------------------------ //
	
};

#endif
