export module bubble_sort;

import <vector>;
import <iostream>;
import <algorithm>;

export template <typename t> // list can be of any type, uses a template to avoid type clashes and less code bloat
class bubble_sort {
  public:
    bubble_sort(std::vector<t> list) : m_list(std::move(list)) {} // initialise the list

    void sort() {
      
      for (std::size_t i = 0; i < m_list.size(); ++i) { // loop through the entire list
        bool swapped = false; // checking condition to see if the loop can break early, used to optimise the process
        for (std::size_t j = 0; j < m_list.size() - (i + 1); ++j) { // loop through each item of the list
          if (m_list[j] > m_list[j + 1]) { // if the first is bigger than the second element
            std::swap(m_list[j], m_list[j + 1]); // swap the elements
              swapped = true;
          }
        }
        if (swapped == false) { // early exit to optimise performance
          break;
        }
      }
        
    }

    void report_memory() const {
      
      std::size_t element_size = sizeof(t); // stores the size of the implemented data type
      std::size_t total_size = m_list.capacity() * element_size; // total size is list capacity * element size

      std::cout << "Total memory used: " << total_size << " B\n";
      std::cout << "Empirical memory complexity of O(1) of bubble sort\n";
      
    }

    void print() const {

      std::cout << "[ ";
      for (std::size_t i = 0; i < std::size(m_list); ++i) {
        std::cout << m_list[i];
        if (i < std::size(m_list) - 1) std::cout << ", ";
      }
      std::cout << " ]\n";
      
    }


  private:
    std::vector<t> m_list; // cannot be accessed by client code unless initialiser called
};
