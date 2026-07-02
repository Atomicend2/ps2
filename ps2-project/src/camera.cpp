/**
 * @file camera.cpp
 * @brief Implementing third-person orbital camera physics and look-at transformations for the PS2
 */

#include "camera.hpp"
#include <cmath>

namespace TheSeventhVow {

Camera::Camera() {
    init();
}

Camera::~Camera() {}

void Camera::init() {
    distance = 18.0f;
    yaw = 0.0f;       // Radians
    pitch = 0.4f;     // Radians (slight overhead angle)
    
    // Look-at height offset (roughly shoulder level for standard OBJ models)
    lookAtOffset.set(0.0f, 3.5f, 0.0f, 1.0f);
    
    // Up vector
    up.set(0.0f, 1.0f, 0.0f, 0.0f);
    
    // Default positions
    position.set(0.0f, 5.0f, -18.0f, 1.0f);
    target.set(0.0f, 3.5f, 0.0f, 1.0f);
}

void Camera::update(float rightJoyX, float rightJoyY, const Tyra::Vec4& targetPos, float deltaTime) {
    // 1. Process analog stick orbits
    // In Tyra, input joystick values are centered, so rightJoyX/rightJoyY are pre-normalized inputs
    const float orbitSpeed = 2.5f; // Rads per second
    
    yaw += rightJoyX * orbitSpeed * deltaTime;
    pitch += rightJoyY * orbitSpeed * deltaTime;

    // 2. Clamp vertical pitch to prevent flipping overhead (gimbal lock)
    const float minPitch = -0.3f; // Look slightly from below
    const float maxPitch = 1.3f;  // Look down from high above
    if (pitch < minPitch) pitch = minPitch;
    if (pitch > maxPitch) pitch = maxPitch;

    // 3. Compute target look-at vector (player position + height offset)
    target.x = targetPos.x + lookAtOffset.x;
    target.y = targetPos.y + lookAtOffset.y;
    target.z = targetPos.z + lookAtOffset.z;

    // 4. Calculate camera coordinates using spherical coordinates orbiting the target
    // x = target.x + R * cos(pitch) * sin(yaw)
    // y = target.y + R * sin(pitch)
    // z = target.z + R * cos(pitch) * cos(yaw)
    float cosPitch = std::cos(pitch);
    float sinPitch = std::sin(pitch);
    float cosYaw = std::cos(yaw);
    float sinYaw = std::sin(yaw);

    position.x = target.x + distance * cosPitch * sinYaw;
    position.y = target.y + distance * sinPitch;
    position.z = target.z + distance * cosPitch * cosYaw;
    position.w = 1.0f;
}

Tyra::M4x4 Camera::getViewMatrix() const {
    // Manual construction of standard look-at matrix for complete toolchain safety
    // Z-axis: forward vector pointing from target to camera (right-handed view space)
    Tyra::Vec4 zAxis = position - target;
    
    // Custom robust normalization
    float zLen = std::sqrt(zAxis.x * zAxis.x + zAxis.y * zAxis.y + zAxis.z * zAxis.z);
    if (zLen > 0.0001f) {
        zAxis.x /= zLen;
        zAxis.y /= zLen;
        zAxis.z /= zLen;
    }
    zAxis.w = 0.0f;

    // X-axis: cross product of global UP and Z-axis (Right direction)
    Tyra::Vec4 xAxis;
    xAxis.x = up.y * zAxis.z - up.z * zAxis.y;
    xAxis.y = up.z * zAxis.x - up.x * zAxis.z;
    xAxis.z = up.x * zAxis.y - up.y * zAxis.x;
    xAxis.w = 0.0f;

    float xLen = std::sqrt(xAxis.x * xAxis.x + xAxis.y * xAxis.y + xAxis.z * xAxis.z);
    if (xLen > 0.0001f) {
        xAxis.x /= xLen;
        xAxis.y /= xLen;
        xAxis.z /= xLen;
    }

    // Y-axis: cross product of Z-axis and X-axis (Local UP)
    Tyra::Vec4 yAxis;
    yAxis.x = zAxis.y * xAxis.z - zAxis.z * xAxis.y;
    yAxis.y = zAxis.z * xAxis.x - zAxis.x * xAxis.z;
    yAxis.z = zAxis.x * xAxis.y - zAxis.y * xAxis.x;
    yAxis.w = 0.0f;

    // Calculate translations (negative dot products of axes and camera position)
    float tx = -(xAxis.x * position.x + xAxis.y * position.y + xAxis.z * position.z);
    float ty = -(yAxis.x * position.x + yAxis.y * position.y + yAxis.z * position.z);
    float tz = -(zAxis.x * position.x + zAxis.y * position.y + zAxis.z * position.z);

    // Populate standard 4x4 Row-Major matrix
    Tyra::M4x4 viewMatrix;
    
    // Row 0
    viewMatrix.data[0] = xAxis.x;
    viewMatrix.data[1] = xAxis.y;
    viewMatrix.data[2] = xAxis.z;
    viewMatrix.data[3] = tx;

    // Row 1
    viewMatrix.data[4] = yAxis.x;
    viewMatrix.data[5] = yAxis.y;
    viewMatrix.data[6] = yAxis.z;
    viewMatrix.data[7] = ty;

    // Row 2
    viewMatrix.data[8] = zAxis.x;
    viewMatrix.data[9] = zAxis.y;
    viewMatrix.data[10] = zAxis.z;
    viewMatrix.data[11] = tz;

    // Row 3
    viewMatrix.data[12] = 0.0f;
    viewMatrix.data[13] = 0.0f;
    viewMatrix.data[14] = 0.0f;
    viewMatrix.data[15] = 1.0f;

    return viewMatrix;
}

} // namespace TheSeventhVow
