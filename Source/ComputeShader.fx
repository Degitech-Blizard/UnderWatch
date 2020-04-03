struct VS_INPUT
{
	float4 mPositon :POSITION;
	float2 mTexCoord : TEXCOORD0;
};

struct VS_OUTPUT
{
	float4 mPosition :POSITION;
	float2 mTexCoord : TEXCOORD0;
};

float4x4 gWorldMatrix;
float4x4 gViewMatrix;
float4x4 gProjMatrix;
sampler2D gDiffuseSampler;

VS_OUTPUT vs_main(VS_INPUT Input)
{
	VS_OUTPUT Output;
	Output.mPosition = mul(Input.mPosition, gWorldMatrix);
	Output.mPosition = mul(Output.mPosition, gViewMatrix);
	Output.mPosition = mul(Output.mPosition, gProjMatrix);

	Output.mTexCoord = Input.mTexCoord;
	return Output;
}

struct PS_INPUT
{
	float2 mTexCoord : TEXCOORD0;
};

float4 ps_main(PS_INPUT Input) : COLOR
{
	float4 albedo = tex2D(gDiffuseSampler, Input.mTexCoord);
	return albedo.rgba;
}

technique Tech
{
	pass p0
	{
		VertexShader = compile vs_2_0 vs_main(); // 여기 함수이름?
		PixelShader = compile ps_2_0 ps_main();
	}
}
