#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>
#include <vector>
#include <ctime> // Include this for srand
#include <cstdlib> // Include this for rand
using namespace std;
using namespace sf;

int main() {
    int catTimer = 40;
    RenderWindow window(VideoMode(800, 600), "Cat Dodge", Style::Default);
    window.setFramerateLimit(60);

    srand(static_cast<unsigned int>(time(NULL))); // Seed the random number generator

    Texture catTex;
    Sprite cat; 
    if (!catTex.loadFromFile("TExture/cat.png")){
        throw "Could not load cat.png"; 
    }

    cat.setTexture(catTex);
    cat.setScale(Vector2f(0.1f, 0.1f));

    vector<Sprite> cats;

    Texture dogTex;
    if (!dogTex.loadFromFile("TExture/dog.png")){
        throw "Could not load dog.png";
    }

    Sprite dog;
    int hp = 10;
    dog.setTexture(dogTex);
    dog.setScale(Vector2f(0.04f, 0.04f));
    dog.setPosition(50.f, window.getSize().y - dog.getGlobalBounds().height);
    RectangleShape hpbar;
    hpbar.setFillColor(Color::Red);
    hpbar.setSize(Vector2f((float)hp * 20.f, 20.f));
    hpbar.setPosition(200.f, 10.f);
    while (window.isOpen() and hp>0) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            if (event.type == Event::KeyPressed and event.key.code == Keyboard::Escape) {
                window.close();
            }
        }
        dog.setPosition(dog.getPosition().x, Mouse::getPosition(window).y);
        if (dog.getPosition().y > window.getSize().y - dog.getGlobalBounds().height) {
            dog.setPosition(dog.getPosition().x, window.getSize().y - dog.getGlobalBounds().height);
        }
        if (dog.getPosition().y < 0) {

            dog.setPosition(dog.getPosition().x,0);
        }
        for (size_t i = 0; i < cats.size(); i++) {
            cats[i].move(-7.f, 0.f);
            if (cats[i].getPosition().x < 0 - cat.getGlobalBounds().width) {
                cats.erase(cats.begin() + i);
            }
        }

        if (catTimer < 40) {
            catTimer++;
        }

        if (catTimer >= 40) {
            cat.setPosition(window.getSize().x, rand() % int(window.getSize().y - cat.getGlobalBounds().height));
            cats.push_back(Sprite(cat));
            catTimer = 0;
        }
        for (size_t i = 0; i < cats.size(); i++) {
            if (dog.getGlobalBounds().intersects(cats[i].getGlobalBounds())) {
                hp--;
                cats.erase(cats.begin() + i);
            }
        }
        hpbar.setSize(Vector2f((float)hp * 20.f, 20.f));
        window.clear();
        window.draw(dog);

        for (size_t i = 0; i < cats.size(); i++) {
            window.draw(cats[i]);
        }
        window.draw(hpbar);
        window.display();
    }

    return 0;
}
