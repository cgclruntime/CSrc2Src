SET(SRC_LIST betweennessCentrality.cpp computeGraph.cpp findSubGraphs.cpp genScalData.cpp getStartLists.cpp init.cpp rand.cpp SSCA2.cpp utils.cpp)
INCLUDE_DIRECTORIES(${INCLUDE_DIRS})

LINK_DIRECTORIES(${TOOLS_LINK_DIRS})
ADD_DEFINITIONS(${DEBUG_DEFS})
ADD_EXECUTABLE(SSCA2 ${SRC_LIST})
TARGET_LINK_LIBRARIES(SSCA2 ${TOOLS_LINK_LIBS})

