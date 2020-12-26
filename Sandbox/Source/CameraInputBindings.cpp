#include "CameraInputBindings.h"

#include "Input.h"

#include <GLFW/glfw3.h>

/*
+=============================================+
|----------- WASDCameraInputBindings ---------|
+=============================================+
*/

bool WASDCameraInputBindings::MoveForward() const
{
    return Input::IsKeyPressed(GLFW_KEY_W);
}

bool WASDCameraInputBindings::MoveBackward() const
{
    return Input::IsKeyPressed(GLFW_KEY_S);
}

bool WASDCameraInputBindings::MoveLeft() const
{
    return Input::IsKeyPressed(GLFW_KEY_A);
}

bool WASDCameraInputBindings::MoveRight() const
{
    return Input::IsKeyPressed(GLFW_KEY_D);
}

bool WASDCameraInputBindings::MoveUp() const
{
    return Input::IsKeyPressed(GLFW_KEY_E);
}

bool WASDCameraInputBindings::MoveDown() const
{
    return Input::IsKeyPressed(GLFW_KEY_Q);
}

/*
+==================================================+
|----------- ArrowKeysCameraInputBindings ---------|
+==================================================+
*/

bool ArrowKeysCameraInputBindings::MoveForward() const
{
    return Input::IsKeyPressed(GLFW_KEY_UP);
}

bool ArrowKeysCameraInputBindings::MoveBackward() const
{
    return Input::IsKeyPressed(GLFW_KEY_DOWN);
}

bool ArrowKeysCameraInputBindings::MoveLeft() const
{
    return Input::IsKeyPressed(GLFW_KEY_LEFT);
}

bool ArrowKeysCameraInputBindings::MoveRight() const
{
    return Input::IsKeyPressed(GLFW_KEY_RIGHT);
}

bool ArrowKeysCameraInputBindings::MoveUp() const
{
    return Input::IsKeyPressed(GLFW_KEY_HOME);
}

bool ArrowKeysCameraInputBindings::MoveDown() const
{
    return Input::IsKeyPressed(GLFW_KEY_END);
}

/*
+================================================+
|----------- DefaultCameraInputBindings ---------|
+================================================+
*/

bool DefaultCameraInputBindings::MoveForward() const
{
    return ArrowKeyBindings.MoveForward() || WASDKeyBindings.MoveForward();
}

bool DefaultCameraInputBindings::MoveBackward() const
{
    return ArrowKeyBindings.MoveBackward() || WASDKeyBindings.MoveBackward();
}

bool DefaultCameraInputBindings::MoveLeft() const
{
    return ArrowKeyBindings.MoveLeft() || WASDKeyBindings.MoveLeft();
}

bool DefaultCameraInputBindings::MoveRight() const
{
    return ArrowKeyBindings.MoveRight() || WASDKeyBindings.MoveRight();
}

bool DefaultCameraInputBindings::MoveUp() const
{
    return ArrowKeyBindings.MoveUp() || WASDKeyBindings.MoveUp();
}

bool DefaultCameraInputBindings::MoveDown() const
{
    return ArrowKeyBindings.MoveDown() || WASDKeyBindings.MoveDown();
}
