#ifndef T0946_MIN_MAX_QUEUE_HPP_
#define T0946_MIN_MAX_QUEUE_HPP_

#include <queue>

namespace t0946 {
template <typename T, class Container = std::deque<T> >
class MinMaxQueue {
 private:
  MinMaxQueue(const MinMaxQueue&);
  MinMaxQueue& operator=(const MinMaxQueue&);

 public:
  typedef typename Container::value_type value_type;
  typedef typename Container::reference reference;
  typedef typename Container::const_reference const_reference;
  typedef typename Container::size_type size_type;
  typedef Container container_type;

  MinMaxQueue() {}

  bool empty() const { return queue_.empty(); }

  size_type size() const { return queue_.size(); }

  value_type& front() { return queue_.front(); }
  const value_type& front() const { return queue_.front(); }

  value_type& back() { return queue_.back(); }
  const value_type& back() const { return queue_.back(); }

  void push(const value_type& x) {
    queue_.push_back(x);
    PushMinMax();
  }

#if __cplusplus >= 201103L
  void push(value_type&& x) {
    queue_.push_back(x);
    PushMinMax();
  }
#endif

#if __cplusplus >= 201103L
  template <class... Args>
  void emplace(Args&&... args) {
    queue_.emplace_back(std::forward<Args>(args)...);
    PushMinMax();
  }
#endif

  void pop() {
    const T& front = queue_.front();
    if (&front == min_queue_.front()) min_queue_.pop_front();
    if (&front == max_queue_.front()) max_queue_.pop_front();
    queue_.pop_front();
  }

#if __cplusplus >= 201103L
  void swap(MinMaxQueue& q) {
    queue_.swap(q.queue_);
    min_queue_.swap(q.min_queue_);
    max_queue_.swap(q.max_queue_);
  }
#endif

  // Interfaces for min/max
  const value_type& Min() const { return *min_queue_.front(); }
  const value_type& Max() const { return *max_queue_.front(); }

 private:
  void PushMinMax() {
    const T& back = queue_.back();

    while (!min_queue_.empty() && *min_queue_.back() > back) min_queue_.pop_back();
    min_queue_.push_back(&back);

    while (!max_queue_.empty() && *max_queue_.back() < back) max_queue_.pop_back();
    max_queue_.push_back(&back);
  }

  Container queue_;
  std::deque<const T*> min_queue_;
  std::deque<const T*> max_queue_;
};
}  // namespace t0946

namespace std {
template <typename T, class Container>
void swap(t0946::MinMaxQueue<T, Container>& q1, t0946::MinMaxQueue<T, Container>& q2) {
  q1.swap(q2);
}
}  // namespace std

#endif  // T0946_MIN_MAX_QUEUE_HPP_
