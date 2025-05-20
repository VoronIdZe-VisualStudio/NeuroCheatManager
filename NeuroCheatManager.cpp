
#include "NeuroCheatManager.h"
#include "ProcessUtils.h"
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GLFW/glfw3.h>
#include <vector>

int main() {
    // Инициализация GLFW
    if (!glfwInit()) return -1;
    GLFWwindow* window = glfwCreateWindow(1280, 720, "AI Reverse Tool", NULL, NULL);
    if (!window) {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Инициализация ImGui
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // Данные приложения
    char processName[256] = "game.exe";
    std::vector<uint8_t> memoryDump;
    bool isAttached = false;
    HANDLE hProcess = NULL;
    DWORD pid = 0;

    // Главный цикл
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Окно управления процессом
        ImGui::Begin("Process Control");
        ImGui::InputText("Process Name", processName, sizeof(processName));
        if (ImGui::Button("Attach")) {
            pid = ProcessUtils::FindProcess(processName);
            if (pid) {
                hProcess = ProcessUtils::Attach(pid);
                isAttached = (hProcess != NULL);
            }
        }
        ImGui::SameLine();
        ImGui::Text(isAttached ? "Attached to PID: %d" : "Not attached", pid);

        if (isAttached && ImGui::Button("Dump Memory")) {
            memoryDump = ProcessUtils::DumpMemory(hProcess, 0x00400000, 1024); // Пример: дамп 1 КБ с адреса 0x00400000
        }
        ImGui::End();

        // Окно дампа памяти
        if (!memoryDump.empty()) {
            ImGui::Begin("Memory Dump");
            ImGui::Text("First 16 bytes:");
            for (int i = 0; i < 16 && i < memoryDump.size(); i++) {
                ImGui::Text("%02X ", memoryDump[i]);
                if (i % 8 == 7) ImGui::NewLine();
            }
            if (ImGui::Button("Save to File")) {
                ProcessUtils::SaveToFile("dump.bin", memoryDump);
            }
            ImGui::End();
        }

        // Рендеринг
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    // Очистка
    if (hProcess) CloseHandle(hProcess);
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;
}