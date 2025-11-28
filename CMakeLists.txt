cmake_minimum_required(VERSION 3.16)
project(Folder_Exam_Visualisation_and_Simulation_2025 LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

qt_standard_project_setup()

qt_add_executable(Folder_Exam_Visualisation_and_Simulation_2025
    MainWindow.cpp MainWindow.h
    main.cpp
    Part1_Camera.cpp
    Part1_Camera.h
    Part1_ObjMesh.cpp
    Part1_ObjMesh.h
    Part1_VisualObj.cpp
    Part1_VisualObj.h
    Part1_Vertex
    Part1_Vertex.cpp
    Part1_Vertex.h
    Part1_Utilities.h
    Part1_Renderer.cpp
    Part1_Renderer.h
    Part1_WorldAxis.cpp
    Part1_WorldAxis.h
    Part1_VWindow.h
    Part1_VWindow.cpp
    Part1_Input.h
)
# Define the shader files
set(SHADER_FILES
    color.frag
    color.vert
    texture.frag
    texture.vert
)

# Add the shader files to the project
add_custom_target(Shaders
    SOURCES ${SHADER_FILES}
)

set_target_properties(Folder_Exam_Visualisation_and_Simulation_2025 PROPERTIES
    WIN32_EXECUTABLE TRUE
    MACOSX_BUNDLE TRUE
)

target_link_libraries(Folder_Exam_Visualisation_and_Simulation_2025 PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

# Resources:
set_source_files_properties("color_frag.spv"
    PROPERTIES QT_RESOURCE_ALIAS "color_frag.spv"
)

set_source_files_properties("color_vert.spv"
    PROPERTIES QT_RESOURCE_ALIAS "color_vert.spv"
)

set_source_files_properties("texture_frag.spv"
    PROPERTIES QT_RESOURCE_ALIAS "texture_frag.spv"
)

set_source_files_properties("texture_vert.spv"
    PROPERTIES QT_RESOURCE_ALIAS "texture_vert.spv"
)

set(Folder_Exam_Visualisation_and_Simulation_2025_resource_files
    "color_frag.spv"
    "color_vert.spv"
    "texture_frag.spv"
    "texture_vert.spv"
)

qt_add_resources(Folder_Exam_Visualisation_and_Simulation_2025 "Folder_Exam_Visualisation_and_Simulation_2025"
    PREFIX
        "/"
    FILES
        ${Folder_Exam_Visualisation_and_Simulation_2025_resource_files}
)

install(TARGETS Folder_Exam_Visualisation_and_Simulation_2025
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET Folder_Exam_Visualisation_and_Simulation_2025
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})

# auto-compilation of the shaders:
add_custom_target(
    PreBuildCommandCF ALL
    COMMAND glslc color.frag -o color_frag.spv
#   This version includes the debug info in the compiled shader - good for RenderDoc
#   COMMAND glslangValidator -g -V -o color_frag.spv color.frag
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Compiling color fragment shader"
)
add_custom_target(
    PreBuildCommandCV ALL
    COMMAND glslc color.vert -o color_vert.spv
#   COMMAND glslangValidator -g -V -o color_vert.spv color.vert
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Compiling color vertex shader"
)
add_custom_target(
    PreBuildCommandTF ALL
    COMMAND glslc texture.frag -o texture_frag.spv
#   This version includes the debug info in the compiled shader - good for RenderDoc
#   COMMAND glslangValidator -g -V -o texture_frag.spv texture.frag
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Compiling texture fragment shader"
)
add_custom_target(
    PreBuildCommandTV ALL
    COMMAND glslc texture.vert -o texture_vert.spv
#   COMMAND glslangValidator -g -V -o texture_vert.spv texture.vert
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Compiling texture vertex shader"
)

add_dependencies(Folder_Exam_Visualisation_and_Simulation_2025 PreBuildCommandCF)
add_dependencies(Folder_Exam_Visualisation_and_Simulation_2025 PreBuildCommandCV)
add_dependencies(Folder_Exam_Visualisation_and_Simulation_2025 PreBuildCommandTF)
add_dependencies(Folder_Exam_Visualisation_and_Simulation_2025 PreBuildCommandTV)


