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

#include <estd/clone_ptr.hpp>
#include <iostream>

struct ExampleType {
	int x;
	int y;
	int z;
	ExampleType(int x,  int y, int z): x(x), y(y), z(z) {}
	void print(){
		std::cout << "(" << x << ","<< y << ","<< z  << ")\n";
	}
};

struct ExampleTypeClonable: public estd::clonable {
	int x;
	int y;
	int z;
	ExampleTypeClonable(int x,  int y, int z): x(x), y(y), z(z) {}
	void print(){
		std::cout << "(" << x << ","<< y << ","<< z  << ")\n";
	}
	
	clonable* clone() const{
		std::cout << "ran clone\n";
		return new ExampleTypeClonable(x,y,z);
	}
};

int main() {
	estd::clone_ptr<int> i(1);
	estd::clone_ptr<int> j(2);
	estd::clone_ptr<ExampleType> tst(1,2,3);
	estd::clone_ptr<ExampleType> tst2(tst);

	std::cout << *i << std::endl;
	std::cout << *j << std::endl;
	std::cout << std::endl;

	j = i;

	std::cout << *i << std::endl;
	std::cout << *j << std::endl;
	std::cout << std::endl;

	*j = 2;

	std::cout << *i << std::endl;
	std::cout << *j << std::endl;
	std::cout << std::endl;

	tst2->x = 9;

	tst->print();
	tst2->print();

	return 0;
}


//if constexpr (ESTD_PRIVATE_DO_NOT_USE_HAS_METHOD(T, clone)) {
//std::is_base_of<A, B>::value
