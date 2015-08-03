#include "pipeline_state.hpp"

_agpu_pipeline_state::_agpu_pipeline_state()
{

}

void _agpu_pipeline_state::lostReferences()
{

}

// Exported C interface
AGPU_EXPORT agpu_error agpuAddPipelineStateReference(agpu_pipeline_state* pipeline_state)
{
    CHECK_POINTER(pipeline_state);
    return pipeline_state->retain();
}

AGPU_EXPORT agpu_error agpuReleasePipelineState(agpu_pipeline_state* pipeline_state)
{
    CHECK_POINTER(pipeline_state);
    return pipeline_state->release();
}

AGPU_EXPORT agpu_int agpuGetUniformLocation(agpu_pipeline_state* pipeline_state, agpu_cstring name)
{
    // Not supported for now.
    return -1;
}