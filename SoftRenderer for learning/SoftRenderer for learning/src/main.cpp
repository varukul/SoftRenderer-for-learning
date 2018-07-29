#include<fstream>
#include<iostream>
#include"vec3f.h"
#include"matrix44.h"
#include"Draw.h"
#include"color.h"
#include"sample.h"

void generate_color_PPM(const char *filename, const int &w, const int &h, color **mat) {

	std::ofstream outfile;
	outfile.open(filename, std::ios::out);
	outfile << "P3\n" << w << " " << h << "\n" << "255\n";
	if (!outfile.is_open()) {
		std::cout << "failed to open file" << std::endl;
		return;
	}
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			outfile << mat[i][j]._r << " " << mat[i][j]._g << " " << mat[i][j]._b << "\n";
		}
	}
	outfile.close();
}



void demo_cube(int w, int h) {

	color **mat = new color*[h];
	for (int i = 0; i < h; i++) {
		*(mat + i) = new color[w];
	}

	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			mat[i][j] = 0;
		}
	}

	matrix44 camera;
	matrix44 viewport;
	matrix44 perspective;
	matrix44 othorgraphic;
	matrix44 perspective_off;
	matrix44 othorgraphic_off;
	matrix44 trans;
	matrix44 p;

	camera.set_camera(vec3f(-40, 30, 0), vec3f(20, -20, -70), vec3f(0, 1, 0));
	viewport.set_viewport(w, h);
	othorgraphic.set_orthorgraphic(200, (float)w / (float)h, 0, 300);
	perspective.set_perspective((float)w / (float)h, 60, -10, 1000);
	othorgraphic_off.set_orthorgraphic_offCenter(vec3f(-50, -50, -10), vec3f(500, 500, -1100));
	perspective_off.set_perspective_offCenter(vec3f(-50, -50, -10), vec3f(500, 500, -1100));
	//p = camera;
	//p = viewport;
	p = othorgraphic * camera;
	//p = perspective * camera;
	//p = perspective_off * camera;
	p = viewport * p;

	vec3f lbfc(-20, -20, -30);
	vec3f rbfc(20, -20, -30);
	vec3f lbbc(-20, -20, -70);
	vec3f rbbc(20, -20, -70);
	vec3f ltfc(-20, 20, -30);
	vec3f rtfc(20, 20, -30);
	vec3f ltbc(-20, 20, -70);
	vec3f rtbc(20, 20, -70);

	vec3f v[8] = { lbfc,rbfc,lbbc,rbbc,ltfc,rtfc,ltbc,rtbc };
	for (int i = 0; i < 8; i++) {
		v[i] = p * v[i];
		std::cout << v[i] << "\n";
	}

	//cube test
	Draw::drawline(mat, v[0]._x, v[0]._y, v[1]._x, v[1]._y, w, h);
	Draw::drawline(mat, v[0]._x, v[0]._y, v[2]._x, v[2]._y, w, h);
	Draw::drawline(mat, v[0]._x, v[0]._y, v[4]._x, v[4]._y, w, h);

	Draw::drawline(mat, v[6]._x, v[6]._y, v[4]._x, v[4]._y, w, h);
	Draw::drawline(mat, v[6]._x, v[6]._y, v[2]._x, v[2]._y, w, h);
	Draw::drawline(mat, v[6]._x, v[6]._y, v[7]._x, v[7]._y, w, h);

	Draw::drawline(mat, v[3]._x, v[3]._y, v[2]._x, v[2]._y, w, h);
	Draw::drawline(mat, v[3]._x, v[3]._y, v[7]._x, v[7]._y, w, h);
	Draw::drawline(mat, v[3]._x, v[3]._y, v[1]._x, v[1]._y, w, h);

	Draw::drawline(mat, v[5]._x, v[5]._y, v[4]._x, v[4]._y, w, h);
	Draw::drawline(mat, v[5]._x, v[5]._y, v[1]._x, v[1]._y, w, h);
	Draw::drawline(mat, v[5]._x, v[5]._y, v[7]._x, v[7]._y, w, h);

	//for old test
	generate_color_PPM("./images/perspective_triangles_3.PPM", w, h, mat);

	for (int i = 0; i < h; i++) {
		delete[]mat[i];
	}
	delete[]mat;
	mat = NULL;
}

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
	//

	for (int i = 0; i < h; i++) {
		delete[]mat[i];
	}
	delete[]mat;
	mat = NULL;
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

	for (int i = 0; i < h; i++) {
		delete[]mat[i];
	}
	delete[]mat;
	mat = NULL;
}

void demo_sample(int w, int h) {
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


	Draw::draw_triangles(mat, v, 6, w, h, true);

	boxfilter b(10);
	mat=sample::filter_image(mat, &b, w, h);

	generate_color_PPM("./images/box_sample_image_1.PPM", w, h, mat);

	for (int i = 0; i < h; i++) {
		delete[]mat[i];
	}
	delete[]mat;
	mat = NULL;
}

int main() {

	const int w = 640;
	const int h = 480;

	demo_sample(w, h);

	system("pause");
	return 0;
}