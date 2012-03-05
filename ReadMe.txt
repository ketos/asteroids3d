Um das Programm zu Kompilieren build.sh ausführen.
Um das Programm zu starten run.sh ausführen.

Um das Doxygen zum bauen braucht man graphviz,
danach nur doxygen doxconf eingeben.
(meine Lieblingsseite im Doxygen: .doc/html/Asteorid_8cpp.html)

Ich find die Game lustiger

Steuerung:
    Menü:
        Enter   : Startet das Spiel
        H       : Zeigt den Highscore
    Spiel:
        W       : erhöht die Geschwindigkeit
        S       : bremst das Raumschiff 
        Pfeil Hoch  : hebt die Nase des Raumschiffs
        Pfeil Runter: senkt die Nase des Raumschiffs
        Pfeil Links : fliegt nach links, und rollt nach links
        Pfeil Rechts: fliegt nach rechts und rollt nach rehts
        Space   : Schiessen
        1       : Ego Perspektive
        2       : Third-Person
        3       : Cockpit
        
        9       : Kamera von Schiff entfernen
        0       : Kamera näher zum Schiff
        Bild rauf   : Kamera höher
        Bild runter : Kamera niedriger
        Escape      : Bewegung auf 0 (nur zu Testzwecken)

    Joystick (XBox360 Wireless)
        Linker Analogstick : Steuern (links/rechts/hoch/runter)
        Linker Trigger  : Beschleunigen
        Rechter Trigger : Bremsen
        A               : Schiessen
        B               : Perspektive 1
        X               : Perspektive 2
        Y               : Perspektive 3
        
        LB              : Kamera entfernen
        RB              : Kamera ranholen
        Rechter Analogstick : Kamera steuern (hoch/runter/rechts/links) (Debugzwecke)
        Start           : Bewegung auf 0 (nur zu Testzwecken)

benötigte Packages:
sudo apt-get install joystick
