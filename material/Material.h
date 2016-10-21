/*
 *  Material.h
 *  Maximus
 *
 *  Created by User on 11/17/16.
 *  Copyright 2011 Daosheng Mu. All rights reserved.
 *
 */

#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "Util/MUtils.h"

namespace Maximus {

class IMGraphics;
  
class Material
{
public:
  Material() {}
  virtual ~Material() {
    glDeleteShader(_shader);
  }
  virtual bool CreateShader(IMGraphics* aGraphics) = 0;
  
protected:
  GShader _shader;
  // TODO: Constant table
  // TODO: Render state
  // TODO: Textures
  
private:
  GShader GetShader() {return _shader;}
  
  friend class cMGraphicsOSX;
};

} // End of namespace Maximus

#endif /* __MATERIAL_H__ */
