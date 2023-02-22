#include <iostream>
#include <stack>
#include <vector>
#include <random>
#include <Windows.h>

using namespace std;

void setConsoleSize(int width, int height)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SMALL_RECT rect = { 0, 0, static_cast<SHORT>(width - 1), static_cast<SHORT>(height - 1) };
    COORD size = { static_cast<SHORT>(width), static_cast<SHORT>(height) };
    SetConsoleWindowInfo(hConsole, TRUE, &rect);
    SetConsoleScreenBufferSize(hConsole, size);
}

void setConsoleColor(WORD color)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    // Your code here
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void drawBackground()
{
    setConsoleColor(0x0B);
    for (int y = 0; y < 50; y++)
    {
        for (int x = 0; x < 80; x++)
        {
            cout << ".";
        }
        cout << endl;
    }
}
void drawImage(){
    setConsoleColor(0x0F);
    cout << "            /\\         \n";
    cout << "           /  \\        \n";
    cout << "          /    \\       \n";
    cout << "         /      \\      \n";
    cout << "        /        \\     \n";
    cout << "       /          \\    \n";
    cout << "      /            \\   \n";
    cout << "     /______________\\  \n";
    cout << "     \\______________/  \n";
    cout << "     /\\            /\\  \n";
    cout << "    /  \\          /  \\ \n";
    cout << "   /    \\        /    \\ \n";
    cout << "  /      \\      /      \\ \n";
    cout << " /        \\    /        \\ \n";
    cout << "/__________\\/__________\\\n";
    cout << "\\          /\\          / \n";
    cout << " \\        /  \\        /  \n";
    cout << "  \\      /    \\      /   \n";
    cout << "   \\    /      \\    /    \n";
    cout << "    \\  /        \\  /     \n";
    cout << "     \\/__________\\/      \n";

    // Print the title of the maze simulation
    setConsoleColor(0x0A);
    cout << "Maze Simulation\n\n";
}

const int ROWS = 10;
const int COLS = 10;

// Define the maze grid as a 2D array of booleans
bool maze[ROWS][COLS];

// Define a struct to represent a cell in the maze
struct Cell
{
    int row;
    int col;
    bool visited;
};

// Define a vector of possible directions for the maze algorithm to move in
vector<pair<int, int>> directions = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

// Generate a random number in the range [low, high)
int random(int low, int high)
{
    static random_device rd;
    static mt19937 gen(rd());
    uniform_int_distribution<> dist(low, high - 1);
    return dist(gen);
}

// Initialize the maze to all walls
void initializeMaze()
{
    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            maze[row][col] = true;
        }
    }
}

// Generate a random maze using the depth-first search algorithm
void generateMaze()
{
    stack<Cell> cellStack;
    Cell currentCell = { 0, 0, true };
    maze[0][0] = false;

    while (true)
    {
        vector<Cell> neighbors;
        for (auto& dir : directions)
        {
            int row = currentCell.row + dir.first;
            int col = currentCell.col + dir.second;
            if (row >= 0 && row < ROWS && col >= 0 && col < COLS && maze[row][col])
            {
                neighbors.push_back({ row, col, false });
            }
        }

        if (neighbors.empty())
        {
            if (cellStack.empty())
            {
                break;
            }
            currentCell = cellStack.top();
            cellStack.pop();
        }
        else
        {
            Cell nextCell = neighbors[random(0, neighbors.size())];
            maze[nextCell.row][nextCell.col] = false;
            cellStack.push(currentCell);
            currentCell = nextCell;
        }
    }
}





// Display the maze on the screen
void displayMaze(Cell currentCell)
{
    std::cout << "Displaying maze with currentCell at (" << currentCell.row << ", " << currentCell.col << "):" << endl;
    // Define strings for the maze walls and floor
    string wall = "\u2588\u2588";
    string floor = "  ";

    // Print the maze row by row
    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            // Print the current cell
            if (row == currentCell.row && col == currentCell.col)
            {
                cout << "O ";
            }
            // Print the maze walls
            else if (maze[row][col])
            {
                cout << wall;
            }
            // Print the maze floor
            else
            {
                cout << floor;
            }
        }
        cout << endl;
    }
}


// Solve the maze using the depth-first search algorithm
bool solveMaze(Cell currentCell)
{
    if (currentCell.row < 0 || currentCell.row >= ROWS || currentCell.col < 0 || currentCell.col >= COLS)
    {
        return false;
    }
    if (!maze[currentCell.row][currentCell.col])
    {
        return false;
    }
    if (currentCell.row == ROWS - 1 && currentCell.col == COLS - 1)
    {
        return true;
    }

    maze[currentCell.row][currentCell.col] = false;

    for (auto& dir : directions)
    {
        Cell nextCell = { currentCell.row + dir.first, currentCell.col + dir.second, false };
        if (solveMaze(nextCell))
        {
            return true;
        }
    }
}

void playMazeGame() {
    initializeMaze();  // Initialize the maze to all walls
    generateMaze();    // Generate a random maze
    Cell currentCell = { 0, 0, false }; // Set the current cell to the top-left corner
    displayMaze(currentCell);  // Display the maze on the screen

    while (true) {
        // Read user input
        char userInput;
        cin >> userInput;

        // Update the current cell based on the user input
        if (userInput == 'w') {
            Cell nextCell = { currentCell.row - 1, currentCell.col, false };
            if (nextCell.row >= 0 && !maze[currentCell.row][currentCell.col * 2 + 1]) {
                currentCell = nextCell;
            }
        }
        else if (userInput == 'a') {
            Cell nextCell = { currentCell.row, currentCell.col - 1, false };
            if (nextCell.col >= 0 && !maze[currentCell.row * 2 + 1][currentCell.col]) {
                currentCell = nextCell;
            }
        }
        else if (userInput == 's') {
            Cell nextCell = { currentCell.row + 1, currentCell.col, false };
            if (nextCell.row < ROWS && !maze[currentCell.row + 1][currentCell.col * 2 + 1]) {
                currentCell = nextCell;
            }
        }
        else if (userInput == 'd') {
            Cell nextCell = { currentCell.row, currentCell.col + 1, false };
            if (nextCell.col < COLS && !maze[currentCell.row * 2 + 1][currentCell.col + 1]) {
                currentCell = nextCell;
            }
        }
        else if (userInput == 'q') {
            break;  // Quit the game
        }

        // Clear the console, draw the background and image, and display the updated maze
        system("cls");
        drawBackground();
        drawImage();
        displayMaze(currentCell);

        // Check if the player has reached the end of the maze
        if (currentCell.row == ROWS - 1 && currentCell.col == COLS - 1) {
            cout << "Congratulations, you have reached the end of the maze!" << endl;
            break;
        }
    }
}


int main() {\
    setConsoleSize(80, 50);
    drawBackground();
    drawImage();
    playMazeGame();
    return 0;
}

