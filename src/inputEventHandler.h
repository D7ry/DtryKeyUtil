using EventResult = RE::BSEventNotifyControl;

class inputEventHandler : public RE::BSTEventSink<RE::InputEvent*>
{
public:
    virtual EventResult ProcessEvent(RE::InputEvent* const* a_event, RE::BSTEventSource<RE::InputEvent*>* a_eventSource) override;

    static void Register()
    {
        auto deviceManager = RE::BSInputDeviceManager::GetSingleton();
        deviceManager->AddEventSink(inputEventHandler::GetSingleton());
    }

private:

    enum : std::uint32_t
    {
        kInvalid = static_cast<std::uint32_t>(-1),
        kKeyboardOffset = 0,
        kMouseOffset = 256,
        kGamepadOffset = 266
    };
    static inputEventHandler* GetSingleton()
    {
        static inputEventHandler singleton;
        return std::addressof(singleton);
    }

    static std::uint32_t GetGamepadIndex(RE::BSWin32GamepadDevice::Key a_key);
};