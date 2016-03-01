/*
 Copyright (C) 2015 Apple Inc. All Rights Reserved.
 See LICENSE.txt for this sample’s licensing information
 
 Abstract:
 The application delegate.
 */

#version 150

in vec4 inPosition;
in vec3 inTexcoord;

out vec3 texCoord;

void main()
{
    gl_Position = inPosition;
    texCoord = inTexcoord;
}
