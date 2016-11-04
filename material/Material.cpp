//
//  Material.cpp
//  Maximus
//
//  Created by User on 11/17/16.
//  Copyright 2011 Daosheng Mu. All rights reserved.
//

#include "material/Material.h"

namespace Maximus {
  
Material::Material()
 : mColor(1.0f, 1.0f, 1.0f, 1.0f)
{
}
  
const cMVector4Df& Material::GetMaterialColor()
{
  return mColor;
}
  
void Material::SetMaterialColor(const cMVector4Df& aColor)
{
  mColor = aColor;
}

} // End of namespace Maximus
