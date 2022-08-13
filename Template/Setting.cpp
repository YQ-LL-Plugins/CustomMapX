#include <fstream>
#include <LoggerAPI.h>

#define JSON2(key1,key2,val)                                \
if (json.find(key1) != json.end()) {                      \
    if (json.at(key1).find(key2) != json.at(key1).end()) {\
    const nlohmann::json& out2 = json.at(key1).at(key2);  \
         out2.get_to(val);}}                              \

#define JSON1(key,val)                                         \
if (json.find(key) != json.end()) {                          \
    const nlohmann::json& out = json.at(key);                \
    out.get_to(val);}                                         \

namespace Settings {

    namespace DownloadImg {
        bool allowmember = false;
    }
    namespace LocalImg {
        bool allowmember = false;
    }

    nlohmann::json globaljson() {
        nlohmann::json json;
        json["DownloadImg"]["Allow-Member"] = DownloadImg::allowmember;
        json["LocalImg"]["Allow-Member"] = LocalImg::allowmember;
        return json;
    }

    void initjson(nlohmann::json json) {
        JSON2("DownloadImg", "Allow-Member", DownloadImg::allowmember);
        JSON2("LocalImg", "Allow-Member", LocalImg::allowmember);
    }

    void WriteDefaultConfig(const std::string& fileName) {
        std::ofstream file(fileName);
        if (!file.is_open()) {
            Logger("CustomMapX").error("Can't open file ",fileName);
            return;
        }
        auto json = globaljson();
        file << json.dump(4);
        file.close();
    }

    void LoadConfigFromJson(const std::string& fileName) {
        std::ifstream file(fileName);
        if (!file.is_open()) {
            Logger("CustomMapX").error("Can't open file ", fileName);
            return;
        }
        nlohmann::json json;
        file >> json;
        file.close();
        initjson(json);
        WriteDefaultConfig(fileName);
    }

    void reloadJson(const std::string& fileName) {
        std::ofstream file(fileName);
        if (file)
        {
            file << globaljson().dump(4);
        }
        else
        {
            Logger("CustomMapX").error("Configuration File Creation failed!");
        }
        file.close();
    }
} // namespace Settings


