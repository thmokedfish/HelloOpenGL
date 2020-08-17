#version 330 core
layout(location=0) in vec3 aPos;
layout(location=1) in vec3 aColor;
out vec3 ourColor;
uniform float move;
void main()
{
   gl_Position = vec4(aPos.x+move, -aPos.y, aPos.z, 1.0);  //输出给gl_Position(vec4类型)
   ourColor = aPos; 
}
