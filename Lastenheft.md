# Lastenheft: 3-Phasen Inverter 
* Es soll ein 3-Phasen Wechselrichter entwickelt werden. Es sollen 3 H-Brücken aus je 2 N-MOSFETs über einen µC angesteuert werden.
## Anforderungen
* Req 1: Der Inverter besteht aus 3 Halbbrücken aus je zwei N-Channel MOSFETs
* Req 2: Alle MOSFETs werden über MOSFET-Treiber angesteuert
* Req 3: Zwischenkreisleistung: 24V
* Req 4: Phasenstrom: 20A max
* Req 5: Induktive Strommessung an jeder Phase
* Req 6.1: Bei Überstrom an einer Phase kann der µC die Gates nicht mehr ansteuern
* Req 6.2: Ein derartiger Stromfehler wird über eine LED angezeigt. Der µC kann mittels Knopfdruck wieder mit dem Motor verbunden werden  
* Req 6: PWM Schaltfrequenz: 50 kHz
* Req 7: Ansteuerung ueber µC
