#include "Settings.hpp"

#include <regex>
#include <fstream>

#define SETTINGS_FILEPATH "data/settings.ini"

SettingBase::SettingBase(const std::string& name) : name(name) {}
SettingBase::~SettingBase() {}

template<typename T>
std::function<bool(const T&)> getPredicateAlwaysTrue() {
    return [](const T& v){ return true; };
}

template<typename T>
std::function<bool(const T&)> getPredicateNumberWithinBounds(const T& min, const T& max) {
    return [min,max](const T& f){ return min <= f && f <= max; };
}

std::function<bool(const std::string&)> getPredicateStringMatchesRegex(std::string regex) {
    return [regex](const std::string& str){ return std::regex_match(str, std::regex(regex)); };
}

std::string parseStringFromString(const std::string& str) {
    return str;
}
int parseIntFromString(const std::string& str) {
    return std::stoi(str);
}
float parseFloatFromString(const std::string& str) {
    return std::stof(str);
}

const char* convertIntToString(const int& i) {
    return std::to_string(i).c_str();
}
const char* convertFloatToString(const float& f) {
    return std::to_string(f).c_str();
}
const char* convertStringToString(const std::string& str) {
    return str.c_str();
}

IntSetting::IntSetting(std::string name, int defaultValue, int minBound, int maxBound)
        : Setting<int>(name, defaultValue, getPredicateNumberWithinBounds<int>(minBound, maxBound), parseIntFromString, convertIntToString) {}
IntSetting::~IntSetting() {}

FloatSetting::FloatSetting(std::string name, float defaultValue, float minBound, float maxBound)
        : Setting<float>(name, defaultValue, getPredicateNumberWithinBounds<float>(minBound, maxBound), parseFloatFromString, convertFloatToString) {}
FloatSetting::~FloatSetting() {}

StringSetting::StringSetting(std::string name, std::string defaultValue, std::string regex)
        : Setting<std::string>(name, defaultValue, getPredicateStringMatchesRegex(regex), parseStringFromString, convertStringToString) {}
StringSetting::~StringSetting() {}



SettingManager::SettingManager()
    : initialModelScale("initialModelScale", 32, 8, 64) {

    addSettingToLookup(initialModelScale);
}
SettingManager::~SettingManager() {} // DO NOT SAVE! Do not force the app to save on exit, let the app ask for it manually.

template<typename T>
void SettingManager::addSettingToLookup(Setting<T>& setting) {
    if (settingsLookup.count(setting.name) == 1) {
        printf("WARNING: Setting with the same name \"%s\" already exists! Skipping...\n", setting.name.c_str());
        return;
    }
    settingsLookup[setting.name] = &setting;
}

void SettingManager::load() {
    loadFromFile(SETTINGS_FILEPATH);
}
void SettingManager::loadFromFile(const char* filepath) { // Adapted from https://www.walletfox.com/course/parseconfigfile.php
    // Open file
    std::ifstream settingsFile(filepath);
    if (!settingsFile.is_open()) {
        printf("Could not open settings file \"%s\" for loading! Missing?", filepath);
        return;
    }

    // Build hashmap of data names

    // Read data
    std::string line;
    while (getline(settingsFile, line)) {
        // Remove all whitespaces
        line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());

        // Ignore comments (i.e. lines preceded by a '#')
        if(line[0] == '#') continue;

        // Get position of '='
        size_t delimiterPos = line.find("=");
        if (delimiterPos == std::string::npos) continue; // '=' not found

        // Retrieve name and value
        std::string name = line.substr(0, delimiterPos);
        std::string value = line.substr(delimiterPos + 1);

        // Check if name exists
        if (settingsLookup.count(name) == 0) {
            printf("Unknown setting encountered in file: \"%s\"\n", name.c_str());
            continue; // Skip if name does not exist
        }

        // Assign value to Setting
        if (settingsLookup.at(name)->read(value)) printf("Assigned value \"%s\" to setting \"%s\"\n", value.c_str(), name.c_str());
        else printf("Warning: value \"%s\" for setting \"%s\" is invalid!\n", value.c_str(), name.c_str());
    }

    // No need to close ifstream file
}

bool SettingManager::save() {
    return saveToFile(SETTINGS_FILEPATH);
}
bool SettingManager::saveToFile(const char* filepath) {
    // Open file
    FILE *settingsFile = fopen(filepath, "w");
    if (!settingsFile) {
        printf("Could not open settings file \"%s\" for saving!", filepath);
        return false;
    }

    // Save settings
    //initialModelScale.printToFile(settingsFile);
    for (auto settingPair : settingsLookup) { // settingPair is of type std::pair<...>
        settingPair.second->printToFile(settingsFile);
    }

    // Close file
    fclose(settingsFile);

    return true;
}
