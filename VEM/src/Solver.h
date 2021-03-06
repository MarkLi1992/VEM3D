#ifndef Mesh3_Solver_h
#define Mesh3_Solver_h

#include <Eigen/Dense>
#include <Eigen/IterativeLinearSolvers>

using namespace Eigen;


/** Generic Solver
 *
 *	It is compatible with any numerical scheme that consists in computing the local stiffness matrix.
 *
 *	\param embedded Dimension of the space
 *	\param baseElement Polygon or Polyhedron
 *	\param MatrixType Kind of Matrix to use.
 *	\param real double or long double
 */
template <long embedded,typename baseElement,typename MatrixType,typename real>
class Solver {
	protected:
		muParserInterface<embedded,real>& forceTerm; //!< ForceTerm function to use, in the form of a muParserInterface expression
		
	public:
		/** Very generic constructor
		 */
		Solver(muParserInterface<embedded,real>& inputForceTerm):forceTerm(inputForceTerm) {};
		
		/** Main virtual method. To be implemented in subclasses
		 */
		virtual MatrixType computeLocalK(const shared_ptr<baseElement>& element)=0;
};

#endif /* Mesh3_Solver_h */
