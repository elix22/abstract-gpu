#include "framebuffer.hpp"
#include "texture.hpp"

_agpu_framebuffer::_agpu_framebuffer()
{
    depthStencil = nullptr;
    swapChainBuffer = false;
}

void _agpu_framebuffer::lostReferences()
{
    for (size_t i = 0; i < colorBuffers.size(); ++i)
    {
        auto colorBuffer = colorBuffers[i];
        if (colorBuffer)
            colorBuffer->release();
    }

    if (depthStencil)
        depthStencil->release();
}

agpu_framebuffer* agpu_framebuffer::create(agpu_device* device, agpu_uint width, agpu_uint height, agpu_uint colorCount, agpu_texture_view_description* colorViews, agpu_texture_view_description* depthStencilView)
{
    int heapSize = colorCount;
    bool hasDepth = false;
    bool hasStencil = false;
    if (depthStencilView)
    {
        hasDepth = (depthStencilView->subresource_range.usage_flags & AGPU_TEXTURE_FLAG_DEPTH) != 0;
        hasStencil = (depthStencilView->subresource_range.usage_flags & AGPU_TEXTURE_FLAG_STENCIL) != 0;
    }

    // Describe and create a render target view (RTV) descriptor heap.
    ComPtr<ID3D12DescriptorHeap> heap;
    {
        D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
        heapDesc.NumDescriptors = heapSize;
        heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
        heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
        if (FAILED(device->d3dDevice->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&heap))))
            return nullptr;
    }

    // Describe and create a depth stencil view heap.
    ComPtr<ID3D12DescriptorHeap> depthStencilHeap;
    if (depthStencilView != nullptr)
    {
        D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
        heapDesc.NumDescriptors = 1;
        heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_DSV;
        heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
        if (FAILED(device->d3dDevice->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&depthStencilHeap))))
            return nullptr;
    }

    // Create the framebuffer object.
    auto framebuffer = new agpu_framebuffer();
    framebuffer->width = width;
    framebuffer->height = height;
    framebuffer->device = device;
    framebuffer->colorBuffers.resize(colorCount, nullptr);
    framebuffer->hasDepth = hasDepth;
    framebuffer->hasStencil = hasStencil;
    framebuffer->heap = heap;
    framebuffer->depthStencilHeap = depthStencilHeap;
    framebuffer->descriptorSize = device->d3dDevice->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

    framebuffer->colorBufferDescriptors.reserve(colorCount);
    for (agpu_uint i = 0; i < colorCount; ++i)
        framebuffer->colorBufferDescriptors.push_back(framebuffer->getColorBufferCpuHandle(i));

    // Attach the views.
    for (agpu_uint i = 0; i < colorCount; ++i)
        framebuffer->attachColorBuffer(i, &colorViews[i]);
    if (depthStencilView)
        framebuffer->attachDepthStencilBuffer(depthStencilView);

    return framebuffer;
}

agpu_error _agpu_framebuffer::attachColorBuffer(agpu_int index, agpu_texture_view_description* bufferView)
{
    CHECK_POINTER(bufferView);
    auto buffer = bufferView->texture;
    CHECK_POINTER(buffer);
    if ((size_t)index >= colorBuffers.size())
        return AGPU_OUT_OF_BOUNDS;

    // Store the new color buffer.
    buffer->retain();
    if (colorBuffers[index])
        colorBuffers[index]->release();
    colorBuffers[index] = buffer;

    // View description.
    D3D12_RENDER_TARGET_VIEW_DESC viewDesc;
    memset(&viewDesc, 0, sizeof(viewDesc));
    viewDesc.Format = (DXGI_FORMAT)bufferView->format;
    if (buffer->description.sample_count > 1)
        viewDesc.ViewDimension = buffer->description.depthOrArraySize > 1 ? D3D12_RTV_DIMENSION_TEXTURE2DMSARRAY : D3D12_RTV_DIMENSION_TEXTURE2DMS;
    else
        viewDesc.ViewDimension = buffer->description.depthOrArraySize > 1 ? D3D12_RTV_DIMENSION_TEXTURE2DARRAY : D3D12_RTV_DIMENSION_TEXTURE2D;

    // Perform the actual attachment.
    D3D12_CPU_DESCRIPTOR_HANDLE handle(heap->GetCPUDescriptorHandleForHeapStart());
    handle.ptr += index * descriptorSize;
    device->d3dDevice->CreateRenderTargetView(buffer->gpuResource.Get(), nullptr/*&viewDesc*/, handle);
    return AGPU_OK;
}

agpu_error _agpu_framebuffer::attachDepthStencilBuffer(agpu_texture_view_description* bufferView)
{
    CHECK_POINTER(bufferView);
    auto buffer = bufferView->texture;
    CHECK_POINTER(buffer);


    // Store the new depth stencil buffer.
    buffer->retain();
    if (depthStencil)
        depthStencil->release();
    depthStencil = buffer;

    // View description.
    D3D12_DEPTH_STENCIL_VIEW_DESC viewDesc;
    memset(&viewDesc, 0, sizeof(viewDesc));
    viewDesc.Format = (DXGI_FORMAT)bufferView->format;
    if (buffer->description.sample_count > 1)
        viewDesc.ViewDimension = buffer->description.depthOrArraySize > 1 ? D3D12_DSV_DIMENSION_TEXTURE2DMSARRAY : D3D12_DSV_DIMENSION_TEXTURE2DMS;
    else
        viewDesc.ViewDimension = buffer->description.depthOrArraySize > 1 ? D3D12_DSV_DIMENSION_TEXTURE2DARRAY : D3D12_DSV_DIMENSION_TEXTURE2D;

    // Perform the actual attachment.
    device->d3dDevice->CreateDepthStencilView(depthStencil->gpuResource.Get(), nullptr/*&viewDesc*/, depthStencilHeap->GetCPUDescriptorHandleForHeapStart());
    return AGPU_OK;
}

size_t _agpu_framebuffer::getColorBufferCount() const
{
    return colorBuffers.size();
}

D3D12_CPU_DESCRIPTOR_HANDLE _agpu_framebuffer::getColorBufferCpuHandle(size_t i)
{
    auto handle = heap->GetCPUDescriptorHandleForHeapStart();
    handle.ptr += i * descriptorSize;
    return handle;
}

D3D12_CPU_DESCRIPTOR_HANDLE _agpu_framebuffer::getDepthStencilCpuHandle()
{
    return depthStencilHeap->GetCPUDescriptorHandleForHeapStart();
}

// Exported C interface
AGPU_EXPORT agpu_error agpuAddFramebufferReference(agpu_framebuffer* framebuffer)
{
    CHECK_POINTER(framebuffer);
    return framebuffer->retain();
}

AGPU_EXPORT agpu_error agpuReleaseFramebuffer(agpu_framebuffer* framebuffer)
{
    CHECK_POINTER(framebuffer);
    return framebuffer->release();
}
