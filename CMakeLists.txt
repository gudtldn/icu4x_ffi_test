cmake_minimum_required(VERSION 3.28)
project(icu4x_ffi_test LANGUAGES CXX)


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
