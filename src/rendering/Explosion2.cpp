#include "Explosion2.hpp"


double Explosion::newRandom(const double radius){
        return (2.0*radius * ((GLdouble) rand()) / ((GLdouble) RAND_MAX)) - radius;
}

void Explosion::newSpeed (Point3d &destination, const double radius)
{
        float   x, y, z;
        
        x = newRandom(radius);
        y = newRandom(radius);
        z = newRandom(radius);
        
        destination.x() = x;
        destination.y() = y;
        destination.z() = z;
        destination.normalize();
}

void Explosion::display(){
        
        glDisable(GL_LIGHTING);
        glEnable (GL_BLEND); 
        glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glClear(GL_ACCUM_BUFFER_BIT);
                        
        glPushMatrix();
        glTranslated(center.x(), center.y(), center.z());
        
        int max = 5;
        for(int i = 0; i < max; i++) {
            displayParticles();
            displayDebris();
            glAccum(GL_ACCUM, 1.f/(max-i));
        } 
        glAccum(GL_RETURN, 1.f);
        
        glPopMatrix();
        glDisable(GL_BLEND);
        glEnable(GL_LIGHTING);
}

Explosion::~Explosion(){

};

Explosion::Explosion (const Point3<double> &center, const double radius, const int particleNum, const int debrisNum)
: particleNum(particleNum), debrisNum(debrisNum), radius(radius), center(center){
        

        
        for (int i = 0; i < particleNum; i++){
                particle p;
                newSpeed (p.speed,2);
                p.alpha = 1.0;
                p.position=p.speed*radius/5.0;
                p.color = RGBd(1.0, 1.0, 0.0);
                particles.push_back(p);
        }
        
        for (int i = 0; i < debrisNum; i++){
                debris d;
                d.alpha = 1.0;
                d.scale[0] = 1.0 + newRandom();
                d.scale[1] = 1.0 + newRandom();
                d.scale[2] = 1.0 + newRandom();
                d.scale *= 5.0;
                d.color = RGBd(0.9, 0.1, 0.0);
                newSpeed (d.speed,4);
                newSpeed (d.rotationSpeed,5.0);
                
                debrises.push_back(d);
        }
        fuel = 300;
        colorRatio = 1.0/ (double)fuel;
        
}

void Explosion::displayParticles(){
        
        glPointSize(2.0f);
        glEnable(GL_POINT_SMOOTH);
        glBegin(GL_POINTS);
        
        std::vector <particle>::iterator it = particles.begin();
        
        for (; it<particles.end(); it++)
        {
                const RGBd rgb = it->color;
                glColor4d(rgb.r(), rgb.g(), rgb.b(), it->alpha);
                
                glVertex3d (it->position[0], it->position[1], it->position[2]);
                
                it->position += tau * it->speed;
                
                
                it->color[1] -= colorRatio;
                it->alpha -= colorRatio/2.0;
        }
                
        glEnd();
        glDisable(GL_POINT_SMOOTH);
        
}

void Explosion::displayDebris(){
        
        std::vector <debris>::iterator it = debrises.begin();
        
        for (; it < debrises.end(); it++)
        {
                const RGBd rgb = it->color;
                glColor4d(rgb.r(), rgb.g(), rgb.b(), it->alpha);
                glPushMatrix ();
                
                glTranslated (it->position[0],
                                          it->position[1],
                                          it->position[2]);
                
                glRotated (it->rotation[0], 1.0, 0.0, 0.0);
                glRotated (it->rotation[1], 0.0, 1.0, 0.0);
                glRotated (it->rotation[2], 0.0, 0.0, 1.0);
                
                glScaled (it->scale[0], it->scale[1], it->scale[2]);
                
                glBegin (GL_TRIANGLES);
                glVertex3d (0.0, 0.5, 0.0);
                glVertex3d (-0.25, 0.0, 0.0);
                glVertex3d (0.25, 0.0, 0.0);
                glEnd ();
                glPopMatrix();
                
                it->alpha -= colorRatio;
                it->position+=tau * it->speed;
                it->rotation+= 3.0 * it->rotationSpeed;
                
        }
        
}

void Explosion::step(const double tau){
        fuel -= tau;
        this->tau = tau;
}
