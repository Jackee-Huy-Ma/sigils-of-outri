#version 330 core
out vec4 FragColor;

in Vec4 vertexColor;

void main() {
    FragColor = vertexColor;
}