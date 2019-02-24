#include"Lighting.h"
float max(float a, float b) {
	return a > b ? a : b;
}

float saturate(float num) {
	return num > 1 ? 1 : max(num, 0);
}

float CalcAttenuation(float d, float falloffStart, float falloffEnd) {
	return saturate((falloffEnd - d) / (falloffEnd - falloffStart));
}

vec3f SchlickFresnel(vec3f R0, vec3f normal, vec3f lightVec) {
	float cosIncidentAngle = saturate(dot(normal, lightVec));
	float f0 = 1.0f - cosIncidentAngle;
	vec3f reflectPercent = R0 - (R0 - 1.0f)*(f0*f0*f0*f0*f0);
	return reflectPercent;
}

vec3f BlinnPhong(vec3f lightSrength, vec3f lightVec, vec3f normal, vec3f toEye, Material mat) {
	const float m = mat.Shininess*256.0f;
	vec3f halfVec = (toEye + lightVec).normalize();
	float roughnessFactor = (m + 8.0f)*pow(max(dot(halfVec, normal), 0.0f), m) / 8.0f;
	vec3f fresnelFactor = SchlickFresnel(mat.FresnelR0, halfVec, lightVec);
	vec3f specAlbedo = fresnelFactor * roughnessFactor;
	specAlbedo = specAlbedo / (specAlbedo + 1.0f);
	return (specAlbedo + mat.DiffuseAlbedo.xyz()) * lightSrength;
}

vec3f ComputeDirectionLight(Light L, Material mat, vec3f normal, vec3f toEye) {
	vec3f lightVec = -L.Direction;
	float ndotl = max(dot(lightVec, normal), 0.0f);
	vec3f lightStrength = L.Strength*ndotl;
	return BlinnPhong(lightStrength, lightVec, normal, toEye, mat);
}

vec3f ComputePointLight(Light L, Material mat, vec3f pos, vec3f normal, vec3f toEye) {
	vec3f lightVec = L.Position - pos;
	float d = lightVec.squared_length();
	if (d > L.FalloffEnd)return 0.0f;
	lightVec = lightVec / d;
	float ndotl = max(dot(lightVec, normal), 0.0f);
	vec3f lightStrength = L.Strength*ndotl;                   //lambert cos law
	float att = CalcAttenuation(d, L.FalloffStart, L.FalloffEnd);
	lightStrength = lightStrength * att;

	return BlinnPhong(lightStrength, lightVec, normal, toEye, mat);
}

vec3f ComputeSpotLight(Light L, Material mat, vec3f pos, vec3f normal, vec3f  toEye) {
	vec3f lightVec = L.Position - pos;
	float d = lightVec.squared_length();
	if (d > L.FalloffEnd)return 0.0f;
	lightVec = lightVec / d;
	float ndotl = max(dot(lightVec, normal), 0.0f);
	vec3f lightStrength = L.Strength*ndotl;

	float spotFactor = pow(max(dot(-lightVec, L.Direction), 0.0f), L.SpotPower);
	lightStrength = lightStrength * spotFactor;

	float att = CalcAttenuation(d, L.FalloffStart, L.FalloffEnd);
	lightStrength = lightStrength * att;
	return BlinnPhong(lightStrength, lightVec, normal, toEye, mat);
}

vec4f ComputeLighting(const LightGroup& LG, const Material& mat, vec3f Pos, vec3f normal, vec3f toEye, vec3f shadowFactor) {
	vec3f result = 0.0f;

	uint16_t NUM_DIR_LIGHTS = LG.NUM_DIR_LIGHTS;
	uint16_t NUM_POINT_LIGHTS = LG.NUM_POINT_LIGHTS;
	uint16_t NUM_SPOT_LIGHTS = LG.NUM_SPOT_LIGHTS;
	auto& lights = LG.lights;
	//float shadow[3] = { shadowFactor._x,shadowFactor._y,shadowFactor._z };
	int i = 0;
	for (i = 0; i < NUM_DIR_LIGHTS; ++i) {
		result = result + ComputeDirectionLight(lights[i], mat, normal, toEye); /** shadow[i]*/
	}

	for (i = NUM_DIR_LIGHTS; i < NUM_DIR_LIGHTS + NUM_POINT_LIGHTS; ++i) {
		result = result + ComputePointLight(lights[i], mat, Pos, normal, toEye);
	}

	for (i = NUM_DIR_LIGHTS + NUM_POINT_LIGHTS; i < NUM_DIR_LIGHTS + NUM_POINT_LIGHTS + NUM_SPOT_LIGHTS; ++i) {
		result = result + ComputePointLight(lights[i], mat, Pos, normal, toEye);
	}
	return vec4f(result);
}