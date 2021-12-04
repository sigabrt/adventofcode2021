#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

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

  int depth = 0, position = 0;
  int p2_depth = 0, p2_position = 0, p2_aim = 0;

  string line;
  while (getline(input, line)) {
    stringstream line_stream(line);
    string command;
    int delta;
    line_stream >> command >> delta;

    if (command == "forward") {
      position += delta;
      p2_position += delta;
      p2_depth += p2_aim * delta;
    } else if (command == "up") {
      depth -= delta;
      p2_aim -= delta;
    } else if (command == "down") {
      depth += delta;
      p2_aim += delta;
    }
  }

  cout << "part 1: " << depth * position << endl;
  cout << "part 2: " << p2_depth * p2_position << endl;
}