// BSD 3-Clause License

// Copyright (c) 2022, Alex Tarasov
// All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:

// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.

// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.

// 3. Neither the name of the copyright holder nor the names of its
//    contributors may be used to endorse or promote products derived from
//    this software without specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#pragma once
#include <memory>


template <class... Ts>
struct overloaded : Ts... {
	using Ts::operator()...;
};
// explicit deduction guide (not needed as of C++20)
template <class... Ts>
overloaded(Ts...) -> overloaded<Ts...>;

#define ESTD_PRIVATE_DO_NOT_USE_HAS_METHOD(class_type, method)                                                         \
	overloaded{[](auto* arg, decltype(&std::decay_t<decltype(*arg)>::method) ptr) constexpr {return true;              \
	}                                                                                                                  \
	, [](auto* arg, ...) constexpr { return false; }                                                                   \
	}                                                                                                                  \
	((class_type*)nullptr, nullptr)



namespace estd {
	class clonable {
        public:
		virtual clonable* clone() const = 0;
	};

	// Literally the same as a unique pointer, but you can copy it and it makes
	// two copies of the object, value like behavior.
	template <typename T>
	class clone_ptr : public std::unique_ptr<T> {
		using Parent = std::unique_ptr<T>;

	public:
		using std::unique_ptr<T>::unique_ptr;

		clone_ptr() {}

		clone_ptr(const T& other) {
			if constexpr (std::is_base_of<clonable, T>::value) {
				this->reset((T*)other.clone());
			} else {
				this->reset(new T(other));
			}
		}

		clone_ptr(T&& other) {
			if constexpr (std::is_base_of<clonable, T>::value) {
				this->reset((T*)other.clone());
			} else {
				this->reset(new T(other));
			}
		}

		clone_ptr(const clone_ptr& other) {
			if constexpr (std::is_base_of<clonable, T>::value) {
				this->reset((T*)other->clone());
			} else {
				this->reset(new T(*other));
			}
		}

		clone_ptr(clone_ptr&& other) {
			if constexpr (std::is_base_of<clonable, T>::value) {
				this->reset((T*)other->clone());
			} else {
				this->reset(new T(*other));
			}
		}

		template <typename... Args, typename = decltype(T(std::declval<Args>()...))>
		clone_ptr(Args&&... params) : Parent(new T(std::forward<Args>(params)...)) {}


		clone_ptr& operator=(const clone_ptr& other) noexcept {
			if constexpr (std::is_base_of<clonable, T>::value) {
				this->reset((T*)other->clone());
			} else {
				// static_assert(!std::is_abstract<T>::value, "Abstract types must implement the clone() method");
				this->reset(new T(*other));
			}
			return *this;
		}

		clone_ptr& operator=(clone_ptr&& other) noexcept {
			if constexpr (std::is_base_of<clonable, T>::value) {
				this->reset((T*)other->clone());
			} else {
				// static_assert(!std::is_abstract<T>::value, "Abstract types must implement the clone() method");
				this->reset(new T(*other));
			}
			return *this;
		}

		clone_ptr& operator=(const T& other) noexcept {
			if constexpr (std::is_base_of<clonable, T>::value) {
				this->reset((T*)other.clone());
			} else {
				this->reset(new T(other));
			}
			return *this;
		}

		clone_ptr& operator=(T&& other) noexcept {
			if constexpr (std::is_base_of<clonable, T>::value) {
				this->reset((T*)other.clone());
			} else {
				this->reset(new T(other));
			}
			return *this;
		}

		clone_ptr& operator=(const T* other) noexcept {
			if constexpr (std::is_base_of<clonable, T>::value) {
				this->reset((T*)other->clone());
			} else {
				this->reset(new T(*other));
			}
			return *this;
		}
	};
};// namespace estd


// #undef ESTD_PRIVATE_DO_NOT_USE_HAS_METHOD
