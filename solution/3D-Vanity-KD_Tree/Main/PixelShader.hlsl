// Input Pixel type (struct)
struct PixelShaderObj
{
    float4 position : SV_POSITION;
    float4 color :    COLOR0;
};

/*
 * main()
 * Returns the vertex color
 */
float4 main(PixelShaderObj value) : SV_TARGET
{
    return value.color;
}
