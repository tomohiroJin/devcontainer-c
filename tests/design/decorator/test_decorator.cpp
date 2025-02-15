#include "design/decorator/notification.h"
#include "design/decorator/notification_decorator.h"
#include <gtest/gtest.h>

// 基本の Eメール通知のテスト
TEST(DecoratorPatternTest, TestEmailNotification)
{
  std::unique_ptr<Notification> email = std::make_unique<EmailNotification>();
  EXPECT_EQ(email->send(), "Sending Email Notification");
}

// SMS デコレーターのテスト
TEST(DecoratorPatternTest, TestSMSNotification)
{
  std::unique_ptr<Notification> email = std::make_unique<EmailNotification>();
  std::unique_ptr<Notification> sms = std::make_unique<SMSNotification>(std::move(email));
  EXPECT_EQ(sms->send(), "Sending Email Notification + Sending SMS Notification");
}

// プッシュ通知デコレーターのテスト
TEST(DecoratorPatternTest, TestPushNotification)
{
  std::unique_ptr<Notification> email = std::make_unique<EmailNotification>();
  std::unique_ptr<Notification> push = std::make_unique<PushNotification>(std::move(email));
  EXPECT_EQ(push->send(), "Sending Email Notification + Sending Push Notification");
}

// 複数のデコレーターを適用
TEST(DecoratorPatternTest, TestMultipleDecorators)
{
  std::unique_ptr<Notification> email = std::make_unique<EmailNotification>();
  std::unique_ptr<Notification> sms = std::make_unique<SMSNotification>(std::move(email));
  std::unique_ptr<Notification> push = std::make_unique<PushNotification>(std::move(sms));
  EXPECT_EQ(push->send(), "Sending Email Notification + Sending SMS Notification + Sending Push Notification");
}