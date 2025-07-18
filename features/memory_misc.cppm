export module features.memory_misc;

import <iostream>;
import <string>;
import <unordered_map>;

#ifdef _WIN32 // configures the algorithm for compatibility with windows 32
import <windows.h>;
import <psapi.h>;
#elif __linux__
import <unistd.h>; // configured for linux kernel
import <sys/resource.h>;
#endif

enum SortAlgorithm {
    bubble,
    stable_merge,
    unstable_merge,
    insertion,
    optimal_quick,
    naive_quick,
    heap,
    bogo,
    stalin,
    lsd_radix,
    msd_radix,
    shell,
    user_introsort,
    introsort
};

std::unordered_map <std::string, SortAlgorithm> converter {{"bubble", bubble}, {"stable_merge", stable_merge}, {"unstable_merge", unstable_merge},
{"insertion", insertion}, {"optimal_quick", optimal_quick}, {"naive_quick", naive_quick}, {"heap", heap}, {"bogo", bogo}, {"stalin", stalin}, {"lsd_radix", lsd_radix},
{"msd_radix", msd_radix}, {"shell", shell}, {"user_introsort", user_introsort}, {"introsort", introsort}};

void report_process_memory_size() { // reports peak memory usage by full process (platform dependent)

#ifdef _WIN32
  PROCESS_MEMORY_COUNTERS memInfo; // stores the amount of memory in use
  GetProcessMemoryInfo(GetCurrentProcess(), &memInfo, sizeof(memInfo)); // stores the memory val stored at memInfo
  std::cout << "Process Working Set Size: " << memInfo.WorkingSetSize / 1024 << "KB\n"; // outputs the amount of memory used in KB (/1024 due to orders of magnitude being powers of 2)
#elif __linux__
  struct rusage usage;
  getrusage(RUSAGE_SELF, &usage);
  std::cout << "Max resident set size: " << usage.ru_maxrss << "KB\n";
#else
  std::cout << "Platform not supported by the current implementation\n";
#endif
        
}

void output_memory_complexity(std::string_view sorting_algorithm) {

  SortAlgorithm sort_algorithm = converter[sorting_algorithm];

  switch (sort_algorithm) {
    case bubble:
      std::cout << "Empirical memory complexity of O(1) (in-place)\n";
      break;
    case stable_merge:
      std::cout << "Empirical memory complexity of O(n) (auxillary arrays required)\n";
      break;
    case unstable_merge:
      std::cout << "Empirical memory complexity of O(n) (auxillary arrays required)\n";
      break;
    case insertion:
      std::cout << "Empirical memory complexity of O(1) (in-place)\n";
      break;
    case optimal_quick:
      std::cout << "Empirical memory complexity of O(log2 n) (tail recursion optimised)\n";
      break;
    case naive_quick:
      std::cout << "Empirical memory complexity of O(n) (unbalanced recursion)\n";
      break;
    case heap:
      std::cout << "Empirical memory complexity of O(1) (in-place)\n";
      break;
    case bogo:
      std::cout << "Empirical memory complexity of O(1) (in-place)\n";
      break;
    case stalin:
      std::cout << "Empirical memory complexity of O(1)\n";
      break;
    case lsd_radix:
      std::cout << "Empirical memory complexity of O(n + k) (need count buckets, k is the range of digits)\n";
      break;
    case msd_radix:
      std::cout << "Empirical memory complexity of O(n * k) (need count buckets, k is the range of digits)\n";
      break;
    case shell:
      std::cout << "Empirical memory complexity of O(1) (in-place)\n";
      break;
    case user_introsort:
      std::cout << "Empirical memory complexity of O(log2 n) (ensured by switch to heap if recursive depth is too great)\n";
      break;
    case introsort:
      std::cout << "Empirical memory complexity of O(log2 n) (ensured by switch to heap if recursive depth is too great)\n";
      break;
  }

}
