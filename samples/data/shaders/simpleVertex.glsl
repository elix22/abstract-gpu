#version 420

layout(std140, binding=0) uniform TransformationBuffer
{
    mat4 projectionMatrix;
    mat4 modelMatrix;
    mat4 viewMatrix;
};

in vec3 vPosition;
in vec4 vColor;

out vec4 fColor;

void main()
{
    fColor = vColor;
    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vPosition, 1.0);
}
