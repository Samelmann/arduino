# SMS-gesteuerter Garagenöffner

Dieses Projekt ermöglicht es, ein Garagentor per SMS zu öffnen – mithilfe eines Arduino MKR GSM 1400  
und eines angeschlossenen Funksenders oder Relais, das einen Tasterimpuls simuliert.

## Funktionen

- Öffnet die Garage bei Empfang eines gültigen SMS-Passworts
- Passwortliste im Code gespeichert
- "Testegarage"-Modus zum 3-maligen Öffnen zu Testzwecken
- Reconnect-Logik bei GSM-Verbindungsverlust
- Reset des GSM-Moduls nach ca. 24 Stunden
- Erweiterung: Passwortänderung per SMS (optional)

## Hardware

- Arduino MKR GSM 1400 oder ähnliches GSM-fähiges Board
- SIM-Karte mit SMS-Funktion
- Relais oder Transistor, der den Garagentaster überbrückt
- (Optional: LED zur Statusanzeige)

## Pinbelegung

| Funktion         | Pin |
|------------------|-----|
| GSM Reset        | 4   |
| Garagenöffner    | 0   |
| Status-LED       | LED_BUILTIN |
| Dauerstrom-Pin   | 6   |

## Sicherheit

- Nur bekannte Passwörter führen zur Garagenöffnung
- Telefonnummernfilter ist (noch) nicht implementiert – kann erweitert werden

## Installation

1. Arduino MKR GSM in der Arduino IDE konfigurieren
2. Library `MKRGSM` installieren
3. Datei `arduino_secrets.h` anlegen mit folgendem Inhalt:

```cpp
#define SECRET_PINNUMBER "1234"
