#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace sage {

/** @brief Camera with orthographic projection matrix. **/
class OrthographicCamera {
public:
    /** @brief Default constructor. **/
    OrthographicCamera() = default;

    /** @brief Contstrutor with params.
     * @details Accept params for ortho projection matrix.
     * @param[in] left Left coordinate of the orthographic frustum
     * @param[in] right Right coordinate of the orthographic frustum
     * @param[in] bottom Bottom coordinate of the orthographic frustum
     * @param[in] top Top coordinate of the orthographic frustum
     * @param[in] near Near plane of the orthographic frustum
     * @param[in] far Far plane coordinate of the orthographic frustum **/
    OrthographicCamera(float left, float right,
                       float bottom, float top,
                       float near = -1.0f, float far = 1.0f);

    /** @brief Destructor. **/
    virtual ~OrthographicCamera();

    /** @brief Getter.
     * @return Reference to ortho projection matrix. **/
    const glm::mat4& getOrthoProjectionMat() const;

    /** @brief Getter.
     * @return Reference to view matrix. **/
    const glm::mat4& getViewMat() const;

    /** @brief Getter.
     * @return Reference to ortho view projection matrix. **/
    const glm::mat4& getOrthoViewProjectionMat() const;

    /** @brief Getter.
     * @return Reference to camera position. **/
    const glm::vec3& getPosition() const;

    /** @brief Getter.
     * @return Get camera rotation. **/
    const float getRotation() const;

    /** @brief Setter.
     * @param[in] pos Set camera position. **/
    void setPosition(const glm::vec3& pos);

    /** @brief Setter.
     * @param[in] rotation Set camera rotation. **/
    void setRotation(float rotation);

private:
    /** @brief Make transformation of ortho view space coordinates. **/
    void updateViewMat();

private:
    glm::mat4 _orthoProjectionMat;
    glm::mat4 _orthoViewProjectionMat; 
    glm::mat4 _viewMat;  //> Space from the camera's point of view

    glm::vec3 _position;  //> Position vector
    float _rotation;      //> Rotation angler
};

}  // namespace sage