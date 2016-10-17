/*
 Copyright (C) 2015 Apple Inc. All Rights Reserved.
 See LICENSE.txt for this sample’s licensing information
 
 Abstract:
 The application delegate.
 */

#version 150

uniform mat4 projectionMatrix;
uniform mat4 cameraMatrix;
uniform mat4 orientationMatrix;
uniform vec4 color;

in vec3 inNormal;
in vec4 inPosition;

out vec3 normal, position;
out vec4 frontColor;


void main() {
	mat4 mv = cameraMatrix * orientationMatrix;
	normal = vec3(mv * vec4(inNormal, 0.0));
    position = vec3(mv * inPosition);
    gl_Position = projectionMatrix * mv * inPosition;
    frontColor = color;
}