#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char *argv[]) {
  const size_t WINDOW_SIZE = 3;

  if (argc < 2) {
    cerr << "no input file specified" << endl;
    return 1;
  }

  ifstream input(argv[1]);
  if (!input.good()) {
    cerr << "failed to open file: " << argv[1] << endl;
    return 1;
  }

  // part 1
  int prev_depth;
  size_t depth_increases = 0;

  // part 2
  int window[WINDOW_SIZE] = {0};
  int prev_window_sum = 0;
  int sliding_window_depth_increases = 0;

  string line;
  size_t current_line = 0;
  while (getline(input, line)) {
    auto depth = stoi(line);

    if (current_line > 0 && depth > prev_depth) {
      depth_increases += 1;
    }
    prev_depth = depth;

    int window_sum = depth;
    for (int window_idx = 0; window_idx < WINDOW_SIZE-1; ++window_idx) {
      window[window_idx] = window[window_idx+1];
      window_sum += window[window_idx];
    }
    window[WINDOW_SIZE-1] = depth;
    cout << current_line << ": " << window_sum << " " << prev_window_sum << endl;

    if (current_line >= WINDOW_SIZE && window_sum > prev_window_sum) {
      sliding_window_depth_increases += 1;
    }
    prev_window_sum = window_sum;

    current_line += 1;
  }

  cout << "part 1: " << depth_increases << endl;
  cout << "part 2: " << sliding_window_depth_increases << endl;
}