cmake -DCMSISDSP=/Volumes/Ext/Embedded/CMSIS-DSP \
      -DCMSISSTREAM=/Volumes/Ext/Embedded/CMSIS-Stream \
      -DHOST=ON -DMAC=OFF \
      -DCMAKE_TOOLCHAIN_FILE=/Volumes/Ext/MyDev/emsdk/upstream/emscripten/cmake/Modules/Platform/Emscripten.cmake \
      ..