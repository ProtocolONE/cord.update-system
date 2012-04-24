#ifndef _GGS_GAMEDOWNLOADER_TEST_SIGNALCOUNTER_H_
#define _GGS_GAMEDOWNLOADER_TEST_SIGNALCOUNTER_H_

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

#endif // _GGS_GAMEDOWNLOADER_TEST_SIGNALCOUNTER_H_