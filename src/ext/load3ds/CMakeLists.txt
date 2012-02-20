set(C3DSREADER_SOURCES
	C3DSLightReader.cpp
	C3DSMaterialReader.cpp
	C3DSMeshNormalCalculator.cpp
	C3DSMeshReader.cpp
	C3DSReaderBase.cpp
)

include_directories(math3d++)

add_library(c3dsreader ${C3DSREADER_SOURCES})
set_target_properties(c3dsreader PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
