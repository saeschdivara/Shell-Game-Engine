#include "Renderer.h"

#include <glad/glad.h>

namespace Shell {

    Scope<Renderer> Renderer::m_Instance;

    Scope<Renderer> Renderer::Create() {
        return CreateScope<Renderer>();
    }

    Scope<Renderer>& Renderer::Instance() {

        if (!m_Instance) {
            m_Instance = Create();
        }

        return m_Instance;
    }

    void Renderer::AddBatch(RenderBatchUnit batch) {
        m_Batches.push_back(batch);
    }

    void Renderer::RenderBatch() {

        for (const auto &batch: m_Batches) {
            GLint inputColorLocation = glGetUniformLocation(batch.programID, "inputColor");
            if (inputColorLocation != -1) {
                glUniform4f(inputColorLocation, 0.4, 0.4, 0.8, 0.8);
            }

            glUseProgram(batch.programID);

            // 1st attribute buffer : vertices
            glEnableVertexAttribArray(0);
            glBindBuffer(GL_ARRAY_BUFFER, batch.vertexbuffer);
            glVertexAttribPointer(
                    0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                    3,                  // size
                    GL_FLOAT,           // type
                    GL_FALSE,           // normalized?
                    sizeof(float)*3,    // stride
                    (void *) 0          // array buffer offset
            );
            // Draw the triangle !
            glDrawArrays(GL_TRIANGLES, 0, 3); // Starting from vertex 0; 3 vertices total -> 1 triangle
        }
    }
}