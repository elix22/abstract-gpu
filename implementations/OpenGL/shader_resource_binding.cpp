#include "shader_resource_binding.hpp"
#include "shader_signature.hpp"
#include "texture.hpp"
#include "buffer.hpp"

inline GLenum mapMinFilter(agpu_filter filter)
{
    switch (filter)
    {
    case AGPU_FILTER_MIN_NEAREST_MAG_NEAREST_MIPMAP_NEAREST:
    case AGPU_FILTER_MIN_NEAREST_MAG_NEAREST_MIPMAP_LINEAR:
    case AGPU_FILTER_MIN_NEAREST_MAG_LINEAR_MIPMAP_NEAREST:
    case AGPU_FILTER_MIN_NEAREST_MAG_LINEAR_MIPMAP_LINEAR:
        return GL_NEAREST;
    case AGPU_FILTER_MIN_LINEAR_MAG_NEAREST_MIPMAP_NEAREST:
    case AGPU_FILTER_MIN_LINEAR_MAG_NEAREST_MIPMAP_LINEAR:
    case AGPU_FILTER_MIN_LINEAR_MAG_LINEAR_MIPMAP_NEAREST:
    case AGPU_FILTER_MIN_LINEAR_MAG_LINEAR_MIPMAP_LINEAR:
    case AGPU_FILTER_ANISOTROPIC:
    default:
        return GL_LINEAR;
    }
}

inline GLenum mapMagFilter(agpu_filter filter)
{
    switch (filter)
    {
    case AGPU_FILTER_MIN_NEAREST_MAG_NEAREST_MIPMAP_NEAREST:    return GL_NEAREST_MIPMAP_NEAREST;
    case AGPU_FILTER_MIN_NEAREST_MAG_NEAREST_MIPMAP_LINEAR:     return GL_NEAREST_MIPMAP_LINEAR;
    case AGPU_FILTER_MIN_NEAREST_MAG_LINEAR_MIPMAP_NEAREST:     return GL_LINEAR_MIPMAP_NEAREST;
    case AGPU_FILTER_MIN_NEAREST_MAG_LINEAR_MIPMAP_LINEAR:      return GL_LINEAR_MIPMAP_LINEAR;

    case AGPU_FILTER_MIN_LINEAR_MAG_NEAREST_MIPMAP_NEAREST:     return GL_NEAREST_MIPMAP_NEAREST;
    case AGPU_FILTER_MIN_LINEAR_MAG_NEAREST_MIPMAP_LINEAR:      return GL_NEAREST_MIPMAP_LINEAR;
    case AGPU_FILTER_MIN_LINEAR_MAG_LINEAR_MIPMAP_NEAREST:      return GL_LINEAR_MIPMAP_NEAREST;
    case AGPU_FILTER_MIN_LINEAR_MAG_LINEAR_MIPMAP_LINEAR:       return GL_LINEAR_MIPMAP_LINEAR;
    case AGPU_FILTER_ANISOTROPIC:                               return GL_LINEAR_MIPMAP_LINEAR;
    default:
        return GL_NEAREST;
    }
}

inline GLenum mapAddressMode(agpu_texture_address_mode mode)
{
    switch (mode)
    {
    default:
    case AGPU_TEXTURE_ADDRESS_MODE_WRAP:    return GL_REPEAT;
    case AGPU_TEXTURE_ADDRESS_MODE_MIRROR:  return GL_MIRRORED_REPEAT;
    case AGPU_TEXTURE_ADDRESS_MODE_CLAMP:   return GL_CLAMP_TO_EDGE;
    case AGPU_TEXTURE_ADDRESS_MODE_BORDER:  return GL_CLAMP;
    case AGPU_TEXTURE_ADDRESS_MODE_MIRROR_ONCE: return GL_MIRROR_CLAMP_TO_EDGE;
    }
}

_agpu_shader_resource_binding::_agpu_shader_resource_binding()
{
}

void _agpu_shader_resource_binding::lostReferences()
{
    for(auto &binding : uniformBuffers)
    {
        if (binding.buffer)
            binding.buffer->release();
    }

    for(auto &binding : textures)
    {
        if(binding.texture)
            binding.texture->release();
    }

    if(!samplers.empty())
    {
        device->onMainContextBlocking([&]{
            device->glDeleteSamplers(samplers.size(), &samplers[0]);
        });
    }
}

agpu_shader_resource_binding *_agpu_shader_resource_binding::create(agpu_shader_signature *signature, int elementIndex)
{
	std::unique_ptr<agpu_shader_resource_binding> binding(new agpu_shader_resource_binding());
	binding->device = signature->device;
    binding->signature = signature;
    signature->retain();
	binding->elementIndex = elementIndex;

    auto &element = signature->elements[elementIndex];
    binding->type = element.type;
    binding->startIndex = element.startIndex;

    switch (binding->type)
    {
    case AGPU_SHADER_BINDING_TYPE_SAMPLED_IMAGE:
        binding->textures.resize(element.bindingPointCount);
        break;
    case AGPU_SHADER_BINDING_TYPE_UNIFORM_BUFFER:
        binding->uniformBuffers.resize(element.bindingPointCount);
        break;
    case AGPU_SHADER_BINDING_TYPE_SAMPLER:
        binding->samplers.resize(element.bindingPointCount);
        binding->device->onMainContextBlocking([&]{
            binding->device->glGenSamplers(binding->samplers.size(), &binding->samplers[0]);
        });
        break;
    case AGPU_SHADER_BINDING_TYPE_STORAGE_IMAGE:
    default:
        abort();
        break;
    }
	return binding.release();
}

agpu_error _agpu_shader_resource_binding::bindUniformBuffer(agpu_int location, agpu_buffer* uniform_buffer)
{
	if(location < 0)
		return AGPU_OK;
	if(location >= 4)
		return AGPU_ERROR;

    std::unique_lock<std::mutex> l(bindMutex);
	if(uniform_buffer)
		uniform_buffer->retain();
	if(uniformBuffers[location].buffer)
		uniformBuffers[location].buffer->release();
 	uniformBuffers[location].buffer = uniform_buffer;

	uniformBuffers[location].range = false;
	return AGPU_OK;
}

agpu_error _agpu_shader_resource_binding::bindUniformBufferRange(agpu_int location, agpu_buffer* uniform_buffer, agpu_size offset, agpu_size size)
{
	if(location < 0)
		return AGPU_OK;
	if(location >= (int)uniformBuffers.size())
		return AGPU_ERROR;

    std::unique_lock<std::mutex> l(bindMutex);
	if(uniform_buffer)
		uniform_buffer->retain();
	if(uniformBuffers[location].buffer)
		uniformBuffers[location].buffer->release();
 	uniformBuffers[location].buffer = uniform_buffer;

	uniformBuffers[location].range = true;
	uniformBuffers[location].offset = offset;
	uniformBuffers[location].size = size;
	return AGPU_OK;
}

agpu_error _agpu_shader_resource_binding::bindTexture(agpu_int location, agpu_texture* texture, agpu_uint startMiplevel, agpu_int miplevels, agpu_float lodClamp)
{
    if(location < 0)
		return AGPU_OK;
	if(location >= (int)textures.size())
		return AGPU_ERROR;

    std::unique_lock<std::mutex> l(bindMutex);
    auto &binding = textures[location];
    if(texture)
        texture->retain();
    if(binding.texture)
		binding.texture->release();
    binding.texture = texture;

    // Store some of the texture parameters.
    binding.startMiplevel = startMiplevel;
    binding.miplevels = miplevels;
    binding.lodClamp = lodClamp;

    return AGPU_OK;
}

agpu_error _agpu_shader_resource_binding::bindTextureArrayRange(agpu_int location, agpu_texture* texture, agpu_uint startMiplevel, agpu_int miplevels, agpu_int firstElement, agpu_int numberOfElements, agpu_float lodClamp)
{
    return AGPU_UNIMPLEMENTED;
}

agpu_error _agpu_shader_resource_binding::createSampler(agpu_int location, agpu_sampler_description* description)
{
    if(location < 0)
        return AGPU_OK;
    if(location >= (int)samplers.size())
        return AGPU_ERROR;

    auto sampler = samplers[location];
    device->onMainContextBlocking([&]{
        std::unique_lock<std::mutex> l(bindMutex);
        device->glSamplerParameteri(sampler, GL_TEXTURE_MAG_FILTER, mapMagFilter(description->filter));
        device->glSamplerParameteri(sampler, GL_TEXTURE_MIN_FILTER, mapMinFilter(description->filter));
        device->glSamplerParameteri(sampler, GL_TEXTURE_WRAP_S, mapAddressMode(description->address_u));
        device->glSamplerParameteri(sampler, GL_TEXTURE_WRAP_T, mapAddressMode(description->address_v));
        device->glSamplerParameteri(sampler, GL_TEXTURE_WRAP_R, mapAddressMode(description->address_w));
    });

    return AGPU_OK;
}

void _agpu_shader_resource_binding::activate()
{
    std::unique_lock<std::mutex> l(bindMutex);
    if (type == AGPU_SHADER_BINDING_TYPE_SAMPLED_IMAGE)
    {
        for (size_t i = 0; i < textures.size(); ++i)
        {
            auto &binding = textures[i];
            if(!binding.texture)
                continue;

            auto id = startIndex + i;

            auto target = binding.texture->target;
            device->glActiveTexture(GL_TEXTURE0 + id);
            glBindTexture(target, binding.texture->handle);
        }
    }
    else if (type == AGPU_SHADER_BINDING_TYPE_UNIFORM_BUFFER)
    {
        for (size_t i = 0; i < uniformBuffers.size(); ++i)
        {
            auto &binding = uniformBuffers[i];
            if (!binding.buffer)
                continue;

            if (binding.range)
                device->glBindBufferRange(GL_UNIFORM_BUFFER, GLuint(startIndex + i), binding.buffer->handle, binding.offset, binding.size);
            else
                device->glBindBufferBase(GL_UNIFORM_BUFFER, GLuint(startIndex + i), binding.buffer->handle);
        }
    }
    else if(type == AGPU_SHADER_BINDING_TYPE_SAMPLER)
    {
        for (size_t i = 0; i < samplers.size(); ++i)
        {
            auto sampler = samplers[i];
            if(sampler)
                device->glBindSampler(i, sampler);
        }
    }
}


// Exported C interace

AGPU_EXPORT agpu_error agpuAddShaderResourceBindingReference ( agpu_shader_resource_binding* shader_resource_binding )
{
	CHECK_POINTER(shader_resource_binding);
	return shader_resource_binding->retain();
}

AGPU_EXPORT agpu_error agpuReleaseShaderResourceBinding ( agpu_shader_resource_binding* shader_resource_binding )
{
	CHECK_POINTER(shader_resource_binding);
	return shader_resource_binding->release();
}

AGPU_EXPORT agpu_error agpuBindUniformBuffer ( agpu_shader_resource_binding* shader_resource_binding, agpu_int location, agpu_buffer* uniform_buffer )
{
	CHECK_POINTER(shader_resource_binding);
	return shader_resource_binding->bindUniformBuffer(location, uniform_buffer);
}

AGPU_EXPORT agpu_error agpuBindUniformBufferRange ( agpu_shader_resource_binding* shader_resource_binding, agpu_int location, agpu_buffer* uniform_buffer, agpu_size offset, agpu_size size )
{
	CHECK_POINTER(shader_resource_binding);
	return shader_resource_binding->bindUniformBufferRange(location, uniform_buffer, offset, size);
}

AGPU_EXPORT agpu_error agpuBindTexture(agpu_shader_resource_binding* shader_resource_binding, agpu_int location, agpu_texture* texture, agpu_uint startMiplevel, agpu_int miplevels, agpu_float lodclamp)
{
    CHECK_POINTER(shader_resource_binding);
    return shader_resource_binding->bindTexture(location, texture, startMiplevel, miplevels, lodclamp);
}

AGPU_EXPORT agpu_error agpuBindTextureArrayRange(agpu_shader_resource_binding* shader_resource_binding, agpu_int location, agpu_texture* texture, agpu_uint startMiplevel, agpu_int miplevels, agpu_int firstElement, agpu_int numberOfElements, agpu_float lodclamp)
{
    CHECK_POINTER(shader_resource_binding);
    return shader_resource_binding->bindTextureArrayRange(location, texture, startMiplevel, miplevels, firstElement, numberOfElements, lodclamp);
}

AGPU_EXPORT agpu_error agpuCreateSampler(agpu_shader_resource_binding* shader_resource_binding, agpu_int location, agpu_sampler_description* description)
{
    CHECK_POINTER(shader_resource_binding);
    return shader_resource_binding->createSampler(location, description);
}
