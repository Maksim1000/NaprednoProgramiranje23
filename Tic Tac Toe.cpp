#include <iostream>
using namespace std;

char board[3][3] = {{'1', '2', '3'}, {'4', '5', '6'}, {'7', '8', '9'}};
char player = 'X';

void drawBoard() {
  cout << "Tic Tac Toe\n\n";
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      cout << board[i][j] << " ";
    }
    cout << endl;
  }
}

bool gameOver() {
  // Check for row win
  for (int i = 0; i < 3; i++) {
    if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
      return true;
    }
  }

  // Check for column win
  for (int j = 0; j < 3; j++) {
    if (board[0][j] == board[1][j] && board[1][j] == board[2][j]) {
      return true;
    }
  }

  // Check for diagonal win
  if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
    return true;
  }

  if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
    return true;
  }

  return false;
}

void switchPlayer() {
  if (player == 'X') {
    player = 'O';
  } else {
    player = 'X';
  }
}

bool makeMove(int move) {
  int row = (move - 1) / 3;
  int col = (move - 1) % 3;

  if (board[row][col] == 'X' || board[row][col] == 'O') {
    return false;
  }

  board[row][col] = player;
  return true;
}

int main() {
  int move;
  bool validMove;

  while (!gameOver()) {
    drawBoard();

    validMove = false;
    while (!validMove) {
      cout << "Player " << player << ", enter your move: ";
      cin >> move;

      validMove = makeMove(move);

      if (!validMove) {
        cout << "Invalid move. Try again." << endl;
      }
    }

    switchPlayer();
  }

  drawBoard();
  cout << "Player " << (player == 'X' ? 'O' : 'X') << " wins!" << endl;

  return 0;
}