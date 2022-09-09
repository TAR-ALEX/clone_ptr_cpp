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

// #include "../nomacros/include/estd/ptr.hpp"
#include <estd/ptr.hpp>
#include <iostream>
#include <vector>

using namespace estd::shortnames;

struct TypeX : public estd::clonable {
	virtual void print() = 0;
};

struct TypeA : public TypeX {
	int x;
	int y;
	int z;

	TypeA(int x, int y, int z) : x(x), y(y), z(z) { std::cerr << "ran construct\n"; }
	virtual void print() { std::cout << "TypeA(" << x << "," << y << "," << z << ")\n"; }
	virtual ~TypeA() { std::cerr << "ran destruct\n"; }

	clonable* clone() const {
		std::cout << "ran clone\n";
		return new TypeA(x, y, z);
	}
};

struct TypeB : public TypeA {
	TypeB(int x, int y, int z) : TypeA(x, y, z) {}
	virtual void print() { std::cout << "TypeB(" << x << "," << y << "," << z << ")\n"; }

	clonable* clone() const {
		std::cout << "ran clone\n";
		return new TypeB(x, y, z);
	}
};

int main() {
    sptr<int> it = 1;
    it += 1;
    std::cout << (*it) << std::endl;

	estd::clone_ptr<std::vector<estd::clone_ptr<TypeX>>> arra = new std::vector<estd::clone_ptr<TypeX>>();
	arra->resize(6);

	arra[0] = new TypeA(1, 2, 3);
	arra[1] = new TypeB(4, 5, 6);
	arra[2] = new TypeA(7, 8, 9);
	arra[3] = new TypeB(10, 11, 12);
	arra[4] = arra[1];
	arra[4] = arra[0];
	arra[5] = arra[1];

	for (auto& e : arra) { e->print(); }

	estd::joint_ptr<int> i = 0;
	estd::joint_ptr<int> j = i;
	estd::joint_ptr<int> k;

    estd::view_joint_ptr<int> vjp = i;

	i += 4;
	std::cout << (*j) << std::endl;

	std::cout << (vjp.lock() == nullptr) << std::endl;
	std::cout << (j == nullptr) << std::endl;
	std::cout << (k == nullptr) << std::endl<< std::endl;

	estd::clone_ptr<std::array<int, 2>> arr({1,2});
	arr[0] = 7;
	arr[1] = 8;

	std::cout << arr[0] << std::endl;
	std::cout << arr[1] << std::endl;

	return 0;
}
