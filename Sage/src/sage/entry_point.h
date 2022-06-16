#pragma once


extern sage::Application* sage::CreateApplication();

int main(int argc, char** argv) {
    auto app = sage::CreateApplication();
    app->run();
    delete app;
}