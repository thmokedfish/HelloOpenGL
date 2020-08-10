#version 330 core
out vec4 FragColor;
uniform float unifCol;
void main()
{
   FragColor = vec4(1.0f, unifCol, 0.2f, 1.0f);
}