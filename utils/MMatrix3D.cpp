///*
// *  MMatrix3D.cpp
// *  Maximous
// *
// *  Created by User on 5/29/11.
// *  Copyright 2011 Daosheng Mu. All rights reserved.
// *
// */
//
////#include "MMatrix3D.h"
//#include "Maximous_Prefix.pch"
//
//template <class Type>
//cMMatrix3D<Type>::cMMatrix3D( M_IN Type _m00, M_IN Type _m01, M_IN Type _m02, M_IN Type _m03,
//						M_IN Type _m10, M_IN Type _m11, M_IN Type _m12, M_IN Type _m13, 
//						M_IN Type _m20, M_IN Type _m21, M_IN Type _m22, M_IN Type _m23,
//						M_IN Type _m30, M_IN Type _m31, M_IN Type _m32, M_IN Type _m33 )
//{
//	_items[0] = _m00;  	_items[1] = _m01; 	_items[2] = _m02; 	_items[3] = _m03;
//	_items[4] = _m10;  	_items[5] = _m11; 	_items[6] = _m12; 	_items[7] = _m13;
//	_items[8] = _m20;  	_items[9] = _m21; 	_items[10] = _m22; 	_items[11] = _m23;
//	_items[12] = _m30;  _items[13] = _m31; 	_items[14] = _m32; 	_items[15] = _m33;
//
//}
//
//template <class Type>
//cMMatrix3D<Type>::cMMatrix3D( M_IN const cMMatrix3D<Type>&rhs )
//{
//	const Type* v = rhs.getRawData();
//	
//	memcpy( _items, v, sizeof( _items ) );
//}
//
//template <class Type>
//void
//cMMatrix3D<Type>::setValueToItem( int row, int col, Type value )
//{
//	_items[ row*4 + col ] = value;
//}
