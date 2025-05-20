cmake_minimum_required(VERSION 3.15)
project ("NeuroCheatManager")
add_subdirectory ("NeuroCheatManager")

# Настройки C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ищем зависимости
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# Подключаем ImGui (предполагается, что он в папке libs)
add_subdirectory(libs/imgui)

# Включаем ONNX Runtime (если используется)
if (USE_ONNX)
    find_package(ONNXRuntime REQUIRED)
endif()

# Главный исполняемый файл
add_executable(AI_Reverse_Tool
    src/main.cpp
    src/core/NeuralNetwork.cpp
    src/reverse/ProcessManager.cpp
    src/gui/UI.cpp
)

# Линковка библиотек
target_link_libraries(AI_Reverse_Tool
    OpenGL::GL
    glfw
    imgui
    ${ONNXRuntime_LIBRARIES}  # Если используется ONNX
)

# Для Windows
if (WIN32)
    target_link_libraries(AI_Reverse_Tool kernel32.lib user32.lib)
endif()

