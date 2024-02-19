#pragma once

#include "Runtime/Renderer/Public/VariableRateShadingImageManager.h"
#include "Runtime/Renderer/Private/VariableRateShading/ContrastAdaptiveImageGenerator.h"


class FNvidiaOFAImageGeneration : public FContrastAdaptiveImageGenerator
{
public:

	virtual ~FNvidiaOFAImageGeneration() = default;
	
	// Generates image(s) and saves to generator cache. Should only be run once per view per frame, in Render().
	virtual void PrepareImages(FRDGBuilder& GraphBuilder, const FSceneViewFamily& ViewFamily, const FMinimalSceneTextures& SceneTextures) override;

	// Returns whether or not generator is enabled - can change at runtime
	virtual bool IsEnabledForView(const FSceneView& View) const override;

	// Return bitmask of generator type
	virtual FVariableRateShadingImageManager::EVRSSourceType GetType() const { return FVariableRateShadingImageManager::EVRSSourceType::None; };

	// Get VRS image to be used w/ debug overlay
	virtual FRDGTextureRef GetDebugImage(FRDGBuilder& GraphBuilder, const FViewInfo& ViewInfo, FVariableRateShadingImageManager::EVRSImageType ImageType) override;

};