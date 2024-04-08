// Copyright 2024 Kiselev Igor
#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

#include "seq/kiselev_i_shell_simple/include/shell_simple.hpp"

TEST(kiselev_i_shell_simple_seq, check_5_size) {
  const int count = 5;

  // Create data
  std::vector<int> in = {2, 6, 4, 1, 0};
  std::vector<int> out(count, 0);
  std::vector<int> res = {0, 1, 2, 4, 6};
  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(&in));
  taskDataSeq->inputs_count.emplace_back(in.size());
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(&out));
  taskDataSeq->outputs_count.emplace_back(out.size());

  // Create Task
  TestTaskSequential testTaskSequential(taskDataSeq);
  ASSERT_EQ(testTaskSequential.validation(), true);
  ASSERT_EQ(testTaskSequential.pre_processing(), true);
  ASSERT_EQ(testTaskSequential.run(), true);
  ASSERT_EQ(testTaskSequential.post_processing(), true);
  ASSERT_EQ(res, out);
}

TEST(kiselev_i_shell_simple_seq, check_100_size_reverse) {
  const int count = 100;

  // Create data
  std::vector<int> in(count, 0);
  std::vector<int> out(count, 0);
  std::vector<int> res(count, 0);
  for (int i = 0; i < count; i++) {
    in[i] = count - 1 - i;
    res[i] = i;
  }
  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(&in));
  taskDataSeq->inputs_count.emplace_back(in.size());
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(&out));
  taskDataSeq->outputs_count.emplace_back(out.size());

  // Create Task
  TestTaskSequential testTaskSequential(taskDataSeq);
  ASSERT_EQ(testTaskSequential.validation(), true);
  ASSERT_EQ(testTaskSequential.pre_processing(), true);
  ASSERT_EQ(testTaskSequential.run(), true);
  ASSERT_EQ(testTaskSequential.post_processing(), true);
  ASSERT_EQ(res, out);
}

TEST(kiselev_i_shell_simple_seq, check_100_size_sorted) {
  const int count = 100;

  // Create data
  std::vector<int> in(count, 0);
  std::vector<int> out(count, 0);
  std::vector<int> res(count, 0);
  for (int i = 0; i < count; i++) {
    in[i] = i;
    res[i] = i;
  }
  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(&in));
  taskDataSeq->inputs_count.emplace_back(in.size());
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(&out));
  taskDataSeq->outputs_count.emplace_back(out.size());

  // Create Task
  TestTaskSequential testTaskSequential(taskDataSeq);
  ASSERT_EQ(testTaskSequential.validation(), true);
  ASSERT_EQ(testTaskSequential.pre_processing(), true);
  ASSERT_EQ(testTaskSequential.run(), true);
  ASSERT_EQ(testTaskSequential.post_processing(), true);
  ASSERT_EQ(res, out);
}

TEST(kiselev_i_shell_simple_seq, check_100_size_bias) {
  const int count = 100;
  const int bias = 50;

  // Create data
  std::vector<int> in(count, 0);
  std::vector<int> out(count, 0);
  std::vector<int> res(count, 0);
  for (int i = 0; i < count; i++) {
    in[i] = count - 1 - i + bias;
    res[i] = i + bias;
  }
  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(&in));
  taskDataSeq->inputs_count.emplace_back(in.size());
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(&out));
  taskDataSeq->outputs_count.emplace_back(out.size());

  // Create Task
  TestTaskSequential testTaskSequential(taskDataSeq);
  ASSERT_EQ(testTaskSequential.validation(), true);
  ASSERT_EQ(testTaskSequential.pre_processing(), true);
  ASSERT_EQ(testTaskSequential.run(), true);
  ASSERT_EQ(testTaskSequential.post_processing(), true);
  ASSERT_EQ(res, out);
}

TEST(kiselev_i_shell_simple_seq, check_100_size_random) {
  const int count = 100;

  // Create data
  std::vector<int> in(count, 0);
  std::vector<int> out(count, 0);
  std::vector<int> res(count, 0);
  for (int i = 0; i < count; i++) {
    int a = std::rand() % 100;
    in[i] = a;
    res[i] = a;
  }
  sort(res.begin(), res.end());
  // Create TaskData
  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(&in));
  taskDataSeq->inputs_count.emplace_back(in.size());
  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(&out));
  taskDataSeq->outputs_count.emplace_back(out.size());

  // Create Task
  TestTaskSequential testTaskSequential(taskDataSeq);
  ASSERT_EQ(testTaskSequential.validation(), true);
  ASSERT_EQ(testTaskSequential.pre_processing(), true);
  ASSERT_EQ(testTaskSequential.run(), true);
  ASSERT_EQ(testTaskSequential.post_processing(), true);
  ASSERT_EQ(res, out);
}

// TEST(kiselev_i_shell_simple_seq, check_incorrect_input) {
//  const int count = 2;

  // Create data
//  std::vector<std::vector<int>> in = {{2, 1}, {4, 3}};
//  std::vector<int> out(count, 0);
//  std::vector<int> res = {1, 2, 3, 4};
  // Create TaskData
//  std::shared_ptr<ppc::core::TaskData> taskDataSeq = std::make_shared<ppc::core::TaskData>();
//  taskDataSeq->inputs.emplace_back(reinterpret_cast<uint8_t *>(&in));
//  taskDataSeq->inputs_count.emplace_back(in.size());
//  taskDataSeq->outputs.emplace_back(reinterpret_cast<uint8_t *>(&out));
//  taskDataSeq->outputs_count.emplace_back(out.size());

  // Create Task
//  TestTaskSequential testTaskSequential(taskDataSeq);
//  ASSERT_EQ(testTaskSequential.validation(), false);
// }
