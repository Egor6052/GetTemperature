#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Data {
private:
	int GPUtemperature;
	int CPUtemperature;

public:

// Витягання температури з системних файлів;
	
	float getGPUTemperature(){
		ifstream file("/sys/class/drm/card0/device/hwmon/hwmon0/temp1_input");
		if (!file.is_open()) {
			cout << "Error: Unable to open temperature file. Maybe, you GPU is not a AMD.\n" << endl;
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
	        cerr << "Error: Unable to open temperature file.\n" << endl;
	        return -1;
	    }

	    float temperature;
	    file >> temperature;
	    file.close();

	    // Температура зазвичай записується в тисячах градусів Цельсія
	    return temperature / 1000.0;
	}

	void setCPUTemperature(int valueTemperature){
		if (valueTemperature < 0){
			cout << "--- Temperature < 0 ---" << endl;
		}
		else {
			CPUtemperature = valueTemperature;
		}
	}

	void setGPUTemperature(int valueTemperature){
		if (valueTemperature < 0){
			cout << "--- Temperature < 0 ---" << endl;
		}
		else {
			GPUtemperature = valueTemperature;
		}
	}
	
};

int main(){
	Data data;
	data.setCPUTemperature(data.getCPUTemperature());
	data.setGPUTemperature(data.getGPUTemperature());

	cout << "CPU Temperature: " << data.getCPUTemperature() << endl;
	cout << "GPU Temperature: " << data.getGPUTemperature() << endl;
	return 0;
}

