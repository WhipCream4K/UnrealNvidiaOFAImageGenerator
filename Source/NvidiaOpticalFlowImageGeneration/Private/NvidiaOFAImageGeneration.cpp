#include "..\Public\NvidiaOFAImageGeneration.h"

#include "VRSUtils.h"
#include "Runtime/Renderer/Private/SceneRendering.h"


TAutoConsoleVariable<int32> CVarNvidiaOFAImageGeneration(
	TEXT("r.VRS.NvidiaOFAImageGeneration"),
	0,
	TEXT("Enables using Variable Rate Shading based on the pixel's velocity from the previous frame's post process output with the help of Nvidia OFA \n"),
	ECVF_RenderThreadSafe);

static bool IsNvidiaOFAImageGenerationEnabled()
{
	return CVarNvidiaOFAImageGeneration.GetValueOnRenderThread() != 0;
}

static void AddCreateShadingRateImagePass(FRDGBuilder &GraphBuilder, const FViewInfo &View)
{
	// AddCreateShadingRateImagePass(GraphBuilder, View);
}

static void AddPrepareImageBasedVRSPass(FRDGBuilder &GraphBuilder, const FMinimalSceneTextures &SceneTextures, const FSceneViewFamily &ViewFamily)
{
}

void FNvidiaOFAImageGeneration::PrepareImages(FRDGBuilder& GraphBuilder, const FSceneViewFamily& ViewFamily, const FMinimalSceneTextures& SceneTextures)
{
	RDG_EVENT_SCOPE(GraphBuilder, "NvidiaOFAImageGeneration");
	bool bAreAllViewsVRSCompatible = true;
	for (const FSceneView* View : ViewFamily.Views)
	{
		check(View->bIsViewInfo);
		const FViewInfo* ViewInfo = static_cast<const FViewInfo*>(View);
		if (View->bCameraCut || !FVariableRateShadingImageManager::IsVRSCompatibleWithView(*ViewInfo) || !ViewInfo->PrevViewInfo.LuminanceHistory)
		{
			bAreAllViewsVRSCompatible = false;
			break;
		}
	}
	bool bPrepareImageBasedVRS = IsNvidiaOFAImageGenerationEnabled() && bAreAllViewsVRSCompatible;
	if (!bPrepareImageBasedVRS)
	{
		return;
	}

	
	FVRSTextures& VRSTextures = GraphBuilder.Blackboard.Create<FVRSTextures>();
	VRSTextures.Create(GraphBuilder, ViewFamily);

	for (int32 ViewIndex = 0; ViewIndex < ViewFamily.Views.Num(); ViewIndex++)
	{
		check(ViewFamily.Views[ViewIndex]->bIsViewInfo);
		const FViewInfo& View = *(FViewInfo*)ViewFamily.Views[ViewIndex];
		RDG_GPU_MASK_SCOPE(GraphBuilder, View.GPUMask);
		RDG_EVENT_SCOPE_CONDITIONAL(GraphBuilder, ViewFamily.Views.Num() > 1, "View%d", ViewIndex);
		AddCreateShadingRateImagePass(GraphBuilder, View);
	}
	AddPrepareImageBasedVRSPass(GraphBuilder, SceneTextures, ViewFamily);
}
