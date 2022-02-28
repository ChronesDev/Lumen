#pragma once

#include <MinHook.h>
#include <indx>

#include <indxs>

namespace Lumen::Detour
{
	class SimpleDetour
	{
	public:
		SimpleDetour() = default;
		~SimpleDetour() { }

	private:
		bool Created_ = false;
		bool Enabled_ = false;
		void* Address_ = nullptr;

	public:
		fun GetAddress()->IntPtr { return (IntPtr)Address_; }
		fun SetAddress(IntPtr address)->void { Address_ = (void*)address; }
		INDEX_Property(get = GetAddress, put = SetAddress) IntPtr Address;

		fun GetAddressPtr()->void* { return Address_; }
		fun SetAddressPtr(void* address)->void { Address_ = address; }
		INDEX_Property(get = GetAddressPtr, put = SetAddressPtr) void* AddressPtr;

		fun GetIsCreated()->bool { return Created_; }
		INDEX_Property(get = GetIsCreated) bool IsCreated;

		fun GetIsEnabled()->bool { return Enabled_; }
		INDEX_Property(get = GetIsEnabled) bool IsEnabled;

		fun Hook(void* address, void** original, void* function)->void
		{
			if (Enabled_) { return; }
			Address_ = address;
			if (address == nullptr) { throw std::exception("The Address cannot be nullptr."); }
			if (original == nullptr) { throw std::exception("The Original function pointer cannot be nullptr."); }
			if (function == nullptr) { throw std::exception("The Function cannot be nullptr."); }
			if (!Created_)
			{
				if (MH_CreateHook(address, function, original) != MH_OK)
				{
					throw std::exception("MH_CreateHook didn't return MH_OK.");
				}
				Created_ = true;
			}
			if (MH_EnableHook(address) != MH_OK) { throw std::exception("MH_EnabledHook didn't return MH_OK."); }
			Enabled_ = true;
		}

		fun Hook(IntPtr address, void** original, void* function)->void { Hook((void*)address, original, function); }

		template <class TOriginal, class TFunction>
		fun Hook(void* address, TOriginal& original, TFunction function)->void
		{
			Hook(address, (void**)&original, (void*)function);
		}

		template <class TOriginal, class TFunction>
		fun Hook(IntPtr address, TOriginal& original, TFunction function)->void
		{
			Hook((void*)address, (void**)&original, (void*)function);
		}

		fun Unhook()->void
		{
			if (Address_ != nullptr)
			{
				if (Created_)
				{
					if (Enabled_)
					{
						MH_DisableHook(Address_);
						Enabled_ = false;
					}
					MH_RemoveHook(Address_);
					Created_ = false;
				}
			}
		}

		fun UnhookIfEnabled()->void
		{
			if (IsEnabled) Unhook();
		}
	};
}

#include <indxe>