export module algorithms.heap_sort;

import <vector>;
import <algorithm>;
import <iostream>;

export template <typename t>
class heap_sort {
public:
    heap_sort(std::vector<t> list) : m_list(std::move(list)) {}

    void sort() {
        heapify();
        for (std::size_t i = m_list.size() - 1; i > 0; --i) {
            std::swap(m_list[0], m_list[i]);
            sift_down(0, i);
        }
    }

    void print() {

      std::cout << "[ ";
      for (std::size_t i = 0; i < std::size(m_list); ++i) {
        std::cout << m_list[i];
        if (i < std::size(m_list) - 1) std::cout << ", ";
      }
      std::cout << " ]\n";
      
    }

    void heapify() {
        std::size_t n = m_list.size();
        for (std::size_t i = n / 2; i-- > 0; --i;) {
            sift_down(i, n);
        }
    }

    void sift_down(std::size_t node, std::size_t heap_size) {
        std::size_t largest = node;
        std::size_t left = 2 * node + 1;
        std::size_t right = 2 * node + 2;

        if (left < heap_size && m_list[left] > m_list[largest]) {
            largest = left;
        }
        if (right < heap_size && m_list[right] > m_list[largest]) {
            largest = right;
        }
        if (largest != node) {
            std::swap(m_list[node], m_list[largest]);
            sift_down(largest, heap_size);
        }
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
