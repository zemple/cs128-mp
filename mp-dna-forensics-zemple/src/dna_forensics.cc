#include <iostream>
#include <fstream>
#include <string>

#include "functions.hpp"
#include "utilities.hpp"

using namespace std;

int main(int argc, char* argv[]) {
  if (argc != 3) { 
    std::cerr << "Usage: " << argv[0] << " [input_file] [dna_sequence]"
              << std::endl;
    return 1; 
  }

  Print(argv[1], argv[2]);
  
  return 0;
}