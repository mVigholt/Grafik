#include "camera.h"

/*
 * Default constructor, creates a camera with default values of the defining parameters.
 */
Camera::Camera()
{
    this->vrp = glm::vec3(0.0f, 0.0f, 0.0f);
    this->vpn = glm::vec3(0.0f, 0.0f, 1.0f);
    this->vup = glm::vec3(0.0f, 1.0f, 0.0f);
    this->prp = glm::vec3(8.0f, 6.0f, 84.0f);
    this->lower_left_window  = glm::vec2(-50.0f, -50.0f);
    this->upper_right_window = glm::vec2(50.0f, 50.0f);
    this->front_plane = 60.0f;
    this->back_plane  = 25.0f;
    this->x_viewport  = 0.0f;
    this->y_viewport  = 0.0f;
    this->viewport_width  = 2.0f;
    this->viewport_height = 2.0f;

    this->vieworientationmatrix    = glm::mat4x4(1.0f);
    this->invvieworientationmatrix = glm::mat4x4(1.0f);
    this->ComputeViewOrientation(this->vrp, this->vpn, this->vup);

    this->viewprojectionmatrix     = glm::mat4x4(1.0f);
    this->invviewprojectionmatrix  = glm::mat4x4(1.0f);
    this->ComputeViewProjection(this->prp, this->lower_left_window, this->upper_right_window,
                this->front_plane, this->back_plane);

    this->windowviewportmatrix     = glm::mat4x4(1.0f);
    this->invwindowviewportmatrix  = glm::mat4x4(1.0f);
    this->ComputeWindowViewport(this->x_viewport, this->y_viewport, this->viewport_width, this->viewport_height);

    this->currenttransformationmatrix    = glm::mat4x4(1.0f);
    this->invcurrenttransformationmatrix = glm::mat4x4(1.0f);
}

/* 
 * Parameterized constructor, creates a camere with the parameteres given.
 * \param vrp - a vector which specifies the View Reference Point in world coordinates.
 * \param vpn - a vector which specifies the View Plane Normal in world coordinates.
 * \param vup - a vector which specifies the View Up vector in world coordinates.
 * \param prp - a vector which specifies the Projection Reference Point in eye coordinates.
 * \param lower_left_window - a vector which specifies the lower left corner of the window in eye coordinates.
 * \param upper_right_window - a vector which specifies the upper right corner of the window in eye coordinates.
 * \param front_plane - the z-coordinate of the front clipping plane, relative to vrp, i.e. in eye coordinates.
 * \param back_plane - the z-coordinate of the back clipping plane, relative to vrp, i.e. in eye coordinates.
 * \param x_viewport - the x-coordinate of the viewport on the screen in NDC coordinates.
 * \param y_viewport - the y-coordinate of the viewport on the screen in NDC coordinates.
 * \param viewport_width - the width of the viewport on the screen in NDC coordinates.
 * \param viewport_height - the height of the viewport on the screen in NDC coordinates.
 */
Camera::Camera(glm::vec3 const& vrp, glm::vec3 const& vpn, glm::vec3 const& vup, glm::vec3 const& prp,
               glm::vec2 const& lower_left_window, glm::vec2 const& upper_right_window,
               float front_plane,    float back_plane,
               float x_viewport,     float y_viewport,
               float viewport_width, float viewport_height)
{
    this->vrp = vrp;
    this->vpn = vpn;
    this->vup = vup;
    this->prp = prp;

    this->lower_left_window  = lower_left_window;
    this->upper_right_window = upper_right_window;
    this->front_plane = front_plane;
    this->back_plane  = back_plane;

    this->x_viewport = x_viewport;
    this->y_viewport = y_viewport;
    this->viewport_width  = viewport_width;
    this->viewport_height = viewport_height;

    this->vieworientationmatrix    = glm::mat4x4(1.0f);
    this->invvieworientationmatrix = glm::mat4x4(1.0f);
    this->ComputeViewOrientation(this->vrp, this->vpn, this->vup);

    this->viewprojectionmatrix     = glm::mat4x4(1.0f);
    this->invviewprojectionmatrix  = glm::mat4x4(1.0f);
    this->ComputeViewProjection(this->prp, this->lower_left_window, this->upper_right_window, this->front_plane, this->back_plane);

    this->windowviewportmatrix     = glm::mat4x4(1.0f);
    this->invwindowviewportmatrix  = glm::mat4x4(1.0f);
    this->ComputeWindowViewport(this->x_viewport, this->y_viewport, this->viewport_width, this->viewport_height);

    this->currenttransformationmatrix    = glm::mat4x4(1.0f);
    this->invcurrenttransformationmatrix = glm::mat4x4(1.0f);
}
 
/*
 * Copy constructor, creates a copy of its parameter.
 * \param camera - the camera object which shuld be copied.
 */
Camera::Camera(Camera const& camera)
{
    this->vieworientationmatrix    = camera.vieworientationmatrix;
    this->invvieworientationmatrix = camera.invvieworientationmatrix;

    this->viewprojectionmatrix     = camera.viewprojectionmatrix;
    this->invviewprojectionmatrix  = camera.invviewprojectionmatrix;

    this->windowviewportmatrix     = camera.windowviewportmatrix;
    this->invwindowviewportmatrix  = camera.invwindowviewportmatrix;

    this->currenttransformationmatrix    = camera.currenttransformationmatrix;
    this->invcurrenttransformationmatrix = camera.invcurrenttransformationmatrix;

    this->vrp = camera.vrp;
    this->vpn = camera.vpn;
    this->vup = camera.vup;
    this->prp = camera.prp;

    this->lower_left_window  = camera.lower_left_window;
    this->upper_right_window = camera.upper_right_window;
    this->front_plane = camera.front_plane;
    this->back_plane  = camera.back_plane;

    this->x_viewport = camera.x_viewport;
    this->y_viewport = camera.y_viewport;
    this->viewport_width  = camera.viewport_width;
    this->viewport_height = camera.viewport_height;
}

/*
 * Destructor, cleans up the camere and destroys the object.
 */
Camera::~Camera()
{}

/*
 * Assignment operator, assigns its parameter to the current instance of class Camera
 * \param camera - the new value of class Camera.
 */
Camera& Camera::operator=(Camera const& camera)
{
    if (this != &camera) {
        this->vieworientationmatrix    = camera.vieworientationmatrix;
        this->invvieworientationmatrix = camera.invvieworientationmatrix;

        this->viewprojectionmatrix     = camera.viewprojectionmatrix;
        this->invviewprojectionmatrix  = camera.invviewprojectionmatrix;

        this->windowviewportmatrix     = camera.windowviewportmatrix;
        this->invwindowviewportmatrix  = camera.invwindowviewportmatrix;

        this->currenttransformationmatrix    = camera.currenttransformationmatrix;
        this->invcurrenttransformationmatrix = camera.invcurrenttransformationmatrix;

        this->vrp = camera.vrp;
        this->vpn = camera.vpn;
        this->vup = camera.vup;
        this->prp = camera.prp;

        this->lower_left_window  = camera.lower_left_window;
        this->upper_right_window = camera.upper_right_window;
        this->front_plane = camera.front_plane;
        this->back_plane  = camera.back_plane;

        this->x_viewport = camera.x_viewport;
        this->y_viewport = camera.y_viewport;
        this->viewport_width  = camera.viewport_width;
        this->viewport_height = camera.viewport_height;
    }
    return *this;
}

/*
 * \return the current ViewOrientation matrix.
 */
glm::mat4x4 Camera::ViewOrientation() const
{
    return this->vieworientationmatrix;
}

/*
 * \return the inverse of the current ViewOrientation matrix.
 */
glm::mat4x4 Camera::InvViewOrientation() const
{
    return this->invvieworientationmatrix;
}

/*
 * \return the current ViewProjection matrix.
 */
glm::mat4x4 Camera::ViewProjection() const
{
    return this->viewprojectionmatrix;
}

/*
 * \return the inverse of the current ViewProjection matrix.
 */
glm::mat4x4 Camera::InvViewProjection() const
{
    return this->invviewprojectionmatrix;
}

/*
 * \return the current WindowViewport matrix.
 */
glm::mat4x4 Camera::WindowViewport() const
{
    return this->windowviewportmatrix;
}

/*
 * \return the inverse of the current WindowViewport matrix.
 */
glm::mat4x4 Camera::InvWindowViewport() const
{
    return this->invwindowviewportmatrix;
}

/*
 * \return the current transformation matrix = WindowViewport() * ViewProjection() * ViewOrientation().
 */
glm::mat4x4 Camera::CurrentTransformationMatrix()
{
    // std::cout << "Camera::CurrentTransformationMatrix(): Not implemented yet!" << std::endl;

    this->currenttransformationmatrix = this->windowviewportmatrix *
                                        this->viewprojectionmatrix *
                                        this->vieworientationmatrix;
    
    return this->currenttransformationmatrix;
}

/*
 * \return the inverse of the current transformation 
 * matrix = InvViewOrientation() * InvViewProjection() * InvWindowViewport().
 */
glm::mat4x4 Camera::InvCurrentTransformationMatrix()
{
    Trace("Camera", "InvCurrentTransformationMatrix()");

    TraceMessage("InvViewOrientation() = " << std::endl << this->invvieworientationmatrix << std::endl;);
    TraceMessage("InvViewProjection() = " << std::endl << this->invviewprojectionmatrix << std::endl;);
    TraceMessage("InvWindowViewport() = " << std::endl << this->invwindowviewportmatrix << std::endl;);

    // std::cout << "Camera::InvCurrentTransformationMatrix(): Not implemented yet!" << std::endl;

    // this->invcurrenttransformationmatrix = this->invvieworientationmatrix *
    //                                        this->invviewprojectionmatrix *
    //                                        this->invwindowviewportmatrix;
    
    this->invcurrenttransformationmatrix = glm::inverse(this->currenttransformationmatrix);                                      glm::inverse(this->currenttransformationmatrix);
    
    return this->invcurrenttransformationmatrix;
}

/*
 * \return the current value of the View Reference Point.
 */
glm::vec3 const& Camera::VRP() const
{
    return this->vrp;
}

/*
 * Changes the value of the View Reference Point.
 * \param vrp - the new View Reference Point
 */
void Camera::VRP(glm::vec3 const& vrp)
{
    this->vrp = vrp;
    this->ComputeViewOrientation(this->vrp, this->vpn, this->vup);
}

/*
 * \return the current value of the View Plane Normal.
 */
glm::vec3 const& Camera::VPN() const
{
    return this->vpn;
}

/*
 * Changes the value of the View Plane Normal.
 * \param vpn - the new View Plane Normal.
 */
void Camera::VPN(glm::vec3 const& vpn)
{
    this->vpn = vpn;
    this->ComputeViewOrientation(this->vrp, this->vpn, this->vup);
}

/*
 * \return the current value of the View Up vector.
 */
glm::vec3 const& Camera::VUP() const
{
    return this->vup;
}

/*
 * Changes the value of the View Up vector.
 * \param vpn - the new View Up vector.
 */
void Camera::VUP(glm::vec3 const& vup)
{
    this->vup = vup;
    this->ComputeViewOrientation(this->vrp, this->vpn, this->vup);
}

/*
 * \return the current value of the Projection Reference Point.
 */
glm::vec3 const& Camera::PRP() const
{
    return this->prp;
}

/*
 * Changes the value of the Projection Reference Point.
 * \param prp - the new Projection Reference Point.
 */
void Camera::PRP(glm::vec3 const& prp)
{
    this->prp = prp;
    this->ComputeViewProjection(this->prp, this->lower_left_window, this->upper_right_window, this->front_plane, this->back_plane);
}

/*
 * \return the lower left corner of the current camera window.
 */
glm::vec2 const& Camera::WinLowerLeft() const
{
    return this->lower_left_window;
}

/*
 * Changes the lower left corner of the camera window.
 * \param lower_left_window - the new value of the lower left corner of the window.
 */
void Camera::WinLowerLeft(glm::vec2 const& lower_left_window)
{
    this->lower_left_window = lower_left_window;
    this->ComputeViewProjection(this->prp, this->lower_left_window, this->upper_right_window, this->front_plane, this->back_plane);
}

/*
 * \return the upper right corner of the current camera window.
 */
glm::vec2 const& Camera::WinUpperRight() const
{
    return this->upper_right_window;
}

/*
 * Changes the upper right corner of the camera window.
 * \param upper_right_window - the new value of the upper right corner of the window.
 */
void Camera::WinUpperRight(glm::vec2 const& upper_right_window)
{
    this->upper_right_window = upper_right_window;
    this->ComputeViewProjection(this->prp, this->lower_left_window, this->upper_right_window, this->front_plane, this->back_plane);
}

/*
 * \return the value of the z-coordinate of the Back Clipping Plane.
 */
float Camera::FrontClippingPlane() const
{
    return this->front_plane;
}

/*
 * Changes the z-value of the Front Clipping Plane.
 * \param front_plane - the new value of the z-coordinate of the Front Clipping Plane.
 */
void Camera::FrontClippingPlane(float const front_plane)
{
    this->front_plane = front_plane;
    this->ComputeViewProjection(this->prp, this->lower_left_window, this->upper_right_window, this->front_plane, this->back_plane);
}

/*
 * \return the value of the z-coordinate of the Back Clipping Plane.
 */
float Camera::BackClippingPlane() const
{
    return this->back_plane;
}

/*
 * Changes the z-value of the Back Clipping Plane.
 * \param front_plane - the new value of the z-coordinate of the Back Clipping Plane.
 */
void Camera::BackClippingPlane(float const back_plane)
{
    this->back_plane = back_plane;
    this->ComputeViewProjection(this->prp, this->lower_left_window, this->upper_right_window, this->front_plane, this->back_plane);
}

/*
 * \return - the value of the x-coordinate of the viewport on the screen
 */
float Camera::XPosition() const
{
    return this->x_viewport;
}

/*
 * Changes the x-coordinate of the viewport on the screen
 * \param new_x_position - the new x-coordinate of the viewport
 */
void Camera::XPosition(float new_x_position)
{
    this->x_viewport = new_x_position;
}

/*
 * \return - the value of the y-coordinate of the viewport on the screen
 */
float Camera::YPosition() const
{
    return this->y_viewport;
}

/*
 * Changes the y-coordinate of the viewport on the screen
 * \param new_y_position - the new y-coordinate of the viewport
 */
void Camera::YPosition(float new_y_position)
{
    this->y_viewport = new_y_position;
}

/*
 * \return the value of the Viewport width on the screen.
 */
float Camera::ViewportWidth() const
{
    return this->viewport_width;
}

/*
 * Changes the Viewport width
 * \param viewport_width - the new value of the Viewport width on the screen.
 */
void Camera::ViewportWidth(int new_viewport_width)
{
    this->viewport_width = new_viewport_width;
    this->ComputeWindowViewport(this->x_viewport, this->y_viewport, this->viewport_width, this->viewport_height);
}

/*
 * \return the value of the Viewport height on the screen.
 */
float Camera::ViewportHeight() const
{
    return this->viewport_height;
}

/*
 * Changes the Viewport height on the screen.
 * \param viewport_height - the new value of the Viewport height
 */
void Camera::ViewportHeight(int new_viewport_height)
{
    this->viewport_height = new_viewport_height;
    this->ComputeWindowViewport(this->x_viewport, this->y_viewport, this->viewport_width, this->viewport_height);
}

/**
 * Private Functions
 */

/*
 * Compute the View Orientation Matrix
 * \param vrp - the View Reference Point.
 * \param vpn - the View Plane Normal.
 * \param vup - the View Up vector.
 * \return - the computed ViewOrientation matrix.
 */
void Camera::ComputeViewOrientation(glm::vec3& vrp, glm::vec3& vpn, glm::vec3& vup)
{
    Trace("Camera", "ComputeViewOrientation(vec3&, vec3&, vec3&)");

    // std::cout << " Camera::ComputeViewOrientation(vec3&, vec3&, vec3&): Not implemented yet!" << std::endl;

    // Construct the translation matrix T(-VRP)
    glm::mat4 T_vrp = glm::translate(glm::mat4(1.0f), -vrp);
    
    // Construct the rotation matrix R
    glm::mat4 R(1.0f);
    // Normalize vpn and vup
    glm::vec3 n = glm::normalize(vpn);
    glm::vec3 u = glm::normalize(glm::cross(vup, n));
    glm::vec3 v = glm::normalize(glm::cross(n, u));
    R[0] = glm::vec4(u, 0.0f);
    R[1] = glm::vec4(v, 0.0f);
    R[2] = glm::vec4(n, 0.0f);
    R = glm::transpose(R);

    // Compute the View Orientation matrix
    this->vieworientationmatrix = R * T_vrp;
    this->invvieworientationmatrix = glm::inverse(this->vieworientationmatrix);

    // std::cout << "R:" << std::endl;
    // for (int row = 0; row < 4; ++row) {
    //     for (int col = 0; col < 4; ++col) {
    //         std::cout << R[col][row] << " ";
    //     }
    //     std::cout << std::endl; // Newline for each row
    // }
    // std::cout << " T(-VRP):" << std::endl;
    // for (int row = 0; row < 4; ++row) {
    //     for (int col = 0; col < 4; ++col) {
    //         std::cout << T_vrp[col][row] << " ";
    //     }
    //     std::cout << std::endl; // Newline for each row
    // }
}

/*
 * Compute the Projection Orientation Matrix.
 * \param prp - the Projection Reference Point.
 * \param lower_left_window - the lower left corner of the window.
 * \param upper_right_window - the upper right corner of the window.
 * \param front_clipping_plane - the z-coordinate of the front clipping plane.
 * \param back_clipping_plane - the z-coordinate of the back clipping plane.
 * \return - the computed ViewProjection matrix.
 */
void Camera::ComputeViewProjection(glm::vec3& prp, 
                   glm::vec2& lower_left_window, glm::vec2& upper_right_window,
                   float front_clipping_plane, float back_clipping_plane)
{
    Trace("Camera", "ComputeViewProjection(vec3&, vec2&, vec2&, float, float)");

    // std::cout << "Camera::ComputeViewProjection(vec3&, vec2&, vec2&, float, float): Not Implemented yet!" << std::endl;

    float Umin = lower_left_window.x;
    float Umax = upper_right_window.x;
    float Vmin = lower_left_window.y;
    float Vmax = upper_right_window.y;
    float F = front_clipping_plane;
    float B = back_clipping_plane;

    // Construct the translation matrix T(-prp)
    glm::mat4x4 T_prp = glm::translate(glm::mat4x4(1.0f), -prp);

    // Construct the shear matrix Sh_per
    glm::mat4 Sh_per = glm::mat4(1.0f);
    glm::vec3 CW = glm::vec3((Umax+Umin)/2, (Vmax+Vmin)/2, 0.0f);
    glm::vec3 DOP = prp - CW;
    // float shx = - DOP.x/DOP.z;
    // float shy = - DOP.y/DOP.z;
    // Sh_per[2] = glm::vec4(shx, shy, 1.0f, 0.0f);
    Sh_per[2][0] = -DOP.x/DOP.z;
    Sh_per[2][1] = -DOP.y/DOP.z;

    // Construct the scaleing matrix S_per
    glm::mat4 S_per(1.0f);
    float Sx = -2*prp.z /((Umax-Umin)*(B-prp.z));
    float Sy = -2*prp.z /((Vmax-Vmin)*(B-prp.z));
    float Sz = -1 /(B-prp.z);
    S_per[0][0] = Sx;
    S_per[1][1] = Sy;
    S_per[2][2] = Sz;

    // Construct the Transformation of View Volumes matrix M_perpar
    glm::mat4 M_perpar = glm::mat4(1.0f);
    float Z_max = (F-prp.z) / (B-prp.z);
    M_perpar[2][2] = 1.0f / (1.0f + Z_max);
    M_perpar[2][3] = -1.0f;
    M_perpar[3][2] = (Z_max) / (1 + Z_max); //according to slides, which is wrong!: (-Z_max) / (1 + Z_max);
    M_perpar[3][3] = 0.0f;

    glm::mat4 M_wv = glm::mat4(1.0f);
    // glm::mat4 T = glm::translate(glm::vec3(1.0f, 1.0f, 0.0f));
    // glm::mat4 S = glm::scale(glm::vec3(Umax-Umin / 2.0f, Vmax-Vmin / 2.0f, 1.0f));
    // M_wv = S * T;
    
    // M_pertotal = M_wv * M_perpar * S_per * Sh_per * T_prp * R * T_vrp

    // Combine to get the View Projection matrix
    this->viewprojectionmatrix = M_wv * M_perpar * S_per * Sh_per * T_prp;
    this->invviewprojectionmatrix = glm::inverse(this->viewprojectionmatrix);

    // std::cout << "T(-PRP):" << std::endl;
    // for (int row = 0; row < 4; ++row) {
    //     for (int col = 0; col < 4; ++col) {
    //         std::cout << T_prp[col][row] << " ";
    //     }
    //     std::cout << std::endl; // Newline for each row
    // }
    // std::cout << "Sh_per:" << std::endl;
    // for (int row = 0; row < 4; ++row) {
    //     for (int col = 0; col < 4; ++col) {
    //         std::cout << Sh_per[col][row] << " ";
    //     }
    //     std::cout << std::endl; // Newline for each row
    // }
    // std::cout << "S_per:" << std::endl;
    // for (int row = 0; row < 4; ++row) {
    //     for (int col = 0; col < 4; ++col) {
    //         std::cout << S_per[col][row] << " ";
    //     }
    //     std::cout << std::endl; // Newline for each row
    // }
    // std::cout << "M_perpar:" << std::endl;
    // for (int row = 0; row < 4; ++row) {
    //     for (int col = 0; col < 4; ++col) {
    //         std::cout << M_perpar[col][row] << " ";
    //     }
    //     std::cout << std::endl; // Newline for each row
    // }
}

/*
 * Compute the Window Viewport Matrix.
 * \param x_viewport - the x-coordinate of the viewport.
 * \param y_viewport - the y-coordinate of the viewport.
 * \param viewport_width - the width of the screen viewport.
 * \param viewport_height - the height of the screen viewport.
 * \return - the computed ViewportViewport matrix.
 */
void Camera::ComputeWindowViewport(float x_viewport, float y_viewport, float viewport_width, float viewport_height)
{
    Trace("Camera", "ComputeWindowViewport(float, float, float, float)");

    // The view volume is the canonical parallel view volume: [-1, 1] x [-1, 1] x [-1, 0]
    // OpenGL does this, so just return the identity matrix.
    this->windowviewportmatrix    = glm::mat4x4(1.0f);
    this->invwindowviewportmatrix = glm::mat4x4(1.0f);

    // Not needed because OpenGL does the window viewport mapping
    return;
    
    // But I have implemented it so I can have more figures in one window.

    // Translate (-1, -1, 0) to the origin (0, 0, 0)
    glm::mat4x4 Translate = glm::translate(glm::vec3(1.0f, 1.0f, 0.0f));

    TraceMessage("TranslationMatrix = " << std::endl << Translate << std::endl;);

    // Scale the canonical view volume to the screen viewport size
    glm::mat4x4 Scale = glm::scale(glm::vec3(viewport_width / 2.0f, viewport_height / 2.0f, 1.0f));

    TraceMessage("ScaleMatrix = " << std::endl << Scale << std::endl;);

    // Translate final viewport to its right position
    glm::mat4x4 ScreenTranslate = glm::translate(glm::vec3(x_viewport, y_viewport, 0.0f));

    // Compute the resulting WindowViewport matrix
    this->windowviewportmatrix = ScreenTranslate * Scale * Translate;

    // Compute the inverse of Translate
    glm::mat4x4 invTranslate = glm::translate(glm::vec3(-1.0f, -1.0f, 0.0f));

    // Compute the inverse of Scale
    glm::mat4x4 invScale = glm::scale(glm::vec3(2.0f / viewport_width, 2.0f / viewport_height, 1.0f));

    // Compute the inverse of ScreenTranslate
    glm::mat4x4 invScreenTranslate = glm::translate(glm::vec3(-x_viewport, -y_viewport, 0.0f));

    // Compute the inverse of the WindowViewport matrix
    this->invwindowviewportmatrix = invTranslate * invScale * invScreenTranslate;

    TraceMessage("WindowViewportMatrix = " << std::endl << this->windowviewportmatrix << std::endl;);
}
