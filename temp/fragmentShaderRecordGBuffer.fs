/*
 Copyright (C) 2015 Apple Inc. All Rights Reserved.
 See LICENSE.txt for this sample’s licensing information
 
 Abstract:
 The application delegate.
 */

#version 150

in vec3 normal, position;
in vec4 frontColor;

out vec4 fragColor;
out vec3 fragPosition;
out vec2 fragNormal;

void main()
{
	vec3 n = normalize(normal);
    fragPosition = position.xyz;
    fragColor =  frontColor;
    fragNormal = n.xy;
}
