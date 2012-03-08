/**
 * @file   Bullet.hpp
 * @author gruppe3
 */

#ifndef BULLET_HPP_
#define BULLET_HPP_

#include "TexturedMesh.hpp"
#include <GL/glu.h>
#include <GL/glut.h>
#include <QThread>
#include "math/glVector.hpp"
#include "io/SoundManager.hpp"
#include <stdio.h>

/**
 * @brief represents a bullet, shoot from a Fighter
 */
class Bullet: public TexturedMesh, public QThread
{
        public:
            /**
             * @brief Contructor. Build a seeking bullet on the given Fighter's
             *                      position.
             * @param   fighter_position   Position of the fighter that shoots this bullet
             * @param   fighter_axis   Axis the bullet will move on
             * @param   asteorid    The Asteroid
             */
             Bullet(glVector<float> fighter_position, glVector<float> fighter_axis, glVector<float> asteorid);

            /**
             * @brief Contructor. Build a bullet on the given Fighter's
             *          position. The bullet will move on the
             *          given axis.
             * @param   fighter_position   Position of the fighter that shoots this bullet
             * @param   fighter_axis   Axis the bullet will move on
             */
             Bullet(glVector<float> fighter_position, glVector<float> fighter_axis);

            /**
             * @brief Moves the bullet until it's lifetime is over.
             */
             void run();

            /**
             * @brief kills the bullet
             */
             void kill();

            /**
             * @brief  returns position
             * @return returns a float position
             */
             glVector<float> getPosition();

            /**
             * @brief returns position
             * @param xA x part of axis
             * @param yA y part of axis
             * @param zA z part of axis
             */
             void setAxis(glVector<float> xA, glVector<float> yA, glVector<float> zA);
    

            /**
             * @brief Returns the status of this bullet.
             * @return false, if the bullet's lifetime is over and true otherwise
             */
             bool isAlive();

        private:
            // lifetime of the bullet, how long it's visible
            static const int lifetime = 9000;

            // true, if the bullet's lifetime isn't over yet
            bool alive;

            // axis, the bullet is moving on (one of the shooting fighter's axes)
            glVector<float> fighter_axis;

            // speed of the bullet
            static float b_speed;

            // target
            glVector<float> target;

            // searching for target
            bool seeking;
};


#endif /* BULLET_HPP_ */
