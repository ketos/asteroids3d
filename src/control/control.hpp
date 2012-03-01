    
#ifndef __CONTROL_H__
#define __CONTROL_H__

/**
 * @brief einige Konstanten für die Steuerung
 */
#define DEADZONE 5000.0 // Deazone für die Achsen des Joysticks
#define JOYMAX 32767.0  // Maximalwerte der Joystickachsen

#define ANGLE 0.05      // Änderung des Winkel bei Tastendruck, bzw Maximale winkeländerung bei Joystick
#define SPEED 2         // Speedänderung bei Tastendruck / Joystick
#define REDUCE 0.001    // Winkelverkleinerung über die Zeit    
#define MAXANGLE 0.2    // Maximal möglicher Flugwinkel
#define BRAKE -0.5       // Bremsung

#endif
