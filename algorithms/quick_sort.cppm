export module algorithms.quick_sort;

import <iostream>;
import <vector>;
import <algorithm>;
import <cmath>;

export template <typename t>
class quick_sort {
  public:
    quick_sort(std::vector<t> list) : m_list(std::move(list)) {}

    void sort() {
      quicksort(0, m_list.size() - 1);
    }

    void quicksort(std::size_t left, std::size_t right) {
      if (left < right) {
        std::size_t pi = partition(left, right); // recursive function call
        if (pi > 0) {
          quicksort(left, pi - 1); // avoiding underflow
        }
        quicksort(pi+1, right);
      }
    }

    std::size_t partition(std::size_t left, std::size_t right) {
      t pivot = m_list[right];
      std::size_t i = left;

      for (std::size_t j = left; j < right; ++j) {
        if (m_list[j] < pivot) {
          std::swap(m_list[j], m_list[i]); // using swap() for performance optimisation
          ++i;
        }
      }

      std::swap(m_list[i], m_list[right]);
      return i;
    }

    void print() {

      std::cout << "[ ";
      for (std::size_t i = 0; i < std::size(m_list); ++i) {
        std::cout << m_list[i];
        if (i < std::size(m_list) - 1) std::cout << ", ";
      }
      std::cout << " ]\n";
      
    }

    void report_memory() const {

      std::size_t list_size = m_list.capacity() * std::sizeof(t);
      std::size_t recursive_memory_usage = std::log2(m_list.size()) * 3 * sizeof(t);
      std::size_t total_memory = list_size + recursive_memory_usage;

      std::cout << "Total (estimated) memory used by the function: " << total_memory << " B\n"; // due to recursion depth varying
      
    }

  private:
    std::vector<t> m_list;
};
