# ChemMate: Your Command-Line Companion for Chemistry Calculations

ChemMate is a command-line tool designed to assist with various chemistry calculations. It's built with C++ and uses the CLI11 library for command-line parsing.

## Features

- **Molecular Mass Calculation**: Given a chemical formula, calculate the molecular mass and output it in grams per mole (g/mol).

- **Spectral Data Analysis**: ChemMate can analyze spectral data provided as a comma-separated list of peaks. It prints matching IR peaks for each provided peak.

- **pH Calculation**: Calculate the pH of a solution given the concentration of H+ or OH- ions.

- **Ksp Calculation**: The solubility product constant (Ksp) of a compound can be calculated given the concentrations and stoichiometries of the ions.

- **Reaction Kinetics**: ChemMate can calculate the concentration of a reactant/product at a given time for zero, first, second, and third order reactions.

## Usage

To calculate the molecular mass of a molecule, use the `--molmass` option followed by the chemical formula:

```bash
./ChemMate --molmass H2O
```

To analyze spectral data, use the `--spectra` option followed by a comma-separated list of peaks:

```bash
./ChemMate --spectra 2000,3000
```
To calculate the pH of a solution, use the `phcalc` subcommand followed by the `--h` or `--oh` option and the concentration:

```bash
./ChemMate phcalc --h 0.01
```
To calculate the Ksp of a compound, use the `kspcalc` subcommand followed by the `--ion1, --ion2, --stoich1, --stoich2` options and their respective values:

```bash
./ChemMate kspcalc --ion1 0.01 --ion2 0.02 --stoich1 1 --stoich2 2
```
To calculate the concentration of a reactant/product at a given time, use the `kinetics` subcommand followed by the `-i, -k, -t`, and `--order` options and their respective values:

```bash
./ChemMate kinetics -i 0.01 -k 0.02 -t 10 --order 1
```
## Building

To build ChemMate, you'll need a C++ compiler like `g++`. Navigate to the directory containing [`main.cpp`] and compile the program:

```bash
g++ main.cpp -o ChemMate
```

This will create an executable file named `ChemMate` which you can run as shown in the usage examples above.

## Contributing

Contributions to ChemMate are welcome! pull requests are right there.

## License

ChemMate is licensed under the MIT License. See the `LICENSE` file for more details.
