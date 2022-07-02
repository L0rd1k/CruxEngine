#include "ortho_camera.h"

namespace sage {

OrthographicCamera::OrthographicCamera(float left, float right,
                                       float bottom, float top,
                                       float near, float far)
    : _orthoProjectionMat(glm::ortho(left, right, bottom, top, near, far)),
      _viewMat(1.0f),
      _position({0.0f, 0.0f, 0.0f}),
      _rotation(0.0f) {
    _orthoViewProjectionMat = _orthoProjectionMat * _viewMat;
}

OrthographicCamera::~OrthographicCamera() {
}

const glm::mat4& OrthographicCamera::getOrthoProjectionMat() const {
    return _orthoProjectionMat;
}

const glm::mat4& OrthographicCamera::getViewMat() const {
    return _viewMat;
}

const glm::mat4& OrthographicCamera::getOrthoViewProjectionMat() const {
    return _orthoViewProjectionMat;
}

const glm::vec3& OrthographicCamera::getPosition() const {
    return _position;
}

const float OrthographicCamera::getRotation() const {
    return _rotation;
}

void OrthographicCamera::setPosition(const glm::vec3& pos) {
    _position = pos;
    updateViewMat();
}

void OrthographicCamera::setRotation(float rotation) {
    _rotation = rotation;
    updateViewMat();
}

void OrthographicCamera::updateViewMat() {
    glm::mat4 transform = glm::translate(glm::mat4(1.0f), _position) *
                          glm::rotate(glm::mat4(1.0f), glm::radians(_rotation), glm::vec3(0, 0, 1));

    _viewMat = glm::inverse(transform);
    _orthoViewProjectionMat = _orthoProjectionMat * _viewMat;
}

}  // namespace sage