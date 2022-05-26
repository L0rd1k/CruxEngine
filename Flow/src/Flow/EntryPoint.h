#pragma once


extern Flow::Application* Flow::CreateApplication();

int main(int argc, char** argv) {
    auto app = Flow::CreateApplication();
    app->run();
    delete app;
}