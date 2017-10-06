// MyVector.cpp
//
// -- Coding practice assignment #1
// -- Implement a simple vector (container)
//
// Apirux Boontherawara
//

#include <stdexcept>		// out_of_range
#include <algorithm>		// rotate
#include <utility>			// forward
#include <cstdint>			// UINT32_MAX
//

typedef unsigned int uint;

template < typename T >
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
		MyVector( const MyVector<T>& myVec );				// Constructor ...copy
		MyVector( MyVector<T>&& myVec );					// Constructor (move)
		virtual ~MyVector();								// Destructor
		//
		MyVector<T>& operator=( const MyVector<T>& myVec );	// = ...assignment
		MyVector<T>& operator=( MyVector<T>&& myVec );		// = ...assignment (move)
		
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
		const T& operator[]( uint index ) const;			// [] ...indexing
		T& operator[]( uint index );						// [] ...indexing
		const T& at( uint index ) const;					// at()
		T& at( uint index );								// at()
		const T& front() const;								// front()
		T& front();											// front()
		const T& back() const;								// back()
		T& back();											// back()
		
		// add, remove, swap
		void push_back( const T& val );						// push_back()
		void pop_back();									// pop_back()
		T* insert( T* position, T val, uint n = 1 );		// insert()
		T* erase( T* first, T* last = nullptr );			// erase()
		void swap( MyVector<T>& myVec );					// swap()
		void clear();										// clear()
		//
		template < typename... Args >
		T* emplace( const T* position, Args&&... args );	// emplace()
		template < typename... Args >
		void emplace_back( Args&&... args );				// emplace_back()
		
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
	
	protected:
		void _free_array();											// _free_array()
		void _copy_elements( const MyVector& myVec, uint num = 0 );	// _copy_elements
		void _resize_array( uint newSize );							// _resize_array()
	
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
	template < typename T >
	MyVector<T>::MyVector( uint sz /*= 10*/ ) 
		: _size(0)
		, _capacity(sz)
	{
		//init array
		_array = new T[ _capacity ];
	}
	
	// Constructor (copy)
	template < typename T >
	MyVector<T>::MyVector( const MyVector<T>& myVec ) 
		: _size( myVec.size() )
		, _capacity( myVec.capacity() )
	{
		//init array
		_array = new T[ _capacity ];
		
		//copy elements
		for ( uint i = 0; i < _size; ++i )
			_array[i] = myVec[i];
	}
	
	// Constructor (move)
	template < typename T >
	MyVector<T>::MyVector( MyVector<T>&& myVec ) 
		: _size( myVec.size() )
		, _capacity( myVec.capacity() )
		, _array( myVec._array )
	{ myVec._array = nullptr; }
	
	// Destructor
	template < typename T >
	MyVector<T>::~MyVector()
	{ _free_array(); }
	
	// operator= ...assignment
	template < typename T >
	MyVector<T>& MyVector<T>::operator=( const MyVector<T>& myVec )
	{
		//early exit ...self assignment
		if ( this == &myVec )
			return *this;
		
		//free old memory
		_free_array();
		
		//re-init new values
		_size = myVec.size();
		_capacity = myVec.capacity();
		_array = new T[ _capacity ];
		
		//copy elements
		for ( uint i = 0; i < _size; ++i )
			_array[i] = myVec[i];
		
		return *this;
	}
	
	// operator= ...assignment (move)
	template < typename T >
	MyVector<T>& MyVector<T>::operator=( MyVector<T>&& myVec )
	{
		//early exit ...self assignment
		if ( this == &myVec )
			return *this;
		
		//free old memory
		_free_array();
		
		//re-init new values
		_size = myVec.size();
		_capacity = myVec.capacity();
		
		//move array
		_array = myVec._array;
		myVec = nullptr;
		
		return *this;
	}
	
	// ---------------------------------------------------------------------- //
	
	///////////////
	// FUNCTIONS //
	///////////////
	
	// size()
	template < typename T >
	uint MyVector<T>::size() const
	{ return _size; }
	
	// max_size()
	// ...maximum quantity of elements MyVector can hold
	// ...assumes: 32-bit
	template < typename T >
	uint MyVector<T>::max_size() const
	{ return UINT32_MAX; }
	
	// capacity()
	// ...current capacity in terms of # of elements
	template < typename T >
	uint MyVector<T>::capacity() const
	{ return _capacity; }
	
	// empty()
	template < typename T >
	bool MyVector<T>::empty() const
	{ return ( _size == 0 ); }
	
	// resize()
	template < typename T >
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
	template < typename T >
	void MyVector<T>::shrink_to_fit()
	{
		//early-exit
		if ( _size < _capacity )
			_resize_array( _size );
	}
	
	// reserve()
	template < typename T >
	void MyVector<T>::reserve( uint sz )
	{
		//grow capacity ...if applicable
		if ( _capacity < sz )
			_resize_array( sz );
	}
	
	
	// operator[] ...indexing
	template < typename T >
	const T& MyVector<T>::operator[]( uint index ) const
	{ return _array[ index ]; }
	//
	template < typename T >
	T& MyVector<T>::operator[]( uint index )
	{ return const_cast<T&>( static_cast<const MyVector&>(*this)[index] ); }
	
	// at()
	template < typename T >
	const T& MyVector<T>::at( uint index ) const
	{
		//bounds checking
		if ( index >= _size )
			throw std::out_of_range( "Invalid index ...via at()" );
		
		return _array[ index ];
	}
	//
	template < typename T >
	T& MyVector<T>::at( uint index )
	{ return const_cast<T&>( static_cast<const MyVector&>(*this).at(index) ); }
	
	// front()
	template < typename T >
	const T& MyVector<T>::front() const
	{ return _array[0]; }
	//
	template < typename T >
	T& MyVector<T>::front()
	{ return const_cast<T&>( static_cast<const MyVector&>(*this).front() ); }
	
	// back()
	template < typename T >
	const T& MyVector<T>::back() const
	{ return _array[ _size ]; }
	//
	template < typename T >
	T& MyVector<T>::back()
	{ return const_cast<T&>( static_cast<const MyVector&>(*this).back() ); }
	
	
	// push_back()
	template < typename T >
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
	template < typename T >
	void MyVector<T>::pop_back()
	{
		//destroy & remove last element
		_array[ _size - 1 ].~T();
		--_size;
	}
	
	// insert()
	template < typename T >
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
		
		//update _size
		_size += n;
		
		return ( _array + posIndex );
	}
	
	// erase()
	template < typename T >
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
	template < typename T >
	void MyVector<T>::swap( MyVector<T>& myVec )
	{
		//triangle swap
		T* temp = _array;
		_array = myVec._array;
		myVec._array = temp;
	}
	
	// clear()
	template < typename T >
	void MyVector<T>::clear()
	{
		while ( !empty() )
			pop_back();
	}
	
	
	// emplace()
	template < typename T >
	template < typename... Args >
	T* MyVector<T>::emplace( const T* position, Args&&... args )
	{
		//variables
		T* pos = const_cast<T*>( position );			//insert position
		T* end_ptr = _array + _size;
		
		//init and re-position new element
		emplace_back( std::forward<Args>(args)... );	//init
		std::rotate( pos, end_ptr - 1, end_ptr );		//re-position
		
		return pos;
	}
	
	// emplace_back()
	template < typename T >
	template < typename... Args >
	void MyVector<T>::emplace_back( Args&&... args )
	{
		//variables
		T* end_ptr;
		
		//grow capacity ...if applicable
		if ( _size == _capacity )
			_resize_array( _capacity * 2 );
		
		//init in-place
		end_ptr = _array + _size;						//1 past last element
		new (end_ptr) T( std::forward<Args>(args)... );	//placement new w/ args
		
		//update _size
		++_size;
	}
	
	
	// operator== ...equal to
	template < typename T >
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
	template < typename T >
	bool MyVector<T>::operator!=( const MyVector<T>& myVec ) const
	{ return !(*this == myVec); }
	
	// operator< ...less than
	template < typename T >
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
	template < typename T >
	bool MyVector<T>::operator<=( const MyVector<T>& myVec ) const
	{ return !( myVec < *this ); }
	
	// operator> ...greater than
	template < typename T >
	bool MyVector<T>::operator>( const MyVector<T>& myVec ) const
	{ return !( myVec < *this ); }
	
	// operator>= ...greater or equal to
	template < typename T >
	bool MyVector<T>::operator>=( const MyVector<T>& myVec ) const
	{ return !( *this < myVec ); }
	
	// ---------------------------------------------------------------------- //
	
	/////////////
	// HELPERS //
	/////////////
	
	// _free_array()
	template < typename T >
	void MyVector<T>::_free_array()
	{
		//free memory ...applicable
		if ( capacity() > 0 )
		{
			clear();				//deep destruction
			delete[] _array;		//array deletion
		}
		
		//Note:		Deep destruction is needed for cases where T-obj's 
		//			have members with dynamic memory allocation
	}
	
	// _resize_array()
	template < typename T >
	void MyVector<T>::_resize_array( uint newCapacity )
	{
		//variables
		T* arr = new T[ newCapacity ];									//new array
		uint num_copy = ( _size < newCapacity ) ? _size : newCapacity;	//# elements to copy
		
		//copy elements to new array ...truncate if applicable
		for ( uint i = 0; i < num_copy; ++i )
			arr[i] = _array[i];
		
		//assign new array ...after freeing old memory
		_free_array();
		_array = arr;
		
		//update values
		_size = num_copy;
		_capacity = newCapacity;
	}
	
	
// -------------------------------------------------------------------------------- //
