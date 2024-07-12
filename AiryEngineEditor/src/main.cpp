#include <iostream>
using std::cout;
using std::endl;

#include <AiryEngineCore/Utils/test.hpp>

int main(int argc, char const *argv[])
{
    cout << "Program run" << endl;
    AiryEngine::checkGlfw();
    return 0;
}
