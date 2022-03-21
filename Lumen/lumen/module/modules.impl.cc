#include "modules.cc"

#include <indxs>

namespace Lumen::Modules
{
    static List<IPtr<Module>> Modules_ = {};

    fun Init()->void
    {
        for (var& m : Modules_)
        {
            m->Init();
        }
    }
    fun Deinit()->void
    {
        for (var& m : Modules_)
        {
            m->Deinit();
        }
    }

    fun FindModuleByName(string name)->IPtr<Module>
    {
        var result = TryFindModuleByName(name);
        if (!result.HasValue) INDEX_THROW("Could not find any modules with this name.");
        return result.Value;
    }

    fun TryFindModuleByName(string name)->Nullable<IPtr<Module>>
    {
        for (var& m : Modules_)
        {
            if (m->Name == name) return m;
        }
        return Null;
    }

    fun FindModuleByNameAnyCase(string name)->IPtr<Module>
    {
        var result = TryFindModuleByNameAnyCase(name);
        if (!result.HasValue) INDEX_THROW("Could not find any modules with this name.");
        return result.Value;
    }
    fun TryFindModuleByNameAnyCase(string name)->Nullable<IPtr<Module>>
    {
        name = name.ToLower();
        for (var& m : Modules_)
        {
            if (m->Name.ToLower() == name) return m;
        }
        return Null;
    }

    fun FindModuleById(string id)->IPtr<Module>
    {
        var result = TryFindModuleById(id);
        if (!result.HasValue) INDEX_THROW("Could not find any modules with this id.");
        return result.Value;
    }
    fun TryFindModuleById(string id)->Nullable<IPtr<Module>>
    {
        for (var& m : Modules_)
        {
            if (m->Id == id) return m;
        }
        return Null;
    }

    fun ContainsModule(IPtr<Module> module)->bool { return Modules_.Contains(module); }

    fun AddModule(IPtr<Module> module)->void
    {
        if (Modules_.Contains(module)) INDEX_THROW("The module already exists.");
        Modules_.Add(module);
    }
    fun RemoveModule(IPtr<Module> module)->void { Modules_.Remove(module); }

    fun MakeConfig(nlohmann::json& j)->void
    {
        if (!j.contains("@LumenModules")) return;

        for (var& m : Modules_)
        {
            nlohmann::json jm = {};
            jm["@LumenModule"] = "*";

            m->MakeConfig(jm);
            j[Str(".", m->Id)] = jm;
        }
    }
    fun LoadConfig(nlohmann::json& j)->void
    {
        if (!j.contains("@LumenModules")) return;

        for (var& ji : j.items())
        {
            for (var& m : Modules_)
            {
                if (ji.key() == Str(".", m->Id))
                {
                    nlohmann::json& jm = ji.value();
                    if (!jm.contains("@LumenModule")) break;

                    m->LoadConfig(jm);
                    break;
                }
            }
        }
    }
}

#include <indxe>