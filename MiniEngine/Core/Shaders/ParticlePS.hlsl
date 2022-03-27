//
// Copyright (c) Microsoft. All rights reserved.
// This code is licensed under the MIT License (MIT).
// THIS CODE IS PROVIDED *AS IS* WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESS OR IMPLIED, INCLUDING ANY
// IMPLIED WARRANTIES OF FITNESS FOR A PARTICULAR
// PURPOSE, MERCHANTABILITY, OR NON-INFRINGEMENT.
//
// Developed by Minigraph
//
// Author:  James Stanard 
//          Julia Careaga
//

#include "ParticleUpdateCommon.hlsli"
#include "ParticleUtility.hlsli"

Texture2DArray<float4> ColorTex : register(t1);
Texture2D<float> LinearDepthTex : register(t2);

[RootSignature(Particle_RootSig)]
float4 main(ParticleVertexOutput input ) : SV_Target0
{
    float3 uv = float3(input.TexCoord.xy, input.TexID);
    float4 TextureColor = ColorTex.Sample( gSampLinearBorder, uv );
    TextureColor.a *= saturate(1000.0 * (LinearDepthTex[(uint2)input.Pos.xy] - input.LinearZ));
    TextureColor.rgb *= TextureColor.a;

    float4 fogColor;
    fogColor = float4(0.5f, 0.5f, 0.5f,1.0f);

    float3 toEyeW = ViewerPos - input.worldPos;
    float distToEye = length(toEyeW);

    float fogAmount = saturate((distToEye - 5) / 1000);
    float4 FianlColor = TextureColor * input.Color;
    float4 fogData = lerp(FianlColor, fogColor, 0);
    FianlColor.rgb = fogData.rgb;

    return fogData;
}
