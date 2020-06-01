#include <Eigen/Dense>
#include <Eigen/LU>
#include <unsupported/Eigen/MatrixFunctions>
#include <Eigen/Eigenvalues>
#include <iostream>
#include <cassert>
#include <cmath>

Eigen::MatrixXd ctrb(const Eigen::MatrixXd& A, const Eigen::MatrixXd& B){
  /*
    ctrb(A,B) = [B AB (A^2)B (A^3)B .... (A^n-1)B]
   */
  assert(A.cols() == A.rows());
  assert(B.rows() == A.rows());
  Eigen::MatrixXd temp;
  Eigen::MatrixPower<Eigen::MatrixXd> Apow(A);
  Eigen::MatrixXd mat = B;
  for(auto n = 1; n < A.cols(); n++){
    temp = mat;
    mat.resize(B.rows(), mat.cols()+B.cols());
    mat << temp, (Apow(n) * B);
  }
  return mat;
}

bool is_controllable(const Eigen::MatrixXd& A){
  // checks if the matrix is controllable or not
  Eigen::FullPivLU<Eigen::MatrixXd> luA(A);
  return luA.rank() == A.rows();
}

Eigen::MatrixXcd eigenvalue(const Eigen::MatrixXd& A){
  // returns the eigenvalue of input
  Eigen::EigenSolver<Eigen::MatrixXd> es(A);
  Eigen::MatrixXcd D = es.eigenvalues();
  return D;
}

Eigen::MatrixXcd eigenvector(const Eigen::MatrixXd& A){
  // Returns the eigenvector of input
  Eigen::EigenSolver<Eigen::MatrixXd> es(A);
  Eigen::MatrixXcd D = es.eigenvectors();
  return D;
}

int main(){
  Eigen::MatrixXd A(2, 2);
  Eigen::MatrixXd B(2, 1);
  A <<1.0f, 1.0f,
      0.0f, 2.0f;
  B <<0.0f, 1.0f;
  Eigen::MatrixXd controllable;
  controllable = ctrb(A, B);
  std::cout << "A = \n" << A << "\nB = \n" << B << "\n";
  std::cout << "controllability matrix = \n"
            << controllable << "\n"
            << "Is controllable = "
            << std::boolalpha << is_controllable(controllable)
            << "\n";

  std::cout <<"----------------\n";
  std::cout <<"Eigenvalue = \n"
            << eigenvalue(controllable) << "\n"
            << "Eigenvector = \n"
            << eigenvector(controllable) << "\n";
  return 0;
}

//  LocalWords:  cassert cmath Eigen MatrixFunctions controllability
