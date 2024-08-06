#include <SFML/Graphics.hpp>
#include<iostream>
#include <sstream>
using namespace sf;
using namespace std;
const int W = 40;
const int H = 30;
const int EnemyCount = 3;
const int ts = 20;

int grid[H][W] = { 0 };



struct Enemy
{
    int posX, posY, delx, dely;
}en[10];

//the function responsible for the movement of the enemies and their collision with the filled in part//
void Move(int& x, int& y, int& dx, int& dy)
{
    x += dx;
    if (grid[y / ts][x / ts] == 1)
    {
        dx = -dx;
        x += dx;

    }
    y += dy;
    if (grid[y / ts][x / ts] == 1)
    {
        dy = -dy;
        y += dy;
    }

}

//the function responsible for the fill in//
void fill(int y, int x)
{
    if (grid[y][x] == 0)
    {
        grid[y][x] = -1;
    }
    if (grid[y - 1][x] == 0)
    {
        fill(y - 1, x);
    }
    if (grid[y + 1][x] == 0)
    {
        fill(y + 1, x);
    }
    if (grid[y][x - 1] == 0)
    {
        fill(y, x - 1);
    }
    if (grid[y][x + 1] == 0)
    {
        fill(y, x + 1);
    }

}

int main()
{




    srand(time(0));

    RenderWindow window(VideoMode(W * ts, (H * ts) + 50), "Xonix");
    window.setFramerateLimit(60);

    Texture e, t, go, grl, lvl1;
    e.loadFromFile("C:/C++/SFML.HOME/pictures/dancingball.png");
    go.loadFromFile("C:/C++/SFML.HOME/pictures/gameover2.jpg");
    t.loadFromFile("C:/C++/SFML.HOME/pictures/tiles.jpg");
    grl.loadFromFile("C:/C++/SFML.HOME/pictures/ra2asa.png");
    lvl1.loadFromFile("C:/C++/SFML.HOME/pictures/youwin.jpg");

    Sprite enemy, tiles, gameover, girl, levelone;
    tiles.setTexture(t);
    gameover.setTexture(go);
    enemy.setTexture(e);
    girl.setTexture(grl);
    levelone.setTexture(lvl1);
    //girl.setPosition(400, 20);

    bool Game = true;
    bool win = true;
    int x = 0;
    int y = 0;
    int dx = 0;
    int dy = 0;
    float timer = 0;
    float delay = 0.07;
    Clock clock;
    int score = 0, highscore = 1020, max = 0;



    //setting the frame of the window//
    for (int i = 0; i < H; i++)
    {
        for (int j = 0; j < W; j++)
        {
            if (i == 0 || j == 0 || i == H - 1 || j == W - 1)
            {
                grid[i][j] = 1;

            }
        }
    }
    //initiallizing the velocities and the positions of the enemies//
    for (int i = 0; i < EnemyCount; i++)
    {
        en[i].posX = en[i].posY = 400;
        en[i].delx = 1 - rand() % 8;
        en[i].dely = 3 - rand() % 8;
    }

    while (window.isOpen())
    {

        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer += time;

        Event event;

        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed || (event.type == Event::KeyPressed && Keyboard::isKeyPressed(Keyboard::Escape)))
                window.close();
        }

        //movement speed of the girl///
        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            dx = -1;
            dy = 0;
        }
        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            dx = 1;
            dy = 0;
        }
        if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            dx = 0;
            dy = -1;
        }
        if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            dx = 0;
            dy = 1;
        }

        if (timer > delay)
        {
            x += dx;
            y += dy;
            timer = 0;

            ///collision of the girl to the frame///
            if (x < 0)
            {
                x = 0;
            }

            if (x > W - 1)
            {
                x = W - 1;
            }

            if (y < 0)
            {
                y = 0;
            }

            if (y > H - 1)
            {
                y = H - 1;
            }

            ///so if the girl hits the trail he leaves behind before filling it in it's game over///
            if (grid[y][x] == 2)
            {
                Game = false;
            }

            /// so the girl would leave a trail behind him///law wa2ef 3ala 7eta fadya ye5alyha trail///
            if (grid[y][x] == 0)
            {
                grid[y][x] = 2;
            }

        }


        //calling the move function of the enemies//
        for (int i = 0; i < EnemyCount; i++)
        {
            Move(en[i].posX, en[i].posY, en[i].delx, en[i].dely);
        }
        //making the fill in//


        if (grid[y][x] == 1)
        {
            dx = dy = 0;//if the girl is inside the blue she moves step by step otherwise she runs//
            for (int i = 0; i < EnemyCount; i++)
            {
                fill(en[i].posY / ts, en[i].posX / ts);
            }
            for (int i = 0; i < H; i++)
            {
                for (int j = 0; j < W; j++)
                {
                    if (grid[i][j] == -1)
                    {
                        grid[i][j] = 0;
                    }
                    else
                    {
                        grid[i][j] = 1;

                    }
                }
            }

        }

        //the collision of the enemies with the trail of the girl//
        for (int i = 0; i < EnemyCount; i++)
        {
            if (grid[en[i].posY / ts][en[i].posX / ts] == 2)
            {
                Game = false;
            }
        }


        window.clear();

        for (int i = 0; i < H; i++)
        {
            for (int j = 0; j < W; j++)
            {
                if (grid[i][j] == 1)
                {
                    tiles.setTextureRect(IntRect(70, 0, ts, ts));
                }
                if (grid[i][j] == 2)
                {
                    tiles.setTextureRect(IntRect(0, 0, ts, ts));
                }
                if (grid[i][j] == 0)
                {
                    continue;
                }
                tiles.setPosition(j * ts, i * ts);
                window.draw(tiles);
            }
        }



        girl.setOrigin(40, 30);
        girl.setPosition(x * ts, y * ts);
        window.draw(girl);
        for (int i = 0; i < EnemyCount; i++)
        {
            enemy.setPosition(en[i].posX, en[i].posY);
            window.draw(enemy);
        }
        int temp = 0;
        int score = 0;

        for (int i = 0; i < W; i++)
        {
            for (int j = 0; j < H; j++)
            {
                if (grid[i][j] == 1)
                {
                    temp++;

                }
            }

        }
        score += temp;
        score = score - 88;
        if (score > 100)
        {
            win = false;
        }


        sf::Font font;
        if (!font.loadFromFile("C:/C++/SFML.HOME/UncrackedFreeTrial-X3WjK.otf"))
        {
            cout << "handle error";
        }

        string str;
        sf::Text text;

        text.setFont(font);
        text.setString("score");
        text.setFillColor(Color::Cyan);
        text.setCharacterSize(40);
        text.setPosition(550, 600);
        sf::Text stringaya;
        stringstream ss;
        ss << score;
        ss >> str;
        stringaya.setFont(font);
        stringaya.setString(str);
        stringaya.setFillColor(Color::Cyan);
        stringaya.setCharacterSize(40);
        stringaya.setPosition(610, 601);



        window.draw(text);
        window.draw(stringaya);
        if (!win)
        {
            window.draw(levelone);
        }
        if (!Game)
        {
            window.draw(gameover);
        }

        window.display();

    }

    system("pause");

    return 0;
}