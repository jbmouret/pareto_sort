#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <vector>

namespace pareto_sort {
    // <data, <objective 1, objective 2> >
    template <class T>
    using vec_t = std::pair<T, std::pair<double, double>>;

    // lexical order
    template <typename T>
    inline bool compare_objs_lex(const vec_t<T>& i1, const vec_t<T>& i2)
    {
        if (i1.second.first > i2.second.first)
            return true;
        else if (i1.second.first == i2.second.first && i1.second.second > i2.second.second)
            return true;
        return false;
    }

    template <typename T>
    inline std::vector<T> new_vector(const T& t)
    {
        std::vector<T> v;
        v.push_back(t);
        return v;
    }

    template <typename T>
    inline bool comp_fronts(const std::vector<vec_t<T>>& f2, const std::vector<vec_t<T>>& f1)
    {
        // we only need to compare f1 to the value of the last element of f2
        if (f1[0].second.second <= f2.back().second.second)
            return true;
        else
            return false;
    }

    // see M. T. Jensen, 2003
    // takes a population and returns a vector of fronts
    // - this works only for 2 objectives
    // - we maximize the objectives
    template <typename T>
    inline std::vector<std::vector<vec_t<T>>> sort(const std::vector<vec_t<T>>& pop)
    {
        // result is a vector of vectors (first is the Pareto front)
        using f_t = std::vector<std::vector<vec_t<T>>>;
        f_t f;
        // make a copy to sort the population
        std::vector<vec_t<T>> p = pop;
        std::sort(p.begin(), p.end(), compare_objs_lex<T>);
        f.push_back(new_vector(p[0]));
        size_t e = 0;
        for (size_t i = 1; i < p.size(); ++i) {
            if (p[i].second.second > f[e].back().second.second) { // !dominate(si, f_e)
                auto b = std::lower_bound(f.begin(), f.end(), new_vector(p[i]), comp_fronts<T>);
                assert(b != f.end());
                b->push_back(p[i]);
            }
            else {
                ++e;
                f.push_back(new_vector(p[i]));
            }
        }
        return f;
    }
} // namespace pareto_sort