cmake_minimum_required(VERSION 3.1.0)

project(spreadsheet)

FIND_PACKAGE(Qt5LinguistTools)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)

# Create code from a list of Qt designer ui files
set(CMAKE_AUTOUIC ON)

# Automatically handle resource files
set(CMAKE_AUTORCC ON)

# Find the QtWidgets library
find_package(Qt5Widgets CONFIG REQUIRED)

# Populate a CMake variable with the sources
set(spreadsheet_SRCS
    cell.cpp
    finddialog.cpp
    gotocelldialog.cpp
    main.cpp
    mainwindow.cpp
    sortdialog.cpp
    spreadsheet.cpp
    spreadsheet.qrc
)

# Translation files
SET(TS_FILES
    spreadsheet_de.ts
    spreadsheet_fr.ts
)

qt5_add_translation(QM_FILES ${TS_FILES})

# Tell CMake to create the spreadsheet executable
add_executable(spreadsheet WIN32 ${spreadsheet_SRCS} ${QM_FILES})

# Use the Widgets module from Qt 5
target_link_libraries(spreadsheet Qt5::Widgets)
