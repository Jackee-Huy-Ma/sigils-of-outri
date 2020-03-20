#pragma once
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <unordered_map>

class Shader {
public:
    //Consturctor, takes in program handle
    Shader(GLuint programHandle);

    //Deconstructor
    virtual ~Shader();

    //Please no copying Shader
    Shader(const Shader & other) = delete;
    Shader& operator=(const Shader& other) = delete;

    // Getter for program handle
    GLuint getProgramHandle() const;

    //Sets a uniform int value for shader.
    void setUniform1i(const std::string& name, const int value);

    //Sets uniform float value in shader.
    void setUniform2f(const std::string& name, const glm::vec2 values);

    //Sets uniform vector with three values in the shader
    void setUniform3f(const std::string& name, const glm::vec3 values);

    //Sets uniform vector with four values in the shader
    void setUniform4f(const std::string& name, const glm::vec4 values);

    //Sets a uniform 4x4 matrix in the shader
    void setUniformMatrix4v(const std::string& name, const glm::mat4 &matrux);

private:
    int getUniformLocation(const std::string& uniformName);

    //Program number of compiled shader
    GLuint m_programHandle;

    //caching shaders' uniform location
    std::unordered_map<std::string, int> m_uniformMap;
};