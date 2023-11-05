cmake_minimum_required(VERSION 3.26)
project(projeto)

set(CMAKE_CXX_STANDARD 17)

set(SOURCES
    main.cpp
        ClassSession.cpp
    Student.cpp
    TimeInterval.cpp
    Uc.cpp
    Class.cpp
    Data.cpp
    App.cpp
    UserInterface.cpp
    Request.cpp
        Request.cpp)

add_executable(projeto ${SOURCES})
