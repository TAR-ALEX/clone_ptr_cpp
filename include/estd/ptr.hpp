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
#include <type_traits>

#define DEFINE_BIN_OP(OPT)                                                                                             \
	template <typename T2>                                                                                             \
	decltype(auto) operator OPT(const T2& other) {                                                                     \
		return (*(this->get()))OPT other;                                                                              \
	}                                                                                                                  \
	template <typename T2>                                                                                             \
	decltype(auto) operator OPT(T2&& other) {                                                                          \
		return (*(this->get()))OPT other;                                                                              \
	}                                                                                                                  \
	template <typename T2>                                                                                             \
	decltype(auto) operator OPT(const clone_ptr<T2>& other) {                                                          \
		return (*(this->get()))OPT(*(other.get()));                                                                    \
	}                                                                                                                  \
	template <typename T2>                                                                                             \
	decltype(auto) operator OPT(clone_ptr<T2>&& other) {                                                               \
		return (*(this->get()))OPT(*(other.get()));                                                                    \
	}


#define DEFINE_PRE_OP(OPT)                                                                                             \
	template <typename T2>                                                                                             \
	decltype(auto) operator OPT(int) {                                                                                 \
		return OPT(*(this->get()));                                                                                    \
	}

#define DEFINE_POST_OP(OPT)                                                                                            \
	template <typename T2>                                                                                             \
	decltype(auto) operator OPT() {                                                                                    \
		return (*(this->get()))OPT;                                                                                    \
	}

#define DEFINE_UNARY_OP(OPT)                                                                                           \
	template <typename T2>                                                                                             \
	decltype(auto) operator OPT() {                                                                                    \
		return OPT(*(this->get()));                                                                                    \
	}


namespace estd {
	class clonable {
	public:
		virtual clonable* clone() const = 0;
		virtual ~clonable() = default;
	};

	// Literally the same as a unique pointer, but you can copy it and it makes
	// two copies of the object, value like behavior.
	template <typename T>
	class clone_ptr : public std::unique_ptr<T> {
		using Parent = std::unique_ptr<T>;

	public:
		using std::unique_ptr<T>::unique_ptr;
		using std::unique_ptr<T>::operator*;

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

		template <typename T2>
		clone_ptr(const clone_ptr<T2>& other) {
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

		template <typename T2>
		clone_ptr(clone_ptr<T2>&& other) {
			if constexpr (std::is_base_of<clonable, T>::value) {
				this->reset((T*)other->clone());
			} else {
				this->reset(new T(*other));
			}
		}

		clone_ptr(T* other) { this->reset(other); }

		clone_ptr& operator=(const clone_ptr& other) noexcept {
			if constexpr (std::is_base_of<clonable, T>::value) {
				this->reset((T*)other->clone());
			} else {
				this->reset(new T(*other));
			}
			return *this;
		}

		template <typename T2>
		clone_ptr& operator=(const clone_ptr<T2>& other) noexcept {
			if constexpr (std::is_base_of<clonable, T>::value) {
				this->reset((T*)other->clone());
			} else {
				this->reset(new T(*other));
			}
			return *this;
		}

		clone_ptr& operator=(clone_ptr&& other) noexcept {
			if constexpr (std::is_base_of<clonable, T>::value) {
				this->reset((T*)other->clone());
			} else {
				this->reset(new T(*other));
			}
			return *this;
		}

		template <typename T2>
		clone_ptr& operator=(clone_ptr<T2>&& other) noexcept {
			if constexpr (std::is_base_of<clonable, T>::value) {
				this->reset((T*)other->clone());
			} else {
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

		clone_ptr& operator=(T* other) noexcept {
			this->reset(other);
			return *this;
		}

		template <typename... Args, typename = decltype(T(std::declval<Args>()...))>
		clone_ptr(Args&&... params) : Parent(new T(std::forward<Args>(params)...)) {}

		/////////ITERATOR FORWARDING/////////

		decltype(auto) begin() { return this->get()->begin(); }
		decltype(auto) begin() const { this->get()->begin(); }
		decltype(auto) end() { return this->get()->end(); }
		decltype(auto) end() const { return this->get()->end(); }

		/////////OPERATOR FORWARDING/////////

		template <typename T2>
		decltype(auto) operator[](T2 i) const {
			if constexpr (!std::is_array<T>::value) {
				return (*this->get())[i];
			} else {
				return (this->get())[i];
			}
		}

		DEFINE_BIN_OP(+)
		DEFINE_BIN_OP(-)
		DEFINE_BIN_OP(*)
		DEFINE_BIN_OP(/)
		DEFINE_BIN_OP(%)
		DEFINE_BIN_OP(^)
		DEFINE_BIN_OP(&)
		DEFINE_BIN_OP(|)
		DEFINE_BIN_OP(<)
		DEFINE_BIN_OP(>)

		DEFINE_BIN_OP(+=)
		DEFINE_BIN_OP(-=)
		DEFINE_BIN_OP(*=)
		DEFINE_BIN_OP(/=)
		DEFINE_BIN_OP(%=)
		DEFINE_BIN_OP(^=)
		DEFINE_BIN_OP(&=)
		DEFINE_BIN_OP(|=)

		DEFINE_BIN_OP(<<)
		DEFINE_BIN_OP(>>)
		DEFINE_BIN_OP(<<=)
		DEFINE_BIN_OP(>>=)

		DEFINE_BIN_OP(==)
		DEFINE_BIN_OP(!=)

		DEFINE_BIN_OP(<=)
		DEFINE_BIN_OP(>=)

		DEFINE_BIN_OP(&&)
		DEFINE_BIN_OP(||)

		DEFINE_UNARY_OP(~)
		DEFINE_UNARY_OP(!)

		DEFINE_POST_OP(++)
		DEFINE_POST_OP(--)

		DEFINE_PRE_OP(++)
		DEFINE_PRE_OP(--)

		template <typename T2>
		decltype(auto) operator,(const T2& other) {
			return (*(this->get())), other;
		}

		template <typename T2>
		decltype(auto) operator,(T2&& other) {
			return (*(this->get())), other;
		}

		template <typename... Args>
		decltype(auto) operator()(Args&&... params) {
			(*(this->get()))(std::forward<Args>(params)...);
		}

		bool operator==(std::nullptr_t) { return this->get() == nullptr; }
		bool operator!=(std::nullptr_t) { return this->get() != nullptr; }

#if __cplusplus >= 202002L
		DEFINE_BIN_OP(<=>)
#endif
	};


	// Literally the same as a shared pointer, but it forwards operators and has a forwarding constructor
	template <typename T>
	class joint_ptr : public std::shared_ptr<T> {
		using Parent = std::shared_ptr<T>;

	public:
		using std::shared_ptr<T>::shared_ptr;
		using std::shared_ptr<T>::operator*;

		template <typename... Args, typename = decltype(T(std::declval<Args>()...))>
		joint_ptr(Args&&... params) : Parent(new T(std::forward<Args>(params)...)) {}

		/////////ITERATOR FORWARDING/////////

		decltype(auto) begin() { return this->get()->begin(); }
		decltype(auto) begin() const { this->get()->begin(); }
		decltype(auto) end() { return this->get()->end(); }
		decltype(auto) end() const { return this->get()->end(); }

		/////////OPERATOR FORWARDING/////////

		template <typename T2>
		decltype(auto) operator[](T2 i) const {
			if constexpr (!std::is_array<T>::value) {
				return (*this->get())[i];
			} else {
				return (this->get())[i];
			}
		}

		DEFINE_BIN_OP(+)
		DEFINE_BIN_OP(-)
		DEFINE_BIN_OP(*)
		DEFINE_BIN_OP(/)
		DEFINE_BIN_OP(%)
		DEFINE_BIN_OP(^)
		DEFINE_BIN_OP(&)
		DEFINE_BIN_OP(|)
		DEFINE_BIN_OP(<)
		DEFINE_BIN_OP(>)

		DEFINE_BIN_OP(+=)
		DEFINE_BIN_OP(-=)
		DEFINE_BIN_OP(*=)
		DEFINE_BIN_OP(/=)
		DEFINE_BIN_OP(%=)
		DEFINE_BIN_OP(^=)
		DEFINE_BIN_OP(&=)
		DEFINE_BIN_OP(|=)

		DEFINE_BIN_OP(<<)
		DEFINE_BIN_OP(>>)
		DEFINE_BIN_OP(<<=)
		DEFINE_BIN_OP(>>=)

		DEFINE_BIN_OP(==)
		DEFINE_BIN_OP(!=)

		DEFINE_BIN_OP(<=)
		DEFINE_BIN_OP(>=)

		DEFINE_BIN_OP(&&)
		DEFINE_BIN_OP(||)

		DEFINE_UNARY_OP(~)
		DEFINE_UNARY_OP(!)

		DEFINE_POST_OP(++)
		DEFINE_POST_OP(--)

		DEFINE_PRE_OP(++)
		DEFINE_PRE_OP(--)

		template <typename T2>
		decltype(auto) operator,(const T2& other) {
			return (*(this->get())), other;
		}

		template <typename T2>
		decltype(auto) operator,(T2&& other) {
			return (*(this->get())), other;
		}

		template <typename... Args>
		decltype(auto) operator()(Args&&... params) {
			(*(this->get()))(std::forward<Args>(params)...);
		}

		bool operator==(std::nullptr_t) { return this->get() == nullptr; }
		bool operator!=(std::nullptr_t) { return this->get() != nullptr; }

#if __cplusplus >= 202002L
		DEFINE_BIN_OP(<=>)
#endif
	};


};// namespace estd

#undef DEFINE_PRE_OP
#undef DEFINE_POST_OP
#undef DEFINE_UNARY_OP
#undef DEFINE_BIN_OP