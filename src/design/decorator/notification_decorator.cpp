#include "notification_decorator.h"

NotificationDecorator::NotificationDecorator(std::unique_ptr<Notification> notif)
    : wrappee(std::move(notif)) {}

std::string SMSNotification::send() const
{
  return wrappee->send() + " + Sending SMS Notification";
}

SMSNotification::SMSNotification(std::unique_ptr<Notification> notif)
    : NotificationDecorator(std::move(notif)) {}

std::string PushNotification::send() const
{
  return wrappee->send() + " + Sending Push Notification";
}

PushNotification::PushNotification(std::unique_ptr<Notification> notif)
    : NotificationDecorator(std::move(notif)) {}
