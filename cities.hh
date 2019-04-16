/*
 * API file for Travelling-Salesperson Cities class and utilities
 */

#pragma once

#include <vector>
#include <iostream>
#include <random>


// Representation of an ordering of cities
class Cities {
 public:
  // A pair of integral coordinates for each city
  using coord_t = std::pair<int, int>;

  // An ordering of the cities in cities_t. Each value represents a unique index
  // into the current city ordering.
  using permutation_t = std::vector<unsigned int>;

  Cities(std::vector<coord_t> cities = std::vector<coord_t>());
  ~Cities() = default;

  // Given a permutation, return a new Cities object where the order of the
  // cities reflects the original order of this class after reordering with
  // the given ordering. So for example, the ordering { 1, 0 } simply swaps
  // the first two elements (coordinates) in the new Cities object.
  Cities reorder(const permutation_t& ordering) const;

  // For a given permutation of the cities in this object,
  // compute how long (distance) it would take to traverse all the cities in the
  // order of the permutation, and then returning to the first city.
  // The distance between any two cities is computed as the Euclidean 
  // distance on a plane between their coordinates.
  double total_path_distance(const permutation_t& ordering) const;

  // declare the IO functions declared below to be friends.
  // so we can load the cities listed in the .tsv files
  // into the object and read from the object when we have determined 
  // our shortest distance
  friend std::istream& operator>>(std::istream& is, Cities& cities);
  friend std::ostream& operator<<(std::ostream& os, Cities& cities);

  // accessor method for the number of cities, used in main()
  int num_cities() const { return cities_.size(); }

  // generates new permutation of numbers 0 through n-1
  Cities::permutation_t random_permutation(unsigned len);

private:
  std::vector<coord_t> cities_; // stores the coordinates of the cities

  // we store the random engine here because so it saves the state when
  // the order of the cities is not changed. That way, we get a new permutation
  // each time
  std::default_random_engine engine_; 
};

// input and output functions for writing to or
// reading from files to/from Cities object
std::istream& operator>>(std::istream& is, Cities& cities);
std::ostream& operator<<(std::ostream& os, Cities& cities);






