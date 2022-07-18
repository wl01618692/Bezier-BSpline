#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;
in vec4 shadow_coord;
in vec3 normal_modelspace;

// Ouput data
layout(location = 0) out vec3 color;

// Values that stay constant for the whole mesh.
uniform sampler2D color_map;
uniform sampler2DShadow shadow_map;
uniform bool spot_light;

void main(){

	// Light emission properties
	vec3 light_color = vec3(1,1,1);
	
	// Material properties
	vec3 material_diffuse_color = texture(color_map, UV).rgb;

	float visibility;
	if (!spot_light) {
		visibility = texture(shadow_map, vec3(shadow_coord.xy, (shadow_coord.z)/shadow_coord.w));
	} else {
		visibility = texture(shadow_map, shadow_coord.xyz/shadow_coord.w);
	}

	color = visibility * material_diffuse_color * light_color;

}
