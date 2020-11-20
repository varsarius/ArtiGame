#include <stdlib.h>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

const int mapWidth = 100;///Нужно сделать:
const int mapHeight = 100;// Подобрать размеры перса в пикселях и изначально рисовать столько пикселей, сколько нужно и не подбирать в программе масштаб
int cletca = 50;//Подобрать анимацию на перса Артёма(хотя ещё не все спрайты пришли)
int WindowHeight = 768;// Показать, как делается карта и сделать такую
int WindowWidth = 1024;// Сделать уже более-менее презентабильный вид меню
int map[mapWidth][mapHeight]; // Добавить врагов и логику взаимодействия с ними

class Player{
public:
  float x, y, dx, dy, speed, frame = 0;
  int dir;
  std::string File;
  sf::Image image;
  sf::Texture texture;
  sf::Sprite sprite;
  sf::SoundBuffer buffer;
  sf::Sound sound;
  Player(std::string F,std::string S, int X, int Y, int DX, int DY){
    File = F;
    image.loadFromFile(File);
    image.createMaskFromColor(sf::Color(255,255,255));
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0,0,32,48));
    sprite.scale(2,2);
    buffer.loadFromFile("no-1.wav");
    sound.setBuffer(buffer);
    x = X;
    y = Y;
    dx = DX;
    dy = DY;
  }
  void chdir(int DIR, float SPEED){
    dir = DIR;
    speed = SPEED;
  }
  void update(float time){
    switch (dir){
      case 0:
        dx = speed;
        dy = 0;
        frame += 0.05 * time;
        if(frame > 4) frame = 0;
        sprite.setTextureRect(sf::IntRect(32*int(frame), 96, 32, 48));
      break;
      case 1:
        dx = -speed;
        dy = 0;
        frame += 0.05 * time;
        if(frame > 4) frame = 0;
        sprite.setTextureRect(sf::IntRect(32*int(frame), 48, 32, 48));
      break;
      case 2:
        dx = 0;
        dy = speed;
        frame += 0.05 * time;
        if(frame > 4) frame = 0;
        sprite.setTextureRect(sf::IntRect(32*int(frame), 0, 32, 48));
      break;
      case 3:
        dx = 0;
        dy = -speed;
        frame += 0.05 * time;
        if(frame > 4) frame = 0;
        sprite.setTextureRect(sf::IntRect(32*int(frame), 144, 32, 48));
      break;
      case 4:
        dx = -speed;
        dy = -speed;
      break;
      case 5: dx = speed; dy = -speed; break;
      case 6: dx = -speed; dy = speed; break;
      case 7: dx = speed; dy = speed; break;

      case -1:
        dx = 0;
        dy = 0;
        frame += 0.05 * time;
        if(frame > 2) frame = 0;
        sprite.setTextureRect(sf::IntRect(0, 28*int(frame), 28, 28));
      break;
    }

    x += dx*time;
    y += dy*time;

    //**** Столкновение с черным квадратом
    for(int i = 0;i<mapHeight;i++){
      for(int j = 0;j<mapWidth;j++){
        if (map[i][j] == 1){
          if(sf::IntRect(x, y, cletca, cletca).intersects(sf::IntRect(j*cletca, i*cletca, cletca, cletca))){//Если столкновение произошло, то отодвигаем перса обратно, когда он не успел наприсоваться
                x -= dx*time;
                y -= dy*time;
            }
          }
        }
      }




    speed = 0;
    sprite.setPosition(x,y);
   }
};

Player hero("hero.png", "no-1.wav", 20, 20, 0, 0);


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

   sf::Texture polTexture;
   polTexture.loadFromFile("pol.png");
   sf::Sprite polSprite(polTexture);// 32, 48

   polSprite.setScale(5, 5);



   sf::RectangleShape rectangle(sf::Vector2f(320.f, 50.f));
   rectangle.setSize(sf::Vector2f(cletca, cletca));

   sf::Music music;
    if (!music.openFromFile("music.ogg"))
        return -1; // error
    music.play();
    music.setLoop(true);
    music.setVolume(40);

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
       }



       if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
       {
         menu(window);
         window.setView(view);
       }

       if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))){
         hero.chdir(4,0.707);
       }else
       if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))){
         hero.chdir(5,0.707);
       }else
       if((sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))){
         hero.chdir(6,0.707);
       }else
       if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) && (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))){
         hero.chdir(7,0.707);
       }else
       if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
       {
         hero.chdir(1,1);
       }else
       if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
       {
         hero.chdir(0,1);
       }else
       if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
       {
         hero.chdir(3,1);
       }else
       if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
       {
         hero.chdir(2,1);
       } else hero.chdir(-1,0);
       hero.update(time);



//**************ПОСТАНОВКА КАМЕРЫ**********************
       int viewx = hero.x+cletca/2;
       int viewy = hero.y+cletca/2;
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
       window.draw(hero.sprite);
//************

       window.display();
   }

   return 0;
}
