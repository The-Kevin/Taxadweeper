#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>

using namespace std;
#define PROBABILITY_MINE 20 // value in porcentage

int main(int argc, char *argv[])
{

    srand(time(0));
    sf::RenderWindow window(sf::VideoMode(640, 480), "Mine sweeper - @The-Kevin");
    sf::Texture texture;

    texture.loadFromFile("files/tiles.jpg");
    sf::Sprite s(texture);

    int cellSize = 32;
    int grid[12][12];  // grid size
    int sgrid[12][12]; // grid currently state

    /**
     *  @explain the code below
     *  The code below set the grid and initial values
     *  first set all sgrid state with 10 as not discovered
     *  below get the current cell and calculate the probability to be a mine
     *  defined by the macro variable and set the cell as 9 to be a mine
     *  if is not a mine, define as 0, not is a mine
     *
     *  @definitions
     *  0 = not a mine
     *  9 = is a mine
     *  10 = undefined or not discovered
     */

    for (int i = 1; i <= 10; i++)
    {
        for (int j = 1; j <= 10; j++)
        {
            sgrid[i][j] = 10;
            if (rand() % 100 < PROBABILITY_MINE)
            {
                grid[i][j] = 9;
                continue;
            }
            grid[i][j] = 0;
        }
    }

    /**
     *  @explain the code below
     *  This is a calculum about the cell close the mines
     *  it's very simple, if the cell is 9 (a mine)
     *  continue, do nothing
     *  the number is a 0 by default, the loop for 8 positions is about
     *  the dx and dy arrays, looping through the array and checking the positions
     *  incrementing the number value of the cell (the n variable) according if there's a mine around
     *
     *  this was be implemented in this way to avoid too many if/elses
     */

    int dx[] = {1, 1, 0, -1, -1, -1, 0, 1}; // x-displacements of the 8 directions
    int dy[] = {0, 1, 1, 1, 0, -1, -1, -1}; // y-displacements of the 8 directions
    for (int i = 1; i <= 10; i++)
    {
        for (int j = 1; j <= 10; j++)
        {
            if (grid[i][j] == 9)
                continue;

            int n = 0;

            for (int k = 0; k < 8; k++)
            {
                int ni = i + dx[k];
                int nj = j + dy[k];

                if (grid[ni][nj] == 9)
                    n++;
            }
            grid[i][j] = n;
        }
    }

    while (window.isOpen())
    {
        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::White);
        window.display();
    }
    return 0;
}
