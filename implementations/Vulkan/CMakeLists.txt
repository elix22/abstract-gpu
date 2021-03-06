set(AGPU_Vulkan_SOURCES
    buffer.cpp
    buffer.hpp
    command_allocator.cpp
    command_allocator.hpp
    command_list.cpp
    command_list.hpp
    command_queue.cpp
    command_queue.hpp
    common.hpp
    device.cpp
    device.hpp
    fence.cpp
    fence.hpp
    framebuffer.cpp
    framebuffer.hpp
    icd.c
    object.hpp
    pipeline_builder.cpp
    pipeline_builder.hpp
    pipeline_state.cpp
    pipeline_state.hpp
    platform.cpp
    platform.hpp
    renderpass.cpp
    renderpass.hpp
    shader.cpp
    shader.hpp
    shader_resource_binding.cpp
    shader_resource_binding.hpp
    shader_signature.cpp
    shader_signature.hpp
    shader_signature_builder.cpp
    shader_signature_builder.hpp
    swap_chain.cpp
    swap_chain.hpp
    texture.cpp
    texture.hpp
    texture_format.hpp
    vertex_binding.cpp
    vertex_binding.hpp
    vertex_layout.cpp
    vertex_layout.hpp
)

include_directories(${VULKAN_INCLUDE_DIRS})

add_definitions(-DAGPU_BUILD)

add_library(AgpuVulkan SHARED ${AGPU_Vulkan_SOURCES})
target_link_libraries(AgpuVulkan ${VULKAN_LIBRARY} ${VULKAN_WSYS_LIBRARIES})
