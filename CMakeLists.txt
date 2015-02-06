cmake_minimum_required(VERSION 2.8)
project(SampleLibSVM)


find_package(OpenCV REQUIRED )
find_package(Boost COMPONENTS system filesystem REQUIRED)
find_package(CUDA REQUIRED )

INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

#SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -stdlib=libstdc++" )

SET(LIBSVM_SRC_DIR "src/libsvm-3.20")
INCLUDE_DIRECTORIES(${LIBSVM_SRC_DIR})


set( NAME_SRC
    src/SampleLibSVM.cpp    
)


ADD_LIBRARY(
    libsvm_lib
    ${LIBSVM_SRC_DIR}/svm-predict.c
    ${LIBSVM_SRC_DIR}/svm-scale.c
    ${LIBSVM_SRC_DIR}/svm-train.c
    ${LIBSVM_SRC_DIR}/svm.cpp
)

CUDA_add_executable(SampleLibSVM src/SampleLibSVM.cpp)
target_link_libraries(SampleLibSVM ${OpenCV_LIBS})
target_link_libraries(SampleLibSVM ${Boost_LIBRARIES}  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SYSTEM_LIBRARY} )
target_link_libraries(SampleLibSVM libsvm_lib)