#include <unordered_map>
#include <string>
#include <cctype>
#include <stack>
#include <map>
#include <cstddef>

// Define atomic masses of some elements
std::map<std::string, double> atomicMasses = {
    {"H", 1.008}, {"He", 4.0026}, {"Li", 6.94}, {"Be", 9.0122}, {"B", 10.81}, {"C", 12.011}, {"N", 14.007}, {"O", 15.999}, {"F", 18.998}, {"Ne", 20.180}, 
    {"Na", 22.990}, {"Mg", 24.305}, {"Al", 26.982}, {"Si", 28.085}, {"P", 30.974}, {"S", 32.06}, {"Cl", 35.45}, {"Ar", 39.948}, {"K", 39.098}, {"Ca", 40.078}, 
    {"Sc", 44.956}, {"Ti", 47.867}, {"V", 50.942}, {"Cr", 51.996}, {"Mn", 54.938}, {"Fe", 55.845}, {"Co", 58.933}, {"Ni", 58.693}, {"Cu", 63.546}, {"Zn", 65.38}, 
    {"Ga", 69.723}, {"Ge", 72.630}, {"As", 74.922}, {"Se", 78.971}, {"Br", 79.904}, {"Kr", 83.798}, {"Rb", 85.468}, {"Sr", 87.62}, {"Y", 88.906}, {"Zr", 91.224}, 
    {"Nb", 92.906}, {"Mo", 95.95}, {"Tc", 98}, {"Ru", 101.07}, {"Rh", 102.91}, {"Pd", 106.42}, {"Ag", 107.87}, {"Cd", 112.41}, {"In", 114.82}, {"Sn", 118.71}, 
    {"Sb", 121.76}, {"Te", 127.60}, {"I", 126.90}, {"Xe", 131.29}, {"Cs", 132.91}, {"Ba", 137.33}, {"La", 138.91}, {"Ce", 140.12}, {"Pr", 140.91}, {"Nd", 144.24}, 
    {"Pm", 145}, {"Sm", 150.36}, {"Eu", 151.96}, {"Gd", 157.25}, {"Tb", 158.93}, {"Dy", 162.50}, {"Ho", 164.93}, {"Er", 167.26}, {"Tm", 168.93}, {"Yb", 173.05}, 
    {"Lu", 174.97}, {"Hf", 178.49}, {"Ta", 180.95}, {"W", 183.84}, {"Re", 186.21}, {"Os", 190.23}, {"Ir", 192.22}, {"Pt", 195.08}, {"Au", 196.97}, {"Hg", 200.59}, 
    {"Tl", 204.38}, {"Pb", 207.2}, {"Bi", 208.98}, {"Th", 232.04}, {"Pa", 231.04}, {"U", 238.03}, {"Np", 237}, {"Pu", 244}, {"Am", 243}, {"Cm", 247}, 
    {"Bk", 247}, {"Cf", 251}, {"Es", 252}, {"Fm", 257}, {"Md", 258}, {"No", 259}, {"Lr", 266}, {"Rf", 267}, {"Db", 270}, {"Sg", 271}, {"Bh", 270}, 
    {"Hs", 277}, {"Mt", 276}, {"Ds", 281}, {"Rg", 282}, {"Cn", 285}, {"Nh", 284}, {"Fl", 289}, {"Mc", 288}, {"Lv", 293}, {"Ts", 294}, {"Og", 294}
};

// Function to extract an element symbol and its coefficient
std::pair<std::string, int> extractElement(const std::string& formula, std::size_t& i) {
    std::string element;
    int coefficient = 0;
    
    // Extract element symbol
    element += formula[i++];
    if (i < formula.size() && islower(formula[i])) {
        element += formula[i++];
    }
    
    // Extract coefficient
    while (i < formula.size() && isdigit(formula[i])) {
        coefficient = coefficient * 10 + (formula[i++] - '0');
    }
    
    if (coefficient == 0) {
        coefficient = 1;
    }
    
    return {element, coefficient};
}

// Function to calculate molecular mass from a formula
double calculateMolecularMass(const std::string& formula) {
    std::stack<double> massStack;
    std::stack<int> coeffStack;
    std::size_t i = 0;
    int globalCoeff = 1;

    while (i < formula.size()) {
        if (isdigit(formula[i])) {
            int coeff = 0;
            while (i < formula.size() && isdigit(formula[i])) {
                coeff = coeff * 10 + (formula[i++] - '0');
            }
            globalCoeff = coeff;
        } else if (isalpha(formula[i])) {
            auto [element, coeff] = extractElement(formula, i);
            massStack.push(atomicMasses[element] * coeff * globalCoeff);
            globalCoeff = 1;
        } else if (formula[i] == '(') {
            massStack.push(-1); // Marker for parenthesis
            coeffStack.push(globalCoeff);
            globalCoeff = 1;
            i++;
        } else if (formula[i] == ')') {
            i++;
            double subtotal = 0;
            while (massStack.top() != -1) {
                subtotal += massStack.top();
                massStack.pop();
            }
            massStack.pop(); // Pop the -1 marker
            int coeff = 1;
            if (i < formula.size() && isdigit(formula[i])) {
                coeff = 0;
                while (i < formula.size() && isdigit(formula[i])) {
                    coeff = coeff * 10 + (formula[i++] - '0');
                }
            }
            subtotal *= coeff;
            subtotal *= coeffStack.top();
            coeffStack.pop();
            massStack.push(subtotal);
        }
    }

    double totalMass = 0;
    while (!massStack.empty()) {
        totalMass += massStack.top();
        massStack.pop();
    }
    
    return totalMass;
}

