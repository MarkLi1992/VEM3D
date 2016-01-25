// GUIDA

// Classe Point
// Memorizza la posizione del punto, la soluzione calcolata in esso.


#ifndef Point_h
#define Point_h



#include <array>
#include <vector>
#include <math.h>
#include <memory>
#include <cmath>
#include "Mesh.h"
#include "MeshPoint.h"

using namespace std;

template <long embedded, typename real>
class Polygon;

template <long embedded, typename real>
class Polyhedron;

template <long embedded, typename real>
class MeshPoint;

template <long embedded2,typename baseElement,OpenEnum isOpen,typename real2>
class Mesh;

template <typename real>
class Mesh3D;

template <typename real>
class Mesh2D;

template <long embedded,typename real=double>
class Point {
	
protected:
	// PROPERTIES
	array<real,embedded> coordinates;
		
public:
	// CONSTRUCTORS
	Point(const array<real,embedded>& inputArray);
	Point(const Point<embedded,real>& inputPoint);
	Point(const MeshPoint<embedded,real>& inputPoint);
	Point():coordinates({}) {
		for (int i=0; i<embedded; i++) {
			coordinates[i]=0;
		}
	};
	//constructor with variadic template: http://stackoverflow.com/questions/8158261/templates-how-to-control-number-of-constructor-args-using-template-variable
	template <typename... Args>
	Point(Args... arguments):coordinates{static_cast<real>(arguments)...} {
		static_assert(sizeof...(Args)==embedded,"wrong number of input paramethers");
	};
	
	
	// STANDARD METHOS
	long maxIndex() const;
	long maxAbsIndex() const;
	real norm() const;  // L2 norm of the vector
	real normL1() const; // L1 norm of the vector
	string write() const;
	
	real& x();
	real x() const;
	real& y();
	real y() const;
	real& z();
	real z() const;
	
	
	// OPERATORS
	Point<embedded,real>& operator=(Point<embedded,real> inputPoint); // be careful, it copies only the coordinates, not the other things
	bool operator==(const Point<embedded,real>& inputPoint) const; // It compares only coordinates
	bool operator!=(const Point<embedded,real>& inputPoint) const; // It compares only coordinates
	real& operator[](long index);
	real operator[](long index) const;

	
	
	// EXTERNAL METHODS
	// Operators mainly. They work in the usual way
	template<long embedded2,typename real2>
	friend ostream& operator<<(ostream& os,const Point<embedded2,real2>&point);
	template <long embedded2,typename real2>
	friend Point<embedded2,real2> operator+(const Point<embedded2,real2>& point1,const Point<embedded2,real2>& point2);
	template <long embedded2,typename real2>
	friend Point<embedded2,real2> operator-(const Point<embedded2,real2>& point1,const Point<embedded2,real2>& point2);
	template <long embedded2,typename real2>
	friend Point<embedded2,real2> operator-(const Point<embedded2,real2>& point1);
	template <long embedded2,typename real2>
	friend real2 operator*(const Point<embedded2,real2>& point1,const Point<embedded2,real2>& point2);
	template <long embedded2,typename real2>
	friend Point<embedded2,real2> operator*(long double coefficient,const Point<embedded2,real2>& point);
	template <long embedded2,typename real2>
	friend Point<embedded2,real2> operator*(const Point<embedded2,real2>& point,long double coefficient);
	template <long embedded2,typename real2>
	friend Point<embedded2,real2> operator/(const Point<embedded2,real2>& point,long double coefficient);
	template <long embedded2,typename real2>
	friend Point<embedded2,real2> cross(const Point<embedded2,real2>& point1,const Point<embedded2,real2>& point2);
	template <long embedded2,typename real2>
	friend Point<embedded2,real2> prodTermByTerm(const Point<embedded2,real2>& point1,const Point<embedded2,real2>& point2);

};




///////////////////
// CONSTRUCTORS  //
///////////////////

template <long embedded,typename real>
Point<embedded,real>::Point(const array<real,embedded>& inputArray):coordinates(inputArray) {
}

template <long embedded,typename real>
Point<embedded,real>::Point(const Point<embedded,real>& inputPoint):coordinates(inputPoint.coordinates) {
}

template <long embedded,typename real>
Point<embedded,real>::Point(const MeshPoint<embedded,real>& inputPoint):coordinates(inputPoint.coordinates) {
}


///////////////////////
// STANDARD METHODS  //
///////////////////////

// maxIndex
template <long embedded,typename real>
long Point<embedded,real>::maxIndex() const{
	long maxIndex=0;
	real maxValue=coordinates[0];
	
	for (long i=1; i<embedded; i++) {
		if (coordinates[i]>maxValue) {
			maxIndex=i;
			maxValue=coordinates[i];
		}
	}
	return maxIndex;
}

// maxAbsIndex
template <long embedded,typename real>
long Point<embedded,real>::maxAbsIndex() const{
	long maxIndex=0;
	real maxValue=abs(coordinates[0]);
	
	for (long i=1; i<embedded; i++) {
		if (abs(coordinates[i])>maxValue) {
			maxIndex=i;
			maxValue=abs(coordinates[i]);
		}
	}
}

// norm
template <long embedded,typename real>
real Point<embedded,real>::norm() const{
	double sum=0;
	for (int i=0; i<embedded; i++) {
		sum+=coordinates[i]*coordinates[i];
	}
	return sqrt(sum);
}

// normL1
template <long embedded,typename real>
real Point<embedded,real>::normL1() const{
	double sum=0;
	for (int i=0; i<embedded; i++) {
		sum+=abs(coordinates[i]);
	}
	return sum;
}

// write
template <long embedded,typename real>
string Point<embedded,real>::write() const{
	string output="";
	for (int i=0; i<embedded-1; i++) {
		output+=(to_string(coordinates[i])+",");
	}
	output+=to_string(coordinates[embedded-1]);
	return output;
}



/////////////////////////////
// TEMPLATE SPECIALIZATION //
/////////////////////////////

// x
template <long embedded,typename real>
real& Point<embedded,real>::x() {
	static_assert(embedded>=1,"embedded lower than 1");
	return coordinates[0];
}
template <long embedded,typename real>
real Point<embedded,real>::x() const{
	static_assert(embedded>=1,"embedded lower than 1");
	return coordinates[0];
}

// y
template <long embedded,typename real>
real& Point<embedded,real>::y() {
	static_assert(embedded>=2,"embedded lower than 2");
	return coordinates[1];
}
template <long embedded,typename real>
real Point<embedded,real>::y() const{
	static_assert(embedded>=2,"embedded lower than 2");
	return coordinates[1];
}

// z
template <long embedded,typename real>
real& Point<embedded,real>::z() {
	static_assert(embedded>=3,"embedded lower than 3");
	return coordinates[2];
}
template <long embedded,typename real>
real Point<embedded,real>::z() const{
	static_assert(embedded>=3,"embedded lower than 3");
	return coordinates[2];
}

///////////////
// OPERATORS //
///////////////

// operator =
template <long embedded,typename real>
Point<embedded,real>& Point<embedded,real>::operator=(Point<embedded,real> inputPoint) {
	swap(coordinates,inputPoint.coordinates);
	return *this;
}

// operator ==
template <long embedded,typename real>
bool Point<embedded,real>::operator==(const Point<embedded,real>& inputPoint) const{
	real toll=1e-13;
	if (((*this)-inputPoint).norm()<toll) {
		return true;
	}
	
	return false;
}

// operator !=
template <long embedded,typename real>
bool Point<embedded,real>::operator!=(const Point<embedded,real>& inputPoint) const{
	real toll=1e-13;
	if (((*this)-inputPoint).norm()<toll) {
		return false;
	}
	
	return true;
}

// operator []
template <long embedded,typename real>
real& Point<embedded,real>::operator[](long index) {
	return coordinates[index%embedded];
}

// operator []
template <long embedded,typename real>
real Point<embedded,real>::operator[](long index) const {
	return coordinates[index%embedded];
}


//////////////////////
// EXTERNAL METHODS //
//////////////////////

// operator <<
template <long embedded,typename real>
ostream& operator <<(ostream& os,const Point<embedded,real>&point) {
	cout<<endl<<"(";
	for (int i=0; i<embedded-1; i++) {
		cout<<point.coordinates[i]<<",";
	}
	cout<<point.coordinates[embedded-1];
	cout<<")"<<endl;
	return os;
}

// operator +
template <long embedded,typename real>
Point<embedded,real> operator+(const Point<embedded,real>& point1,const Point<embedded,real>& point2) {
	Point<embedded,real> returnPoint(point1);
	for (int i=0; i<embedded; i++) {
		returnPoint.coordinates[i]+=point2.coordinates[i];
	}
	return returnPoint;
}

// operator -
template <long embedded,typename real>
Point<embedded,real> operator-(const Point<embedded,real>& point1,const Point<embedded,real>& point2) {
	Point<embedded,real> returnPoint(point1);
	for (int i=0; i<embedded; i++) {
		returnPoint.coordinates[i]-=point2.coordinates[i];
	}
	return returnPoint;
}

// operator -
template <long embedded,typename real>
Point<embedded,real> operator-(const Point<embedded,real>& point1) {
	Point<embedded,real> returnPoint;
	for (int i=0; i<embedded; i++) {
		returnPoint.coordinates[i]=-point1.coordinates[i];
	}
	return returnPoint;
}

// operator *
template <long embedded,typename real>
real operator*(const Point<embedded,real>& point1,const Point<embedded,real>& point2) {
	real result=0;
	for (int i=0; i<embedded; i++) {
		result+=point1.coordinates[i]*point2.coordinates[i];
	}
	return result;
}

// operator *
template <long embedded,typename real>
Point<embedded,real> operator*(long double coefficient,const Point<embedded,real>& point) {
	Point<embedded,real> newPoint(point);
	for (int i=0; i<embedded; i++) {
		newPoint.coordinates[i]*=coefficient;
	}
	return newPoint;
}

// operator *
template <long embedded,typename real>
Point<embedded,real> operator*(const Point<embedded,real>& point,long double coefficient) {
	return coefficient*point;
}

// operator /
template <long embedded,typename real>
Point<embedded,real> operator/(const Point<embedded,real>& point,long double coefficient) {
	Point<embedded,real> newPoint(point);
	for (int i=0; i<embedded; i++) {
		newPoint.coordinates[i]/=coefficient;
	}
	return newPoint;
}

// cross
template <long embedded,typename real>
Point<embedded,real> cross(const Point<embedded,real>& point1,const Point<embedded,real>& point2) {
	
	real component1=point1[1]*point2[2]-point1[2]*point2[1];
	real component2=point1[2]*point2[0]-point1[0]*point2[2];
	real component3=point1[0]*point2[1]-point1[1]*point2[0];
	Point<embedded,real> returnVector(component1,component2,component3);
	
	return returnVector;
}

//prodTermByTerm
template <long embedded,typename real>
Point<embedded,real> prodTermByTerm(const Point<embedded,real>& point1,const Point<embedded,real>& point2) {
	Point<embedded,real> returnVector;
	for (int i=0; i<embedded; i++) {
		returnVector[i]=point1[i]*point2[i];
	}
	
	return returnVector;
}


/////////////
// TYPEDEF //
/////////////

using Point2D=Point<2>;
using Point3D=Point<3>;

using PointLong2D=Point<2,long double>;
using PointLong3D=Point<3,long double>;



// A Point can be seen as a vector (for example this is useful for surfaces normals)
using Vector2D=Point<2>;
using Vector3D=Point<3>;
using Vector4D=Point<4>;

template <long embedded,typename real>
using Vector =Point<embedded,real>;
template <long embedded>
using VectorD=Point<embedded,double>;




#endif
















