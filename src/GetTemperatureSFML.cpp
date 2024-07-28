#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <chrono>

using namespace std;

class Data {
private:
    float GPUtemperature;
    float CPUtemperature;

public:
    float getGPUTemperature() {
        ifstream file("/sys/class/drm/card0/device/hwmon/hwmon0/temp1_input");
        if (!file.is_open()) {
            cout << "Error: Unable to open GPU temperature file. Maybe, your GPU is not AMD.\n";
            return -1;
        }

        float temperature;
        file >> temperature;
        file.close();

        return temperature / 1000.0;
    }

    float getCPUTemperature() {
        ifstream file("/sys/class/thermal/thermal_zone0/temp");
        if (!file.is_open()) {
            cerr << "Error: Unable to open CPU temperature file.\n";
            return -1;
        }

        float temperature;
        file >> temperature;
        file.close();

        return temperature / 1000.0;
    }

    void setCPUTemperature(float valueTemperature) {
        CPUtemperature = valueTemperature;
    }

    void setGPUTemperature(float valueTemperature) {
        GPUtemperature = valueTemperature;
    }

    float getCPUTemperatureValue() {
        return CPUtemperature;
    }

    float getGPUTemperatureValue() {
        return GPUtemperature;
    }
};

sf::Color getTemperatureColor(float temperature) {
    int red = min(255, static_cast<int>((temperature / 100.0) * 255));
    int green = max(0, 255 - red);
    return sf::Color(red, green, 0);
}

void drawTemperatureText(sf::RenderWindow& window, const string& label, float temperature, float x, float y, sf::Font& font) {
    sf::Text text;
    text.setFont(font);
    text.setString(label + ": " + to_string(static_cast<int>(temperature)) + " C");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(x, y);
    window.draw(text);
}

int main() {
    Data data;
    sf::RenderWindow window(sf::VideoMode(400, 300), "Temperature Monitor");

    sf::RectangleShape cpuRect(sf::Vector2f(200, 50));
    sf::RectangleShape gpuRect(sf::Vector2f(200, 50));
    cpuRect.setPosition(100, 50);
    gpuRect.setPosition(100, 150);

    sf::Font font;
    if (!font.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf")) {
        cerr << "Error loading font\n";
        return -1;
    }

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (clock.getElapsedTime().asSeconds() >= 1.0f) {
            data.setCPUTemperature(data.getCPUTemperature());
            data.setGPUTemperature(data.getGPUTemperature());
            clock.restart();
        }

        float cpuTemp = data.getCPUTemperatureValue();
        float gpuTemp = data.getGPUTemperatureValue();

        cpuRect.setFillColor(getTemperatureColor(cpuTemp));
        gpuRect.setFillColor(getTemperatureColor(gpuTemp));

        window.clear(sf::Color::Black);

        window.draw(cpuRect);
        window.draw(gpuRect);

        drawTemperatureText(window, "CPU", cpuTemp, 120, 60, font);
        drawTemperatureText(window, "GPU", gpuTemp, 120, 160, font);

        window.display();
    }

    return 0;
}
