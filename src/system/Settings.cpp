#include "Settings.hpp"

#include <regex>
#include <fstream>

#define SETTINGS_FILEPATH "data/settings.ini"

SettingBase::SettingBase(const std::string& name) : name(name) {}
SettingBase::~SettingBase() {}

void SettingBase::printToFile(FILE *file) {
    fprintf(file, "%s=%s\n", name.c_str(), getValueAsString().c_str());
}

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

bool parseBoolFromString(const std::string& str) { // Accept the specified strings as true; anything else is false
    return str.compare("true") == 0 ||
           str.compare("TRUE") == 0 ||
           str.compare("1") == 0;
}
int parseIntFromString(const std::string& str) {
    return std::stoi(str);
}
float parseFloatFromString(const std::string& str) {
    return std::stof(str);
}
std::string parseStringFromString(const std::string& str) {
    return str;
}

std::string convertBoolToString(const bool& b) {
    return b ? "true" : "false";
}
std::string convertIntToString(const int& i) {
    return std::to_string(i);
}
std::string convertFloatToString(const float& f) {
    return std::to_string(f);
}
std::string convertStringToString(const std::string& str) {
    return str;
}

BoolSetting::BoolSetting(std::string name, bool defaultValue)
        : Setting<bool>(name, defaultValue, getPredicateAlwaysTrue<bool>(), parseBoolFromString, convertBoolToString) {}
BoolSetting::~BoolSetting() {}

IntSetting::IntSetting(std::string name, int defaultValue, int minBound, int maxBound)
        : Setting<int>(name, defaultValue, getPredicateNumberWithinBounds<int>(minBound, maxBound), parseIntFromString, convertIntToString) {}
IntSetting::~IntSetting() {}

FloatSetting::FloatSetting(std::string name, float defaultValue, float minBound, float maxBound)
        : Setting<float>(name, defaultValue, getPredicateNumberWithinBounds<float>(minBound, maxBound), parseFloatFromString, convertFloatToString) {}
FloatSetting::~FloatSetting() {}

StringSetting::StringSetting(std::string name, std::string defaultValue, std::string regex)
        : Setting<std::string>(name, defaultValue, getPredicateStringMatchesRegex(regex), parseStringFromString, convertStringToString) {}
StringSetting::~StringSetting() {}



/**   Initialize Settings here!   **/
FloatSetting Settings::initialGameModelScale("initialGameModelScale", 32, 8, 128);

Settings* Settings::instance = new Settings(); // Note: Should come AFTER the settings have been constructed!
Settings::Settings()
        : settingsLookup() {

    /**   Build the lookup table of Settings here!   **/
    addSettingToLookup(initialGameModelScale);
}
Settings::~Settings() {} // Do not force the app to save on exit, let the app ask for it manually.

template<typename T>
void Settings::addSettingToLookup(Setting<T>& setting) {
    if (settingsLookup.count(setting.name) == 1) {
        printf("WARNING: Setting with the same name \"%s\" already exists! Skipping...\n", setting.name.c_str());
        return;
    }
    settingsLookup[setting.name] = &setting;
}

void Settings::load() {
    loadFromFile(SETTINGS_FILEPATH);
}
void Settings::loadFromFile(const char* filepath) { // Adapted from https://www.walletfox.com/course/parseconfigfile.php
    // Open file
    std::ifstream settingsFile(filepath);
    if (!settingsFile.is_open()) {
        printf("Could not open settings file \"%s\" for loading! Missing?\n", filepath);
        return;
    }

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
        std::string value = line.substr(delimiterPos+1);

        // Check if name exists
        if (instance->settingsLookup.count(name) == 0) {
            printf("Unknown setting encountered in file: \"%s\"\n", name.c_str());
            continue; // Skip if name does not exist
        }

        // Assign value to Setting
        if (instance->settingsLookup.at(name)->read(value))
            printf("Assigned value \"%s\" to setting \"%s\"\n", value.c_str(), name.c_str());
        else printf("Warning: value \"%s\" for setting \"%s\" is invalid!\n", value.c_str(), name.c_str());
    }

    // No need to close ifstream file
}

void Settings::save() {
    return saveToFile(SETTINGS_FILEPATH);
}
void Settings::saveToFile(const char* filepath) {
    // Open file
    FILE *settingsFile = fopen(filepath, "w");
    if (!settingsFile) {
        printf("Could not open settings file \"%s\" for saving!\n", filepath);
        return;
    }

    // Save settings
    //initialModelScale.printToFile(settingsFile);
    for (auto settingPair : instance->settingsLookup) { // settingPair is of type std::pair<...>
        settingPair.second->printToFile(settingsFile);
    }
    printf("Settings saved to \"%s\"!\n", filepath);

    // Close file
    fclose(settingsFile);
}
