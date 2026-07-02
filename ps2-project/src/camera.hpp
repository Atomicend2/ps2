/**
 * @file camera.hpp
 * @brief Third-person orbital camera for PlayStation 2 3D rendering
 */

#ifndef SEVENTH_VOW_CAMERA_HPP
#define SEVENTH_VOW_CAMERA_HPP

#include <tyra>

namespace TheSeventhVow {

class Camera {
public:
    Camera();
    ~Camera();

    /**
     * @brief Initialize default camera distances, angles, and offsets
     */
    void init();

    /**
     * @brief Update orbital angles using right analog stick inputs and re-calculate position
     * @param rightJoyX Normalised right joystick X value [-1.0f, 1.0f]
     * @param rightJoyY Normalised right joystick Y value [-1.0f, 1.0f]
     * @param targetPos Position of the player model (Xyven) to look at
     * @param deltaTime Elapsed frame time in seconds
     */
    void update(float rightJoyX, float rightJoyY, const Tyra::Vec4& targetPos, float deltaTime);

    /**
     * @brief Generate the 4x4 View Matrix representing the camera's frame of reference
     */
    Tyra::M4x4 getViewMatrix() const;

    // Getters and setters
    const Tyra::Vec4& getPosition() const { return position; }
    const Tyra::Vec4& getTarget() const { return target; }
    float getDistance() const { return distance; }
    void setDistance(float d) { distance = d; }

private:
    Tyra::Vec4 position;
    Tyra::Vec4 target;
    Tyra::Vec4 up;
    
    float distance; // Orbit radius
    float yaw;      // Horizontal angle around player
    float pitch;    // Vertical angle around player

    Tyra::Vec4 lookAtOffset; // Look-at height offset above player origin
};

} // namespace TheSeventhVow

#endif // SEVENTH_VOW_CAMERA_HPP
