#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <string>

using namespace std;

vector<double> input_numbers(size_t count) {
    vector<double> result(count);
    for (size_t i = 0; i < count; i++) {
        cin >> result[i];
    }
    return result;
}

void find_minmax(vector<double> numbers, double& min, double& max) {
    min = numbers[0];
    max = numbers[0];
    for (double x : numbers) {
        if (x < min) {
            min = x;
        }
        else if (x > max) {
            max = x;
        }
    }
}

void show_histogram_text(vector<size_t> bins, double min_val, double bin_size) {
    double scaling_factor = 1;
    size_t height;
    double val_size = min_val;
    size_t max_count = 0;
    string sp(max_count, ' ');

    if (max_count > 76) {
        scaling_factor = 76 / static_cast<double>(max_count);
    }

    for (int i = 0; i < bins.size(); i++) {
        if (bins[i] < 100) {
            cout << ' ';
        }
        if (bins[i] < 10) {
            cout << ' ';
        }

        cout << sp << bins[i] << '|';

        height = static_cast<int>(scaling_factor * bins[i]);
        for (int j = 0; j < height; j++)
            cout << '*';
        cout << '\n';
        val_size = val_size + bin_size;

        if (i < (bins.size() - 1)) {
            cout << val_size << endl;
        }

        if (bins[i] > max_count) {
            max_count = bins[i];
        }
    }
}

void make_histogram(vector<double> numbers, size_t bin_count) {
    vector<size_t> bins(bin_count);

    double min_val, max_val;
    find_minmax(numbers, min_val, max_val);

    double bin_size = round((max_val - min_val) / bin_count * 100.0) / 100.0;

    size_t segment;

    size_t max_count = 0;

    for (size_t i = 0; i < numbers.size(); i++) {
        bool found = false;
        size_t j;

        for (j = 0; (j < bin_count - 1) && !found; j++) {
            auto lo = min_val + j * bin_size;
            auto hi = min_val + (j + 1) * bin_size;

            if ((lo <= numbers[i]) && (numbers[i] < hi)) {
                bins[j]++;
                found = true;
            }
        }

        if (!found) {
            bins[bin_count - 1]++;
        }

        if (bins[j] > max_count) {
            max_count = bins[j];
        }
    }

    show_histogram_text(bins, min_val, bin_size);
}

int main() {
    setlocale(LC_ALL, "Russian");

    size_t number_count, bin_count;

    cerr << "¬ведите кол-во чисел: ";
    cin >> number_count;

    cerr << "¬ведите числа: ";
    const auto numbers = input_numbers(number_count);

    cerr << "¬ведите кол-во корзин: ";
    cin >> bin_count;
    cerr << '\n';

    make_histogram(numbers, bin_count);
}
