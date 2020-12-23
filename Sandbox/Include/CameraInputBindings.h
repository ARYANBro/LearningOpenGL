#pragma once

#include <type_traits>
#include <memory>

struct CameraInputBindings
{
    virtual ~CameraInputBindings() noexcept = default;

    template<typename CameraInputBindingType, typename = std::enable_if_t<std::is_base_of<CameraInputBindings, CameraInputBindingType>::value, std::shared_ptr<CameraInputBindingType>>>
    static std::shared_ptr<CameraInputBindingType> Create()
    {
        return std::make_shared<CameraInputBindingType>();
    }

    virtual bool MoveForward() const = 0;
    virtual bool MoveBackward() const = 0;
    virtual bool MoveLeft() const = 0;
    virtual bool MoveRight() const = 0;
    virtual bool MoveUp() const = 0;
    virtual bool MoveDown() const = 0;
};

struct WASDCameraInputBindings : public CameraInputBindings
{
    virtual ~WASDCameraInputBindings() noexcept = default;

    virtual bool MoveForward() const override;
    virtual bool MoveBackward() const override;
    virtual bool MoveLeft() const override;
    virtual bool MoveRight() const override;
    virtual bool MoveUp() const override;
    virtual bool MoveDown() const override;
};

struct ArrowKeysCameraInputBindings : public CameraInputBindings
{
    virtual ~ArrowKeysCameraInputBindings() noexcept = default;

    virtual bool MoveForward() const override;
    virtual bool MoveBackward() const override;
    virtual bool MoveLeft() const override;
    virtual bool MoveRight() const override;
    virtual bool MoveUp() const override;
    virtual bool MoveDown() const override;
};

struct DefaultCameraInputBindings : public CameraInputBindings
{
    virtual ~DefaultCameraInputBindings() noexcept = default;

    virtual bool MoveForward() const override;
    virtual bool MoveBackward() const override;
    virtual bool MoveLeft() const override;
    virtual bool MoveRight() const override;
    virtual bool MoveUp() const override;
    virtual bool MoveDown() const override;

    ArrowKeysCameraInputBindings ArrowKeyBindings;
    WASDCameraInputBindings WASDKeyBindings;
};
