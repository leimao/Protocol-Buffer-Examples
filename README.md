# Protocol Buffer Examples

Lei Mao

## Introduction

Protocol Buffer, also known as Protobuf, is Google's language-neutral, platform-neutral, extensible mechanism for serializing structured data. Protocol Buffers Version 3 (Proto3) was released in 2016. However, the official [tutorials](https://developers.google.com/protocol-buffers/docs/cpptutorial) on the Google protobuf website are still for Proto2. The official [samples](https://github.com/protocolbuffers/protobuf/tree/master/examples) are using Proto3 and CMake, however, its CMake is not standard and many of its macros were not documented on the official CMake website.

In this repository, I re-implemented Google's official Protobuf C++ example using Proto3 and CMake with the best practice. I also put code comments as many as possible to make sure the code is human readable and easy to understand. 

## Dependencies

* Google Protocol Buffers 3.8.0
* CMake 3.14.4+

## Files

```
.
├── CMakeLists.txt
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

### Compile

```bash
$ mkdir -p build
$ cd build
$ cmake ..
$ make
```

All the executable files would be generated in `build/bin` directory.

### Run Examples

```bash
$ cd bin

$ ./add_people data.pb # Add people to data
data.pb: File not found.  Creating a new file.
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
andrew.ng@standford.edu
Enter a phone number (or leave blank to finish): 

Add person to address book? yes | no
no

$ ./list_people data.pb # Read data
Person ID: 12345
  Name: Lei Mao
  E-mail address: dukeleimao@gmail.com
  Home phone #: +1123456789
  Updated: 2019-06-06T19:07:39Z
Person ID: 54321
  Name: Andrew Ng
  E-mail address: andrew.ng@standford.edu
  Updated: 2019-06-06T19:08:20Z
```