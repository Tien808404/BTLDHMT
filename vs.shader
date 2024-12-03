//vs.shader
#version 460

layout(location = 0) in vec4 vertex_position;
layout(location = 1) in vec4 vertex_color;
layout(location = 2) in vec4 vertex_normal;

uniform mat4 projection_mat_shader;
uniform mat4 view_mat_shader;
uniform mat4 model_mat_shader;

uniform int color;

out vec3 position_eye;
out vec3 normal_eye;

out vec4 fragment_color;

void main(void)
{
	position_eye = vec3(view_mat_shader * model_mat_shader * vertex_position);
	normal_eye = vec3(view_mat_shader * model_mat_shader * vertex_normal);
	
	if (color == 1)    fragment_color = vec4(0.48, 0.21, 0.1, 1.0); //brown
	if (color == 2)    fragment_color = vec4(0.23, 0.23, 0.23, 1.0); //grey  
	if (color == 3)    fragment_color = vec4(0.75, 0.02, 0.02, 1.0); //red
	
	if (color == 4)    fragment_color = vec4(0.02, 0.75, 0.02, 1.0); //blue
	if (color == 5)    fragment_color = vec4(0, 1, 0, 1); //green
	if (color == 6)    fragment_color = vec4(0.196078443137, 0.50980392157, 0.96470588235, 0); //dark blue
	if (color == 7)    fragment_color = vec4(0.80, 0.25, 0.03, 1.0); //orange  
	if (color == 8)    fragment_color = vec4(0.02, 0.68, 0.65, 1.0); //greenagai
	if (color == 9)    fragment_color = vec4(0.7, 0.7, 0.7, 0);//glass
	if (color == 10)   fragment_color = vec4(0.75, 0.75, 0.75, 1.0);//sliver
	if (color == 11)   fragment_color = vec4(1.0, 1.0, 0.75, 1.0);//yellowlight
	if (color == 12)   fragment_color = vec4(0.83, 0.83, 0.83, 1.0);//lightgray
	if (color == 13)   fragment_color = vec4(0.803921568627451, 0.5215686274509804, 0.2470588235294118, 1.0);//peru
	if (color == 14)   fragment_color = vec4(0.95, 0.95, 0.90, 1.0);//yellow_kem
	if (color == 15)   fragment_color = vec4(0.94, 0.9, 0.55, 0.01);//khaki
	if (color == 16)   fragment_color = vec4(0.45098039216, 0.98431372549, 0.99215686275, 0);//skyblue

	if (color == 98)   fragment_color = vec4(0.95, 0.95, 0.90, 1.0); //white
	if (color == 99)   fragment_color = vec4(0.03, 0.03, 0.03, 1.0); //black

	gl_Position = projection_mat_shader * vec4(position_eye, 1.0);
}
