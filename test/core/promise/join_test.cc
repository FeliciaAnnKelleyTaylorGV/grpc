// Copyright 2021 gRPC authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "src/core/lib/promise/join.h"

#include <memory>
#include <tuple>

#include "gmock/gmock.h"
#include "gtest/gtest.h"

#include "src/core/lib/promise/poll.h"
#include "test/core/promise/poll_matcher.h"

namespace grpc_core {

TEST(JoinTest, Join1) {
  EXPECT_THAT(Join([] { return 3; })(), IsReady(std::make_tuple(3)));
}

TEST(JoinTest, Join2) {
  EXPECT_THAT(Join([] { return 3; }, [] { return 4; })(),
              IsReady(std::make_tuple(3, 4)));
}

TEST(JoinTest, Join3) {
  EXPECT_THAT(Join([] { return 3; }, [] { return 4; }, [] { return 5; })(),
              IsReady(std::make_tuple(3, 4, 5)));
}

}  // namespace grpc_core

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
