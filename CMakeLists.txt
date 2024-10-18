cmake_minimum_required(VERSION 3.26)
project (stream_kernel VERSION 0.1)



option(MAC "Build for mac" OFF)

add_subdirectory(${CMSISDSP}/Source bin_dsp)



if (MAC)
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_C_STANDARD 11)
add_executable(stream_kernel)
target_compile_options(CMSISDSP PUBLIC -Ofast)
target_sources(stream_kernel PUBLIC osxmain.cpp )
target_compile_definitions(stream_kernel PUBLIC OSX)
target_link_libraries(stream_kernel PUBLIC -Wl,-framework,CoreAudio,-framework,AudioUnit)
else()
set (CMAKE_C_STANDARD 11)
add_executable(stream_kernel)
target_compile_options(CMSISDSP PUBLIC -O2)
target_sources(stream_kernel PUBLIC StreamKernel.cc )
target_compile_options(stream_kernel PUBLIC 
	    -sSHARED_MEMORY
		-sWASM_WORKERS=1
		-sUSE_PTHREADS
		-std=c++2b
		)
target_link_options(stream_kernel PUBLIC -sEXPORTED_FUNCTIONS=['_malloc','_free']
	    -sEXPORTED_RUNTIME_METHODS=['ccall','cwrap']
	    -sWASM=1
	    -sSHARED_MEMORY
		-sWASM_WORKERS=1
	    -sSINGLE_FILE=0
	    -sUSE_PTHREADS
		-sWASM_ASYNC_COMPILATION=0
	    --bind 
	    --post-js ${CMAKE_SOURCE_DIR}/lib/em-es6-module.js)
endif()

target_include_directories(stream_kernel PUBLIC include)
target_include_directories(stream_kernel PUBLIC .)
target_include_directories(stream_kernel PUBLIC ${CMSISSTREAM}/Include/cg/nodes/cpp)
target_link_libraries(stream_kernel PUBLIC CMSISDSP)

target_include_directories(stream_kernel PUBLIC SAM/src)

if (MAC)
add_custom_command(TARGET stream_kernel PRE_BUILD 
        BYPRODUCTS ${CMAKE_CURRENT_SOURCE_DIR}/test.pdf
        COMMAND dot -Tsvg -o ${CMAKE_CURRENT_SOURCE_DIR}/graph.svg ${CMAKE_CURRENT_SOURCE_DIR}/test.dot
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/test.dot
        VERBATIM
        )
else()
	add_custom_command(TARGET stream_kernel PRE_BUILD 
        BYPRODUCTS ${CMAKE_CURRENT_SOURCE_DIR}/test.pdf
        COMMAND dot -Tsvg -o ${CMAKE_CURRENT_SOURCE_DIR}/stream_demo/graph.svg ${CMAKE_CURRENT_SOURCE_DIR}/test.dot
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/test.dot
        VERBATIM
        )
endif()

target_sources(stream_kernel PUBLIC scheduler.cpp 
	source/Songs/ImperialMarch.cpp
	source/Songs/BohemianRhapsody.cpp
	source/Songs/Overture.cpp
        source/Songs/Ghostbusters.cpp
        source/Songs/PinkPanther.cpp
        source/Songs/ToccataAndFugueInDMinor.cpp
        source/Songs/WeAreTheChampion.cpp
	source/instruments.cpp
	source/synth_Playtune_waves.cpp
	SAM/src/debug.c             
	SAM/src/render.c
        SAM/src/sam.c
        SAM/src/processframes.c
        SAM/src/createtransitions.c 
        SAM/src/reciter.c
	)


install(FILES ${CMAKE_BINARY_DIR}/stream_kernel.js
	    ${CMAKE_BINARY_DIR}/stream_kernel.wasm
	    ${CMAKE_BINARY_DIR}/stream_kernel.worker.js
	    ${CMAKE_BINARY_DIR}/stream_kernel.ww.js
        DESTINATION ${CMAKE_SOURCE_DIR}/stream_demo
)