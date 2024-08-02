#include "save.h"

#include <fstream>
#include <nlohmann/json.hpp>

#include "util/log.h"

#ifdef __EMSCRIPTEN__
#include "emscripten.h"
#include "emscripten/html5.h"

// Tests if currently runnning on ofstatic.com
EM_JS(bool, testOnOfStatic, (), {
    console.log(typeof(window.fetchSaveData));
    return typeof(window.fetchSaveData) === "function";
})

EM_ASYNC_JS(char*, callFetchSaveData, (), {
    const response = await window.fetchSaveData();

    console.log("C++ calls JS fetchSaveData() response: " + response);
    
    if (response) {
        return stringToNewUTF8(response);
    }

    return stringToNewUTF8("{}"); // Return empty JSON
});

EM_JS(void, callUpdateSaveData, (const char* data), {
    const stringData = UTF8ToString(data);

    if (typeof(window.updateSaveData) === "function") {
        window.updateSaveData(stringData);
    }
});

EM_JS(void, callSaveHighscore, (const int32_t score), {
    window.saveHighscore(score);
});

#endif

const nlohmann::json Save::loadData(const std::string savePath)
{
#ifndef __EMSCRIPTEN__
    std::ifstream file(savePath, std::ios::in);

    if (!file.is_open())
        return nlohmann::json::array(); // Return empty JSON

    const nlohmann::json data = nlohmann::json::parse(file, nullptr, true, true);
    file.close();

    return data;
#else
    if (testOnOfStatic())
    {
        logger::info("Running on ofstatic.com, using save data");

        char* stringData = callFetchSaveData();
        
        const nlohmann::json saveData = nlohmann::json::parse(stringData);
        free(stringData);

        return saveData;
    }
    else logger::warn("Not running on ofstatic.com, save data not used");
#endif

    return nlohmann::json::array(); // Return empty JSON if not on website
}

void Save::updateSaveData(const std::string savePath, const nlohmann::json& data)
{
#ifndef __EMSCRIPTEN__
    std::ofstream file(savePath, std::ios::out | std::ios::trunc);

    if (!file.is_open())
    {
        logger::error("Failed to open save file at" + savePath + " for writing");
        return;
    }

    file << data.dump();
    file.close();
#else
    if (testOnOfStatic()){
        std::string stringData = data.dump();
        callUpdateSaveData(stringData.c_str());
    }
#endif
}

void Save::saveNewHighscore(const int32_t score)
{
#ifdef __EMSCRIPTEN__
    if (testOnOfStatic())
        callSaveHighscore(score);
#endif
}