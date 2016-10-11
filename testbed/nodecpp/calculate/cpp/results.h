#include <vector>
#include <string>
using namespace std;

class sample {
    public:
    sample(){
        month = ""; results = 0;
    }
    sample(string m, double r){
        month = m;
        results = r;
    }
    string month;
    double results;
};

//for median calculation (sorting)
bool operator <(const sample &s1, const sample &s2);

class location {
    public:
     string country;
     vector<sample> samples;
};

class country_result {
    public:
    float median;
    float mean;
    float standard_deviation;
    int n;
};


double avg_sales(location &loc);

country_result calc_country_stats(location &loc);