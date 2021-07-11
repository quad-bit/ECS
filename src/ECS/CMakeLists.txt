
include("${CMAKE_CURRENT_SOURCE_DIR}/../../Util.cmake")

HEADER_DIRECTORIES(SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})

Set ( SourceList "")

FOREACH(subdir ${SUBDIRS})
    #message(${subdir})
    #file(RELATIVE_PATH test ${CMAKE_CURRENT_SOURCE_DIR} ${subdir})
    #message(${test})

    file(GLOB fileListInDir
        "${subdir}/*.h"
        "${subdir}/*.cpp"
        "${subdir}/*.txt"
    )
    LIST(APPEND SourceList ${fileListInDir})
    source_group(${subdir} FILES ${fileListInDir})

ENDFOREACH()

message("\n")

#get all the source files
file(GLOB filesInParentDir
    "*.h"
    "*.cpp"
    "*.txt"
)

list(LENGTH filesInParentDir size)
IF(NOT ${size} EQUAL 0)
    LIST(APPEND SourceList ${filesInParentDir})
    source_group("" FILES ${filesInParentDir})
    LIST(APPEND SUBDIRS ${CMAKE_CURRENT_SOURCE_DIR})
ENDIF()

##  file list creation ends

#find glm

message ("If cmake is not able to find glm. \nCreate an environ var for glm, variable : GLM_PATH, and assign it the top directory of glm lib\n")

IF( DEFINED ENV{GLM_PATH} )
  SET( glm_DIR "$ENV{GLM_PATH}" )
ENDIF()

find_package(glm HINTS "${glm_DIR}")

IF( glm_FOUND )
  message ("\nfound glm ")
ELSE()
  SET( glm_DIR "$ENV{GLM_PATH}" )
  SET ( glm_INCLUDE_DIR "${glm_DIR}")
  message (" glm include directory set to : ${glm_INCLUDE_DIR}")
ENDIF()

add_Executable(ECS ${SourceList})

#include directories
message ("include directories ${glm_INCLUDE_DIR}")
target_include_directories(ECS PUBLIC
${glm_INCLUDE_DIR}
#${CMAKE_CURRENT_SOURCE_DIR}
)