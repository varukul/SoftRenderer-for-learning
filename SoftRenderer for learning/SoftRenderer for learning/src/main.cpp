#include<fstream>
#include<iostream>
#include<vector>
#include"vec.h"
#include"matrix44.h"
#include"Draw.h"
#include"color.h"
#include"ioimages.h"
#include"Lighting.h"
#include"Geometry.h"



//void demo_color_triangle(int w, int h) {
//	color **mat = new color*[h];
//	for (int i = 0; i < h; i++) {
//		*(mat + i) = new color[w];
//	}
//
//	vertex v[3] = { vertex(vec3f(-20, 0, -40), color(255, 0, 0)) ,         //counterclockwise
//		vertex(vec3f(20, 0, -40), color(0, 255, 0)) ,
//		vertex(vec3f(0, 20, -40), color(0, 0, 255)) };
//
//	matrix44 view;
//	view.set_viewport(w, h);
//	matrix44 perspective;
//	perspective.set_perspective(float(w) / float(h), 60, -10, -100);
//	matrix44 camera;
//	camera.set_camera(vec3f(0, 0, 0), vec3f(0, 0, -1), vec3f(0, 1, 0));
//	matrix44 p;
//	p = perspective * camera;
//	p = view * p;
//	for (int i = 0; i < 3; i++) {
//		v[i]._pos = p * v[i]._pos;
//		std::cout << v[i]._pos << std::endl;
//	}
//	Draw::draw_triangle(mat, v, w, h);
//	//for color test
//	generate_color_PPM("./images/color_triangles_1.PPM", w, h, mat);
//}
//
//void demo_hiden_surface(int w, int h) {
//	color **mat = new color*[h];
//	for (int i = 0; i < h; i++) {
//		*(mat + i) = new color[w];
//	}
//
//	vertex v[6] = { vertex(vec3f(-20, 0, -40), color(255, 0, 0)) ,         
//		vertex(vec3f(20, 0, -40), color(255, 0, 0)) ,
//		vertex(vec3f(0, 20, -40), color(255, 0, 0)) ,
//		vertex(vec3f(-30, 10, -60), color(0, 0, 255)) ,         
//		vertex(vec3f(10, 10, -20), color(0, 0, 255)) ,
//		vertex(vec3f(0, 10, -60), color(0, 0, 255)) };
//
//	matrix44 view;
//	view.set_viewport(w, h);
//	matrix44 perspective;
//	perspective.set_perspective(float(w) / float(h), 60, -10, -100);
//	matrix44 camera;
//	camera.set_camera(vec3f(0, 0, 0), vec3f(0, 0, -1), vec3f(0, 1, 0));
//	matrix44 p;
//	p = perspective * camera;
//	p = view * p;
//	for (int i = 0; i < 6; i++) {
//		v[i]._pos = p * v[i]._pos;
//		std::cout << v[i]._pos << std::endl;
//	}
//
//
//	Draw::draw_triangles(mat, v, 6, w, h,true);
//
//	generate_color_PPM("./images/hiden_surface_1.PPM", w, h, mat);
//}

//
//void demo_texture(int w,int h) {
//	//初始化贴图
//	texture2d tex = readBmp("D:/images/woodtexture.bmp");
//	//初始化矩阵
//	matrix44 view;
//	view.set_viewport(w, h);
//	matrix44 perspective;
//	perspective.set_perspective(float(w) / float(h), 60, -10, -100);
//	matrix44 camera;
//	camera.set_camera(vec3f(0, 0, 0), vec3f(0, 0, -1), vec3f(0, 1, 0));
//	matrix44 p;
//	p = perspective * camera;
//	p = view * p;
//	//初始化图形
//
//	int texcoord_wid = (tex._width - w) >= 0 ? (w - 1) : tex._width - 1;
//	int texcoord_het = (tex._height - h) >= 0 ? (h - 1) : tex._height - 1;
//
//	vertex v[4] = { vertex(vec3f(-20,-20,-30),color(0),textcoord(0,0)),
//		vertex(vec3f(20,-20,-30),color(0),textcoord(texcoord_wid,0)),
//		vertex(vec3f(20,20,-30),color(0),textcoord(texcoord_wid,texcoord_het)),
//		vertex(vec3f(-20,20,-30),color(0),textcoord(0,texcoord_het)) };
//	for (int i = 0; i < 4; i++) {
//		v[i]._pos = p * v[i]._pos;
//	}
//	//初始化像素矩阵
//	
//	color **mat = new color*[h];
//	for (int i = 0; i < h; i++) {
//		*(mat + i) = new color[w];
//	}
//
//	//绘制图形 
//	vertex temp[3] = { v[0],v[1],v[2] };
//	vertex temp2[3] = { v[0],v[2],v[3] };
//	Draw::draw_triangle(mat, temp, w, h, tex,true);
//	Draw::draw_triangle(mat, temp2, w, h, tex,true);
//
//	generate_color_PPM("./images/flat_texture_1.PPM", w, h, mat);
//}


void generate_texture(texture2d& tex) {                //test texture
	int height = 640, width = 640;
	std::vector<std::vector<color>> texc(height, std::vector<color>(width, color(0)));
	tex._height = height, tex._width = width;
	tex._texc = std::move(texc);
	for (int h = 0; h < height; h++) {
		int count = 0;
		for (int w = 0; w < width; w++) {
			int t = (count++) % 160;
			tex._texc[h][w] = t > 80 ? 255 : color(60,10,60);
		}
	}
}

void demo_cube(int w, int h) {
	texture2d tex = readBmp("D:/images/woodframe.bmp");
	/*texture2d tex;
	generate_texture(tex);*/
	//初始化矩阵
	matrix44 view;
	view.set_viewport(w, h);
	matrix44 perspective;
	perspective.set_perspective(float(w) / float(h), 90, -10, -100);
	matrix44 camera;
	vec3f eye(30, 15, 15);
	camera.set_camera(eye, vec4f(0, 0, 0), vec4f(0, 1, 0));
	matrix44 p;
	p = perspective * camera;
	p = view * p;
	//初始化图形

	int texcoord_wid = (tex._width - w) >= 0 ? (w - 1) : tex._width - 1;
	int texcoord_het = (tex._height - h) >= 0 ? (h - 1) : tex._height - 1;
	    //前面
	std::vector<vertex> vertices = { vertex(vec4f(-10,-10,10),textcoord(0,0)),  //左下
		vertex(vec4f(10,-10,10),textcoord(1,0)),								//右下
		vertex(vec4f(10,10,10),textcoord(1,1)),									//右上
		vertex(vec4f(-10,10,10),textcoord(0,1)) ,								//左上
		//后面
		vertex(vec4f(-10,-10,-10),textcoord(1,0)),						        //左下
		vertex(vec4f(10,-10,-10),textcoord(0,0)),                               //右下
		vertex(vec4f(10,10,-10),textcoord(0,1)),								//右上
		vertex(vec4f(-10,10,-10),textcoord(0,0))								//左上
	};

	std::vector<uint16_t> indices = {
		0,1,2, 0,2,3,                    //front
		0,3,4, 4,3,7,                    //left
		4,7,5, 5,7,6,                    //back
		5,6,2, 5,2,1,                     //right
		6,7,2, 3,2,7,                     //top
		5,1,0, 5,0,4                      //bottom
	};


	//计算顶点法线向量
	for (int i = 0; i < indices.size(); i += 3) {                 
		vec3f u = vertices[indices[i + 1]]._posW - vertices[indices[i]]._posW;
		vec3f v = vertices[indices[i + 2]]._posW - vertices[indices[i]]._posW;
		vertices[indices[i]]._normal = vertices[indices[i]]._normal + cross(u, v).normalize();
	}
	for (auto iv : vertices) {
		iv._normal = iv._normal.normalize();
	}

	//定义光源 及 材质
	LightGroup LG;
	LG.lights[0] = { vec3f(1.0f),0.0f,vec3f(-1.0f).normalize(),0.0f,vec3f(20.0f),0.0f }; // direction light
	LG.lights[1] = { vec3f(1.0f,1.0f,1.0f),0.0f,vec3f(2.0f,3.0f,5.0f).normalize(),20.0f,vec3f(-10.0f,-5.0f,0.0f),0.0f }; //point light
	LG.lights[2] = { vec3f(1.0f,1.0f,1.0f),0.0f,vec3f(4.0f,-5.0f,-6.0f).normalize(),20.0f,vec3f(-6.0f,4.0f,3.0f),5.0f }; //spot light
	LG.NUM_DIR_LIGHTS = 1;
	LG.NUM_POINT_LIGHTS = 1;
	LG.NUM_SPOT_LIGHTS = 1;
	LG.Eye = eye;

	MaterialGroup MG;
	MG.materials[0] = { vec4f(0.85f, 0.5f, 0.8f, 1.0f),vec3f(0.01f,0.01f,0.01f),0.5f };
	MG.useIdx = 0;

	for (int i = 0; i < 8; i++) {
		vertices[i]._pos = p * vertices[i]._pos;
	}
	//初始化像素矩阵
	std::vector<std::vector<color>> mat(h, std::vector<color>(w,color(0)));

	Draw::draw_index(mat, vertices, indices, nullptr, LG, MG);

	generate_color_PPM("./images/cube_lighting.PPM", w, h, mat);
}

void GeoSphere_Lighting(int w,int h) {
	texture2d tex = readBmp("D:/images/woodframe.bmp");
	/*texture2d tex;
	generate_texture(tex);*/
	//初始化矩阵
	matrix44 view;
	view.set_viewport(w, h);
	matrix44 perspective;
	perspective.set_perspective(float(w) / float(h), 90, -10, -100);
	matrix44 camera;
	vec3f eye(0, 0, 10);
	camera.set_camera(eye, vec4f(0, 0, 0), vec4f(0, 1, 0));
	matrix44 p;
	p = perspective * camera;
	p = view * p;
	//初始化图形
	std::vector<vertex> vertices;
	std::vector<uint16_t> indices;
	Geometry::create_GeoSphere(5, 3, vertices, indices);

	//定义光源 及 材质
	LightGroup LG;
	LG.lights[0] = { vec3f(1.0f),0.0f,vec3f(-1.0f).normalize(),0.0f,vec3f(20.0f),0.0f }; // direction light
	LG.lights[1] = { vec3f(1.0f,1.0f,1.0f),0.0f,vec3f(2.0f,3.0f,5.0f).normalize(),20.0f,vec3f(-10.0f,-5.0f,0.0f),0.0f }; //point light
	LG.lights[2] = { vec3f(1.0f,1.0f,1.0f),0.0f,vec3f(4.0f,-5.0f,-6.0f).normalize(),20.0f,vec3f(-6.0f,4.0f,3.0f),5.0f }; //spot light
	LG.NUM_DIR_LIGHTS = 1;
	LG.NUM_POINT_LIGHTS = 1;
	LG.NUM_SPOT_LIGHTS = 1;
	LG.Eye = eye;
	LG.ambientLight = vec3f(0.25f, 0.25f, 0.25f);

	MaterialGroup MG;
	MG.materials[0] = { vec4f(0.85f, 0.5f, 0.8f, 1.0f),vec3f(0.01f,0.01f,0.01f),0.5f };
	MG.useIdx = 0;

	Draw::rasterization(vertices, indices, p, LG, MG, nullptr, h, w, "./images/GeoSphere_lighting.PPM");
}

int main() {

	const int w = 640;
	const int h = 480;
	
	GeoSphere_Lighting(w, h);
	//demo_cube(w, h);

	system("pause");
	return 0;
}