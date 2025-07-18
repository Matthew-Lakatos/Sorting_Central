export module lsd_radix_sort;

import <vector>;
import <iostream>;
import <algorithm>;
import <cmath>;

class lsd_radix_sort {
  public:

    lsd_radix_sort(std::vector<int> list) : m_list(std::move(list)) {};

    void sort() {

    std::vector<int> negatives, positives;

    // separate negative and positive numbers
    for (int i : m_list) {
        if (i < 0) {
            negatives.push_back(-i); // make negative numbers positive for sorting
        } else {
            positives.push_back(i);
        }
    }

    // sort separately
    lsd_radix(negatives);
    lsd_radix(positives);

    // reverse negatives (since more negative means smaller)
    std::reverse(negatives.begin(), negatives.end());
    for (int& i : negatives) {
        i = -i; // convert back to negative
    }

    // merge into final list
    m_list = negatives;
    m_list.insert(m_list.end(), positives.begin(), positives.end());
    }

    void lsd_radix(std::vector<int>& list) {
      if (list.empty()) return;

      // find the maximum number to determine number of digits
      int maxNum = *std::max_element(list.begin(), list.end());
      int maxDigits = 0;

      while (maxNum > 0) {

        ++maxDigits;
        maxNum /= 10;

      }

      // the actual logic behind the sort
      for (int digit = 0; digit < maxDigits; ++digit) {
        std::vector<std::vector<int>> buckets(10);
        }

        for (int num : list) {

          int digitVal = (num / static_cast<int>(std::pow(10, digit))) % 10;
          buckets[digitVal].push_back(num);

        }

        // flatten buckets back into list
        list.clear();

        for (const auto& bucket : buckets) {

          list.insert(list.end(), bucket.begin(), bucket.end());

        }
    }

    void print() const {
        std::cout << "[ ";
        for (auto it = m_list.begin(); it != m_list.end(); ++it) {
            std::cout << *it;
            if (std::next(it) != m_list.end()) std::cout << ", ";
        }
        std::cout << " ]\n";
    }

    void report_memory() const {
        size_t input_mem = arr.capacity() * sizeof(int);
        size_t bucket_mem = buckets.size() * sizeof(std::vector<int>);

        size_t data_mem = 0;
        for (const auto& b : buckets) {
            data_mem += b.capacity() * sizeof(int);
        }

        size_t total = input_mem + bucket_mem + data_mem;

        std::println("Estimated total memory used: {} B\n", total);
    }

  private:
    std::vector<int> m_list;

};
