#include <iostream>
#include <cstdlib> // For system()

void callPythonScript(const std::string& scriptPath, const std::string& argument) {
    // Form the command to execute
    std::string command = "/usr/bin/python " + scriptPath + " " + argument;

    // Execute the command
    int result = system(command.c_str());

    if (result == -1) {
        std::cerr << "Failed to call Python script" << std::endl;
    }
}

int main() {
    std::string scriptPath = "/home/max/Arduino/projects/BasicStepperDriver/stepper_driver.py"; // Path to your Python script
    std::string argument = ""; // Argument to pass to the Python script

    callPythonScript(scriptPath, argument);

    return 0;
}