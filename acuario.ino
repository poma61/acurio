#include <TimeLib.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Definir constantes
#define ANCHO_PANTALLA 128  // ancho pantalla OLED
#define ALTO_PANTALLA 64    // alto pantalla OLED

// Objeto de la clase Adafruit_SSD1306
Adafruit_SSD1306 display(ANCHO_PANTALLA, ALTO_PANTALLA, &Wire, -1);

//luz pecera
int active = 8;

String status_pecera = "Acua. OFF";

//editable
String hora_active = "13:00";
String hora_disable = "00:20";
String reloj = "";
int hora = 12;
int minutos = 55;
//editable

void setup() {
  //hora
  setTime(hora, minutos, 0, 13, 12, 2016);  //hora,m,s,dia,mes,year
  //relay (luz pecera)
  pinMode(active, OUTPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
}

void loop() {
  reloj = clock();
  showDisplay(reloj);

  if (reloj.substring(0, 5) == hora_active) {
    digitalWrite(active, HIGH);
    status_pecera = "Acua. ON";
  }
  if (reloj.substring(0, 5) == hora_disable) {
    digitalWrite(active, LOW);
    status_pecera = "Acua. OFF";
  }

  delay(1000);  //1s
}

String parseNumber(int dig) {
  String dt = "0" + String(dig);
  return dt.substring(dt.length() - 2);
}

String clock() {
  return parseNumber(hour()) + ":" + parseNumber(minute()) + ":" + parseNumber(second());
}

void showDisplay(String message) {
  display.clearDisplay();
  // Tamaño del texto
  display.setTextSize(2);
  // Color del texto
  display.setTextColor(SSD1306_WHITE);
  // Posición del texto
  // display.setCursor(x, y);
  display.setCursor(10, 0);
  //texto
  display.print(message);

  // Posición del texto
  display.setCursor(0, 17);
  display.print("ON  " + hora_active);
  display.setCursor(0, 32);
  display.print("OFF " + hora_disable);

  display.setCursor(0, 47);
  display.print(status_pecera);

  // Enviar a pantalla
  display.display();
}