#pragma once
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <vector>

class Renderer {
public:
    
    //Creates a renderer, takes in a GLFWwindow for the context.
    Renderer(GLFWwindow * window, int windowWidth, int windowHeight);

    //Deletes the renderer 
    ~Renderer();

    //Sets up shaders for rendering
    void setupShaders();

    //Updates lights from a list
    //TODO implement scene
    void setupLighting();

    //Shadow pass
    void shadowPass();

    //Transparency
    void transparencyPass();

    //Render
    void render();

private:
    //Width of the screen
    int m_width;
    
    //Height of screen
    int m_height;

    //window used for context.
    GLFWwindow * window;

    //Uniform buffer object for camera matrices
    GLuint m_cameraUniformBuffer;

    //ShaderManager Pointer.
    // ShaderManager * m_shaderManager;

    //Pointer to the shadow buffer.
    //std::unique_ptr<ShadowBuffer> m_shadowBuffer;

    //Pointer to the geometry buffer.
    //std::unique_ptr<GeometryBuffer> m_geometryBuffer;

    //Shader Pointers
    /*
    std::shared_ptr<Shader> m_shadowShader;
    std::shared_ptr<Shader> m_geometryShader;
    std::shared_ptr<Shader> m_transparencyShader;
    std::shared_ptr<Shader> m_lightingShader;

    Render quad to frame
    std::unique_ptr<GameObject> m_screenQuad;

    //Vector of all pointlights
    std::vector<std::weak_ptr<PointLight>> m_pointLights;

    //List of all spot lights in the scene.
    std::vector<std::weak_ptr<SpotLight>> m_spotLights;

    //Direction LIght
    std::weak_ptr<DirectionalLight> m_directionalLight;
    */
};