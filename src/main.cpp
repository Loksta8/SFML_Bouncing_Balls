#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <cmath>

std::random_device rd;
std::mt19937 gen(rd());

int generateRand(int aInt) {
    std::uniform_int_distribution<> distrib(0, aInt);
    return distrib(gen);
}

int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML Random Balls Bouncing");
    window.setFramerateLimit(60);

    // Circle Attribute variables
    sf::CircleShape circle;
    std::vector<sf::CircleShape> myCircles;
    std::vector<sf::Vector2f> myCircPos;
    const sf::Color colorArray[6] = { sf::Color::Cyan, sf::Color::Blue, sf::Color::Green, sf::Color::Red, sf::Color::Yellow, sf::Color::White };
    std::vector<float> myXVel;
    std::vector<float> myYVel;
    std::vector<sf::Color> myColor;
    int HOWMANY = 30;
    int edgeR = 1920;
    int edgeL = 0;
    int edgeT = 0;
    int edgeB = 1080;
    int diameter = 20;
    float radius = diameter / 2.0f;

    // Circle Attributes Added to vector
    for (int i = 0; i < HOWMANY; i++) {
        int myRanNum = generateRand(5);
        int myRanXVel = generateRand(6) + 1; // Ensure velocity is not 0
        int myRanYVel = generateRand(6) + 1; // Ensure velocity is not 0
        int myXRand = generateRand(edgeR - diameter) + radius; // Avoid spawning on edges
        int myYRand = generateRand(edgeB - diameter) + radius; // Avoid spawning on edges

        sf::Vector2f circPos(myXRand, myYRand);
        myCircPos.push_back(circPos);
        myCircles.push_back(circle);
        myXVel.push_back(myRanXVel);
        myYVel.push_back(myRanYVel);
        myColor.push_back(colorArray[myRanNum]);
        myCircles[i].setRadius(radius); // Set radius ONCE
        myCircles[i].setOrigin(radius, radius); //Set the origin to the center
    }

    // Start the game loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }

        // Clear screen
        window.clear();

        // Physics and rendering
        for (int i = 0; i < myCircles.size(); i++) {
            // Wall collision handling
            if (myCircPos[i].x < edgeL + radius) {
                myCircPos[i].x = edgeL + radius;
                myXVel[i] *= -1.f;
            }
            if (myCircPos[i].x > edgeR - radius) {
                myCircPos[i].x = edgeR - radius;
                myXVel[i] *= -1.f;
            }
            if (myCircPos[i].y < edgeT + radius) {
                myCircPos[i].y = edgeT + radius;
                myYVel[i] *= -1.f;
            }
            if (myCircPos[i].y > edgeB - radius) {
                myCircPos[i].y = edgeB - radius;
                myYVel[i] *= -1.f;
            }

            // Collision detection and resolution
            for (int j = i + 1; j < myCircles.size(); j++) {
                sf::Vector2f collisionNormal = myCircPos[j] - myCircPos[i];
                float distance = std::sqrt(collisionNormal.x * collisionNormal.x + collisionNormal.y * collisionNormal.y);

                if (distance < diameter) {
                    collisionNormal /= distance;

                    sf::Vector2f relativeVelocity = sf::Vector2f(myXVel[i], myYVel[i]) - sf::Vector2f(myXVel[j], myYVel[j]);
                    float impulse = 2.0f * (relativeVelocity.x * collisionNormal.x + relativeVelocity.y * collisionNormal.y) / (1 + 1);

                    myXVel[i] -= impulse * collisionNormal.x;
                    myYVel[i] -= impulse * collisionNormal.y;
                    myXVel[j] += impulse * collisionNormal.x;
                    myYVel[j] += impulse * collisionNormal.y;

                    myCircPos[i] -= collisionNormal * ((diameter - distance) / 2);
                    myCircPos[j] += collisionNormal * ((diameter - distance) / 2);
                }
            }

            myCircPos[i].x += myXVel[i];
            myCircPos[i].y += myYVel[i];
            myCircles[i].setPosition(myCircPos[i]);
            myCircles[i].setFillColor(myColor[i]);
            window.draw(myCircles[i]);
        }

        window.display();
    }

    return EXIT_SUCCESS;
}