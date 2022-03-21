#pragma once

#include <lumen/input/key.cc>
#include <lumen/module/module.cc>

#include <indxs>

namespace Lumen::Modules
{
    struct Night;

    struct Night : Module
    {
        Night() = default;

        fun GetName() const->string override { return "Night"; }
        fun GetId() const->string override { return "lumen_night"; }
        fun GetDescription() const->string override { return "Changes the time to night."; }
        fun GetHasState() const->bool override { return true; }

        fun OnInit()->void override;
        fun OnDeinit()->void override;

    protected:
        fun OnEnable()->void override;
        fun OnDisable()->void override;

    public:
        fun GetSupportsConfig() const->bool override { return true; }
        fun MakeConfig(nlohmann::json& j)->void override;
        fun LoadConfig(nlohmann::json& j)->void override;

    public:
        static const int NightTime = 42000;
    };

    global IPtr<Night> NightModule;
}

#include <indxe>