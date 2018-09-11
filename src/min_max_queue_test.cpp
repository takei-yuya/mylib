#include <queue>
#include <list>

#include "gtest/gtest.h"
#include "min_max_queue.hpp"

namespace t0946 {

TEST(SimpleTest, SimpleTest) {
  MinMaxQueue<int> mmq;

  EXPECT_EQ(0u, mmq.size());
  EXPECT_TRUE(mmq.empty());

  mmq.push(1);
  EXPECT_EQ(1, mmq.front());
  EXPECT_EQ(1, mmq.Min());
  EXPECT_EQ(1, mmq.Max());
  EXPECT_EQ(1u, mmq.size());
  EXPECT_FALSE(mmq.empty());

  mmq.push(2);
  EXPECT_EQ(1, mmq.front());
  EXPECT_EQ(1, mmq.Min());
  EXPECT_EQ(2, mmq.Max());
  EXPECT_EQ(2u, mmq.size());
  EXPECT_FALSE(mmq.empty());

  mmq.push(3);
  EXPECT_EQ(1, mmq.front());
  EXPECT_EQ(1, mmq.Min());
  EXPECT_EQ(3, mmq.Max());
  EXPECT_EQ(3u, mmq.size());
  EXPECT_FALSE(mmq.empty());

  mmq.pop();
  EXPECT_EQ(2, mmq.front());
  EXPECT_EQ(2, mmq.Min());
  EXPECT_EQ(3, mmq.Max());
  EXPECT_EQ(2u, mmq.size());
  EXPECT_FALSE(mmq.empty());

  mmq.push(100);
  EXPECT_EQ(2, mmq.front());
  EXPECT_EQ(2, mmq.Min());
  EXPECT_EQ(100, mmq.Max());
  EXPECT_EQ(3u, mmq.size());
  EXPECT_FALSE(mmq.empty());

  mmq.push(5);
  EXPECT_EQ(2, mmq.front());
  EXPECT_EQ(2, mmq.Min());
  EXPECT_EQ(100, mmq.Max());
  EXPECT_EQ(4u, mmq.size());
  EXPECT_FALSE(mmq.empty());

  mmq.pop();
  EXPECT_EQ(3, mmq.front());
  EXPECT_EQ(3, mmq.Min());
  EXPECT_EQ(100, mmq.Max());
  EXPECT_EQ(3u, mmq.size());
  EXPECT_FALSE(mmq.empty());

  mmq.pop();
  EXPECT_EQ(100, mmq.front());
  EXPECT_EQ(5, mmq.Min());
  EXPECT_EQ(100, mmq.Max());
  EXPECT_EQ(2u, mmq.size());
  EXPECT_FALSE(mmq.empty());

  mmq.pop();
  EXPECT_EQ(5, mmq.front());
  EXPECT_EQ(5, mmq.Min());
  EXPECT_EQ(5, mmq.Max());
  EXPECT_EQ(1u, mmq.size());
  EXPECT_FALSE(mmq.empty());

  mmq.push(5);
  EXPECT_EQ(5, mmq.front());
  EXPECT_EQ(5, mmq.Min());
  EXPECT_EQ(5, mmq.Max());
  EXPECT_EQ(2u, mmq.size());
  EXPECT_FALSE(mmq.empty());

  mmq.pop();
  EXPECT_EQ(5, mmq.front());
  EXPECT_EQ(5, mmq.Min());
  EXPECT_EQ(5, mmq.Max());
  EXPECT_EQ(1u, mmq.size());
  EXPECT_FALSE(mmq.empty());

  mmq.pop();
  EXPECT_EQ(0u, mmq.size());
  EXPECT_TRUE(mmq.empty());
}

TEST(SimpleTest, SimpleTest_list) {
  MinMaxQueue<int, std::list<int>  > mmq;

  EXPECT_EQ(0u, mmq.size());
  EXPECT_TRUE(mmq.empty());

  mmq.push(1);
  EXPECT_EQ(1, mmq.front());
  EXPECT_EQ(1, mmq.Min());
  EXPECT_EQ(1, mmq.Max());
  EXPECT_EQ(1u, mmq.size());
  EXPECT_FALSE(mmq.empty());

  mmq.push(2);
  EXPECT_EQ(1, mmq.front());
  EXPECT_EQ(1, mmq.Min());
  EXPECT_EQ(2, mmq.Max());
  EXPECT_EQ(2u, mmq.size());
  EXPECT_FALSE(mmq.empty());

  mmq.push(3);
  EXPECT_EQ(1, mmq.front());
  EXPECT_EQ(1, mmq.Min());
  EXPECT_EQ(3, mmq.Max());
  EXPECT_EQ(3u, mmq.size());
  EXPECT_FALSE(mmq.empty());

  mmq.pop();
  EXPECT_EQ(2, mmq.front());
  EXPECT_EQ(2, mmq.Min());
  EXPECT_EQ(3, mmq.Max());
  EXPECT_EQ(2u, mmq.size());
  EXPECT_FALSE(mmq.empty());

  mmq.push(100);
  EXPECT_EQ(2, mmq.front());
  EXPECT_EQ(2, mmq.Min());
  EXPECT_EQ(100, mmq.Max());
  EXPECT_EQ(3u, mmq.size());
  EXPECT_FALSE(mmq.empty());

  mmq.push(5);
  EXPECT_EQ(2, mmq.front());
  EXPECT_EQ(2, mmq.Min());
  EXPECT_EQ(100, mmq.Max());
  EXPECT_EQ(4u, mmq.size());
  EXPECT_FALSE(mmq.empty());

  mmq.pop();
  EXPECT_EQ(3, mmq.front());
  EXPECT_EQ(3, mmq.Min());
  EXPECT_EQ(100, mmq.Max());
  EXPECT_EQ(3u, mmq.size());
  EXPECT_FALSE(mmq.empty());

  mmq.pop();
  EXPECT_EQ(100, mmq.front());
  EXPECT_EQ(5, mmq.Min());
  EXPECT_EQ(100, mmq.Max());
  EXPECT_EQ(2u, mmq.size());
  EXPECT_FALSE(mmq.empty());

  mmq.pop();
  EXPECT_EQ(5, mmq.front());
  EXPECT_EQ(5, mmq.Min());
  EXPECT_EQ(5, mmq.Max());
  EXPECT_EQ(1u, mmq.size());
  EXPECT_FALSE(mmq.empty());

  mmq.push(5);
  EXPECT_EQ(5, mmq.front());
  EXPECT_EQ(5, mmq.Min());
  EXPECT_EQ(5, mmq.Max());
  EXPECT_EQ(2u, mmq.size());
  EXPECT_FALSE(mmq.empty());

  mmq.pop();
  EXPECT_EQ(5, mmq.front());
  EXPECT_EQ(5, mmq.Min());
  EXPECT_EQ(5, mmq.Max());
  EXPECT_EQ(1u, mmq.size());
  EXPECT_FALSE(mmq.empty());

  mmq.pop();
  EXPECT_EQ(0u, mmq.size());
  EXPECT_TRUE(mmq.empty());
}

}  // namespace t0946
