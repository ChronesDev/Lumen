#pragma once

#include "module.cc"

#include <indxs>

namespace Lumen::Modules
{
    fun Init()->void;
    fun Deinit()->void;

    fun FindModuleByName(string name)->IPtr<Module>;
    fun TryFindModuleByName(string name)->Nullable<IPtr<Module>>;

    fun FindModuleByNameAnyCase(string name)->IPtr<Module>;
    fun TryFindModuleByNameAnyCase(string name)->Nullable<IPtr<Module>>;

    fun FindModuleById(string id)->IPtr<Module>;
    fun TryFindModuleById(string id)->Nullable<IPtr<Module>>;

    fun ContainsModule(IPtr<Module> module)->bool;
    fun AddModule(IPtr<Module> module)->void;
    fun RemoveModule(IPtr<Module> module)->void;

    fun MakeConfig(nlohmann::json& j)->void;
    fun LoadConfig(nlohmann::json& j)->void;
}

#include <indxe>