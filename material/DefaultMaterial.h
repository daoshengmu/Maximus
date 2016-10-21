/*
 *  DefaultMaterial.h
 *  Maximus
 *
 *  Created by User on 11/17/16.
 *  Copyright 2011 Daosheng Mu. All rights reserved.
 *
 */

#ifndef __DEFAULT_MATERIAL_H__
#define __DEFAULT_MATERIAL_H__

#include "Util/MUtils.h"
#include "material/Material.h"

namespace Maximus {
class IMGraphics;
  
class DefaultMaterial : public Material
{
public:
  DefaultMaterial() {}
  virtual ~DefaultMaterial() {};
  virtual bool CreateShader(IMGraphics* aGraphics) override;

  // TODO: Render state
  // TODO: Textures
};

} // End of namespace Maximus

#endif /* __MATERIAL_H__ */
