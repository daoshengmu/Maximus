/*
 Copyright (C) 2015 Apple Inc. All Rights Reserved.
 See LICENSE.txt for this sample’s licensing information
 
 Abstract:
 The application delegate.
 */

#version 150

uniform sampler2D displayTex;

in vec3 texCoord;
out vec4 fragColor;

void main()
{
    // Retrieve a color from the texture for the resulting fragment
    fragColor = texture(displayTex, texCoord.st);
}
