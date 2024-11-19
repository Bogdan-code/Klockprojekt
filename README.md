# README

## Översikt

Det här projektet är en Arduino-applikation som använder en DS3231 realtidsklocka för att läsa aktuell tid och temperatur. Informationen visas på en OLED-skärm, och en servo motor justeras baserat på temperaturen. Dessutom finns det funktionalitet för att styra LED-lampor (kommenterad kod) och läsa från en analog ingång.

## Komponenter och bibliotek

- **Arduino** (eller kompatibel mikrokontroller)
- **DS3231** realtidsklocka
- **OLED-skärm** med SSD1306-driver
- **Servo** motor
- **LED-lampor** (valfritt, se kommenterad kod)
- **Bibliotek**:
  - `U8glib.h` för OLED-skärmen
  - `RTClib.h` för DS3231-klockan
  - `Wire.h` för I2C-kommunikation
  - `Servo.h` för servo kontroll

## Funktionsbeskrivning

### setup()

- **Initiering av pins**: Sätter digitala pins 4 till 6 som utgångar och A1 som ingång.
- **Seriell kommunikation**: Startar seriell kommunikation med en baudrate på 9600.
- **I2C-kommunikation**: Initierar I2C-bussen.
- **Realtidsklocka**: Startar DS3231 och ställer in tiden till kompileringstid.
- **Servo**: Fäster servon till pin 9 och sätter startpositionen till 0 grader.

### loop()

- **Läser aktuell tid och temperatur** från DS3231.
- **Visar tid och temperatur** på OLED-skärmen via funktionen `oledWrite()`.
- **Justerar servo** baserat på aktuell temperatur via funktionen `servoWrite()`.
- **Skriver temperatur till seriell monitor**.
- **Fördröjning**: Väntar 1 sekund innan loopen upprepas.

### getTemp()

- **Returnerar temperaturen** från DS3231-klockan som en flyttal.

### oledWrite(String time, float temp)

- **Visar tid och temperatur på OLED-skärmen**.
- **Använder U8glib** för att skriva textsträngar på specifika positioner på skärmen.

### getTime()

- **Hämtar aktuell tid från DS3231**.
- **Formaterar tiden** som en sträng i formatet "Time: hh:mm:ss".

### servoWrite(float value)

- **Mappar temperaturvärdet** från intervallet 17-27 grader till servo-positioner mellan 0 och 179 grader.
- **Skriver positionen till servon** för att justera dess vinkel baserat på temperaturen.

## Anmärkningar

- **LED-styrning**: Det finns en kommenterad funktion `alarm()` som kan användas för att blinka LED-lampor.
- **Tidsjustering**: För att ställa in en specifik tid, avkommentera raden med `rtc.adjust(DateTime(2019, 1, 21, 5, 0, 0));` och ange önskad tid.
- **Temperaturavläsning**: Temperaturen från DS3231 används både för display och för att styra servon.
- **Felhantering**: Koden förutsätter att alla komponenter fungerar korrekt; ingen felhantering är implementerad.

## Installation och användning

1. **Montera hårdvaran** enligt komponentlistan och anslutningsschemat för respektive komponent.
2. **Installera nödvändiga bibliotek** i Arduino IDE:
   - U8glib
   - RTClib
   - Servo
3. **Ladda upp koden** till din Arduino.
4. **Öppna seriell monitor** (valfritt) för att se temperaturutskrifter.
5. **Observera OLED-skärmen** för aktuell tid och temperatur.
6. **Observera servon** som justeras baserat på temperaturen.

## Felsökning

- **Ingen display på OLED-skärmen**:
  - Kontrollera I2C-anslutningarna.
  - Se till att rätt I2C-adress används.
- **Felaktig tid eller temperatur**:
  - Kontrollera att DS3231 är korrekt ansluten.
  - Testa att justera tiden manuellt.
- **Servon rör sig inte**:
  - Kontrollera anslutningen till servon.
  - Se till att servon får tillräcklig ström.
