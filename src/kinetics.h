#include <cmath>
double i, k, t;
int order = 1;

// Kinetics functions for different reaction orders
double zero_order_concentration(double i, double k, double t) {
    return i - k * t;
}

double first_order_concentration(double i, double k, double t) {
    return i * std::exp(-k * t);
}

double second_order_concentration(double i, double k, double t) {
    return 1.0 / ((1.0 / i) + k * t);
}

double third_order_concentration(double i, double k, double t) {
    return std::pow((1.0 / std::pow(i, 2)) + 2 * k * t, -0.5);
}