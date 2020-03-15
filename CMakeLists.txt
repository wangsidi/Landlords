cmake_minimum_required(VERSION 3.0)
project(Fight_the_Landlord)

#����C/C++��׼
set(CMAKE_CXX_COMPILER "g++")
set (CMAKE_CXX_FLAGS  "-g -fexec-charset=GBK")

#ͷ�ļ�·��
include_directories(${PROJECT_SOURCE_DIR}/Inc IncFiles)
#Դ�ļ�·��
aux_source_directory(./Src SrcFiles)
#���·��
set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/Bin)

#Ŀ�������
add_executable(game ${SrcFiles})
