#include<fstream>
#include<iostream>
#include"vec3f.h"
#include"matrix44.h"
#include"Draw.h"
#include"color.h"
#include"sample.h"
#include"ioimages.h"




void demo_color_triangle(int w, int h) {
	color **mat = new color*[h];
	for (int i = 0; i < h; i++) {
		*(mat + i) = new color[w];
	}

	vertex v[3] = { vertex(vec3f(-20, 0, -40), color(255, 0, 0)) ,         //counterclockwise
		vertex(vec3f(20, 0, -40), color(0, 255, 0)) ,
		vertex(vec3f(0, 20, -40), color(0, 0, 255)) };

	matrix44 view;
	view.set_viewport(w, h);
	matrix44 perspective;
	perspective.set_perspective(float(w) / float(h), 60, -10, -100);
	matrix44 camera;
	camera.set_camera(vec3f(0, 0, 0), vec3f(0, 0, -1), vec3f(0, 1, 0));
	matrix44 p;
	p = perspective * camera;
	p = view * p;
	for (int i = 0; i < 3; i++) {
		v[i]._pos = p * v[i]._pos;
		std::cout << v[i]._pos << std::endl;
	}
	Draw::draw_triangle(mat, v, w, h);
	//for color test
	generate_color_PPM("./images/color_triangles_1.PPM", w, h, mat);
}

void demo_hiden_surface(int w, int h) {
	color **mat = new color*[h];
	for (int i = 0; i < h; i++) {
		*(mat + i) = new color[w];
	}

	vertex v[6] = { vertex(vec3f(-20, 0, -40), color(255, 0, 0)) ,         //counterclockwise
		vertex(vec3f(20, 0, -40), color(255, 0, 0)) ,
		vertex(vec3f(0, 20, -40), color(255, 0, 0)) ,
		vertex(vec3f(-30, 10, -60), color(0, 0, 255)) ,         //counterclockwise
		vertex(vec3f(10, 10, -20), color(0, 0, 255)) ,
		vertex(vec3f(0, 10, -60), color(0, 0, 255)) };

	matrix44 view;
	view.set_viewport(w, h);
	matrix44 perspective;
	perspective.set_perspective(float(w) / float(h), 60, -10, -100);
	matrix44 camera;
	camera.set_camera(vec3f(0, 0, 0), vec3f(0, 0, -1), vec3f(0, 1, 0));
	matrix44 p;
	p = perspective * camera;
	p = view * p;
	for (int i = 0; i < 6; i++) {
		v[i]._pos = p * v[i]._pos;
		std::cout << v[i]._pos << std::endl;
	}


	Draw::draw_triangles(mat, v, 6, w, h,true);

	generate_color_PPM("./images/hiden_surface_1.PPM", w, h, mat);
}


void demo_texture(int w,int h) {
	//初始化贴图
	texture2d tex = readBmp("D:/images/woodtexture.bmp");
	//初始化矩阵
	matrix44 view;
	view.set_viewport(w, h);
	matrix44 perspective;
	perspective.set_perspective(float(w) / float(h), 60, -10, -100);
	matrix44 camera;
	camera.set_camera(vec3f(0, 0, 0), vec3f(0, 0, -1), vec3f(0, 1, 0));
	matrix44 p;
	p = perspective * camera;
	p = view * p;
	//初始化图形

	int texcoord_wid = (tex._width - w) >= 0 ? (w - 1) : tex._width - 1;
	int texcoord_het = (tex._height - h) >= 0 ? (h - 1) : tex._height - 1;

	vertex v[4] = { vertex(vec3f(-20,-20,-30),color(0),textcoord(0,0)),
		vertex(vec3f(20,-20,-30),color(0),textcoord(texcoord_wid,0)),
		vertex(vec3f(20,20,-30),color(0),textcoord(texcoord_wid,texcoord_het)),
		vertex(vec3f(-20,20,-30),color(0),textcoord(0,texcoord_het)) };
	for (int i = 0; i < 4; i++) {
		v[i]._pos = p * v[i]._pos;
	}
	//初始化像素矩阵
	color **mat = new color*[h];
	for (int i = 0; i < h; i++) {
		*(mat + i) = new color[w];
	}

	//绘制图形 
	vertex temp[3] = { v[0],v[1],v[2] };
	vertex temp2[3] = { v[0],v[2],v[3] };
	Draw::draw_triangle_texture(mat, temp, w, h, tex,true);
	Draw::draw_triangle_texture(mat, temp2, w, h, tex,true);

	generate_color_PPM("./images/flat_texture_1.PPM", w, h, mat);
}

void demo_cube(int w, int h) {
	texture2d tex = readBmp("D:/images/woodframe.bmp");
	//初始化矩阵
	matrix44 view;
	view.set_viewport(w, h);
	matrix44 perspective;
	perspective.set_perspective(float(w) / float(h), 90, -10, -100);
	matrix44 camera;
	camera.set_camera(vec3f(20,20,0), vec3f(0, 0, -30), vec3f(0, 1, 0));
	matrix44 p;
	p = perspective * camera;
	p = view * p;
	//初始化图形

	int texcoord_wid = (tex._width - w) >= 0 ? (w - 1) : tex._width - 1;
	int texcoord_het = (tex._height - h) >= 0 ? (h - 1) : tex._height - 1;

	vertex v[8] = { vertex(vec3f(-10,-10,-30),color(0),textcoord(0,0)),
		vertex(vec3f(10,-10,-30),color(0),textcoord(texcoord_wid,0)),
		vertex(vec3f(10,10,-30),color(0),textcoord(texcoord_wid,texcoord_het)),
		vertex(vec3f(-10,10,-30),color(0),textcoord(0,texcoord_het)) ,

		vertex(vec3f(-10,-10,-50),color(0),textcoord(texcoord_wid,0)),
		vertex(vec3f(10,-10,-50),color(0),textcoord(0,0)),
		vertex(vec3f(10,10,-50),color(0),textcoord(0,texcoord_het)),
		vertex(vec3f(-10,10,-50),color(0),textcoord(texcoord_wid,texcoord_het))
	};
	for (int i = 0; i < 8; i++) {
		v[i]._pos = p * v[i]._pos;
	}
	//初始化像素矩阵
	color **mat = new color*[h];
	for (int i = 0; i < h; i++) {
		*(mat + i) = new color[w];
	}

	//绘制图形 
	vertex temp1[3] = { v[0],v[1],v[2] };
	vertex temp2[3] = { v[0],v[2],v[3] };

	vertex temp3[3] = { v[0],v[3],v[4] };
	vertex temp4[3] = { v[4],v[3],v[7] };

	vertex temp5[3] = { v[4],v[7],v[5] };
	vertex temp6[3] = { v[5],v[7],v[6] };

	vertex temp7[3] = { v[5],v[6],v[2] };
	vertex temp8[3] = { v[5],v[2],v[1] };

	vertex temp9[3] = { v[5],v[1],v[0] };
	vertex tempA[3] = { v[5],v[0],v[4] };

	vertex tempB[3] = { v[6],v[7],v[2] };
	vertex tempC[3] = { v[3],v[2],v[7] };
	//前面
	Draw::draw_triangle_texture(mat, temp1, w, h, tex, true);
	Draw::draw_triangle_texture(mat, temp2, w, h, tex, true);

	//左侧面
	Draw::draw_triangle_texture(mat, temp3, w, h, tex, true);
	Draw::draw_triangle_texture(mat, temp4, w, h, tex, true);
	
	//后面
	Draw::draw_triangle_texture(mat, temp5, w, h, tex, true);
	Draw::draw_triangle_texture(mat, temp6, w, h, tex, true);
	
	//右侧面
	Draw::draw_triangle_texture(mat, temp7, w, h, tex, true);
	Draw::draw_triangle_texture(mat, temp8, w, h, tex, true);

	//下面
	Draw::draw_triangle_texture(mat, temp9, w, h, tex, true);
	Draw::draw_triangle_texture(mat, tempA, w, h, tex, true);

	//上面
	Draw::draw_triangle_texture(mat, tempB, w, h, tex, true);
	Draw::draw_triangle_texture(mat, tempC, w, h, tex, true);

	generate_color_PPM("./images/cube_texture_1.PPM", w, h, mat);
}

int main() {

	const int w = 640;
	const int h = 480;
	
	system("pause");
	return 0;
}