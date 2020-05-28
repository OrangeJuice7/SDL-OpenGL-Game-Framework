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
        virtual std::string getValueAsString()=0;
        void printToFile(FILE *file);
};

template<typename T>
class Setting : public SettingBase {
    protected:
        T value;
        std::function<bool(const T&)> isValid;
        std::function<T(const std::string&)> parseFromString;
        std::function<std::string(const T&)> convertToString;

    public:
        // Even if the specified default value that fails the validity predicate, it will still be used.
        // Maybe useful for const/readonly Settings?
        Setting(
                std::string name,
                T defaultValue,
                std::function<bool(const T&)> validityPredicate,
                std::function<T(const std::string&)> parseFromString,
                std::function<std::string(const T&)> convertToString)

                : SettingBase(name) {

            value = defaultValue;
            isValid = validityPredicate;
            this->parseFromString = parseFromString;
            this->convertToString = convertToString;
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

        std::string getValueAsString() {
            return convertToString(value);
        }
};

class BoolSetting : public Setting<bool> {
    public:
        BoolSetting(std::string name, bool defaultValue);
        ~BoolSetting();
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

struct STRING_COMPARATOR {
    bool operator()(const std::string& str1, const std::string& str2) const {
        return str1.compare(str2) < 0;
    }
};
class Settings {
    private:
        // Singleton
        static Settings* instance;

        // List of settings for easy lookup when reading from file
        // (The explicit settings are still kept separate for easy access and compile-time checking within the program)
        // The second template param is supposed to be a pointer to a Setting, just that Settings need a type to be instantiated first
        std::map<std::string, SettingBase*, STRING_COMPARATOR> settingsLookup;

        template<typename T>
        void addSettingToLookup(Setting<T>& setting);

        Settings();
        ~Settings();

    public:
        // Place Setting members here
        // Remember to init them and add them to the map in the constructor too!
        // Call them in any other file by using Settings::[setting name].get()
        static BoolSetting isFullscreen;
        static FloatSetting initialGameModelScale;

        // Load settings: guaranteed to maintain safe values for the settings
        static void load(); // Loads settings from the default filepath (specified in Settings.cpp)
        static void loadFromFile(const char* filepath);

        // Returns true iff all settings could be saved successfully
        static void save(); // Saves settings to the default filepath
        static void saveToFile(const char* filepath);
};

#endif // SETTINGS_HPP
