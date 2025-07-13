export module merge_sort;

import <iostream>;
import <vector>;
import <chrono>;
import <algorithm>;

#ifdef _WIN32 // configuration for different kernels (currently only supports linux and windows 32 bit)
import <windows.h>;
import <psapi.h>;
#elif __linux__
import <unistd.h>;
import <sys/resource.h>;
#endif

export template <typename t>
class merge_sort {
  public:
    merge_sort(std::vector<t> list) : m_list(std::move(list)) {} // initialises the list as m_list

    void sort(bool stable = false) {

      auto start = std::chrono::high_resolution_clock::now(); // stores function starting time

      if (stable) {
        std::cout << "This function has a less optimised performance than its unstable counterpart, use its unstable counterpart to achieve this\n";
        stable_sort(0, std::size(m_list) - 1);
      } else {
        std::cout << "This function does not support stability, use its less optimal counterpart to achieve this\n";
        unstable_sort(0, std::size(m_list) - 1));
      }

      auto end = std::chrono::high_resolution_clock::now();
      auto duration = std::chrono::duration<double, std::milli>(end - start); // calculates total time taken for algorithm to complete
      std::cout << "Time taken: " << duration.count() << "ms\n";
      std::cout << "Empirical time complexity of O(n * log2 (n)) (average and worst cases)\n";

    }

    void unstable_sort(std::size_t left, std::size_t right) {

      if (left >= right) { return; }
      std::size_t mid = (left + right) / 2;
      unstable_sort(left, mid);
      unstable_sort(mid+1, right);
      unstable_merge(left, mid, right);
      
    }

    void unstable_merge(std::size_t left, std::size_t mid, std::size_t right) {

      std:size_t total = (right - left) + 1;
      std::vector<t> temp(total);
      std::size_t i = left, j = mid + 1, k = 0;

      while (i <= mid && j <= right) {
        if (m_list[i] < m_list[j]) { // breaks ties (introduces instability) due to optimisation of choosing the right side
          temp[k++] = m_list[i++];
        } else {
          temp[k++] = m_list[j++];
        }
      }

      while (i <= mid) {
        temp[k++] = m_list[i++];
      }
      while (j <= right) {
        temp[k++] = m_list[j++];
      }

      std::copy(temp.begin(), temp.end(), m_list.begin()+left); // copies the temp list onto the pre-existing m_list

    }

    void stable_sort(std::size_t left, std::size_t right) {

      if (left >= right) { return; }
      std::size_t mid = (left + right) / 2;
      stable_sort(left, mid);
      stable_sort(mid+1, right);
      stable_merge(left, mid, right);
      
    }

    void stable_merge(std::size_t left, std::size_t mid, std::size_t right) {

      std::vector<t> left_half(m_list.begin() + left, m_list.begin() + mid + 1);
      std::vector<t> right_half(m_list.begin() + mid + 1, m_list.begin() + right + 1);
      std::size_t i = 0, j = 0, k = left;

      while (i < left_half.size() && j < right_half.size()) {
        if (left_half[i] <= right_half[j]) {
          m_list[k++] = left_half[i++];
        } else {
          m_list[k++] = right_half[j++];
        }
      }
      while (i < left_half.size()) {
        m_list[k++] = left_half[i++];
      }
      while (j < right_half.size()) {
        m_list[k++] = right_half[j++];
      }

    }

    // marked as static due to gathering information from the entire algorithm, not just one aspect
    static void report_memory_process_size()  { // reports peak memory usage by the full algorithm

#ifdef _WIN32
      PROCESS_MEMORY_COUNTERS memInfo;
      GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo));
      std::cout << "Process Working Set Size: " << memInfo.WorkingSetSize / 1024 << "KB\n"; // outputs peak memory used in KB
#elif __linux__
      struct rusage usage;
      getrusage(RUSAGE_SELF, &usage);
      std::cout << "Max resident set size: " << usage.ru_maxrss << "KB\n"; // already stored in KB in linux, no conversion needed
#endif
      
    }

    void print() const {
      
      for (std::size_t i = 0; i < std::size(m_list); ++i) {
        std::cout << m_list[i];
        if (i < std::size(m_list) - 1) std::cout << ", ";
      }
      std::cout << " ]\n";
      
    }

  private:
    std::vector<t> m_list;
};
