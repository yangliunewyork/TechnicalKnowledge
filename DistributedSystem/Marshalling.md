### Introduction
In computer science, marshalling or marshaling is the process of transforming the memory representation of an object to a data format suitable for storage or transmission, and it is typically used when data must be moved between different parts of a computer program or from one program to another. Marshalling is similar to serialization and is used to communicate to remote objects with an object, in this case a serialized object. It simplifies complex communication, using custom/complex objects to communicate instead of primitives. The opposite, or reverse, of marshalling is called unmarshalling (or demarshalling, similar to deserialization).

### Usage
Marshalling is used within implementations of different remote procedure call (RPC) mechanisms, where it is necessary to transport data between processes and/or between threads.

### Comparison with serialization
To "serialize" an object means to convert its state into a byte stream in such a way that the byte stream can be converted back into a copy of the object.
The term "marshal" is considered to be synonymous with "serialize" in the Python standard library,[5] but the terms are not synonymous in the Java-related RFC 2713:
To "marshal" an object means to record its state and codebase(s)[note 1] in such a way that when the marshalled object is "unmarshalled," a copy of the original object is obtained, possibly by automatically loading the class definitions of the object. You can marshal any object that is serializable or remote (that is, implements the java.rmi.Remote interface). Marshalling is like serialization, except marshalling also records codebases. Marshalling is different from serialization in that marshalling treats remote objects specially.

To "serialize" an object means to convert its state into a byte stream in such a way that the byte stream can be converted back into a copy of the object.

So, marshalling also saves the code of an object in the byte stream in addition to its state.

