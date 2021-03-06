#ifndef AGPU_METAL_TEXTURE_FORMAT_HPP
#define AGPU_METAL_TEXTURE_FORMAT_HPP

#include "device.hpp"
#include "../Common/texture_formats_common.hpp"

inline MTLPixelFormat mapTextureFormat(agpu_texture_format format)
{
    switch(format)
    {
	case AGPU_TEXTURE_FORMAT_UNKNOWN: return MTLPixelFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R32G32B32A32_TYPELESS: return MTLPixelFormatRGBA32Uint;
	case AGPU_TEXTURE_FORMAT_R32G32B32A32_FLOAT: return MTLPixelFormatRGBA32Float;
	case AGPU_TEXTURE_FORMAT_R32G32B32A32_UINT: return MTLPixelFormatRGBA32Uint;
	case AGPU_TEXTURE_FORMAT_R32G32B32A32_SINT: return MTLPixelFormatRGBA32Sint;
	case AGPU_TEXTURE_FORMAT_R32G32B32_TYPELESS: return MTLPixelFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R32G32B32_FLOAT: return MTLPixelFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R32G32B32_UINT: return MTLPixelFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R32G32B32_SINT: return MTLPixelFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R16G16B16A16_TYPELESS: return MTLPixelFormatRGBA16Uint;
	case AGPU_TEXTURE_FORMAT_R16G16B16A16_FLOAT: return MTLPixelFormatRGBA16Float;
	case AGPU_TEXTURE_FORMAT_R16G16B16A16_UNORM: return MTLPixelFormatRGBA16Unorm;
	case AGPU_TEXTURE_FORMAT_R16G16B16A16_UINT: return MTLPixelFormatRGBA16Uint;
	case AGPU_TEXTURE_FORMAT_R16G16B16A16_SNORM: return MTLPixelFormatRGBA16Snorm;
	case AGPU_TEXTURE_FORMAT_R16G16B16A16_SINT: return MTLPixelFormatRGBA16Sint;
	case AGPU_TEXTURE_FORMAT_R32G32_TYPELESS: return MTLPixelFormatRG32Uint;
	case AGPU_TEXTURE_FORMAT_R32G32_FLOAT: return MTLPixelFormatRG32Float;
	case AGPU_TEXTURE_FORMAT_R32G32_UINT: return MTLPixelFormatRG32Uint;
	case AGPU_TEXTURE_FORMAT_R32G32_SINT: return MTLPixelFormatRG32Sint;
	case AGPU_TEXTURE_FORMAT_R32G8X24_TYPELESS: return MTLPixelFormatDepth32Float_Stencil8;
	case AGPU_TEXTURE_FORMAT_D32_FLOAT_S8X24_UINT: return MTLPixelFormatDepth32Float_Stencil8;
	case AGPU_TEXTURE_FORMAT_R32_FLOAT_S8X24_TYPELESS: return MTLPixelFormatDepth32Float_Stencil8;
	case AGPU_TEXTURE_FORMAT_X32_TYPELESS_G8X24_UINT: return MTLPixelFormatDepth32Float_Stencil8;
	case AGPU_TEXTURE_FORMAT_R10G10B10A2_TYPELESS: return MTLPixelFormatRGB10A2Uint;
	case AGPU_TEXTURE_FORMAT_R10G10B10A2_UNORM: return MTLPixelFormatRGB10A2Unorm;
	case AGPU_TEXTURE_FORMAT_R10G10B10A2_UINT: return MTLPixelFormatRGB10A2Uint;
	case AGPU_TEXTURE_FORMAT_R11G11B10_FLOAT: return MTLPixelFormatRG11B10Float;
	case AGPU_TEXTURE_FORMAT_R8G8B8A8_TYPELESS: return MTLPixelFormatRGBA8Uint;
	case AGPU_TEXTURE_FORMAT_R8G8B8A8_UNORM: return MTLPixelFormatRGBA8Unorm;
	case AGPU_TEXTURE_FORMAT_R8G8B8A8_UNORM_SRGB: return MTLPixelFormatRGBA8Unorm_sRGB;
	case AGPU_TEXTURE_FORMAT_R8G8B8A8_UINT: return MTLPixelFormatRGBA8Uint;
	case AGPU_TEXTURE_FORMAT_R8G8B8A8_SNORM: return MTLPixelFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R8G8B8A8_SINT: return MTLPixelFormatRGBA8Sint;
	case AGPU_TEXTURE_FORMAT_R16G16_TYPELESS: return MTLPixelFormatRG16Uint;
	case AGPU_TEXTURE_FORMAT_R16G16_FLOAT: return MTLPixelFormatRG16Float;
	case AGPU_TEXTURE_FORMAT_R16G16_UNORM: return MTLPixelFormatRG16Unorm;
	case AGPU_TEXTURE_FORMAT_R16G16_UINT: return MTLPixelFormatRG16Uint;
	case AGPU_TEXTURE_FORMAT_R16G16_SNORM: return MTLPixelFormatRG16Snorm;
	case AGPU_TEXTURE_FORMAT_R16G16_SINT: return MTLPixelFormatRG16Sint;
	case AGPU_TEXTURE_FORMAT_R32_TYPELESS: return MTLPixelFormatR32Float;
	case AGPU_TEXTURE_FORMAT_D32_FLOAT: return MTLPixelFormatDepth32Float;
	case AGPU_TEXTURE_FORMAT_R32_FLOAT: return MTLPixelFormatR32Float;
	case AGPU_TEXTURE_FORMAT_R32_UINT: return MTLPixelFormatR32Uint;
	case AGPU_TEXTURE_FORMAT_R32_SINT: return MTLPixelFormatR32Sint;
	case AGPU_TEXTURE_FORMAT_R24G8_TYPELESS: return MTLPixelFormatDepth32Float_Stencil8;
	case AGPU_TEXTURE_FORMAT_D24_UNORM_S8_UINT: return MTLPixelFormatDepth32Float_Stencil8;
	case AGPU_TEXTURE_FORMAT_R24_UNORM_X8_TYPELESS: return MTLPixelFormatDepth32Float_Stencil8;
	case AGPU_TEXTURE_FORMAT_X24TG8_UINT: return MTLPixelFormatDepth24Unorm_Stencil8;
	case AGPU_TEXTURE_FORMAT_R8G8_TYPELESS: return MTLPixelFormatRG8Uint;
	case AGPU_TEXTURE_FORMAT_R8G8_UNORM: return MTLPixelFormatRG8Unorm;
	case AGPU_TEXTURE_FORMAT_R8G8_UINT: return MTLPixelFormatRG8Uint;
	case AGPU_TEXTURE_FORMAT_R8G8_SNORM: return MTLPixelFormatRG8Snorm;
	case AGPU_TEXTURE_FORMAT_R8G8_SINT: return MTLPixelFormatRG8Sint;
	case AGPU_TEXTURE_FORMAT_R16_TYPELESS: return MTLPixelFormatR16Uint;
	case AGPU_TEXTURE_FORMAT_R16_FLOAT: return MTLPixelFormatR16Float;
	case AGPU_TEXTURE_FORMAT_D16_UNORM: return MTLPixelFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R16_UNORM: return MTLPixelFormatR16Unorm;
	case AGPU_TEXTURE_FORMAT_R16_UINT: return MTLPixelFormatR16Uint;
	case AGPU_TEXTURE_FORMAT_R16_SNORM: return MTLPixelFormatR16Snorm;
	case AGPU_TEXTURE_FORMAT_R16_SINT: return MTLPixelFormatR16Sint;
	case AGPU_TEXTURE_FORMAT_R8_TYPELESS: return MTLPixelFormatR8Uint;
	case AGPU_TEXTURE_FORMAT_R8_UNORM: return MTLPixelFormatR8Unorm;
	case AGPU_TEXTURE_FORMAT_R8_UINT: return MTLPixelFormatR8Uint;
	case AGPU_TEXTURE_FORMAT_R8_SNORM: return MTLPixelFormatR8Snorm;
	case AGPU_TEXTURE_FORMAT_R8_SINT: return MTLPixelFormatR8Sint;
	case AGPU_TEXTURE_FORMAT_A8_UNORM: return MTLPixelFormatA8Unorm;
	case AGPU_TEXTURE_FORMAT_R1_UNORM: return MTLPixelFormatInvalid;
	case AGPU_TEXTURE_FORMAT_BC1_TYPELESS: return MTLPixelFormatInvalid;
	case AGPU_TEXTURE_FORMAT_BC1_UNORM: return MTLPixelFormatInvalid;
	case AGPU_TEXTURE_FORMAT_BC1_UNORM_SRGB: return MTLPixelFormatInvalid;
	case AGPU_TEXTURE_FORMAT_BC2_TYPELESS: return MTLPixelFormatInvalid;
	case AGPU_TEXTURE_FORMAT_BC2_UNORM: return MTLPixelFormatInvalid;
	case AGPU_TEXTURE_FORMAT_BC2_UNORM_SRGB: return MTLPixelFormatInvalid;
	case AGPU_TEXTURE_FORMAT_BC3_TYPELESS: return MTLPixelFormatInvalid;
	case AGPU_TEXTURE_FORMAT_BC3_UNORM: return MTLPixelFormatInvalid;
	case AGPU_TEXTURE_FORMAT_BC3_UNORM_SRGB: return MTLPixelFormatInvalid;
	case AGPU_TEXTURE_FORMAT_BC4_TYPELESS: return MTLPixelFormatInvalid;
	case AGPU_TEXTURE_FORMAT_BC4_UNORM: return MTLPixelFormatInvalid;
	case AGPU_TEXTURE_FORMAT_BC4_SNORM: return MTLPixelFormatInvalid;
	case AGPU_TEXTURE_FORMAT_BC5_TYPELESS: return MTLPixelFormatInvalid;
	case AGPU_TEXTURE_FORMAT_BC5_UNORM: return MTLPixelFormatInvalid;
	case AGPU_TEXTURE_FORMAT_BC5_SNORM: return MTLPixelFormatInvalid;
	case AGPU_TEXTURE_FORMAT_B5G6R5_UNORM: return MTLPixelFormatInvalid;
	case AGPU_TEXTURE_FORMAT_B5G5R5A1_UNORM: return MTLPixelFormatInvalid;
	case AGPU_TEXTURE_FORMAT_B8G8R8A8_UNORM: return MTLPixelFormatBGRA8Unorm;
	case AGPU_TEXTURE_FORMAT_B8G8R8X8_UNORM: return MTLPixelFormatBGRA8Unorm;
	case AGPU_TEXTURE_FORMAT_B8G8R8A8_TYPELESS: return MTLPixelFormatBGRA8Unorm;
	case AGPU_TEXTURE_FORMAT_B8G8R8A8_UNORM_SRGB: return MTLPixelFormatBGRA8Unorm_sRGB;
	case AGPU_TEXTURE_FORMAT_B8G8R8X8_TYPELESS: return MTLPixelFormatBGRA8Unorm;
	case AGPU_TEXTURE_FORMAT_B8G8R8X8_UNORM_SRGB: return MTLPixelFormatBGRA8Unorm_sRGB;
    default: return MTLPixelFormatInvalid;
    }
}

inline MTLVertexFormat mapVertexFormat(agpu_texture_format format)
{
    switch(format)
    {
    case AGPU_TEXTURE_FORMAT_UNKNOWN: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R32G32B32A32_TYPELESS: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R32G32B32A32_FLOAT: return MTLVertexFormatFloat4;
	case AGPU_TEXTURE_FORMAT_R32G32B32A32_UINT: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R32G32B32A32_SINT: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R32G32B32_TYPELESS: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R32G32B32_FLOAT: return MTLVertexFormatFloat3;
	case AGPU_TEXTURE_FORMAT_R32G32B32_UINT: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R32G32B32_SINT: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R16G16B16A16_TYPELESS: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R16G16B16A16_FLOAT: return MTLVertexFormatHalf4;
	case AGPU_TEXTURE_FORMAT_R16G16B16A16_UNORM: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R16G16B16A16_UINT: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R16G16B16A16_SNORM: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R16G16B16A16_SINT: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R32G32_TYPELESS: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R32G32_FLOAT: return MTLVertexFormatFloat2;
	case AGPU_TEXTURE_FORMAT_R32G32_UINT: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R32G32_SINT: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R32G8X24_TYPELESS: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_D32_FLOAT_S8X24_UINT: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R32_FLOAT_S8X24_TYPELESS: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_X32_TYPELESS_G8X24_UINT: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R10G10B10A2_TYPELESS: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R10G10B10A2_UNORM: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R10G10B10A2_UINT: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R11G11B10_FLOAT: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R8G8B8A8_TYPELESS: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R8G8B8A8_UNORM: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R8G8B8A8_UNORM_SRGB: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R8G8B8A8_UINT: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R8G8B8A8_SNORM: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R8G8B8A8_SINT: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R16G16_TYPELESS: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R16G16_FLOAT: return MTLVertexFormatHalf2;
	case AGPU_TEXTURE_FORMAT_R16G16_UNORM: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R16G16_UINT: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R16G16_SNORM: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R16G16_SINT: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R32_TYPELESS: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_D32_FLOAT: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R32_FLOAT: return MTLVertexFormatFloat;
	case AGPU_TEXTURE_FORMAT_R32_UINT: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R32_SINT: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R24G8_TYPELESS: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_D24_UNORM_S8_UINT: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R24_UNORM_X8_TYPELESS: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_X24TG8_UINT: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R8G8_TYPELESS: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R8G8_UNORM: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R8G8_UINT: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R8G8_SNORM: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R8G8_SINT: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R16_TYPELESS: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R16_FLOAT: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_D16_UNORM: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R16_UNORM: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R16_UINT: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R16_SNORM: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R16_SINT: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R8_TYPELESS: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R8_UNORM: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R8_UINT: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R8_SNORM: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R8_SINT: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_A8_UNORM: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_R1_UNORM: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_BC1_TYPELESS: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_BC1_UNORM: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_BC1_UNORM_SRGB: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_BC2_TYPELESS: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_BC2_UNORM: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_BC2_UNORM_SRGB: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_BC3_TYPELESS: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_BC3_UNORM: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_BC3_UNORM_SRGB: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_BC4_TYPELESS: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_BC4_UNORM: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_BC4_SNORM: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_BC5_TYPELESS: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_BC5_UNORM: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_BC5_SNORM: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_B5G6R5_UNORM: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_B5G5R5A1_UNORM: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_B8G8R8A8_UNORM: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_B8G8R8X8_UNORM: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_B8G8R8A8_TYPELESS: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_B8G8R8A8_UNORM_SRGB: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_B8G8R8X8_TYPELESS: return MTLVertexFormatInvalid;
	case AGPU_TEXTURE_FORMAT_B8G8R8X8_UNORM_SRGB: return MTLVertexFormatInvalid;
    default: return MTLVertexFormatInvalid;
    }
}

#endif //case AGPU_METAL_TEXTURE_FORMAT_HPP
