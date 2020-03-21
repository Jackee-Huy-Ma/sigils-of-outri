#include "Shader.h"

Shader::Shader(const char * vertexPath, const char * fragmentPath) {
    //Get the code from a shader file
    //Store data in these strings 
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    //Deal with exceptions
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    //Try catch when peforming I/O
    try {
        //Open file
        vShaderFile.open(vertexPath);
        fShaderFile.open(fragmentPath);
        
        //Stream used for processing strings
        std::stringstream vShaderStream;
        std::stringstream fShaderStream;

        //Read file then buffer the contents
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();

        //Close file handlers
        vShaderFile.close();
        fShaderFile.close();

        //convert stream to strings
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();
    }
    catch(std::ifstream::failure e) {
        std::cout << "ERROR::SHADER::FILE_NOT_READ" << std::endl;
    }

    // Pointer to a char. Converted string to array of chars.
    const char * vShaderCode = vertexCode.c_str();
    const char * fShaderCode = fragmentCode.c_str();

    //Compile shaders
    GLuint vertex;
    GLuint fragment;
    int success;
    char infoLog[512];

    //Vertex Shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);

    //Print error messages from vertex shader
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);

    if(!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::FAIL_COMPILATION\n" << infoLog << std::endl;
    };

    //Fragment Shader
    fragment = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    //Print error messages from fragment shader
    if(!success) {
        glGetShaderInfoLog(vertex, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::FAIL_COMPILATION\n" << infoLog << std::endl;
    }

    //Shader Program
    programHandle = glCreateProgram();
    glAttachShader(programHandle, vertex);
    glAttachShader(programHandle, fragment);
    glLinkProgram(programHandle);

    //Print error messages from Shader Program
    glGetProgramiv(programHandle, GL_LINK_STATUS, &success);

    if(!success) {
        glGetProgramInfoLog(programHandle, 512, NULL, infoLog);
        std::cout << "ERROR::PROGRAM::LINK_FAILED\n" << infoLog << std::endl;
    }

    //delete the shaders because already linked to program
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void::Shader::use() {
    glUseProgram(programHandle);
}

void::Shader::setBool(const std::string & name, bool value) const {
    glUniform1i(glGetUniformLocation(programHandle, name.c_str()), (int)value); 
}

void::Shader::setInt(const std::string & name, int value) const {
    glUniform1i(glGetUniformLocation(programHandle, name.c_str()), value); 
}
void::Shader::setFloat(const std::string & name, float value) const {
    glUniform1f(glGetUniformLocation(programHandle, name.c_str()), value); 
}