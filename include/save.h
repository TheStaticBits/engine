#pragma once

#include <nlohmann/json.hpp>

namespace Save
{
    const nlohmann::json loadData(const std::string savePath);
    void updateSaveData(const std::string savePath, const nlohmann::json& data);

    void saveNewHighscore(const int32_t score);
};