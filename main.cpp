import bubble_sort;
import merge_sort;

import time_misc;
import memory_misc;

import <iostream>;
import <vector>;
import <string>;
import <sstream>;
import <limits>;
import <typeinfo>;

int main() {
  
  std::string input;
  std::cout << "Enter some space separated values for the list you need sorting\n";
  std::cout << "              (end the input stream with value " << R"("end")" << " )\n";
  std::getline(std::cin, input);
  std::cout << "\n";
  // Try to determine the type based on first token (aka the most painful thing in the world) (i miss python and dynamic type inference)
  std::istringstream iss_probe(input);
  std::string first_token;
  iss_probe >> first_token;

  std::istringstream iss(input); // fresh stream for actual parsing

  // Try to interpret the first token
  int int_val
  long long_val;
  double double_val;
  long double ld_val;

  std::istringstream test_stream(first_token);
  if (test_stream >> int_val && test_stream.eof()) {
      std::vector<int> list;
      int val;
      while (iss >> val) {
          list.push_back(val);
      }
  } else if ((test_stream = std::istringstream(first_token)) && test_stream >> long_val && test_stream.eof()) {
      std::vector<long> list;
      long val;
      while (iss >> val) {
          list.push_back(val);
      }
  } else if ((test_stream = std::istringstream(first_token)) && test_stream >> double_val && test_stream.eof()) {
      std::vector<double> list;
      double val;
      while (iss >> val) {
          list.push_back(val);
      }
  } else if ((test_stream = std::istringstream(first_token)) && test_stream >> ld_val && test_stream.eof()) {
      std::vector<long double> list;
      long double val;
      while (iss >> val) {
          list.push_back(val);
      }
  } else {
      std::vector<std::string> list;
      std::string word;
      while (iss >> word) {
            list.push_back(word);
      }
  }

  // list is finally initialised, now the actual sorting can occur, but fr, c++ needs some function to identify input types more easily

  std::string algorithm;
  std::cout << "Enter the sorting algorithm you would like to implement:\n- bubble sort (a)\n- merge sort (b)\n- insertion sort (WIP) (c)\n- quick sort (WIP) (d)\n- heap sort (WIP) (e)\n- bogo sort (WIP) (f)\n";
  std::cout << "- stalin (g)\n- lsd radix (currently only built for integer values) (h)\n- msd radix (currently only built for integer values) (i)\n- shell (j)\n- my introsort implementation (k)\n- optimal introsort (l)\n";
  std::getline(cin, algorithm);
  algorithm[0] = std::tolower(algorithm[0]);

  auto start = time_misc::take_time()
  switch (algorithm) {
    case "a":
      bubble_sort bubbler {list};
      bubbler.sort();
      auto end = time_misc::take_time()
      bubbler.print();
      break;
    case "b":
      merge_sort merger {list};
      
  }
  
  auto difference = time_misc::total_time_calc(start, end);

  return 0;
}
