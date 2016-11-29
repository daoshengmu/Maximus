/*
 *  MMatrix3D.h
 *  Maximous
 *
 *  Created by User on 5/29/11.
 *  Copyright 2011 Daosheng Mu. All rights reserved.
 *
 */

#ifndef __M_QUATERNION_H__
#define __M_QUATERNION_H__

namespace Maximus
{

template<class Type>
class MQuaternion
{
public:
  MQuaternion()
   : x(0), y(0), z(0), w(1)
  {}
  
  MQuaternion(const MQuaternion<Type>& rhs)
   : x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w)
  {}

  MQuaternion(Type aX, Type aY, Type aZ, Type aW)
   : x(aX), y(aY), z(aZ), w(aW)
  {}

  ~MQuaternion()
  {}
  
  MQuaternion<Type> operator + (const MQuaternion<Type>& aIn) const
  {
    return MQuaternion<Type>(x + aIn.x, y + aIn.y, z + aIn.z, w + aIn.w);
  }

  MQuaternion<Type>& operator += (const MQuaternion<Type>& aIn)
  {
    x += aIn.x;
    y += aIn.y;
    z += aIn.z;
    w += aIn.w;
    
    return *this;
  }

  MQuaternion<Type> operator - (const MQuaternion<Type>& aIn) const
  {
    return MQuaternion<Type>(x - aIn.x, y - aIn.y, z - aIn.z, w - aIn.w);
  }

  MQuaternion<Type>& operator -= (const MQuaternion<Type>& aIn)
  {
    x -= aIn.x;
    y -= aIn.y;
    z -= aIn.z;
    w -= aIn.w;
    
    return *this;
  }
  
  MQuaternion<Type> operator * (const MQuaternion<Type>& aIn) const
  {
    return MQuaternion<Type>(y * aIn.z - z * aIn.y + x * aIn.w + w * aIn.x,
                            z * aIn.x - x * aIn.z + y * aIn.w + w * aIn.y,
                            x * aIn.y - y * aIn.x + z * aIn.w + w * aIn.z,
                            w * aIn.w - x * aIn.x - y * aIn.y - z * aIn.z);
  }

  MQuaternion<Type>& operator *= (const MQuaternion<Type>& aIn)
  {
    Type rX, rY, rZ, rW;
    
    rX = y * aIn.z - z * aIn.y + x * aIn.w + w * aIn.x;
    rY = z * aIn.x - x * aIn.z + y * aIn.w + w * aIn.y;
    rZ = x * aIn.y - y * aIn.x + z * aIn.w + w * aIn.z;
    rW = w * aIn.w - x * aIn.x - y * aIn.y - z * aIn.z;
    
    x = rX;
    y = rY;
    z = rZ;
    w = rW;
    
    return *this;
  }
  
  MQuaternion<Type> operator * (Type aScale) const
  {
    return MQuaternion<Type>(x * aScale, y * aScale, z * aScale, w * aScale);
  }

  MQuaternion& operator *= (Type aScale)
  {
    x *= aScale;
    y *= aScale;
    z *= aScale;
    w *= aScale;
    
    return (*this);
  }

  Type Norm() const
  {
    Type sum = x*x + y*y + z*z + w*w;
    return sqrt( sum );
  }

  void Normalize()
  {
    Type norm = Norm();
    Type inv = 1 / norm;
    
    x *= inv;
    y *= inv;
    z *= inv;
    w *= inv;
  }

  void Conjugate()
  {
    x *= -1;
    y *= -1;
    z *= -1;
  }

  void Inverse()
  {
    Type d = x*x + y*y + z*z + w*w;
    Type inv = 1 / d;
    
    x = -x * inv;
    y = -y * inv;
    z = -z * inv;
    w =  w * inv;
  }

  void Slerp(const MQuaternion<Type>& aIn, Type aT, MQuaternion<Type>& aOut)
  {
    (const_cast<const MQuaternion<Type>& >(*this)).Slerp(aIn, aT, aOut);
  }
  
  void Slerp(const MQuaternion<Type>& aIn, Type aT, MQuaternion<Type>& aOut) const
  {
    if (aT < 0) {
      aT = 0;
    }
    else if (aT > 1) {
      aT = 1;
    }
    
    MQuaternion<Type> rhs2 = aIn;
    Type v = x * aIn.x + y * aIn.y + z * aIn.z + w * aIn.w;
    
    if (v < 0)
    {
      v = -v;
      rhs2 *= -1;
    }
    
    if (v > 1)
    {
      v = 1;
    }
    
    Type angle = acos(v);
    
    if (angle == 0)
    {
      aOut.x = aIn.x;
      aOut.y = aIn.y;
      aOut.z = aIn.z;
      aOut.w = aIn.w;
      
      return;
    }
    
    Type a = sin(angle * (1 - aT));
    Type b = sin(angle * aT);
    Type c = 1 / sin(angle);
    
    Type l = a * c;
    Type r = b * c;
    
    aOut.x = l * x + r * rhs2.x;
    aOut.y = l * y + r * rhs2.y;
    aOut.z = l * z + r * rhs2.z;
    aOut.w = l * w + r * rhs2.w;
  }

  cMMatrix3D<Type> CovertToMatrix3D() const
  {
    cMMatrix3D<Type> out;
    
    Type *pEntries = out.GetItems();
    
    pEntries[4 * 0 + 0] = 1 - 2 * (y * y + z * z);
    pEntries[4 * 0 + 1] = 2 * (x * y + w * z);
    pEntries[4 * 0 + 2] = 2 * (x * z - w * y);
    pEntries[4 * 0 + 3] = 0;
    
    pEntries[4 * 1 + 0] = 2 * (x * y - w * z);
    pEntries[4 * 1 + 1] = 1 - 2 * (x*x + z * z);
    pEntries[4 * 1 + 2] = 2 * (y * z + w * x);
    pEntries[4 * 1 + 3] = 0;
    
    pEntries[4 * 2 + 0] = 2 * (x * z + w * y);
    pEntries[4 * 2 + 1] = 2 * (y * z - w * x);
    pEntries[4 * 2 + 2] = 1 - 2 * (x * x + y * y);
    pEntries[4 * 2 + 3] = 0;
    
    pEntries[4 * 3 + 0] = 0;
    pEntries[4 * 3 + 1] = 0;
    pEntries[4 * 3 + 2] = 0;
    pEntries[4 * 3 + 3] = 1;
    
    return out;
  }

  void SetZero()
  {
    x = y = z = w = 0;
  }

  void ConvertFromMatrix3D(const cMMatrix3D<Type>& aMtx)
  {
    const float qw2 = 0.25f * (aMtx.GetEntries()[0] + aMtx.GetEntries()[5] + aMtx.GetEntries()[10] + 1.0f);
    const float qx2 = qw2 - 0.5f	* (aMtx.GetEntries()[5]  + aMtx.GetEntries()[10]);
    const float qy2 = qw2 - 0.5f	* (aMtx.GetEntries()[10] + aMtx.GetEntries()[0]);
    const float qz2 = qw2 - 0.5f	* (aMtx.GetEntries()[0]  + aMtx.GetEntries()[5]);
    
    const int i = (qw2 > qx2) ?
    ((qw2 > qy2) ? ((qw2 > qz2) ? 0 : 3) : ((qy2 > qz2) ? 2 : 3)) :
    ((qx2 > qy2) ? ((qx2 > qz2) ? 1 : 3) : ((qy2 > qz2) ? 2 : 3));
    
    switch (i)
    {
      case 0:
      {
        w = (float)sqrt(qw2);
        const float tmp = 0.25f / w;
        x = (aMtx.GetEntries()[6] - aMtx.GetEntries()[9]) * tmp;
        y = (aMtx.GetEntries()[8] - aMtx.GetEntries()[2]) * tmp;
        z = (aMtx.GetEntries()[1] - aMtx.GetEntries()[4]) * tmp;
        break;
      }
        
      case 1:
      {
        x = (float)sqrt(qx2);
        const float tmp = 0.25f / x;
        w = (aMtx.GetEntries()[6] - aMtx.GetEntries()[9]) * tmp;
        y = (aMtx.GetEntries()[4] - aMtx.GetEntries()[1]) * tmp;
        z = (aMtx.GetEntries()[8] - aMtx.GetEntries()[2]) * tmp;
        break;
      }
        
      case 2:
      {
        y = (float)sqrt(qy2);
        const float tmp = 0.25f / y;
        w = (aMtx.GetEntries()[8] - aMtx.GetEntries()[2]) * tmp;
        z = (aMtx.GetEntries()[9] - aMtx.GetEntries()[6]) * tmp;
        x = (aMtx.GetEntries()[1] - aMtx.GetEntries()[4]) * tmp;
        break;
      }
        
      case 3:
      {
        z = (float)sqrt(qz2);
        const float tmp = 0.25f / z;
        w = (aMtx.GetEntries()[1] - aMtx.GetEntries()[4]) * tmp;
        x = (aMtx.GetEntries()[2] - aMtx.GetEntries()[8]) * tmp;
        y = (aMtx.GetEntries()[6] - aMtx.GetEntries()[9]) * tmp;
        break;
      }
    }
    
    if ( w < 0 ) *this = SetMinus(*this);
    
    Normalize();
  }

  void SetIdentity()
  {
    x = y = z = w = 1;
  }

  void GetAxisAngle(const cMVector3D<Type>& aAxis, float aAngle) const
  {
    Type sum = x*x + y*y + z*z;
    
    if ( sum < 1.0e-6f )
    {
      aAngle = 0.0f;
      aAxis = cMVector3D<float>(1.0f, 0.0f, 0.0f);
      return;
    }
    
    float oneOver = 1.0f/(float)sqrtf(sum);
    aAxis = cMVector3D<float>(oneOver * x, oneOver * y, oneOver * z);
    float w1 = (float)w;
    
    if (std::abs(w1 - 1.0f) < 1.0e-6f)
    {
      aAngle = 0.0f;
    }
    else
    {
      aAngle = 2.0f * (float)acosf(w1);
    }
  }

  MQuaternion<Type>& SetMinus(const MQuaternion<Type>&aQ)
  {
    x = -aQ.x;
    y = -aQ.y;
    z = -aQ.z;
    w = -aQ.w;
    return (*this);
  }

  MQuaternion<Type>& SetQuat(const cMVector3D<Type>& aVec, float aW)
  {
    x = aVec.x;
    y = aVec.y;
    z = aVec.z;
    w = aW;
    
    return (*this);
  }

  MQuaternion<Type>& SetQuat(float aAngle, const cMVector3D<Type>& axis)
  {
    float halfAngle = aAngle * 0.5f;
    float sinHalfAngle = sinf(halfAngle);
    float cosHalfAngle = cosf(halfAngle);
    cMVector3D<float> tmp = axis * sinHalfAngle;
    
    SetQuat(tmp, cosHalfAngle);
    
    return (*this);
  }
  
  cMVector3D<Type> XAxis() const
  {
    const Type ty  = y * 2;
    const Type tz  = z * 2;
    const Type twy = ty * w;
    const Type twz = tz * w;
    const Type txy = ty * x;
    const Type txz = tz * x;
    const Type tyy = ty * y;
    const Type tyz = tz * y;
    const Type tzz = tz * z;
    
    return cMVector3D<Type>(1.0f - (tyy + tzz), txy-twz, txz+twy);
  }

  cMVector3D<Type> YAxis() const
  {
    const Type tx  = x * 2;
    const Type ty  = y * 2;
    const Type tz  = z * 2;
    const Type twx = tx * w;
    const Type twy = ty * w;
    const Type twz = tz * w;
    const Type txx = tx * x;
    const Type txy = ty * x;
    const Type tyz = tz * y;
    const Type tzz = tz * z;
    
    return cMVector3D<Type>(txy + twz, 1.0f - (txx + tzz), tyz - twx);
  }

  cMVector3D<Type> ZAxis() const
  {
    const Type tx  = x * 2;
    const Type ty  = y * 2;
    const Type tz  = z * 2;
    const Type twx = tx * w;
    const Type twy = ty * w;
    const Type txx = tx * x;
    const Type txz = tz * x;
    const Type tyy = ty * y;
    const Type tyz = tz * y;
    
    return cMVector3D<Type>(txz - twy, tyz + twx, 1.0f-(txx + tyy));
  }

  cMVector3D<Type> TransformVector3D(const cMVector3D<Type>& aV) const
  {
    MQuaternion<Type> inv(x, y, z, w);
    inv.Inverse();
    
    MQuaternion<Type> input(aV.x, aV.y, aV.z, 0);
    MQuaternion<Type> output = (*this) * input * inv;
    
    return MQuaternion<Type>(output.x, output.y, output.z);
  }

  Type x;
  Type y;
  Type z;
  Type w;
};
} // End of namespace Maximus

#endif // __M_QUATERNION_H__
