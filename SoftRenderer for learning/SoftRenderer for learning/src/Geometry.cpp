#include "Geometry.h"

float interp(float a, float b, float t) {
	return a + (b - a)*t;
}

vec3f interp(const vec3f& v1, const vec3f& v2, float t) {
	return vec3f(interp(v1._x, v2._x, t),
		interp(v1._y, v2._y, t),
		interp(v1._z, v2._z, t));
}

vec4f interp(const vec4f& v1, const vec4f& v2, float t) {
	return vec4f(interp(v1.xyz(), v2.xyz(), t));
}


void Geometry::create_GeoSphere(float radius, uint32_t numSubdivisions , std::vector<vertex>& vertice, std::vector<std::uint16_t>& indice) {
	const float X = 0.525731f;
	const float Z = 0.850651f;
	std::vector<vertex> vertices = {
		vertex({vec3f(-X,0.0f,Z)}),
		vertex({vec3f(X,0.0f,Z)}),
		vertex({vec3f(-X,0.0f,-Z)}),
		vertex({vec3f(X,0.0f,-Z)}),
		vertex({vec3f(0.0f,Z,X)}),
		vertex({vec3f(0.0f,Z,-X)}),
		vertex({vec3f(0.0f,-Z,X)}),
		vertex({vec3f(0.0f,-Z,-X)}),
		vertex({vec3f(Z,X,0.0f)}),
		vertex({vec3f(-Z,X,0.0f)}),
		vertex({vec3f(Z,-X,0.0f)}),
		vertex({vec3f(-Z,-X,0.0f)})
	};

	for (auto& it : vertices) {
		it._pos = it._normal = it._posW.normalize();
		it._pos = it._pos*radius;
		it._posW = it._pos.xyz();
	}

	std::vector<std::uint16_t> indices = {
		1,4,0,  4,9,0,  4,5,9,  8,5,4,  1,8,4,
		1,10,8,  10,3,8,  8,3,5,  3,2,5,  3,7,2,
		3,10,7,  10,6,7,  6,11,7,  6,0,11,  6,1,0,
		10,1,6,  11,0,9,  2,11,9,  5,2,9,  11,2,7
	};


	for (int i = 0; i < numSubdivisions; i++) {
		int times = indices.size() / 3;
		int CurrVertexIdx = vertices.size(); //recorded the end of vertices
		int CurrIndiceIdx = 0;
		for (int j = 0; j < times; j++, CurrIndiceIdx += 12, CurrVertexIdx += 3) {  //subdivide one triangle to four,so we gonna jump 12 vertex indices
			vertices.push_back(vertex(interp(vertices[indices[CurrIndiceIdx]]._pos, vertices[indices[CurrIndiceIdx + 1]]._pos, 0.5f),
				interp(vertices[indices[CurrIndiceIdx]]._normal, vertices[indices[CurrIndiceIdx + 1]]._normal, 0.5f).normalize(),
				textcoord(interp(vertices[indices[CurrIndiceIdx]]._tc._u, vertices[indices[CurrIndiceIdx + 1]]._tc._u, 0.5f),
					interp(vertices[indices[CurrIndiceIdx]]._tc._v, vertices[indices[CurrIndiceIdx + 1]]._tc._v, 0.5f)))); //m0
			vertices[CurrVertexIdx]._pos = vertices[CurrVertexIdx]._pos.normalize()*radius;
			vertices[CurrVertexIdx]._posW = vertices[CurrVertexIdx]._pos.xyz();

			vertices.push_back(vertex(interp(vertices[indices[CurrIndiceIdx + 1]]._pos, vertices[indices[CurrIndiceIdx + 2]]._pos, 0.5f),
				interp(vertices[indices[CurrIndiceIdx + 1]]._normal, vertices[indices[CurrIndiceIdx + 2]]._normal, 0.5f).normalize(),
				textcoord(interp(vertices[indices[CurrIndiceIdx + 1]]._tc._u, vertices[indices[CurrIndiceIdx + 2]]._tc._u, 0.5f),
					interp(vertices[indices[CurrIndiceIdx + 1]]._tc._v, vertices[indices[CurrIndiceIdx + 2]]._tc._v, 0.5f)))); //m0
			vertices[CurrVertexIdx + 1]._pos = vertices[CurrVertexIdx + 1]._pos.normalize()*radius;
			vertices[CurrVertexIdx + 1]._posW = vertices[CurrVertexIdx + 1]._pos.xyz();

			vertices.push_back(vertex(interp(vertices[indices[CurrIndiceIdx]]._pos, vertices[indices[CurrIndiceIdx + 2]]._pos, 0.5f),
				interp(vertices[indices[CurrIndiceIdx]]._normal, vertices[indices[CurrIndiceIdx + 2]]._normal, 0.5f).normalize(),
				textcoord(interp(vertices[indices[CurrIndiceIdx]]._tc._u, vertices[indices[CurrIndiceIdx + 2]]._tc._u, 0.5f),
					interp(vertices[indices[CurrIndiceIdx]]._tc._v, vertices[indices[CurrIndiceIdx + 2]]._tc._v, 0.5f)))); //m0
			vertices[CurrVertexIdx + 2]._pos = vertices[CurrVertexIdx + 2]._pos.normalize()*radius;
			vertices[CurrVertexIdx + 2]._posW = vertices[CurrVertexIdx + 2]._pos.xyz();

			//insert m0,m2 .consist triangle (p0 m0 m2)
			indices.insert(indices.begin() + CurrIndiceIdx + 1, CurrVertexIdx);    //m0
			indices.insert(indices.begin() + CurrIndiceIdx + 2, CurrVertexIdx + 2); //m2
			//insert m1,m0 .consist triangle (p1,m1,m0)
			indices.insert(indices.begin() + CurrIndiceIdx + 4, CurrVertexIdx + 1);      //m1
			indices.insert(indices.begin() + CurrIndiceIdx + 5, CurrVertexIdx);  //m0
			//insert m2,m1 .consist triangle  (p2,m2,m1)
			indices.insert(indices.begin() + CurrIndiceIdx + 7, CurrVertexIdx + 2);      //m2
			indices.insert(indices.begin() + CurrIndiceIdx + 8, CurrVertexIdx + 1);  //m1

			//insert m0,m1,m2.consist triangle (m0,m1,m2)
			indices.insert(indices.begin() + CurrIndiceIdx + 9, CurrVertexIdx);
			indices.insert(indices.begin() + CurrIndiceIdx + 10, CurrVertexIdx + 1);
			indices.insert(indices.begin() + CurrIndiceIdx + 11, CurrVertexIdx + 2);
		}
	}
	vertice = std::move(vertices);
	indice = std::move(indices);
}
