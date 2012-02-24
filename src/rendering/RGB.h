/*
 *  RGB.h
 *  GLRender
 *
 *  Created by Patrick zulian on 5/18/10.
 *  Copyright 2010 University  of Lugano. All rights reserved.
 *
 */


template < typename T = double >
class RGB
{
private:
        T _r, _g, _b;
        
        T _clamp (T value)
        {
                if (value < (T) 0.0)
                        value = (T) 0.0;
                if (value > (T) 1.0)
                        value = (T) 1.0;
                return value;
        }
        
public:
        
        RGB (const T r, const T g, const T b) : _r(r), _g(g), _b(b) {}
        RGB () : _r(0), _g(0), _b(0) {}
        
        
        
        T r () const { return _r; }
        T g () const { return _g; }
        T b () const { return _b; }
        
        const RGB operator + (const RGB &rgb) const
        {
                return RGB(_r + rgb.r(), _g + rgb.g(), _b + rgb.b());
        }
        
        const RGB operator - (const RGB &rgb) const 
        {
                return RGB(_r - rgb.r(), _g - rgb.g(), _b - rgb.b());
        }
        
        const RGB operator * (const RGB &rgb) const
        {
                return RGB(_r * rgb.r(), _g * rgb.g(), _b * rgb.b());
        }       
        
        const RGB operator * (const T l) const
        {
                return RGB(_r * l, _g * l, _b * l);
        }
        
        
        friend const RGB operator * (const T lambda, const RGB &rgb)  
        {
                return rgb * lambda;
        }
        
        void clamp()
        {
                _r = _clamp(_r); _g = _clamp(_g); _b = _clamp(_b);
        }
        
        const T operator [] ( const int i ) const {
                
                if ( i == 0 )
                        return _r;
                if ( i == 1 )
                        return _g;
                
                return _b;
        }
        
        
         T &operator [] ( const int i ) {
                
                if ( i == 0 )
                        return _r;
                if ( i == 1 )
                        return _g;
                
                return _b;
        }

};
