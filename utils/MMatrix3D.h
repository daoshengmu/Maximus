/*
 *  MMatrix3D.h
 *  Maximous
 *
 *  Created by User on 5/29/11.
 *  Copyright 2011 Daosheng Mu. All rights reserved.
 *
 */

#ifndef __MMATRIX3D_H__
#define __MMATRIX3D_H__


template<class Type>
class cMMatrix3D 
{
private:
	Type _items[16];
	static const cMMatrix3D<Type> g_Identity;
	
public:
	//--------------------------------
	// @breif: Constructor
	//--------------------------------
	cMMatrix3D() { identity(); };

	//--------------------------------
	// @breif: Constructor
	//--------------------------------
	cMMatrix3D( M_IN Type M_IN _m00, M_IN Type _m01, M_IN Type _m02, M_IN Type _m03,
			    M_IN Type M_IN _m10, M_IN Type _m11, M_IN Type _m12, M_IN Type _m13, 
			    M_IN Type M_IN _m20, M_IN Type _m21, M_IN Type _m22, M_IN Type _m23,
			    M_IN Type M_IN _m30, M_IN Type _m31, M_IN Type _m32, M_IN Type _m33)
	{
		_items[0] = _m00;  	_items[1] = _m01; 	_items[2] = _m02; 	_items[3] = _m03;
		_items[4] = _m10;  	_items[5] = _m11; 	_items[6] = _m12; 	_items[7] = _m13;
		_items[8] = _m20;  	_items[9] = _m21; 	_items[10] = _m22; 	_items[11] = _m23;
		_items[12] = _m30;  _items[13] = _m31; 	_items[14] = _m32; 	_items[15] = _m33;
		
	};
	
	//--------------------------------
	// @breif: Copy constructor
	//--------------------------------
	cMMatrix3D( M_IN const cMMatrix3D<Type>&rhs )
	{
		const Type* v = rhs.getRawData();
		
		memcpy( _items, v, sizeof( _items ) );
	};
	
	//--------------------------------
	// @breif: Destructor
	//--------------------------------
	~cMMatrix3D() {};
	
	Type operator [] ( M_IN unsigned int item )
	{	
		return _items[ item ];
	};
	
	const Type* getRawData() const { return _items; };
	
	void identity()
	{
		//const Type* v = getRawData();
		memcpy( (Type *)_items, ( const Type *)g_Identity.getRawData(), sizeof( _items ) );
		//memcpy( _items, v, sizeof( _items ) );
	};
	
	void setValueToItem( M_IN int row, M_IN int col, M_IN Type value )
	{
		_items[ row*4 + col ] = value;
	};
	
	void setRawData( M_IN Type *data, M_IN int counts )
	{
		memcpy( _items, data, sizeof(Type) * counts );		
	};		
	
	void translate( M_IN Type x, M_IN Type y, M_IN Type z )
	{
		_items[12] += x;
		_items[13] += y;
		_items[14] += z;
	};
	
	void translate( M_IN const cMVector3D<Type>& vect )
	{
		_items[12] += vect.x;
		_items[13] += vect.y;
		_items[14] += vect.z;
	};

};

template<class Type> 
const cMMatrix3D<Type> cMMatrix3D<Type>::g_Identity( 1,0,0,0,
													 0,1,0,0,
													 0,0,1,0,
													 0,0,0,1 );

#endif