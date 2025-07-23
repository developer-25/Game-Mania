//         Snake And Ladder Game

#include<iostream>  
#include<bits/stdc++.h>  
#include<ctime>
#include<cstdlib>

using namespace std;

// roll a die
int rollDie(){
    return rand() % 6 + 1;
}

// players position
int player1 = 0, player2 = 0;

// Print Board
void printBoardSnakeAndLadder(){
    vector<int> board(101);
    for(int i=1;i<=100;i++){
        board[i] = i;
    }

    int alt = 0; // switcg between the alternate nature
    int iterLR = 101; // print L To R
    int iterRL = 80; // print R to L
    int val = 100;

    while(val--) { 
        if(alt == 0){ 
            iterLR--; 
            if(iterLR == player1){ 
                cout<<"#P1    "; 
            } 
            else if(iterLR == player2){ 
                cout<<"#P2    "; 
            } 
            else{
                cout<<board[iterLR]<<"    "; 
            }
  
            if(iterLR % 10 == 1){ 
                cout<<"\n\n"; 
                alt = 1; 
                iterLR -= 10; 
            } 
        } 
        else{ 
            iterRL++; 
            if(iterRL == player1){ 
                cout<<"#P1    "; 
            } 
            else if(iterRL == player2){ 
                cout<<"#P2    "; 
            } 
            else{
                cout<<board[iterRL]<<"    "; 
            }
            if(iterRL % 10 == 0){ 
                cout<<"\n\n"; 
                alt = 0; 
                iterRL -= 30; 
            } 
        } 
        if (iterRL == 10){
            break; 
        }
    } 
    cout<<endl; 
}

// move the player
int movePlayerSnakeAndLadder(int currPlayer, int roll){
    int newPos = currPlayer + roll;

    vector<int> snakesAndLadders(101, 0);

    // Positive = ladders, negative = snakes
    snakesAndLadders[6] = 40;
    snakesAndLadders[23] = -10;
    snakesAndLadders[45] = -7;
    snakesAndLadders[61] = -18;
    snakesAndLadders[65] = -8;
    snakesAndLadders[77] = 5;
    snakesAndLadders[98] = -10;

    int newsquare = newPos + snakesAndLadders[newPos];

    if(newsquare > 100){
        return currPlayer;
    }
    return newsquare;
}

void menuSnakeAndLadder(){
    srand(time(0));
    int currPlayer = 1;
    bool won = false;

    cout<<"Snake and Ladder Game"<<endl;
    while(!won){
        cout<<"\nPlayer "<<currPlayer<<", Press Enter to roll the die....";
        cin.ignore(); // wait for player to press enter
        int roll = rollDie();
        cout<<"You rolled a "<<roll<<"."<<endl;

        if(currPlayer == 1){
            player1 = movePlayerSnakeAndLadder(player1, roll);
            cout << "Player 1 is now at square " << player1 << ".\n\n";
            printBoardSnakeAndLadder();
            if(player1 == 100){
                cout<<"Player 1 Wins!!"<<endl;
                won = true;
            }
        }
        else{
            player2 = movePlayerSnakeAndLadder(player2, roll);
            cout << "Player 2 is now at square " << player2 << ".\n\n";
            printBoardSnakeAndLadder();
            if(player2 == 100){
                cout<<"Player 2 Wins!!"<<endl;
                won = true;
            }
        }
        currPlayer = (currPlayer == 1)?2:1;
    }
    return ;
}

 /*Minesweeper Game
 Implementation of Minesweeper Game: 
 Input for coordinates is taken from user
 */


#define Beginner 0
#define Intermediate 1
#define Advanced 2
#define maxside 25
#define maxmines 99
#define movesize 526 // (25 * 25 - 99)

int side; // side length of the board
int mine; // number of mines on the board

// check whether given cell is a valid cell or not
bool isValidMinesweeper(int row, int col)
{
    return (row >= 0) && (row < side) && (col >= 0) && (col < side);
}

class BoardMinesweeper{
    public:
    char** board;
    BoardMinesweeper(){
        board = new char*[maxside + 1];
        for (int i = 0; i <= maxside; i++){
            board[i] = new char[maxside + 1];
            for (int j = 0; j <= maxside; j++){
                board[i][j] = '-';
            }
        }
    }

    // check whether given cell has a mine or not.
    bool isMine(int row, int col){
        if (board[row][col] == '*'){
            return (true);
        }
        else{
            return (false);
        }
    }

    // user's move
    void makeMove(int* x, int* y){
        // Take the input move
        cout<<"Enter your move (row, col) ";
        scanf("%d %d", x, y);
        return;
    }

    //print the board
    void printBoard(){
        cout << "    ";
        for(int i = 0; i < side; i++){
            cout << i << " ";
        }
        cout << "\n\n";

        for(int i = 0; i < side; i++) {
            cout << i << "   ";
            for (int j = 0; j < side; j++) {
                cout << board[i][j] << " ";
            }
            cout << "\n";
        }
        return;
    }

    // cnt the number of mines in the adjacent cell
    int countAdjacentMines(int row, int col, int mines[][2]){
        int cnt = 0;

        int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
        int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };

        for(int d = 0; d < 8; d++) {
            int newRow = row + dx[d];
            int newCol = col + dy[d];

            if (isValidMinesweeper(newRow, newCol) == true) {
                if (isMine(newRow, newCol) == true){
                    cnt++;
                }
            }
        }
        return cnt;
    }

    // place the mines randomly on the board
    void placeMines(int mines[][2]){
        bool mark[maxside * maxside];

        memset(mark, false, sizeof(mark));

        // Continue til all random mines created.
        for (int i = 0; i < mine;) {
            int random = rand() % (side * side);
            int x = random / side;
            int y = random % side;

            // Add the mine if no mine
            if (mark[random] == false) {
                mines[i][0] = x;
                mines[i][1] = y;

                // Place the mine
                board[mines[i][0]][mines[i][1]] = '*';
                mark[random] = true;
                i++;
            }
        }
        return;
    }

    // replace the mine put it to a vacant space
    void replaceMine(int row, int col){
        for (int i = 0; i < side; i++) {
            for (int j = 0; j < side; j++) {
                // find first location in the board not having a mine and put a mine there.
                if (board[i][j] != '*') {
                    board[i][j] = '*';
                    board[row][col] = '-';
                    return;
                }
            }
        }
        return;
    }
};

class GameMinesweeper{
public:
    // play the Minesweeper Game
    bool playMinesweeperUtil(BoardMinesweeper& myBoard, BoardMinesweeper& realBoard, int mines[][2], int row, int col, int* movesLeft){
        // base case
        if (myBoard.board[row][col] != '-'){
            return (false);
        }

        // mine open we will lose
        if (realBoard.board[row][col] == '*') {
            myBoard.board[row][col] = '*';
            for(int i = 0; i < mine; i++){
                myBoard.board[mines[i][0]][mines[i][1]] = '*';
            }
            myBoard.printBoard();
            cout<<"\nMy Badassss!\n";
            return true;
        }
        else {
            // number of adjacent mines and the board
            int cnt = realBoard.countAdjacentMines(row, col, mines);
            (*movesLeft)--;

            myBoard.board[row][col] = cnt + '0';
            if (!cnt) {
                int dx[8] = { -1, -1, -1, 0, 0, 1, 1, 1 };
                int dy[8] = { -1, 0, 1, -1, 1, -1, 0, 1 };
                for(int d = 0; d < 8; d++) {
                    int newRow = row + dx[d];
                    int newCol = col + dy[d];
                    if(isValidMinesweeper(newRow, newCol) == true) {
                        if(realBoard.isMine(newRow, newCol) == false){
                            playMinesweeperUtil(myBoard, realBoard, mines, newRow, newCol, movesLeft);
                        }
                    }
                }
            }
            return false;
        }
    }

    // cheat by revealing where the mines are placed.
    void cheatMinesweeper(BoardMinesweeper& realBoard){
        cout<<"The mines locations are-\n";
        realBoard.printBoard();
        return;
    }

    // play Minesweeper game
    void playMinesweeper(BoardMinesweeper& realBoard, BoardMinesweeper& myBoard){
        // the game is not over
        bool gameOver = false;

        int movesLeft = side * side - mine, x, y;
        // stores (x,y) of all mines.
        int mines[maxmines][2];

        // Place the Mines randomly
        realBoard.placeMines(mines);

        // If you want to cheat and know where mines are before playing the game then uncomment this part

        // cheatMinesweeper(realBoard);

        // You are in the game until you have not opened a mine

        int currentMoveIndex = 0;
        while (gameOver == false) {
            cout<<"Current Status of Board : \n";
            myBoard.printBoard();
            myBoard.makeMove(&x, &y);

            //the first move is always safe
            // If it is the first move
            if (currentMoveIndex == 0) {
                // If the first move itself is a mine remove the mine
                if (realBoard.isMine(x, y) == true)
                    realBoard.replaceMine(x, y);
            }
            currentMoveIndex++;
            gameOver = playMinesweeperUtil(
                myBoard, realBoard, mines, x, y,
                &movesLeft);
            if ((gameOver == false) && (movesLeft == 0)) {
                printf("\nYou won !\n");
                gameOver = true;
            }
        }
        return;
    }
};

void chooseDifficultyLevel()
{
    /*
    --> BEGINNER = 9 * 9 Cells and 10 Mines
    --> INTERMEDIATE = 16 * 16 Cells and 40 Mines
    --> ADVANCED = 24 * 24 Cells and 99 Mines
    */

    int level;

    cout<<"Enter the Difficulty Level\n";
    cout<<"0 -> Beginner (9 X 9 Cells and 10 Mines)\n";
    cout<<"1 -> Intremediate (16 X 16 Cells and 40 Mines)\n";
    cout<<"2 -> Advanced (24 X 24 Cells and 99 Mines)\n";

    cin>>level;

    if (level == Beginner) {
        side = 9;
        mine = 10;
    }
    if (level == Intermediate) {
        side = 16;
        mine = 40;
    }
    if (level == Advanced) {
        side = 24;
        mine = 99;
    }
}

void displayMenu() {
    cout << "\n======== Minesweeper Game Menu ========\n";
    cout << "1. Start New Game\n";
    cout << "2. Choose Difficulty Level\n";
    cout << "3. Exit\n";
    cout << "=======================================\n";
    cout << "Enter your choice: ";
}

void startGame() {
    BoardMinesweeper myBoard, realBoard;
    GameMinesweeper* game = new GameMinesweeper();
    game->playMinesweeper(myBoard, realBoard);
    delete game;
}


int menuMinesweepers(){
    srand(time(0)); // Seed for random number generation
    int choice;

    // Default difficulty level
    side = 9;
    mine = 10;

    while (true) {
        displayMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "\nStarting New Game...\n";
            startGame();
            break;
        case 2:
            chooseDifficultyLevel();
            break;
        case 3:
            cout << "\nThank you for playing Minesweeper! Goodbye!\n";
            return 0;
        default:
            cout << "\nInvalid choice! Please try again.\n";
        }
    }
    return 0;
}


// Rock-Paper-Scissors

// get the computer move
char getComputerMove(){
    int move;
    // generating random number between 0 - 2
    srand(time(NULL));
    move = rand() % 3;

    // returning move based on the random number generated
    if (move == 0) {
        return 'p';
    }
    else if (move == 1) {
        return 's';
    }
    return 'r';
}

// Function to return the result of the game
int getResults(char playerMove, char computerMove){
    // condition for draw
    if (playerMove == computerMove){
        return 0;
    }

    // condition for win and loss according to game rule
    if (playerMove == 's' && computerMove == 'p'){
        return 1;
    }
    if (playerMove == 's' && computerMove == 'r'){
        return -1;
    }
    if (playerMove == 'p' && computerMove == 'r'){
        return 1;
    }
    if (playerMove == 'p' && computerMove == 's'){
        return -1;
    }
    if (playerMove == 'r' && computerMove == 'p'){
        return -1;
    }
    if (playerMove == 'r' && computerMove == 's'){
        return 1;
    }
    
    return 0;
}

void menuRockPapperAndScissors(){
    char playerMove;
    cout << "\n\n\n\t\t\tWelcome to Stone Paper Scissor Game\n";
    cout << "\n\t\tEnter r for ROCK, p for PAPER, and s for SCISSOR\n\t\t\t\t\t";
    // input from the user
    while(1) {
        cin >> playerMove;
        if (playerMove == 'p' || playerMove == 'r' || playerMove == 's') {
            break;
        }
        else {
            cout << "\t\t\tInvalid Player Move!!! Please Try Again." << endl;
        }
    }
    // computer move
    char computerMove = getComputerMove();
    int result = getResults(playerMove, computerMove);
    // priting result based on who won the game
    if (result == 0) {
        cout << "\n\t\t\tGame Draw!\n";
    }
    else if (result == 1) {
        cout << "\n\t\t\tCongratulations! Player won the game!\n";
    }
    else {
        cout << "\n\t\t\tOh! Computer won the game!\n";
    }

    // showing both  moves
    cout << "\t\t\tYour Move: " << playerMove << endl;
    cout << "\t\t\tComputer's Move: " << computerMove << endl;

    return ;
}


// Sudoku Solver
// C++ Code
// Input matrix
#define N 9

// Bitmasks for each row/column/box
int row[N], col[N], box[N];
bool seted = false;

// Utility function to find the box index of an element at position [i][j] in the grid
int getBox(int i, int j) { return i / 3 * 3 + j / 3; }

// Utility function to check if a number is present in the corresponding row/column/box
bool isSafe(int i, int j, int number)
{
    return !((row[i] >> number) & 1)
           && !((col[j] >> number) & 1)
           && !((box[getBox(i, j)] >> number) & 1);
}

// Utility function to set the initial values of a Sudoku board (map the values in the bitmasks)
void setInitialValues(int grid[N][N])
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            row[i] |= 1 << grid[i][j],
                col[j] |= 1 << grid[i][j],
                box[getBox(i, j)] |= 1 << grid[i][j];
}

/* Takes a partially filled-in grid and attempts
to assign values to all unassigned locations in
such a way to meet the requirements for
Sudoku solution (non-duplication across rows,
columns, and boxes) */
bool SolveSudoku(int grid[N][N], int i, int j)
{
    // Set the initial values
    if (!seted)
        seted = true, setInitialValues(grid);

    if (i == N - 1 && j == N)
        return true;
    if (j == N)
        j = 0, i++;

    if (grid[i][j])
        return SolveSudoku(grid, i, j + 1);

    for (int nr = 1; nr <= N; nr++) {
        if (isSafe(i, j, nr)) {
            /*  Assign nr in the
                current (i, j)
                position and
                add nr to each bitmask
            */
            grid[i][j] = nr;
            row[i] |= 1 << nr;
            col[j] |= 1 << nr;
            box[getBox(i, j)] |= 1 << nr;

            if (SolveSudoku(grid, i, j + 1))
                return true;

            // Remove nr from each bitmask
            // and search for another possibility
            row[i] &= ~(1 << nr);
            col[j] &= ~(1 << nr);
            box[getBox(i, j)] &= ~(1 << nr);
        }

        grid[i][j] = 0;
    }

    return false;
}

// Utility function to print the solved grid
void printSudoku(int grid[N][N])
{
    for (int i = 0; i < N; i++, cout << '\n')
        for (int j = 0; j < N; j++)
            cout << grid[i][j] << ' ';
}

void menuSudokuSolver(){
    int grid[N][N] = { { 3, 0, 6, 5, 0, 8, 4, 0, 0 },
                       { 5, 2, 0, 0, 0, 0, 0, 0, 0 },
                       { 0, 8, 7, 0, 0, 0, 0, 3, 1 },
                       { 0, 0, 3, 0, 1, 0, 0, 8, 0 },
                       { 9, 0, 0, 8, 6, 3, 0, 0, 5 },
                       { 0, 5, 0, 0, 9, 0, 6, 0, 0 },
                       { 1, 3, 0, 0, 0, 0, 2, 5, 0 },
                       { 0, 0, 0, 0, 0, 0, 0, 7, 4 },
                       { 0, 0, 5, 2, 0, 6, 3, 0, 0 } };
    int choice;

    cout << "\n==== Sudoku Game Menu ====\n";
    cout << "1. View Sudoku Board\n";
    cout << "2. Start Solving Sudoku\n";
    cout << "3. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1:{
            cout << "\nCurrent Sudoku Board:\n";
            printSudoku(grid);
            break;
        }
        case 2: {
            cout << "\nStarting to solve the Sudoku...\n";
            if (SolveSudoku(grid, 0, 0)){
                printSudoku(grid);
            }
            else{
                cout << "No solution exists\n";
            }
            break;
        }
        case 3:{
            cout << "Exiting the game. Goodbye!\n";
            break;
        }
        default:{
            cout << "Invalid choice. Please try again.\n";
        }
    }
    return ;
}

// Full MEnu
void displayMainMenu() {
    cout << "\n======== Game Menu ========\n";
    cout << "1. Snake and Ladder\n";
    cout << "2. Minesweeper\n";
    cout << "3. Rock-Papper-Scissor\n";
    cout << "4. Sudoku\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

int main() {
    srand(time(0)); // Seed for randomness
    int choice;

    do {
        displayMainMenu();
        cin >> choice;

        switch (choice) {
            case 1: {
                cout << "\nStarting Snake and Ladder Game...\n";
                menuSnakeAndLadder();
                break;
            }
            case 2: {
                cout << "\nStarting Minesweeper Game...\n";
                chooseDifficultyLevel();
                BoardMinesweeper realBoard;
                BoardMinesweeper myBoard;
                GameMinesweeper game;
                game.playMinesweeper(realBoard, myBoard);
                break;
            }
            case 3: {
                cout << "\nStarting Rock-Papper-Scissor Game...\n";
                menuRockPapperAndScissors();
                break;
            }
            case 4: {
                cout << "\nStarting Sudoku Game...\n";
                menuSudokuSolver();
                break;
            }
            case 5: {
                cout << "\nExiting the application. Goodbye!\n";
                break;
            }
            default: {
                cout << "\nInvalid choice. Please try again.\n";
                break;
            }
        }
    } while (choice != 5);

    return 0;
}