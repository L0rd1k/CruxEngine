#pragma once


extern Sage::Application* Sage::CreateApplication();

int main(int argc, char** argv) {
    auto app = Sage::CreateApplication();
    app->run();
    delete app;
}