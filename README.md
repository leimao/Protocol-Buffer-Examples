# Protocol Buffer Examples

Lei Mao

## Introduction

Protocol Buffer, also known as Protobuf, is Google's language-neutral, platform-neutral, extensible mechanism for serializing structured data. Protocol Buffers Version 3 (Proto3) was released in 2016. However, the official [tutorials](https://developers.google.com/protocol-buffers/docs/cpptutorial) on the Google protobuf website are still for Proto2. The official [samples](https://github.com/protocolbuffers/protobuf/tree/master/examples) are using Proto3 and CMake, however, its CMake is not standard and many of its macros were not documented on the official CMake website.

In this repository, I re-implemented Google's official Protobuf C++ and Python example using Proto3 and CMake with the best practice. I also put code comments as many as possible to make sure the code is human readable and easy to understand. 

## Dependencies

* Google Protocol Buffers 3.21.9
* CMake 3.14.4+

## Files

```
.
├── CMakeLists.txt
├── docker
│   └── protobuf.Dockerfile
├── examples
│   ├── add_people
│   │   ├── add_people.cc
│   │   └── CMakeLists.txt
│   ├── CMakeLists.txt
│   └── list_people
│       ├── CMakeLists.txt
│       └── list_people.cc
├── LICENSE.md
├── protos
│   ├── addressbook.proto
│   └── CMakeLists.txt
└── README.md
```

## Usages

### Build Docker Image

```bash
$ docker build -f docker/protobuf.Dockerfile --build-arg PROTOBUF_VERSION=21.9 --build-arg NUM_JOBS=8 --tag protobuf-cmake:21.9 .
```

### Run Docker Container

```bash
$ docker run -it --rm -v $(pwd):/mnt protobuf-cmake:21.9
```

### Build Examples

```bash
$ cmake -B build
$ cmake --build build --config Release --parallel
```

All the executable files would be generated in `build/bin` directory.

### Run Examples

The C++ and Python serialization and deserialization can be used interchangeably (C++ serialization + C++ deserialization, C++ serialization + Python deserialization, Python serialization + Python deserialization, Python serialization + C++ deserialization), as the data formats are all generated from the same `proto` file and they are all the same. 

#### Add People Using C++

```bash
$ ./build/bin/add_people build/data.pb # Add people to data
build/data.pb: File not found.  Creating a new file.
Add person to address book? yes | no
yes
Enter person ID number: 
12345
Enter name: 
Lei Mao
Enter email address (blank for none): 
dukeleimao@gmail.com
Enter a phone number (or leave blank to finish): 
+1123456789
Is this a mobile, home, or work phone? mobile | home | work 
home
Enter a phone number (or leave blank to finish): 

Add person to address book? yes | no
yes
Enter person ID number: 
54321
Enter name: 
Andrew Ng
Enter email address (blank for none): 
andrew.ng@stanford.edu
Enter a phone number (or leave blank to finish): 

Add person to address book? yes | no
no
```

#### List People Using C++

```bash
$ python examples-python/add_people.py build/data.pb # Read data
Person ID: 12345
  Name: Lei Mao
  E-mail address: dukeleimao@gmail.com
  Home phone #: +1123456789
  Updated: 2019-06-06T19:07:39Z
Person ID: 54321
  Name: Andrew Ng
  E-mail address: andrew.ng@stanford.edu
  Updated: 2019-06-06T19:08:20Z
```

#### Add People Using Python

```bash
$ python examples-python/list_people.py build/data.pb 
build/data.pb: File not found.  Creating a new file.
Add person to address book? yes | no
yes
Enter person ID number: 12345
Enter name: Lei Mao
Enter email address (blank for none): dukeleimao@gmail.com
Enter a phone number (or leave blank to finish): +1123456789
Is this a mobile, home, or work phone? home
Enter a phone number (or leave blank to finish): 
Add person to address book? yes | no
yes
Enter person ID number: 54321
Enter name: Andrew Ng
Enter email address (blank for none): andrew.ng@stanford.edu
Enter a phone number (or leave blank to finish): 
Add person to address book? yes | no
no
```

#### List People Using Python

```bash
$ python examples-python/list_people.py build/data.pb 
Person ID: 12345
  Name: Lei Mao
  E-mail address: dukeleimao@gmail.com
  Home phone #: +1123456789
Person ID: 54321
  Name: Andrew Ng
  E-mail address: andrew.ng@stanford.edu
```
