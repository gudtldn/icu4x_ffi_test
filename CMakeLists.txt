cmake_minimum_required(VERSION 3.28)
project(icu4x_ffi_test LANGUAGES CXX)


# =====================================================================
# FetchContent 설정 (의존성 자동 다운로드)
# =====================================================================
include(FetchContent)

# Corrosion (Rust 빌드 연동 모듈) 가져오기
FetchContent_Declare(
        Corrosion
        GIT_REPOSITORY https://github.com/corrosion-rs/corrosion.git
        GIT_TAG        v0.6.1
        GIT_SHALLOW    TRUE
)

# ICU4X 소스코드 가져오기
FetchContent_Declare(
        icu4x_src
        GIT_REPOSITORY https://github.com/unicode-org/icu4x.git
        GIT_TAG        icu@2.1.0
        GIT_SHALLOW    TRUE
)

FetchContent_MakeAvailable(Corrosion icu4x_src)


# =====================================================================
# ICU4X Crate(Cargo.toml)를 CMake 타겟으로 가져오기
# Usage: https://corrosion-rs.github.io/corrosion/usage.html
# =====================================================================
corrosion_import_crate(
        MANIFEST_PATH "${icu4x_src_SOURCE_DIR}/ffi/capi/Cargo.toml"
)


# =====================================================================
# 컴파일 타겟 세팅
# =====================================================================
add_executable(icu4x_ffi_test main.cpp)

# C++ 기본 Properties 설정
target_compile_features(icu4x_ffi_test PRIVATE
        cxx_std_23
)

set_target_properties(icu4x_ffi_test PROPERTIES
        CXX_EXTENSIONS OFF
        CXX_STANDARD_REQUIRED ON
)

# 빌드된 Rust 라이브러리(icu_capi)를 C++ 실행 파일에 링킹
target_link_libraries(icu4x_ffi_test PRIVATE
        icu_capi
)

# C++ 바인딩 헤더 경로 지정
target_include_directories(icu4x_ffi_test PRIVATE
        "${icu4x_src_SOURCE_DIR}/ffi/capi/bindings/cpp"
)

# 컴파일러별 옵션 설정
if(MSVC)
    target_compile_options(icu4x_ffi_test PRIVATE
            /utf-8           # 소스/실행 파일 인코딩을 UTF-8로 사용
            /permissive-     # MSVC 비표준 확장 끄기
            /Zc:preprocessor # MSVC 전처리기가 표준을 준수하도록 설정
            /Zc:__cplusplus  # 표준 __cplusplus 버전을 사용
            /W4              # 경고 수준을 최고 수준으로 설정
    )

else()
    target_compile_options(icu4x_ffi_test PRIVATE
            -finput-charset=UTF-8 # 소스 파일 인코딩을 UTF-8로 설정
            -fexec-charset=UTF-8  # 실행 파일 문자열 인코딩을 UTF-8로 설정
            -pedantic             # 비표준 문법 경고 (MSVC /permissive- 대응)
            -Wall -Wextra         # 일반적인 모든 경고와 추가적인 경고까지 활성화
    )
endif()
