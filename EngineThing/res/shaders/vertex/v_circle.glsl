#version 330

layout (location = 0) in vec2 iResolution;
layout (location = 1) in vec2 iPosition;

out vec2 uv;

void main()
{
    float aspect = iResolution.x / iResolution.y;
    uv = gl_FragCoord.xy / iResolution.xy * 2.0 - 1.0;
    uv.x *= aspect;

    vec2 pos = iPosition;
    pos = pos / iResolution.xy * 2.0 - 1.0;
    pos.x *= aspect;
    uv -= pos;

    
}