# ESP8266-Temperature-measurement-open-system
Пример датчика температуры окружающей среды (схема+программа) для работы с окрытой системой (https://github.com/grinzya/Temp_Stirage_System_backend и https://github.com/alexandr-blinkov/vue-ymaps)
# Описание
# Модули для работы системы
* Контроллер ESP8266
* Датчик температуры SHTC3
* Плата преобразования напряжения 3.7 вольт в 5 вольт 1А
* Аккумуляторная батарея 2200 mA.
* Корпус
# Схема подключения модулей
https://github.com/ArtRu-ai/ESP8266-Temperature-measurement-open-system/blob/main/Схема%20подключения.jpg?raw=true
# Схема работы датчика
Датчик температуры по Wi-Fi подключается к маршрутизатору, питание обеспечивается посредством аккумуляторной батареи, в данной версии прошивки автономная работа составляет около 24 часов.
# Схема взаимодействия с системой хранения
Данные о температуре окружающей среды передаются через интернет на сервер базы данных 1 раз в 10 минут. Авторизация на сервере производится по средствам логина и пароля, который должен быть внесён в базу данных системы хранения данных. Кодировка учётных данных в момент аутентификации производится посредством Base64.
# Библиотеки для работы c ESP8266 в среде Arduino IDE 
* ESP8266HTTPClient
* ESP8266WiFi
* WiFiClient
* Wire
* SparkFun_SHTC3 (https://github.com/sparkfun/SparkFun_SHTC3_Arduino_Library)
* ArduinoJson (https://github.com/bblanchon/ArduinoJson)
* base64 (https://github.com/Densaugeo/base64_arduino)
