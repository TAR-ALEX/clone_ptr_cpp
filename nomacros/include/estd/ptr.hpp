/*


THIS IS AN AUTO GENERATED FILE FROM MACRO EXPANSION, DO NOT EDIT, CHANGE THE ORIGINAL


BSD 3-Clause License

Copyright (c) 2022, Alex Tarasov
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once

#include <memory>
#include <optional>
#include <type_traits>

namespace estd {
class clonable {
 public:
  virtual clonable* clone() const = 0;
  virtual ~clonable() = default;
};

template <typename T>
class clone_ptr : public std::unique_ptr<T> {
  static_assert(!std::is_array<T>::value,
                "Error: clone_ptr not supported on raw arrays, they are not "
                "easily copyable.");

  using Parent = std::unique_ptr<T>;

 public:
  inline T* get() const noexcept { return Parent::get(); }
  inline bool has_value() const { return this->get() != nullptr; }
  inline T& value() const {
    if (this->get() == nullptr)
      throw std::runtime_error("getting the value of nullptr");
    return *(this->get());
  }

  void reset() { Parent::reset(nullptr); }
  void reset(std::nullptr_t) { Parent::reset(nullptr); }
  void reset(const T& other) {
    if constexpr (std::is_base_of<clonable, T>::value) {
      Parent::reset((T*)other.clone());
    } else {
      Parent::reset(new T(other));
    }
  }
  void reset(T&& other) {
    if constexpr (std::is_base_of<clonable, T>::value) {
      Parent::reset((T*)other.clone());
    } else {
      Parent::reset(new T(other));
    }
  }
  void reset(T* other) { Parent::reset(other); }

  template <typename T2>
  void reset(const clone_ptr<T2>& other) {
    if (other.get() == nullptr) {
      Parent::reset(nullptr);
      return;
    }
    if constexpr (std::is_base_of<clonable, T>::value) {
      Parent::reset((T*)other->clone());
    } else {
      Parent::reset(new T(*other));
    }
  }

  template <typename... Args,
            typename = decltype(typename std::remove_all_extents<T>::type(
                std::declval<Args>()...))>
  clone_ptr(Args&&... params) : Parent(new T(std::forward<Args>(params)...)) {}

  clone_ptr() { reset(nullptr); }
  clone_ptr(std::nullptr_t) { reset(nullptr); }
  clone_ptr(T* other) { reset(other); }
  clone_ptr(const clone_ptr& other) { reset(other); }
  template <typename T2>
  clone_ptr(clone_ptr<T2> other) {
    reset(other);
  }
  clone_ptr& operator=(std::nullptr_t) {
    reset(nullptr);
    return *this;
  }
  clone_ptr& operator=(T* other) {
    reset(other);
    return *this;
  }
  clone_ptr& operator=(const clone_ptr& other) {
    reset(other);
    return *this;
  }
  template <typename T2>
  clone_ptr& operator=(clone_ptr<T2> other) {
    reset(other);
    return *this;
  }
  clone_ptr(const T& other) { reset(other); }
  clone_ptr(T&& other) { reset(other); }
  clone_ptr& operator=(const T& other) {
    this->reset(other);
    return *this;
  }
  clone_ptr& operator=(T&& other) {
    this->reset(other);
    return *this;
  }

  decltype(auto) begin() { return this->value().begin(); }
  decltype(auto) begin() const { return this->value().begin(); }
  decltype(auto) end() { return this->value().end(); }
  decltype(auto) end() const { return this->value().end(); }
  template <typename T2>
  decltype(auto) operator[](T2 i) const {
    if constexpr (!std::is_array<T>::value) {
      return this->value()[i];
    } else {
      return (this->get())[i];
    }
  }
  template <typename T2>
  decltype(auto) operator+(const T2& other) {
    return this->value() + other;
  }
  template <typename T2>
  decltype(auto) operator+(T2&& other) {
    return this->value() + other;
  }
  template <typename T2>
  decltype(auto) operator+(const clone_ptr<T2>& other) {
    return this->value() + other.value();
  }
  template <typename T2>
  decltype(auto) operator+(clone_ptr<T2>&& other) {
    return this->value() + other.value();
  }
  template <typename T2>
  decltype(auto) operator-(const T2& other) {
    return this->value() - other;
  }
  template <typename T2>
  decltype(auto) operator-(T2&& other) {
    return this->value() - other;
  }
  template <typename T2>
  decltype(auto) operator-(const clone_ptr<T2>& other) {
    return this->value() - other.value();
  }
  template <typename T2>
  decltype(auto) operator-(clone_ptr<T2>&& other) {
    return this->value() - other.value();
  }
  template <typename T2>
  decltype(auto) operator*(const T2& other) {
    return this->value() * other;
  }
  template <typename T2>
  decltype(auto) operator*(T2&& other) {
    return this->value() * other;
  }
  template <typename T2>
  decltype(auto) operator*(const clone_ptr<T2>& other) {
    return this->value() * other.value();
  }
  template <typename T2>
  decltype(auto) operator*(clone_ptr<T2>&& other) {
    return this->value() * other.value();
  }
  template <typename T2>
  decltype(auto) operator/(const T2& other) {
    return this->value() / other;
  }
  template <typename T2>
  decltype(auto) operator/(T2&& other) {
    return this->value() / other;
  }
  template <typename T2>
  decltype(auto) operator/(const clone_ptr<T2>& other) {
    return this->value() / other.value();
  }
  template <typename T2>
  decltype(auto) operator/(clone_ptr<T2>&& other) {
    return this->value() / other.value();
  }
  template <typename T2>
  decltype(auto) operator%(const T2& other) {
    return this->value() % other;
  }
  template <typename T2>
  decltype(auto) operator%(T2&& other) {
    return this->value() % other;
  }
  template <typename T2>
  decltype(auto) operator%(const clone_ptr<T2>& other) {
    return this->value() % other.value();
  }
  template <typename T2>
  decltype(auto) operator%(clone_ptr<T2>&& other) {
    return this->value() % other.value();
  }
  template <typename T2>
  decltype(auto) operator^(const T2& other) {
    return this->value() ^ other;
  }
  template <typename T2>
  decltype(auto) operator^(T2&& other) {
    return this->value() ^ other;
  }
  template <typename T2>
  decltype(auto) operator^(const clone_ptr<T2>& other) {
    return this->value() ^ other.value();
  }
  template <typename T2>
  decltype(auto) operator^(clone_ptr<T2>&& other) {
    return this->value() ^ other.value();
  }
  template <typename T2>
  decltype(auto) operator&(const T2& other) {
    return this->value() & other;
  }
  template <typename T2>
  decltype(auto) operator&(T2&& other) {
    return this->value() & other;
  }
  template <typename T2>
  decltype(auto) operator&(const clone_ptr<T2>& other) {
    return this->value() & other.value();
  }
  template <typename T2>
  decltype(auto) operator&(clone_ptr<T2>&& other) {
    return this->value() & other.value();
  }
  template <typename T2>
  decltype(auto) operator|(const T2& other) {
    return this->value() | other;
  }
  template <typename T2>
  decltype(auto) operator|(T2&& other) {
    return this->value() | other;
  }
  template <typename T2>
  decltype(auto) operator|(const clone_ptr<T2>& other) {
    return this->value() | other.value();
  }
  template <typename T2>
  decltype(auto) operator|(clone_ptr<T2>&& other) {
    return this->value() | other.value();
  }
  template <typename T2>
  decltype(auto) operator<(const T2& other) {
    return this->value() < other;
  }
  template <typename T2>
  decltype(auto) operator<(T2&& other) {
    return this->value() < other;
  }
  template <typename T2>
  decltype(auto) operator<(const clone_ptr<T2>& other) {
    return this->value() < other.value();
  }
  template <typename T2>
  decltype(auto) operator<(clone_ptr<T2>&& other) {
    return this->value() < other.value();
  }
  template <typename T2>
  decltype(auto) operator>(const T2& other) {
    return this->value() > other;
  }
  template <typename T2>
  decltype(auto) operator>(T2&& other) {
    return this->value() > other;
  }
  template <typename T2>
  decltype(auto) operator>(const clone_ptr<T2>& other) {
    return this->value() > other.value();
  }
  template <typename T2>
  decltype(auto) operator>(clone_ptr<T2>&& other) {
    return this->value() > other.value();
  }
  template <typename T2>
  decltype(auto) operator+=(const T2& other) {
    return this->value() += other;
  }
  template <typename T2>
  decltype(auto) operator+=(T2&& other) {
    return this->value() += other;
  }
  template <typename T2>
  decltype(auto) operator+=(const clone_ptr<T2>& other) {
    return this->value() += other.value();
  }
  template <typename T2>
  decltype(auto) operator+=(clone_ptr<T2>&& other) {
    return this->value() += other.value();
  }
  template <typename T2>
  decltype(auto) operator-=(const T2& other) {
    return this->value() -= other;
  }
  template <typename T2>
  decltype(auto) operator-=(T2&& other) {
    return this->value() -= other;
  }
  template <typename T2>
  decltype(auto) operator-=(const clone_ptr<T2>& other) {
    return this->value() -= other.value();
  }
  template <typename T2>
  decltype(auto) operator-=(clone_ptr<T2>&& other) {
    return this->value() -= other.value();
  }
  template <typename T2>
  decltype(auto) operator*=(const T2& other) {
    return this->value() *= other;
  }
  template <typename T2>
  decltype(auto) operator*=(T2&& other) {
    return this->value() *= other;
  }
  template <typename T2>
  decltype(auto) operator*=(const clone_ptr<T2>& other) {
    return this->value() *= other.value();
  }
  template <typename T2>
  decltype(auto) operator*=(clone_ptr<T2>&& other) {
    return this->value() *= other.value();
  }
  template <typename T2>
  decltype(auto) operator/=(const T2& other) {
    return this->value() /= other;
  }
  template <typename T2>
  decltype(auto) operator/=(T2&& other) {
    return this->value() /= other;
  }
  template <typename T2>
  decltype(auto) operator/=(const clone_ptr<T2>& other) {
    return this->value() /= other.value();
  }
  template <typename T2>
  decltype(auto) operator/=(clone_ptr<T2>&& other) {
    return this->value() /= other.value();
  }
  template <typename T2>
  decltype(auto) operator%=(const T2& other) {
    return this->value() %= other;
  }
  template <typename T2>
  decltype(auto) operator%=(T2&& other) {
    return this->value() %= other;
  }
  template <typename T2>
  decltype(auto) operator%=(const clone_ptr<T2>& other) {
    return this->value() %= other.value();
  }
  template <typename T2>
  decltype(auto) operator%=(clone_ptr<T2>&& other) {
    return this->value() %= other.value();
  }
  template <typename T2>
  decltype(auto) operator^=(const T2& other) {
    return this->value() ^= other;
  }
  template <typename T2>
  decltype(auto) operator^=(T2&& other) {
    return this->value() ^= other;
  }
  template <typename T2>
  decltype(auto) operator^=(const clone_ptr<T2>& other) {
    return this->value() ^= other.value();
  }
  template <typename T2>
  decltype(auto) operator^=(clone_ptr<T2>&& other) {
    return this->value() ^= other.value();
  }
  template <typename T2>
  decltype(auto) operator&=(const T2& other) {
    return this->value() &= other;
  }
  template <typename T2>
  decltype(auto) operator&=(T2&& other) {
    return this->value() &= other;
  }
  template <typename T2>
  decltype(auto) operator&=(const clone_ptr<T2>& other) {
    return this->value() &= other.value();
  }
  template <typename T2>
  decltype(auto) operator&=(clone_ptr<T2>&& other) {
    return this->value() &= other.value();
  }
  template <typename T2>
  decltype(auto) operator|=(const T2& other) {
    return this->value() |= other;
  }
  template <typename T2>
  decltype(auto) operator|=(T2&& other) {
    return this->value() |= other;
  }
  template <typename T2>
  decltype(auto) operator|=(const clone_ptr<T2>& other) {
    return this->value() |= other.value();
  }
  template <typename T2>
  decltype(auto) operator|=(clone_ptr<T2>&& other) {
    return this->value() |= other.value();
  }
  template <typename T2>
  decltype(auto) operator<<(const T2& other) {
    return this->value() << other;
  }
  template <typename T2>
  decltype(auto) operator<<(T2&& other) {
    return this->value() << other;
  }
  template <typename T2>
  decltype(auto) operator<<(const clone_ptr<T2>& other) {
    return this->value() << other.value();
  }
  template <typename T2>
  decltype(auto) operator<<(clone_ptr<T2>&& other) {
    return this->value() << other.value();
  }
  template <typename T2>
  decltype(auto) operator>>(const T2& other) {
    return this->value() >> other;
  }
  template <typename T2>
  decltype(auto) operator>>(T2&& other) {
    return this->value() >> other;
  }
  template <typename T2>
  decltype(auto) operator>>(const clone_ptr<T2>& other) {
    return this->value() >> other.value();
  }
  template <typename T2>
  decltype(auto) operator>>(clone_ptr<T2>&& other) {
    return this->value() >> other.value();
  }
  template <typename T2>
  decltype(auto) operator<<=(const T2& other) {
    return this->value() <<= other;
  }
  template <typename T2>
  decltype(auto) operator<<=(T2&& other) {
    return this->value() <<= other;
  }
  template <typename T2>
  decltype(auto) operator<<=(const clone_ptr<T2>& other) {
    return this->value() <<= other.value();
  }
  template <typename T2>
  decltype(auto) operator<<=(clone_ptr<T2>&& other) {
    return this->value() <<= other.value();
  }
  template <typename T2>
  decltype(auto) operator>>=(const T2& other) {
    return this->value() >>= other;
  }
  template <typename T2>
  decltype(auto) operator>>=(T2&& other) {
    return this->value() >>= other;
  }
  template <typename T2>
  decltype(auto) operator>>=(const clone_ptr<T2>& other) {
    return this->value() >>= other.value();
  }
  template <typename T2>
  decltype(auto) operator>>=(clone_ptr<T2>&& other) {
    return this->value() >>= other.value();
  }
  template <typename T2>
  decltype(auto) operator<=(const T2& other) {
    return this->value() <= other;
  }
  template <typename T2>
  decltype(auto) operator<=(T2&& other) {
    return this->value() <= other;
  }
  template <typename T2>
  decltype(auto) operator<=(const clone_ptr<T2>& other) {
    return this->value() <= other.value();
  }
  template <typename T2>
  decltype(auto) operator<=(clone_ptr<T2>&& other) {
    return this->value() <= other.value();
  }
  template <typename T2>
  decltype(auto) operator>=(const T2& other) {
    return this->value() >= other;
  }
  template <typename T2>
  decltype(auto) operator>=(T2&& other) {
    return this->value() >= other;
  }
  template <typename T2>
  decltype(auto) operator>=(const clone_ptr<T2>& other) {
    return this->value() >= other.value();
  }
  template <typename T2>
  decltype(auto) operator>=(clone_ptr<T2>&& other) {
    return this->value() >= other.value();
  }
  template <typename T2>
  decltype(auto) operator&&(const T2& other) {
    return this->value() && other;
  }
  template <typename T2>
  decltype(auto) operator&&(T2&& other) {
    return this->value() && other;
  }
  template <typename T2>
  decltype(auto) operator&&(const clone_ptr<T2>& other) {
    return this->value() && other.value();
  }
  template <typename T2>
  decltype(auto) operator&&(clone_ptr<T2>&& other) {
    return this->value() && other.value();
  }
  template <typename T2>
  decltype(auto) operator||(const T2& other) {
    return this->value() || other;
  }
  template <typename T2>
  decltype(auto) operator||(T2&& other) {
    return this->value() || other;
  }
  template <typename T2>
  decltype(auto) operator||(const clone_ptr<T2>& other) {
    return this->value() || other.value();
  }
  template <typename T2>
  decltype(auto) operator||(clone_ptr<T2>&& other) {
    return this->value() || other.value();
  }
  template <typename T2>
  decltype(auto) operator~() {
    return ~this->value();
  }
  template <typename T2>
  decltype(auto) operator!() {
    return !this->value();
  }
  template <typename T2>
  decltype(auto) operator++() {
    return this->value()++;
  }
  template <typename T2>
  decltype(auto) operator--() {
    return this->value()--;
  }
  template <typename T2>
  decltype(auto) operator++(int) {
    return ++this->value();
  }
  template <typename T2>
  decltype(auto) operator--(int) {
    return --this->value();
  }
  template <typename T2>
  decltype(auto) operator,(const T2& other) {
    return (this->value()), other;
  }
  template <typename T2>
  decltype(auto) operator,(T2&& other) {
    return (this->value()), other;
  }
  template <typename... Args>
  decltype(auto) operator()(Args&&... params) {
    (this->value())(std::forward<Args>(params)...);
  }
  bool operator==(std::nullptr_t) { return this->get() == nullptr; }
  template <typename T2>
  decltype(auto) operator==(T2* other) {
    return this->get() == other;
  }
  template <typename T2>
  decltype(auto) operator==(const clone_ptr<T2>& other) {
    return this->get() == other.get();
  }
  template <typename T2>
  decltype(auto) operator==(clone_ptr<T2>&& other) {
    return this->get() == other.get();
  }
  template <typename T2>
  bool operator!=(T2 other) {
    return !(operator==(other));
  }
  inline explicit operator bool() const noexcept {
    return this->get() != nullptr;
  }
  T& operator*() const { return this->value(); }
  T* operator->() const { return &(this->value()); }
};

template <typename T>
class joint_ptr : public std::shared_ptr<T> {
  using Parent = std::shared_ptr<T>;
  static_assert(!std::is_array<T>::value,
                "Error: joint_ptr not supported on raw arrays, they are not "
                "easily copyable.");

 public:
  template <typename... Args,
            typename = decltype(typename std::remove_all_extents<T>::type(
                std::declval<Args>()...))>
  joint_ptr(Args&&... params) : Parent(new T(std::forward<Args>(params)...)) {}

  inline T* get() const noexcept { return Parent::get(); }
  inline bool has_value() const { return this->get() != nullptr; }
  inline T& value() const {
    if (this->get() == nullptr)
      throw std::runtime_error("getting the value of nullptr");
    return *(this->get());
  }

  void reset() { Parent::reset(); }
  void reset(std::nullptr_t) { Parent::reset(); }
  void reset(T* other) { Parent::reset(other); }
  void reset(const T& other) {
    if constexpr (std::is_base_of<clonable, T>::value) {
      Parent::reset((T*)other.clone());
    } else {
      Parent::reset(new T(other));
    }
  }
  void reset(T&& other) {
    if constexpr (std::is_base_of<clonable, T>::value) {
      Parent::reset((T*)other.clone());
    } else {
      Parent::reset(new T(other));
    }
  }

  template <typename T2>
  void reset(const joint_ptr<T2>& other) {
    Parent::operator=(other);
  }

  template <typename T2>
  void reset(const std::shared_ptr<T2>& other) {
    Parent::operator=(other);
  }

  joint_ptr() { reset(nullptr); }
  joint_ptr(std::nullptr_t) { reset(nullptr); }
  joint_ptr(T* other) { reset(other); }
  joint_ptr(const joint_ptr& other) { reset(other); }
  template <typename T2>
  joint_ptr(joint_ptr<T2> other) {
    reset(other);
  }
  joint_ptr& operator=(std::nullptr_t) {
    reset(nullptr);
    return *this;
  }
  joint_ptr& operator=(T* other) {
    reset(other);
    return *this;
  }
  joint_ptr& operator=(const joint_ptr& other) {
    reset(other);
    return *this;
  }
  template <typename T2>
  joint_ptr& operator=(joint_ptr<T2> other) {
    reset(other);
    return *this;
  }
  joint_ptr(const T& other) { reset(other); }
  joint_ptr(T&& other) { reset(other); }
  joint_ptr& operator=(const T& other) {
    this->reset(other);
    return *this;
  }
  joint_ptr& operator=(T&& other) {
    this->reset(other);
    return *this;
  }
  template <typename T2>
  joint_ptr& operator=(const std::shared_ptr<T2>& other) {
    reset(other);
    return *this;
  }
  template <typename T2>
  joint_ptr(const std::shared_ptr<T2>& other) {
    reset(other);
  }

  decltype(auto) begin() { return this->value().begin(); }
  decltype(auto) begin() const { return this->value().begin(); }
  decltype(auto) end() { return this->value().end(); }
  decltype(auto) end() const { return this->value().end(); }
  template <typename T2>
  decltype(auto) operator[](T2 i) const {
    if constexpr (!std::is_array<T>::value) {
      return this->value()[i];
    } else {
      return (this->get())[i];
    }
  }
  template <typename T2>
  decltype(auto) operator+(const T2& other) {
    return this->value() + other;
  }
  template <typename T2>
  decltype(auto) operator+(T2&& other) {
    return this->value() + other;
  }
  template <typename T2>
  decltype(auto) operator+(const joint_ptr<T2>& other) {
    return this->value() + other.value();
  }
  template <typename T2>
  decltype(auto) operator+(joint_ptr<T2>&& other) {
    return this->value() + other.value();
  }
  template <typename T2>
  decltype(auto) operator-(const T2& other) {
    return this->value() - other;
  }
  template <typename T2>
  decltype(auto) operator-(T2&& other) {
    return this->value() - other;
  }
  template <typename T2>
  decltype(auto) operator-(const joint_ptr<T2>& other) {
    return this->value() - other.value();
  }
  template <typename T2>
  decltype(auto) operator-(joint_ptr<T2>&& other) {
    return this->value() - other.value();
  }
  template <typename T2>
  decltype(auto) operator*(const T2& other) {
    return this->value() * other;
  }
  template <typename T2>
  decltype(auto) operator*(T2&& other) {
    return this->value() * other;
  }
  template <typename T2>
  decltype(auto) operator*(const joint_ptr<T2>& other) {
    return this->value() * other.value();
  }
  template <typename T2>
  decltype(auto) operator*(joint_ptr<T2>&& other) {
    return this->value() * other.value();
  }
  template <typename T2>
  decltype(auto) operator/(const T2& other) {
    return this->value() / other;
  }
  template <typename T2>
  decltype(auto) operator/(T2&& other) {
    return this->value() / other;
  }
  template <typename T2>
  decltype(auto) operator/(const joint_ptr<T2>& other) {
    return this->value() / other.value();
  }
  template <typename T2>
  decltype(auto) operator/(joint_ptr<T2>&& other) {
    return this->value() / other.value();
  }
  template <typename T2>
  decltype(auto) operator%(const T2& other) {
    return this->value() % other;
  }
  template <typename T2>
  decltype(auto) operator%(T2&& other) {
    return this->value() % other;
  }
  template <typename T2>
  decltype(auto) operator%(const joint_ptr<T2>& other) {
    return this->value() % other.value();
  }
  template <typename T2>
  decltype(auto) operator%(joint_ptr<T2>&& other) {
    return this->value() % other.value();
  }
  template <typename T2>
  decltype(auto) operator^(const T2& other) {
    return this->value() ^ other;
  }
  template <typename T2>
  decltype(auto) operator^(T2&& other) {
    return this->value() ^ other;
  }
  template <typename T2>
  decltype(auto) operator^(const joint_ptr<T2>& other) {
    return this->value() ^ other.value();
  }
  template <typename T2>
  decltype(auto) operator^(joint_ptr<T2>&& other) {
    return this->value() ^ other.value();
  }
  template <typename T2>
  decltype(auto) operator&(const T2& other) {
    return this->value() & other;
  }
  template <typename T2>
  decltype(auto) operator&(T2&& other) {
    return this->value() & other;
  }
  template <typename T2>
  decltype(auto) operator&(const joint_ptr<T2>& other) {
    return this->value() & other.value();
  }
  template <typename T2>
  decltype(auto) operator&(joint_ptr<T2>&& other) {
    return this->value() & other.value();
  }
  template <typename T2>
  decltype(auto) operator|(const T2& other) {
    return this->value() | other;
  }
  template <typename T2>
  decltype(auto) operator|(T2&& other) {
    return this->value() | other;
  }
  template <typename T2>
  decltype(auto) operator|(const joint_ptr<T2>& other) {
    return this->value() | other.value();
  }
  template <typename T2>
  decltype(auto) operator|(joint_ptr<T2>&& other) {
    return this->value() | other.value();
  }
  template <typename T2>
  decltype(auto) operator<(const T2& other) {
    return this->value() < other;
  }
  template <typename T2>
  decltype(auto) operator<(T2&& other) {
    return this->value() < other;
  }
  template <typename T2>
  decltype(auto) operator<(const joint_ptr<T2>& other) {
    return this->value() < other.value();
  }
  template <typename T2>
  decltype(auto) operator<(joint_ptr<T2>&& other) {
    return this->value() < other.value();
  }
  template <typename T2>
  decltype(auto) operator>(const T2& other) {
    return this->value() > other;
  }
  template <typename T2>
  decltype(auto) operator>(T2&& other) {
    return this->value() > other;
  }
  template <typename T2>
  decltype(auto) operator>(const joint_ptr<T2>& other) {
    return this->value() > other.value();
  }
  template <typename T2>
  decltype(auto) operator>(joint_ptr<T2>&& other) {
    return this->value() > other.value();
  }
  template <typename T2>
  decltype(auto) operator+=(const T2& other) {
    return this->value() += other;
  }
  template <typename T2>
  decltype(auto) operator+=(T2&& other) {
    return this->value() += other;
  }
  template <typename T2>
  decltype(auto) operator+=(const joint_ptr<T2>& other) {
    return this->value() += other.value();
  }
  template <typename T2>
  decltype(auto) operator+=(joint_ptr<T2>&& other) {
    return this->value() += other.value();
  }
  template <typename T2>
  decltype(auto) operator-=(const T2& other) {
    return this->value() -= other;
  }
  template <typename T2>
  decltype(auto) operator-=(T2&& other) {
    return this->value() -= other;
  }
  template <typename T2>
  decltype(auto) operator-=(const joint_ptr<T2>& other) {
    return this->value() -= other.value();
  }
  template <typename T2>
  decltype(auto) operator-=(joint_ptr<T2>&& other) {
    return this->value() -= other.value();
  }
  template <typename T2>
  decltype(auto) operator*=(const T2& other) {
    return this->value() *= other;
  }
  template <typename T2>
  decltype(auto) operator*=(T2&& other) {
    return this->value() *= other;
  }
  template <typename T2>
  decltype(auto) operator*=(const joint_ptr<T2>& other) {
    return this->value() *= other.value();
  }
  template <typename T2>
  decltype(auto) operator*=(joint_ptr<T2>&& other) {
    return this->value() *= other.value();
  }
  template <typename T2>
  decltype(auto) operator/=(const T2& other) {
    return this->value() /= other;
  }
  template <typename T2>
  decltype(auto) operator/=(T2&& other) {
    return this->value() /= other;
  }
  template <typename T2>
  decltype(auto) operator/=(const joint_ptr<T2>& other) {
    return this->value() /= other.value();
  }
  template <typename T2>
  decltype(auto) operator/=(joint_ptr<T2>&& other) {
    return this->value() /= other.value();
  }
  template <typename T2>
  decltype(auto) operator%=(const T2& other) {
    return this->value() %= other;
  }
  template <typename T2>
  decltype(auto) operator%=(T2&& other) {
    return this->value() %= other;
  }
  template <typename T2>
  decltype(auto) operator%=(const joint_ptr<T2>& other) {
    return this->value() %= other.value();
  }
  template <typename T2>
  decltype(auto) operator%=(joint_ptr<T2>&& other) {
    return this->value() %= other.value();
  }
  template <typename T2>
  decltype(auto) operator^=(const T2& other) {
    return this->value() ^= other;
  }
  template <typename T2>
  decltype(auto) operator^=(T2&& other) {
    return this->value() ^= other;
  }
  template <typename T2>
  decltype(auto) operator^=(const joint_ptr<T2>& other) {
    return this->value() ^= other.value();
  }
  template <typename T2>
  decltype(auto) operator^=(joint_ptr<T2>&& other) {
    return this->value() ^= other.value();
  }
  template <typename T2>
  decltype(auto) operator&=(const T2& other) {
    return this->value() &= other;
  }
  template <typename T2>
  decltype(auto) operator&=(T2&& other) {
    return this->value() &= other;
  }
  template <typename T2>
  decltype(auto) operator&=(const joint_ptr<T2>& other) {
    return this->value() &= other.value();
  }
  template <typename T2>
  decltype(auto) operator&=(joint_ptr<T2>&& other) {
    return this->value() &= other.value();
  }
  template <typename T2>
  decltype(auto) operator|=(const T2& other) {
    return this->value() |= other;
  }
  template <typename T2>
  decltype(auto) operator|=(T2&& other) {
    return this->value() |= other;
  }
  template <typename T2>
  decltype(auto) operator|=(const joint_ptr<T2>& other) {
    return this->value() |= other.value();
  }
  template <typename T2>
  decltype(auto) operator|=(joint_ptr<T2>&& other) {
    return this->value() |= other.value();
  }
  template <typename T2>
  decltype(auto) operator<<(const T2& other) {
    return this->value() << other;
  }
  template <typename T2>
  decltype(auto) operator<<(T2&& other) {
    return this->value() << other;
  }
  template <typename T2>
  decltype(auto) operator<<(const joint_ptr<T2>& other) {
    return this->value() << other.value();
  }
  template <typename T2>
  decltype(auto) operator<<(joint_ptr<T2>&& other) {
    return this->value() << other.value();
  }
  template <typename T2>
  decltype(auto) operator>>(const T2& other) {
    return this->value() >> other;
  }
  template <typename T2>
  decltype(auto) operator>>(T2&& other) {
    return this->value() >> other;
  }
  template <typename T2>
  decltype(auto) operator>>(const joint_ptr<T2>& other) {
    return this->value() >> other.value();
  }
  template <typename T2>
  decltype(auto) operator>>(joint_ptr<T2>&& other) {
    return this->value() >> other.value();
  }
  template <typename T2>
  decltype(auto) operator<<=(const T2& other) {
    return this->value() <<= other;
  }
  template <typename T2>
  decltype(auto) operator<<=(T2&& other) {
    return this->value() <<= other;
  }
  template <typename T2>
  decltype(auto) operator<<=(const joint_ptr<T2>& other) {
    return this->value() <<= other.value();
  }
  template <typename T2>
  decltype(auto) operator<<=(joint_ptr<T2>&& other) {
    return this->value() <<= other.value();
  }
  template <typename T2>
  decltype(auto) operator>>=(const T2& other) {
    return this->value() >>= other;
  }
  template <typename T2>
  decltype(auto) operator>>=(T2&& other) {
    return this->value() >>= other;
  }
  template <typename T2>
  decltype(auto) operator>>=(const joint_ptr<T2>& other) {
    return this->value() >>= other.value();
  }
  template <typename T2>
  decltype(auto) operator>>=(joint_ptr<T2>&& other) {
    return this->value() >>= other.value();
  }
  template <typename T2>
  decltype(auto) operator<=(const T2& other) {
    return this->value() <= other;
  }
  template <typename T2>
  decltype(auto) operator<=(T2&& other) {
    return this->value() <= other;
  }
  template <typename T2>
  decltype(auto) operator<=(const joint_ptr<T2>& other) {
    return this->value() <= other.value();
  }
  template <typename T2>
  decltype(auto) operator<=(joint_ptr<T2>&& other) {
    return this->value() <= other.value();
  }
  template <typename T2>
  decltype(auto) operator>=(const T2& other) {
    return this->value() >= other;
  }
  template <typename T2>
  decltype(auto) operator>=(T2&& other) {
    return this->value() >= other;
  }
  template <typename T2>
  decltype(auto) operator>=(const joint_ptr<T2>& other) {
    return this->value() >= other.value();
  }
  template <typename T2>
  decltype(auto) operator>=(joint_ptr<T2>&& other) {
    return this->value() >= other.value();
  }
  template <typename T2>
  decltype(auto) operator&&(const T2& other) {
    return this->value() && other;
  }
  template <typename T2>
  decltype(auto) operator&&(T2&& other) {
    return this->value() && other;
  }
  template <typename T2>
  decltype(auto) operator&&(const joint_ptr<T2>& other) {
    return this->value() && other.value();
  }
  template <typename T2>
  decltype(auto) operator&&(joint_ptr<T2>&& other) {
    return this->value() && other.value();
  }
  template <typename T2>
  decltype(auto) operator||(const T2& other) {
    return this->value() || other;
  }
  template <typename T2>
  decltype(auto) operator||(T2&& other) {
    return this->value() || other;
  }
  template <typename T2>
  decltype(auto) operator||(const joint_ptr<T2>& other) {
    return this->value() || other.value();
  }
  template <typename T2>
  decltype(auto) operator||(joint_ptr<T2>&& other) {
    return this->value() || other.value();
  }
  template <typename T2>
  decltype(auto) operator~() {
    return ~this->value();
  }
  template <typename T2>
  decltype(auto) operator!() {
    return !this->value();
  }
  template <typename T2>
  decltype(auto) operator++() {
    return this->value()++;
  }
  template <typename T2>
  decltype(auto) operator--() {
    return this->value()--;
  }
  template <typename T2>
  decltype(auto) operator++(int) {
    return ++this->value();
  }
  template <typename T2>
  decltype(auto) operator--(int) {
    return --this->value();
  }
  template <typename T2>
  decltype(auto) operator,(const T2& other) {
    return (this->value()), other;
  }
  template <typename T2>
  decltype(auto) operator,(T2&& other) {
    return (this->value()), other;
  }
  template <typename... Args>
  decltype(auto) operator()(Args&&... params) {
    (this->value())(std::forward<Args>(params)...);
  }
  bool operator==(std::nullptr_t) { return this->get() == nullptr; }
  template <typename T2>
  decltype(auto) operator==(T2* other) {
    return this->get() == other;
  }
  template <typename T2>
  decltype(auto) operator==(const joint_ptr<T2>& other) {
    return this->get() == other.get();
  }
  template <typename T2>
  decltype(auto) operator==(joint_ptr<T2>&& other) {
    return this->get() == other.get();
  }
  template <typename T2>
  bool operator!=(T2 other) {
    return !(operator==(other));
  }
  inline explicit operator bool() const noexcept {
    return this->get() != nullptr;
  }
  T& operator*() const { return this->value(); }
  T* operator->() const { return &(this->value()); };
};

template <typename T>
class stack_ptr : public std::optional<T> {
  using Parent = std::optional<T>;
  static_assert(!std::is_array<T>::value,
                "Error: stack_ptr not supported on raw arrays, they are not "
                "easily copyable.");

 public:
  template <typename... Args,
            typename = decltype(typename std::remove_all_extents<T>::type(
                std::declval<Args>()...))>
  stack_ptr(Args&&... params) : Parent(T(std::forward<Args>(params)...)) {}

  inline bool has_value() const { return Parent::has_value(); }
  inline T& value() const { return *(const_cast<T*>(&(Parent::value()))); }
  inline T* get() const { return Parent::has_value() ? &value() : nullptr; }
  void reset() { Parent::reset(); }
  void reset(std::nullptr_t) { Parent::reset(); }
  void reset(const T& v) { Parent::operator=(v); }
  void reset(T&& v) { Parent::operator=(v); }
  void reset(T* v) = delete;

  template <typename T2>
  void reset(const stack_ptr<T2>& other) {
    if (other.get() == nullptr) {
      Parent::reset();
      return;
    }
    Parent::operator=(other);
  }

  stack_ptr() { reset(nullptr); }
  stack_ptr(std::nullptr_t) { reset(nullptr); }
  stack_ptr(T* other) { reset(other); }
  stack_ptr(const stack_ptr& other) { reset(other); }
  template <typename T2>
  stack_ptr(stack_ptr<T2> other) {
    reset(other);
  }
  stack_ptr& operator=(std::nullptr_t) {
    reset(nullptr);
    return *this;
  }
  stack_ptr& operator=(T* other) {
    reset(other);
    return *this;
  }
  stack_ptr& operator=(const stack_ptr& other) {
    reset(other);
    return *this;
  }
  template <typename T2>
  stack_ptr& operator=(stack_ptr<T2> other) {
    reset(other);
    return *this;
  }
  stack_ptr(const T& other) { reset(other); }
  stack_ptr(T&& other) { reset(other); }
  stack_ptr& operator=(const T& other) {
    this->reset(other);
    return *this;
  }
  stack_ptr& operator=(T&& other) {
    this->reset(other);
    return *this;
  }

  decltype(auto) begin() { return this->value().begin(); }
  decltype(auto) begin() const { return this->value().begin(); }
  decltype(auto) end() { return this->value().end(); }
  decltype(auto) end() const { return this->value().end(); }
  template <typename T2>
  decltype(auto) operator[](T2 i) const {
    if constexpr (!std::is_array<T>::value) {
      return this->value()[i];
    } else {
      return (this->get())[i];
    }
  }
  template <typename T2>
  decltype(auto) operator+(const T2& other) {
    return this->value() + other;
  }
  template <typename T2>
  decltype(auto) operator+(T2&& other) {
    return this->value() + other;
  }
  template <typename T2>
  decltype(auto) operator+(const stack_ptr<T2>& other) {
    return this->value() + other.value();
  }
  template <typename T2>
  decltype(auto) operator+(stack_ptr<T2>&& other) {
    return this->value() + other.value();
  }
  template <typename T2>
  decltype(auto) operator-(const T2& other) {
    return this->value() - other;
  }
  template <typename T2>
  decltype(auto) operator-(T2&& other) {
    return this->value() - other;
  }
  template <typename T2>
  decltype(auto) operator-(const stack_ptr<T2>& other) {
    return this->value() - other.value();
  }
  template <typename T2>
  decltype(auto) operator-(stack_ptr<T2>&& other) {
    return this->value() - other.value();
  }
  template <typename T2>
  decltype(auto) operator*(const T2& other) {
    return this->value() * other;
  }
  template <typename T2>
  decltype(auto) operator*(T2&& other) {
    return this->value() * other;
  }
  template <typename T2>
  decltype(auto) operator*(const stack_ptr<T2>& other) {
    return this->value() * other.value();
  }
  template <typename T2>
  decltype(auto) operator*(stack_ptr<T2>&& other) {
    return this->value() * other.value();
  }
  template <typename T2>
  decltype(auto) operator/(const T2& other) {
    return this->value() / other;
  }
  template <typename T2>
  decltype(auto) operator/(T2&& other) {
    return this->value() / other;
  }
  template <typename T2>
  decltype(auto) operator/(const stack_ptr<T2>& other) {
    return this->value() / other.value();
  }
  template <typename T2>
  decltype(auto) operator/(stack_ptr<T2>&& other) {
    return this->value() / other.value();
  }
  template <typename T2>
  decltype(auto) operator%(const T2& other) {
    return this->value() % other;
  }
  template <typename T2>
  decltype(auto) operator%(T2&& other) {
    return this->value() % other;
  }
  template <typename T2>
  decltype(auto) operator%(const stack_ptr<T2>& other) {
    return this->value() % other.value();
  }
  template <typename T2>
  decltype(auto) operator%(stack_ptr<T2>&& other) {
    return this->value() % other.value();
  }
  template <typename T2>
  decltype(auto) operator^(const T2& other) {
    return this->value() ^ other;
  }
  template <typename T2>
  decltype(auto) operator^(T2&& other) {
    return this->value() ^ other;
  }
  template <typename T2>
  decltype(auto) operator^(const stack_ptr<T2>& other) {
    return this->value() ^ other.value();
  }
  template <typename T2>
  decltype(auto) operator^(stack_ptr<T2>&& other) {
    return this->value() ^ other.value();
  }
  template <typename T2>
  decltype(auto) operator&(const T2& other) {
    return this->value() & other;
  }
  template <typename T2>
  decltype(auto) operator&(T2&& other) {
    return this->value() & other;
  }
  template <typename T2>
  decltype(auto) operator&(const stack_ptr<T2>& other) {
    return this->value() & other.value();
  }
  template <typename T2>
  decltype(auto) operator&(stack_ptr<T2>&& other) {
    return this->value() & other.value();
  }
  template <typename T2>
  decltype(auto) operator|(const T2& other) {
    return this->value() | other;
  }
  template <typename T2>
  decltype(auto) operator|(T2&& other) {
    return this->value() | other;
  }
  template <typename T2>
  decltype(auto) operator|(const stack_ptr<T2>& other) {
    return this->value() | other.value();
  }
  template <typename T2>
  decltype(auto) operator|(stack_ptr<T2>&& other) {
    return this->value() | other.value();
  }
  template <typename T2>
  decltype(auto) operator<(const T2& other) {
    return this->value() < other;
  }
  template <typename T2>
  decltype(auto) operator<(T2&& other) {
    return this->value() < other;
  }
  template <typename T2>
  decltype(auto) operator<(const stack_ptr<T2>& other) {
    return this->value() < other.value();
  }
  template <typename T2>
  decltype(auto) operator<(stack_ptr<T2>&& other) {
    return this->value() < other.value();
  }
  template <typename T2>
  decltype(auto) operator>(const T2& other) {
    return this->value() > other;
  }
  template <typename T2>
  decltype(auto) operator>(T2&& other) {
    return this->value() > other;
  }
  template <typename T2>
  decltype(auto) operator>(const stack_ptr<T2>& other) {
    return this->value() > other.value();
  }
  template <typename T2>
  decltype(auto) operator>(stack_ptr<T2>&& other) {
    return this->value() > other.value();
  }
  template <typename T2>
  decltype(auto) operator+=(const T2& other) {
    return this->value() += other;
  }
  template <typename T2>
  decltype(auto) operator+=(T2&& other) {
    return this->value() += other;
  }
  template <typename T2>
  decltype(auto) operator+=(const stack_ptr<T2>& other) {
    return this->value() += other.value();
  }
  template <typename T2>
  decltype(auto) operator+=(stack_ptr<T2>&& other) {
    return this->value() += other.value();
  }
  template <typename T2>
  decltype(auto) operator-=(const T2& other) {
    return this->value() -= other;
  }
  template <typename T2>
  decltype(auto) operator-=(T2&& other) {
    return this->value() -= other;
  }
  template <typename T2>
  decltype(auto) operator-=(const stack_ptr<T2>& other) {
    return this->value() -= other.value();
  }
  template <typename T2>
  decltype(auto) operator-=(stack_ptr<T2>&& other) {
    return this->value() -= other.value();
  }
  template <typename T2>
  decltype(auto) operator*=(const T2& other) {
    return this->value() *= other;
  }
  template <typename T2>
  decltype(auto) operator*=(T2&& other) {
    return this->value() *= other;
  }
  template <typename T2>
  decltype(auto) operator*=(const stack_ptr<T2>& other) {
    return this->value() *= other.value();
  }
  template <typename T2>
  decltype(auto) operator*=(stack_ptr<T2>&& other) {
    return this->value() *= other.value();
  }
  template <typename T2>
  decltype(auto) operator/=(const T2& other) {
    return this->value() /= other;
  }
  template <typename T2>
  decltype(auto) operator/=(T2&& other) {
    return this->value() /= other;
  }
  template <typename T2>
  decltype(auto) operator/=(const stack_ptr<T2>& other) {
    return this->value() /= other.value();
  }
  template <typename T2>
  decltype(auto) operator/=(stack_ptr<T2>&& other) {
    return this->value() /= other.value();
  }
  template <typename T2>
  decltype(auto) operator%=(const T2& other) {
    return this->value() %= other;
  }
  template <typename T2>
  decltype(auto) operator%=(T2&& other) {
    return this->value() %= other;
  }
  template <typename T2>
  decltype(auto) operator%=(const stack_ptr<T2>& other) {
    return this->value() %= other.value();
  }
  template <typename T2>
  decltype(auto) operator%=(stack_ptr<T2>&& other) {
    return this->value() %= other.value();
  }
  template <typename T2>
  decltype(auto) operator^=(const T2& other) {
    return this->value() ^= other;
  }
  template <typename T2>
  decltype(auto) operator^=(T2&& other) {
    return this->value() ^= other;
  }
  template <typename T2>
  decltype(auto) operator^=(const stack_ptr<T2>& other) {
    return this->value() ^= other.value();
  }
  template <typename T2>
  decltype(auto) operator^=(stack_ptr<T2>&& other) {
    return this->value() ^= other.value();
  }
  template <typename T2>
  decltype(auto) operator&=(const T2& other) {
    return this->value() &= other;
  }
  template <typename T2>
  decltype(auto) operator&=(T2&& other) {
    return this->value() &= other;
  }
  template <typename T2>
  decltype(auto) operator&=(const stack_ptr<T2>& other) {
    return this->value() &= other.value();
  }
  template <typename T2>
  decltype(auto) operator&=(stack_ptr<T2>&& other) {
    return this->value() &= other.value();
  }
  template <typename T2>
  decltype(auto) operator|=(const T2& other) {
    return this->value() |= other;
  }
  template <typename T2>
  decltype(auto) operator|=(T2&& other) {
    return this->value() |= other;
  }
  template <typename T2>
  decltype(auto) operator|=(const stack_ptr<T2>& other) {
    return this->value() |= other.value();
  }
  template <typename T2>
  decltype(auto) operator|=(stack_ptr<T2>&& other) {
    return this->value() |= other.value();
  }
  template <typename T2>
  decltype(auto) operator<<(const T2& other) {
    return this->value() << other;
  }
  template <typename T2>
  decltype(auto) operator<<(T2&& other) {
    return this->value() << other;
  }
  template <typename T2>
  decltype(auto) operator<<(const stack_ptr<T2>& other) {
    return this->value() << other.value();
  }
  template <typename T2>
  decltype(auto) operator<<(stack_ptr<T2>&& other) {
    return this->value() << other.value();
  }
  template <typename T2>
  decltype(auto) operator>>(const T2& other) {
    return this->value() >> other;
  }
  template <typename T2>
  decltype(auto) operator>>(T2&& other) {
    return this->value() >> other;
  }
  template <typename T2>
  decltype(auto) operator>>(const stack_ptr<T2>& other) {
    return this->value() >> other.value();
  }
  template <typename T2>
  decltype(auto) operator>>(stack_ptr<T2>&& other) {
    return this->value() >> other.value();
  }
  template <typename T2>
  decltype(auto) operator<<=(const T2& other) {
    return this->value() <<= other;
  }
  template <typename T2>
  decltype(auto) operator<<=(T2&& other) {
    return this->value() <<= other;
  }
  template <typename T2>
  decltype(auto) operator<<=(const stack_ptr<T2>& other) {
    return this->value() <<= other.value();
  }
  template <typename T2>
  decltype(auto) operator<<=(stack_ptr<T2>&& other) {
    return this->value() <<= other.value();
  }
  template <typename T2>
  decltype(auto) operator>>=(const T2& other) {
    return this->value() >>= other;
  }
  template <typename T2>
  decltype(auto) operator>>=(T2&& other) {
    return this->value() >>= other;
  }
  template <typename T2>
  decltype(auto) operator>>=(const stack_ptr<T2>& other) {
    return this->value() >>= other.value();
  }
  template <typename T2>
  decltype(auto) operator>>=(stack_ptr<T2>&& other) {
    return this->value() >>= other.value();
  }
  template <typename T2>
  decltype(auto) operator<=(const T2& other) {
    return this->value() <= other;
  }
  template <typename T2>
  decltype(auto) operator<=(T2&& other) {
    return this->value() <= other;
  }
  template <typename T2>
  decltype(auto) operator<=(const stack_ptr<T2>& other) {
    return this->value() <= other.value();
  }
  template <typename T2>
  decltype(auto) operator<=(stack_ptr<T2>&& other) {
    return this->value() <= other.value();
  }
  template <typename T2>
  decltype(auto) operator>=(const T2& other) {
    return this->value() >= other;
  }
  template <typename T2>
  decltype(auto) operator>=(T2&& other) {
    return this->value() >= other;
  }
  template <typename T2>
  decltype(auto) operator>=(const stack_ptr<T2>& other) {
    return this->value() >= other.value();
  }
  template <typename T2>
  decltype(auto) operator>=(stack_ptr<T2>&& other) {
    return this->value() >= other.value();
  }
  template <typename T2>
  decltype(auto) operator&&(const T2& other) {
    return this->value() && other;
  }
  template <typename T2>
  decltype(auto) operator&&(T2&& other) {
    return this->value() && other;
  }
  template <typename T2>
  decltype(auto) operator&&(const stack_ptr<T2>& other) {
    return this->value() && other.value();
  }
  template <typename T2>
  decltype(auto) operator&&(stack_ptr<T2>&& other) {
    return this->value() && other.value();
  }
  template <typename T2>
  decltype(auto) operator||(const T2& other) {
    return this->value() || other;
  }
  template <typename T2>
  decltype(auto) operator||(T2&& other) {
    return this->value() || other;
  }
  template <typename T2>
  decltype(auto) operator||(const stack_ptr<T2>& other) {
    return this->value() || other.value();
  }
  template <typename T2>
  decltype(auto) operator||(stack_ptr<T2>&& other) {
    return this->value() || other.value();
  }
  template <typename T2>
  decltype(auto) operator~() {
    return ~this->value();
  }
  template <typename T2>
  decltype(auto) operator!() {
    return !this->value();
  }
  template <typename T2>
  decltype(auto) operator++() {
    return this->value()++;
  }
  template <typename T2>
  decltype(auto) operator--() {
    return this->value()--;
  }
  template <typename T2>
  decltype(auto) operator++(int) {
    return ++this->value();
  }
  template <typename T2>
  decltype(auto) operator--(int) {
    return --this->value();
  }
  template <typename T2>
  decltype(auto) operator,(const T2& other) {
    return (this->value()), other;
  }
  template <typename T2>
  decltype(auto) operator,(T2&& other) {
    return (this->value()), other;
  }
  template <typename... Args>
  decltype(auto) operator()(Args&&... params) {
    (this->value())(std::forward<Args>(params)...);
  }
  bool operator==(std::nullptr_t) { return this->get() == nullptr; }
  template <typename T2>
  decltype(auto) operator==(T2* other) {
    return this->get() == other;
  }
  template <typename T2>
  decltype(auto) operator==(const stack_ptr<T2>& other) {
    return this->get() == other.get();
  }
  template <typename T2>
  decltype(auto) operator==(stack_ptr<T2>&& other) {
    return this->get() == other.get();
  }
  template <typename T2>
  bool operator!=(T2 other) {
    return !(operator==(other));
  }
  inline explicit operator bool() const noexcept {
    return this->get() != nullptr;
  }
  T& operator*() const { return this->value(); }
  T* operator->() const { return &(this->value()); };
};

template <typename T>
class view_joint_ptr : public std::weak_ptr<T> {
  using Parent = std::weak_ptr<T>;

 public:
  using std::weak_ptr<T>::weak_ptr;
  joint_ptr<T> lock() const noexcept { return Parent::lock(); }
};

template <typename T>
class raw_ptr {
 private:
  T* data = nullptr;

 public:
  inline T* get() const noexcept { return data; }
  inline bool has_value() const { return this->get() != nullptr; }
  inline T& value() const {
    if (this->get() == nullptr)
      throw std::runtime_error("getting the value of nullptr");
    return *(this->get());
  }

  void reset() { data = nullptr; }
  void reset(std::nullptr_t) { reset(); }
  void reset(T* other) { data = other; }
  void reset(const T& other) = delete;

  void reset(T&& v) = delete;
  template <typename T2>
  void reset(const raw_ptr<T2>& other) {
    data = other.get();
  }

  raw_ptr() { reset(nullptr); }
  raw_ptr(std::nullptr_t) { reset(nullptr); }
  raw_ptr(T* other) { reset(other); }
  raw_ptr(const raw_ptr& other) { reset(other); }
  template <typename T2>
  raw_ptr(raw_ptr<T2> other) {
    reset(other);
  }
  raw_ptr& operator=(std::nullptr_t) {
    reset(nullptr);
    return *this;
  }
  raw_ptr& operator=(T* other) {
    reset(other);
    return *this;
  }
  raw_ptr& operator=(const raw_ptr& other) {
    reset(other);
    return *this;
  }
  template <typename T2>
  raw_ptr& operator=(raw_ptr<T2> other) {
    reset(other);
    return *this;
  }
  raw_ptr(const T& other) { reset(other); }
  raw_ptr(T&& other) { reset(other); }
  raw_ptr& operator=(const T& other) {
    this->reset(other);
    return *this;
  }
  raw_ptr& operator=(T&& other) {
    this->reset(other);
    return *this;
  }

  decltype(auto) begin() { return this->value().begin(); }
  decltype(auto) begin() const { return this->value().begin(); }
  decltype(auto) end() { return this->value().end(); }
  decltype(auto) end() const { return this->value().end(); }
  template <typename T2>
  decltype(auto) operator[](T2 i) const {
    if constexpr (!std::is_array<T>::value) {
      return this->value()[i];
    } else {
      return (this->get())[i];
    }
  }
  template <typename T2>
  decltype(auto) operator+(const T2& other) {
    return this->value() + other;
  }
  template <typename T2>
  decltype(auto) operator+(T2&& other) {
    return this->value() + other;
  }
  template <typename T2>
  decltype(auto) operator+(const raw_ptr<T2>& other) {
    return this->value() + other.value();
  }
  template <typename T2>
  decltype(auto) operator+(raw_ptr<T2>&& other) {
    return this->value() + other.value();
  }
  template <typename T2>
  decltype(auto) operator-(const T2& other) {
    return this->value() - other;
  }
  template <typename T2>
  decltype(auto) operator-(T2&& other) {
    return this->value() - other;
  }
  template <typename T2>
  decltype(auto) operator-(const raw_ptr<T2>& other) {
    return this->value() - other.value();
  }
  template <typename T2>
  decltype(auto) operator-(raw_ptr<T2>&& other) {
    return this->value() - other.value();
  }
  template <typename T2>
  decltype(auto) operator*(const T2& other) {
    return this->value() * other;
  }
  template <typename T2>
  decltype(auto) operator*(T2&& other) {
    return this->value() * other;
  }
  template <typename T2>
  decltype(auto) operator*(const raw_ptr<T2>& other) {
    return this->value() * other.value();
  }
  template <typename T2>
  decltype(auto) operator*(raw_ptr<T2>&& other) {
    return this->value() * other.value();
  }
  template <typename T2>
  decltype(auto) operator/(const T2& other) {
    return this->value() / other;
  }
  template <typename T2>
  decltype(auto) operator/(T2&& other) {
    return this->value() / other;
  }
  template <typename T2>
  decltype(auto) operator/(const raw_ptr<T2>& other) {
    return this->value() / other.value();
  }
  template <typename T2>
  decltype(auto) operator/(raw_ptr<T2>&& other) {
    return this->value() / other.value();
  }
  template <typename T2>
  decltype(auto) operator%(const T2& other) {
    return this->value() % other;
  }
  template <typename T2>
  decltype(auto) operator%(T2&& other) {
    return this->value() % other;
  }
  template <typename T2>
  decltype(auto) operator%(const raw_ptr<T2>& other) {
    return this->value() % other.value();
  }
  template <typename T2>
  decltype(auto) operator%(raw_ptr<T2>&& other) {
    return this->value() % other.value();
  }
  template <typename T2>
  decltype(auto) operator^(const T2& other) {
    return this->value() ^ other;
  }
  template <typename T2>
  decltype(auto) operator^(T2&& other) {
    return this->value() ^ other;
  }
  template <typename T2>
  decltype(auto) operator^(const raw_ptr<T2>& other) {
    return this->value() ^ other.value();
  }
  template <typename T2>
  decltype(auto) operator^(raw_ptr<T2>&& other) {
    return this->value() ^ other.value();
  }
  template <typename T2>
  decltype(auto) operator&(const T2& other) {
    return this->value() & other;
  }
  template <typename T2>
  decltype(auto) operator&(T2&& other) {
    return this->value() & other;
  }
  template <typename T2>
  decltype(auto) operator&(const raw_ptr<T2>& other) {
    return this->value() & other.value();
  }
  template <typename T2>
  decltype(auto) operator&(raw_ptr<T2>&& other) {
    return this->value() & other.value();
  }
  template <typename T2>
  decltype(auto) operator|(const T2& other) {
    return this->value() | other;
  }
  template <typename T2>
  decltype(auto) operator|(T2&& other) {
    return this->value() | other;
  }
  template <typename T2>
  decltype(auto) operator|(const raw_ptr<T2>& other) {
    return this->value() | other.value();
  }
  template <typename T2>
  decltype(auto) operator|(raw_ptr<T2>&& other) {
    return this->value() | other.value();
  }
  template <typename T2>
  decltype(auto) operator<(const T2& other) {
    return this->value() < other;
  }
  template <typename T2>
  decltype(auto) operator<(T2&& other) {
    return this->value() < other;
  }
  template <typename T2>
  decltype(auto) operator<(const raw_ptr<T2>& other) {
    return this->value() < other.value();
  }
  template <typename T2>
  decltype(auto) operator<(raw_ptr<T2>&& other) {
    return this->value() < other.value();
  }
  template <typename T2>
  decltype(auto) operator>(const T2& other) {
    return this->value() > other;
  }
  template <typename T2>
  decltype(auto) operator>(T2&& other) {
    return this->value() > other;
  }
  template <typename T2>
  decltype(auto) operator>(const raw_ptr<T2>& other) {
    return this->value() > other.value();
  }
  template <typename T2>
  decltype(auto) operator>(raw_ptr<T2>&& other) {
    return this->value() > other.value();
  }
  template <typename T2>
  decltype(auto) operator+=(const T2& other) {
    return this->value() += other;
  }
  template <typename T2>
  decltype(auto) operator+=(T2&& other) {
    return this->value() += other;
  }
  template <typename T2>
  decltype(auto) operator+=(const raw_ptr<T2>& other) {
    return this->value() += other.value();
  }
  template <typename T2>
  decltype(auto) operator+=(raw_ptr<T2>&& other) {
    return this->value() += other.value();
  }
  template <typename T2>
  decltype(auto) operator-=(const T2& other) {
    return this->value() -= other;
  }
  template <typename T2>
  decltype(auto) operator-=(T2&& other) {
    return this->value() -= other;
  }
  template <typename T2>
  decltype(auto) operator-=(const raw_ptr<T2>& other) {
    return this->value() -= other.value();
  }
  template <typename T2>
  decltype(auto) operator-=(raw_ptr<T2>&& other) {
    return this->value() -= other.value();
  }
  template <typename T2>
  decltype(auto) operator*=(const T2& other) {
    return this->value() *= other;
  }
  template <typename T2>
  decltype(auto) operator*=(T2&& other) {
    return this->value() *= other;
  }
  template <typename T2>
  decltype(auto) operator*=(const raw_ptr<T2>& other) {
    return this->value() *= other.value();
  }
  template <typename T2>
  decltype(auto) operator*=(raw_ptr<T2>&& other) {
    return this->value() *= other.value();
  }
  template <typename T2>
  decltype(auto) operator/=(const T2& other) {
    return this->value() /= other;
  }
  template <typename T2>
  decltype(auto) operator/=(T2&& other) {
    return this->value() /= other;
  }
  template <typename T2>
  decltype(auto) operator/=(const raw_ptr<T2>& other) {
    return this->value() /= other.value();
  }
  template <typename T2>
  decltype(auto) operator/=(raw_ptr<T2>&& other) {
    return this->value() /= other.value();
  }
  template <typename T2>
  decltype(auto) operator%=(const T2& other) {
    return this->value() %= other;
  }
  template <typename T2>
  decltype(auto) operator%=(T2&& other) {
    return this->value() %= other;
  }
  template <typename T2>
  decltype(auto) operator%=(const raw_ptr<T2>& other) {
    return this->value() %= other.value();
  }
  template <typename T2>
  decltype(auto) operator%=(raw_ptr<T2>&& other) {
    return this->value() %= other.value();
  }
  template <typename T2>
  decltype(auto) operator^=(const T2& other) {
    return this->value() ^= other;
  }
  template <typename T2>
  decltype(auto) operator^=(T2&& other) {
    return this->value() ^= other;
  }
  template <typename T2>
  decltype(auto) operator^=(const raw_ptr<T2>& other) {
    return this->value() ^= other.value();
  }
  template <typename T2>
  decltype(auto) operator^=(raw_ptr<T2>&& other) {
    return this->value() ^= other.value();
  }
  template <typename T2>
  decltype(auto) operator&=(const T2& other) {
    return this->value() &= other;
  }
  template <typename T2>
  decltype(auto) operator&=(T2&& other) {
    return this->value() &= other;
  }
  template <typename T2>
  decltype(auto) operator&=(const raw_ptr<T2>& other) {
    return this->value() &= other.value();
  }
  template <typename T2>
  decltype(auto) operator&=(raw_ptr<T2>&& other) {
    return this->value() &= other.value();
  }
  template <typename T2>
  decltype(auto) operator|=(const T2& other) {
    return this->value() |= other;
  }
  template <typename T2>
  decltype(auto) operator|=(T2&& other) {
    return this->value() |= other;
  }
  template <typename T2>
  decltype(auto) operator|=(const raw_ptr<T2>& other) {
    return this->value() |= other.value();
  }
  template <typename T2>
  decltype(auto) operator|=(raw_ptr<T2>&& other) {
    return this->value() |= other.value();
  }
  template <typename T2>
  decltype(auto) operator<<(const T2& other) {
    return this->value() << other;
  }
  template <typename T2>
  decltype(auto) operator<<(T2&& other) {
    return this->value() << other;
  }
  template <typename T2>
  decltype(auto) operator<<(const raw_ptr<T2>& other) {
    return this->value() << other.value();
  }
  template <typename T2>
  decltype(auto) operator<<(raw_ptr<T2>&& other) {
    return this->value() << other.value();
  }
  template <typename T2>
  decltype(auto) operator>>(const T2& other) {
    return this->value() >> other;
  }
  template <typename T2>
  decltype(auto) operator>>(T2&& other) {
    return this->value() >> other;
  }
  template <typename T2>
  decltype(auto) operator>>(const raw_ptr<T2>& other) {
    return this->value() >> other.value();
  }
  template <typename T2>
  decltype(auto) operator>>(raw_ptr<T2>&& other) {
    return this->value() >> other.value();
  }
  template <typename T2>
  decltype(auto) operator<<=(const T2& other) {
    return this->value() <<= other;
  }
  template <typename T2>
  decltype(auto) operator<<=(T2&& other) {
    return this->value() <<= other;
  }
  template <typename T2>
  decltype(auto) operator<<=(const raw_ptr<T2>& other) {
    return this->value() <<= other.value();
  }
  template <typename T2>
  decltype(auto) operator<<=(raw_ptr<T2>&& other) {
    return this->value() <<= other.value();
  }
  template <typename T2>
  decltype(auto) operator>>=(const T2& other) {
    return this->value() >>= other;
  }
  template <typename T2>
  decltype(auto) operator>>=(T2&& other) {
    return this->value() >>= other;
  }
  template <typename T2>
  decltype(auto) operator>>=(const raw_ptr<T2>& other) {
    return this->value() >>= other.value();
  }
  template <typename T2>
  decltype(auto) operator>>=(raw_ptr<T2>&& other) {
    return this->value() >>= other.value();
  }
  template <typename T2>
  decltype(auto) operator<=(const T2& other) {
    return this->value() <= other;
  }
  template <typename T2>
  decltype(auto) operator<=(T2&& other) {
    return this->value() <= other;
  }
  template <typename T2>
  decltype(auto) operator<=(const raw_ptr<T2>& other) {
    return this->value() <= other.value();
  }
  template <typename T2>
  decltype(auto) operator<=(raw_ptr<T2>&& other) {
    return this->value() <= other.value();
  }
  template <typename T2>
  decltype(auto) operator>=(const T2& other) {
    return this->value() >= other;
  }
  template <typename T2>
  decltype(auto) operator>=(T2&& other) {
    return this->value() >= other;
  }
  template <typename T2>
  decltype(auto) operator>=(const raw_ptr<T2>& other) {
    return this->value() >= other.value();
  }
  template <typename T2>
  decltype(auto) operator>=(raw_ptr<T2>&& other) {
    return this->value() >= other.value();
  }
  template <typename T2>
  decltype(auto) operator&&(const T2& other) {
    return this->value() && other;
  }
  template <typename T2>
  decltype(auto) operator&&(T2&& other) {
    return this->value() && other;
  }
  template <typename T2>
  decltype(auto) operator&&(const raw_ptr<T2>& other) {
    return this->value() && other.value();
  }
  template <typename T2>
  decltype(auto) operator&&(raw_ptr<T2>&& other) {
    return this->value() && other.value();
  }
  template <typename T2>
  decltype(auto) operator||(const T2& other) {
    return this->value() || other;
  }
  template <typename T2>
  decltype(auto) operator||(T2&& other) {
    return this->value() || other;
  }
  template <typename T2>
  decltype(auto) operator||(const raw_ptr<T2>& other) {
    return this->value() || other.value();
  }
  template <typename T2>
  decltype(auto) operator||(raw_ptr<T2>&& other) {
    return this->value() || other.value();
  }
  template <typename T2>
  decltype(auto) operator~() {
    return ~this->value();
  }
  template <typename T2>
  decltype(auto) operator!() {
    return !this->value();
  }
  template <typename T2>
  decltype(auto) operator++() {
    return this->value()++;
  }
  template <typename T2>
  decltype(auto) operator--() {
    return this->value()--;
  }
  template <typename T2>
  decltype(auto) operator++(int) {
    return ++this->value();
  }
  template <typename T2>
  decltype(auto) operator--(int) {
    return --this->value();
  }
  template <typename T2>
  decltype(auto) operator,(const T2& other) {
    return (this->value()), other;
  }
  template <typename T2>
  decltype(auto) operator,(T2&& other) {
    return (this->value()), other;
  }
  template <typename... Args>
  decltype(auto) operator()(Args&&... params) {
    (this->value())(std::forward<Args>(params)...);
  }
  bool operator==(std::nullptr_t) { return this->get() == nullptr; }
  template <typename T2>
  decltype(auto) operator==(T2* other) {
    return this->get() == other;
  }
  template <typename T2>
  decltype(auto) operator==(const raw_ptr<T2>& other) {
    return this->get() == other.get();
  }
  template <typename T2>
  decltype(auto) operator==(raw_ptr<T2>&& other) {
    return this->get() == other.get();
  }
  template <typename T2>
  bool operator!=(T2 other) {
    return !(operator==(other));
  }
  inline explicit operator bool() const noexcept {
    return this->get() != nullptr;
  }
  T& operator*() const { return this->value(); }
  T* operator->() const { return &(this->value()); };
};

namespace shortnames {
template <typename T>
using cptr = clone_ptr<T>;
template <typename T>
using jptr = joint_ptr<T>;
template <typename T>
using sptr = stack_ptr<T>;
template <typename T>
using vjptr = view_joint_ptr<T>;
template <typename T>
using rptr = raw_ptr<T>;
};  // namespace shortnames
};  // namespace estd
