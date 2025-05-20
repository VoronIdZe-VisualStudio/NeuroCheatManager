#pragma once
#include <onnxruntime_cxx_api.h>
#include <vector>
#include <string>

class NeuralNetwork {
public:
    NeuralNetwork();
    bool LoadModel(const std::string& model_path);
    std::string AnalyzeProcessData(const std::vector<uint8_t>& data);
    std::string GetSuggestedTool(const std::string& input);

private:
    Ort::Env env;
    Ort::Session session{ nullptr };
    bool model_loaded = false;
};