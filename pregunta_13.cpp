#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

std::mutex mtx;

void fibonacci_section(std::vector<unsigned long long>& fib_sequence, int start, int end) {
    for (int i = start; i < end; ++i) {
        fib_sequence[i] = fib_sequence[i - 1] + fib_sequence[i - 2];
    }
}

int main() {
    const int num_terms = 1000;
    const int num_threads = 4; // Cambia esto dependiendo de cuántos threads quieres usar

    std::vector<unsigned long long> fib_sequence(num_terms, 0);
    fib_sequence[0] = 0;
    fib_sequence[1] = 1;

    std::vector<std::thread> threads;

    int section_size = (num_terms - 2) / num_threads;
    int remainder = (num_terms - 2) % num_threads;
    int start = 2;

    for (int i = 0; i < num_threads; ++i) {
        int end = start + section_size;
        if (remainder > 0) {
            end++;
            remainder--;
        }
        threads.push_back(std::thread(fibonacci_section, std::ref(fib_sequence), start, end));
        start = end;
    }

    for (auto& th : threads) {
        th.join();
    }

    // Imprimir la secuencia
    for (const auto& num : fib_sequence) {
        std::cout << num << std::endl;
    }

    return 0;
}
