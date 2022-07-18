#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vp_modelspace;

void main(){
    gl_Position.xyz = vp_modelspace;
    gl_Position.w = 1.0;
}

