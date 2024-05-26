## C++ Weather Application ##

Приложение для погоды, написанное на cpp. Оно подключается к API Национальной метеорологической службы США (NWS) и получает прогноз погоды в формате NDFD. Также анализирует xml для использования.

### Ссылки: ###
US National Weather Service NDFD (https://graphical.weather.gov/xml/)
PugiXML parser (http://pugixml.org/)

### Требования: ###
* libcurl
* cmake

### Платформы: ###
* Тестирование на Rpi под управлением debian

### Установка: ###
    mkdir build
    cmake ..
    make

### Пользовательская настройка: ###
Weather.h

### Пример использования: ###
main.cpp
