//
//  DefaultShader.h
//  MaximusOSX
//
//  Created by Daosheng Mu on 2/21/16.
//
//

#ifndef DefaultShader_h
#define DefaultShader_h

//#include <string.h>
//#include <iostream>

class BasicShader
{
public:
    
  //--------------------------------------------------------------------------------------
  /// @brief Constructor, write shader here
  //--------------------------------------------------------------------------------------
  BasicShader()
  {
      _vertexShader =
      "#version 150 \n"
      "in vec3 g_vPositionOS; \n"
      "in vec4 g_vColorOS; \n"
      
      "uniform mat4 g_worldViewProjMatrix; \n"
      
      "out vec4 outColor; \n"
      "\n"
      "void main(void) \n"
      "{ \n"
      " gl_Position = g_worldViewProjMatrix * vec4( g_vPositionOS, 1.0 ); \n"
      " outColor = g_vColorOS;"
      "} \n";
      
      _fragmentShader =
      "#version 150 \n"
      "in vec4 outColor; \n"
      "out vec4 fragColor; \n"
      "\n"
      "void main(void) \n"
      "{ \n"
      " fragColor = outColor; \n"
      "} \n";
  }
  
  //--------------------------------------------------------------------------------------
  /// @brief Get vertex shader
  ///
  /// @return vertex shader
  //-------------------------------------------------------------------------------------
  const std::string* GetVertexShader() { return &_vertexShader; }
  
  
  //--------------------------------------------------------------------------------------
  /// @brief Get fragment shader
  ///  
  /// @return fragement shader
  //--------------------------------------------------------------------------------------
  const std::string* GetFragmentShader() { return &_fragmentShader; }
    
private:
  std::string _vertexShader;
  std::string _fragmentShader;
    
};

#endif /* DefaultShader_h */
