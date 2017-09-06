// MyVector.cpp
//
// -- Coding practice assignment #1
// -- Implement a simple vector (container)
//
// Apirux Boontherawara
//

#include <stdexcept>
#include <cstdint>			// UINT32_MAX
//

typedef unsigned int uint;

template < class T >
class MyVector
{
	///////////////
	// CONSTANTS //
	///////////////
	
	
	// ---------------------------------------------------------------------- //
	
	////////////
	// BASICS //
	////////////
	
	public:
		MyVector( uint sz = 10 );							// Constructor ...default
		~MyVector();										// Destructor
		MyVector<T>& operator=( const MyVector<T>& myVec );	// = ...assignment
		
	// ---------------------------------------------------------------------- //
	
	///////////////
	// FUNCTIONS //
	///////////////
	
	public:
		// size, resizing
		uint size() const;									// size()
		uint max_size() const;								// max_size()
		uint capacity() const;								// capacity()
		bool empty() const;									// empty()
		void resize( uint newSize );						// resize()
		void shrink_to_fit();								// shrink_to_fit()
		void reserve( uint sz );							// reserve()
		
		// indexing
		T& operator[]( uint index ) const;					// [] ...indexing
		T& at( uint index ) const;							// at()
		T& front() const;									// front()
		T& back() const;									// back()
		
		// add, remove, swap
		void push_back( const T& val );						// push_back()
		void pop_back();									// pop_back()
		T* insert( T* position, T val, uint n = 1 );		// insert()
		T* erase( T* first, T* last = nullptr );			// erase()
		void swap( MyVector<T>& myVec );					// swap()
		void clear();										// clear()
		
		// operator overloads
		bool operator==( const MyVector<T>& myVec ) const;	// ==
		bool operator!=( const MyVector<T>& myVec ) const;	// !=
		bool operator<( const MyVector<T>& myVec ) const;	// <
		bool operator<=( const MyVector<T>& myVec ) const;	// <=
		bool operator>( const MyVector<T>& myVec ) const;	// >
		bool operator>=( const MyVector<T>& myVec ) const;	// >=
	
	// ---------------------------------------------------------------------- //
	
	/////////////
	// HELPERS //
	/////////////
	
	private:
		void _resize_array( uint newSize );				// _resize_array()
	
	// ---------------------------------------------------------------------- //
	
	///////////////
	// VARIABLES //
	///////////////
	
	private:
		T* _array;				//array of T-obj's
		uint _size;				//num elements
		uint _capacity;			//max elements without expanding array
	
};


// -------------------------------------------------------------------------------- //


////////////////////
// IMPLEMENTATION //
////////////////////

	////////////
	// BASICS //
	////////////
	
	// Constructor ...default
	template < class T >
	MyVector<T>::MyVector( uint sz /*= 10*/ ) 
		: _size(0),
		  _capacity(sz)
	{
		//init array
		_array = new T[ _capacity ];
	}
	
	// Destructor
	template < class T >
	MyVector<T>::~MyVector()
	{
		//array deletion
		delete[] _array;
	}
	
	// operator= ...assignment
	template < class T >
	MyVector<T>& MyVector<T>::operator=( const MyVector<T>& myVec )
	{
		//early exit ...self assignment
		if ( this == &myVec )
			return *this;
		
		//free old memory
		delete[] _array;
		
		//init new values
		_size = myVec.size();
		_capacity = myVec.capacity();
		_array = new T[ _capacity ];
		
		//copy elements
		for ( uint i = 0; i < _size; ++i )
			_array[i] = myVec[i];
		
		return *this;
	}
	
	// ---------------------------------------------------------------------- //
	
	///////////////
	// FUNCTIONS //
	///////////////
	
	// size()
	template < class T >
	uint MyVector<T>::size() const
	{ return _size; }
	
	// max_size()
	// ...maximum quantity of elements MyVector can hold
	// ...assumes: 32-bit
	template < class T >
	uint MyVector<T>::max_size() const
	{ return UINT32_MAX; }
	
	// capacity()
	// ...current capacity in terms of # of elements
	template < class T >
	uint MyVector<T>::capacity() const
	{ return _capacity; }
	
	// empty()
	template < class T >
	bool MyVector<T>::empty() const
	{ return ( _size == 0 ); }
	
	// resize()
	template < class T >
	void MyVector<T>::resize( uint newSize )
	{
		//grow capacity ...if applicable
		if ( newSize > _capacity )
			_resize_array( newSize );		//helper
		
		//shrink case
		while ( newSize < _size )
			pop_back();
		
		//expand case
		while ( newSize > _size )
			push_back( T() );
	}
	
	// shrink_to_fit()
	template < class T >
	void MyVector<T>::shrink_to_fit()
	{
		//early-exit
		if ( _size < _capacity )
			_resize_array( _size );
	}
	
	// reserve()
	template < class T >
	void MyVector<T>::reserve( uint sz )
	{
		//grow capacity ...if applicable
		if ( _capacity < sz )
			_resize_array( sz );
	}
	
	
	// operator[] ...indexing
	template < class T >
	T& MyVector<T>::operator[]( uint index ) const
	{ return _array[ index ]; }
	
	// at()
	template < class T >
	T& MyVector<T>::at( uint index ) const
	{
		//bounds checking
		if ( index >= _size )
			throw std::out_of_range( "Invalid index ...via at()" );
		
		return _array[ index ];
	}
	
	// front()
	template < class T >
	T& MyVector<T>::front() const
	{ return _array[0]; }
	
	// back()
	template < class T >
	T& MyVector<T>::back() const
	{ return _array[ _size ]; }
	
	
	// push_back()
	template < class T >
	void MyVector<T>::push_back( const T& val )
	{
		//grow capacity ...if applicable
		if ( _size == _capacity )
			_resize_array( _capacity * 2 );
		
		//add new element
		_array[ _size ] = val;
		++_size;
	}
	
	// pop_back()
	template < class T >
	void MyVector<T>::pop_back()
	{
		//remove last element
		_array[ _size - 1 ].~T();
		--_size;
	}
	
	// insert()
	template < class T >
	T* MyVector<T>::insert( T* position, T val, uint n /*= 1*/ )
	{
		//variables
		uint posIndex = position - _array;		//index of insert position
		
		//grow capacity ...if applicable
		if ( (_size + n) > _capacity )
		{
			//local vars
			uint new_capacity = _capacity;
			
			//double target size until sufficient
			while ( (_size + n) > new_capacity )
				new_capacity *= 2;
			
			//grow capacity
			_resize_array( new_capacity );
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
	template < class T >
	T* MyVector<T>::erase( T* first, T* last /*= nullptr*/ )
	{
		//variables
		uint firstIndex = first - _array;		//index of first erased
		uint lastIndex = ( last == nullptr ) ? _size : ( last - _array );
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
	template < class T >
	void MyVector<T>::swap( MyVector<T>& myVec )
	{
		//triangle swap
		T* temp = _array;
		_array = myVec._array;
		myVec._array = temp;
	}
	
	// clear()
	template < class T >
	void MyVector<T>::clear()
	{
		while ( _size > 0 )
			pop_back();
	}
	
	// operator== ...equal to
	template < class T >
	bool MyVector<T>::operator==( const MyVector<T>& myVec ) const
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
	template < class T >
	bool MyVector<T>::operator!=( const MyVector<T>& myVec ) const
	{ return !(*this == myVec); }
	
	// operator< ...less than
	template < class T >
	bool MyVector<T>::operator<( const MyVector<T>& myVec ) const
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
	template < class T >
	bool MyVector<T>::operator<=( const MyVector<T>& myVec ) const
	{ return !( myVec < *this ); }
	
	// operator> ...greater than
	template < class T >
	bool MyVector<T>::operator>( const MyVector<T>& myVec ) const
	{ return !( myVec < *this ); }
	
	// operator>= ...greater or equal to
	template < class T >
	bool MyVector<T>::operator>=( const MyVector<T>& myVec ) const
	{ return !( *this < myVec ); }
	
	// ---------------------------------------------------------------------- //
	
	/////////////
	// HELPERS //
	/////////////
	
	// _resize_array()
	template < class T >
	void MyVector<T>::_resize_array( uint newSize )
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
		
		//update capacity
		_capacity = newSize;
	}
	
	
// -------------------------------------------------------------------------------- //
