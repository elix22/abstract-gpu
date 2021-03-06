set(AGPU_Metal_SOURCES
    buffer.hpp
    buffer.mm
    command_allocator.hpp
    command_allocator.mm
    command_list.hpp
    command_list.mm
    command_queue.hpp
    command_queue.mm
    common.hpp
    device.hpp
    device.mm
    fence.hpp
    fence.mm
    framebuffer.hpp
    framebuffer.mm
    icd.c
    object.hpp
    pipeline_builder.hpp
    pipeline_builder.mm
    pipeline_state.hpp
    pipeline_state.mm
    platform.mm
    platform.hpp
    renderpass.hpp
    renderpass.mm
    shader_signature_builder.hpp
    shader_signature_builder.mm
    shader_signature.hpp
    shader_signature.mm
    shader_resource_binding.hpp
    shader_resource_binding.mm
    shader.hpp
    shader.mm
    swap_chain.hpp
    swap_chain.mm
    texture.hpp
    texture.mm
    vertex_binding.hpp
    vertex_binding.mm
    vertex_layout.hpp
    vertex_layout.mm
)

add_definitions(-DAGPU_BUILD)

add_library(AgpuMetal SHARED ${AGPU_Metal_SOURCES})
target_link_libraries(AgpuMetal ${METAL_LIBRARY} ${QUARTZCORE_LIBRARY} ${APPKIT_LIBRARY})
