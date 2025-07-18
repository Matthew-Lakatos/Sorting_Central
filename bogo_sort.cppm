export module bogo_sort;

import <iostream>;
import <vector>;
import <algorithm>;
import <chrono>;
import <random>;
import <ranges>;
import <format>;

export template <typename t>
class bogo_sort {
public:
    bogo_sort(std::vector<t> list) : m_list(std::move(list)) {}

    // Sorts using bogo sort until max_duration_ms is reached
    void sort(double max_duration_ms, std::chrono::steady_clock::time_point start) {
        std::random_device rd;
        std::mt19937 gen(rd());

        auto first = m_list.begin();
        auto last = m_list.end();
        double elapsed_ms = 0.0;

        while (!std::is_sorted(first, last) && elapsed_ms < max_duration_ms) {
            std::ranges::shuffle(m_list, gen); // C++20 ranges-based shuffle
            auto now = std::chrono::steady_clock::now();
            elapsed_ms = std::chrono::duration<double, std::milli>(now - start).count();
        }

        if (elapsed_ms >= max_duration_ms) {
            std::println("Took over {:.2f} ms, list has not been sorted", max_duration_ms);
        }
    }

    void report_memory() const {
        std::size_t element_size = sizeof(t);
        std::size_t total_size = m_list.capacity() * element_size + 2500; // mt19937 internal state estimate

        std::println("Estimated total memory used: {} B", total_size);
    }

    void print() const {
        std::cout << "[ ";
        for (auto it = m_list.begin(); it != m_list.end(); ++it) {
            std::cout << *it;
            if (std::next(it) != m_list.end()) std::cout << ", ";
        }
        std::cout << " ]\n";
    }

private:
    std::vector<t> m_list;
};

