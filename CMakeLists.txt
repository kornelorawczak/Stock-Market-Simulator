cmake_minimum_required(VERSION 3.5)

project(StockSimGui VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH  "[C:/Qt/6.6.3/msvc2019_64/lib/cmake/Qt6]")
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Charts)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Charts)

add_subdirectory(httplib)
add_subdirectory(json2)

set(PROJECT_SOURCES
    main.cpp
    startmenu.cpp
    startmenu.h
    startmenu.ui
    deposit.h deposit.cpp deposit.ui
    withdrawal.h withdrawal.cpp withdrawal.ui
    history.h history.cpp history.ui
    tradinginstruments.h tradinginstruments.cpp tradinginstruments.ui
    portfolio.h portfolio.cpp portfolio.ui
    details.h details.cpp details.ui
    serializer.cpp serializer.hpp
    data.cpp data.hpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(StockSimGui
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        deposit.cpp deposit.h deposit.ui details.cpp details.h details.ui history.cpp history.h history.ui main.cpp portfolio.cpp portfolio.h portfolio.ui startmenu.cpp startmenu.h startmenu.ui tradinginstruments.cpp tradinginstruments.h tradinginstruments.ui withdrawal.cpp withdrawal.h withdrawal.ui
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET StockSimGui APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(StockSimGui SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(StockSimGui
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(StockSimGui PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt6::Charts httplib nlohmann_json)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.StockSimGui)
endif()
set_target_properties(StockSimGui PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS StockSimGui
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(StockSimGui)
endif()
