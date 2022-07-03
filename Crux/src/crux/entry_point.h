#pragma once


extern crux::Application* crux::CreateApplication();

int main(int argc, char** argv) {
    auto app = crux::CreateApplication();
    app->run();
    delete app;
}