#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <numeric>
#include <stdexcept>
#include <string>
#include <vector>
#include <functional>

struct StatResult
{
    std::string description;
    double value;

    StatResult(const std::string& desc, double val)
        : description(desc)
        , value(val)
    {
    }
};

using Data = std::vector<double>;
using Results = std::vector<StatResult>;

enum StatisticsType
{
    avg,
    min_max,
    sum
};

using Statistics = std::function<void (const Data& data, Results& results)>;

class DataAnalyzer
{
    Statistics statistics_;
    Data data_;
    Results results_;

public:
    DataAnalyzer(Statistics statistics)
        : statistics_{statistics}
    {
    }

    void load_data(const std::string& file_name)
    {
        data_.clear();
        results_.clear();

        std::ifstream fin(file_name.c_str());
        if (!fin)
            throw std::runtime_error("File not opened");

        double d;
        while (fin >> d)
        {
            data_.push_back(d);
        }

        std::cout << "File " << file_name << " has been loaded...\n";
    }

    void set_statistics(Statistics statistics)
    {
        statistics_ = statistics;
    }

    void calculate()
    {
        statistics_(data_, results_);
    }

    const Results& results() const
    {
        return results_;
    }
};

void show_results(const Results& results)
{
    for (const auto& rslt : results)
        std::cout << rslt.description << " = " << rslt.value << std::endl;
}

struct Avg
{
    void operator()(const Data& data, Results& results)
    {
            double sum = std::accumulate(data.begin(), data.end(), 0.0);
            double avg = sum / data.size();

            StatResult result("Avg", avg);
            results.push_back(result);
    }
};

struct Sum
{
    void operator()(const Data& data, Results& results)
    {
            double sum = std::accumulate(data.begin(), data.end(), 0.0);

             results.push_back(StatResult("Sum", sum));
    }
};

// Composite Statistics
class StatGroup
{
    std::vector<Statistics> stats_;
public:
    using iterator = std::vector<Statistics>::iterator;
    using const_iterator = std::vector<Statistics>::const_iterator;

    StatGroup() = default;

    StatGroup(std::vector<Statistics> stats) : stats_{stats}
    {}

    void add_statistics(Statistics statistics)
    {
        stats_.push_back(statistics);
    }

    void operator()(const Data& data, Results& results)
    {
        for(auto& stat : stats_)
            stat(data, results);
    }
};

int main()
{
    Avg avg;
    Sum sum;
    
    auto min_max = [](const Data& data, Results& results) {
            double min = *(std::min_element(data.begin(), data.end()));
            double max = *(std::max_element(data.begin(), data.end()));

            results.push_back(StatResult("Min", min));
            results.push_back(StatResult("Max", max));
    };
    
    StatGroup std_stats({avg, min_max, sum});

    DataAnalyzer da{std_stats};
    da.load_data("data.dat");
    da.calculate();    

    show_results(da.results());

    std::cout << "\n\n";

    da.load_data("new_data.dat");
    da.calculate();

    show_results(da.results());
}
