#include "NeuralNetwork.h"
#include <stdexcept>

NeuralNetwork::NeuralNetwork() : env(ORT_LOGGING_LEVEL_WARNING, "AI-Reverser") {}

bool NeuralNetwork::LoadModel(const std::string& model_path) {
    try {
        Ort::SessionOptions session_options;
        session = Ort::Session(env, model_path.c_str(), session_options);
        model_loaded = true;
        return true;
    }
    catch (const Ort::Exception& e) {
        return false;
    }
}

std::string NeuralNetwork::AnalyzeProcessData(const std::vector<uint8_t>& data) {
    if (!model_loaded) return "Error: Model not loaded!";

    // Заглушка: реальная модель будет анализировать дамп памяти
    return "Detected patterns: Unpacker (UPX), Anti-Debug (IsDebuggerPresent)";
}

std::string NeuralNetwork::GetSuggestedTool(const std::string& input) {
    // Заглушка: нейросеть предлагает инструменты на основе входных данных
    if (input.find("packed") != std::string::npos) {
        return "Suggested tools: Ghidra (unpack), x64dbg (dynamic analysis)";
    }
    return "Suggested tools: Cheat Engine, IDA Pro";
}