#include <fstream>
#include <random>

#include "pareto_sort.hpp"

std::random_device rd;
std::mt19937 mt(rd());
std::normal_distribution<double> dist(0.0, 10.0);

pareto_sort::vec_t<double> random_indiv()
{
    auto v = std::make_pair(dist(mt), dist(mt));
    return std::make_pair(0, v);
}

int main()
{
    std::vector<pareto_sort::vec_t<double>> data;
    for (size_t i = 0; i < 1000; ++i)
        data.push_back(random_indiv());
    

    std::ofstream ofs("data.dat"), ofs2("pareto_data.dat");
    for (auto& i : data)
        ofs << i.second.first << " " << i.second.second << std::endl;

    auto res = pareto_sort::sort(data);

    for (auto& i : res[0])
        ofs2 << i.second.first << " " << i.second.second << std::endl;

    return 0;
}