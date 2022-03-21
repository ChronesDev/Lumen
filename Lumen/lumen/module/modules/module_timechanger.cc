#pragma once

#include <lumen/input/key.cc>
#include <lumen/module/module.cc>

#include <indxs>

namespace Lumen::Modules
{
    struct TimeChanger;

    struct TimeChanger : Module
    {
        TimeChanger() = default;

        fun GetName() const->string override { return "TimeChanger"; }
        fun GetId() const->string override { return "lumen_timechanger"; }
        fun GetDescription() const->string override { return "Changes the time."; }
        fun GetHasState() const->bool override { return true; }

        fun OnInit()->void override;
        fun OnDeinit()->void override;

    protected:
        fun OnEnable() -> void override;
        fun OnDisable() -> void override;

    public:
        fun ExecuteGet(List<string> args)->void override;
        fun ExecuteSet(List<string> args)->void override;

        fun GetSupportsConfig() const->bool override { return true; }
        fun MakeConfig(nlohmann::json& j)->void override;
        fun LoadConfig(nlohmann::json& j)->void override;

        Event<void()> Enabled;
        Event<void()> Disabled;

        Event<void()> CustomTimeChanged;

    protected:
        int CustomTime_ = 0;

    public:
        fun GetCustomTime() const->int { return CustomTime_; }
        fun SetCustomTime(int value)->void
        {
            if (value != CustomTime_) CustomTimeChanged.Invoke();
            CustomTime_ = value;
        }
        INDEX_Property(get = GetCustomTime, put = SetCustomTime) int CustomTime;
    };

    global IPtr<TimeChanger> TimeChangerModule;
}

#include <indxe>