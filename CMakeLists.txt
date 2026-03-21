# CMakeLists.txt
cmake_minimum_required(VERSION 3.14)

# 빌드 타입이 지정되지 않은 경우 Debug로 설정
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

# message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

set(PROJECT_NAME CppGraphic)

project(${PROJECT_NAME})

# 2. 패키지 찾기 
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)  
find_package(glm REQUIRED) 

# 1. 소스 파일들을 리스트로 만들기 (source 폴더 내의 모든 cpp)
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.c" "msrc/*.cpp")

# add_executable(${PROJECT_NAME} main.cpp)
# 3. 실행 파일 생성 (main.cpp가 루트에 있다면 포함, 소스 리스트 추가)
add_executable(${PROJECT_NAME} main.cpp ${SOURCES}) 

include(Dependency.cmake) # 
# include(ExternalProject) 에서 dependency에 있는 파일 불러오기로 

# 4. 핵심: include 폴더 경로를 컴파일러에게 알려주기 
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${DEP_INCLUDE_DIR})

target_link_directories(${PROJECT_NAME} PUBLIC ${DEP_LIB_DIR})

# 5. 라이브러리 연결 glm추가
target_link_libraries(${PROJECT_NAME} PUBLIC OpenGL::GL glfw glm::glm ${DEP_LIBS})

add_dependencies(${PROJECT_NAME} ${DEP_LIST})

# 쉐이더 파일 의 경로를 소스에서 참조 하도록 하는 방식으로 변경. 
target_compile_definitions(${PROJECT_NAME} PRIVATE SHADER_DIR="${CMAKE_CURRENT_SOURCE_DIR}/KShader/" )

# 소스파일을 메이크 수행시에 /build 경로로 복사하는 방식 
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/KImage DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/KImage
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/KImage
    COMMENT "Copying KImage files..."
)