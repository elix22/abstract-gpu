#ifndef _AGPU_VULKAN_COMMON_HPP
#define _AGPU_VULKAN_COMMON_HPP

#include <AGPU/agpu.h>
#include <stdarg.h>
#include <stdio.h>

#define CHECK_POINTER(pointer) if (!(pointer)) return AGPU_NULL_POINTER;
#define MAKE_CURRENT() if (!makeCurrent) return AGPU_NOT_CURRENT_CONTEXT;
#define CHECK_CURRENT() if (!isCurrentContext()) return AGPU_NOT_CURRENT_CONTEXT;
#define CONVERT_VULKAN_ERROR(error) if(error) return AGPU_ERROR;

void printError(const char *format, ...);

#endif //_AGPU_VULKAN_COMMON_HPP
