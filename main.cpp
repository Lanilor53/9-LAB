#include <iostream>
#include <array>
#include <random>
#include <ctime>

// some globals
// global variables are bad practice btw
// but I don't care here :^)
std::array<std::array<std::string,3>,3> field;
enum GameState { PLAYING, X_WIN, O_WIN, DRAW };
int turnCount;
//Setup random
std::mt19937 mt(time(nullptr)); // I love Mersenne Twister, best prng ever (maybe I like lcg better, dunno)
int RANDOM_MIN = 0;
int RANDOM_MAX = 2;
std::uniform_int_distribution<int> uid(RANDOM_MIN,RANDOM_MAX);

/**
 * Draw the game field
 */
void draw_field(){
  // Get rid of the space in front of output
  // Could be a CLion terminal-only bug
  std::cout << "\b";
  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      std::cout << "|" << field[i][j];
    }
    std::cout << "|" << std::endl;
  }
}

/**
 * Get a move from player
 * Move must come from stdin in format "%d %d"
 */
void get_move(){
  int x,y;
  std::cout << "Input your move (format: 1 3): ";
  scanf("%d %d", &x,&y);
  while(x<1 or x>3 or y<1 or y>3 or field[x-1][y-1]!=" "){
    std::cout << "Wrong move!" << std::endl;
    scanf("%d %d", &x,&y);
  }
  field[x-1][y-1] = "X";
  turnCount+=1;
};

/**
 * The Great If Tree of Win Checking
 * @return PLAYING if nobody won, X_WIN if x won, O_WIN if o won, DRAW if field is full
 */
GameState check_for_end() {
  // pls no UML
  // I can break it into 4 different functions, but it would just be stupid
  std::string winner = " ";
  // Check diagonals
  if ((field[0][0] != " " and field[0][0] == field[1][1] and field[1][1] == field[2][2]) or
      (field[0][2] != " " and field[0][2] == field[1][1] and field[1][1] == field[2][0])) {
    winner = field[1][1];
  }
    // Check horizontals
  else if (field[0][0] != " " and field[0][0] == field[0][1] and field[0][1] == field[0][2]) {
    winner = field[0][0];
  } else if (field[1][0] != " " and field[1][0] == field[1][1] and field[1][1] == field[1][2]) {
    winner = field[1][0];
  } else if (field[2][0] != " " and field[2][0] == field[2][1] and field[2][1] == field[2][2]) {
    winner = field[2][0];
  }
    // Check verticals
  else if (field[0][0] != " " and field[0][0] == field[1][0] and field[1][0] == field[2][0]) {
    winner = field[0][0];
  } else if (field[0][1] != " " and field[0][1] == field[1][1] and field[1][1] == field[2][1]) {
    winner = field[0][1];
  } else if (field[0][2] != " " and field[0][2] == field[1][2] and field[1][2] == field[2][2]) {
    winner = field[0][2];
  }
  if (winner == "X") {
    return X_WIN;
  } else if (winner == "O") {
    return O_WIN;
  } else if (turnCount == 9){
    return DRAW;
  } else{
    return PLAYING;
  }
}

/**
 * Make a random AI move
 */
void ai_move(){
  int x,y;
  x = uid(mt);
  y = uid(mt);
  while(field[x][y]!=" "){
    x = uid(mt);
    y = uid(mt);
  }
  field[x][y] = "O";
  turnCount+=1;
}

int main() {
  // and I can break this into more functions too, but it would just be stupid
  // and barely readable
  // pls no UML
  GameState state = PLAYING;
  turnCount = 0;
  // Fill the field with empty spaces
  for(int i=0;i<3;i++){
    for(int j=0;j<3;j++){
      field[i][j] = " ";
    }
  }
  // REPL
  while(state==PLAYING) {
    draw_field();
    get_move();
    state = check_for_end();
    if (state==PLAYING){
      ai_move();
      state = check_for_end();
    }
  }
  draw_field();
  if(state==X_WIN){
    std::cout << "X wins!";
  }else if(state==O_WIN){
    std::cout << "O wins!";
  }else if(state==DRAW){
    std::cout << "Draw!";
  }
  return 0;
}