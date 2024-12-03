#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>

#include <glew.h>
#include <freeglut.h>

#include <Vector_Matrix.h>


using namespace std;

//thêm tam giác màu
static const float coloredTriangle[] = {
	//position			//colors
	 1.0, -1.0,  0.0,	1.0, 0.0, 0.0,//bottom right
	-1.0, -1.0,  0.0,	0.0, 1.0, 0.0,//bottom left
	 0.0,  1.0,  0.0,	0.0, 0.0, 1.0//top
};

typedef struct
{
	float xyzw[4];

	float normal[4];
} Vertex;

Vertex Vertices[] =
{
	// v0-v1-v2 (front)
	{ {  0.5f,	 0.5f,	0.5f, 1.0 },{ 0, 0, 1, 0 } },
	{ { -0.5f,	 0.5f,	0.5f, 1.0 },{ 0, 0, 1, 0 } },
	{ { -0.5f,	-0.5f,	0.5f, 1.0 },{ 0, 0, 1, 0 } },
	// v2-v3-v0
	{ { -0.5f,	-0.5f,	0.5f, 1.0 },{ 0, 0, 1, 0 } },
	{ {  0.5f,	-0.5f,	0.5f, 1.0 },{ 0, 0, 1, 0 } },
	{ {  0.5f,	 0.5f,	0.5f, 1.0 },{ 0, 0, 1, 0 } },

	// v0-v3-v4 (right)
	{ { 0.5f,	 0.5f,	 0.5f, 1.0 },{ 1, 0, 0, 0 } },
	{ { 0.5f,	-0.5f,   0.5f, 1.0 },{ 1, 0, 0, 0 } },
	{ { 0.5f,	-0.5f,  -0.5f, 1.0 },{ 1, 0, 0, 0 } },
	// v4-v5-v0
	{ { 0.5f,	-0.5f,	-0.5f, 1.0 },{ 1, 0, 0, 0 } },
	{ { 0.5f,	 0.5f,	-0.5f, 1.0 },{ 1, 0, 0, 0 } },
	{ { 0.5f,	 0.5f,   0.5f, 1.0 },{ 1, 0, 0, 0 } },

	// v0-v5-v6 (top)
	{ {  0.5f,	0.5f,	 0.5f, 1.0 },{ 0, 1, 0, 0 } },
	{ {  0.5f,	0.5f,	-0.5f, 1.0 },{ 0, 1, 0, 0 } },
	{ { -0.5f,	0.5f,	-0.5f, 1.0 },{ 0, 1, 0, 0 } },
	// v6-v1-v0
	{ { -0.5f,	0.5f,	-0.5f, 1.0 },{ 0, 1, 0, 0 } },
	{ { -0.5f,	0.5f,	 0.5f, 1.0 },{ 0, 1, 0, 0 } },
	{ {  0.5f,	0.5f,	 0.5f, 1.0 },{ 0, 1, 0, 0 } },

	// v1-v6-v7 (left)
	{ { -0.5f,	 0.5f,	 0.5f, 1.0 },{ -1, 0, 0, 0 } },
	{ { -0.5f,	 0.5f,	-0.5f, 1.0 },{ -1, 0, 0, 0 } },
	{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ -1, 0, 0, 0 } },
	// v7-v2-v1
	{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ -1, 0, 0, 0 } },
	{ { -0.5f,	-0.5f,	 0.5f, 1.0 },{ -1, 0, 0, 0 } },
	{ { -0.5f,	 0.5f,	 0.5f, 1.0 },{ -1, 0, 0, 0 } },

	// v7-v4-v3 (bottom)
	{ { -0.5f,	 -0.5f,	-0.5f, 1.0 },{ 0,-1, 0, 0 } },
	{ {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 0,-1, 0, 0 } },
	{ {  0.5f,	-0.5f,	 0.5f, 1.0 },{ 0,-1, 0, 0 } },
	// v3-v2-v7
	{ {  0.5f,	-0.5f,	 0.5f, 1.0 },{ 0,-1, 0, 0 } },
	{ { -0.5f,	-0.5f,	 0.5f, 1.0 },{ 0,-1, 0, 0 } },
	{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 0,-1, 0, 0 } },

	// v4-v7-v6 (back)
	{ {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 0, 0,-1, 0 } },
	{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 0, 0,-1, 0 } },
	{ { -0.5f,	 0.5f,	-0.5f, 1.0 },{ 0, 0,-1, 0 } },
	// v6-v5-v4
	{ { -0.5f,	 0.5f,	-0.5f, 1.0 },{ 0, 0,-1, 0 } },
	{ {  0.5f,	 0.5f,	-0.5f, 1.0 },{ 0, 0,-1, 0 } },
	{ {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 0, 0,-1, 0 } }
};

const size_t BufferSize = sizeof(Vertices);
const size_t VertexSize = sizeof(Vertices[0]);
const size_t NormalOffset = sizeof(Vertices[0].xyzw);


// định nghĩa stack cho ma trận
class MatrixStack {
	int    index;
	int    size;
	mat4* matrices;

public:
	MatrixStack(int numMatrices = 32) :index(0), size(numMatrices)
	{
		matrices = new mat4[numMatrices];
	}

	~MatrixStack()
	{
		delete[]matrices;
	}

	// phép toán đẩy vào
	mat4& push(const mat4& m) {
		assert(index + 1 < size);
		matrices[index++] = m;
		return matrices[index];
	}

	// phép toán lấy ra
	mat4& pop(void) {
		assert(index - 1 >= 0);
		index--;
		return matrices[index];
	}
};

MatrixStack  mvstack;

int CurrentWidth = 700,
CurrentHeight = 700;

GLuint
VaoId[2],
VboId[2],
VertexShaderId,
FragmentShaderId,
ProgramId;

mat4
model_mat_cpp,
view_mat_cpp,
projection_mat_cpp;

int
model_mat_location,
view_mat_location,
projection_mat_location;

// Dùng biến đổi mô hình
float
r[] = { 0.0f, 0.0f, 0.0f },
s[] = { 1.0f, 1.0f, 1.0f },
t[] = { 0.0f, 0.0f, 0.0f };
//=============sử dụng cho camera============
int midWindowX;
int midWindowY;


bool keys[256]; // Array to keep track of pressed keys
bool mouseLocked = true;
float yaw = 0.0f;
float pitch = 0.0f;

float cameraX = 0.0f;
float cameraY = 0.0f;
float cameraZ = 5.0f;
float moveSpeed = 0.5f;
float jumpSpeed = 0.2f;
float gravity = 0.010f;
bool isJumping = false;
bool isGrounded = true;

// ======Dùng kiểm tra tịnh tiến, quay, co giãn====
bool
translated = false,
rotated = false,
scaled = false;

//---------------------------------------------Khai báo các biến sử dụng để vẽ------------------------------------------
float Alpha = 0.0f;
//thiết lập chỉ mục cho menu

enum {
	windown1,
	windown2,
	windown3,
	windown4,
	windown5,
	windown6,
	windownJoint_z
};
GLfloat windown_rotate[windownJoint_z]{
	0.0,//windown1
	0.0,//windown2
	0.0,//windown3
	0.0,//windown4
	0.0,//windown5
	0.0//windown6
};
GLint rotate_windown = windown1;
//--------------------------------------------------kết thúc khai báo các biến vẽ
// ------------------------------------------
string ReadShaderSourceFile(string fileName) {
	fstream reader(fileName.c_str());
	string line;
	string code = "";
	while (getline(reader, line)) {
		code += line + "\n";
	}
	reader.close();
	return code;
}
// ------------------------------------------
void CreatVaoVbo()
{
	// Tạo và liên kết VAO và VBO cho tam giác có màu
	glGenVertexArrays(2, &VaoId[0]);
	glGenBuffers(2, &VboId[0]);

	// Thiết lập VAO và VBO cho coloredTriangle
	glBindVertexArray(VaoId[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VboId[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(coloredTriangle), coloredTriangle, GL_DYNAMIC_DRAW);

	// Cấu hình thuộc tính đỉnh cho vị trí (3 float) và màu sắc (3 float)
	// Layout location 0 cho vertex_position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	// Layout location 1 cho vertex_color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	// Bật các thuộc tính đỉnh
	glEnableVertexAttribArray(0); // Bật vertex_position
	glEnableVertexAttribArray(1); // Bật vertex_color

	// Thiết lập VAO và VBO cho mảng Vertices
	glBindVertexArray(VaoId[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VboId[1]);
	glBufferData(GL_ARRAY_BUFFER, BufferSize, Vertices, GL_STATIC_DRAW);

	// Cấu hình thuộc tính đỉnh cho vị trí và vector pháp tuyến
	// Layout location 0 cho vertex_position
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, VertexSize, (void*)0);
	// Layout location 2 cho vertex_normal
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)NormalOffset);

	// Bật thuộc tính đỉnh
	glEnableVertexAttribArray(0); // Bật vertex_position
	glEnableVertexAttribArray(2); // Bật vertex_normal

	// Bật kiểm tra độ sâu và ẩn con trỏ chuột
	glEnable(GL_DEPTH_TEST);
	glutSetCursor(GLUT_CURSOR_NONE);
}
// ------------------------------------------
void CreatShaders()
{
	string vertexSrc = ReadShaderSourceFile("./vs.shader");
	string fragmentSrc = ReadShaderSourceFile("./fs.shader");

	const GLchar* VertexShader = vertexSrc.c_str();
	const GLchar* FragmentShader = fragmentSrc.c_str();

	VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShaderId, 1, &VertexShader, NULL);
	glCompileShader(VertexShaderId);

	FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShaderId, 1, &FragmentShader, NULL);
	glCompileShader(FragmentShaderId);

	ProgramId = glCreateProgram();
	glAttachShader(ProgramId, VertexShaderId);
	glAttachShader(ProgramId, FragmentShaderId);
	glLinkProgram(ProgramId);
	glUseProgram(ProgramId);
}
// ------------------------------------------
void CloseFunc()
{
	glUseProgram(0);

	glDetachShader(ProgramId, VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);

	glDeleteShader(FragmentShaderId);
	glDeleteShader(VertexShaderId);

	glDeleteProgram(ProgramId);

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VboId[0]);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId[0]);
}
//--------------------------------------------
//-------------------------ánh sáng----------------------------------
#pragma region light
bool light1 = true, light2 = true;

void updateLightUniforms() {
	//light1 = 1; light2 = 1;
	glUniform1i(glGetUniformLocation(ProgramId, "enable_light_1"), light1 ? 0 : 1);
	glUniform1i(glGetUniformLocation(ProgramId, "enable_light_2"), light2 ? 1 : 0);
}

void onl1() {
	light1 = true;
	updateLightUniforms();
}

void offl1() {
	light1 = false;
	updateLightUniforms();
}

void onl2() {
	light2 = true;
	updateLightUniforms();
}

void offl2() {
	light2 = false;
	updateLightUniforms();
}
#pragma endregion
// ==========================================================Tạo các đối tượng==========================================
// --------------Hàm gọi màu trong vs.shader----------------------------
void setInt(const string& name, int value) {
	glUniform1i(glGetUniformLocation(ProgramId, name.c_str()), value);
}
//-----------Tạo khối hộp cube đơn vị--------
void cube()
{
	mvstack.push(model_mat_cpp);
	mat4 instance = identity_mat4();
	mat4 model_cube = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_cube.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop();
}

//--------------ve phong lam viec------------
#pragma region room and door
void room()
{

	mvstack.push(model_mat_cpp);
	// trần nhà
	//FillColor(lemon);
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0.0, 2.9, -3.5)) * scale(vec3(5.0, 0.01, 7.0));
	setInt("color", 14);
	cube();
	model_mat_cpp = mvstack.pop();

	// tường trái 
	mvstack.push(model_mat_cpp);
	setInt("color", 15);
	model_mat_cpp = model_mat_cpp * translate(vec3(0.0, 0.9, 0)) * scale(vec3(5.0, 4.0, 0.01));
	cube();
	model_mat_cpp = mvstack.pop();

	// sàn 
	mvstack.push(model_mat_cpp);
	setInt("color", 15);
	model_mat_cpp = model_mat_cpp * translate(vec3(0.0, -1.1, -3.5)) * scale(vec3(5.0, 0.01, 7.0));
	cube();
	model_mat_cpp = mvstack.pop();

	// mặt trước
	 //mảnh tường to thứ nhất
	mvstack.push(model_mat_cpp);
	setInt("color", 15);
	model_mat_cpp = model_mat_cpp * translate(vec3(-2.5, 1.65, -3.5)) * scale(vec3(0.01, 2.5, 7.0));
	cube();
	model_mat_cpp = mvstack.pop();

	////mảnh tường nhỏ bên trái
	mvstack.push(model_mat_cpp);
	setInt("color", 15);
	model_mat_cpp = model_mat_cpp * translate(vec3(-2.5, -0.35, -0.5)) * scale(vec3(0.01, 1.5, 1));
	cube();
	model_mat_cpp = mvstack.pop();
	
	//mảnh tường nhỏ bên phải 
	mvstack.push(model_mat_cpp);
	setInt("color", 15);
	model_mat_cpp = model_mat_cpp * translate(vec3(-2.5, -0.35, -4.5)) * scale(vec3(0.01, 1.5, 5));
	cube();
	model_mat_cpp = mvstack.pop();

	model_mat_cpp = mvstack.pop();

	// mặt sau 
	mvstack.push(model_mat_cpp);
	setInt("color", 15);
	model_mat_cpp = model_mat_cpp * translate(vec3(2.5, 0.9, -3.5)) * scale(vec3(0.01, 4.0, 7.0));
	cube();
	model_mat_cpp = mvstack.pop();

	// tường phải 
//  mảnh tường to trên
	mvstack.push(model_mat_cpp);
	setInt("color", 15);
	model_mat_cpp = model_mat_cpp * translate(vec3(0.0, 2.15, -7)) * scale(vec3(5.0, 1.5, 0.01));
	cube();
	model_mat_cpp = mvstack.pop();
	//mảnh tường to dưới
	mvstack.push(model_mat_cpp);
	setInt("color", 15);
	model_mat_cpp = model_mat_cpp * translate(vec3(0.0,-0.35, -7)) * scale(vec3(5.0, 1.5, 0.01));
	cube();
	model_mat_cpp = mvstack.pop();
	//mảnh tường to trái
	mvstack.push(model_mat_cpp);
	setInt("color", 15);
	model_mat_cpp = model_mat_cpp * translate(vec3(1, 0.9, -7)) * scale(vec3(3, 1.0, 0.01));
	cube();
	model_mat_cpp = mvstack.pop();
	// mảnh tường nhỏ  phải
	mvstack.push(model_mat_cpp);
	setInt("color", 15);
	model_mat_cpp = model_mat_cpp * translate(vec3(-2, 0.9, -7)) * scale(vec3(1, 1.0, 0.01));
	cube();
	model_mat_cpp = mvstack.pop();
}
// cửa
float door_angle = 0.0f;
void door() {
	mvstack.push(model_mat_cpp);
	// Xoay cánh cửa
	mvstack.push(model_mat_cpp);
	setInt("color", 1);
	model_mat_cpp = model_mat_cpp
		* translate(vec3(-2.5, -0.35, -1.5)) // Đặt cửa gần khung trái
		* translate(vec3(-0.025, 0.0, 0.5))   // Đưa về điểm xoay (bản lề)
		* rotate_y(door_angle)              // Xoay cửa quanh bản lề
		* translate(vec3(0.025, 0.0, -0.5))    // Đưa cửa về vị trí ban đầu
		* scale(vec3(0.05, 1.5, 1.0));      // Kích thước cửa (dày, cao, rộng)   
	cube();  // Vẽ cánh cửa
	model_mat_cpp = mvstack.pop();

	// Tay nắm cửa hình chữ nhật
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp
		* translate(vec3(-2.53, -0.3, -1)) // Đặt vị trí tay nắm trên cánh cửa
			* rotate_y(door_angle)              // Xoay cửa quanh bản lề
			* translate(vec3(0.01, 0.0, -0.4))   // Đưa về điểm xoay (bản lề)
			* translate(vec3(0.01, 0.0, -0.4))   // Đưa cửa về vị trí ban đầu
			* scale(vec3(0.14, 0.4, 0.05));      // Kích thước tay nắm hình chữ nhật (dài, rộng, dày)
	setInt("color", 2); // Tay nắm có màu khác
	cube();  // Vẽ tay nắm
	model_mat_cpp = mvstack.pop();

	// Khung cửa trái
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(-2.5, -0.35, -1)) * scale(vec3(0.05, 1.5, 0.05));  // Khung trái, cao hơn cánh cửa
	setInt("color", 1);
	cube();
	model_mat_cpp = mvstack.pop();

	// Khung cửa phải
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(-2.5, -0.35, -2)) * scale(vec3(0.05, 1.5, 0.05));  // Khung phải
	setInt("color", 1);
	cube();
	model_mat_cpp = mvstack.pop();

	// Khung cửa trên
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(-2.5, 0.4, -1.5)) * scale(vec3(0.05, 0.05, 1.0)); // Khung trên
	setInt("color", 1);
	cube();
	model_mat_cpp = mvstack.pop();

	model_mat_cpp = mvstack.pop();
}
#pragma endregion

//-----ve window------
#pragma region window
void windown(float tmp) {
	//khung tren
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(1.6, 0.275, -0.9)) * scale(vec3(1.05, 0.05, 0.05));
	setInt("color", 1);
	cube();
	//khung duoi
	model_mat_cpp = mvstack.pop();
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(1.6, -0.35, -0.9)) * scale(vec3(1.05, 0.05, 0.05));
	setInt("color", 1);
	cube();
	model_mat_cpp = mvstack.pop();
	//khung trai
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(2.1, -0.05, -0.9)) * scale(vec3(0.05, 0.65, 0.05));
	setInt("color", 1);
	cube();
	model_mat_cpp = mvstack.pop();
	//khung phai
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(1.05, -0.04, -0.9)) * scale(vec3(0.05, 0.67, 0.05));
	setInt("color", 1);
	cube();
	model_mat_cpp = mvstack.pop();

	//kinh
	mvstack.push(model_mat_cpp); 
	model_mat_cpp = model_mat_cpp
		* translate(vec3(1.58, -0.04, -0.9))   // Vị trí trung tâm giữa các khung
		* translate(vec3(0.0, 0.3, 0))
		* rotate_x(tmp)
		* translate(vec3(0.0, -0.3, 0))
		* scale(vec3(1.0, 0.6, 0.02));
	setInt("color", 9);
	cube();
	model_mat_cpp = mvstack.pop();

	//tay nam
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp
		* translate(vec3(1.55, 0.25, -0.89))
		* rotate_x(tmp)
		* translate(vec3(0.0, -0.25, 0.0))
		* translate(vec3(0.0, -0.15, 0.0))
		* scale(vec3(0.1, 0.02, 0.02));
	setInt("color", 1);
	cube();
	model_mat_cpp = mvstack.pop();

}
void windowns(float tx, float ty, float tz, float sx, float sy, float sz, float tmp, int j) {

	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(tx, ty, tz)) * scale(vec3(sx, sy, sz)) * rotate_y(360 / j);
	windown(tmp);
	model_mat_cpp = mvstack.pop();
}
#pragma endregion

//-------ve camera-------------
#pragma region camera
bool switch_camera = false;
float camera_angle = 0.0f;
float camera_direction = 1.0f;
void camera() {
	mvstack.push(model_mat_cpp);

	// Base
	mvstack.push(model_mat_cpp);
	setInt("color", 99);
	model_mat_cpp = model_mat_cpp * scale(vec3(0.03, 0.03, 0.12));
	cube();
	model_mat_cpp = mvstack.pop();
	// camera
	mvstack.push(model_mat_cpp);
	setInt("color", 2);
	model_mat_cpp = model_mat_cpp * rotate_y(camera_angle) * translate(vec3(0.0, 0.0, 0.1)) * scale(vec3(0.1, 0.1, 0.2));
	cube();
	model_mat_cpp = mvstack.pop();

	model_mat_cpp = mvstack.pop();
}
void cameras(float tx, float ty, float tz, float sx, float sy, float sz) {
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(tx, ty, tz)) * scale(vec3(sx, sy, sz));
	camera();
	model_mat_cpp = mvstack.pop();
}
#pragma endregion

void light() {
	mvstack.push(model_mat_cpp);
	//bong
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(1.35, 3, 0)) * scale(vec3(0.05, 0.05, 1.86));
	setInt("color", 98);
	cube();
	model_mat_cpp = mvstack.pop();
	//de
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(1.42, 3, 0)) * scale(vec3(0.03, 0.1, 2));
	setInt("color", 1);
	cube();
	model_mat_cpp = mvstack.pop();
	//tai phai
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(1.35, 3, 0.95)) * scale(vec3(0.1, 0.1, 0.07));
	setInt("color", 1);
	cube();
	model_mat_cpp = mvstack.pop();
	//tai trai
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(1.35, 3, 0.95)) * scale(vec3(0.1, 0.1, 0.07));
	setInt("color", 1);
	cube();
	model_mat_cpp = mvstack.pop();
	model_mat_cpp = mvstack.pop();
}

void lights(float tx, float ty, float tz, float sx, float sy, float sz, int tmp) {
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(tx, ty, tz)) * scale(vec3(sx, sy, sz)) * rotate_z(90.0f * tmp);
	light();
	model_mat_cpp = mvstack.pop();
}
#pragma endregion
//==============================================================Hết tạo các đối tượng==============================
//-------------------------------
void DisplayFunc(void)
{
	model_mat_cpp = identity_mat4();
	model_mat_location = glGetUniformLocation(ProgramId, "model_mat_shader");
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_mat_cpp.m);
	if (translated)
	{
		model_mat_cpp = model_mat_cpp * translate(vec3(t[0], t[1], t[2]));
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_mat_cpp.m);
	}
	if (rotated)
	{
		model_mat_cpp = model_mat_cpp * rotate_x(r[0])
			* rotate_y(r[1])
			* rotate_z(r[2]);
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_mat_cpp.m);
	}
	if (scaled)
	{
		model_mat_cpp = model_mat_cpp * scale(vec3(s[0], s[1], s[2]));
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_mat_cpp.m);
	}

	glMatrixMode(GL_MODELVIEW);
	// Các tham số của hàm lookat
	vec3	eye(cameraX, cameraY, cameraZ),
		at(cameraX + sin(yaw ), cameraY - pitch, cameraZ - cos(yaw)),
		up(0.0f, 1.0f, 0.0f);

	view_mat_cpp = lookat(eye, at, up);
	view_mat_location = glGetUniformLocation(ProgramId, "view_mat_shader");
	glUniformMatrix4fv(view_mat_location, 1, GL_FALSE, view_mat_cpp.m);

	float
		znear = 0.1f,
		zfar = 100.0f,
		fov = 90.0f,
		aspect = (float)CurrentWidth / CurrentHeight;
	projection_mat_cpp = perspective(fov, aspect, znear, zfar);
	projection_mat_location = glGetUniformLocation(ProgramId, "projection_mat_shader");
	glUniformMatrix4fv(projection_mat_location, 1, GL_FALSE, projection_mat_cpp.m);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//-----------------draw------------------
	room();
	door();


	lights(13.5, 1.15, -2.6, 4.5, 1.2, 1.9, 1);
	windowns(-2.5, 0.975, -5.5, 0.95, 1.6, 1.65, windown_rotate[windown1], 1);
	//camera
	cameras(2.2, 2.8, -6.95, 1.0, 1.0, 1.0);
	glutSwapBuffers();
}
//---các hàm cho cam-----------
void handleMouseMove(int x, int y) {
	if (mouseLocked) {
		int deltaX = x - midWindowX;
		int deltaY = y - midWindowY;

		yaw += deltaX * 0.001f;
		pitch += deltaY * 0.001f;

		if (pitch > 1.5f) pitch = 1.5f;
		else if (pitch < -1.5f) pitch = -1.5f;

		glutWarpPointer(midWindowX, midWindowY);
	}
	glutPostRedisplay();
}
void handleKeyRelease(unsigned char key, int x, int y) {
	keys[key] = false;
	glutPostRedisplay();
}
void updateCamera() {
	if (isJumping) {
		cameraY += jumpSpeed;
		jumpSpeed -= gravity;
		if (cameraY <= 0.0f) {
			cameraY = 0.0f;
			isJumping = false;
			isGrounded = true;
			jumpSpeed = 0.2f;
		}
	}
	glutPostRedisplay();
}
// ------------------------------------------
void ReshapeFunc(int Width, int Height)
{
	CurrentWidth = Width;
	CurrentHeight = Height;
	midWindowX = Width / 2;//
	midWindowY = Height / 2;//
	glViewport(0, 0, CurrentWidth, CurrentHeight);
}
// ------------------------------------------
bool phim1 = true, phim2 = true;
void IdleFunc(void)
{
	updateCamera();
	//------light-----on---off----
	if (phim1) {
		onl1(); glutPostRedisplay();
	}
	else {
		offl1(); glutPostRedisplay();
	}
	if (phim2) {
		onl2(); glutPostRedisplay();
	}
	else {
		offl2();
		glutPostRedisplay();
	}

	// camera
	if (switch_camera) {
		camera_angle += camera_direction * 0.1f;  // Cap nhat goc quayy
		if (camera_angle >= 60.0f || camera_angle <= -60.0f) {
			camera_direction = -camera_direction;
		}
		glutPostRedisplay();
	}
}
// ------------------------------------------
void KeyboardFunc(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		glutLeaveMainLoop();
		break;
		//----camera------------
	case 'w':
		cameraX += sin(yaw) * moveSpeed;
		cameraZ -= cos(yaw) * moveSpeed;
		break;
	case 's':
		cameraX -= sin(yaw) * moveSpeed;
		cameraZ += cos(yaw) * moveSpeed;
		break;
	case 'd':
		cameraX += sin(yaw - 3.1415926535 / 2) * moveSpeed;
		cameraZ -= cos(yaw - 3.1415926535 / 2) * moveSpeed;
		break;
	case 'a':
		cameraX += sin(yaw + 3.1415926535 / 2) * moveSpeed;
		cameraZ -= cos(yaw + 3.1415926535 / 2) * moveSpeed;
		break;
	case ' ':
		if (isGrounded) {
			isJumping = true;
			isGrounded = false;
		}
		keys[key] = true;
		break;
		//-----light---
	case 'C':
	case 'c'://on/off light1
		if (phim1) phim1 = false;
		else phim1 = true;
		break;
	case 'V':
	case 'v'://on/of light2
		if (phim2) phim2 = false;
		else phim2 = true;
		break;
		//-----light---
	case 'x':
		r[0] -= 10.0f;
		rotated = true;
		break;
	case 'X':
		r[0] += 10.0f;
		rotated = true;
		break;

	case 'y':
		r[1] -= 10.0f;
		rotated = true;
		break;
	case 'Y':
		r[1] += 10.0f;
		rotated = true;
		break;

	case 'z':
		r[2] -= 10.0f;
		rotated = true;
		break;
	case 'Z':
		r[2] += 10.0f;
		rotated = true;
		break;

	case '=':
	case '+':
		s[0] *= 1.05f;
		s[1] *= 1.05f;
		s[2] *= 1.05f;
		scaled = true;
		break;

	case '-':
	case '_':
		s[0] /= 1.05f;
		s[1] /= 1.05f;
		s[2] /= 1.05f;
		scaled = true;
		break;

	case 'j':
		t[0] -= 0.05f;
		translated = true;
		break;
	case 'l':
		t[0] += 0.05f;
		translated = true;
		break;
	case 'i':
		t[1] += 0.05f;
		translated = true;
		break;
	case ',':
		t[1] -= 0.05f;
		translated = true;
		break;
	case 'h':
		t[2] -= 0.05f;
		translated = true;
		break;
	case 'g':
		t[2] += 0.05f;
		translated = true;
		break;

	case '/'://mở cửa
		door_angle += 2.0f;
		if (door_angle >= 170) door_angle = 170.0f;
		break;
	case '?'://đóng cửa
		door_angle -= 2.0f;
		if (door_angle <= 0) door_angle = 0;
		break;

	case '6'://window
		windown_rotate[rotate_windown] += 1.5;
		if (windown_rotate[rotate_windown] >= 90.0) { windown_rotate[rotate_windown] = 90.0; }
		break;
	case '7'://window
		windown_rotate[rotate_windown] -= 1.5;
		if (windown_rotate[rotate_windown] <= 0.0) { windown_rotate[rotate_windown] = 0.0; }
		break;
		//// camera//////////////////////////////////////
	case '2':
		if (switch_camera) {
			switch_camera = false;
			break;
		}
		else {
			switch_camera = true;
			break;
		}
	}
}
// ----------------------------------------
// Xử lý phím đặc biệt
void SpecialFunc(int key, int x, int y)
{

	switch (key)
	{
	case GLUT_KEY_LEFT:
		t[0] -= 0.05f;
		translated = true;
		break;
	case GLUT_KEY_RIGHT:
		t[0] += 0.05f;
		translated = true;
		break;
	case GLUT_KEY_UP:
		t[1] += 0.05f;
		translated = true;
		break;
	case GLUT_KEY_DOWN:
		t[1] -= 0.05f;
		translated = true;
		break;
	case GLUT_KEY_ALT_R:
		t[2] -= 0.05f;
		translated = true;
		break;
	case GLUT_KEY_CTRL_R:
		t[2] += 0.05f;
		translated = true;
		break;
	}
}
void danhsachlenh() {
	cout << "/ : mo cua chinh " << endl;
	cout << "? : dong cua chinh " << endl;
	cout << "6 : mo cua so " << endl;
	cout << "7 : dong cua so" << endl;
	cout << "chuot di chuyen huong camera " << endl;
	cout << "g : tinh tien vat the ve gan camera" << endl;
	cout << "h : tinh tien vat the ra xa camera  " << endl;
	cout << "w : tien camera len  " << endl;
	cout << "s : lui camera xuong  " << endl;
	cout << "a : xoay camera sang trai  " << endl;
	cout << "d : xoay camera sang phai  " << endl;
	cout << "+ : phong to " << endl;
	cout << "- : thu nho " << endl;
	cout << ", : dua camera len tren " << endl;
	cout << "i : dua camera xuong duoi " << endl;
	cout << "c : bat, tat den dien " << endl;
	cout << "v : ngay, dem " << endl;
	cout << endl;
}
// ------------------------------------------
int main(int argc, char* argv[])
{
	danhsachlenh();
	glutInit(&argc, argv);
	glutInitContextVersion(4, 0);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitWindowSize(CurrentWidth, CurrentHeight);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("phong lam viec");

	glewExperimental = GL_TRUE;
	glewInit();

	CreatVaoVbo();
	CreatShaders();

	glutDisplayFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc);
	glutIdleFunc(IdleFunc);
	glutPassiveMotionFunc(handleMouseMove);//camera
	glutKeyboardFunc(KeyboardFunc);
	glutSpecialFunc(SpecialFunc);
	glutKeyboardUpFunc(handleKeyRelease);//camera
	glutCloseFunc(CloseFunc);

	// Attach the menu to the middle mouse button
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
	return 0;
}

