#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vp_modelspace;

out vec3 face_color;

void main(){

	// Output position of the vertex, in clip space : Matrix * position
	gl_Position = vec4(vp_modelspace,1);
	
	face_color = vec3(vp_modelspace.z, 1, 0);

}