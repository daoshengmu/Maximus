//
//  DefaultMaterial.cpp
//  Maximus
//
//  Created by User on 11/17/16.
//  Copyright 2011 Daosheng Mu. All rights reserved.
//
#include "material/DefaultMaterial.h"
#include "interface/IMGraphics.h"
#include "shader/BasicShader.h"


namespace Maximus {
  
bool DefaultMaterial::CreateShader(IMGraphics* aGraphics)
{
  // Init shader
  BasicShader shader;
  
  if (!aGraphics->CreateShader(shader.GetVertexShader()->c_str(),
                               shader.GetFragmentShader()->c_str(),
                               &_shader)) {
    assert(false);
    return false;
  }
  
  return true;
}

} // End of namespace Maximus
