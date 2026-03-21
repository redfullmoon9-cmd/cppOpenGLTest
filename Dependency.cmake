# ExternalProject 관련 명령어 셋 추가
include(ExternalProject)

# Dependency 관련 변수 설정
set(DEP_INSTALL_DIR ${PROJECT_BINARY_DIR}/install)
set(DEP_INCLUDE_DIR ${DEP_INSTALL_DIR}/include)
set(DEP_LIB_DIR ${DEP_INSTALL_DIR}/lib  ${DEP_INSTALL_DIR}/lib64) #페도라는 기본적으로 lib64를 사용. 

# spdlog: fast logger library
ExternalProject_Add(
    dep-spdlog
    # GIT_REPOSITORY "https://github.com/gabime/spdlog.git"
    # GIT_TAG "v1.x" 
    URL "${CMAKE_CURRENT_SOURCE_DIR}/external/spdlog" # 로컬경로에서 파일가져와서 설치. 
    GIT_SHALLOW 1  # 커밋 된것과 관계없이 가장 최신의 것만 받는다
    UPDATE_COMMAND "" # 업데이트 방지.  
    PATCH_COMMAND "" # 패치 방지. 
    # CMAKE_GENERATOR ${CMAKE_GENERATOR} #메인과 동일한 generator 사용하게 됨. 
    CMAKE_ARGS 
        -DCMAKE_INSTALL_PREFIX=${DEP_INSTALL_DIR} 
        -DSPDLOG_BUILD_SHARED=OFF #정적라이브러리
        -DSPDLOG_BUILD_EXAMPLE=OFF
        -DSPDLOG_INSTALL=ON # 명시적으로 install target활성화. 
    TEST_COMMAND ""
)
# Dependency 리스트 및 라이브러리 파일 리스트 추가
set(DEP_LIST ${DEP_LIST} dep-spdlog)
# set(DEP_LIBS ${DEP_LIBS} spdlog$<$<CONFIG:Debug>:d>) // 원도우즈용 설정의 습관
set(DEP_LIBS ${DEP_LIBS} spdlog)