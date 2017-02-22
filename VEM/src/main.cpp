#include <iostream>
#include <random>
#include "Point.h"
#include "MeshPoint.h"
#include "Polygon.h"
#include "Polyhedron.h"
#include "Mesh.h"
#include "Problem.h"
#include "Laplace.h"
#include "Monomials.h"
#include "MonomialsPolygon.h"
#include "Solver.h"
#include "BoundaryCondition.h"
#include "Error.h"
#include "Mesh3D.h"
#include "Mesh2D.h"
#include "SolverVEM.h"
#include "SolverVEM3D.h"
#include "SolverVEM2D.h"
#include "Eigen/Dense"
#include "SolverVEM.h"
#include "Dirichlet.h"
#include "muParserInterface.h"
#include "carthesianParserInterface.h"
#include "sphericalParserInterface.h"

 /*
// FUNCTIONS
template <long embedded,typename real=double>
real forceTermSphere(const Point<embedded,real>& inputPoint) {
	auto ro=inputPoint.norm();
		
	return 6;
	
}

template <long embedded,typename real=double>
real forceTermSquare(const Point<embedded,real>& inputPoint) {
	if (embedded==2) {
		auto x=inputPoint[0];
		auto y=inputPoint[1];
		
		
		return M_PI*M_PI/2*cos(M_PI*x/2)*cos(M_PI*y/2);
		
		//return -2*(y*y-1)-2*(x*x-1);
	}
	else {
		auto x=inputPoint[0];
		auto y=inputPoint[1];
		auto z=inputPoint[2];
		
		return -(exp(x*y)*(cos(z)*(pow(x,4)*(y*y-1)*(z*z-1)+4*pow(x,3)*y*(z*z-1)+x*x*(pow(y,4)*(z*z-1)+y*y*(5-3*z*z)+4*z*z-6)+4*x*y*(y*y-2)*(z*z-1)-pow(y,4)*(z*z-1)+y*y*(4*z*z-6)-5*z*z+7)-4*(x*x-1)*(y*y-1)*z*sin(z)));
		
		//return -2*(y*y-1)*(z*z-1)-2*(x*x-1)*(z*z-1)-2*(x*x-1)*(y*y-1);
	}
}

template <long embedded,typename real=double>
real forceTermConvergence(const Point<embedded,real>& inputPoint) {
 	if (embedded==2) {
 		auto x=inputPoint[0];
 		auto y=inputPoint[1];
 		
 		return 98*M_PI*M_PI*sin(7*M_PI*x)*sin(7*M_PI*y);
 	} else {
 		auto x=inputPoint[0];
 		auto y=inputPoint[1];
 		auto z=inputPoint[2];
 		
 		return 147*M_PI*M_PI*sin(7*M_PI*x)*sin(7*M_PI*y)*sin(7*M_PI*z);
	}
}

template <long embedded,typename real=double>
real solutionSphere(const Point<embedded,real>& inputPoint) {
	auto ro=inputPoint.norm();
		
	return 1-ro*ro;
	
}

template <long embedded,typename real=double>
real solutionSquare(const Point<embedded,real>& inputPoint) {
	if (embedded==2) {
		auto x=inputPoint[0];
		auto y=inputPoint[1];
		
		return cos(x*M_PI/2)*cos(y*M_PI/2);
		
		//return (x*x-1)*(y*y-1);
	}
	else {
		auto x=inputPoint[0];
		auto y=inputPoint[1];
		auto z=inputPoint[2];
	
		return (x*x-1)*(y*y-1)*(z*z-1)*exp(x*y)*cos(z);
		
		//return (x*x-1)*(y*y-1)*(z*z-1);
	}
}

template <long embedded,typename real=double>
real solutionConvergence(const Point<embedded,real>& inputPoint) {
	if (embedded==2) {
 		auto x=inputPoint[0];
 		auto y=inputPoint[1];
 		
 		return sin(7*M_PI*x)*sin(7*M_PI*y);
 	} else {
 		auto x=inputPoint[0];
 		auto y=inputPoint[1];
 		auto z=inputPoint[2];
 	
 		return sin(7*M_PI*x)*sin(7*M_PI*y)*sin(7*M_PI*z);
  	}
}
*/

////////////////////////////////////////////////////
///////                 MAIN                 ///////


int main(int argc, const char * argv[]) {
	
	////////////  PARAMETERS TO BE READ  /////////////
	
	long embedded=3;
	string inputPoint;
	string inputConnection;
	string meshType;
	string fileType;
	string solverType;
	string boundaryCondition;
	string outputPoint;
	string outputConnection;
	string outputSolution;
	string outputError;
	string errorAction;
	string coordinateType;
	string forceTermFunctionExpr;
	string boundaryFunctionExpr;
	string solutionFunctionExpr;
	string real;
	
	
	////////////  READ THE FILE  ///////////////////
	string parametroInput,valore,linea;
	ifstream inputFile("Datafile/datafile.dat");
	
	while (getline(inputFile, linea)) {
		// eliminate white spaces
		std::string::iterator end_pos = std::remove(linea.begin(), linea.end(), ' ');
		linea.erase(end_pos, linea.end());
		
		if (linea=="") {
			continue;
		} else if (linea.substr(0,2)=="//") {
			continue;
		}
		
		// obtain input parameters and their values
		stringstream iss(linea);
		getline(iss, parametroInput, '=');
		getline(iss, valore, ';');
		
		// overwrite found input parameters
		if (parametroInput=="inputPoint") {
			inputPoint=valore;
		} else if (parametroInput=="inputConnection") {
			inputConnection=valore;
		} else if (parametroInput=="meshType") {
			meshType=valore;
			if (meshType=="Mesh3D") {
				embedded=3;
			} else if (meshType=="Mesh2D"){
				embedded=2;
			}
		} else if (parametroInput=="fileType") {
			fileType=valore;
		} else if (parametroInput=="solverType") {
			solverType=valore;
		} else if (parametroInput=="boundaryCondition") {
			boundaryCondition=valore;
		} else if (parametroInput=="outputPoint") {
			outputPoint=valore;
		} else if (parametroInput=="outputConnection") {
			outputConnection=valore;
		} else if (parametroInput=="outputSolution") {
			outputSolution=valore;
		} else if (parametroInput=="outputError") {
			outputError=valore;
		} else if (parametroInput=="errorAction") {
			errorAction=valore;
		} else if (parametroInput=="coordinateType") {
			coordinateType=valore;
		} else if (parametroInput=="forceTermFunction") {
			forceTermFunctionExpr=valore;
		} else if (parametroInput=="boundaryFunction") {
			boundaryFunctionExpr=valore;
		} else if (parametroInput=="solutionFunction") {
			solutionFunctionExpr=valore;
		} else if (parametroInput=="real") {
			real=valore;
		}
	}

	//////////////  CREATE THE APPROPRIATES CLASSES  ///////////////////
	
	// Obtain the fileType
	MeshType fileTypeMesh=TETRAHEDRON;
	if (fileType=="TETRAHEDRON") {
		fileTypeMesh=TETRAHEDRON;
	} else if (fileType=="TRIANGLE") {
		fileTypeMesh=TRIANGLE;
	} else if (fileType=="ANYTHING3D") {
		fileTypeMesh=ANYTHING3D;
	} else if (fileType=="ANYTHING2D") {
		fileTypeMesh=ANYTHING2D;
	} else if (fileType=="FILETYPE1") {
		fileTypeMesh=FILETYPE1;
	} else if (fileType=="FILETYPE1") {
		fileTypeMesh=FILETYPE2;
	}
    
	try{
		// double case
		if (real=="double") {
			
			if (meshType=="Mesh3D") {
				muParserInterface<3,double>* forceTerm;
				muParserInterface<3,double>* boundaryFunc;
				muParserInterface<3,double>* solution;
				if (coordinateType=="carthesian") {
					forceTerm = new carthesianParserInterface<3,double>(forceTermFunctionExpr);
					boundaryFunc = new carthesianParserInterface<3,double>(boundaryFunctionExpr);
					if (solutionFunctionExpr == "boundaryFunction") {
						solution = new carthesianParserInterface<3,double>(boundaryFunctionExpr);
					} else if (solutionFunctionExpr != "null") {
						solution = new carthesianParserInterface<3,double>(solutionFunctionExpr);
					}
				} else if (coordinateType=="spherical") {
					forceTerm = new sphericalParserInterface<3,double>(forceTermFunctionExpr);
					boundaryFunc = new sphericalParserInterface<3,double>(boundaryFunctionExpr);
					if (solutionFunctionExpr == "boundaryFunction") {
						solution = new sphericalParserInterface<3,double>(boundaryFunctionExpr);
					} else if (solutionFunctionExpr != "null") {
						solution = new sphericalParserInterface<3,double>(solutionFunctionExpr);
					}
				}
			
				Mesh3D<> newMesh(inputPoint,inputConnection,fileTypeMesh);
				
				cout<<"Mesh created"<<endl;
				
				Laplace<3, Mesh3D<>, SolverVEM3D<>, Dirichlet3D<>> problem3(newMesh,*forceTerm,*boundaryFunc,1);
				problem3();
				if (solutionFunctionExpr != "null")
					problem3.displayError(*solution,outputError,errorAction);
				
				if (outputPoint!="") {
					problem3.write(outputPoint,outputConnection,outputSolution);
				}
				
				cout<<"hTriangle: "<<newMesh.hTriangle()<<endl<<endl;

				// Clear memory
				delete forceTerm;
				delete boundaryFunc;
				if (solutionFunctionExpr != "null")
					delete solution;
			}
			else if(meshType=="Mesh2D") {
				muParserInterface<2,double>* forceTerm;
				muParserInterface<2,double>* boundaryFunc;
				muParserInterface<2,double>* solution;
				if (coordinateType=="carthesian") {
					forceTerm = new carthesianParserInterface<2,double>(forceTermFunctionExpr);
					boundaryFunc = new carthesianParserInterface<2,double>(boundaryFunctionExpr);
					if (solutionFunctionExpr == "boundaryFunction") {
						solution = new carthesianParserInterface<2,double>(boundaryFunctionExpr);
					} else if (solutionFunctionExpr != "null") {
						solution = new carthesianParserInterface<2,double>(solutionFunctionExpr);
					}
				} else if (coordinateType=="spherical") {
					forceTerm = new sphericalParserInterface<2,double>(forceTermFunctionExpr);
					boundaryFunc = new sphericalParserInterface<2,double>(boundaryFunctionExpr);
					if (solutionFunctionExpr == "boundaryFunction") {
						solution = new sphericalParserInterface<2,double>(boundaryFunctionExpr);
					} else if (solutionFunctionExpr != "null") {
						solution = new sphericalParserInterface<2,double>(solutionFunctionExpr);
					}
				}
			
				Mesh2D<> newMesh(inputPoint,inputConnection,fileTypeMesh);
				
				Laplace<2, Mesh2D<>, SolverVEM2D<>, Dirichlet2D<>> problem3(newMesh,*forceTerm,*boundaryFunc,1);
				problem3();
				if (solutionFunctionExpr != "null")
					problem3.displayError(*solution,outputError,errorAction);
				
				if (outputPoint!="") {
					problem3.write(outputPoint,outputConnection,outputSolution);
				}
				
				cout<<"hTriangle: "<<newMesh.hTriangle()<<endl<<endl;

				// Clear memory
				delete forceTerm;
				delete boundaryFunc;
				if (solutionFunctionExpr != "null")
					delete solution;
			} else {
				cout<<"No predefined behaviour with this Mesh type"<<endl<<endl;
			}
			
		}
		// long double case
		else if (real=="longdouble") {
			
			if (meshType=="Mesh3D") {
				muParserInterface<3,long double>* forceTerm;
				muParserInterface<3,long double>* boundaryFunc;
				muParserInterface<3,long double>* solution;
				if (coordinateType=="carthesian") {
					forceTerm = new carthesianParserInterface<3,long double>(forceTermFunctionExpr);
					boundaryFunc = new carthesianParserInterface<3,long double>(boundaryFunctionExpr);
					if (solutionFunctionExpr == "boundaryFunction") {
						solution = new carthesianParserInterface<3,long double>(boundaryFunctionExpr);
					} else if (solutionFunctionExpr != "null") {
						solution = new carthesianParserInterface<3,long double>(solutionFunctionExpr);
					}
				} else if (coordinateType=="spherical") {
					forceTerm = new sphericalParserInterface<3,long double>(forceTermFunctionExpr);
					boundaryFunc = new sphericalParserInterface<3,long double>(boundaryFunctionExpr);
					if (solutionFunctionExpr == "boundaryFunction") {
						solution = new sphericalParserInterface<3,long double>(boundaryFunctionExpr);
					} else if (solutionFunctionExpr != "null") {
						solution = new sphericalParserInterface<3,long double>(solutionFunctionExpr);
					}
				}
				
				Mesh3D<long double> newMesh(inputPoint,inputConnection,fileTypeMesh);
				
				cout<<"Mesh created"<<endl;
				
				Laplace<3, Mesh3D<long double>, SolverVEM3D<long double>, Dirichlet3D<long double>,long double> problem3(newMesh,*forceTerm,*boundaryFunc,1);
				problem3();
				if (solutionFunctionExpr != "null")
					problem3.displayError(*solution,outputError,errorAction);
				
				if (outputPoint!="") {
					problem3.write(outputPoint,outputConnection,outputSolution);
				}
				
				cout<<"hTriangle: "<<newMesh.hTriangle()<<endl<<endl;

				// Clear memory
				delete forceTerm;
				delete boundaryFunc;
				if (solutionFunctionExpr != "null")
					delete solution;
			}
			else if(meshType=="Mesh2D") {
				muParserInterface<2,long double>* forceTerm;
				muParserInterface<2,long double>* boundaryFunc;
				muParserInterface<2,long double>* solution;
				if (coordinateType=="carthesian") {
					forceTerm = new carthesianParserInterface<2,long double>(forceTermFunctionExpr);
					boundaryFunc = new carthesianParserInterface<2,long double>(boundaryFunctionExpr);
					if (solutionFunctionExpr == "boundaryFunction") {
						solution = new carthesianParserInterface<2,long double>(boundaryFunctionExpr);
					} else if (solutionFunctionExpr != "null") {
						solution = new carthesianParserInterface<2,long double>(solutionFunctionExpr);
					}
				} else if (coordinateType=="spherical") {
					forceTerm = new sphericalParserInterface<2,long double>(forceTermFunctionExpr);
					boundaryFunc = new sphericalParserInterface<2,long double>(boundaryFunctionExpr);
					if (solutionFunctionExpr == "boundaryFunction") {
						solution = new sphericalParserInterface<2,long double>(boundaryFunctionExpr);
					} else if (solutionFunctionExpr != "null") {
						solution = new sphericalParserInterface<2,long double>(solutionFunctionExpr);
					}
				}				
				
				Mesh2D<long double> newMesh(inputPoint,inputConnection,fileTypeMesh);
				
				Laplace<2, Mesh2D<long double>, SolverVEM2D<long double>, Dirichlet2D<long double>,long double> problem3(newMesh,*forceTerm,*boundaryFunc,1);
				problem3();
				if (solutionFunctionExpr != "null")
					problem3.displayError(*solution,outputError,errorAction);
				
				if (outputPoint!="") {
					problem3.write(outputPoint,outputConnection,outputSolution);
				}
				
				cout<<"hTriangle: "<<newMesh.hTriangle()<<endl<<endl;

				// Clear memory
				delete forceTerm;
				delete boundaryFunc;
				if (solutionFunctionExpr != "null")
					delete solution;
		
			} else {
				cout<<"No predefined behaviour with this Mesh type"<<endl<<endl;
			}
			
		} else {
			cout<<"Program can run only with type=double or long double. You selected type="<<real<<endl<<endl;
		}
	}
	catch (mu::Parser::exception_type &e) {
		cerr<<"Error in evaluating an expression."<<std::endl;
		printMuException(e);
		cerr<<endl;
	}

	
	return 0;
}
