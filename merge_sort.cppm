export module merge_sort;

import <iostream>;
import <vector>;
import <numeric>;
import <chrono>;
import <algorithm>;

#ifdef _WIN32 // configuration for different kernels (currently only supports linux and windows 32 bit)
import <windows.h>;
import <psapi.h>;
#elif __linux__
import <unistd.h>;
import <sys/resource.h>;
#endif

export template <typename t>;
class merge_sort {
  public:
    merge_sort(std::vector<t> list) : m_list(std::move(list)) {} // initialises the list as m_list

    void sort() {

      auto start = std::chrono::high_resolution_clock::now(); // stores function starting time
      
      // insert functional (and hopefully optimised) merge sort algorithm here

      auto end = std::chrono::high_resolution_clock::now();
      auto duration = std::chrono::duration<double, std::milli>(end - start); // calculates total time taken for algorithm to complete
      std::cout << "Time taken: " << duration.count() << "ms\n";
      std::cout << "Amortised empirical time complexity of O(n * log2 (n))\n";
      
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
      
      std::cout << "[ ";
      for (std::size_t i = 0; i < std::size(m_list) - 2; ++i) {
        std::cout << m_list[i] << ", ";
      }
      std::cout << m_list[-1] << " ]\n";
      
    }

  private:
    std::vector<t> m_list;
};
