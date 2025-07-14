export module memory_misc;

import <iostream>;

#ifdef _WIN32 // configures the algorithm for compatibility with windows 32
import <windows.h>;
import <psapi.h>;
#elif __linux__
import <unistd.h>; // configured for linux kernel
import <sys/resource.h>;
#endif

static void report_process_memory_size() { // reports peak memory usage by full process (platform dependent)

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
        
};
