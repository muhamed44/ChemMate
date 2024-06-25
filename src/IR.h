#include <map>
#include <string>
#include <vector>

// Define the IRPeakMap type
using IRPeakMap = std::map<std::string, std::pair<double, double>>;

IRPeakMap initialize_ir_peak_data() {
    IRPeakMap ir_data;

    // Populate the map with common IR peaks and their typical wavenumber ranges (cm^-1)
    // IR data is hardcoded, better to be imported from a data file and to increase IR peaks data to cover more cases
    ir_data["O-H stretch (alcohol)"] = {3200, 3650};
    ir_data["N-H stretch (amine)"] = {3200, 3500};
    ir_data["C=O stretch (aldehyde)"] = {1700, 1750};
    ir_data["C=O stretch (ketone)"] = {1680, 1750};
    ir_data["C=O stretch (carboxylic acid)"] = {1680, 1725};
    ir_data["C=C stretch (alkene)"] = {1600, 1680};
    ir_data["C=C stretch (aromatic)"] = {1450, 1600};
    ir_data["C-H stretch (alkane)"] = {2850, 3000};
    ir_data["O-H bend (alcohol)"] = {1350, 1450};
    ir_data["N-H bend (amine)"] = {1600, 1650};
    ir_data["C-H bend (alkane)"] = {1350, 1470};
    ir_data["C-H bend (aromatic)"] = {680, 900};

    return ir_data;
}

// Function to match user input peaks with known IR peaks
std::vector<std::string> match_user_peaks(const IRPeakMap& ir_data, const std::vector<double>& user_peaks) {
    std::vector<std::string> matched_groups;

    for (double user_peak : user_peaks) {
        for (const auto& pair : ir_data) {
            double min_range = pair.second.first;
            double max_range = pair.second.second;

            if (user_peak >= min_range && user_peak <= max_range) {
                matched_groups.push_back(pair.first);
            }
        }
    }

    return matched_groups;
}
