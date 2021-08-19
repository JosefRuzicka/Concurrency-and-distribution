TEMPLATE = app
QT -= core
CONFIG += console c++2a
CONFIG -= qt app_bundle
LIBS += -pthread

INCLUDEPATH += common

SOURCES += \
  common/Semaphore.cpp \
  common/Thread.cpp \
  DispatcherTest.cpp \
  ProducerConsumerTest.cpp \
  ProducerTest.cpp \
  UtilityTest.cpp \
  main.cpp \
    ConsumerTest.cpp \
    LogTest.cpp

HEADERS += \
  common/Consumer.hpp \
  common/Dispatcher.hpp \
  common/Producer.hpp \
  common/Queue.hpp \
  common/Semaphore.hpp \
  common/Thread.hpp \
  common/common.hpp \ \
  DispatcherTest.hpp \
  NetworkMessage.hpp \
  ProducerConsumerTest.hpp \
  ProducerTest.hpp \
  UtilityTest.hpp \
    ConsumerTest.hpp \
    LogTest.hpp
