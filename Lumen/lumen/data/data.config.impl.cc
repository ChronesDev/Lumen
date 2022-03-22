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
        }
    }

    fun MakeConfigData(string name)->nlohmann::json
    {
        if (!IsConfigNameValid(name)) INDEX_THROW("Bad config (invalid config name).");

        nlohmann::json j = {};
        j["@LumenConfig"] = "*";
        j["Targets"] = (string)Config::ClientVersion;
        j["Author"] = "";
        j["Name"] = name;

        nlohmann::json jm = {};
        j["@LumenModules"] = "*";

        Modules::MakeConfig(jm);

        j["Modules"] = jm;

        return j;
    }

    fun LoadConfigData(nlohmann::json& j)->void
    {
        if (!j.contains("@LumenConfig")) INDEX_THROW("Bad config (missing @LumenConfig).");

        if (!j.contains("Name")) INDEX_THROW("Bad config (missing Name).");
        if (!IsConfigNameValid(j["Name"])) INDEX_THROW("Bad config (invalid config name).");

        if (!j.contains("Targets")) INDEX_THROW("Bad config (missing Target).");
        if (j["Target"] != "any")
        {
            Version v;
            try
            {
                v = Version::Parse(j["Target"]);
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

        Modules::LoadConfig(jm);
    }
}

#include <indxe>