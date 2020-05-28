#ifndef SETTINGS_HPP
#define SETTINGS_HPP

#include <cstdio> // For sprintf
#include <string>
#include <map>
#include <functional>

// Base class for settings, to provide some base functionality without using templates
class SettingBase {
    public:
        const std::string name;

        SettingBase(const std::string& name);
        ~SettingBase();

        virtual bool read(const std::string& strValue)=0;
        virtual void printToFile(FILE *file)=0;
};

template<typename T>
class Setting : public SettingBase {
    protected:
        T value;
        std::function<bool(const T&)> isValid;
        std::function<T(const std::string&)> parseFromString;
        std::function<const char*(const T&)> convertToString;

    public:
        // Even if the specified default value that fails the validity predicate, it will still be used.
        // Maybe useful for const/readonly Settings?
        Setting(
                std::string name,
                T defaultValue,
                std::function<bool(const T&)> validityPredicate,
                std::function<T(const std::string&)> parseFromString,
                std::function<const char*(const T&)> convertToString)

                : SettingBase(name) {

            value = defaultValue;
            isValid = validityPredicate;
            this->parseFromString = parseFromString;
        }
        ~Setting() {}

        // Returns the stored value
        const T& get() const {
            return value;
        }

        bool set(const T& value) {
            if (isValid(value)) {
                this->value = value;
                return true;
            } else return false;
        }
        bool read(const std::string& strValue) {
            return set( parseFromString(strValue) );
        }

        void printToFile(FILE *file) {
            fprintf(file, "%s=%s\n", name.c_str(), convertToString(value));
        }
};

class IntSetting : public Setting<int> {
    public:
        IntSetting(std::string name, int defaultValue, int minBound, int maxBound);
        ~IntSetting();
};
class FloatSetting : public Setting<float> {
    public:
        FloatSetting(std::string name, float defaultValue, float minBound, float maxBound);
        ~FloatSetting();
};
class StringSetting : public Setting<std::string> {
    public:
        StringSetting(std::string name, std::string defaultValue, std::string regex);
        ~StringSetting();
};

class SettingManager { // Singleton?
    protected:
        // List of settings for easy lookup when reading from file
        // (The explicit settings are still kept separate for easy access and compile-time checking within the program)
        // The second template param is supposed to be a pointer to a Setting, just that Settings need a type to be instantiated first
        std::map<std::string, SettingBase*> settingsLookup;

        template<typename T>
        void addSettingToLookup(Setting<T>& setting);

    public:
        // Place Setting members here
        // Remember to init them and add them to the map in the constructor too!
        FloatSetting initialModelScale;

        SettingManager();
        ~SettingManager();

        void load(); // Loads settings from the default filepath (specified in Settings.cpp)
        void loadFromFile(const char* filepath);

        // Returns true iff all settings could be saved successfully
        bool save(); // Saves settings to the default filepath
        bool saveToFile(const char* filepath);
};

#endif // SETTINGS_HPP
