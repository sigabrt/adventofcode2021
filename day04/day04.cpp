#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

class BingoBoard {
  struct Tile {
    int val = 0;
    bool marked = false;
  };
  
  size_t m_grid_size;
  std::vector<Tile> m_board;
  
public:
  BingoBoard(size_t grid_size)
    : m_grid_size(grid_size),
      m_board(m_grid_size * m_grid_size)
  {
  }
  
  void mark(int val) {
    for (auto &tile : m_board) {
      if (tile.val == val) {
        tile.marked = true;
        break;
      }
    }
  }
  
  void set(size_t row, size_t col, int val) {
    m_board[row*m_grid_size+col].val = val;
  }
  
  bool has_bingo() const {
    for (size_t row = 0; row < m_grid_size; ++row) {
      auto marked = true;
      for (size_t col = 0; col < m_grid_size; ++col) {
        marked &= m_board[row * m_grid_size + col].marked;
      }

      if (marked) {
        return true;
      }
    }

    for (size_t col = 0; col < m_grid_size; ++col) {
      auto marked = true;
      for (size_t row = 0; row < m_grid_size; ++row) {
        marked &= m_board[row * m_grid_size + col].marked;
      }

      if (marked) {
        return true;
      }
    }

    return false;
  }
  
  int get_score(int last_number) {
    int sum = 0;
    for (const auto &tile : m_board) {
      if (!tile.marked) {
        sum += tile.val;
      }
    }
    return sum * last_number;
  }
};

int main(int argc, char *argv[]) {
  const size_t GRID_SIZE = 5;

  if (argc < 2) {
    cerr << "no input file specified" << endl;
    return 1;
  }

  ifstream input(argv[1]);
  if (!input.good()) {
    cerr << "failed to open file: " << argv[1] << endl;
    return 1;
  }
  
  string numbers_to_draw;
  getline(input, numbers_to_draw);

  vector<BingoBoard> boards;
  size_t current_row = 0;
  for (string line; getline(input, line); ) {
    if (line.empty()) {
      current_row = 0;
      boards.emplace_back(GRID_SIZE);
    } else {
      istringstream line_stream(line);
      auto &board = boards.back();
      for (size_t col = 0; col < GRID_SIZE; ++col) {
        int val;
        line_stream >> val;
        board.set(current_row, col, val);
      }
      current_row += 1;
    }
  }
  
  istringstream number_stream(numbers_to_draw);
  bool first_bingo = false;
  for (string number_string; getline(number_stream, number_string, ','); ) {
    auto number = stoi(number_string);
    for (auto board_iter = boards.begin(); board_iter < boards.end(); ) {
      auto &board = *board_iter;
      board.mark(number);
      if (board.has_bingo()) {
        if (!first_bingo) {
          cout << "part 1: " << board.get_score(number) << endl;
          first_bingo = true;
        }
        
        if (boards.size() == 1) {
          cout << "part 2: " << board.get_score(number) << endl;
        }
        board_iter = boards.erase(board_iter);
      } else {
        ++board_iter;
      }
    }
  }
}
