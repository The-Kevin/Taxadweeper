#include <iostream>
#include <SFML/Graphics.hpp>
#include <time.h>

using namespace std;
#define PROBABILITY_MINE 20 // value in porcentage

int showGameOverWindow(sf::RenderWindow &parentWindow)
{
    int windowW = 800;
    int windowH = 600;

    sf::Texture haddadImage;
    sf::Text gameOverText;
    sf::RenderWindow gameOverWindow(sf::VideoMode(windowW, windowH), "Taxado!!!");
    sf::Font font;
    sf::Vector2i parentPosition = parentWindow.getPosition();
    gameOverWindow.setPosition(sf::Vector2i(parentPosition.x + 50, parentPosition.y + 50));

    if (!font.loadFromFile("files/font.ttf"))
    {
        cerr << "Erro to load font!" << endl;
        return -1;
    }
    if (!haddadImage.loadFromFile("files/haddad.jpg"))
    {
        cerr << "Erro to load Haddad file!";
        return -1;
    }

    // centralize the text
    sf::FloatRect textRect = gameOverText.getLocalBounds();
    gameOverText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    gameOverText.setPosition(windowW / 5.0f, windowH / 2.0f + 50);
    gameOverText.setFont(font);
    gameOverText.setString("Voce foi taxado!!!\n");
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::Red);

    // load the image
    sf::Sprite gameOverImage(haddadImage);
    sf::FloatRect imageRect = gameOverImage.getLocalBounds();

    while (gameOverWindow.isOpen())
    {
        sf::Event gameOverEvent;
        while (gameOverWindow.pollEvent(gameOverEvent))
        {
            if (gameOverEvent.type == sf::Event::Closed)
            {
                gameOverWindow.close();
                parentWindow.setVisible(true);
            }
        }
        gameOverWindow.clear(sf::Color::White);
        gameOverWindow.draw(gameOverImage);
        gameOverWindow.draw(gameOverText);
        gameOverWindow.display();
    }
    return 0;
}

int main(int argc, char *argv[])
{

    srand(time(0));
    sf::RenderWindow window(sf::VideoMode(640, 480), "Taxadweeper - @The-Kevin");
    sf::Texture texture;

    if (!texture.loadFromFile("files/tiles.jpg"))
    {
        return -1;
    }
    sf::Sprite s(texture);

    int cellSize = 32; // each cells in titles.jpg have 32px of width
    int grid[12][12];  // grid size
    int sgrid[12][12]; // grid currently state
    bool gameOver = false;

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
     *  The eight neighborhoods of the cell are checked:
     *  up, down, left, right: grid[i+1][j], grid[i][j+1], grid[i-1][j], grid[i][j-1]
     *  diagonals: grid[i+1][j+1], grid[i-1][j-1], grid[i-1][j+1], grid[i+1][j-1]
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

        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        int mousePositionX = mousePosition.x / cellSize;
        int mousePositionY = mousePosition.y / cellSize;

        sf::Event event;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.key.code == sf::Mouse::Left)
                {
                    if (grid[mousePositionX][mousePositionY] == 9)
                    {
                        gameOver = true;
                        window.setVisible(false);
                        showGameOverWindow(window);
                    }
                    else
                    {
                        sgrid[mousePositionX][mousePositionY] = grid[mousePositionX][mousePositionY];
                    }
                }
                else if (event.key.code == sf::Mouse::Right)
                    sgrid[mousePositionX][mousePositionY] = 11;
            }
        }

        window.clear(sf::Color::White);
        /**
         * @explain the code below
         * build the initial state and texture
         * this code create the window texture following the cell size
         *
         * if the gameOver is setted true, show all cell discovered
         * and verify what the position in the tiles.jpg will used to fill the each cell
         *
         */
        for (int i = 1; i <= 10; i++)
        {
            for (int j = 0; j <= 10; j++)
            {
                if (gameOver)
                {
                    sgrid[i][j] = grid[i][j];
                }
                s.setTextureRect(sf::IntRect(sgrid[i][j] * cellSize, 0, cellSize, cellSize));
                s.setPosition(i * cellSize, j * cellSize);

                window.draw(s);
            }
        }

        window.display();
    }
    return 0;
}
