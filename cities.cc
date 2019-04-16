#include "cities.hh"
#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <random>
#include <cassert>

// constructor for cities object - idk why I didn't just define
// it in the header ¯\_(ツ)_/¯
Cities::Cities(std::vector<coord_t> cities)
    : cities_(cities) {}

// reads in city coordinates from file and places them
// into the vector of cities in the cities object
std::istream& 
operator>>(std::istream& is, Cities& cities)
{
    Cities::coord_t tup;
    while (is >> tup.first >> tup.second) 
    {
        cities.cities_.push_back(tup);
    }
    return is;
}

// for outputing cordinates of cities to file
// we use this once we have determined the best order we 
// can to traverse the cities, and we output the cities to
// a file in that order
std::ostream& 
operator<<(std::ostream& os, Cities& cities)
{
    for (auto v : cities.cities_)
    {
        os << v.first << "  " << v.second << "\n";
    }
    return os;
}

// returns new cities object, with the order of the cities in the 
// vector of coordinates as defined by the permutation
Cities 
Cities::reorder(const Cities::permutation_t& ordering) const
{
    assert(ordering.size() == cities_.size());
    std::vector<Cities::coord_t> new_cities;

    // iterate through permutation, adding cities to new vector
    // in order defined by permutation
    for (auto v : ordering)
    {
        new_cities.push_back(cities_[v]);
    }
    return Cities(new_cities);
}

// calculates the total distance for traveling all the cities (and
// back to the first) in the order defined by the permutation 
// arguement
double 
Cities::total_path_distance(const permutation_t& ordering) const
{
    assert(ordering.size() == cities_.size()); 
    double total_dist = 0; 
    int prev = cities_.size()-1;
    int x, y; // these will store the x-axis and y-axis distances, respectively

    // iterate through the vector of cities, adding up the distances 
    //between successive cities
    for (unsigned long i = 0; i != cities_.size(); i++)
    {
        x = cities_[ordering[i]].first - cities_[ordering[prev]].first;
        y = cities_[ordering[i]].second - cities_[ordering[prev]].second;
        total_dist += std::hypot(x, y); 
        prev = i;
    }
    return total_dist;
}


// generates a new permuatation of numbers from 0 to len-1
// I implemented this as a method in order to store the current state of 
// the random engine, so we get new permutations each time
Cities::permutation_t 
Cities::random_permutation(unsigned len)
{
    Cities::permutation_t ordering;

    // load the desired numbers into the vector
    for (unsigned i = 0; i != len; i++)
    {
        ordering.push_back(i);
    }

    //permute the elements in the vector, using the objects random engine
    std::shuffle(ordering.begin(), ordering.end(), engine_);
    return ordering;
}




