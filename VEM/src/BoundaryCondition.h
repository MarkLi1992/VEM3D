#ifndef Mesh3_BoundaryCondition_h
#define Mesh3_BoundaryCondition_h

using namespace Eigen;

template <typename real>
using VectorX=Matrix<real, Dynamic, 1>;

/** Abstract class for BoundaryCondition
 *
 *  This class does 3 main things:
 *	- It processes the Kloc matrices after their creation from Solver (e.g in Dirichlet condition the upper part of the stiffness matrix is diagonal and there is no need to add the corresponding terms)
 *	- Once the K matrix is assembled, it processes the full matrix to assign boundary condition (e.g in the same example it makes the upper part diagonal)
 *	- It imposes boundary condition also on the known term
 *
 *	\param embedded Dimension of the space
 *	\param MeshType Kind of Mesh we have
 *	\param MeshElement Polygon or Polyhedron
 *	\param real double or long double
 */
template <long embedded,typename MeshType,typename MeshElement,typename real=double>
class BoundaryCondition {
	protected:
		const MeshType& mesh;
		muParserInterface<embedded,real>& boundaryFunction;
		
		/** Standard constructor
		 */
		BoundaryCondition(const MeshType& inputMesh,muParserInterface<embedded,real>& inputBoundaryFunction):mesh(inputMesh),boundaryFunction(inputBoundaryFunction) {};
	
	public:
		/** Decide whether the computed Kloc will be added to the global matrix. It depends on the boundary condition.
		 *
		 *	For example, for Dirichlet boundary condition, the upper part of the matrix should be diagonal.
		 */
		virtual void addToTripletList(Matrix<real,Dynamic,Dynamic>& Kloc,MeshElement& element,vector<Triplet<real>>& tripletList)=0;
		
		/** Changes the stiffnessMatrix to take into account the boundary condition.
		 */
		virtual void assignBoundaryConditionOnStiffnessMatrix(vector<Triplet<real>>& tripletList)=0;
		
		/** Changes the known term to take into account the boundary condition.
		 */
		virtual void assignBoundaryConditionOnKnownTerm(VectorX<real>& knownTerm)=0; 	
	
};

#endif /* Mesh3_BoundaryCondition_h */
