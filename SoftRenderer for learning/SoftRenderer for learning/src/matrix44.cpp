#include"matrix44.h"

const float PI = 3.1415926f;

void set_smallest_magnitude_to_1(vec4f &v) {
	float x = v.x();
	float y = v.y();
	float z = v.z();
	if (x < 0)x = -x;
	if (y < 0)y = -y;
	if (z < 0)z = -z;
	float t = (x > y) ? y : x;
	t = (t > z) ? z : t;
	if (t == x) {
		v.x(1);
	}
	else if (t == y) {
		v.y(1);
	}
	else {
		v.z(1);
	}
}


matrix44::matrix44() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			mat[i][j] = 0;
		}
	}
}

matrix44::~matrix44() {

}

void matrix44::set_identity() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			mat[i][j] = (i == j) ? 1.0f : 0.0f;
		}
	}
}

matrix44 matrix44::set_transformation() {
	matrix44 temp = *this;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			temp.mat[j][i] = mat[i][j];
		}
	}
	return temp;
}

matrix44 matrix44::set_inverse() {
	matrix44 temp;
	temp.set_identity();
	return temp * this->set_transformation();
}

void matrix44::set_rotate(float theta, const vec4f& unit_axis) {
	set_identity();
	float cosT = cos(PI*theta / 180.0f);
	float sinT = sin(PI*theta / 180.0f);
	float u = (unit_axis.x() > 0) ? unit_axis.x() : -unit_axis.x();
	float v = (unit_axis.y() > 0) ? unit_axis.y() : -unit_axis.y();
	float w = (unit_axis.z() > 0) ? unit_axis.z() : -unit_axis.z();
	float u2 = unit_axis.x()*unit_axis.x();
	float v2 = unit_axis.y()*unit_axis.y();
	float w2 = unit_axis.z()*unit_axis.z();

	mat[0][0] = u2 + (1 - u2)*cosT;
	mat[0][1] = u * v*(1 - cosT) - w * sinT;
	mat[0][2] = u * w*(1 - cosT) + v * sinT;
	mat[1][0] = u * v*(1 - cosT) + w * sinT;
	mat[1][1] = v2 + (1 - v2)*cosT;
	mat[1][2] = v * 2 * (1 - cosT) - u * sinT;
	mat[2][0] = u * w*(1 - cosT) - v * sinT;
	mat[2][1] = v * w*(1 - cosT) + u * sinT;
	mat[2][2] = w2 + (1 - w2)*cosT;
}

void matrix44::set_rotate_g(float theta, const vec4f &axis) {//   prefer
	vec4f w = axis.normalize();
	vec4f t = w;
	set_smallest_magnitude_to_1(t);
	vec4f u = cross(t, w).normalize();
	vec4f v = cross(w, u);
	//Ruvw                                               // transform xyz coordinary to uvw coordinary
	matrix44 Ruvw;
	Ruvw.set_identity();
	Ruvw.mat[0][0] = u.x(); Ruvw.mat[0][1] = u.y(); Ruvw.mat[0][2] = u.z();
	Ruvw.mat[1][0] = v.x(); Ruvw.mat[1][1] = v.y(); Ruvw.mat[1][2] = v.z();
	Ruvw.mat[2][0] = w.x(); Ruvw.mat[2][1] = w.y(); Ruvw.mat[2][2] = w.z();

	//Rz                                                 // rotate by z(w) axis
	float cosT = cos(PI*theta / 180);
	float sinT = sin(PI*theta / 180);
	matrix44 Rz;
	Rz.set_identity();
	Rz.mat[0][0] = cosT; Rz.mat[0][1] = -sinT;
	Rz.mat[1][0] = sinT; Rz.mat[1][1] = cosT;

	//Ruvw(T)                                            // transform uvw coordinary to xyz coordinary
	matrix44 Ruvw_t = Ruvw.set_transformation();

	matrix44 temp = Rz * Ruvw;
	*this = Ruvw_t * temp;
}

void matrix44::set_normal_transform(const matrix44& transpos) {
	set_identity();
	matrix44 temp = transpos;
	for (int i = 0; i < 2; i++) {                             //将变换矩阵中的位移清理 因为法向量不需要位移
		temp.mat[i][3] = 0;
	}
	*this = temp.set_inverse().set_transformation();     //(A^-1)^T 变换矩阵逆的转置矩阵
}

void matrix44::set_scale(float sx, float sy, float sz) {
	set_identity();
	mat[0][0] = sx;
	mat[1][1] = sy;
	mat[2][2] = sz;
}

void matrix44::set_translate(float nx, float ny, float nz) {
	set_identity();
	mat[0][3] = nx;
	mat[1][3] = ny;
	mat[2][3] = nz;
}


void matrix44::set_shearing_x(float dy, float dz) {
	set_identity();
	mat[0][1] = dy;
	mat[0][2] = dz;
}
void matrix44::set_shearing_y(float dx, float dz) {
	set_identity();
	mat[0][0] = dx;
	mat[0][2] = dz;
}
void matrix44::set_shearing_z(float dx, float dy) {
	set_identity();
	mat[0][0] = dx;
	mat[0][1] = dy;
}

void matrix44::set_viewport(float nx, float ny) {
	set_identity();
	mat[0][0] = nx / 2.0f;
	mat[0][3] = (nx - 1) / 2.0f;
	mat[1][1] = ny / 2.0f;
	mat[1][3] = (ny - 1) / 2.0f;
}

void matrix44::set_camera(const vec4f &eye, const vec4f &lookat, const vec4f &vup) {
	vec4f w = -(lookat - eye).normalize();
	vec4f u = cross(vup, w).normalize();
	vec4f v = cross(w, u);

	matrix44 Translate;
	Translate.set_translate(-eye.x(), -eye.y(), -eye.z());

	matrix44 Ruvw;
	Ruvw.set_identity();
	Ruvw.mat[0][0] = u.x(); Ruvw.mat[0][1] = u.y(); Ruvw.mat[0][2] = u.z();
	Ruvw.mat[1][0] = v.x(); Ruvw.mat[1][1] = v.y(); Ruvw.mat[1][2] = v.z();
	Ruvw.mat[2][0] = w.x(); Ruvw.mat[2][1] = w.y(); Ruvw.mat[2][2] = w.z();
	*this = Ruvw * Translate;
}

void matrix44::set_orthorgraphic_offCenter(const vec4f &left_corner, const vec4f &right_corner) {
	set_identity();
	float rml = right_corner.x() - left_corner.x();
	float ral = right_corner.x() + left_corner.x();
	float tmb = right_corner.x() - left_corner.x();
	float tab = right_corner.x() + left_corner.x();
	float nmf = left_corner.z() - right_corner.z();
	float naf = left_corner.z() + right_corner.z();
	mat[0][0] = 2.0f / rml;
	mat[1][1] = 2.0f / tmb;
	mat[2][2] = 2.0f / nmf;
	mat[0][3] = -ral / rml;
	mat[1][3] = -tab / tmb;
	mat[2][3] = -naf / nmf;
}

void matrix44::set_perspective_offCenter(const vec4f &left_bottom_corner, const vec4f &right_top_corner) {
	matrix44 othor;
	othor.set_orthorgraphic_offCenter(left_bottom_corner, right_top_corner);
	matrix44 p;
	p.set_identity();
	p.mat[0][0] = left_bottom_corner.z();
	p.mat[1][1] = left_bottom_corner.z();
	p.mat[2][2] = left_bottom_corner.z() + right_top_corner.z();
	p.mat[2][3] = -(left_bottom_corner.z()*right_top_corner.z());
	p.mat[3][2] = 1;
	p.mat[3][3] = 0;
	*this = othor * p;
}

void matrix44::set_orthorgraphic(float w, float aspect, float n, float f) {
	set_identity();
	float h = w / aspect;
	mat[0][0] = 2.0f / w;
	mat[1][1] = 2.0f / h;
	mat[2][2] = -1.0f / (f - n);
	mat[2][3] = n / (f - n);
}
void matrix44::set_perspective(float aspect, float theta, float n, float f) {
	matrix44 orthor;
	float tanHalfT = tan(PI*theta / 180 / 2);
	float h = -2 * n *tanHalfT;
	float w = h * aspect;
	orthor.set_orthorgraphic(w, aspect, n, f);
	matrix44 p;
	p.set_identity();
	p.mat[0][0] = n;
	p.mat[1][1] = n;
	p.mat[2][2] = n + f;
	p.mat[2][3] = -(n + f);
	p.mat[3][2] = 1;
	p.mat[3][3] = 0;
	*this = orthor * p;
}

void matrix44::set_inverse_perspective(float aspect, float theta, float n, float f, float z) {
	matrix44 orthor;
	float tanHalfT = tan(PI*theta / 180 / 2);
	float h = -2 * n *tanHalfT;
	float w = h * aspect;
	orthor.set_orthorgraphic(w, aspect, n, f);
	matrix44 p;
	p.set_identity();
	p.mat[0][0] = f;
	p.mat[1][1] = f;
	p.mat[2][2] = 0;
	p.mat[2][3] = f * n;
	p.mat[3][2] = -1;
	p.mat[3][3] = n + f;
	*this = p * orthor.set_inverse();
}

matrix44 matrix44::operator*(const matrix44 &m) {
	matrix44 n;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			n.mat[i][j] = mat[i][0] * m.mat[0][j] + mat[i][1] * m.mat[1][j] + mat[i][2] * m.mat[2][j] + mat[i][3] * m.mat[3][j];
		}
	}
	return n;
}

vec4f matrix44::operator*(const vec4f &v) const {
	vec4f nv;
	nv.x(mat[0][0] * v.x() + mat[0][1] * v.y() + mat[0][2] * v.z() + mat[0][3] * v.w());
	nv.y(mat[1][0] * v.x() + mat[1][1] * v.y() + mat[1][2] * v.z() + mat[1][3] * v.w());
	nv.z(mat[2][0] * v.x() + mat[2][1] * v.y() + mat[2][2] * v.z() + mat[2][3] * v.w());
	nv.w(mat[3][0] * v.x() + mat[3][1] * v.y() + mat[3][2] * v.z() + mat[3][3] * v.w());
	nv = nv / nv.w();
	return nv;
}

//matrix44& matrix44::operator=(const matrix44 &m) {
//	for (int i = 0; i < 4; i++) {
//		for (int j = 0; j < 4; j++) {
//			mat[i][j] = m.mat[i][j];
//		}
//	}
//	return *this;
//}