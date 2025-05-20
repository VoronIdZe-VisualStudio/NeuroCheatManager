#pragma once
#include "NeuralNetwork.h"
#include "ProcessManager.h"
#include <imgui.h>

class UI {
public:
    void Render();
    void ShowToolSuggestions(const std::string& input);

private:
    NeuralNetwork nn;
    ProcessManager pm;
    char processName[256] = "game.exe";
    std::string aiResponse;
    std::vector<std::string> installedTools;
};