//struct VS_INPUT
//{
//	float4 mPosition  : POSITION;
//	float2 mTexCoord : TEXCOORD0;
//};
//
//struct VS_OUTPUT
//{
//	float4 mPosition : POSITION;
//	float2 mTexCoord : TEXCOORD0;
//};
//
float4x4 gWorldMatrix;
float4x4 gViewMatrix;
float4x4 gProjMatrix;
sampler2D gDiffuseSampler;
//
//VS_OUTPUT vs_main(VS_INPUT Input)
//{
//	VS_OUTPUT Output;
//	float4x4 matWorld = gWorldMatrix;
//	matWorld[0].x = mul(matWorld[0].x, 1.15f);
//	matWorld[1].y = mul(matWorld[1].y, 1.15f);
//	matWorld[2].z = mul(matWorld[2].z, 1.15f);
//	Output.mPosition = mul(Input.mPosition, gWorldMatrix);
//	Output.mPosition = mul(Output.mPosition, gViewMatrix);
//	Output.mPosition = mul(Output.mPosition, gProjMatrix);
//
//	Output.mTexCoord = Input.mTexCoord;
//	return Output;
//}
//
//VS_OUTPUT vs_main2(VS_INPUT Input)
//{
//	VS_OUTPUT Output;
//
//	Output.mPosition = mul(Input.mPosition, gWorldMatrix);
//	Output.mPosition = mul(Output.mPosition, gViewMatrix);
//	Output.mPosition = mul(Output.mPosition, gProjMatrix);
//
//	Output.mTexCoord = Input.mTexCoord;
//	return Output;
//}
//
//struct PS_INPUT
//{
//	float2 mTexCoord : TEXCOORD0;
//};
//
//float4 ps_main(PS_INPUT Input) : COLOR
//{
//	float4 albedo = tex2D(gDiffuseSampler, Input.mTexCoord);
//	return float4(0.f,0.f,0.f,1.f);
//}
//float4 ps_main2(PS_INPUT Input) : COLOR
//{
//	float4 albedo = tex2D(gDiffuseSampler, Input.mTexCoord);
//	return albedo.rgba;
//}
//
//
//technique  Tech
//{
//	pass p0
//	{
//		VertexShader = compile vs_2_0 vs_main();
//		PixelShader = compile ps_2_0 ps_main();
//	}
//
//	pass p1
//	{
//		VertexShader = compile vs_2_0 vs_main2();
//		PixelShader = compile ps_2_0 ps_main2();
//	}
//}

//
// Globals
//



struct VS_INPUT
{
	float4 Pos      : POSITION;
	float2 TexCoord : TEXCOORD0; 
	float3 Normal   : NORMAL;
};

struct VS_OUTPUT
{
	float4 Pos      : POSITION;
	float2 TexCoord : TEXCOORD0;
};

VS_OUTPUT vs_main(VS_INPUT In)
{
	VS_OUTPUT Out;

	//Out.Pos.xy = sign(Out.Pos.xy);
	//Out.Pos = float4(In.Pos.xy, 0.0, 1.0);


	//// Image-space
	//Out.TexCoord = In.TexCoord;
	Out.Pos = mul(In.Pos, gWorldMatrix);
	Out.Pos = mul(Out.Pos, gViewMatrix);
	Out.Pos = mul(Out.Pos, gProjMatrix);
	Out.TexCoord.x = In.TexCoord.x + (0.5f * (1 + Out.Pos.x));
	Out.TexCoord.y = In.TexCoord.y + (0.5f * (1 - Out.Pos.y));
	return Out;
}

sampler2D RT;

float mask[9] =
{ -1, -1, -1,
  -1,  8, -1,
  -1, -1, -1 }; // Laplacian Filter

float coord[3] = { -1, 0, +1 };
float divider = 1;
float MAP_CX = 512;
float MAP_CY = 512;

struct PS_INPUT
{
	float2 TexCoord : TEXCOORD0;
};

float4 ps_main(float2 Tex : TEXCOORD0) : COLOR
{
	float4 Color = float4(0.f,0.f,0.f,0.f);
	float4 Ret;
	float3 grayScale = float3(0.3, 0.59, 0.11);

	for (int i = 0; i < 9; i++)
	{
		Color += mask[i] * (tex2D(RT, Tex + float2(coord[i % 3] / MAP_CX, coord[i / 3] / MAP_CY)));
	}
	    float gray = 1 - (Color.r * 0.3 + Color.g * 0.59 + Color.b * 0.11);
	////	float gray = 1 - dot(Color, grayScale);
		Ret = float4(gray, gray, gray, 1) / divider;

	   //Ret = tex2D(gDiffuseSampler, Tex ); // Normal Image
			return Ret.rgba;
}

technique  Tech
{
	pass p0
	{
		VertexShader = compile vs_2_0 vs_main();
		PixelShader = compile ps_2_0 ps_main();
	}
}