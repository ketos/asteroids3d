#ifndef POINT3_H
#define POINT3_H

/***************************************************************************
Point.h
Comment:  This file contains all point definitions.
***************************************************************************/

//-----------------------------------------------------------------------------
/// Template class for vectors or points with 3 coordinates.
/**
* This is the main class for all 3d points.
* The type of the three coordinates is variable.
*/
template < typename T > class Point3 {
  
//-----------------------------------------------------------------------------
public:

  /**
  * Standard constructor. Point will be set to 0.0.
  */
  Point3() 
    : _x( 0.0 ), _y( 0.0 ), _z( 0.0 ) {};

  /**
  * Constructor with given value that will be set to all coordinates.
  * @param v - the value
  */
  Point3( const T v )
    : _x( v ), _y( v ), _z( v ) {};

  /**
  * Constructor with given values for all 3 coordinates.
  * @param x - first coordinate of this point
  * @param y - second coordinate of this point
  * @param z - third coordinate of this point
  */
  Point3( const T x, const T y, const T z ) 
    : _x( x ), _y( y ), _z( z ) {};


  /**
  * Returns the first coordinate of this point.
  * @return the \b first coordinate
  */
  T& x() { return _x; };

  /**
  * Returns the first coordinate of this point (constant).
  * @return the \b first coordinate
  */
  const T x() const { return _x; };

  /**
  * Returns the second coordinate of this point.
  * @return the \b second coordinate
  */
  T& y() { return _y; };

  /**
  * Returns the second coordinate of this point (constant).
  * @return the \b second coordinate
  */
  const T y() const { return _y; };

  /**
  * Returns the third coordinate of this point.
  * @return the \b third coordinate
  */
  T& z() { return _z; };

  /**
  * Returns the third coordinate of this point (constant).
  * @return the \b third coordinate
  */
  const T z() const { return _z; };

  /**
  * Set the coords of this point.
  * @param x - first coordinate of this point
  * @param y - second coordinate of this point
  * @param z - third coordinate of this point
  */
  void setCoords( const T x, const T y, const T z ) {
    _x = x; _y = y; _z = z;
  };

  /**
  * Operator that returns the coordinate at the given index.
  * @param i - index of the coordinate
  * @return the \b coordinate at index \em i
  */
  T& operator [] ( const int i ) {
    //assert( i < 3 );
    if ( i == 0 )
      return _x;
    if ( i == 1 )
      return _y;

    return _z;
  };

  /**
  * Operator that returns the coordinate at the given index (constant).
  * @param i - index of the coordinate
  * @return the \b coordinate at index \em i
  */
  const T operator [] ( const int i ) const {
    //assert( i < 3 );
    if ( i == 0 )
      return _x;
    if ( i == 1 )
      return _y;
    
    return _z;
  };

  /**
  * Equality operator based on the coordinates of the points.
  * @param p - point to compare with
  * @return \b true if this point is equal to p, else \b false
  */
  const bool operator == ( const Point3& p ) const {
    if ( _x == p.x() && _y == p.y() && _z == p.z() )
      return true;
    return false;
  };

  /** 
  * Operator that returns the inverted point.
  * @return the <b> inverted point </b>
  */
  const Point3 operator - () const {
    return Point3( -_x, -_y, -_z );
  };

  /**
  * Adding Operator.
  * @param p - the addend
  * @return the \b sum of the points
  */
  const Point3 operator + ( const Point3& p ) const {
    return Point3( _x + p.x(), _y + p.y(), _z + p.z() );
  };

  /**
  * Add a point to this point.
  * @param p - the addend
  */
  void operator += ( const Point3& p ) {
    _x += p.x(); _y += p.y(); _z += p.z();
  };

  /**
  * Minus operator.
  * @param p - the subtrahend
  * @return the \b difference point
  */
  const Point3 operator - ( const Point3& p ) const {
    return Point3( _x - p.x(), _y - p.y(), _z - p.z() );
  };

  /**
  * Substract a point from this point.
  * @param p - the subtrahend
  */
  void operator -= ( const Point3& p ) {
    _x -= p.x(); _y -= p.y(); _z -= p.z();
  };

  /**
  * Division operator for a single value. 
  * All coordinates will be divided by the given value.
  * @param w - the divisor
  * @return the <b> new point </b>
  */
  const Point3 operator / ( const T w ) const {
    return Point3( _x / w, _y / w, _z / w );
  };

  /**
  * Division operator for a single value. 
  * All coordinates will be divided by the given value.
  * @param w - the divisor
  * @return the <b> new point </b>
  */
  friend const Point3 operator / ( const T w, const Point3& p ) {
    return p / w;
  }

  /**
  * Divide all coordinates of this point by the given value.
  * @param w - the divisor
  */
  void operator /= ( const T w ) {
    _x /= w; _y /= w; _z /= w;
  };

  /**
  * Multiply operator for a single value. 
  * All coordinates will be multiplied with the given value.
  * @param w - the multiplier
  * @return the <b> new point </b>
  */
  const Point3 operator * ( const T w ) const {
    return Point3( _x * w, _y * w, _z * w );
  };

  /**
  * Multiply operator for a single value. 
  * All coordinates will be multiplied with the given value.
  * @param w - the multiplier
  * @return the <b> new point </b>
  */
  friend const Point3 operator * ( const T w, const Point3& p ) {
    return p * w;
  };

  /**
  * Multiply all coordinates of this point with the given value.
  * @param w - the multiplier
  */
  void operator *= ( const T w ) {
    _x *= w; _y *= w; _z *= w;
  };

  /**
  * Cross product operator.
  * @param p - another point
  * @return the <b> cross product </b> of the two points
  */
  const Point3 operator ^ ( const Point3& p ) const {
    return Point3( ( _y * p.z() ) - ( p.y() * _z ),
      ( _z * p.x() ) - ( p.z() * _x ), ( _x * p.y() ) - ( p.x() * _y ) );
  };

  /**
  * Dot product operator.
  * @param p - another point
  * @return the <b> dot product </b> of the two points
  */
  const T operator * ( const Point3& p ) const {
    return ( _x * p.x() + _y * p.y() + _z * p.z() );
  };

  /**
  * Returns the norm1 of this vector.
  * @return the \b norm1
  */
  const T norm1() const {
    return _x + _y + _z;
  };

  /**
  * Returns the norm of this vector.
  * @return the \b norm
  */
  const T norm() const {
    return sqrt( _x * _x + _y * _y + _z * _z );
  };

  /**
  * returns the squared norm of this vector
  * @return the <b> squared norm </b>
  */
  const T squaredNorm() const {
    return _x * _x + _y * _y + _z * _z;
  };

  /**
  * Normalize this point and return a new point with the calculated coordinates.
  * @return the <b> normalized point </b>
  */
  const Point3 normalized() const {
    return ( *this / norm() );
  };

  /** Normalize this point. */
  void normalize() {
    const T n = norm();
    _x /= n; _y /= n; _z /= n;
  };

  /**
  * Get the angle between this vector and another vector.
  * @param p - another vector
  * @return the \b angle between the vectors
  */
  const T getAngle( const Point3& p ) const {
    const T w = norm() * p.norm();
    if ( w == 0 ) return 0;
          T t = ( *this * p ) / w;
    if( t > 1 ) t = 1;
    else if( t < -1 ) t = -1;
      return acos( t );
  };

  /** 
  * Get the cotan angle between this vector and another vector.
  * @param p - another vector
  * @return the <b> cotan angle </b> between the vectors
  */
  const T getCotanAngle( const Point3& p ) const {
    return ( ( *this * p ) / ( *this ^ p ).norm() );
  };

  /**
  * Slerp interpolation.
  * @param p - the other vector
  * @param w - the weight
  * @param alpha - the angle
  */
  const Point3 slerp( const Point3& p, const double w, 
    const double alpha ) const 
  {
    const double sina = sin( alpha );
    if ( sina )
      return ( *this * ( sin( ( 1-w ) * alpha ) / sina )
        + p * ( sin( w * alpha ) / sina ) );
    
    return *this;
  };

  /**
  * Slerp interpolation.
  * @param p - the other vector
  * @param w - the weight
  */
  const Point3 slerp( const Point3& p, const double w ) const 
  {
    return slerp( p, w, this->getAngle( p ) );
  };

  /** 
  * Write a point to the given stream.
  * @param s - the stream
  * @param p - the point
  */
  friend std::ostream& operator << ( std::ostream& s, const Point3& p )  {    
    /*s << "x: " << p.x() << " ";
    s << "y: " << p.y() << " ";
    s << "z: " << p.z() << std::endl;*/

    s  << p.x() << "," << p.y()<< "," <<p.z() << std::endl;
    
    return s;
  };

  /**
  * Average the point and the given point.
  * @param p - the point
  * @param numAvg - the number of done averages
  */
  const Point3 average( const Point3& p, int& numAvg ) const {
    const int old = numAvg++;
    if ( !old ) return p;
    return ( ( *this * old ) + p ) / numAvg;
  };

  /**
  * Get an orthogonal vector to this vector.
  */
  const Point3 getOrthogonal() const {
    Point3 temp( 1, _y, _z );
    if ( _y < _x && _y <= _z )
      temp = Point3( _x, 1, _z );
    else if ( _z < _x && _z <= _y )
      temp = Point3( _x, _y, 1 );
    return ( temp ^ *this );
  };

  /**
  * Set a random coordinates -1..1.
  * Warning: no srand() init is done!
  */
  static const Point3 random() 
  {
    const int rmax = RAND_MAX;

    return Point3( 
             (T) ( 2*rand() ) / rmax - 1,
             (T) ( 2*rand() ) / rmax - 1,
             (T) ( 2*rand() ) / rmax - 1 
           );
  };

//-----------------------------------------------------------------------------
private:

  /** The first coordinate. */
  T _x;
  /** The second coordinate. */
  T _y;
  /** The third coordinate. */
  T _z;

};

#endif
