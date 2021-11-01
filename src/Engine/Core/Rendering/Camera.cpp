#include "Camera.h"

#include "Engine/Core/Profiling.h"

#include <glm/ext.hpp>

namespace Shell {
    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
        : m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)),
          m_ViewMatrix(1.0f),
          m_ViewProjectionMatrix(m_ProjectionMatrix * m_ViewMatrix),
          m_Position(0.0f)
    {
    }

    void OrthographicCamera::SetViewportSize(uint32_t width, uint32_t height) {
        OPTICK_EVENT();

        SHELL_CORE_ASSERT(width > 0 && height > 0);
        m_AspectRatio = (float)width / (float)height;
        RecalculateViewMatrix();
    }

    void OrthographicCamera::RecalculateViewMatrix() {
        OPTICK_EVENT();

        glm::mat4 transform = glm::translate(glm::mat4(1), m_Position) *
                              glm::rotate(glm::mat4(1), glm::radians(m_Rotation), glm::vec3(0, 0, 1));

        m_ViewMatrix = glm::inverse(transform);

        float orthoLeft = -m_OrthographicSize * m_AspectRatio * 0.5f;
        float orthoRight = m_OrthographicSize * m_AspectRatio * 0.5f;
        float orthoBottom = -m_OrthographicSize * 0.5f;
        float orthoTop = m_OrthographicSize * 0.5f;

        m_ProjectionMatrix = glm::ortho(orthoLeft, orthoRight,
                                  orthoBottom, orthoTop, -1.0f, 1.0f);

        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }
}