#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <string>
#include <memory>

// 通知の基本インターフェース
class Notification
{
public:
  virtual ~Notification() = default;
  virtual std::string send() const = 0;
};

// 基本的な通知（Eメール）
class EmailNotification : public Notification
{
public:
  std::string send() const override;
};

#endif // NOTIFICATION_H