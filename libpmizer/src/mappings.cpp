#include <pmize/mappings.h>

#include <cmath>
#include <limits>


namespace pmize {

double normalized(const int value, const int factor) {
	return /*1.0 -*/ static_cast<double>(value) / factor;
}


vec<2> normalized(const int x, const int y, const int width, const int height) {
	return { normalized(x, width), normalized(y, height) };
}


int unnormalized(const double value, const int factor) {
	return static_cast<int>(value * factor);
}


::std::tuple<int, int> unnormalized(const vec<2> v, const int width, const int height) {
	using namespace ::boost::qvm;
	return { unnormalized(X(v), width), unnormalized(Y(v), height) };
}


vec<3> to_sphere(const vec<2> v, const double radius) {
	using namespace ::boost::qvm;
	return { 2 * M_PI * X(v), M_PI * Y(v) - M_PI_2, radius };
}


vec<3> spherical_to_cartesian(const vec<3> v) {
	using namespace ::std;
	using namespace ::boost::qvm;
	return {
		Z(v) * cos(Y(v)) * cos(X(v)),
		Z(v) * sin(Y(v)),
		Z(v) * cos(Y(v)) * sin(X(v))
	};
}


vec<3> cartesian_to_spherical(const vec<3> v) {
	using namespace ::std;
	using namespace ::boost::qvm;

	const auto atan = atan2(Z(v), X(v));
	return {
		atan > 0.0 ? atan : 2 * M_PI + atan,
		acos(Y(v))
	};
}


double norm_infinity(const vec<3> v) {
	using namespace ::std;
	using namespace ::boost::qvm;
	return max(abs(X(v)), max(abs(Y(v)), abs(Z(v))));
}


vec<3> sphere_to_cube(const vec<3> v) {
	using namespace ::boost::qvm;
	return v * (mag(v) / norm_infinity(v));
}


vec<3> cube_to_sphere(const vec<3> v) {
	using namespace ::boost::qvm;
	return v * (norm_infinity(v) / mag(v));
}


::std::tuple<CubeFace, vec<2>> to_cube_map(const vec<3> v) {
	using namespace ::std;
	using namespace ::boost::qvm;
	const auto eps = 2*numeric_limits<double>::epsilon();
	const auto to_01 = [](const vec<2> w) {
		using namespace ::boost::qvm;
		return vec<2>{ X(w) + 1, Y(w) + 1 } * 0.5;
	};

	mat<double, 3, 3> mirror;
	set_identity(mirror);
	A00(mirror) = -1.0;
	
	auto face = CubeFace::Top;
	mat<double, 3, 3> transform;
	if (abs(Z(v) - 1.0) < eps) {
		face = CubeFace::Front;
		transform = rot_mat<3>(vec<3>{0, 1, 0}, M_PI);
	}
	else if (abs(Z(v) + 1.0) < eps) {
		face = CubeFace::Back;
		set_identity(transform);
	}
	else if (abs(X(v) - 1.0) < eps) {
		face = CubeFace::Left;
		transform = rot_mat<3>(vec<3>{ 0, 1, 0 }, M_PI_2);
	}
	else if (abs(X(v) + 1.0) < eps) {
		face = CubeFace::Right;
		transform = rot_mat<3>(vec<3>{ 0, 1, 0 }, -M_PI_2);
	}
	else if (abs(Y(v) - 1.0) < eps) {
		face = CubeFace::Bottom;
		transform = rot_mat<3>(vec<3>{ 1, 0, 0 }, M_PI_2) * mirror;
	}
	else {
		face = CubeFace::Top;
		transform = rot_mat<3>(vec<3>{ 1, 0, 0 }, -M_PI_2) * mirror;
	}

	return { face, to_01(XY(transform * v)) };
}

}