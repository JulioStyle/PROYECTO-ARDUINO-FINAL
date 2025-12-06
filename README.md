# PROYECTO-ARDUINO-FINAL


Nuestro proyecto  tiene como propósito crear un reloj digital que muestre en una pantalla OLED la hora y la fecha actuales obtenidas desde un módulo RTC. De esta manera garantizamos una visualización precisa y estable incluso si dejamos de alimentar al microcontrolador ya que el RTC cuenta con una batería externa. En nuestro sistema utilizamos el bus I2C para comunicarnos con ambos dispositivos y este actualiza la pantalla cada segundo.

Componentes:

RTC, Oled, placa ESP32-S3

Conexiones:

RTC:
GND: Al gnd de la placa
VCC: Al pin de 3v3
SDA: Al pin 8 de la placa
SCL: Al pin 9 de la placa

OLED:
GND: Al gnd de la placa
VCC: Al pin de 3v3
SDA: Al pin 8 de la placa
SCL: Al pin 9 de la placa

