#include "../include/CLI11.hpp"
#include "molmass.h"
#include "kspcalc.h"
#include "phcalc.h"
#include "kinetics.h"
#include "IR.h"
#include <iostream>


std::vector<double> parseData(const std::string& data) {
    std::stringstream ss(data);
    std::string peak;
    std::vector<double> peaks;
    while (std::getline(ss, peak, ',')) {
        peaks.push_back(std::stod(peak));
    }
    return peaks;
}

int main(int argc, char **argv) {
    CLI::App app{
        "----------------------------------------------------------------\n"
        "ChemMate, Your Command-Line Companion for Chemistry Calculations\n"
        "----------------------------------------------------------------\n"
        };

    std::string formula;
    app.add_option("--molmass", formula, "Calculate molecular mass")
       ->each([&](std::string formula){ 
        double mass = calculateMolecularMass(formula);
        std::cout << "The molecular mass of " << formula << " is " << mass << " g/mol" << std::endl;
        throw CLI::Success();
       });

    std::string data;
    bool first = true;
    app.add_option_function<std::string>("--spectra", [&](const std::string& value) {
    std::istringstream iss(value);
    std::string number;
    while (std::getline(iss, number, ',')) {
        if (!first) {
            std::cout << "-----------------------\n";  // print a line of dashes before each peak, except the first one
        }
        first = false;
        std::vector<double> peaks = parseData(number);
        std::vector<std::string> matched_groups = match_user_peaks(initialize_ir_peak_data(), peaks);
        if (matched_groups.empty()) {
            std::cout << "No matching IR peaks found" << std::endl;
        } else {
            std::cout << "Matched IR peaks:" << number << std::endl;
            for (const std::string& group : matched_groups) {
                std::cout << "  - " << group << std::endl;
            }
        }
    }
    throw CLI::Success();
}, "IR peak data in the format 'peak1,peak2,peak3'");

    auto phcalc = app.add_subcommand("phcalc", "Calculate pH '--h_ion <value>' or '--oh_ion <value>'");
    phcalc->add_option("--h_ion", h_concentration, "Concentration of H+ ions in mol/L");
    phcalc->add_option("--oh_ion", oh_concentration, "Concentration of OH- ions in mol/L");
    phcalc->callback([&](){ 
        if (h_concentration != 0.0) {
            double ph = calculate_ph_from_h(h_concentration);
            std::cout << "The pH of the solution is " << ph << std::endl;
        } else if (oh_concentration != 0.0) {
            double ph = calculate_ph_from_oh(oh_concentration);
            std::cout << "The pH of the solution is " << ph << std::endl;
        }
        throw CLI::Success();
    });
    
    auto kspcalc = app.add_subcommand("kspcalc", "Calculate Ksp '--ion1 <value>' '--ion2 <value>' '--stoich1 <value>' '--stoich2 <value>'");
    kspcalc->add_option("--ion1", ion_concentration1, "Concentration of the first ion in mol/L")->required();
    kspcalc->add_option("--ion2", ion_concentration2, "Concentration of the second ion in mol/L")->required();
    kspcalc->add_option("--stoich1", stoich1, "Stoichiometry of the first ion (default: 1)")->default_val(1);
    kspcalc->add_option("--stoich2", stoich2, "Stoichiometry of the second ion (default: 1)")->default_val(1);
    kspcalc->callback([&](){ 
        double ksp = calculate_ksp(ion_concentration1, ion_concentration2, stoich1, stoich2);
        std::cout << "The Ksp of the compound is " << ksp << std::endl;
        throw CLI::Success();
    });

    auto kinetics = app.add_subcommand("kinetics", "Calculate reaction kinetics '-i <value>' '-k <value>' '-t <value>' '--order <value>'");
    kinetics->add_option("-i", i, "Initial concentration (mol/L)")->required();
    kinetics->add_option("-k", k, "Rate constant <unit dependent>")->required();
    kinetics->add_option("-t", t, "Time (s)")->required();
    kinetics->add_option("--order", order, "Reaction order (0, 1, 2, 3)")->required();
    kinetics->callback([&](){ 
        double concentration = 0.0;
        switch (order) {
            case 0:
                concentration = zero_order_concentration(i, k, t);
                break;
            case 1:
                concentration = first_order_concentration(i, k, t);
                break;
            case 2:
                concentration = second_order_concentration(i, k, t);
                break;
            case 3:
                concentration = third_order_concentration(i, k, t);
                break;
            default:
                std::cerr << "Invalid reaction order" << std::endl;
                break;
        }
        std::cout << "The concentration of the reactant is " << concentration << " mol/L" << std::endl;
        throw CLI::Success();
    });



    CLI11_PARSE(app, argc, argv);
  if (argc == 1) {
        std::cout << app.help() << std::endl;
    }
    return 0;
}