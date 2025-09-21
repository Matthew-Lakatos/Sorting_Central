import algorithms.bubble_sort;
import algorithms.merge_sort;
import algorithms.heap_sort;
import algorithms.lsd_radix_sort;
import algorithms.quick_sort;
import algorithms.bogo_sort;
import algorithms.insertion_sort;
import algorithms.msd_radix_sort;

import features.time_misc;
import features.memory_misc;

import <iostream>;
import <vector>;
import <string>;
import <sstream>;
import <limits>;
import <typeinfo>;

int main() {
  
  std::string input;
  std::cout << "Enter some space separated values for the list you need sorting\n";
  std::cout << "              (end the input stream with value " << R"("/0")" << " )\n";
  std::getline(std::cin, input);
  std::cout << "\n";
  // Try to determine the type based on first token (aka the most painful thing in the world) (i miss python and dynamic type inference)
  std::istringstream iss_probe(input);
  std::string first_token;
  iss_probe >> first_token;

  std::istringstream iss(input); // fresh stream for actual parsing

  // Try to interpret the first token
  int int_val;
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
  std::cout << "Enter the sorting algorithm you would like to implement:\n- bubble sort (a)\n- merge sort (b)\n- insertion sort (c)\n- quick sort (d)\n- heap sort (e)\n- bogo sort (f)\n";
  std::cout << "- LSD radix (g)\n- MSD radix (h)\n- shell (i)\n- my introsort implementation (j)\n- optimal introsort (k)\n";
  std::getline(cin, algorithm);
  algorithm[0] = std::tolower(algorithm[0]);

  auto start = time_misc::take_time();
  if (algorithm == 'a') { // no switch statement as only integral types are supported
    bubble_sort bubbler {list};
    bubbler.sort();
    bubbler.print();
  } else if (algorithm == "b") {
    merge_sort merger {list};
    merger.sort();
    merger.print();
  } else if (algorithm == 'c') {
    insertion_sort inserter {list};
    inserter.sort();
    inserter.print();
  } else if (algorithm == 'd') {
    quick_sort qsorter {list};
    qsorter.sort();
    qsorter.print();
  } else if (algorithm == 'e') {
    heap_sort hsorter {list};
    hsorter.sort();
    hsorter.print();
  } else if (algorithm == 'f') {
    bogo_sort bogosorter {list};
    bogosorter.sort();
    bogosorter.print();
  } else if (algorithm == 'g') {
    // completed later
  }
  auto end = time_misc::take_time(); // seperated to avoid code bloat
  
  auto difference = time_misc::total_time_calc(start, end);

  return 0;
}
