//Librerias para poder usar el display
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
//Librerias para poder usar el rtc
#include <RTClib.h>

// Pines I2C que los usamos para comunicar el ESP32-s3 con la pantalla y el RTC
#define I2C_SDA 8
#define I2C_SCL 9

// Dimensiones del OLED
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

//Creamos un objeto 'display' para controlar el OLED
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

//Cremaos un objeto RTC para manejar nuestro reloj
RTC_DS1307 rtc;

void setup() {
  Serial.begin(115200);//Inicia comunicación serie
  Wire.begin(I2C_SDA, I2C_SCL);//Inicializa bus I2C con los pines definidos

// COMPROBACIONES: 

  // Escaneo de bus I2C para ver si tanto elOLED como el RTC están conectados correctamente
  Serial.println("Escaneando bus I2C...");
  byte error, address;
  int nDevices = 0;

  // Escaneamos todas las direcciones posibles del bus I2C
  for(address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    error = Wire.endTransmission();
    //Si el valor de error es 0 enotnces significa que nuestro dispositivo se ha encontrado correctamnete
    if(error == 0){
      Serial.print("Dispositivo encontrado en 0x");
      Serial.println(address, HEX);
      nDevices++;
    }
  }
  //En el caso de que nuestra variable nDevices siga a 0 mostraremos este mensaje ya que significa que no se han encontrado los dispositivos
  if(nDevices == 0) Serial.println("No se encontraron dispositivos I2C");
  Serial.println("Escaneo completado\n");

  // Inicializar OLED, display.begin() devuelve false si no se detecta el display
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {//// la direccion I2C del OLED
    Serial.println("Error: OLED no detectado");
    while(1);//Entramos en un bucle infifnito para evitar futuros errores
  }
  display.clearDisplay();//Vacia la pantalla
  display.setTextColor(SSD1306_WHITE);//Color del texto

  // Lo mismo que en el oled, rtc.begin() devuelve false si el módulo no responde
  if(!rtc.begin()) {
    Serial.println("RTC no encontrado, revisa conexiones");
    while(1);//Entramos en un bucle infifnito para evitar futuros errores
  }
  Serial.println("RTC detectado correctamente");

  // Esta linea sirve para que cuando se incialice el RTC tenga la hora actual del dispositivo ya que en caso contrario se quedaria con la de la ultima vez
   rtc.adjust(DateTime(__DATE__, __TIME__));
}

void loop() {
  //Obtenemos tanto la hora como la actual desde el RTC
  DateTime tiempo = rtc.now();

  // Limpiar pantalla
  display.clearDisplay();

  // Horas
  display.setTextSize(2);//Tamaño de la hora
  display.setCursor(0,0);// Su respectiva posición

  display.print(tiempo.hour());//Mostramos la hora
  display.print(":");//Separador
  // Minutos
  if(tiempo.minute() < 10) display.print("0"); // En este if lo que hacemos es que si los minutos son menores que 10 le ponemos un 0 delante de los mins
  display.print(tiempo.minute());//Mostramos los minutos
  display.print(":");//Separador
  //Segundos
  if(tiempo.second() < 10) display.print("0");//Mismo procedimiento de los minutos si el numeroes menor que 10 solo que con los segundos
  display.println(tiempo.second());

  // Mostramos la fecha 
  display.setTextSize(1);// Ponemos a la fecha un tamaño mas pequeño que a la hora para mejor distinción
  display.setCursor(0,40);// Posicion 

  display.print(tiempo.day());//Dia 
  display.print("/");
  display.print(tiempo.month());//Mes
  display.print("/");
  display.println(tiempo.year());//Año

  display.display();
  delay(1000);
}
