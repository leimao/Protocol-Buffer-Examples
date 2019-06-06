---
layout: post
title: "Google ProtoBuffer"
excerpt: "Beginner's Trial"
modified: 2019-05-23T14:17:25-04:00
categories: blog
tags: [Software Engineering]
comments: true
share: true
---

### Introduction

Installation guide:
https://github.com/protocolbuffers/protobuf/blob/master/src/README.md


I was installing the `all` version so it was a little bit slow.
To accelerate the installation process.

```
$ ./configure
$ make -j16
$ make check -j16
$ sudo make install
$ sudo ldconfig # refresh shared library cache.
```

Protocol Buffer Libraries were installed to `/usr/local/lib` by default.

```
$ protoc --version
libprotoc 3.8.0
```


[vscode-proto3](https://marketplace.visualstudio.com/items?itemName=zxh404.vscode-proto3) plugin.

### References

* [Protocol Buffer Official Website](https://developers.google.com/protocol-buffers/)
* [Protocol Buffer C++ Tutorial](https://developers.google.com/protocol-buffers/docs/cpptutorial)




