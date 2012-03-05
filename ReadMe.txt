Um das Programm zu Kompilieren build.sh ausführen.
Um das Programm zu starten run.sh ausführen.

Um das Doxygen zum bauen braucht man graphviz,
danach nur doxygen doxconf eingeben.
(meine Lieblingsseite im Doxygen: ./doc/html/Game_8hpp.html)

Steuerung:
    Menü:
        Enter           : Startet das Spiel
        H               : Zeigt den Highscore
    Spiel:
        W               : Beschleunigt das Schiff
        S               : Bremst das Schiff
        Pfeil Hoch      : Nase hoch
        Pfeil Runter    : Nase runter
        Pfeil Links     : Nase links
        Pfeil Rechts    : Nase rechts
        1               : Ansicht außen 1
        2               : Ansicht außen 2
        3               : Ansicht Cokpit
        
        9               : Kamera von Schiff entfernen
        0               : Kamera näher zum Schiff
        Bild rauf       : Kamera höher
        Bild runter     : Kamera niedriger
        Escape          : Bewegung auf 0 (nur zu Testzwecken)

    Joystick (XBox360 Wireless) (nur im Spiel)
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
joystick, libxmu, libxi, libglu, libqt4, libsdl, libsdl-mixer, libopengl
