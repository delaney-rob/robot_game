#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <stdlib.h>
using namespace std;

int main()
{
    // Create the main window
    sf::RenderWindow app(sf::VideoMode(1000, 600), "Robot game");
    app.setFramerateLimit(60);

    //Declare textures and sprites and apply textures accordingly, set initial positions and rotations

    //Body
    sf::Texture tBody;
    tBody.loadFromFile("images/robot_body.png");
    tBody.setSmooth(true);
    sf::Sprite sBody;
    sBody.setTexture(tBody);
    sf::Vector2f sBodyPos(75,250);

    //First Part of arm
    sf::Texture tArm1;
    tArm1.loadFromFile("images/robot_arm_1.png");
    tArm1.setSmooth(true);
    sf::Sprite sArm1;
    sArm1.setTexture(tArm1);
    sArm1.setOrigin(30,31);
    //sf::Vector2f sArm1Pos(70,15);
    sf::Vector2f sArm1Pos(133,150);
    float sArm1Rot = 0.0;

    //Second Part of arm
    sf::Texture tArm2;
    tArm2.loadFromFile("images/robot_arm_2.png");
    tArm2.setSmooth(true);
    sf::Sprite sArm2;
    sArm2.setTexture(tArm2);
    sArm2.setOrigin(12,38);
    sf::Vector2f sArm2Pos(200,-1);
    float sArm2Rot = 0.0;

    //First Pincer
    sf::Texture tPincer1;
    tPincer1.loadFromFile("images/robot_pincer.png");
    tPincer1.setSmooth(true);
    sf::Sprite sPincer1;
    sPincer1.setTexture(tPincer1);
    sPincer1.setOrigin(6,6);
    sf::Vector2f sPincer1Pos(198,30);

    //Second Pincer
    sf::Sprite sPincer2;
    sPincer2.setTexture(tPincer1);
    sPincer2.setOrigin(6,6);
    sf::Vector2f sPincer2Pos(198,-25);

    //Point used for collision detection
    sf::Vector2f pincerPoint1 = sf::Vector2f(43,2);

    /* initialize random seed: */
    srand(time(NULL));

    //Balloons
    sf::Texture tBalloon1;
    tBalloon1.loadFromFile("images/robot_rBalloon.png");
    tBalloon1.setSmooth(true);
    sf::Sprite sBalloon1;
    sBalloon1.setTexture(tBalloon1);
    //sBalloon1.setPosition(150,150);
    sBalloon1.setPosition(rand()% 600 + 350, rand() % 500 + 0 );
    bool ballOneHit = false;

    sf::Texture tBalloon2;
    tBalloon2.loadFromFile("images/robot_yBalloon.png");
    tBalloon2.setSmooth(true);
    sf::Sprite sBalloon2;
    sBalloon2.setTexture(tBalloon2);
    //sBalloon2.setPosition(300,200);
    sBalloon2.setPosition(rand()% 600 + 350, rand() % 500 + 0 );
    bool ballTwoHit = false;

    sf::Texture tBalloon3;
    tBalloon3.loadFromFile("images/robot_bBalloon.png");
    tBalloon3.setSmooth(true);
    sf::Sprite sBalloon3;
    sBalloon3.setTexture(tBalloon3);
    //sBalloon3.setPosition(800,450);
    sBalloon3.setPosition(rand()% 600 + 350, rand() % 500 + 0 );
    bool ballThreeHit = false;

    sf::Sprite sBalloon4;
    sBalloon4.setTexture(tBalloon1);
    //sBalloon4.setPosition(600,20);
    sBalloon4.setPosition(rand()% 600 + 350, rand() % 500 + 0 );
    bool ballFourHit = false;

    sf::Sprite sBalloon5;
    sBalloon5.setTexture(tBalloon2);
    //sBalloon5.setPosition(850,0);
    sBalloon5.setPosition(rand()% 600 + 350, rand() % 500 + 0 );
    bool ballFiveHit = false;

    sf::Font font;
    font.loadFromFile("/usr/share/fonts/truetype/droid/DroidSansFallbackFull.ttf");

    sf::Text gOver;
    gOver.setFont(font);
    gOver.setCharacterSize(30);
    gOver.setString("Game Over!");
    gOver.setPosition(430,100);

    sf::Text text;
    text.setFont(font);
    text.setPosition(20,20);
    text.setCharacterSize(20);

    //clock variable for timing and finish variable for end time
    sf::Clock clock;
    string finish = "";

	// Start the game loop
    while (app.isOpen())
    {
        // Process events
        sf::Event Event;
        while (app.pollEvent(Event))
        {
            // Close window : exit
            if (Event.type == sf::Event::Closed)
                app.close();
        }
        ostringstream seconds;
        seconds << clock.getElapsedTime().asSeconds();

        //create a formatted text string

        //If any balloons left keep timer running, else stop timer
        if (ballOneHit==false || ballTwoHit==false || ballThreeHit==false || ballFourHit==false || ballFiveHit==false){
        text.setString(seconds.str() + " seconds.");
        }
        else{
        text.setString(finish);
        }
        finish = text.getString();


        //Check for key presses and adjust position and vectors and rotation accordingly
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
            if (sBodyPos.x >=10){
                sBodyPos -= sf::Vector2f(2,0);
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
            if (sBodyPos.x <=835){
                sBodyPos += sf::Vector2f(2,0);
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
            if (sArm1Rot <=50 ){
                sArm1Rot += 1.0;
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
            if (sArm1Rot >= -60){
                sArm1Rot -= 1.0;
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            if (sArm2Rot <= 130){
                sArm2Rot += 1.0;
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
            if (sArm2Rot >= -115){
                sArm2Rot -= 1.0;
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
            if (sPincer1Pos.y <= 29){
                sPincer1Pos += sf::Vector2f(0,1);
                sPincer2Pos -= sf::Vector2f(0,1);
            }
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
            if (sPincer1Pos.y >= 10){
                sPincer1Pos -= sf::Vector2f(0,1);
                sPincer2Pos += sf::Vector2f(0,1);
            }
        }

        //Transformation Calculations

        //Body
        sf::Transform trBody;
        trBody.translate(sBodyPos);
        /////////////////////////////////////////////////

        //First Part of arm
        sf::Transform trArm1;
        trArm1.translate(sArm1Pos);

        sf::Transform rotArm1;
        rotArm1.rotate(sArm1Rot);

        sf::Transform TR1 = trBody*trArm1*rotArm1;
        /////////////////////////////////////////////////

        //Second Part of Arm
        sf::Transform trArm2;
        trArm2.translate(sArm2Pos);

        sf::Transform rotArm2;
        rotArm2.rotate(sArm2Rot);

        sf::Transform TR2 = TR1*trArm2*rotArm2;
        /////////////////////////////////////////////////

        //First Pincer
        sf::Transform trPincer1;
        trPincer1.translate(sPincer1Pos);

        sf::Transform TR3 = TR2*trPincer1;
        /////////////////////////////////////////////////

        //Second Pincer
        sf::Transform trPincer2;
        trPincer2.translate(sPincer2Pos);

        sf::Transform TR4 = TR2*trPincer2;
        /////////////////////////////////////////////////

        //Points used for collision detection
        sf::Vector2f tp1 = TR3.transformPoint(pincerPoint1);
        sf::Vector2f tp2 = TR4.transformPoint(pincerPoint1);

        // Clear screen
        app.clear();

        //Draw Sprites and text
        app.draw(text);
        app.draw(sArm2, TR2);
        app.draw(sPincer1, TR3);
        app.draw(sPincer2, TR4);
        app.draw(sBody, trBody);
        app.draw(sArm1, TR1);


        if(ballOneHit==true && ballTwoHit==true && ballThreeHit==true && ballFourHit==true && ballFiveHit==true){ app.draw(gOver); }

        //Only draw balloons if not previously been hit
        if (ballOneHit == false){ app.draw(sBalloon1); }

        if (ballTwoHit == false){ app.draw(sBalloon2); }

        if (ballThreeHit == false){ app.draw(sBalloon3); }

        if (ballFourHit == false){ app.draw(sBalloon4); }

        if (ballFiveHit == false){ app.draw(sBalloon5); }

        //Check collisions between pincers and balloons
        if (sBalloon1.getGlobalBounds().contains(tp1) || sBalloon1.getGlobalBounds().contains(tp2)){ ballOneHit = true; }

        if (sBalloon2.getGlobalBounds().contains(tp1) || sBalloon2.getGlobalBounds().contains(tp2)){ ballTwoHit = true; }

        if (sBalloon3.getGlobalBounds().contains(tp1) || sBalloon3.getGlobalBounds().contains(tp2)){ ballThreeHit = true; }

        if (sBalloon4.getGlobalBounds().contains(tp1) || sBalloon4.getGlobalBounds().contains(tp2)){ ballFourHit = true; }

        if (sBalloon5.getGlobalBounds().contains(tp1) || sBalloon5.getGlobalBounds().contains(tp2)){ ballFiveHit = true; }

        // Update the window
        app.display();
    }
    return EXIT_SUCCESS;
}
