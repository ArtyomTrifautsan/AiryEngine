
#include <iostream>
#include <memory>
#include <imgui/imgui.h>
using std::cout;
using std::endl;

#include <AiryEngineCore/Application.hpp>

class AiryEngineEditor : public AiryEngine::Application
{
    virtual void on_update() override
    {
        //cout << "Update frame: " << frame++ << endl;
    }

    virtual void on_ui_draw() override
    {
        ImGui::Begin("Editor");

        ImGui::SliderFloat3("camera position", camera_position, -10.0f, 10.0f);
        ImGui::SliderFloat3("camera rotation", camera_rotation, 0.0f, 360.0f);
        ImGui::Checkbox("Perspective camera", &perspective_camera);

        ImGui::End();
    }   

    int frame = 0;
};

int main(int argc, char const *argv[])
{
    auto airyEngineEditor = std::make_unique<AiryEngineEditor>();
    int returnCode = airyEngineEditor->start(1024, 768, "AiryEngine Editor");

    return returnCode;
}
