#ifndef NOTIFICATION_DECORATOR_H
#define NOTIFICATION_DECORATOR_H

#include "notification.h"

// 通知のデコレーター基底クラス
class NotificationDecorator : public Notification
{
protected:
  std::unique_ptr<Notification> wrappee;

public:
  NotificationDecorator(std::unique_ptr<Notification> notif);
  std::string send() const override = 0;
};

// SMS通知のデコレーター
class SMSNotification : public NotificationDecorator
{
public:
  SMSNotification(std::unique_ptr<Notification> notif);
  std::string send() const override;
};

// プッシュ通知のデコレーター
class PushNotification : public NotificationDecorator
{
public:
  PushNotification(std::unique_ptr<Notification> notif);
  std::string send() const override;
};

#endif // NOTIFICATION_DECORATOR_H