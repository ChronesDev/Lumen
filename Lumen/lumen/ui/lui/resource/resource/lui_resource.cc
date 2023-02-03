#pragma once

#include <lumen/ui/lui/context/context.cc>

#include <indxs>

namespace Lumen::LUI
{
    template <class T, class TRes> struct LUIResource
    {
        LUIResource() = default;
        [[maybe_unused]] explicit LUIResource(T value)
            : Value_(value)
        {
            TriggerValueChanged_();
        }

    protected:
        union
        {
            LUIContext* LContext_ = nullptr;
            LUIContext* lc;
        };

    public:
        fun SetLContext(LUIContext* value)->void
        {
            if (LContext_ != value)
            {
                LContext_ = value;
                Update();
            }
        }
        [[nodiscard]] fun GetLContext() const->LUIContext* { return LContext_; }
        INDEX_Property(get = GetLContext, put = SetLContext) LUIContext* LContext;

    protected:
        T Value_;
        Nullable<TRes> Resource_;

    public:
        fun GetValue()->T& { return Value_; }
        fun GetValue() const->const T& { return Value_; }
        fun SetValue(T& value)->void
        {
            if (Value_ != value)
            {
                Value_ = value;
                TriggerValueChanged_();
            }
            else
                Value_ = value;
        }
        INDEX_Property(get = GetValue, put = SetValue) T& Value;

    protected:
        fun SetResource(const TRes& value)->void { Resource_ = value; }

    public:
        fun GetResource()->TRes&
        {
            if (!Resource_.HasValue) INDEX_THROW("Resource was null.");
            return Resource_.Value;
        }
        fun GetResource() const->const TRes&
        {
            if (!Resource_.HasValue) INDEX_THROW("Resource was null.");
            return Resource_.Value;
        }
        INDEX_Property(get = GetResource, put = SetResource) TRes& Resource;

    public:
        virtual fun GetHasResource() const->bool { return Resource_.HasValue; }
        INDEX_Property(get = GetHasResource) bool HasResource;

    protected:
        fun TriggerValueChanged_()->void
        {
            OnValueChanged();
            Update();
        }

    public:
        fun Update(LUIContext* l)->void
        {
            if (!l)
            {
                Release();
                return;
            }
            LContext = l;
            OnUpdate();
        }
        fun Update()->void
        {
            if (LContext_) OnUpdate();
        }
        fun Release()->void
        {
            LContext = nullptr;
            OnRelease();
        }

    public:
        virtual fun OnUpdate()->void = 0;
        virtual fun OnRelease()->void = 0;

        virtual fun OnValueChanged()->void {};
    };
}

#include <indxe>