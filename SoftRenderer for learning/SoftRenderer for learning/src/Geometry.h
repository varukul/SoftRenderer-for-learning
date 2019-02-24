#pragma once
#include"vertex.h"

namespace Geometry {
	void create_GeoSphere(float radius, uint32_t numSubdivisions, std::vector<vertex>& vertice, std::vector<std::uint16_t>& indice);
}

