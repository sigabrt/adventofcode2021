#include <bitset>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<size_t> count_bits(const vector<uint32_t> &numbers);
void update_one_bits(uint32_t number, vector<size_t> &one_bits, size_t number_of_bits) {
  for (size_t bit_idx = 0; bit_idx < number_of_bits; ++bit_idx) {
    one_bits[bit_idx] += ((number & (1 << bit_idx)) != 0) ? 1 : 0;
  }
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cerr << "no input file specified" << endl;
    return 1;
  }

  ifstream input(argv[1]);
  if (!input.good()) {
    cerr << "failed to open file: " << argv[1] << endl;
    return 1;
  }

  size_t number_of_bits = 0;
  vector<size_t> one_bits;
  vector<uint32_t> numbers;
  for (string line; getline(input, line); ) {
    if (number_of_bits == 0) {
      number_of_bits = line.length();
      one_bits.resize(number_of_bits, 0);
    }

    uint32_t number = stoul(line, nullptr, 2);
    numbers.push_back(number);
    update_one_bits(number, one_bits, number_of_bits);
  }

  // part 1
  uint32_t gamma = 0, epsilon = 0;
  for (size_t bit_idx = 0; bit_idx < number_of_bits; ++bit_idx) {
    auto one_bit_count = one_bits[bit_idx];
    auto zero_bit_count = numbers.size() - one_bit_count;
    if (one_bit_count > zero_bit_count) {
      gamma |= (1 << bit_idx);
    } else {
      epsilon |= (1 << bit_idx);
    }
  }

  // part 2
  uint32_t oxygen_mask = 0, co2_mask = 0, number_mask = 0;
  size_t oxygen, co2;
  bool found_oxygen = false, found_co2 = false;
  function<bool(uint32_t)> oxygen_pred = [&](uint32_t) { return true; };
  function<bool(uint32_t)> co2_pred = [&](uint32_t) { return true; };
  for (size_t bit_idx = number_of_bits-1; bit_idx >= 0; --bit_idx) {
    vector<size_t> oxygen_one_bits(number_of_bits, 0);
    size_t oxygen_count = 0;

    vector<size_t> co2_one_bits(number_of_bits, 0);
    size_t co2_count = 0;

    for (auto n : numbers) {
      if (oxygen_pred(n)) {
        update_one_bits(n, oxygen_one_bits, number_of_bits);
        oxygen_count += 1;
      }

      if (co2_pred(n)) {
        update_one_bits(n, co2_one_bits, number_of_bits);
        co2_count += 1;
      }
    }

    if (oxygen_one_bits[bit_idx] >= oxygen_count - oxygen_one_bits[bit_idx]) {
      oxygen_mask |= (1 << bit_idx);
    }

    if (co2_one_bits[bit_idx] < co2_count - co2_one_bits[bit_idx]) {
      co2_mask |= (1 << bit_idx);
    }

    number_mask |= (1 << bit_idx);
    oxygen_pred = [&](uint32_t n) { return (n & number_mask) == oxygen_mask; };
    co2_pred = [&](uint32_t n) { return (n & number_mask) == co2_mask; };
    if (!found_oxygen && count_if(numbers.begin(), numbers.end(), oxygen_pred) == 1) {
      found_oxygen = true;
      oxygen = *find_if(numbers.begin(), numbers.end(), oxygen_pred);
    }

    if (!found_co2 && count_if(numbers.begin(), numbers.end(), co2_pred) == 1) {
      found_co2 = true;
      co2 = *find_if(numbers.begin(), numbers.end(), co2_pred);
    }

    if (found_oxygen && found_co2) {
      break;
    }
  }

  cout << "part 1: " << gamma * epsilon << endl;
  cout << "part 2: " << oxygen * co2 << endl;
}