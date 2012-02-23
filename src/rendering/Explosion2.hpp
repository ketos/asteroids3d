#ifndef EXPLOSION_H
#define EXPLOSION_H


#include <QtOpenGL>
//#include "WMaterial.h"
#include "Point3.h"
#include "RGB.h"


class Explosion{
        typedef Point3 < double > Point3d;
        
        typedef RGB < double > RGBd;

        typedef struct particle{
                Point3d position;
                Point3d speed;
                RGBd color;
                double alpha;
        } particle;
        
        typedef struct debris{
                Point3d position;
                Point3d speed;
                Point3d rotation;        /* Rotation angles around x, y, and z axes */
                Point3d rotationSpeed;
                
                RGBd color;
                double alpha;
                Point3d scale;
        } debris;
        
        
private:
        std::vector<particle> particles;
        std::vector<debris> debrises;
        int fuel, particleNum, debrisNum;
        double colorRatio, tau, radius;
        Point3d center;

        
public:
        Explosion() {  };
        
        Explosion(const Point3<double>& center, const double radius=1.0, const int particleNum=200, const int debrisNum=20);
        
        virtual ~Explosion();
        
        double newRandom(const double radius=1.0);
        
        void newSpeed (Point3d &destination, const double radius=1.0);
        
        void display();
        
        inline bool isFinished(){return fuel <= 0;};
        
        inline void finish() { fuel = 0; }
        
        inline
        const Point3d & getCenter() { return center; }
        void displayParticles();
        
        void displayDebris();
        
        void step(const double tau);
        
};

#endif
