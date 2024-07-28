# US
The program allows you to see the temperature of the processor and video card.
This program is compatible with Linux and AMD video cards.

To start, you need to double-click on the "GetTemperature" file. 
In order to place the application on your home screen, you can move 
the "GetTemperature.desktop" file to the screen or edit it by inserting your 
path to "GetTemperature" and "icon.jpg".

For those who want to edit and recompile the code, the following commands can be used:

Installing the required libraries:
```
sudo apt-get install libsfml-dev
```
Compile the program:
```
g++ -o GetTemperature GetTemperatureSFML.cpp -lsfml-graphics -lsfml-window -lsfml-system
```
or
```
make -f Makefile
```

# UKR
Програма дозволяє продивитися температуру процесору та відеокарти.
Програма сумісна з Linux та відеокартами АМД.

Для запуску, потрібно два рази нажати на файл "GetTemperature". 
Для того, щоб розмістити додаток собі на домашній екран, можна 
перемістити на екран файл "GetTemperature.desktop" або редагувати його, 
вставиши свій шлях до  "GetTemperature" та "icon.jpg".

Для тих, хто хоче редагувати та скомпілювати  код заново, можна використати такі команди:

Встановлення необхідних бібліотек:
```
sudo apt-get install libsfml-dev
```
Компіляція програми:
```
g++ -o GetTemperature GetTemperatureSFML.cpp -lsfml-graphics -lsfml-window -lsfml-system
```
або
```
make -f Makefile
```
