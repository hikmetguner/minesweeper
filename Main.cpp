#include "Table.h"
#include "embedded.h"
#include "Button.h"
#include "User.h"

using namespace sf;

int main()
{
    //TEXTURE SIZE
    const int width = 32;

    //User
    User userData;

    //Table
    Table* table = nullptr;

    //Table properties
    int row = 10;
    int col = 10;
    int BOMB = 10;
    int space_h = 128;
    int space_w = 64;
    int difficulty = 0;

    int screenWidth = 640;
    int screenHeigth = 460;

    bool lose = false;
    bool firstMove = true;
    bool init = true;
    bool game = false;

    //SFML Declerations
    Texture t;
    Texture t2;
    Font f;
    RenderWindow popup;
    String widthStr;
    String heigthStr;
    String bombStr;

    //Load from memory
    t.loadFromMemory(tiles, sizeof(tiles));
    t2.loadFromMemory(timer, sizeof(timer));
    f.loadFromMemory(consola, sizeof(consola));
    userData.load();

    //Sprites
    Sprite tile(t);
    Sprite timer(t2);


    //Init first window
    RenderWindow gameWindow(VideoMode(screenWidth, screenHeigth), "Minesweeper");
    //Debug Window
    RenderWindow debugWindow;

    //Create buttons
    Button easy(20, 120, 200, 80, f, Color::Green);
    Button medium(20, 240, 200, 80, f, Color::Color(0, 204, 255));
    Button hard(20, 360, 200, 80, f, Color::Red);


    //CUSTOM
    Button custom(420, 360, 180, 80, f, Color::Color(105,105,105));

    Button widthInput(340, 280, 60, 40, f);
    Button heigthInput(440, 280, 60, 40, f);
    Button bombInput(540, 280, 60, 40, f);

    widthInput.release();
    heigthInput.release();
    bombInput.release();

    //Popup
    Button popupButton(0, 0, 300, 150, f, Color::Yellow);
    Button timePrompt(0, 150, 300, 70, f, Color::Cyan);

    //Button text
    easy.setText("Easy");
    medium.setText("Medium");
    hard.setText("Hard");
    custom.setText("Custom");

    //Title
    Button title(20,20,600,80,f, Color::Color(192, 192, 192));
    title.setText("Minesweeper");

    //User stuff
    Button user(450, 130, 160, 90, f, Color::Yellow);
    Button ezWR(290, 130, 160, 30, f, Color::Green);
    Button medWR(290, 160, 160, 30, f, Color::Color(0, 204, 255));
    Button hardWR(290, 190, 160, 30, f, Color::Red);

    //User stuff text
    user.setText(userData.userName,20);
    ezWR.setText(userData.getEzWR(),20);
    medWR.setText(userData.getMedWR(),20);
    hardWR.setText(userData.getHardWR(),20);

    //Text over input fields
    Text widthInputLabel("Width", f, 18);
    widthInputLabel.setPosition(345, 250);
    widthInputLabel.setFillColor(Color::Black);
    Text heigthInputLabel("Heigth", f, 18);
    heigthInputLabel.setPosition(440, 250);
    heigthInputLabel.setFillColor(Color::Black);
    Text bombInputLabel("Bomb", f, 18);
    bombInputLabel.setPosition(550, 250);
    bombInputLabel.setFillColor(Color::Black);

    //60 fps babeeee
    gameWindow.setFramerateLimit(60);

    while (gameWindow.isOpen()) {

        //Update User info
        user.setText(userData.userName, 24);
        ezWR.setText(userData.getEzWR(), 24);
        medWR.setText(userData.getMedWR(), 24);
        hardWR.setText(userData.getHardWR(), 24);

        //Mouse
        Vector2i mouse = Mouse::getPosition(gameWindow);

        //Clear
        gameWindow.clear(Color::Color(192, 192, 192));

        //Title
        title.draw(gameWindow);

        //User
        user.draw(gameWindow);
        ezWR.draw(gameWindow);
        medWR.draw(gameWindow);
        hardWR.draw(gameWindow);

        //Buttons
        easy.draw(gameWindow);
        medium.draw(gameWindow);
        hard.draw(gameWindow);
        custom.draw(gameWindow);
        heigthInput.draw(gameWindow);
        widthInput.draw(gameWindow);
        bombInput.draw(gameWindow);


        //Text
        gameWindow.draw(widthInputLabel);
        gameWindow.draw(heigthInputLabel);
        gameWindow.draw(bombInputLabel);

        //Event handler
        Event event;
        while (gameWindow.pollEvent(event))
        {

            if (event.type == Event::Closed)
                gameWindow.close();

            if (event.type == Event::MouseButtonPressed) {
                if (event.key.code == Mouse::Left) {
                    if (easy.isClicked(mouse.x, mouse.y)) {
                        easy.release();
                    }
                    if (medium.isClicked(mouse.x, mouse.y)) {
                        medium.release();
                    }
                    if (hard.isClicked(mouse.x, mouse.y)) {
                        hard.release();
                    }
                    if (custom.isClicked(mouse.x, mouse.y)) {
                        custom.release();
                    }
                    if (user.isClicked(mouse.x, mouse.y)) {
                        user.release();
                    }

                    widthInput.release();
                    heigthInput.release();
                    bombInput.release();

                    if (widthInput.isClicked(mouse.x, mouse.y) && !widthInput.toggled)
                        widthInput.toggle();
                    if (heigthInput.isClicked(mouse.x, mouse.y) && !heigthInput.toggled)
                        heigthInput.toggle();
                    if (bombInput.isClicked(mouse.x, mouse.y) && !bombInput.toggled)
                        bombInput.toggle();
                }
            }

            if (event.type == Event::MouseButtonReleased) {

                easy.toggle();
                medium.toggle();
                hard.toggle();
                custom.toggle();
                user.toggle();

                if (event.key.code == Mouse::Left) {
                    if (easy.isClicked(mouse.x, mouse.y)) {
                        row = 8;
                        col = 8;
                        BOMB = 10;
                        game = true;
                        difficulty = 1;
                    }
                    if (medium.isClicked(mouse.x, mouse.y)) {
                        row = 16;
                        col = 16;
                        BOMB = 40;
                        game = true;
                        difficulty = 2;
                    }
                    if (hard.isClicked(mouse.x, mouse.y)) {
                        row = 16;
                        col = 30;
                        BOMB = 99;
                        game = true;
                        difficulty = 3;
                    }
                    if (custom.isClicked(mouse.x, mouse.y)) {
                        row = atoi(heigthStr.toAnsiString().c_str());
                        col = atoi(widthStr.toAnsiString().c_str());
                        BOMB = atoi(bombStr.toAnsiString().c_str());
                        if (row < 7 || col < 7 || row * col < BOMB) {
                            popup.create(VideoMode(300, 150), "Error");
                            popupButton.setText("Custom arguments not valid", 18);
                            popupButton.button.setFillColor(Color::Red);
                            while (popup.isOpen()) {
                                popup.clear(Color::White);
                                popupButton.draw(popup);
                                Event popevent;
                                while (popup.pollEvent(popevent)) {
                                    if (popevent.type == Event::Closed) {
                                        popup.close();
                                        game = false;
                                        break;
                                    }
                                }
                                popup.display();
                            }
                            popupButton.button.setFillColor(Color::Black);
                        }
                        else game = true;
                    }
                    if (user.isClicked(mouse.x,mouse.y)) {

                        popup.create(VideoMode(300, 160), "User Settings");
                        popup.setFramerateLimit(15);

                        String userNameVar = userData.userName;

                        Button userNameInput(2, 2, 296, 98, f);
                        userNameInput.setText(userNameVar,20);
                        userNameInput.release();

                        Button reset(2, 102, 148, 56, f, Color::Red);
                        reset.setText("Reset", 18);
                        Button save(152, 102, 146, 56, f, Color::Yellow);
                        save.setText("Save", 18);
                        Event popevent;
                        while (popup.isOpen()) {
                            Vector2i popmouse = Mouse::getPosition(popup);
                            
                            while (popup.pollEvent(popevent)) {
                                if (popevent.type == Event::Closed) {
                                    popup.close();
                                    userData.userName = userNameVar;
                                    break;
                                }
                                if (popevent.type == Event::MouseButtonPressed) {
                                    std::cout << "click \n";
                                    userNameInput.release();
                                    if (userNameInput.isClicked(popmouse.x, popmouse.y)) userNameInput.toggle();
                                    if (reset.isClicked(popmouse.x, popmouse.y)) reset.release();
                                    if (save.isClicked(popmouse.x, popmouse.y)) save.release();
                                }
                                if (popevent.type == Event::MouseButtonReleased) {
                                    reset.toggle();
                                    save.toggle();
                                    if (reset.isClicked(popmouse.x, popmouse.y)) {
                                        userData.reset();
                                        popup.close();
                                    };
                                    if (save.isClicked(popmouse.x, popmouse.y)) {
                                        userData.userName = userNameVar;
                                        userData.save();
                                        popup.close();
                                    };
                                }
                                if (popevent.type == Event::TextEntered) {
                                    std::cout << popevent.text.unicode << std::endl;
                                    if (popevent.text.unicode == '\b') {
                                        std::cout << "DELETE" << std::endl;
                                        if (userNameInput.toggled && userNameVar.getSize() > 0) {
                                            userNameVar.erase(userNameVar.getSize() - 1);
                                            userNameInput.setText(userNameVar,20);
                                        }
                                    }
                                    else {
                                        std::cout << "OTHER" << std::endl;
                                        if (userNameInput.toggled && isprint(popevent.text.unicode) && userNameVar.getSize() < 10) {
                                            userNameVar += popevent.text.unicode;
                                            userNameInput.setText(userNameVar,20);
                                        }
                                    }
                                }
                            }
                            popup.clear(Color::Color(192, 192, 192));
                            userNameInput.draw(popup);
                            reset.draw(popup);
                            save.draw(popup);
                            popup.display();

                        }
                    }
                }
            }

            //TEXT INPUT
            if (event.type == Event::TextEntered) {

                //BACKSPACE
                if (event.text.unicode == '\b') {
                    if (widthInput.toggled && widthStr.getSize() > 0) {
                        widthStr.erase(widthStr.getSize()-1);
                        widthInput.setText(widthStr, 18);
                    }
                    if (heigthInput.toggled && widthStr.getSize() > 0) {
                        heigthStr.erase(heigthStr.getSize()-1);
                        heigthInput.setText(heigthStr, 18);
                    }
                    if (bombInput.toggled && bombStr.getSize() > 0) {
                        bombStr.erase(bombStr.getSize() - 1);
                        bombInput.setText(bombStr, 18);
                    }
                }
                //OTHER CHAR
                else {
                    if (widthInput.toggled && isprint(event.text.unicode) && widthStr.getSize() < 2 
                        && event.text.unicode >= '0' && event.text.unicode <= '9') {
                        widthStr += event.text.unicode;
                        widthInput.setText(widthStr, 18);
                    }
                    if (heigthInput.toggled && isprint(event.text.unicode) && heigthStr.getSize() < 2
                        && event.text.unicode >= '0' && event.text.unicode <= '9') {
                        heigthStr += event.text.unicode;
                        heigthInput.setText(heigthStr, 18);
                    }
                    if (bombInput.toggled && isprint(event.text.unicode) && bombStr.getSize() < 2
                        && event.text.unicode >= '0' && event.text.unicode <= '9') {
                        bombStr += event.text.unicode;
                        bombInput.setText(bombStr, 18);
                    }
                }
            }
        };

        //CLOCK DEBUG

        
        //Za game window

        if (game) {
            screenHeigth = (space_h + space_w) + (width * row);
            screenWidth = (space_w * 2) + (width * col);
            
            gameWindow.create(VideoMode(screenWidth, screenHeigth), "Minesweeper");
            gameWindow.setFramerateLimit(60);

            //DEBUG WINDOW
            debugWindow.create(VideoMode(screenWidth, screenHeigth), "Debug");
            debugWindow.setFramerateLimit(60);

        }
        //Initialize the table and start the game
        Clock clock;
        int toggledLoc;
        int debugCount = 0;
        while (gameWindow.isOpen() && game)
        {

            timePrompt.setText("Time: " + std::to_string((int)floor(clock.getElapsedTime().asSeconds())) + " Seconds", 18);
            //init condition
            if (init) {
                table = new Table(row, col);
                init = false;
            }




            //CLOCK DEBUG
            //std::cout << "In game loop " << clock.getElapsedTime().asSeconds() << std::endl;

            //Win condition
            if (table->win() && !firstMove) {
                switch (difficulty) {
                case 1:
                    userData.ezTotal++;
                    userData.ezWin++;
                    break;
                case 2:
                    userData.medTotal++;
                    userData.medWin++;
                    break;
                case 3:
                    userData.hardTotal++;
                    userData.hardWin++;
                }
                popup.create(VideoMode(300, 220), "You won");

                popupButton.setText("You won!", 60);
                popup.setFramerateLimit(10);

                while (popup.isOpen()) {
                    popup.clear(Color::White);
                    popupButton.draw(popup);
                    timePrompt.draw(popup);
                    Event popevent;
                    while (popup.pollEvent(popevent)) {
                        if (popevent.type == Event::Closed) {
                            popup.close();
                            game = false;
                            break;
                        }
                    }
                    popup.display();
                }
            }

            //lose condition
            if (lose) {
                switch (difficulty) {
                case 1:
                    userData.ezTotal++;
                    break;
                case 2:
                    userData.medTotal++;
                    break;
                case 3:
                    userData.hardTotal++;
                }
                popup.create(VideoMode(300, 220), "You lost");
                popupButton.setText("You lost", 60);
                popupButton.button.setFillColor(Color::Red);
                popup.setFramerateLimit(10);

                while (popup.isOpen()) {
                    popup.clear(Color::White);
                    popupButton.draw(popup);
                    timePrompt.draw(popup);
                    Event popevent;
                    while (popup.pollEvent(popevent)) {
                        if (popevent.type == Event::Closed) {
                            popup.close();
                            game = false;
                            break;
                        }
                    }
                    popup.display();
                }
            }

            //Mouse stuff
            mouse = Mouse::getPosition(gameWindow);
            
            int x = ceil(mouse.x / width) - 2;
            int y = ceil(mouse.y / width) - 4;



            if (firstMove)  clock.restart();

            //Window close
            while (gameWindow.pollEvent(event))
            {
                if (event.type == Event::Closed) {
                    gameWindow.close();
                    return 0;
                }
                

                //TODO Release or ->Press<-
                if (event.type == Event::MouseButtonPressed) {
                    if (event.key.code == Mouse::Right) {
                        //mouse debug
                        std::cout << mouse.x << " " << mouse.y << " -- " << x << " " << y << std::endl;
                        if (!firstMove) table->flag(x, y);
                    }
                    if (event.key.code == Mouse::Left) {
                        toggledLoc = y * col + x;
                        if (table->currentTiles[toggledLoc] == 11) table->currentTiles[toggledLoc] = 9;
                    }
                }
                if (event.type == Event::MouseButtonReleased) {
                    if (event.key.code == Mouse::Left) {

                        //TABLE DEBUG
                        std::cout << "-----------------------------------------" << debugCount++ << std::endl;
                        table->print();
                        std::cout << std::endl;

                        int loc = y * col + x;
                        if (toggledLoc != loc) {
                            table->currentTiles[toggledLoc] = 11;
                            continue;
                        };
                        std::cout << toggledLoc << "-" << loc << std::endl;
                        if (event.key.code == Mouse::Left) {
                            //first move
                            if (firstMove) {
                                table->createBombs(BOMB, loc);
                                table->fillNumberTiles();
                                firstMove = false;
                            }
                            //table->print();
                            if (!table->open(x, y)) {
                                table->currentTiles[y * col + x] = 13;
                                lose = true;
                                break;
                            }
                        }
                    }
                }
            }

            //RENDER SCREEN
            gameWindow.clear(Color::White);

            //ADJUST TIME
            std::string s;
            Uint16 time = clock.getElapsedTime().asSeconds();

            if (time / 10 < 1)
                s += '0';
            if (time / 100 < 1)
                s += '0';
            s += std::to_string(time);

            //Time debug
            //std::cout << "Game time " << time << std::endl;

            //Draw timer
            for (int i = 0; i < 3; i++) {
                //std::cout << s[i] - '0' << std::endl;
                timer.setTextureRect(IntRect((s[i] - '0') * width, 0, width, width));
                timer.setPosition(space_w + i*width, space_h - width * 2);
                gameWindow.draw(timer);
            }

            //Draw Remaining Flags
            tile.setTextureRect(IntRect(12 * width, 0, width, width));
            tile.setPosition(space_w + ((table->col - 1) * width), space_h - width * 2);
            gameWindow.draw(tile);
            timer.setTextureRect(IntRect(((BOMB - table->currentFlag) / 100)* width, 0, width, width));
            timer.setPosition(space_w + ((table->col - 4) * width), space_h - width * 2);
            gameWindow.draw(timer);
            timer.setTextureRect(IntRect(((BOMB - table->currentFlag) / 10)* width, 0, width, width));
            timer.setPosition(space_w + ((table->col - 3) * width), space_h - width * 2);
            gameWindow.draw(timer);
            timer.setTextureRect(IntRect(((BOMB - table->currentFlag) % 10)* width, 0, width, width));
            timer.setPosition(space_w + ((table->col - 2) * width), space_h - width * 2);
            gameWindow.draw(timer);

            //Draw table
            for (int i = 0; i < row; i++)
                for (int j = 0; j < col; j++) {

                    tile.setTextureRect(IntRect(table->currentTiles[i * col + j] * width, 0, width, width));
                    tile.setPosition(space_w - width + (j + 1) * width, space_h - width + (i + 1) * width);
                    gameWindow.draw(tile);

                    //DEBUG
                    tile.setTextureRect(IntRect(table->hiddenTiles[i * col + j] * width, 0, width, width));
                    debugWindow.draw(tile);

                }
            gameWindow.display();

            //DEBUG
            debugWindow.display();
        }
        if (!init) {
            screenWidth = 640;
            screenHeigth = 460;

            lose = false;
            firstMove = true;
            init = true;

            widthStr.clear();
            heigthStr.clear();
            bombStr.clear();

            gameWindow.create(VideoMode(screenWidth,screenHeigth),"Minesweeper");
        }
        gameWindow.display();
    }
    return 0;
}