#pragma once
#include<vector>
#include"vertex.h"
#include"color.h"
#include"matrix44.h"
#include"Lighting.h"
#include"ioimages.h"

namespace Draw {

	void rasterization(std::vector<vertex>& vertices,
		const std::vector<uint16_t>& indices,
		const matrix44& M,
		const LightGroup& LG,
		const MaterialGroup& MG,
		texture2d* texture,
		int height,int width ,
		const char* outputFileName,
		bool enableDepthTest = true);


	 //   Bresenham
	//void drawline(std::vector<std::vector<color>>& mat, const vertex &v1, const vertex &v2, int w, int h, bool enable_depth_test = true);
	//void drawlines(std::vector<std::vector<color>>& mat, const vertex v[], const int length, int w, int h, bool enable_depth_test = true);
	
	/*void draw_triangles(std::vector<std::vector<color>>& mat,
		const std::vector<vertex>& vertices,
		const texture2d *texture,
		bool enable_depth_test = true);
	
	void draw_adjacent_triangles(std::vector<std::vector<color>>& mat,
		const std::vector<vertex>& vertices,
		const texture2d *texture,
		bool enable_depth_test = true);*/
	
	void draw_triangle(std::vector<std::vector<color>>& mat,
		const std::vector<vertex>& vertices,
		const std::vector<uint16_t>& indices,
		const texture2d *texture,
		const LightGroup& LG,
		const MaterialGroup& MG,
		bool enable_depth_test = true);

	void draw_index(std::vector<std::vector<color>>& mat, 
		const std::vector<vertex>& vertices,
		const std::vector<uint16_t>& indices,
		const texture2d *texture,
		const LightGroup& LG,
		const MaterialGroup& MG,
		bool enable_depth_test = true);

	float interp_num(float n1, float n2, float p);
	float interp_line(float x1, float y1, float x2, float y2, float tx, float ty);
	color interpTriangleColor(const vertex &v0, const vertex &v1, const vertex &v2, float x, float y,const LightGroup& LG,const MaterialGroup& MG);
	color interpTriangleTexture(const vertex &v0, const vertex &v1, const vertex &v2, float x, float y, const texture2d &texture);
	
}