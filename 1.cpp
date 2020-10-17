#include <stdlib.h>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

const int mapWidth = 100;
const int mapHeight = 100;
int cletca = 50;
int WindowHeight = 768;
int WindowWidth = 1024;
int map[mapWidth][mapHeight];

float x = 20;
float y = 20;
float speed = 1;
float dx = 0;
float dy = 0;


void menu(sf::RenderWindow & window) {
  window.setView(window.getDefaultView());

  sf::Texture menuTexture1, menuTexture2, menuTexture3;
  menuTexture1.loadFromFile("pol.png");
  menuTexture2.loadFromFile("pol.png");
  sf::Sprite menu1(menuTexture1), menu2(menuTexture2);
  bool isMenu = 1;
  int menuNum = 0;
  menu1.setPosition(100,30);
  menu2.setPosition(100,60);
  while (isMenu)
  {
    window.clear(sf::Color(129, 181, 221));
    menu1.setColor(sf::Color::White);
    menu2.setColor(sf::Color::White);

    menuNum = 0;

    if (sf::IntRect(100,30,300,50).contains(sf::Mouse::getPosition(window))) { menu1.setColor(sf::Color::Blue); menuNum = 1; }
    if (sf::IntRect(100,60,300,80).contains(sf::Mouse::getPosition(window))) { menu2.setColor(sf::Color::Blue); menuNum = 2; }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
      if (menuNum == 1) {isMenu = false;}
      if (menuNum == 2) {window.close(); isMenu = false; }
    }
    window.draw(menu1);
    window.draw(menu2);
    window.display();
  }
}


float heroPlayerFrame = 0;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WindowWidth, WindowHeight), "SFML works!");
    menu(window);
    srand(time(NULL));


    for(int i = 0;i<mapHeight;i++){
      for(int j = 0;j<mapWidth;j++){
        int randa = rand() % 100+1;
        if ((randa > 5) && (randa <= 10)){
          map[i][j] = 2;
        } else if (randa <= 5){
          map[i][j] = 1;
        } else{
          map[i][j] = 0;
        }
      }
    }

   sf::View view(sf::FloatRect(0.f, 0.f, WindowWidth, WindowHeight));

   sf::Texture polTexture, heroPlayerTexture;
   polTexture.loadFromFile("pol.png");
   heroPlayerTexture.loadFromFile("ironman.png");
   sf::Sprite polSprite(polTexture), heroPlayerSptite(heroPlayerTexture);// 32, 48
   heroPlayerSptite.setTextureRect(sf::IntRect(0,0,32,48));

   polSprite.setScale(5, 5);
   heroPlayerSptite.setScale(1.5,1.5);




   sf::RectangleShape rectangle(sf::Vector2f(320.f, 50.f));
   rectangle.setSize(sf::Vector2f(cletca, cletca));

   sf::Music music;
    if (!music.openFromFile("music.ogg"))
        return -1; // error
    music.play();
    music.setLoop(true);
    music.setVolume(80);

    sf::SoundBuffer buffer;
    buffer.loadFromFile("no-1.wav");

    sf::Sound sound;
    sound.setBuffer(buffer);


    sf::Clock clock;

   while (window.isOpen())
   {
       window.setView(view);
       float time = clock.getElapsedTime().asMicroseconds();
       clock.restart();
       time = time/10000;

       sf::Event event;
       while (window.pollEvent(event))
       {
           if (event.type == sf::Event::Closed)
               window.close();

           if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
           {
             menu(window);
             window.setView(view);
           }

           if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
           {
             //**************проверка врезания в чёрный квадрат
              for(int i = y / cletca; i< (y+cletca)/cletca;i++){
                for(int j = x / cletca; j< (x+cletca)/cletca; j++){
                  if (map[i][j] == 1){
                    x = j*cletca+cletca+speed*time;
                    sound.play();
                  }
                }
              }

             dx=-speed*time;
             dy = 0;
             heroPlayerFrame += 0.05 * time;
             if(heroPlayerFrame > 4) heroPlayerFrame = 0;
             heroPlayerSptite.setTextureRect(sf::IntRect(32*int(heroPlayerFrame), 48, 32, 48));
           }
           else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
           {

             //**************проверка врезания в чёрный квадрат
              for(int i = y / cletca; i< (y+cletca)/cletca;i++){
                for(int j = x / cletca; j< (x+cletca)/cletca; j++){
                  if (map[i][j] == 1){
                    x = j*cletca-cletca-speed*time;
                    sound.play();
                  }
                }
              }

             dx=speed*time;
             dy = 0;
             heroPlayerFrame += 0.05 * time;
             if(heroPlayerFrame > 4) heroPlayerFrame = 0;
             heroPlayerSptite.setTextureRect(sf::IntRect(32*int(heroPlayerFrame), 96, 32, 48));
           }
           else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
           {
             //**************проверка врезания в чёрный квадрат
              for(int i = y / cletca; i< (y+cletca)/cletca;i++){
                for(int j = x / cletca; j< (x+cletca)/cletca; j++){
                  if (map[i][j] == 1){
                    y = i*cletca+cletca+speed*time;
                    sound.play();
                  }
                }
              }

             dy=-speed*time;
             dx = 0;
             heroPlayerFrame += 0.05 * time;
             if(heroPlayerFrame > 4) heroPlayerFrame = 0;
             heroPlayerSptite.setTextureRect(sf::IntRect(32*int(heroPlayerFrame), 144, 32, 48));
           }
           else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
           {
             //**************проверка врезания в чёрный квадрат
              for(int i = y / cletca; i< (y+cletca)/cletca;i++){
                for(int j = x / cletca; j< (x+cletca)/cletca; j++){
                  if (map[i][j] == 1){
                    y = i*cletca-cletca-speed*time;
                    sound.play();
                  }
                }
              }

             dy=speed*time;
             dx = 0;
             heroPlayerFrame += 0.05 * time;
             if(heroPlayerFrame > 4) heroPlayerFrame = 0;
             heroPlayerSptite.setTextureRect(sf::IntRect(32*int(heroPlayerFrame), 0, 32, 48));
           }
           else {
             dx = 0;
             dy = 0;
           }
       }

       x+=dx;
       y+=dy;

       int viewx = x+cletca/2;
       int viewy = y+cletca/2;
       if (viewx <=  WindowWidth/2){
         viewx = WindowWidth/2;
       }
       if (viewx >=  cletca*mapWidth-WindowWidth/2){
         viewx = cletca*mapWidth-WindowWidth/2;
       }
       if (viewy <=  WindowHeight/2){
         viewy = WindowHeight/2;
       }
       if (viewy >=  cletca*mapHeight-WindowHeight/2){
         viewy = cletca*mapHeight-WindowHeight/2;
       }
       view.setCenter(viewx, viewy);






       window.clear();


       //***************ОТРИСОВКА КАРТЫ**************
       for(int i = 0;i<mapHeight;i++){
         for(int j = 0;j<mapWidth;j++){
           if (map[i][j] == 1) rectangle.setFillColor(sf::Color(30,30,30));
           if (map[i][j] == 2) rectangle.setFillColor(sf::Color(255,255,0));
           rectangle.setPosition(sf::Vector2f(cletca*j, cletca*i));
           window.draw(rectangle);
           if (map[i][j] == 0) {
             polSprite.setPosition(sf::Vector2f(cletca*j, cletca*i));
             window.draw(polSprite);
           };
         }
       }

//************** ДЛЯ ГЕРОЯ
       heroPlayerSptite.setPosition(sf::Vector2f(x, y));
       window.draw(heroPlayerSptite);
//************

       window.display();
   }

   return 0;
}
