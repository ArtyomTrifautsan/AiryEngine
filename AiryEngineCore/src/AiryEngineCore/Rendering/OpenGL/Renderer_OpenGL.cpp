#include "AiryEngineCore/Rendering/OpenGL/Renderer_OpenGL.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/trigonometric.hpp>

#include <memory>

#include "AiryEngineCore/Camera.hpp"
#include "AiryEngineCore/Log.hpp"
#include "AiryEngineCore/Scene/Model3D.hpp"

#include "AiryEngineCore/Rendering/OpenGL/Mesh.hpp"
#include "AiryEngineCore/Rendering/OpenGL/ShaderProgram.hpp"
#include "AiryEngineCore/Rendering/OpenGL/VertexBuffer.hpp"
#include "AiryEngineCore/Rendering/OpenGL/IndexBuffer.hpp"
#include "AiryEngineCore/Rendering/OpenGL/VertexArray.hpp"
#include "AiryEngineCore/Rendering/OpenGL/Texture2D.hpp"


namespace AiryEngine {

    float background_color[4] = {0.33f, 0.33f, 0.33f, 0.f};

    bool Renderer_OpenGL::init(GLFWwindow* window)
    {
        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
        {
            LOG_CRITICAL("Failed to initialize GLAD");
            return false;
        }

        LOG_INFO("OpenGL context initializited:");
        LOG_INFO("  Vendor: {}", get_vendor_str());
        LOG_INFO("  Renderer: {}", get_renderer_str());
        LOG_INFO("  Version: {}", get_version_str());

        return true;
    }

    void Renderer_OpenGL::before_render()
    {
        set_clear_color(
            background_color[0],
            background_color[1],
            background_color[2],
            background_color[3]
        );
        clear();
    }

    // void Renderer_OpenGL::render_model3D(class Camera& camera, 
    //                         std::shared_ptr<Model3D> model, 
    //                         std::shared_ptr<ShaderProgram> shader_program, 
    //                         const glm::vec3& light_source_position, 
    //                         const glm::vec3& light_source_color)
    // {
    //     std::vector<std::shared_ptr<Mesh>> model_meshes = model->get_meshes();
    //     for (std::shared_ptr<Mesh> current_mesh : model_meshes) 
    //         render_mesh(camera, current_mesh, shader_program, light_source_position, light_source_color);
    // }

    // void Renderer_OpenGL::render_mesh(class Camera& camera, 
    //                     std::shared_ptr<Mesh> mesh,
    //                     std::shared_ptr<ShaderProgram> shader_program, 
    //                     const glm::vec3& light_source_position, 
    //                     const glm::vec3& light_source_color)
    // {
    //     std::shared_ptr<Material> mesh_material = mesh->get_material();

    //     // mesh->get_texture()->bind(0);
    //     shader_program->bind();
    //     mesh->get_vertex_array()->bind();

    //     shader_program->set_matrix4("view_projection_matrix", camera.get_projection_matrix() * camera.get_view_matrix());
    //     shader_program->set_vec3("camera_position", camera.get_camera_position());
    //     shader_program->set_vec3("light_position", light_source_position);
    //     shader_program->set_vec3("light_color", light_source_color);
    //     // shader_program->set_float("ambient_factor", mesh->get_ambiant_factor());
    //     // shader_program->set_float("diffuse_factor",  mesh->get_diffuse_factor());
    //     // shader_program->set_float("specular_factor",  mesh->get_specular_factor());
    //     // shader_program->set_float("shininess",  mesh->get_shininess());
    //     // LOG_INFO("  ambient_color=({0}, {1}, {2})", mesh_material->ambient_color[0], mesh_material->ambient_color[1], mesh_material->ambient_color[2]);
    //     shader_program->set_vec3("ambient_color", mesh_material->ambient_color);
    //     // LOG_INFO("  diffuse_color=({0}, {1}, {2})", mesh_material->diffuse_color[0], mesh_material->diffuse_color[1], mesh_material->diffuse_color[2]);
    //     shader_program->set_vec3("diffuse_color", mesh_material->diffuse_color);
    //     // LOG_INFO("  specular_color=({0}, {1}, {2})", mesh_material->specular_color[0], mesh_material->specular_color[1], mesh_material->specular_color[2]);
    //     shader_program->set_vec3("specular_color", mesh_material->specular_color);
    //     shader_program->set_float("shininess",  mesh_material->shininess);

    //     float scale[3] = {0};
    //     float rotate[3] = {0};
    //     float translate[3] = {0};
    //     mesh->get_scale(scale);
    //     mesh->get_rotate(rotate);
    //     mesh->get_translate(translate);

    //     glm::mat4 scale_matrix(
    //         scale[0], 0,        0,        0,
    //         0,        scale[1], 0,        0,
    //         0,        0,        scale[2], 0,
    //         0,        0,        0,        1
    //     );

    //     float rotate_x_in_radians = glm::radians(rotate[0]);
    //     glm::mat4 rotate_x_matrix(
    //          1,  0,                        0,                        0,
    //          0,  cos(rotate_x_in_radians), sin(rotate_x_in_radians), 0,
    //          0, -sin(rotate_x_in_radians), cos(rotate_x_in_radians), 0,
    //          0,  0,                        0,                        1
    //     );

    //     float rotate_y_in_radians = glm::radians(rotate[1]);
    //     glm::mat4 rotate_y_matrix(
    //          cos(rotate_y_in_radians), 0, -sin(rotate_y_in_radians), 0,
    //          0,                        1,  0,                        0,
    //          sin(rotate_y_in_radians), 0,  cos(rotate_y_in_radians), 0,
    //          0,                        0,  0,                        1
    //     );

    //     float rotate_z_in_radians = glm::radians(rotate[2]);
    //     glm::mat4 rotate_z_matrix(
    //          cos(rotate_z_in_radians), sin(rotate_z_in_radians), 0, 0,
    //         -sin(rotate_z_in_radians), cos(rotate_z_in_radians), 0, 0,
    //          0,                      0,                      1, 0,
    //          0,                      0,                      0, 1
    //     );

    //     glm::mat4 rotate_matrix = rotate_z_matrix * rotate_y_matrix * rotate_x_matrix;

    //     glm::mat4 translate_matrix(
    //         1,            0,            0,            0,
    //         0,            1,            0,            0,
    //         0,            0,            1,            0,  
    //         translate[0], translate[1], translate[2], 1
    //     );

    //     glm::mat4 model_matrix = translate_matrix * rotate_matrix * scale_matrix;
    //     shader_program->set_matrix4("model_matrix", model_matrix);

    //     Renderer_OpenGL::draw_vertex_elements(*mesh->get_vertex_array());
        
    //     mesh->get_vertex_array()->unbind();
    // }

    // void Renderer_OpenGL::render_light_model3D(class Camera& camera, 
    //                         std::shared_ptr<Model3D> model, 
    //                         std::shared_ptr<ShaderProgram> shader_program, 
    //                         const glm::vec3& light_source_position, 
    //                         const glm::vec3& light_source_color)
    // {
    //     std::vector<std::shared_ptr<Mesh>> model_meshes = model->get_meshes();
    //     for (std::shared_ptr<Mesh> current_mesh : model_meshes) 
    //         render_light_mesh(camera, current_mesh, shader_program, light_source_position, light_source_color);
    // }

    // void Renderer_OpenGL::render_light_mesh(class Camera& camera, 
    //                     std::shared_ptr<Mesh> mesh,
    //                     std::shared_ptr<ShaderProgram> shader_program, 
    //                     const glm::vec3& light_source_position, 
    //                     const glm::vec3& light_source_color)
    // {
    //     // std::shared_ptr<Material> mesh_material = mesh->get_material();

    //     shader_program->bind();
    //     mesh->get_vertex_array()->bind();

    //     shader_program->set_matrix4("view_projection_matrix", camera.get_projection_matrix() * camera.get_view_matrix());
    //     shader_program->set_vec3("light_color", light_source_color);

    //     float scale[3];
    //     float rotate[3];
    //     float translate[3];
    //     mesh->get_scale(scale);
    //     mesh->get_rotate(rotate);
    //     mesh->get_translate(translate);

    //     glm::mat4 scale_matrix(
    //         scale[0], 0,        0,        0,
    //         0,        scale[1], 0,        0,
    //         0,        0,        scale[2], 0,
    //         0,        0,        0,        1
    //     );
            
    //     float rotate_x_in_radians = glm::radians(rotate[0]);
    //     glm::mat4 rotate_x_matrix(
    //          1,  0,                        0,                        0,
    //          0,  cos(rotate_x_in_radians), sin(rotate_x_in_radians), 0,
    //          0, -sin(rotate_x_in_radians), cos(rotate_x_in_radians), 0,
    //          0,  0,                        0,                        1
    //     );

    //     float rotate_y_in_radians = glm::radians(rotate[1]);
    //     glm::mat4 rotate_y_matrix(
    //          cos(rotate_y_in_radians), 0, -sin(rotate_y_in_radians), 0,
    //          0,                        1,  0,                        0,
    //          sin(rotate_y_in_radians), 0,  cos(rotate_y_in_radians), 0,
    //          0,                        0,  0,                        1
    //     );

    //     float rotate_z_in_radians = glm::radians(rotate[2]);
    //     glm::mat4 rotate_z_matrix(
    //          cos(rotate_z_in_radians), sin(rotate_z_in_radians), 0, 0,
    //         -sin(rotate_z_in_radians), cos(rotate_z_in_radians), 0, 0,
    //          0,                      0,                      1, 0,
    //          0,                      0,                      0, 1
    //     );

    //     glm::mat4 rotate_matrix = rotate_z_matrix * rotate_y_matrix * rotate_x_matrix;

    //     glm::mat4 translate_matrix(
    //         1,            0,            0,            0,
    //         0,            1,            0,            0,
    //         0,            0,            1,            0,  
    //         translate[0], translate[1], translate[2], 1
    //     );

    //     glm::mat4 model_matrix = translate_matrix * rotate_matrix * scale_matrix;
    //     shader_program->set_matrix4("model_matrix", model_matrix);

    //     Renderer_OpenGL::draw_vertex_elements(*mesh->get_vertex_array());
        
    //     mesh->get_vertex_array()->unbind();
    // }

    void Renderer_OpenGL::draw_vertex_elements(const VertexArray& vertex_array)
    {
        vertex_array.bind();
        glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(vertex_array.get_indices_count()), GL_UNSIGNED_INT, nullptr);
    }

    void Renderer_OpenGL::set_clear_color(const float r, const float g, const float b, const float a) { glClearColor(r, g, b, a); }

    void Renderer_OpenGL::clear() { glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); }

    void Renderer_OpenGL::set_viewport(
        const unsigned int width, 
        const unsigned int height, 
        const unsigned int left_offset, 
        const unsigned bottom_offset
    ) { glViewport(left_offset, bottom_offset, width, height); }

    void Renderer_OpenGL::enable_depth_testing() { glEnable(GL_DEPTH_TEST); }

    void Renderer_OpenGL::disable_depth_testing() { glDisable(GL_DEPTH_TEST); }

    const char* Renderer_OpenGL::get_vendor_str() { return reinterpret_cast<const char*>(glGetString(GL_VENDOR)); }

    const char* Renderer_OpenGL::get_renderer_str() { return reinterpret_cast<const char*>(glGetString(GL_RENDERER)); }
    
    const char* Renderer_OpenGL::get_version_str() { return reinterpret_cast<const char*>(glGetString(GL_VERSION)); }

}