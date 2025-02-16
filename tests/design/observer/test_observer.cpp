#include "design/observer/observer.h"
#include "design/observer/user.h"
#include <gtest/gtest.h>

// Observer パターンのテスト
TEST(ObserverPatternTest, TestNotification)
{
  Subject subject;
  auto user1 = std::make_shared<User>("Alice");
  auto user2 = std::make_shared<User>("Bob");

  subject.addObserver(user1);
  subject.addObserver(user2);

  testing::internal::CaptureStdout();
  subject.notifyObservers("New event available!");
  std::string output = testing::internal::GetCapturedStdout();

  EXPECT_NE(output.find("User Alice received message: New event available!"), std::string::npos);
  EXPECT_NE(output.find("User Bob received message: New event available!"), std::string::npos);
}

TEST(ObserverPatternTest, TestRemoveObserver)
{
  Subject subject;
  auto user1 = std::make_shared<User>("Alice");
  auto user2 = std::make_shared<User>("Bob");

  subject.addObserver(user1);
  subject.addObserver(user2);

  // Bob を削除
  subject.removeObserver(user2);

  testing::internal::CaptureStdout();
  subject.notifyObservers("Update!");
  std::string output = testing::internal::GetCapturedStdout();

  // Alice には通知されるが、Bob には通知されない
  EXPECT_NE(output.find("User Alice received message: Update!"), std::string::npos);
  EXPECT_EQ(output.find("User Bob received message: Update!"), std::string::npos);
}
