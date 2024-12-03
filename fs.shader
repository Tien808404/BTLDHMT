//fs.shader
//fs.shader
#version 460

in vec3 position_eye, normal_eye;
uniform mat4 view_mat_shader;

in vec4 fragment_color;
out vec4 out_color;

// Các bi?n uniform ?? b?t/t?t t?ng ngu?n sáng
uniform bool enable_light_1; // B?t/t?t ngu?n sáng 1
uniform bool enable_light_2; // B?t/t?t ngu?n sáng 2

void main() {
    vec3 final_color = vec3(0);

    //-----------Ngu?n sáng 1-------------
    if (enable_light_1) {
        vec3 light_position_world_1 = vec3(0.0, 2.27, -3.0);
        vec3 light_position_eye_1 = vec3(view_mat_shader * vec4(light_position_world_1, 1.0));
        vec3 position_viewer = vec3(0.0, 0.0, 0.0);
        vec3 n_eye = normalize(normal_eye);

        vec3 distance_to_light_eye_1 = light_position_eye_1 - position_eye;
        vec3 direction_to_light_eye_1 = normalize(distance_to_light_eye_1);
        vec3 surface_to_viewer_eye_1 = normalize(position_viewer - position_eye);

        float dot_prod_1 = max(dot(direction_to_light_eye_1, n_eye), 0.0);
        vec3 Ld_1 = vec3(0.7, 0.7, 0.7);
        vec3 Kd_1 = vec3(1.0, 1.0, 1.0);
        vec3 Id_1 = Ld_1 * Kd_1 * dot_prod_1;

        vec3 half_way_eye_1 = normalize(surface_to_viewer_eye_1 + direction_to_light_eye_1);
        float dot_prod_specular_1 = max(dot(half_way_eye_1, n_eye), 0.0);
        float specular_factor_1 = pow(dot_prod_specular_1, 20.0);
        vec3 Ls_1 = vec3(0.2, 0.2, 0.2);
        vec3 Ks_1 = vec3(1.0, 1.0, 1.0);
        vec3 Is_1 = Ls_1 * Ks_1 * specular_factor_1;

        vec3 La_1 = vec3(0.2, 0.2, 0.2);
        vec3 Ka_1 = vec3(1.0, 1.0, 1.0);
        vec3 Ia_1 = La_1 * Ka_1;

        final_color += (Is_1 + Id_1 + Ia_1);
    }
    else{
        vec3 light_position_world_1 = vec3(0.0, 2.27, 1.0);
        vec3 light_position_eye_1 = vec3(view_mat_shader * vec4(light_position_world_1, 1.0));
        vec3 position_viewer = vec3(0.0, 0.0, 0.0);
        vec3 n_eye = normalize(normal_eye);

        vec3 distance_to_light_eye_1 = light_position_eye_1 - position_eye;
        vec3 direction_to_light_eye_1 = normalize(distance_to_light_eye_1);
        vec3 surface_to_viewer_eye_1 = normalize(position_viewer - position_eye);

        float dot_prod_1 = max(dot(direction_to_light_eye_1, n_eye), 0.0);
        vec3 Ld_1 = vec3(0,0,0);
        vec3 Kd_1 = vec3(0,0,0);
        vec3 Id_1 = Ld_1 * Kd_1 * dot_prod_1;

        vec3 half_way_eye_1 = normalize(surface_to_viewer_eye_1 + direction_to_light_eye_1);
        float dot_prod_specular_1 = max(dot(half_way_eye_1, n_eye), 0.0);
        float specular_factor_1 = pow(dot_prod_specular_1, 20.0);
        vec3 Ls_1 = vec3(0,0,0);
        vec3 Ks_1 = vec3(0,0,0);
        vec3 Is_1 = Ls_1 * Ks_1 * specular_factor_1;

        vec3 La_1 = vec3(0,0,0);
        vec3 Ka_1 = vec3(0,0,0);
        vec3 Ia_1 = La_1 * Ka_1;

        
        final_color += (Is_1 + Id_1 + Ia_1);}

    //-----------Ngu?n sáng 2-------------
    if (enable_light_2) {
        vec3 light_position_world_2 = vec3(2.0, 15.0, 2.0);
        vec3 light_position_eye_2 = vec3(view_mat_shader * vec4(light_position_world_2, 1.0));
        vec3 position_viewer = vec3(0.0, 0.0, 0.0);
        vec3 n_eye = normalize(normal_eye);

        vec3 distance_to_light_eye_2 = light_position_eye_2 - position_eye;
        vec3 direction_to_light_eye_2 = normalize(distance_to_light_eye_2);
        vec3 surface_to_viewer_eye_2 = normalize(position_viewer - position_eye);

        float dot_prod_2 = max(dot(direction_to_light_eye_2, n_eye), 0.0);
        vec3 Ld_2 = vec3(0.7, 0.7, 0.7);
        vec3 Kd_2 = vec3(1, 0.5, 0);
        vec3 Id_2 = Ld_2 * Kd_2 * dot_prod_2;

        vec3 half_way_eye_2 = normalize(surface_to_viewer_eye_2 + direction_to_light_eye_2);
        float dot_prod_specular_2 = max(dot(half_way_eye_2, n_eye), 0.0);
        float specular_factor_2 = pow(dot_prod_specular_2, 50.0);
        vec3 Ls_2 = vec3(0.8, 0.8, 1.0);
        vec3 Ks_2 = vec3(0.7, 0.7, 0.7);
        vec3 Is_2 = Ls_2 * Ks_2 * specular_factor_2;

        vec3 La_2 = vec3(0.1, 0.1, 0.3);
        vec3 Ka_2 = vec3(0.5, 0.5, 0.5);
        vec3 Ia_2 = La_2 * Ka_2;

        
        final_color += (Is_2 + Id_2 + Ia_2);
    }else{
        vec3 light_position_world_2 = vec3(2.0, 15.0, 2.0);
        vec3 light_position_eye_2 = vec3(view_mat_shader * vec4(light_position_world_2, 1.0));
        vec3 position_viewer = vec3(0.0, 0.0, 0.0);
        vec3 n_eye = normalize(normal_eye);

        vec3 distance_to_light_eye_2 = light_position_eye_2 - position_eye;
        vec3 direction_to_light_eye_2 = normalize(distance_to_light_eye_2);
        vec3 surface_to_viewer_eye_2 = normalize(position_viewer - position_eye);

        float dot_prod_2 = max(dot(direction_to_light_eye_2, n_eye), 0.0);
        vec3 Ld_2 = vec3(0,0,0);
        vec3 Kd_2 = vec3(0,0,0);
        vec3 Id_2 = Ld_2 * Kd_2 * dot_prod_2;

        vec3 half_way_eye_2 = normalize(surface_to_viewer_eye_2 + direction_to_light_eye_2);
        float dot_prod_specular_2 = max(dot(half_way_eye_2, n_eye), 0.0);
        float specular_factor_2 = pow(dot_prod_specular_2, 50.0);
        vec3 Ls_2 = vec3(0,0,0);
        vec3 Ks_2 = vec3(0,0,0);
        vec3 Is_2 = Ls_2 * Ks_2 * specular_factor_2;

        vec3 La_2 = vec3(0,0,0);
        vec3 Ka_2 = vec3(0,0,0);
        vec3 Ia_2 = La_2 * Ka_2;

        final_color += (Is_2 + Id_2 + Ia_2);}

    // ------------Màu cu?i cùng t? các ngu?n sáng------------
    out_color = vec4(final_color, 1.0) * fragment_color;
}

/*#version 460

in vec3 position_eye, normal_eye;
uniform mat4 view_mat_shader;

in vec4 fragment_color;
out vec4 out_color;

void main() {
    //-----------ch? ??nh các v? trí ngu?n sáng-------------
    // Ngu?n sáng 1
    vec3 light_position_world_1 = vec3(0.0, 2.27, -3);//trong phòng
    vec3 light_position_eye_1 = vec3(view_mat_shader * vec4(light_position_world_1, 1.0));

    // Ngu?n sáng 2
    vec3 light_position_world_2 = vec3(2.0, 15.0, 2.0);//m?t tr?i
    vec3 light_position_eye_2 = vec3(view_mat_shader * vec4(light_position_world_2, 1.0));

    // V? trí viewer
    vec3 position_viewer = vec3(0.0, 0.0, 0.0);

    // Chu?n hóa normal_eye
    vec3 n_eye = normalize(normal_eye);

    // --------------Ánh sáng t? ngu?n 1---------------------
    vec3 distance_to_light_eye_1 = light_position_eye_1 - position_eye;
    vec3 direction_to_light_eye_1 = normalize(distance_to_light_eye_1);
    vec3 surface_to_viewer_eye_1 = normalize(position_viewer - position_eye);

    float dot_prod_1 = max(dot(direction_to_light_eye_1, n_eye), 0.0);
    vec3 Ld_1 = vec3(0.7, 0.7, 0.7); // Ánh sáng khu?ch tán t? ngu?n 1
    vec3 Kd_1 = vec3(1.0, 0.5, 0.0); // H? s? ph?n x? khu?ch tán t? ngu?n 1
    vec3 Id_1 = Ld_1 * Kd_1 * dot_prod_1;

    vec3 half_way_eye_1 = normalize(surface_to_viewer_eye_1 + direction_to_light_eye_1);
    float dot_prod_specular_1 = max(dot(half_way_eye_1, n_eye), 0.0);
    float specular_factor_1 = pow(dot_prod_specular_1, 100.0); // H? s? sáng bóng t? ngu?n 1
    vec3 Ls_1 = vec3(0.2, 0.2, 0.2);
    vec3 Ks_1 = vec3(1.0, 1.0, 1.0);
    vec3 Is_1 = Ls_1 * Ks_1 * specular_factor_1;

    vec3 La_1 = vec3(0.2, 0.2, 0.2);
    vec3 Ka_1 = vec3(1.0, 1.0, 1.0);
    vec3 Ia_1 = La_1 * Ka_1;

    // --------------Ánh sáng t? ngu?n 2---------------------
    vec3 distance_to_light_eye_2 = light_position_eye_2 - position_eye;
    vec3 direction_to_light_eye_2 = normalize(distance_to_light_eye_2);
    vec3 surface_to_viewer_eye_2 = normalize(position_viewer - position_eye);

    float dot_prod_2 = max(dot(direction_to_light_eye_2, n_eye), 0.0);
    vec3 Ld_2 = vec3(1.5,1.5,1.5);//vec3 Ld_2 = vec3(0.6, 0.6, 0.8); // Ánh sáng khu?ch tán t? ngu?n 2
    vec3 Kd_2 = vec3(0.5, 1.0, 0.5); // H? s? ph?n x? khu?ch tán t? ngu?n 2
    vec3 Id_2 = Ld_2 * Kd_2 * dot_prod_2;

    vec3 half_way_eye_2 = normalize(surface_to_viewer_eye_2 + direction_to_light_eye_2);
    float dot_prod_specular_2 = max(dot(half_way_eye_2, n_eye), 0.0);
    float specular_factor_2 = pow(dot_prod_specular_2, 50.0); // H? s? sáng bóng t? ngu?n 2
    vec3 Ls_2 = vec3(0.8, 0.8, 1.0);
    vec3 Ks_2 = vec3(0.7, 0.7, 0.7);
    vec3 Is_2 = Ls_2 * Ks_2 * specular_factor_2;

    vec3 La_2 = vec3(0.1, 0.1, 0.3);
    vec3 Ka_2 = vec3(0.5, 0.5, 0.5);
    vec3 Ia_2 = La_2 * Ka_2;

    // ------------Màu cu?i cùng t? hai ngu?n sáng------------
    vec3 final_color = (Is_1 + Id_1 + Ia_1) + (Is_2 + Id_2 + Ia_2);
    out_color = vec4(final_color, 1.0) * fragment_color;
}*/


/*#version 460

in vec3 
	position_eye,
	normal_eye;

uniform mat4 view_mat_shader;

in vec4 fragment_color;
out vec4 out_color; 

void main() {
	
	//-----------ch? ??nh các v? trí-------------
		// v? trí ngu?n sáng trong th? gi?i
	vec3 light_position_world = vec3(0.0, 2.27, 0.0);
	//vec3 light_position_world = vec3(0.0, 1.0, 0.0);
		// bi?n ??i v? trí ngu?n sáng sang eye space
	vec3 light_position_eye = vec3(view_mat_shader * vec4(light_position_world, 1.0));

		// v? trí viewer
	vec3 postion_viewer = vec3(0.0, 0.0, 0.0);
		
		// chu?n hóa normal_eye
	vec3 n_eye = normalize(normal_eye);

		// tính vector kho?ng cách t? ngu?n sáng ??n m?t
		// h??ng vector h??ng t? vertex ??n ngu?n sáng
		// = v? trí Light - v? trí Vertex
	vec3 distance_to_light_eye = light_position_eye - position_eye;
		// chu?n hóa vector kho?ng cách t? ngu?n sáng ??n m?t
	vec3 direction_to_light_eye = normalize(distance_to_light_eye);

		// tính vector kho?ng cách v? trí viewer và vertex
		// = v? trí viewer - v? trí vertex
	vec3 surface_to_viewer_eye = postion_viewer - position_eye;
		// chu?n hóa	
	surface_to_viewer_eye = normalize(surface_to_viewer_eye);

	// --------------c??ng ?? ánh sáng khu?ch tán-----------------------
		// tính cosin góc gi?a vector h??ng ánh sáng và vector pháp tuy?n: l.n
	float dot_prod = dot(direction_to_light_eye, n_eye);
		// l?y giá tr? >=0 ?? lo?i b? giá tr? âm ?ng v?i góc >90 ??
	dot_prod = max(dot_prod, 0.0);

		// c??ng ?? ánh sáng ??n
		// màu tr?ng m?
	vec3 Ld = vec3(0.7, 0.7, 0.7);
	//vec3 Ld = vec3(1.5, 1.5, 1.5);

		// h? s? ph?n x? khu?ch tán
		// màu cam
	vec3 Kd = vec3(1.0, 1.0, 1.0);

		// c??ng ?? ánh sáng khu?ch tán cu?i cùng
	vec3 Id = Ld * Kd * dot_prod;

	// -----------------c??ng ?? ánh sáng ph?n x?-------------------
	//vec3 surface_to_viewer_eye = normalize(0.0 - position_eye);

		// tính ph?n x?
		// ??o d?u direction_to_light_eye
		// vì ??i s? th? 1 c?a hàm reflect là vector h??ng t? ngu?n sáng ??n vertex
		// mà direction_to_light_eye hi?n ?ang có h??ng t? vertex ??n ngu?n sáng
	vec3 reflection_eye = reflect(-direction_to_light_eye, n_eye);

		// tính cosin góc gi?a: v.r
	float dot_prod_specular = dot(surface_to_viewer_eye, reflection_eye);
		// l?y giá tr? >=0 ?? lo?i b? giá tr? âm ?ng v?i góc >90 ??
	dot_prod_specular = max(dot_prod_specular, 0.0);

		// h? s? sáng bóng
	float specular_exponent = 100.0;
		// tính m? v?i h? s? sáng bóng
	float specular_factor = pow(dot_prod_specular, specular_exponent);

		// ánh sáng ph?n x?
		// màu tr?ng
	vec3 Ls = vec3(1.0, 1.0, 1.0);

		// h? s? ph?n x?
		// ph?n x? toàn ph?n, màu tr?ng
	vec3 Ks = vec3(1.0, 1.0, 1.0);

		// c??ng ?? ánh sáng ph?n x? cu?i cùng
	vec3 Is = Ls * Ks * specular_factor;

	// --------------c??ng ?? ánh sáng môi tr??ng---------------
		// ánh sáng môi tr??ng
		// màu xám
	vec3 La = vec3(0.2, 0.2, 0.2);

		// h? s? môi tr??ng
		// ph?n chi?u hoàn toàn
	vec3 Ka = vec3(1.0, 1.0, 1.0);

		// c??ng ?? ánh sáng môi tr??ng cu?i cùng
	vec3 Ia = La * Ka;

	// ---------màu cu?i cùng------------
	//out_color = fragment_color;
	//out_color = vec4(Is + Id + Ia, 1.0);
	out_color = vec4(Is + Id + Ia, 1.0)* fragment_color;
}*/
