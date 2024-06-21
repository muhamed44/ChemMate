#include <cmath>

double h_concentration = 0.0;
double oh_concentration = 0.0;

double calculate_ph_from_h(double h_concentration) {
    return -std::log10(h_concentration);
}

double calculate_ph_from_oh(double oh_concentration) {
    double kw = 1e-14; // Ion product of water at 25°C
    double h_concentration = kw / oh_concentration;
    return -std::log10(h_concentration);
}