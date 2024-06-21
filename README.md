# ChemMate: Your Command-Line Companion for Chemistry Calculations

ChemMate is a command-line tool designed to assist with various chemistry calculations. It's built with C++ and uses the CLI11 library for command-line parsing.

## Features

- **Molecular Mass Calculation**: Given a chemical formula, ChemMate can calculate the molecular mass and output it in grams per mole (g/mol).

- **Spectral Data Analysis**: ChemMate can analyze spectral data provided as a comma-separated list of peaks. It prints matching IR peaks for each provided peak.

## Usage

To calculate the molecular mass of a molecule, use the `--molmass` option followed by the chemical formula:

```bash
./ChemMate --molmass H2O
```

To analyze spectral data, use the `--spectra` option followed by a comma-separated list of peaks:

```bash
./ChemMate --spectra 2000,3000
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
