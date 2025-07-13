export module bubble_sort;

import <vector>;
import <iostream>;
import <chrono>; // used for time output capability
import <numeric>;
import <algorithm>;

#ifdef _WIN32 // configures the algorithm for compatibility with windows 32
import <windows.h>;
import <psapi.h>;
#elif __linux__
import <unistd.h>; // configured for linux kernel
import <sys/resource.h>;
#endif

export template <typename t> // list can be of any type, uses a template to avoid type clashes and less code bloat
class bubble_sort {
  public:
    bubble_sort(std::vector<t> list) : m_list(std::move(list)) {} // initialise the list

    void sort() {
      
      auto start = std::chrono::high_resolution_clock::now(); // notes the time the algorithm has begun at
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

      auto end = std::chrono::high_resolution_clock::now(); // notes when the algorithm has finished
      auto duration = std::chrono::duration<double, std::milli>(end - start); // calculates the time taken

      std::cout << "Time taken: " << duration.count() << "ms\n";
      std::cout << "Amortised empirical time complexity of O(n^2), best case O(1)";
        
    }

    void report_memory() const {
      
      std::size_t element_size = sizeof(t); // stores the size of the implemented data type
      std::size_t total_size = m_list.capacity() * element_size; // total size is list capacity * element size

      std::cout << "memory used: " << total_size << "bytes\n";
      std::cout << "Amortised empirical memory complexity of O(1) (due to size of the list sorted)\n";
      
    }

    // marked as static due to gathering information from the entire class, not just a specific instance
    static void report_process_memory_size() { // reports peak memory usage by full process (platform dependent)

#ifdef _WIN32
      PROCESS_MEMORY_COUNTERS memInfo; // stores the amount of memory in use
      GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo)); // calculates the memory used at a location in memory
      std::cout << "Process Working Set Size: " << memInfo.WorkingSetSize / 1024 << "KB\n"; // outputs the amount of memory used in KB (/1024 due to orders of magnitude being powers of 2)
#elif __linux__
      struct rusage usage;
      getrusage(RUSAGE_SELF, &usage);
      std::cout << "Max resident set size: " << usage.ru_maxrss << "KB\n";
#endif
        
    }

    void print() const {

      for (const auto& val : m_list) {
        std::cout << val << "\n";
      }
      std::cout << "\n";
      
    }


  private:
    std::vector<t> m_list; // cannot be accessed by client code unless initialiser called
};
