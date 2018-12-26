#include <queue>
#include <algorithm>
/*
template<class T, class Container = std::vector<T>, class cmp=std::greater<T> >
class pri_queue : public std::priority_queue<T, Container, cmp> {
  public:
    auto begin() {
      return this->c.begin();
    }

    auto end() {
      return this->c.end();
    }

    auto find(T val) {
      return std::find(begin(), end(), val);
    }

    bool remove(const T& value) {
      auto it = this->find(value);
      if (it != this->c.end()) {
        this->c.erase(it);
        std::make_heap(this->c.begin(), this->c.end(), this->comp);
        return true;
      } else {
        return false;
      }
    }

};*/
template<typename T>
class pri_queue : public std::priority_queue<T, std::vector<T>>
{
    public:

      auto find(const T& val) {
        auto it = std::find(this->c.begin(), this->c.end(), val);
        if (it != this->c.end())
          return *it;
      }
    bool remove(const T& value) {
    auto it = std::find(this->c.begin(), this->c.end(), value);
    if (it != this->c.end()) {
      this->c.erase(it);
      std::make_heap(this->c.begin(), this->c.end(), this->comp);
      return true;
    } else {
        return false;
      }
    }

    auto get(const char& name) {
      for (auto it = this->c.begin(); it != this->c.end(); it++) {
        if ((*it).name == name) {
          return *it;
        }
      }
    }

};
