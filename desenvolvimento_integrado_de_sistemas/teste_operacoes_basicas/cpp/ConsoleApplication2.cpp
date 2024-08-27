#include <eigen3/Eigen/Dense>
#include <fstream>
#include <iostream>
#include <vector>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds

#define EIGEN_USE_BLAS

using namespace Eigen;

std::vector<std::vector<double>> parse_file(std::string file_name) {
  std::ifstream file(file_name);
  std::vector<std::vector<double>> H;
  H.reserve(50816);
  for (int i = 0; i < 50816; i++) {
    H.push_back(std::move(std::vector<double>()));
  }
  int index = 0;

  if (file.is_open()) {
    std::string tp;
    int aux = 0;
    int counter = 0;
    while (getline(file, tp)) {
      for (int i = 0; i < tp.size(); i++) {
        if (tp[i] == ',') {
          std::string substr = tp.substr(aux, counter);
          double number;
          if (substr == "0") {
            number = 0;
          } else {
            number = std::stod(substr);
          }
          H[index].push_back(number);
          aux = i + 1;
          counter = 0;
          continue;
        }

        counter++;
      }
      std::string substr = tp.substr(aux, counter);
      double number;
      if (substr == "0") {
        number = 0;
      } else {
        number = std::stod(substr);
      }
      H[index].push_back(number);
      aux = 0;
      counter = 0;

      index++;
    }
  }

  H.resize(index--);
  file.close();
  return H;
}

std::vector<std::vector<double>> parse_signal(std::string file_name) {
  std::ifstream file(file_name);
  std::vector<std::vector<double>> H;
  H.reserve(50816);
  for (int i = 0; i < 50816; i++) {
    H.push_back(std::move(std::vector<double>()));
  }
  int index = 0;

  if (file.is_open()) {
    std::string tp;
    while (getline(file, tp)) {
      double number;
      if (tp == "0") {
        number = 0;
      } else {
        for (int i = 0; i < tp.size(); i++) {
          if (tp[i] == ',') {
            tp[i] = '.';
          }
        }
        number = std::stod(tp);
      }
      H[index].push_back(number);
      index++;
    }
  }

  H.resize(index--);
  file.close();
  return H;
}

MatrixXd create_matrix(std::vector<std::vector<double>> values) {
  int lines = values.size();
  int columns = values[0].size();
  MatrixXd m(lines, columns);

  for (int i = 0; i < values.size(); i++) {
    for (int j = 0; j < values[0].size(); j++) {
      m(i, j) = values[i][j];
    }
  }

  return m;
}

auto reduce(double a, VectorXd array) {
  for (int i = 0; i < array.size(); i++) {
    if (array(i) >= 0) {
      array(i) = array(i) - a >= 0 ? array(i) - a : 0;

    } else {
      array(i) = array(i) - a;
    }
  }

  return array;
}

VectorXd create_vector(std::vector<std::vector<double>> values) {
  int lines = values.size();
  int columns = values[0].size();
  VectorXd m(lines);

  for (int i = 0; i < values.size(); i++) {
    m(i) = values[i][0];
  }

  return m;
}

void zero_vector(VectorXd& v) {
  for (int i = 0; i < v.size(); i++) {
    v(i) = 0.0;
  }
}

int main() {
  // auto a = create_matrix(parse_file("./a.csv"));
  // auto M = create_matrix(parse_file("./M.csv"));
  // auto N = create_matrix(parse_file("./N.csv"));
  auto H = create_matrix(parse_file("./H-1.txt"));
  auto g = create_vector(parse_signal("./a-1.txt"));
  auto S = 60;
  auto N = 60;

  VectorXd f(60 * 60);
  VectorXd last_f(60 * 60);
  zero_vector(f);
  zero_vector(last_f);

  MatrixXd H_transpose = H.transpose();
  auto c = 9.66456e-07;//(H_transpose * H).norm();
  auto aux = H_transpose * g;



  auto lambda = ((H_transpose * g).cwiseAbs()).maxCoeff() * 0.1;//o certo é depois do ganho de sinal
  double yy = 100 + (1.0 / 20.0) * (double)1 * sqrt(float(1));
  int column = 0;
  for (int i = 0; i < g.size(); i++) {
    g(i) = g(i) * yy;
    if (i % (795) == 0) {
      column++;
      yy = 100 + (1.0 / 20.0) * (double)column * sqrt(float(column));
    }
  }

  VectorXd y(60 * 60);
  zero_vector(y);
  double a = 1;
  double last_a = 1;


  for (int i = 0; i < 4; i++) {
    f = reduce(lambda / c, (y + ((1.0 / c) * H_transpose) * (g - H * y)));
    a = (1.0 + sqrt(1.0 + 4.0 * (a * a))) / 2.0;
    y = f + ((last_a - 1.0)/a)*(f - last_f);

    last_a = a;
    last_f = f;
  }

  // usar raylib aqui para ajustar o valor de pixel_value/10000 e escolher o melhor.
  int counter = 0;
  std::ofstream result("out.pgm");
  result << "P2\n";
  result << "60 60\n";
  result << "255\n";

  f.normalize();


  for (int i = 0; i < 60; i++) {
    for (int j = 0; j < 60; j++) {
      double pixel_value = f(counter);

      result << (int)(pixel_value < 0? 0 : pixel_value*1000.0) << " ";
      counter++;
    }
    result << "\n";
  }

  result.close();
}
