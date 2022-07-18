#version 330 core

in vec3 vp_modelspace;

uniform mat4 depth_MVP;

void main(){
	gl_Position = depth_MVP * vec4(vp_modelspace,1);
}
