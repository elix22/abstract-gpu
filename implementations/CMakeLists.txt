add_subdirectory(Loader)

set(LIBRARY_OUTPUT_PATH "${AGPU_BINARY_DIR}/dist/AgpuIcd")

if(D3D12_FOUND)
    add_subdirectory(Direct3D12)
endif()

if(VULKAN_FOUND)
  add_subdirectory(Vulkan)
endif()

if(OPENGL_FOUND)
    add_subdirectory(OpenGL)
endif()

if(METAL_FOUND)
  add_subdirectory(Metal)
endif()
