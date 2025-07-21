export module algorithms.lsd_radix_sort;

import <vector>;
import <iostream>;
import <algorithm>;
import <cmath>;
import <type_traits>;
import <string>;

export template <typename t>
class lsd_radix_sort {
public:
    lsd_radix_sort(std::vector<t> list) : m_list(std::move(list)) {}

    void sort() {
        if constexpr (std::is_arithmetic_v<t> && !std::is_same_v<t, bool>) { // only for numeric values
            std::vector<T> negatives, positives;

            for (t val : m_list) {
                if (val < 0) {
                    negatives.push_back(-val);
                } else {
                    positives.push_back(val);
                }
            }

            lsd_radix(negatives);
            lsd_radix(positives);

            std::reverse(negatives.begin(), negatives.end());
            for (t& val : negatives) {
                val = -val;
            }

            m_list = negatives;
            m_list.insert(m_list.end(), positives.begin(), positives.end());
        } else {
            lsd_radix(m_list);  // generic sort for non-numeric types
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
        size_t input_mem = m_list.capacity() * sizeof(t);
        size_t bucket_mem = buckets.size() * sizeof(std::vector<t>);

        size_t data_mem = 0;
        for (const auto& b : buckets) {
            data_mem += b.capacity() * sizeof(T);
        }

        size_t total = input_mem + bucket_mem + data_mem;

        std::cout << "Estimated total memory used: " << total << " B\n";
    }

private:
    std::vector<t> m_list;
    std::vector<std::vector<t>> buckets;

    void lsd_radix(std::vector<t>& list) {
        if (list.empty()) return;

        if constexpr (std::is_integral_v<t>) {
            int maxNum = *std::max_element(list.begin(), list.end());
            int maxDigits = 0;
            while (maxNum > 0) {
                ++maxDigits;
                maxNum /= 10;
            }

            for (int digit = 0; digit < maxDigits; ++digit) {
                buckets.assign(10, {});
                for (t num : list) {
                    int digitVal = (num / static_cast<t>(std::pow(10, digit))) % 10;
                    buckets[digitVal].push_back(num);
                }

                list.clear();
                for (const auto& bucket : buckets) {
                    list.insert(list.end(), bucket.begin(), bucket.end());
                }
            }
        } else {
            // fallback for non-numeric types: use std::sort
            std::cout << "Type (mangled) used for the conversion: " << typeid(t).name() << " , so standard library introsort implemented, as this sort is only for numeric values\n" << std::endl;
            std::sort(list.begin(), list.end());
        }
    }
};
