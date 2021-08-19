#ifndef GOLDBACHMATHORDERRESPONSEHANDLER_H
#define GOLDBACHMATHORDERRESPONSEHANDLER_H
#pragma once

#include "Consumer.hpp"
#include "GoldbachProccessedMathOrder.hpp"

class GoldbachMathOrderResponseHandler
    : public Consumer<GoldbachProccessedMathOrder> {
 private:
 public:
  GoldbachMathOrderResponseHandler();
  ~GoldbachMathOrderResponseHandler();

  /**
  Override this method to start the thread's tasks.
  */
  int run() override;
  /**
  Override this method to process any data extracted from the queue
  */
  void consume(const GoldbachProccessedMathOrder& data) override;
};
#endif