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

#include <cstring>
#include "util/MVector3D.h"

namespace Maximus
{

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
	cMMatrix3D(  Type  _m00,  Type _m01,  Type _m02,  Type _m03,
			     Type  _m10,  Type _m11,  Type _m12,  Type _m13, 
			     Type  _m20,  Type _m21,  Type _m22,  Type _m23,
			     Type  _m30,  Type _m31,  Type _m32,  Type _m33)
  {
    _items[0] = _m00; _items[1] = _m01; _items[2] = _m02; _items[3] = _m03;
    _items[4] = _m10; _items[5] = _m11; _items[6] = _m12; _items[7] = _m13;
    _items[8] = _m20; _items[9] = _m21; _items[10] = _m22; _items[11] = _m23;
    _items[12] = _m30; _items[13] = _m31; _items[14] = _m32; _items[15] = _m33;
		
  };
	
	//--------------------------------
	// @breif: Copy constructor
	//--------------------------------
	cMMatrix3D( const cMMatrix3D<Type>&rhs )
	{
		const Type* v = rhs.getRawData();
		
		memcpy( _items, v, sizeof( _items ) );
	};
	
	//--------------------------------
	// @breif: Destructor
	//--------------------------------
	~cMMatrix3D() {};
	
	Type operator [] (  unsigned int item )
	{	
		return _items[ item ];
	};
	
	const Type* getRawData() const { return _items; };
	
	void identity()
	{
		//const Type* v = getRawData();
		memcpy( (Type *)_items, ( const Type *)g_Identity.getRawData(), sizeof( _items ) );
		//memcpy( _items, v, sizeof( _items ) );
	}
	
	void setValueToItem(  int row,  int col,  Type value )
	{
		_items[ row*4 + col ] = value;
	}
	
	void setRawData(  Type *data,  int counts )
	{
		memcpy( _items, data, sizeof(Type) * counts );		
	}
	
  Type* GetItems()
  {
      return _items;
  }
  
  //--------------------------------------------------------------------------
  /// @brief Get items of this Matrix
  ///
  /// @return Matrix items
  //--------------------------------------------------------------------------
  const Type* GetItems() const
  {
      return _items;
  }

  void translate( Type x, Type y, Type z )
  {
    _items[12] += x;
    _items[13] += y;
    _items[14] += z;
  }

  void translate( const cMVector3D<Type>& vect )
  {
    _items[12] += vect.x;
    _items[13] += vect.y;
    _items[14] += vect.z;
  }
  
  void scale( const cMVector3D<Type>& vect )
  {
      _items[0*4+0] *= vect.x;
      _items[1*4+0] *= vect.x;
      _items[2*4+0] *= vect.x;
      _items[3*4+0] *= vect.x;
      
      _items[0*4+1] *= vect.y;
      _items[1*4+1] *= vect.y;
      _items[2*4+1] *= vect.y;
      _items[3*4+1] *= vect.y;
      
      _items[0*4+2] *= vect.z;
      _items[1*4+2] *= vect.z;
      _items[2*4+2] *= vect.z;
      _items[3*4+2] *= vect.z;
  }
  
  cMMatrix3D<Type>& operator *= ( const cMMatrix3D<Type>& rhs )
  {
      cMMatrix3D<Type> temp;
      Type* pTempItems = temp.GetItems();
      
      const Type* pRHSItems = rhs.GetItems();
      
      int i;
      for ( i = 0; i < 4; i++)
      {
          pTempItems[i * 4 + 0] = _items[i * 4 + 0] * pRHSItems[ 0 * 4 + 0] +
          _items[i * 4 + 1] * pRHSItems[ 1 * 4 + 0] +
          _items[i * 4 + 2] * pRHSItems[ 2 * 4 + 0] +
          _items[i * 4 + 3] * pRHSItems[ 3 * 4 + 0];
          
          pTempItems[i * 4 + 1] = _items[i * 4 + 0] * pRHSItems[ 0 * 4 + 1] +
          _items[i * 4 + 1] * pRHSItems[ 1 * 4 + 1] +
          _items[i * 4 + 2] * pRHSItems[ 2 * 4 + 1] +
          _items[i * 4 + 3] * pRHSItems[ 3 * 4 + 1];
          
          pTempItems[i * 4 + 2] = _items[i * 4 + 0] * pRHSItems[ 0 * 4 + 2] +
          _items[i * 4 + 1] * pRHSItems[ 1 * 4 + 2] +
          _items[i * 4 + 2] * pRHSItems[ 2 * 4 + 2] +
          _items[i * 4 + 3] * pRHSItems[ 3 * 4 + 2];
          
          pTempItems[i * 4 + 3] = _items[i * 4 + 0] * pRHSItems[ 0 * 4 + 3] +
          _items[i * 4 + 1] * pRHSItems[ 1 * 4 + 3] +
          _items[i * 4 + 2] * pRHSItems[ 2 * 4 + 3] +
          _items[i * 4 + 3] * pRHSItems[ 3 * 4 + 3];
      } // End for    
      
      memcpy( (void*)_items, (const void*)pTempItems, sizeof(_items) );
      
      return *this;
  }
  
  void SetItems( Type m00, Type m01, Type m02, Type m03,
                 Type m10, Type m11, Type m12, Type m13,
                 Type m20, Type m21, Type m22, Type m23,
                 Type m30, Type m31, Type m32, Type m33 )
  {
      _items[0*4+0] = m00; _items[0*4+1] = m01; _items[0*4+2] = m02; _items[0*4+3] = m03;
      _items[1*4+0] = m10; _items[1*4+1] = m11; _items[1*4+2] = m12; _items[1*4+3] = m13;
      _items[2*4+0] = m20; _items[2*4+1] = m21; _items[2*4+2] = m22; _items[2*4+3] = m23;
      _items[3*4+0] = m30; _items[3*4+1] = m31; _items[3*4+2] = m32; _items[3*4+3] = m33;
  }

};

template<class Type> 
const cMMatrix3D<Type> cMMatrix3D<Type>::g_Identity( 1,0,0,0,
													 0,1,0,0,
													 0,0,1,0,
													 0,0,0,1 );

} // End of namespace Maximus
  
#endif
