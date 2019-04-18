#pragma once

#include <glm/glm.hpp>
#include "../../framebuffers/FrameBuffer.h"

struct ShadowmapPassOutput
{
	glm::mat4 directionalLightViewProjMatrix;
	FrameBuffer shadowmapFramebuffer;
};

struct LightingPassOutput
{
	FrameBuffer outputFramebuffer;
};