#include <iostream>
#include <ostream>

class MetricDistance {
public:
    MetricDistance(double x) : x_(x) {}
    
    friend std::ostream& operator<< (std::ostream& out, const MetricDistance& md);
    MetricDistance operator+ (MetricDistance const& md) { 
         return MetricDistance(x_ + md.x_);
    } 

    double x_;
};

std::ostream& operator<< (std::ostream& out, const MetricDistance& md) {
    out << md.x_ << " meters";
    return out;
}

MetricDistance operator"" _km(long double x) {
    std::cout << "Converting " << x << "km expressed in `long double` to MetricDistance" << std::endl;
    return MetricDistance(x * 1000);
}

MetricDistance operator"" _m(unsigned long long int x) {
    return MetricDistance(x);
}

int main() {
    MetricDistance a = 4.1_km;
//  MetricDistance b = 4_km; // compile-time error, literal `4` matches
    // parameter type `unsigned long long int` instead of `long double`
    MetricDistance b = 4_m;
    std::cout << a + b << std::endl;
}
