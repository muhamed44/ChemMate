#include <cmath>

double ion_concentration1 = 0.0;
double ion_concentration2 = 0.0;
int stoich1 = 1;
int stoich2 = 1;

// Function to calculate Ksp from ion concentrations and stoichiometry
double calculate_ksp(double ion_concentration1, double ion_concentration2, int stoich1, int stoich2) {
    return std::pow(ion_concentration1, stoich1) * std::pow(ion_concentration2, stoich2);
}