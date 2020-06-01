#include <Eigen/Dense>
#include <Eigen/LU>
#include <unsupported/Eigen/MatrixFunctions>
#include <iostream>
#include <cassert>
#include <cmath>

Eigen::MatrixXd ctrb(const Eigen::MatrixXd& A, const Eigen::MatrixXd& B){
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
  Eigen::FullPivLU<Eigen::MatrixXd> luA(A);
  return luA.rank() == A.rows();
}

int main(){
  Eigen::MatrixXd A(2, 2);
  Eigen::MatrixXd B(2, 1);
  A <<1.0f, 1.0f,
      0.0f, 2.0f;
  B <<0.0f, 1.0f;

  std::cout << "A = \n" << A << "\nB = \n" << B << "\n";
  std::cout << "controllability matrix = \n"
            << ctrb(A, B) << "\n"
            << "Is controllable = "
            << std::boolalpha << is_controllable(ctrb(A, B))
            << "\n";
  return 0;
}

//  LocalWords:  cassert cmath Eigen MatrixFunctions controllability
