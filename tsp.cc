#include "cities.hh"
#include <iostream>
#include <fstream>
#include <limits>

int main(int argc, char** argv)
{
    // check that we have a .tsv file to use
    if (argc != 2)
    {
        std::cerr << "need a single .tsv file as an argument" << "\n";
    }

    //open file stream and read city coordinates into object
    auto fin = std::ifstream(argv[1]);
    Cities cities;
    fin >> cities;

    // start the best distance off as a really big number
    double best_distance = std::numeric_limits<double>::max();
    double current_distance;
    // first permutation
    Cities::permutation_t perm = cities.random_permutation(cities.num_cities());

    // do 1 million and 1 different permutations and check to see 
    // which one gives best distance
    for (int i = 0; i != 1000000; i++)
    {
        current_distance = cities.total_path_distance(perm);
        if (current_distance < best_distance)
        {
            best_distance = current_distance;
            cities = cities.reorder(perm);
            std::cout << i << "    " << best_distance << "\n";
        }
        perm = cities.random_permutation(perm.size());
    }

    // output best order of cities
    auto fout = std::ofstream("shortest.tsv");
    fout << cities;

    return 0;
}