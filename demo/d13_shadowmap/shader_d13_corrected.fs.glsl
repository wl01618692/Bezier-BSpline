#version 330 core

// Interpolated values from the vertex shaders
in vec2 UV;
in vec3 normal_cameraspace;
in vec3 light_direction_cameraspace;
in vec4 shadow_coord;

// Ouput data
layout(location = 0) out vec3 color;

// Values that stay constant for the whole mesh.
uniform sampler2D color_map;
uniform sampler2DShadow shadow_map;
uniform bool spot_light;
uniform bool dynamic_bias;

vec2 poissonDisk[16] = vec2[]( 
   vec2( -0.94201624, -0.39906216  ), 
   vec2( 0.94558609, -0.76890725   ), 
   vec2( -0.094184101, -0.92938870 ), 
   vec2( 0.34495938, 0.29387760    ), 
   vec2( -0.91588581, 0.45771432   ), 
   vec2( -0.81544232, -0.87912464  ), 
   vec2( -0.38277543, 0.27676845   ), 
   vec2( 0.97484398, 0.75648379    ), 
   vec2( 0.44323325, -0.97511554   ), 
   vec2( 0.53742981, -0.47373420   ), 
   vec2( -0.26496911, -0.41893023  ), 
   vec2( 0.79197514, 0.19090188    ), 
   vec2( -0.24188840, 0.99706507   ), 
   vec2( -0.81409955, 0.91437590   ), 
   vec2( 0.19984126, 0.78641367    ), 
   vec2( 0.14383161, -0.14100790   ) 
);

// Returns a random number based on a vec3 and an int.
float random(vec3 seed, int i){
	vec4 seed4 = vec4(seed,i);
	float dot_product = dot(seed4, vec4(12.9898,78.233,45.164,94.673));
	return fract(sin(dot_product) * 43758.5453);
}

void main(){

	// Material properties
	vec3 material_diffuse_color = texture(color_map, UV).rgb;

	// Normal of the computed fragment, in camera space
	vec3 n = normalize( normal_cameraspace );
	// Direction of the light (from the fragment to the light)
	vec3 l = normalize( light_direction_cameraspace );
	// Cosine of the angle between the normal and the light direction, 
	// clamped above 0
	//  - light is at the vertical of the triangle -> 1
	//  - light is perpendiular to the triangle -> 0
	//  - light is behind the triangle -> 0
	float cos_theta = clamp(dot(n,l), 0,1);
	
	// Fixed bias, or...
	float bias;
	if (!dynamic_bias) {
		bias = 0.005;
	}
	// ...variable bias
	else {
		bias = 0.005*tan(acos(cos_theta));
		bias = clamp(bias, 0,0.01);
	}

	// Sample the shadow map 4 times
	float visibility = 1.0;
	for (int i = 0; i < 4; i++){
		// use either :
		//  - Always the same samples.
		//    Gives a fixed pattern in the shadow, but no noise
		int index = i;
		//  - A random sample, based on the pixel's screen location. 
		//    No banding, but the shadow moves with the camera, which looks weird.
		// int index = int(16.0 * random(gl_FragCoord.xyy, i))%16;
		//  - A random sample, based on the pixel's position in world space.
		//    The position is rounded to the millimeter to avoid too much aliasing
		// int index = int(16.0*random(floor(Position_worldspace.xyz*1000.0), i))%16;
		
		// being fully in the shadow will eat up 4*0.2 = 0.8
		// 0.2 potentially remain, which is quite dark.
		vec4 shadow_uv = vec4(vec3(shadow_coord.xy + poissonDisk[index]/700.0, shadow_coord.z - bias), shadow_coord.w);
		if (!spot_light) {
			visibility -= 0.2*(1.0 - texture(shadow_map, vec3(shadow_uv.xy, shadow_uv.z/shadow_uv.w)));
		} 
		// For spot lights, use either one of these lines instead.
		else {
			// visibility -= 0.2*(1.0 - texture(shadow_map, shadow_uv.xyz/shadow_uv.w));
			visibility -= 0.2*(1.0 - textureProj(shadow_map, shadow_uv));
		}
	}

	color = visibility * material_diffuse_color;

}