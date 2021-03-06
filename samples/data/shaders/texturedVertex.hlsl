cbuffer TransformationBuffer : register(b0)
{
    matrix projectionMatrix;
    matrix modelMatrix;
    matrix viewMatrix;
}

struct VertexInput
{
    float4 position : A;
    float4 color : B;
    float2 texcoord : D;
};

struct VertexOutput
{
    float4 color : COLOR;
    float2 texcoord : TEXCOORD;
    float4 position : SV_POSITION;
};

VertexOutput main(VertexInput input)
{
    VertexOutput output;
    output.color = input.color;
    output.texcoord = input.texcoord;
    output.position = mul(projectionMatrix, mul(viewMatrix, mul(modelMatrix, input.position)));
    return output;
}
