#pragma once

#include <glm/glm.hpp>
#include "BasicShader.h"
#include "../../materials/Material.h"
#include "../../lights/BasicLight.h"
#include "../../lights/DirectionalLight.h"
#include "../../lights/PointLight.h"
#include "../../lights/SpotLight.h"
#include "../../lights/LightScene.h"
#include "../../core/Camera.h"


class TesselatedShader : public BasicShader
{
private:
	static constexpr auto TESS_CTRL_SHADER = "./src/engine/render/shaders/src/tessCtrlShader.glsl";
	static constexpr auto TESS_EVAL_SHADER = "./src/engine/render/shaders/src/tessEvalShader.glsl";

protected:
	void ConstructShader() override;
	void CreateUniforms() override;

public:
	TesselatedShader();
	~TesselatedShader();

	void LoadTessLevels(float outer, float inner);
};

