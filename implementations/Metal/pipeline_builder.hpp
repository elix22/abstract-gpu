#ifndef AGPU_METAL_PIPELINE_BUILDER_HPP
#define AGPU_METAL_PIPELINE_BUILDER_HPP

#include "device.hpp"
#include <string>

struct _agpu_pipeline_builder : public Object<_agpu_pipeline_builder>
{
public:
    _agpu_pipeline_builder(agpu_device *device);
    void lostReferences();

    static _agpu_pipeline_builder *create(agpu_device *device);

    agpu_pipeline_state* build ( );
    agpu_error attachShader ( agpu_shader* shader );
    agpu_size getBuildingLogLength (  );
    agpu_error getBuildingLog ( agpu_size buffer_size, agpu_string_buffer buffer );
    agpu_error setBlendState ( agpu_int renderTargetMask, agpu_bool enabled );
    agpu_error setBlendFunction ( agpu_int renderTargetMask, agpu_blending_factor sourceFactor, agpu_blending_factor destFactor, agpu_blending_operation colorOperation, agpu_blending_factor sourceAlphaFactor, agpu_blending_factor destAlphaFactor, agpu_blending_operation alphaOperation );
    agpu_error setColorMask ( agpu_int renderTargetMask, agpu_bool redEnabled, agpu_bool greenEnabled, agpu_bool blueEnabled, agpu_bool alphaEnabled );
    agpu_error setDepthState ( agpu_bool enabled, agpu_bool writeMask, agpu_compare_function function );
    agpu_error setStencilState ( agpu_bool enabled, agpu_int writeMask, agpu_int readMask );
    agpu_error setStencilFrontFace ( agpu_stencil_operation stencilFailOperation, agpu_stencil_operation depthFailOperation, agpu_stencil_operation stencilDepthPassOperation, agpu_compare_function stencilFunction );
    agpu_error setStencilBackFace ( agpu_stencil_operation stencilFailOperation, agpu_stencil_operation depthFailOperation, agpu_stencil_operation stencilDepthPassOperation, agpu_compare_function stencilFunction );
    agpu_error setRenderTargetCount ( agpu_int count );
    agpu_error setRenderTargetFormat ( agpu_uint index, agpu_texture_format format );
    agpu_error setDepthStencilFormat ( agpu_texture_format format );
    agpu_error setPrimitiveType ( agpu_primitive_topology type );
    agpu_error setVertexLayout ( agpu_vertex_layout* layout );
    agpu_error setPipelineShaderSignature ( agpu_shader_signature* signature );
    agpu_error setSampleDescription ( agpu_uint sample_count, agpu_uint sample_quality );

    agpu_device *device;
    MTLRenderPipelineDescriptor *descriptor;
    std::string buildingLog;
    MTLPrimitiveType primitiveType;
};

#endif //AGPU_METAL_PIPELINE_BUILDER_HPP
