#pragma once

#include "RenderGraphBuilder.h"
#include "Runtime/Renderer/Public/VariableRateShadingImageManager.h"

// static const TCHAR* ShadingRateTextureName = TEXT("ShadingRateTexture");
// static const TCHAR* ScaledShadingRateTextureName = TEXT("ScaledShadingRateTexture");
// static const TCHAR* ScaledConservativeShadingRateTextureName = TEXT("ConservativeScaledShadingRateTexture");
//
// struct RENDERER_API FVRSTextures
// {
// 	// Returns an FVRSTextures created immutable instance from the builder blackboard. Asserts if none was created.
// 	static const FVRSTextures& Get(FRDGBuilder& GraphBuilder)
// 	{
// 		const FVRSTextures* VRSTextures = GraphBuilder.Blackboard.Get<FVRSTextures>();
// 			checkf(VRSTextures, TEXT("FVRSTextures was unexpectedly not initialized."));
// 		return *VRSTextures;
// 	}
// 	static const bool IsInitialized(FRDGBuilder& GraphBuilder)
// 	{
// 		const FVRSTextures* VRSTextures = GraphBuilder.Blackboard.Get<FVRSTextures>();
// 		return VRSTextures != nullptr;
// 	}
// 	void Create(FRDGBuilder& GraphBuilder, const FSceneViewFamily& ViewFamily)
// 	{
// 		FRDGTextureDesc ConstructedSRIDesc = CreateSRIDesc(ViewFamily, false);
// 		ConstructedSRI = GraphBuilder.CreateTexture(ConstructedSRIDesc, ShadingRateTextureName);
// 		FRDGTextureDesc ScaledSRIDesc = CreateSRIDesc(ViewFamily, true);
// 		ScaledSRI = GraphBuilder.CreateTexture(ScaledSRIDesc, ScaledShadingRateTextureName);
// 		ScaledConservativeSRI = GraphBuilder.CreateTexture(ScaledSRIDesc, ScaledConservativeShadingRateTextureName);
// 	}
// 	FRDGTextureRef ConstructedSRI;
// 	FRDGTextureRef ScaledSRI;
// 	FRDGTextureRef ScaledConservativeSRI;
// private:
// 	static FRDGTextureDesc CreateSRIDesc(const FSceneViewFamily& ViewFamily, bool bIsForDynResScaled)
// 	{
// 		if (bIsForDynResScaled)
// 		{
// 			// Use SceneTextures
// 			return FVariableRateShadingImageManager::GetSRIDesc();
// 		}
// 		else
// 		{
// 			// Get initial size based on luminance texture from previous frame
// 			check(ViewFamily.Views[0]->bIsViewInfo);
// 			const FViewInfo* ViewInfo = static_cast<const FViewInfo*>(ViewFamily.Views[0]);
// 			const FIntPoint ViewTargetExtents = ViewInfo->PrevViewInfo.LuminanceHistory->GetDesc().Extent;
//
// 			const FIntPoint SRIDimensions = FMath::DivideAndRoundUp(ViewTargetExtents, FVariableRateShadingImageManager::GetSRITileSize());
// 			return FRDGTextureDesc::Create2D(
// 				SRIDimensions,
// 				GRHIVariableRateShadingImageFormat,
// 				EClearBinding::ENoneBound,
// 				ETextureCreateFlags::DisableDCC |
// 				ETextureCreateFlags::ShaderResource |
// 				ETextureCreateFlags::UAV);
// 		}
// 	}
// };
// RDG_REGISTER_BLACKBOARD_STRUCT(FVRSTextures);