export module insertion_sort;

import <vector>;
import <algorithm>;
import <iostream>;

export template <typename t>
class insertion_sort {
  public:
    insertion_sort(std::vector<int> list) : m_list(std::move(list)) {}

    void sort() {

        for (std::size_t i = 1; i < m_list.size(); ++i) {
            t key = m_list[i];
            int j = static_cast<int>(i) - 1;

            while (j >= 0 && m_list[j] > key) {
                m_list[j + 1] = m_list[j];
                j--;
            }

            m_list[j + 1] = key;
        }
    }

    void report_memory() const {
      
      std::size_t element_size = sizeof(t); // stores the size of the implemented data type
      std::size_t total_size = m_list.capacity() * element_size; // total size is list capacity * element size

      std::cout << "Total memory used: " << total_size << " B\n";
      
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
    std::vector<t> m_list;

};
