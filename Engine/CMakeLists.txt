cmake_minimum_required(VERSION 3.0...3.5)

project(Engine)

set(SOURCES 
src/Flow/Core.cpp
src/Flow/Application.cpp
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})