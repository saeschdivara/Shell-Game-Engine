#pragma once

#include <glm/glm.hpp>

namespace Shell {

    class OrthographicCamera {
    public:
        OrthographicCamera(float left, float right, float bottom, float top);

        void SetViewportSize(uint32_t width, uint32_t height);

        [[nodiscard]] const glm::vec3& GetPosition() const { return m_Position; }
        void SetPosition(glm::vec3 pos) { m_Position = pos; RecalculateViewMatrix(); }

        [[nodiscard]] float GetRotation() const { return m_Rotation; }
        void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

        [[nodiscard]] const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
        [[nodiscard]] const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
        [[nodiscard]] const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

    private:
        void RecalculateViewMatrix();

    private:
        glm::mat4 m_ProjectionMatrix;
        glm::mat4 m_ViewMatrix;
        glm::mat4 m_ViewProjectionMatrix;

        glm::vec3 m_Position;
        float m_Rotation = 0.0f;
        float m_OrthographicSize = 10.0f;
        float m_AspectRatio = 0.0f;
    };

}
