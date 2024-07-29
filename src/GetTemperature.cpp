#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <memory>

using namespace std;

class Data {
private:
    int GPUtemperature;
    int CPUtemperature;
    string NameGPU;

public:
    // Витягання температури з системних файлів;
    // Для AMD
    float getAMDGPUTemperature(){
        ifstream file("/sys/class/drm/card0/device/hwmon/hwmon0/temp1_input");
        if (!file.is_open()) {
            cout << "Error: Unable to open temperature file. Maybe, your GPU is not AMD.\n" << endl;
            return -1;
        }

        float temperature;
        file >> temperature;
        file.close();

        return temperature / 1000.0;
    }

    // Для Intel
    float getIntelGPUTemperature() {
        FILE *pipe = popen("sensors | grep -i 'temp1' | awk '{print $2}'", "r");
        if (!pipe) {
            cout << "Error: Unable to open temperature file. Maybe, your GPU is not Intel.\n" << endl;
            return -1;
        }

        char buffer[128];
        string result = "";
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
            result += buffer;
        }

        pclose(pipe);

        if (result.empty()) {
            cout << "Error: Unable to read temperature.\n" << endl;
            return -1;
        }

        float temperature = stof(result);
        return temperature;
    }

    string getNameGPU(){
        return NameGPU;
    }

    // Для NVIDIA
    // float getNvidiaGPUTemperature() {
    //     nvmlReturn_t result;
    //     result = nvmlInit();
    //     if (NVML_SUCCESS != result) {
    //         cerr << "Failed to initialize NVML: " << nvmlErrorString(result) << endl;
    //         return -1;
    //     }

    //     unsigned int deviceCount;
    //     result = nvmlDeviceGetCount(&deviceCount);
    //     if (NVML_SUCCESS != result) {
    //         cerr << "Failed to query device count: " << nvmlErrorString(result) << endl;
    //         nvmlShutdown();
    //         return -1;
    //     }

    //     nvmlDevice_t device;
    //     result = nvmlDeviceGetHandleByIndex(0, &device);
    //     if (NVML_SUCCESS != result) {
    //         cerr << "Failed to get handle for device: " << nvmlErrorString(result) << endl;
    //         nvmlShutdown();
    //         return -1;
    //     }

    //     unsigned int temperature;
    //     result = nvmlDeviceGetTemperature(device, NVML_TEMPERATURE_GPU, &temperature);
    //     if (NVML_SUCCESS != result) {
    //         cerr << "Failed to get temperature: " << nvmlErrorString(result) << endl;
    //         nvmlShutdown();
    //         return -1;
    //     }

    //     nvmlShutdown();
    //     return static_cast<float>(temperature);

    // }

    // Загальне
    float getGPUTemperature() {
        string gpuVendor = getGPUVendor();
        if (gpuVendor == "AMD") {
            float temperature = getAMDGPUTemperature();
            setGPUTemperature(temperature, "AMD");
            return temperature;
        } else if (gpuVendor == "Intel") {
            float temperature = getIntelGPUTemperature();
            setGPUTemperature(temperature, "Intel");
            return temperature;
        } 
        // else if (gpuVendor == "NVIDIA") {
        //     float temperature = getNvidiaGPUTemperature();
        //     setGPUTemperature(temperature, "NVIDIA");
        //     return temperature;
        // } 
        else {
            cout << "Unknown GPU vendor.\n" << endl;
            return -1;
        }
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
            cout << "--- CPU Temperature < 0 ---" << endl;
        }
        else {
            CPUtemperature = valueTemperature;
        }
    }

    void setGPUTemperature(float valueTemperature, const string& valueNameGPU) {
        if (valueTemperature < 0){
            cout << "--- GPU Temperature < 0 ---" << endl;
        }
        else {
            NameGPU = valueNameGPU;
            GPUtemperature = valueTemperature;
        }
    }

    string getGPUVendor() {
        char buffer[128];
        string result = "";
        // Використовуємо команду lspci для визначення GPU
        shared_ptr<FILE> pipe(popen("lspci | grep VGA", "r"), pclose);
        if (!pipe) {
            return "Unknown";
        }
        while (fgets(buffer, sizeof(buffer), pipe.get()) != nullptr) {
            result += buffer;
        }

        if (result.find("AMD") != string::npos) {
            return "AMD";
        } else if (result.find("Intel") != string::npos) {
            return "Intel";
        } else if (result.find("NVIDIA") != string::npos) {
            return "NVIDIA";
        } else {
            return "Unknown";
        }
    }
};

int main(){
    Data data;
    data.setCPUTemperature(data.getCPUTemperature());

    // Викликаємо setGPUTemperature з двома параметрами
    data.setGPUTemperature(data.getGPUTemperature(), data.getNameGPU());

    cout << "CPU Temperature: " << data.getCPUTemperature() << endl;
    cout << "GPU Temperature: " << data.getGPUTemperature() << endl;
    cout << "GPU Name: " << data.getNameGPU() << endl;

    return 0;
}
