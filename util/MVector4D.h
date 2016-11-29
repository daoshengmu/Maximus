/*
 *  MVector4D.h
 *  Maximus
 *
 *  Created by User on 5/22/11.
 *  Copyright 2011 Daosheng Mu. All rights reserved.
 *
 */

#ifndef __M_VECTOR4D_H__
#define __M_VECTOR4D_H__

namespace Maximus
{
  
  template <class Type>
  class cMVector4D
  {
  public:
    Type x;
    Type y;
    Type z;
    Type w;
    
  public:
    //--------------------------------
    // @breif: Constructor
    //--------------------------------
    cMVector4D(): x(0), y(0), z(0), w(0) {};
    
    //--------------------------------
    // @breif: Destructor
    //--------------------------------
    ~cMVector4D() {};
    
    //--------------------------------
    // @breif: Constructor
    // @params: xVal x element
    // @params: yVal y element
    // @params: yVal z element
    // @params: wVal w element
    //--------------------------------
    cMVector4D(Type xVal, Type yVal, Type zVal, Type wVal)
    : x(xVal), y(yVal), z(zVal), w(wVal){};
    
    //---------------------------------------∫∫-----------------------------------------------
    /// @brief Copy constructor
    ///
    /// @param rhs copy from
    //--------------------------------------------------------------------------------------
    cMVector4D(const cMVector4D<Type>& rhs)
    : x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w) {};
    
    
    void Scale(Type val)
    {
      x *= val;
      y *= val;
      z *= val;
      w *= val;
    }
    
    cMVector4D<Type>& operator *= (Type val)
    {
      x *= val;
      y *= val;
      z *= val;
      w *= val;
      
      return (*this);
    }
    
  };
} //  End of namespace Maximus

#endif // __M_VECTOR4D_H__
