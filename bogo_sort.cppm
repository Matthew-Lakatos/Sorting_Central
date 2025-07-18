export module bogo_sort;

import <iostream>;
import <vector>;
import <algorithm>;
import <chrono>;
import <random>; // for the random element

export template <typename t>
class bogo_sort {
  public:
    bogo_sort(std::vector<t> list) : m_list(std::move(list)) {}

    void sort(double maximum, double start) {

      std::random_device rd; // for random seed generation
      std::mt19937 gen(rd()); // upcast for true random seed generation

      while (! std::is_sorted(first, last) && current_time_taken < maximum) {

        std::shuffle(first, last, gen); / completely inefficient
        current_time_taken = std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now() - start);

      }

      if (current_time_taken > maximum) {

        std::cout << "Took over " << maximum << " ms, list has not been sorted";
      
      }

    }

    void report_memory() const {
      
      std::size_t element_size = sizeof(t); // stores the size of the implemented data type
      std::size_t total_size = m_list.capacity() * element_size + 2500; // total size is list capacity * element size + ~ std::mt19937 internal state

      std::cout << "Estimated total memory used: " << total_size << " B\n";
      
    }

    void print() const {

      std::cout << "[ ";
      for (std::size_t i = 0; i < std::size(m_list); ++i) {
        std::cout << m_list[i];
        if (i < std::size(m_list) - 1) std::cout << ", ";
      }
      std::cout << " ]\n";
      
    }

};
