#include "data.cc"

#include <lumen/config/config.cc>
#include <lumen/log/log.cc>
#include <lumen/module/modules.cc>

#include <indxs>

namespace Lumen::Data
{
    fun IsConfigNameValid(string name)->bool
    {
        for (var& c : name)
        {
            if (c >= 'a' && c <= 'z') continue;
            if (c >= 'A' && c <= 'Z') continue;
            if (c >= '0' && c <= '9') continue;
            if (c == '-' || c == '_') continue;
            if (c == ':' || c == '~') continue;
            if (c == '.' || c == ',') continue;
            return false;
        }
        return true;
    }

    fun IsConfigValid(nlohmann::json& j)->bool
    {
        try
        {
            CheckConfig(j);
            return true;
        }
        catch (std::runtime_error& ex)
        {
            return false;
        }
    }

    fun CheckConfig(nlohmann::json& j)->void
    {
        if (!j.contains("@LumenConfig")) INDEX_THROW("Bad config (missing @LumenConfig).");

        if (!j.contains("Name")) INDEX_THROW("Bad config (missing Name).");
        if (!IsConfigNameValid((std::string)j["Name"])) INDEX_THROW("Bad config (invalid config name).");

        if (!j.contains("Target")) INDEX_THROW("Bad config (missing Target).");
        if (j["Target"] != "any")
        {
            Version v;
            try
            {
                v = Version::Parse((std::string)j["Target"]);
            }
            catch (std::exception& ex)
            {
                INDEX_THROW("Bad config (invalid Target).");
            }
            if (v.Major != Config::ClientVersion.Major || v.Minor != Config::ClientVersion.Minor)
                INDEX_THROW("Unsupported Config.");
        }

        if (!j.contains("Modules")) INDEX_THROW("Bad config (missing Modules).");
        var& jm = j["Modules"];
        if (!jm.contains("@LumenModules")) INDEX_THROW("Bad config (missing @LumenModules).");
    }

    fun MakeConfigData(string name)->nlohmann::json
    {
        if (!IsConfigNameValid(name)) INDEX_THROW("Bad config (invalid config name).");

        nlohmann::json j = {};
        j["@LumenConfig"] = "*";
        j["Target"] = (std::string)(string)Config::ClientVersion;
        j["Author"] = "";
        j["Name"] = (std::string)name;

        nlohmann::json jm = {};
        jm["@LumenModules"] = "*";

        Modules::MakeConfig(jm);

        j["Modules"] = jm;

        return j;
    }

    fun LoadConfigData(nlohmann::json& j)->void
    {
        CheckConfig(j);

        var& jm = j["Modules"];
        Modules::LoadConfig(jm);
    }
}

#include <indxe>