#pragma once
#include"vec.h"
#include<array>

constexpr uint16_t MAX_LIGHTS = 16;
constexpr uint16_t MAX_MATERIALS = 16;

struct Light {
	vec3f Strength;           //光强
	float FalloffStart;       //FalloffEnd-FalloffStart 光强衰减范围
	vec3f Direction;
	float FalloffEnd;
	vec3f Position;
	float SpotPower;          //用于近似聚光灯角度的大小
};

struct Material {
	vec4f DiffuseAlbedo;
	vec3f FresnelR0;
	float Shininess;
};

struct LightGroup {
	std::array<Light, MAX_LIGHTS> lights;
	uint16_t NUM_DIR_LIGHTS;           //direction light 的数量
	uint16_t NUM_POINT_LIGHTS;               //point light 的数量
	uint16_t NUM_SPOT_LIGHTS;                //spot light 的数量
	vec3f Eye;
	vec3f ambientLight;
};

struct MaterialGroup {
	std::array<Material, MAX_MATERIALS> materials;
	uint16_t useIdx;                   //要使用的材质索引
};

vec4f ComputeLighting(const LightGroup& LG, const Material& mat, vec3f Pos, vec3f normal, vec3f toEye, vec3f shadowFactor);