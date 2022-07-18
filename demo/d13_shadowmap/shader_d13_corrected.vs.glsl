#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vp_modelspace;
layout(location = 1) in vec2 vt;
layout(location = 2) in vec3 vn_modelspace;

// Output data ; will be interpolated for each fragment.
out vec2 UV;
out vec3 normal_cameraspace;
out vec3 light_direction_cameraspace;
out vec4 shadow_coord;

// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform mat4 V;
uniform mat4 M;
uniform vec3 light_inv_direction_worldspace;
uniform mat4 depth_bias_MVP;


void main(){

	// Output position of the vertex, in clip space : MVP * position
	gl_Position = MVP * vec4(vp_modelspace,1);
	
	shadow_coord = depth_bias_MVP * vec4(vp_modelspace,1);

	// Vector that goes from the vertex to the light, in camera space
	light_direction_cameraspace = (V*vec4(light_inv_direction_worldspace,0)).xyz;
	
	// Normal of the the vertex, in camera space
	normal_cameraspace = (V * M * vec4(vn_modelspace,0)).xyz; // Only correct if ModelMatrix does not scale the model ! Use its inverse transpose if not.
	
	// UV of the vertex. No special space for this one.
	UV = vt;
}

