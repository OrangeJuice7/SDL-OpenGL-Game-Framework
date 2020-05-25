#include "ModelCamera.hpp"

ModelCamera::ModelCamera(float initialModelScale) {
    this->initialModelScale = initialModelScale;
    reset();
}
ModelCamera::~ModelCamera() {}

float ModelCamera::getScale() const {
    return modelScale;
}
float ModelCamera::getX() const {
    return cameraX;
}
float ModelCamera::getY() const {
    return cameraY;
}

void ModelCamera::reset() {
    modelScale = initialModelScale;
    cameraX = cameraY = 0;
}
void ModelCamera::move(float x, float y) {
    cameraX += x;
    cameraY += y;
}
void ModelCamera::scale(float scale) {
    // Can add some limits to the scale here
    modelScale *= scale;
}
