#ifndef AGPU_METAL_RENDERPASS_HPP
#define AGPU_METAL_RENDERPASS_HPP

#include "device.hpp"
#include <vector>

struct _agpu_renderpass : public Object<agpu_renderpass>
{
public:
    _agpu_renderpass(agpu_device *device);
    void lostReferences();

    static agpu_renderpass *create(agpu_device *device, agpu_renderpass_description *description);

    MTLRenderPassDescriptor *createDescriptor(agpu_framebuffer *framebuffer);
    
    agpu_device *device;
    bool hasDepthStencil;
    agpu_renderpass_depth_stencil_description depthStencil;
    std::vector<agpu_renderpass_color_attachment_description> colorAttachments;
};

#endif //AGPU_METAL_RENDERPASS_HPP
