#ifndef Mesh2_Mesh_h
#define Mesh2_Mesh_h

#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

template <long embedded,typename real>
class MeshPoint;

template <typename Class>
static bool lessSharedPointer(const shared_ptr<Class>& ptr1,const shared_ptr<Class>& ptr2) {
	return *ptr1<*ptr2;
}

enum OpenEnum{CLOSED,OPEN};
enum MeshType{TETRAHEDRON,TRIANGLE,ANYTHING3D,ANYTHING2D,FILETYPE1,FILETYPE2};
// FILETYPE1 and FILETYPE2 used only in case one want to extend class Mesh. 
// They can inherit from Mesh or Mesh3D and specialize the corresponding virtual methods.
// To add other MeshType, it is necessary to change the method setElementVector.


/** Abstract class to create a Mesh
 *	
 *	To inherit from it: create a contructor, implement one of the methods to set the elementVector (setTetrahedronMesh and following) and call the method initialize in the constructor.
 *
 *	\param embedded It can be 2 or 3 for 2D or 3D
 *	\param baseElement It is typically Polygon or Polyhedron
 *  \param isOpen It is typically OPEN. It can be closed for a surface embedded in a 3D space
 *	\param real double or long double
 */
template <long embedded,typename baseElement,OpenEnum isOpen=OPEN,typename real=double>
class Mesh {
	protected:
		vector<shared_ptr<baseElement>> elementVector;	//!< Vector of Polygon or Polyhedron
		vector<shared_ptr<MeshPoint<embedded,real>>> pointVector;	//!< Vector of the vertices of each element
		
	public:
		long numberOfElements;
		long numberOfPoints;
		
		const shared_ptr<baseElement>& element(long index) const;	//!< \return pointer on the element with particular index
		const shared_ptr<MeshPoint<embedded,real>>& point(long index) const;	//!< \return pointer on the MeshPoint with a particular index
		const vector<shared_ptr<MeshPoint<embedded,real>>>& getPointVector() const {return pointVector;};

		virtual real hTriangle();	//!< paramether h of the Mesh
		
		/** Method that calls the functions that read the input files
		 *
		 *	\param pointFile File with the position of the Points (vertices)
		 *	\param connection File with the connections between mesh points
		 *	\param meshType Format of the mesh file
		 */
		void initialize(string pointFile,string connection,MeshType meshType=ANYTHING3D);
		
		// These 4 functions are called one after the other by the constructor, they can be specialized if necessary
		virtual void setPointVector(string file);	//!< It obtains the pointVector from a file
		/** It obtains the elementVector from the connections
		 *
		 *	Then it calls the appropriate method to read the connection file
		 */
		virtual void setElementVector(string connections, MeshType meshType);
		/** Virtual method to keep into account the boundary elements
		 *
		 */
		virtual void setBoundaryElements()=0;
		/**	Virtual method used to set other things, like pointIDs
		 *
		 */
		virtual void setRemainingThings()=0;
		
		// methods to set the elementVector, they have to be implemented in the child class (only the necessary ones)
		virtual void setTetrahedronMesh(string connection) {}; 	//!< Read tetrahedron file type
		virtual void setTriangleMesh(string connection) {};		//!< Read Triangle file type
		virtual void setAnything3DMesh(string connection) {};	//!< Read general polyhedron file type
		virtual void setAnything2DMesh(string connection) {};	//!< Read general polygon file type
		virtual void setFileType1Mesh(string connection) {};	//!< Need to be specialized
		virtual void setFileType2Mesh(string connection) {};	//!< Need to be specialized

		virtual void sort(); //!< Sort the pointVector based on pointID
		
		void shrink_to_fit();
		virtual void write(string outputPoints="points.point",string outputConnections="connections.conn") const;	//!< Full output to file
		virtual void writePoints(string outputFile="points.point") const;	//!< Output the points to file
		virtual void writeConnections(string outputFile="connections.conn") const;	//!< Output the connections to file
		
	protected:
		Mesh():elementVector({}),pointVector({}){};	//!< Empty constructor
		
		template <long embedded2,typename baseElement2,OpenEnum isOpen2,typename real2>
		friend ostream& operator<<(ostream& os,const Mesh<embedded2,baseElement2,isOpen2,real2>& mesh); //!< Output operator
};

// STANDARD METHODS

// hTriangle
template <long embedded,typename baseElement,OpenEnum isOpen,typename real>
real Mesh<embedded,baseElement,isOpen,real>::hTriangle() {
	real maxH=elementVector[0]->hTriangle();
	for (long i=1; i<numberOfElements; i++) {
		real tempMax=elementVector[i]->hTriangle();
		if (tempMax>maxH) {
			maxH=tempMax;
		}
	}
	return maxH;
}

// initialize
template <long embedded,typename baseElement,OpenEnum isOpen,typename real>
void Mesh<embedded,baseElement,isOpen,real>::initialize(string pointFile,string connection,MeshType meshType) {
	clock_t startTime;
	double duration;
	startTime=clock();
	
	// initialize pointVector
	setPointVector(pointFile);
	
	duration = ( clock() - startTime ) / (double) CLOCKS_PER_SEC;
	cout << "PointVector time: " << duration << endl << endl;
	
	startTime=clock();
	
	// initialize elementVector
	setElementVector(connection, meshType);
	
	duration = ( clock() - startTime ) / (double) CLOCKS_PER_SEC;
	cout << "ElementVector time: " << duration << endl << endl;
	
	// initialize all the rest
	setBoundaryElements();
	setRemainingThings();

	sort();
}

// setPointVector
template <long embedded,typename baseElement,OpenEnum isOpen,typename real>
void Mesh<embedded,baseElement,isOpen,real>::setPointVector(string file) {
	ifstream file1;
	file1.open(file);
	if (!file1.is_open()) {
		throw std::runtime_error("Problem reading inputPoint file.");
	}
	
	string rigaFile1;
	
	while (getline(file1, rigaFile1)) {
		istringstream rigaFileStream(rigaFile1);
		auto point=make_shared<MeshPoint<embedded,real>>();
		
		for (long i=0; i<embedded; i++) {
			string stringaDiSupporto;
			getline(rigaFileStream, stringaDiSupporto, ',');
			istringstream stream2(stringaDiSupporto);
			
			stream2 >> (*point)[i];
		}
		
		this->pointVector.push_back(point);
	}
}

// setElementVector
template <long embedded,typename baseElement,OpenEnum isOpen,typename real>
void Mesh<embedded,baseElement,isOpen,real>::setElementVector(string connections, MeshType meshType) {
	switch (meshType) {
		case TETRAHEDRON:
			setTetrahedronMesh(connections);
			break;
		case TRIANGLE:
			setTriangleMesh(connections);
			break;
		case ANYTHING3D:
			setAnything3DMesh(connections);
			break;
		case ANYTHING2D:
			setAnything2DMesh(connections);
			break;
		case FILETYPE1:
			setFileType1Mesh(connections);
			break;
		case FILETYPE2:
			setFileType2Mesh(connections);
			break;
			
		default:
			break;
	}
}

// element
template <long embedded,typename baseElement,OpenEnum isOpen,typename real>
const shared_ptr<baseElement>& Mesh<embedded,baseElement,isOpen,real>::element(long int index) const{
	if (index>elementVector.size()) {
		cerr << endl << endl << "poligonVector size less than index given" << endl << endl;
	}
	
	return elementVector[index%numberOfElements];
}

// point
template <long embedded,typename baseElement,OpenEnum isOpen,typename real>
const shared_ptr<MeshPoint<embedded,real>>& Mesh<embedded,baseElement,isOpen,real>::point(long index) const{
	if (index>pointVector.size()) {
		cerr << endl << endl << "pointVector size less than index given" << endl << endl;
	}
	
	return pointVector[index%numberOfPoints];
}

// sort
template <long embedded,typename baseElement,OpenEnum isOpen,typename real>
void Mesh<embedded,baseElement,isOpen,real>::sort() {
	std::sort(pointVector.begin(),pointVector.end(),lessSharedPointer<MeshPoint<embedded,real>>);
}

// shrink_to_fit
template <long embedded,typename baseElement,OpenEnum isOpen,typename real>
void Mesh<embedded,baseElement,isOpen,real>::shrink_to_fit() {
	elementVector.shrink_to_fit();
	pointVector.shrink_to_fit();
}

// write
template <long embedded,typename baseElement,OpenEnum isOpen,typename real>
void Mesh<embedded,baseElement,isOpen,real>::write(string outputPoints,string outputConnections) const{
	writePoints(outputPoints);
	writeConnections(outputConnections);
}

// writePoints
template <long embedded,typename baseElement,OpenEnum isOpen,typename real>
void Mesh<embedded,baseElement,isOpen,real>::writePoints(string outputFile) const{
	ofstream file;
	file.open(outputFile);
	for (int i=0; i<pointVector.size(); i++) {
		file << pointVector[i]->write();
		file << "\n";
	}
	file.close();
}

// writeConnections
template <long embedded,typename baseElement,OpenEnum isOpen,typename real>
void Mesh<embedded,baseElement,isOpen,real>::writeConnections(string outputFile) const{
	ofstream file;
	file.open(outputFile);
	for (int i=0; i<elementVector.size(); i++) {
		file << elementVector[i]->write();
		file << "\n";
	}
	file.close();
}

// operator <<
template <long embedded,typename baseElement,OpenEnum isOpen,typename real>
ostream& operator<<(ostream& os,const Mesh<embedded,baseElement,isOpen,real>& mesh) {
	cout << endl << endl;
	cout << "POINT VECTOR" << endl << endl;
	
	for (int i=0; i<mesh.pointVector.size(); i++) {
		cout << *mesh.pointVector[i];
	}
	cout << endl << endl << endl;
	
	cout << "ELEMENT VECTOR" << endl << endl;
	
	for (int i=0; i<mesh.elementVector.size(); i++) {
		cout << *(mesh.elementVector[i]);
	}
	
	cout << endl << "There are " << mesh.pointVector.size() << " points";
	cout << endl << "There are " << mesh.elementVector.size() << " elements" << endl << endl;
	
	return os;
}

#endif /* Mesh2_Mesh_h */
