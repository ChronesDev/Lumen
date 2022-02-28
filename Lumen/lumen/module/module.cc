#pragma once

#include <indx>

#include <indxs>

namespace Lumen
{
    class Module
    {
    protected:
        bool Initialized_ = false;

    public:
        [[nodiscard]] fun GetIsInitialized() const->bool { return Initialized_; }
        INDEX_Property(get = GetIsInitialized) string IsInitialized;

        fun Init()->void;
        fun Deinit()->void;

    protected:
        virtual fun OnInit()->void { };
        virtual fun OnDeinit()->void { };

    public:
        [[nodiscard]] virtual fun GetName() const->string { return ""; }
        INDEX_Property(get = GetName) string Name;

    public:
        [[nodiscard]] virtual fun GetHasState() const->bool { return false; }
        INDEX_Property(get = GetHasState) bool HasState;

    protected:
        bool Enabled_ = false;

    public:
        [[nodiscard]] virtual fun GetIsEnabled() const->bool { return Enabled_; }
        INDEX_Property(get = GetIsEnabled) bool IsEnabled;

        [[nodiscard]] virtual fun GetIsDisabled() const->bool { return !Enabled_; }
        INDEX_Property(get = GetIsDisabled) bool IsDisabled;

        fun Enable()->void;
        fun Disable()->void;

    protected:
        virtual fun OnEnable()->void = 0;
        virtual fun OnDisable()->void = 0;
    };
}

#include <indxe>