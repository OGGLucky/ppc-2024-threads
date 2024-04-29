// Copyright 2024 Bakhtiarov Alexander

#include "omp/bakhtiarov_a_matrix_mult_ccs_omp/include/ccs_mat_multy.hpp"

#include <thread>

using namespace std::chrono_literals;
using namespace std;

bool SparseOmpMatrixMultiSequential::pre_processing() {
  internal_order_test();
  auto* matrix1 = reinterpret_cast<double*>(taskData->inputs[0]);
  auto* matrix2 = reinterpret_cast<double*>(taskData->inputs[1]);
  numRows1 = taskData->inputs_count[0];
  numCols1 = taskData->inputs_count[1];
  numRows2 = taskData->inputs_count[2];
  numCols2 = taskData->inputs_count[3];

  result = new double[numRows1 * numCols2]{0};

  int notNullNumbers = 0;
  for (int j = 0; j < numCols1; ++j) {
    colPtr1.push_back(notNullNumbers);
    for (int i = 0; i < numRows1; ++i) {
      int index = i * numRows1 + j;
      if (matrix1[index] != 0) {
        values1.push_back(matrix1[index]);
        rows1.push_back(i);
        notNullNumbers++;
      }
    }
  }
  colPtr1.push_back(notNullNumbers);

  notNullNumbers = 0;
  for (int j = 0; j < numCols2; ++j) {
    colPtr2.push_back(notNullNumbers);
    for (int i = 0; i < numRows2; ++i) {
      int index = i * numRows2 + j;
      if (matrix2[index] != 0) {
        values2.push_back(matrix2[index]);
        rows2.push_back(i);
        notNullNumbers++;
      }
    }
  }
  colPtr2.push_back(notNullNumbers);

  return true;
}

bool SparseOmpMatrixMultiSequential::validation() {
  internal_order_test();
  return taskData->inputs_count[1] == taskData->inputs_count[2] &&
         taskData->outputs_count[0] == taskData->inputs_count[0] &&
         taskData->outputs_count[1] == taskData->inputs_count[3];
}

bool SparseOmpMatrixMultiSequential::run() {
  internal_order_test();

  for (int j = 0; j < numCols1; j++) {
    for (int k = colPtr2[j]; k < colPtr2[j + 1]; k++) {
      int column2 = j;
      int row2 = rows2[k];
      for (int l = colPtr1[row2]; l < colPtr1[row2 + 1]; l++) {
        int row1 = rows1[l];
        double val1 = values1[l];
        double val2 = values2[k];
        int index = row1 * numCols2 + column2;
        result[index] += val1 * val2;
      }
    }
  }

  return true;
}

bool SparseOmpMatrixMultiSequential::post_processing() {
  internal_order_test();

  auto* out_ptr = reinterpret_cast<double*>(taskData->outputs[0]);
  for (int i = 0; i < numRows1 * numCols2; i++) {
    out_ptr[i] = result[i];
  }

  delete[] result;

  return true;
}

bool SparseOmpMatrixMultiParallel::pre_processing() {
  internal_order_test();
  auto* matrix1 = reinterpret_cast<double*>(taskData->inputs[0]);
  auto* matrix2 = reinterpret_cast<double*>(taskData->inputs[1]);
  numRows1 = taskData->inputs_count[0];
  numCols1 = taskData->inputs_count[1];
  numRows2 = taskData->inputs_count[2];
  numCols2 = taskData->inputs_count[3];

  result = new double[numRows1 * numCols2]{0};

  int notNullNumbers = 0;
  for (int j = 0; j < numCols1; ++j) {
    colPtr1.push_back(notNullNumbers);
    for (int i = 0; i < numRows1; ++i) {
      int index = i * numRows1 + j;
      if (matrix1[index] != 0) {
        values1.push_back(matrix1[index]);
        rows1.push_back(i);
        notNullNumbers++;
      }
    }
  }
  colPtr1.push_back(notNullNumbers);

  notNullNumbers = 0;
  for (int j = 0; j < numCols2; ++j) {
    colPtr2.push_back(notNullNumbers);
    for (int i = 0; i < numRows2; ++i) {
      int index = i * numRows2 + j;
      if (matrix2[index] != 0) {
        values2.push_back(matrix2[index]);
        rows2.push_back(i);
        notNullNumbers++;
      }
    }
  }
  colPtr2.push_back(notNullNumbers);

  return true;
}

bool SparseOmpMatrixMultiParallel::validation() {
  internal_order_test();
  return taskData->inputs_count[1] == taskData->inputs_count[2] &&
         taskData->outputs_count[0] == taskData->inputs_count[0] &&
         taskData->outputs_count[1] == taskData->inputs_count[3];
}

bool SparseOmpMatrixMultiParallel::run() {
  internal_order_test();

#pragma omp parallel for
  for (int j = 0; j < numCols1; j++) {
    for (int k = colPtr2[j]; k < colPtr2[j + 1]; k++) {
      int column2 = j;
      int row2 = rows2[k];
      for (int l = colPtr1[row2]; l < colPtr1[row2 + 1]; l++) {
        int row1 = rows1[l];
        double val1 = values1[l];
        double val2 = values2[k];
        int index = row1 * numCols2 + column2;
        result[index] += val1 * val2;
      }
    }
  }
  return true;
}

bool SparseOmpMatrixMultiParallel::post_processing() {
  internal_order_test();

  auto* out_ptr = reinterpret_cast<double*>(taskData->outputs[0]);
  for (int i = 0; i < numRows1 * numCols2; i++) {
    out_ptr[i] = result[i];
  }

  delete[] result;

  return true;
}
