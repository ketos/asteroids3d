/**
 * @brief keyboard.hpp
 * 
 * @author gruppe3
 */
    
#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include <QKeyEvent>
#include <set>
/**
 * @brief verwaltet die Tastatureingaben und leitet sie weiter
 */
class Keyboard
{
public:
    /**
     * @brief Bekommt die gedrückte Taste übergeben und packt diese in die Liste
     *
     * @param e KeyEvent enthält die gedrückte Taste
     */
	static void keypressed(QKeyEvent* e);
    
    /**
     * @brief Bekommt die losgelassene Taste übergeben und löscht diese aus der Liste
     *
     * @param e KeyEvent enthält die losgelassene Taste
     */
	static void keyrelease(QKeyEvent* e);
    
    /**
     * @brief Geht alle Tasten durch und führt die hinterlegten Aktionen aus
     */
    static void update();
protected:
    /**
     * @brief enthält die gedrückten Tasten
     */
    static std::set<int> m_pressedKeys;
};

#endif
