/// @copyright 2020 ECCI, Universidad de Costa Rica. All rights reserved
/// This code is released under the GNU Public License version 3
/// @author Jeisson Hidalgo-Céspedes <jeisson.hidalgo@ucr.ac.cr>

#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <mutex>
#include <queue>

#include "common.hpp"
#include "Semaphore.hpp"

/**
 * @brief A thread-safe generic queue for consumer-producer pattern.
 *
 * @remark None of the methods of this class can be const because all
 * methods require lock the mutex to avoid race-conditions
 */
template <typename DataType>
class Queue {
  DISABLE_COPY(Queue);

 protected:
  /// All read or write operations are mutually exclusive
  std::mutex mutex;
  /// Indicates if there are consumable elements in the queue
  Semaphore canConsume;
  /// Contains the actual data shared between producer and consumer
  std::queue<DataType> queue;

 public:
  /// Constructor
  Queue()
    : canConsume(0) {
  }

  /// Destructor
  ~Queue() {
  }

  /// Produces an element that is pushed in the queue
  /// The semaphore is increased to wait potential consumers
  void push(const DataType& data) {
    this->mutex.lock();
    this->queue.push(data);
    this->mutex.unlock();
    this->canConsume.signal();
  }

  /// Consumes the next available element. If the queue is empty, blocks the
  /// calling thread until an element is produced and enqueue
  /// @return A copy of the element that was removed from the queue
  DataType pop() {
    this->canConsume.wait();
    this->mutex.lock();
    DataType result = this->queue.front();
    this->queue.pop();
    this->mutex.unlock();
    return result;
  }
};

#endif  // QUEUE_HPP
