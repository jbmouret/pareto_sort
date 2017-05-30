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

void test_eq()
{
    std::vector<pareto_sort::vec_t<double>> data;
    data.push_back({2.0, {1.0, 1.0}});
    data.push_back({2.0, {1.0, 0.4}});
    data.push_back({2.0, {0.9, 1.0}});
    data.push_back({2.0, {0.5, 1.0}});

    auto res = pareto_sort::sort(data);

    for (auto& i : res[0])
        std::cout << i.second.first << " " << i.second.second << std::endl;
}

void test_gaussian()
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
}

int main()
{
    test_eq();
    test_gaussian();
    return 0;
}