#pragma once

#include <cpp11/strings.hpp>
#include <cpp11/doubles.hpp>
#include "cgal_types.h"
#include "geometry_vector.h"
#include "exact_numeric.h"
#include "intersection.h"
#include "distance.h"

class segment2 : public geometry_vector<Segment_2, 2> {
public:
  using geometry_vector::geometry_vector;
  ~segment2() = default;

  Primitive geometry_type() const { return SEGMENT; }

  size_t cardinality(size_t i) const { return 2; }
  size_t long_length() const { return size() * 2; }

  cpp11::writable::strings def_names() const {
    return {"x", "y"};
  }

  Exact_number get_single_definition(size_t i, int which, int element) const {
    switch(which) {
    case 0: return _storage[i].vertex(element).x();
    case 1: return _storage[i].vertex(element).y();
    }
    return _storage[i].source().x();
  }

  std::vector<double> get_row(size_t i, size_t j) const {
    return {
      CGAL::to_double(_storage[i].vertex(j).x().exact()),
      CGAL::to_double(_storage[i].vertex(j).y().exact())
    };
  }

  cpp11::writable::list intersection(const geometry_vector_base& other) const {
    if (other.dimensions() != dimensions()) {
      cpp11::stop("Only geometries of the same dimensionality can intersect");
    }
    switch (other.geometry_type()) {
    case ISORECT: return intersection_impl(get_vector_of_geo<Iso_rectangle>(other), _storage);
    case LINE: return intersection_impl(get_vector_of_geo<Line_2>(other), _storage);
    case POINT: return intersection_impl(get_vector_of_geo<Point_2>(other), _storage);
    case RAY: return intersection_impl(get_vector_of_geo<Ray_2>(other), _storage);
    case SEGMENT: return intersection_impl(_storage, get_vector_of_geo<Segment_2>(other));
    case TRIANGLE: return intersection_impl(_storage, get_vector_of_geo<Triangle_2>(other));
    default: cpp11::stop("Don't know how to calculate the intersection of these geometries");
    }
  }

  cpp11::writable::logicals do_intersect(const geometry_vector_base& other) const {
    if (other.dimensions() != dimensions()) {
      cpp11::stop("Only geometries of the same dimensionality can intersect");
    }
    switch (other.geometry_type()) {
    case ISORECT: return do_intersect_impl(get_vector_of_geo<Iso_rectangle>(other), _storage);
    case LINE: return do_intersect_impl(get_vector_of_geo<Line_2>(other), _storage);
    case POINT: return do_intersect_impl(get_vector_of_geo<Point_2>(other), _storage);
    case RAY: return do_intersect_impl(get_vector_of_geo<Ray_2>(other), _storage);
    case SEGMENT: return do_intersect_impl(_storage, get_vector_of_geo<Segment_2>(other));
    case TRIANGLE: return do_intersect_impl(_storage, get_vector_of_geo<Triangle_2>(other));
    default: return unknown_intersect_impl(std::max(size(), other.size()));
    }
  }

  std::vector<Exact_number> squared_distance(const geometry_vector_base& other) const {
    if (other.dimensions() != dimensions()) {
      cpp11::stop("Only geometries of the same dimensionality can intersect");
    }
    switch (other.geometry_type()) {
    case LINE: return squared_distance_impl(get_vector_of_geo<Line_2>(other), _storage);
    case POINT: return squared_distance_impl(get_vector_of_geo<Point_2>(other), _storage);
    case RAY: return squared_distance_impl(get_vector_of_geo<Ray_2>(other), _storage);
    case SEGMENT: return squared_distance_impl(_storage, get_vector_of_geo<Segment_2>(other));
    case TRIANGLE: return squared_distance_impl(_storage, get_vector_of_geo<Triangle_2>(other));
    default: return unknown_squared_distance_impl(std::max(size(), other.size()));
    }
  }

  cpp11::writable::doubles_matrix distance_matrix(const geometry_vector_base& other) const {
    if (other.dimensions() != dimensions()) {
      cpp11::stop("Only geometries of the same dimensionality can intersect");
    }
    switch (other.geometry_type()) {
    case LINE: return distance_matrix_impl(get_vector_of_geo<Line_2>(other), _storage);
    case POINT: return distance_matrix_impl(get_vector_of_geo<Point_2>(other), _storage);
    case RAY: return distance_matrix_impl(get_vector_of_geo<Ray_2>(other), _storage);
    case SEGMENT: return distance_matrix_impl(_storage, get_vector_of_geo<Segment_2>(other));
    case TRIANGLE: return distance_matrix_impl(_storage, get_vector_of_geo<Triangle_2>(other));
    default: return unknown_distance_matrix_impl(size(), other.size());
    }
  }

  std::vector<Segment_2> operator-() const {
    std::vector<Segment_2> result;
    result.reserve(size());
    for (size_t i = 0; i < size(); ++i) {
      if (!_storage[i]) {
        result.push_back(Segment_2::NA_value());
        continue;
      }
      result.push_back(_storage[i].opposite());
    }
    return result;
  }
};

typedef cpp11::external_pointer<segment2> segment2_p;

class segment3 : public geometry_vector<Segment_3, 3, Segment_2> {
public:
  using geometry_vector::geometry_vector;
  ~segment3() = default;

  Primitive geometry_type() const { return SEGMENT; }

  size_t cardinality(size_t i) const { return 2; }
  size_t long_length() const { return size() * 2; }

  cpp11::writable::strings def_names() const {
    return {"x", "y", "z"};
  }

  Exact_number get_single_definition(size_t i, int which, int element) const {
    switch(which) {
    case 0: return _storage[i].vertex(element).x();
    case 1: return _storage[i].vertex(element).y();
    case 2: return _storage[i].vertex(element).z();
    }
    return _storage[i].source().x();
  }

  std::vector<double> get_row(size_t i, size_t j) const {
    return {
      CGAL::to_double(_storage[i].vertex(j).x().exact()),
      CGAL::to_double(_storage[i].vertex(j).y().exact()),
      CGAL::to_double(_storage[i].vertex(j).z().exact())
    };
  }

  cpp11::writable::list intersection(const geometry_vector_base& other) const {
    if (other.dimensions() != dimensions()) {
      cpp11::stop("Only geometries of the same dimensionality can intersect");
    }
    switch (other.geometry_type()) {
    case ISOCUBE: return intersection_impl(get_vector_of_geo<Iso_cuboid>(other), _storage);
    case LINE: return intersection_impl(get_vector_of_geo<Line_3>(other), _storage);
    case PLANE: return intersection_impl(get_vector_of_geo<Plane>(other), _storage);
    case POINT: return intersection_impl(get_vector_of_geo<Point_3>(other), _storage);
    case RAY: return intersection_impl(get_vector_of_geo<Ray_3>(other), _storage);
    case SEGMENT: return intersection_impl(_storage, get_vector_of_geo<Segment_3>(other));
    case TRIANGLE: return intersection_impl(_storage, get_vector_of_geo<Triangle_3>(other));
    default: cpp11::stop("Don't know how to calculate the intersection of these geometries");
    }
  }

  cpp11::writable::logicals do_intersect(const geometry_vector_base& other) const {
    if (other.dimensions() != dimensions()) {
      cpp11::stop("Only geometries of the same dimensionality can intersect");
    }
    switch (other.geometry_type()) {
    case ISOCUBE: return do_intersect_impl(get_vector_of_geo<Iso_cuboid>(other), _storage);
    case LINE: return do_intersect_impl(_storage, get_vector_of_geo<Line_3>(other));
    case PLANE: return do_intersect_impl(_storage, get_vector_of_geo<Plane>(other));
    case POINT: return do_intersect_impl(_storage, get_vector_of_geo<Point_3>(other));
    case RAY: return do_intersect_impl(_storage, get_vector_of_geo<Ray_3>(other));
    case SEGMENT: return do_intersect_impl(_storage, get_vector_of_geo<Segment_3>(other));
    case SPHERE: return do_intersect_impl(_storage, get_vector_of_geo<Sphere>(other));
    case TETRAHEDRON: return do_intersect_impl(_storage, get_vector_of_geo<Tetrahedron>(other));
    case TRIANGLE: return do_intersect_impl(_storage, get_vector_of_geo<Triangle_3>(other));
    default: return unknown_intersect_impl(std::max(size(), other.size()));
    }
  }

  std::vector<Exact_number> squared_distance(const geometry_vector_base& other) const {
    if (other.dimensions() != dimensions()) {
      cpp11::stop("Only geometries of the same dimensionality can intersect");
    }
    switch (other.geometry_type()) {
    case LINE: return squared_distance_impl(get_vector_of_geo<Line_3>(other), _storage);
    case PLANE: return squared_distance_impl(get_vector_of_geo<Plane>(other), _storage);
    case POINT: return squared_distance_impl(get_vector_of_geo<Point_3>(other), _storage);
    case RAY: return squared_distance_impl(get_vector_of_geo<Ray_3>(other), _storage);
    case SEGMENT: return squared_distance_impl(_storage, get_vector_of_geo<Segment_3>(other));
    default: return unknown_squared_distance_impl(std::max(size(), other.size()));
    }
  }

  cpp11::writable::doubles_matrix distance_matrix(const geometry_vector_base& other) const {
    if (other.dimensions() != dimensions()) {
      cpp11::stop("Only geometries of the same dimensionality can intersect");
    }
    switch (other.geometry_type()) {
    case LINE: return distance_matrix_impl(get_vector_of_geo<Line_3>(other), _storage);
    case PLANE: return distance_matrix_impl(get_vector_of_geo<Plane>(other), _storage);
    case POINT: return distance_matrix_impl(get_vector_of_geo<Point_3>(other), _storage);
    case RAY: return distance_matrix_impl(get_vector_of_geo<Ray_3>(other), _storage);
    case SEGMENT: return distance_matrix_impl(_storage, get_vector_of_geo<Segment_3>(other));
    default: return unknown_distance_matrix_impl(size(), other.size());
    }
  }

  std::vector<Segment_3> operator-() const {
    std::vector<Segment_3> result;
    result.reserve(size());
    for (size_t i = 0; i < size(); ++i) {
      if (!_storage[i]) {
        result.push_back(Segment_3::NA_value());
        continue;
      }
      result.emplace_back(_storage[i].opposite());
    }
    return result;
  }
};

typedef cpp11::external_pointer<segment3> segment3_p;
