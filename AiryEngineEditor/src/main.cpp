#include <memory>
#include <iostream>
using std::cout;
using std::endl;

#include <AiryEngineCore/Application.hpp>

class MyApp : public AiryEngine::Application
{
    virtual void on_update() override
    {
        //cout << "Update frame: " << frame++ << endl;
    }

    int frame = 0;
};

int main(int argc, char const *argv[])
{
    auto myApp = std::make_unique<MyApp>();
    int returnCode = myApp->start(1024, 768, "My First App");

    return returnCode;
}
