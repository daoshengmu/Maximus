/*
 *  MVector3D.h
 *  Maximus
 *
 *  Created by User on 5/22/11.
 *  Copyright 2011 Daosheng Mu. All rights reserved.
 *
 */

#ifndef __MVECTOR3D_H__
#define __MVECTOR3D_H__


template <class Type>
class cMVector3D
{
public:
	Type x;
	Type y;
	Type z;
	
public:
	//--------------------------------
	// @breif: Constructor
	//--------------------------------
	cMVector3D(): x(0), y(0), z(0) {};
	
	//--------------------------------
	// @breif: Destructor
	//--------------------------------
	~cMVector3D() {};
	
	//--------------------------------
	// @breif: Constructor
	// @params: xVal x element 
	// @params: yVal y element 
	// @params: yVal z element 
	//--------------------------------
 	cMVector3D(Type xVal, Type yVal, Type zVal)
	: x(xVal), y(yVal), z(zVal) {};
	
	//---------------------------------------∫∫-----------------------------------------------
    /// @brief Copy constructor
    /// 
    /// @param rhs copy from
    //--------------------------------------------------------------------------------------
	cMVector3D(const cMVector3D<Type>& rhs)
	: x(rhs.x), y(rhs.y), z(rhs.z) {};
	
	
	void scale( Type val )
	{
		x *= val;
		y *= val;
		z *= val;
	}
    
    cMVector3D<Type>& operator *= (Type val)
    {
        x *= val;
        y *= val;
        z *= val;
        
        return (*this);
    }

};

#endif
