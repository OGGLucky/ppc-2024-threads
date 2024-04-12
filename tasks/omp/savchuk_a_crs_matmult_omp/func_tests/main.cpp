// Copyright 2024 Savchuk Anton
#include <gtest/gtest.h>

#include <vector>

#include "omp/savchuk_a_crs_matmult_omp/include/crs_matmult_omp.hpp"

TEST(savchuk_a_crs_matmult_omp, test_sizes) {
  size_t n1 = 4;
  size_t m1 = 6;
  size_t n2 = 6;
  size_t m2 = 2;

  // Create data
  std::vector<double> in1(n1 * m1);

  std::vector<double> in2(n2 * m2);

  std::vector<double> out(n1 * m2);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in1.data()));
  taskDataSeq->inputs_count.emplace_back(n1);
  taskDataSeq->inputs_count.emplace_back(m1);
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in2.data()));
  taskDataSeq->inputs_count.emplace_back(n2);
  taskDataSeq->inputs_count.emplace_back(m2);
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(n1);
  taskDataSeq->outputs_count.emplace_back(m2);

  // Create Task
  SavchukCRSMatMultOMPSequential savchukCRSMatMultOMPSequential(taskDataSeq);
  ASSERT_EQ(savchukCRSMatMultOMPSequential.validation(), true);

  // Create data
  std::vector<double> in3(n1 * m1);

  std::vector<double> in4(n2 * m2);

  std::vector<double> out2(n1 * m2);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataParallel = std::make_shared<ppc::core::TaskData>();
  taskDataParallel->inputs.emplace_back(reinterpret_cast<uint8_t *>(in3.data()));
  taskDataParallel->inputs_count.emplace_back(n1);
  taskDataParallel->inputs_count.emplace_back(m1);
  taskDataParallel->inputs.emplace_back(reinterpret_cast<uint8_t *>(in4.data()));
  taskDataParallel->inputs_count.emplace_back(n2);
  taskDataParallel->inputs_count.emplace_back(m2);
  taskDataParallel->outputs.emplace_back(reinterpret_cast<uint8_t *>(out2.data()));
  taskDataParallel->outputs_count.emplace_back(n1);
  taskDataParallel->outputs_count.emplace_back(m2);
  // Create Task
  SavchukCRSMatMultOMPParallel savchukCRSMatMultOMPParallel(taskDataParallel);
  ASSERT_EQ(savchukCRSMatMultOMPParallel.validation(), true);
}

TEST(savchuk_a_crs_matmult_omp, test_sizes2) {
  size_t n1 = 2;
  size_t m1 = 3;
  size_t n2 = 4;
  size_t m2 = 5;

  // Create data
  std::vector<double> in1(n1 * m1);

  std::vector<double> in2(n2 * m2);

  std::vector<double> out(n1 * m2);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in1.data()));
  taskDataSeq->inputs_count.emplace_back(n1);
  taskDataSeq->inputs_count.emplace_back(m1);
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in2.data()));
  taskDataSeq->inputs_count.emplace_back(n2);
  taskDataSeq->inputs_count.emplace_back(m2);
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(n1);
  taskDataSeq->outputs_count.emplace_back(m2);

  // Create Task
  SavchukCRSMatMultOMPSequential savchukCRSMatMultOMPSequential(taskDataSeq);
  ASSERT_FALSE(savchukCRSMatMultOMPSequential.validation());

  // Create data
  std::vector<double> in3(n1 * m1);

  std::vector<double> in4(n2 * m2);

  std::vector<double> out2(n1 * m2);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataParallel = std::make_shared<ppc::core::TaskData>();
  taskDataParallel->inputs.emplace_back(reinterpret_cast<uint8_t *>(in3.data()));
  taskDataParallel->inputs_count.emplace_back(n1);
  taskDataParallel->inputs_count.emplace_back(m1);
  taskDataParallel->inputs.emplace_back(reinterpret_cast<uint8_t *>(in4.data()));
  taskDataParallel->inputs_count.emplace_back(n2);
  taskDataParallel->inputs_count.emplace_back(m2);
  taskDataParallel->outputs.emplace_back(reinterpret_cast<uint8_t *>(out2.data()));
  taskDataParallel->outputs_count.emplace_back(n1);
  taskDataParallel->outputs_count.emplace_back(m2);
  // Create Task
  SavchukCRSMatMultOMPParallel savchukCRSMatMultOMPParallel(taskDataParallel);
  ASSERT_FALSE(savchukCRSMatMultOMPParallel.validation());
}

TEST(savchuk_a_crs_matmult_omp, test_multy_correct) {
  size_t n1 = 3;
  size_t m1 = 3;
  size_t n2 = 3;
  size_t m2 = 3;
  // Create data
  std::vector<double> in1{4, 0, 0, 0, 0, 1, 0, 2, 0};
  std::vector<double> in2{9, 1, 0, 0, 0, 7, 3, 0, 0};
  std::vector<double> out(n1 * m2);
  std::vector<double> test{36, 4, 0, 3, 0, 0, 0, 0, 14};

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in1.data()));
  taskDataSeq->inputs_count.emplace_back(n1);
  taskDataSeq->inputs_count.emplace_back(m1);
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in2.data()));
  taskDataSeq->inputs_count.emplace_back(n2);
  taskDataSeq->inputs_count.emplace_back(m2);
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(n1);
  taskDataSeq->outputs_count.emplace_back(m2);

  // Create Task
  SavchukCRSMatMultOMPSequential savchukCRSMatMultOMPSequential(taskDataSeq);
  savchukCRSMatMultOMPSequential.validation();
  savchukCRSMatMultOMPSequential.pre_processing();
  savchukCRSMatMultOMPSequential.run();
  savchukCRSMatMultOMPSequential.post_processing();

  size_t k = 0;

  for (size_t i = 0; i < out.size(); ++i) {
    if (out[i] == test[i]) {
      k++;
    }
  }

  ASSERT_EQ(k, n1 * m2);
  // Create data
  std::vector<double> in3{4, 0, 0, 0, 0, 1, 0, 2, 0};
  std::vector<double> in4{9, 1, 0, 0, 0, 7, 3, 0, 0};
  std::vector<double> out2(n1 * m2);
  std::vector<double> test2{36, 4, 0, 3, 0, 0, 0, 0, 14};

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataParallel = std::make_shared<ppc::core::TaskData>();
  taskDataParallel->inputs.emplace_back(reinterpret_cast<uint8_t *>(in3.data()));
  taskDataParallel->inputs_count.emplace_back(n1);
  taskDataParallel->inputs_count.emplace_back(m1);
  taskDataParallel->inputs.emplace_back(reinterpret_cast<uint8_t *>(in4.data()));
  taskDataParallel->inputs_count.emplace_back(n2);
  taskDataParallel->inputs_count.emplace_back(m2);
  taskDataParallel->outputs.emplace_back(reinterpret_cast<uint8_t *>(out2.data()));
  taskDataParallel->outputs_count.emplace_back(n1);
  taskDataParallel->outputs_count.emplace_back(m2);

  // Create Task
  SavchukCRSMatMultOMPParallel savchukCRSMatMultOMPParallel(taskDataSeq);
  savchukCRSMatMultOMPParallel.validation();
  savchukCRSMatMultOMPParallel.pre_processing();
  savchukCRSMatMultOMPParallel.run();
  savchukCRSMatMultOMPParallel.post_processing();

  size_t ch = 0;

  for (size_t i = 0; i < out.size(); ++i) {
    if (out[i] == test[i]) {
      ch++;
    }
  }

  ASSERT_EQ(ch, n1 * m2);
}

TEST(savchuk_a_crs_matmult_omp, inverse_matrix) {
  size_t n1 = 3;
  size_t m1 = 3;
  size_t n2 = 3;
  size_t m2 = 3;

  // Create data
  std::vector<double> in1{4, 0, 0, 0, 2, 1, 0, 2, 0};
  std::vector<double> in2{0.25, 0, 0, 0, 0, 0.5, 0, 1, -1};
  std::vector<double> out(n1 * m2);
  std::vector<double> identity{1, 0, 0, 0, 1, 0, 0, 0, 1};

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in1.data()));
  taskDataSeq->inputs_count.emplace_back(n1);
  taskDataSeq->inputs_count.emplace_back(m1);
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in2.data()));
  taskDataSeq->inputs_count.emplace_back(n2);
  taskDataSeq->inputs_count.emplace_back(m2);
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(n1);
  taskDataSeq->outputs_count.emplace_back(m2);

  // Create Task
  SavchukCRSMatMultOMPSequential savchukCRSMatMultOMPSequential(taskDataSeq);
  savchukCRSMatMultOMPSequential.validation();
  savchukCRSMatMultOMPSequential.pre_processing();
  savchukCRSMatMultOMPSequential.run();
  savchukCRSMatMultOMPSequential.post_processing();

  size_t k = 0;

  for (size_t i = 0; i < out.size(); ++i) {
    if (out[i] == identity[i]) {
      k++;
    }
  }

  ASSERT_EQ(k, n1 * m2);
  // Create data
  std::vector<double> in3{4, 0, 0, 0, 2, 1, 0, 2, 0};
  std::vector<double> in4{0.25, 0, 0, 0, 0, 0.5, 0, 1, -1};
  std::vector<double> out2(n1 * m2);
  std::vector<double> identity2{1, 0, 0, 0, 1, 0, 0, 0, 1};

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataParallel = std::make_shared<ppc::core::TaskData>();
  taskDataParallel->inputs.emplace_back(reinterpret_cast<uint8_t *>(in3.data()));
  taskDataParallel->inputs_count.emplace_back(n1);
  taskDataParallel->inputs_count.emplace_back(m1);
  taskDataParallel->inputs.emplace_back(reinterpret_cast<uint8_t *>(in4.data()));
  taskDataParallel->inputs_count.emplace_back(n2);
  taskDataParallel->inputs_count.emplace_back(m2);
  taskDataParallel->outputs.emplace_back(reinterpret_cast<uint8_t *>(out2.data()));
  taskDataParallel->outputs_count.emplace_back(n1);
  taskDataParallel->outputs_count.emplace_back(m2);

  // Create Task
  SavchukCRSMatMultOMPParallel savchukCRSMatMultOMPParallel(taskDataSeq);
  savchukCRSMatMultOMPParallel.validation();
  savchukCRSMatMultOMPParallel.pre_processing();
  savchukCRSMatMultOMPParallel.run();
  savchukCRSMatMultOMPParallel.post_processing();

  size_t ch = 0;

  for (size_t i = 0; i < out.size(); ++i) {
    if (out[i] == identity2[i]) {
      ch++;
    }
  }

  ASSERT_EQ(ch, n1 * m2);
}

TEST(savchuk_a_crs_matmult_omp, zero_matrix) {
  size_t n1 = 3;
  size_t m1 = 3;
  size_t n2 = 3;
  size_t m2 = 3;
  // Create data
  std::vector<double> in1{0, 2, 0, 0, 0, 6, 0, 2, 0};

  std::vector<double> in2(n2 * m2, 0);

  std::vector<double> out(n1 * m2);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in1.data()));
  taskDataSeq->inputs_count.emplace_back(n1);
  taskDataSeq->inputs_count.emplace_back(m1);
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(in2.data()));
  taskDataSeq->inputs_count.emplace_back(n2);
  taskDataSeq->inputs_count.emplace_back(m2);
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(out.data()));
  taskDataSeq->outputs_count.emplace_back(n1);
  taskDataSeq->outputs_count.emplace_back(m2);

  // Create Task
  SavchukCRSMatMultOMPSequential savchukCRSMatMultOMPSequential(taskDataSeq);
  savchukCRSMatMultOMPSequential.validation();
  savchukCRSMatMultOMPSequential.pre_processing();
  savchukCRSMatMultOMPSequential.run();
  savchukCRSMatMultOMPSequential.post_processing();

  size_t k = 0;

  for (size_t i = 0; i < out.size(); ++i) {
    if (out[i] == 0.0) {
      k++;
    }
  }

  ASSERT_EQ(k, n1 * m2);
  // Create data
  std::vector<double> in3{0, 2, 0, 0, 0, 6, 0, 2, 0};
  ;
  std::vector<double> in4(n2 * m2, 0);
  std::vector<double> out2(n1 * m2);

  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataParallel = std::make_shared<ppc::core::TaskData>();
  taskDataParallel->inputs.emplace_back(reinterpret_cast<uint8_t *>(in3.data()));
  taskDataParallel->inputs_count.emplace_back(n1);
  taskDataParallel->inputs_count.emplace_back(m1);
  taskDataParallel->inputs.emplace_back(reinterpret_cast<uint8_t *>(in4.data()));
  taskDataParallel->inputs_count.emplace_back(n2);
  taskDataParallel->inputs_count.emplace_back(m2);
  taskDataParallel->outputs.emplace_back(reinterpret_cast<uint8_t *>(out2.data()));
  taskDataParallel->outputs_count.emplace_back(n1);
  taskDataParallel->outputs_count.emplace_back(m2);

  // Create Task
  SavchukCRSMatMultOMPParallel savchukCRSMatMultOMPParallel(taskDataSeq);
  savchukCRSMatMultOMPParallel.validation();
  savchukCRSMatMultOMPParallel.pre_processing();
  savchukCRSMatMultOMPParallel.run();
  savchukCRSMatMultOMPParallel.post_processing();

  size_t ch = 0;

  for (size_t i = 0; i < out.size(); ++i) {
    if (out[i] == 0.0) {
      ch++;
    }
  }

  ASSERT_EQ(ch, n1 * m2);
}