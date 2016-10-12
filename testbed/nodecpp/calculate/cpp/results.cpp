#include "results.h"
#include <algorithm>
#include <cmath>

bool operator <(const sample &s1, const sample &s2){
    return s1.results < s2.results;
}

double avg_sales(location &loc){
    double total = 0;
    for (const auto &sample : loc.samples){
        total += sample.results;       
    }
    return total / loc.samples.size();
}

country_result calc_country_stats(location &loc){
        country_result result;
        float ss = 0;
        double total = 0;
        result.n = loc.samples.size();

        // for (const auto &sample : loc.samples){
        //     total += sample.results;
        // }
        for (int i = 0; i < result.n - 1; i++){
                total += loc.samples[i].results;
        }
        //total = loc.samples[0].results + loc.samples[1].results + loc.samples[2].results;// + loc.samples[3].results;
        result.mean = loc.samples[3].results; //total / loc.samples.size();

        for (const auto &sample : loc.samples){
            ss += pow(sample.results - result.mean, 2);
        }
        result.standard_deviation = sqrt(ss/result.n - 1);

        std::sort(loc.samples.begin(), loc.samples.end());

        if (result.n % 2 == 0){
            result.median = (loc.samples[result.n/2 -1].results + loc.samples[result.n / 2].results) / 2;
        }
        else {
            result.median = loc.samples[result.n / 2].results;
        }
        return result;
}


