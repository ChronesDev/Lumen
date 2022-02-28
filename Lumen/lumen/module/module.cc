#pragma once

#include <indx>
#include <lumen/input/key.cc>

#include <indxs>

namespace Lumen
{
    class Module : public IObj<Module>
    {
    public:
        ~Module();

    protected:
        bool Initialized_ = false;

    public:
        [[nodiscard]] fun GetIsInitialized() const->bool { return Initialized_; }
        INDEX_Property(get = GetIsInitialized) bool IsInitialized;

        fun Init()->void;
        fun Deinit()->void;

    protected:
        virtual fun OnInit()->void {};
        virtual fun OnDeinit()->void {};

    public:
        [[nodiscard]] virtual fun GetName() const->string = 0;
        INDEX_Property(get = GetName) string Name;

        [[nodiscard]] virtual fun GetId() const->string = 0;
        INDEX_Property(get = GetId) string Id;

        [[nodiscard]] virtual fun GetDescription() const->string = 0;
        INDEX_Property(get = GetDescription) string Description;

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
        virtual fun OnEnable()->void {};
        virtual fun OnDisable()->void {};

    public:
        virtual fun ExecuteGet(List<string> args)->void;
        virtual fun ExecuteSet(List<string> args)->void;

    public:
        virtual fun GetHasBinding()->bool { return false; }
        INDEX_Property(get = GetHasBinding) bool HasBinding;

        virtual fun BindTo(Key key)->void { };
        virtual fun Unbind()->void { };
    };
}

#include <indxe>