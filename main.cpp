#include "ma_lab.cpp"

int main() {
    Settings settings;
    
    settings.add("color", 34);
    settings.add("path", "c:labs");
    settings.add("anything", "nothing");
    
    cout << settings << endl;;
    settings.erase_int("anything");         //удаляем
    settings.save("settings.txt");          //сохраняем
    
    Settings loadedSettings;
    loadedSettings.load("settings.txt");    //качаем
    
    cout << "Loaded settings: \n" << loadedSettings << endl;

    return 0;
}

