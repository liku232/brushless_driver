# Lastenheft 

## Projekt: 3-Phasen Inverter 
* Es soll ein 3-Phasen Wechselrichter entwickelt werden und die 3 Halb Brücken aus je 2 N-MOSFETs über einen µC angesteuert werden. Der Inverter soll eine Strombegrenzung inkludieren.

## Gruppenmitglieder:
* Menzel Luka
* Schuecker Daniel
* Hofer Phillip
* Dindar Abduerrasit

## Rollenverteilung:
* Menzel Luka: Hardware
* Dindar Abduerrasit: Dokumentation
* Schuecker Daniel:   Software
* Hofer Phillip: 

## Anforderungen
* Req 1: Der Inverter besteht aus 3 Halbbrücken aus je zwei N-Channel MOSFETs
* Req 2: Alle MOSFETs werden über MOSFET-Treiber angesteuert
* Req 3: Zwischenkreisspannung: 24V
* Req 4: Phasenstrom: 20A max
* Req 5: Induktive Strommessung an jeder Phase
* Req 6: Bei Überstrom an einer Phase kann der µC die Gates nicht mehr ansteuern
* Req 6.1: Ein derartiger Stromfehler wird über eine LED angezeigt. Der µC kann mittels Knopfdruck wieder mit dem Motor verbunden werden  
* Req 6.2: PWM Schaltfrequenz: 50 kHz
* Req 7: Ansteuerung ueber µC

## Ziele
* Festlegen welche Schaltfrequenz, welche Zwischenkreisspannung und welchen Ausgangsstrom verwendet wird
* Stromabsicherungsschaltung aufbauen und testen
* Simulation von der Strombegrenzung machen
* Stromsensorauswahl
* Gate steuerung fuer jede halbbruecke

## Erreichte Ziele
* Die Schaltfrequenz, Zwischenkreisspannung und Ausgangsstrom wurde bestimmt
* Simulation von der Strombegrenzung gemacht
