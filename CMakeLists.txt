cmake_minimum_required(VERSION 3.16)

project(Spotify VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Sql)

set(PROJECT_SOURCES
        Source/main.cpp
        Source/mainwindow.cpp
        Source/mainwindow.h
        Source/mainwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Spotify
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        Entities/account.cpp
        Entities/album.cpp
        Entities/artist.cpp
        Entities/listener.cpp
        Entities/playlist.cpp
        Entities/song.cpp
        Repositories/AbstractRepository.h

        Repositories/albumrepository.cpp
        Repositories/artistrepository.cpp
        Repositories/listenerrepository.cpp
        Repositories/playlistrepository.cpp
        Repositories/songrepository.cpp
        Entities/Role.h
        Entities/account.h
        Database/database.cpp
        Database/database.h
        Exceptions/LoginException.h
        Source/albumwindow.h Source/albumwindow.cpp Source/albumwindow.ui
        Source/artistwindow.h Source/artistwindow.cpp Source/artistwindow.ui
        Source/changepassworddialog.h Source/changepassworddialog.cpp Source/changepassworddialog.ui
        Source/createalbumdialog.h Source/createalbumdialog.cpp Source/createalbumdialog.ui
        Source/createsongdialog.h Source/createsongdialog.cpp Source/createsongdialog.ui
        Source/editalbumdialog.h Source/editalbumdialog.cpp Source/editalbumdialog.ui
        Source/editartistdialog.h Source/editartistdialog.cpp Source/editartistdialog.ui
        Source/editsongdialog.h Source/editsongdialog.cpp Source/editsongdialog.ui
        Source/listenerwindow.h Source/listenerwindow.cpp Source/listenerwindow.ui
        Source/registerwindow.h Source/registerwindow.cpp Source/registerwindow.ui

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Spotify APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Spotify SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Spotify
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Spotify PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Spotify)
endif()
set_target_properties(Spotify PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Spotify
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Spotify)
endif()
