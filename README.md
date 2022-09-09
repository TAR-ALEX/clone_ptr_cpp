# clone_ptr_cpp
This is the estd smart pointer library.
This library contains 5 pointer types:

### estd::clone_ptr (estd::shortnames::cptr)
This pointer is useful for polymorphism. Such as having a vector made of interfaces. The biggest advantage is that it is copyable. Using this class will not implicitly delete any copy constructors and such.
The behavior of this pointer is value like.
When copying, assigning by value, or constructing by value (lvalues or rvalues), the pointer will construct new objects that are copies and manage the new object.
This pointer is based on std::unique_ptr, but has operator forwarding and is copyable.
The only time the pointer does not allocate its own memory that it manages is when reset, the constructor, or the assignment operator are called by passing a pointer to the underlying type. In this case the pointer will manage the address provided to it.
In addition this pointer has these functions has_value() and value().
This pointer will throw if accessing its value while it is not initialized or pointing to nullptr

### estd::joint_ptr (estd::shortnames::jptr)
This pointer is based on std::shared_ptr, and has operator forwarding.
In addition this pointer has these functions has_value() and value().
This pointer will throw if accessing its value while it is not initialized or pointing to nullptr

### estd::stack_ptr (estd::shortnames::sptr)
This pointer is not actually a pointer but from a usage perspective behaves like one.
This pointer is based on std::optional, and has operator forwarding.
In addition this pointer has these functions get() to retrieve the pointers address (location on the stack).
This pointer will throw if accessing its value while it is not initialized or pointing to nullptr

### estd::view_joint_ptr (estd::shortnames::vjptr)
This pointer is based on std::weak_ptr, and has operator forwarding.
In addition this pointer has these functions has_value() and value().
This pointer will throw if accessing its value while it is not initialized or pointing to nullptr
It provides a view on the joint_ptr without incrementing the reference count.
contains the expired() and lock() methods to view this memory.

### estd::raw_ptr (estd::shortnames::rptr)
This pointer is not based on any std smart pointer, but is a simple wraper around a regular pointer. 
It does no memory managment.
Why would you want to use this? For operator forwarding features (will not do pointer arithmetic, but will forward the operators)

## Other notes

NONE of these should work with C style arrays, they will work with c++ std::array instead.

There is a version that contains no macros in the `nomacros` directory. To build this version you must have clang-format installed and run on a unix with utilities such as grep. run `make nomacros` to update this library

## Building and usage

The makefile will build and run the main file. (modify the main file to try out the library)


To use this project with a dependency manager install the cpp-dependency-manager project from https://github.com/TAR-ALEX/Cpp-Dependency-Manager.git

and create a vendor.txt file and add the following entries:

```
git "https://github.com/TAR-ALEX/clone_ptr_cpp.git" master "./include" "./vendor/include",

```

There is also a version that contains no macros, to use this version:

```
git "https://github.com/TAR-ALEX/clone_ptr_cpp.git" master "./nomacros/include" "./vendor/include",

```