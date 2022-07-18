#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vp_modelspace;
layout(location = 1) in vec2 vt;
layout(location = 2) in vec3 vn_modelspace;

// Output data ; will be interpolated for each fragment.
out vec2 UV;
out vec4 shadow_coord;
out vec3 normal_modelspace;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform mat4 depth_bias_MVP;


void main(){

	// Output position of the vertex, in clip space : MVP * position
	gl_Position =  MVP * vec4(vp_modelspace,1);
	
	shadow_coord = depth_bias_MVP * vec4(vp_modelspace,1);
	
	// UV of the vertex. No special space for this one.
	UV = vt;

	normal_modelspace = vn_modelspace;
}

