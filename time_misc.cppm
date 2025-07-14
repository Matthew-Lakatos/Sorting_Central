import <chrono>;
import <iostream>;
import <string>;
import <unordered_map>;

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
    shell
};

std::unordered_map <std::string, SortAlgorithm> converter {{"bubble", bubble}, {"stable_merge", stable_merge}, {"unstable_merge", unstable_merge},
{"insertion", insertion}, {"optimal_quick", optimal_quick}, {"naive_quick", naive_quick}, {"heap", heap}, {"bogo", bogo}, {"stalin", stalin}, {"lsd_radix", lsd_radix}, {"msd_radix", msd_radix}, {"shell", shell}};

double take_time() {

  double time = std::chrono::high_resolution_clock::now(); // notes the time the algorithm has begun at
  return time;

}

double total_time_calc(auto start, auto end) {

  auto duration = std::chrono::duration<double, std::milli>(end - start); // calculates the time taken
  return duration.count();

}

void output_time(double duration) {

  std::cout << "Time taken for the algorithm to execute: " << duration << " ms\n";

}

void output_time_complexity(std::string sorting_algorithm) {

  SortAlgorithm sort_algorithm = converter[sorting_algorithm];

  switch (sort_algorithm) {
    case bubble:
      std::cout << "Empirical time complexity of O(n^2), best case O(1)\n";
      break;
    case stable_merge:
      std::cout << "Empirical time complexity of O(n * log2 n)\n";
      break;
    case unstable_merge:
      std::cout << "Empirical time complexity of O(n * log2 n)\n";
      break;
    case insertion:
      std::cout << "Empirical time complexity of O(n^2)\n";
      break;
    case optimal_quick:
      std::cout << "Empirical time complexity of O(n * log2 n)\n";
      break;
    case naive_quick:
      std::cout << "Empirical time complexity of O(n * log2 n), worst case O(n^2) (poor pivot selection)\n";
      break;
    case heap:
      std::cout << "Empirical time complexity of O(n * log2 n)\n";
      break;
    case bogo:
      std::cout << "Empirical time complexity of O(n * n!), worst case O(unbounded), best case O(n)\n";
      break;
    case stalin:
      std::cout << "Empirical time complexity of O(n)\n";
      break;
    case lsd_radix:
      std::cout << "Empirical time complexity of O(n * k) (NOT suitable for any decimal value (produces a massive k, which in practice is slower than bogo sort), std::string s (anomalous outcomes for strings of varying size) or bools (overkill))\n";
      break;
    case msd_radix:
      std::cout << "Empirical time complexity of O(n * k) (NOT suitable for any decimal value (produces a massive k, which in practice is slower than bogo sort), std::string s (anomalous outcomes for strings of varying size) or bools (overkill))\n";
      break;
    case shell:
      std::cout << "Empirical time complexity heavily depends on the size of gap used (amortised O(n^4/3) as Sedgewick gap is used in this implementation), but best case of O(n * log2 n), worst case of O(n^2)\n";
      break;
  }

  std::cout << "Key: n = size of input list, k = digits of largest input\n";

}
