cmake_minimum_required(VERSION 3.31) 

set(PROJECT_NAME CppGraphic)
project(${PROJECT_NAME})

# set(CMAKE_CXX_FLAGS "-g -fsanitize=address -fno-omit-frame-pointer")

set(CMAKE_CXX_STANDARD 17)

# 1. 소스 파일들을 리스트로 만들기 (source 폴더 내의 모든 cpp)
file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.c" "msrc/*.cpp")
   
# 2. 패키지 찾기 
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

# 3. 실행 파일 생성 (main.cpp가 루트에 있다면 포함, 소스 리스트 추가)
add_executable(${PROJECT_NAME} main.cpp ${SOURCES}) 

# 4. 핵심: include 폴더 경로를 컴파일러에게 알려주기 
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# 5. 라이브러리 연결
target_link_libraries(${PROJECT_NAME} OpenGL::GL glfw)

# 여기서 부터가 게임 개발용으로 특화 되었다고 하는 옵션들. 
target_compile_options(${PROJECT_NAME} PRIVATE

# Debug only options
$<$<CONFIG:Debug>:-O1>
$<$<CONFIG:Debug>:-g>
$<$<CONFIG:Debug>:-fno-omit-frame-pointer>

# Sanitizers
$<$<CONFIG:Debug>:-fsanitize=address>
$<$<CONFIG:Debug>:-fsanitize=undefined>

)

target_link_options(${PROJECT_NAME} PRIVATE 
$<$<CONFIG:Debug>:-fsanitize=address> 
$<$<CONFIG:Debug>:-fsanitize=undefined>
)

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