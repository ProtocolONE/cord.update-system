#pragma once

#include <QtCore/QObject>

class SignalCounter : public QObject
{
  Q_OBJECT
public:
  SignalCounter();
  ~SignalCounter();

  int eventCount() const;
  
public slots:
  void eventSlot();

private:
  int _eventCount;
};
