#include <iostream>
#include <map>
#include <string>
#include <fstream>

using namespace std;

class Settings {
public:
    using SettingValue = variant<int, string>;

private:
    map<string, SettingValue> settings;

public:
    void add(const string& name, int value) {
        settings[name] = value;
    }

    void add(const string& name, const string& value) {
        settings[name] = value;
    }

    void erase_int(const string& name) {
        settings.erase(name);
    }

    void erase_str(const string& name) {
        settings.erase(name);
    }

    int find_int(const string& name) {
        if (settings.find(name) != settings.end() && holds_alternative<int>(settings[name])) {
            return get<int>(settings[name]);
        }
        throw runtime_error("Настройка не найдена.");
    }

    string find_str(const string& name) {
        if (settings.find(name) != settings.end() && holds_alternative<string>(settings[name])) {
            return get<string>(settings[name]);
        }
        throw runtime_error("Настройка не найдена.");
    }

    friend ostream& operator<<(ostream& os, const Settings& s) {
        for (const auto& [key, value] : s.settings) {
            os << key << ": ";
            if (holds_alternative<int>(value)) {
                os << get<int>(value);
            } else {
                os << get<string>(value);
            }
            os << endl;
        }
        return os;
    }

    void load(const string& filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Невозможно открыть файл");
        }

        string name;
        string value;
        while (file >> name >> value) {
            if (isdigit(value[0])) {
                add(name, stoi(value));
            } else {
                add(name, value);
            }
        }
    }

    void save(const string& filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            throw runtime_error("Невозможно открыть файл");
        }

        for (const auto& [key, value] : settings) {
            file << key << " ";
            if (holds_alternative<int>(value)) {
                file << get<int>(value);
            } else {
                file << get<string>(value);
            }
            file << endl;
        }
    }
};

