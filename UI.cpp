#include "UI.h"

void UI::Render() {
    // ������� ����
    ImGui::Begin("AI Reverse Engineer");

    // ����������� � ��������
    if (ImGui::InputText("Process Name", processName, sizeof(processName))) {}
    if (ImGui::Button("Attach to Process")) {
        DWORD pid = pm.FindProcess(processName);
        if (pid != 0) {
            HANDLE hProcess = pm.Attach(pid);
            if (hProcess) {
                auto dump = pm.DumpMemory(hProcess, 0x00400000, 1024);
                aiResponse = nn.AnalyzeProcessData(dump);
                installedTools = pm.ListInstalledTools();
                CloseHandle(hProcess);
            }
        }
    }

    // ����� ������ ���������
    ImGui::Text("AI Analysis:");
    ImGui::TextWrapped("%s", aiResponse.c_str());

    // ������ ������������
    ImGui::Text("Installed Tools:");
    for (const auto& tool : installedTools) {
        ImGui::BulletText("%s", tool.c_str());
    }

    // ������ ��� ������
    if (ImGui::Button("Ask AI for Tools")) {
        aiResponse = nn.GetSuggestedTool(aiResponse);
    }

    ImGui::End();
}