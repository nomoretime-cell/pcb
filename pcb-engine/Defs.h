#pragma once

#define ENGINE_NAMESPACE_BEGIN namespace Engine {
#define ENGINE_NAMESPACE_END }

#define VISIONTOOL_NAMESPACE_BEGIN namespace VisionTool {
#define VISIONTOOL_NAMESPACE_END }

// 输入参数
#define _In_

// 输出参数
#define _Out_

struct MvpImage
{
	int	width;
	int height;
	void* imageData;
};