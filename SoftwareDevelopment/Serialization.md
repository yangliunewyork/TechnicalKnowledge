# What is serialization

In computer science, in the context of data storage, __serialization__ is the process of _translating data structures or object state into a format that can be stored (for example, in a file or memory buffer) or transmitted (for example, across a network connection link) and reconstructed later (possibly in a different computer environment)_. When the resulting series of bits is reread according to the serialization format, it can be used to create a semantically identical clone of the original object. For many complex objects, such as those that make extensive use of references, this process is not straightforward. Serialization of object-oriented objects does not include any of their associated methods with which they were previously linked.

This process of serializing an object is also called __marshalling__ an object. The opposite operation, extracting a data structure from a series of bytes, is __deserialization__ (which is also called __unmarshalling__).

# Uses

* A method of transferring data through the wires (messaging).  
* A method of storing data (in databases, on hard disk drives).  
* A method of remote procedure calls, e.g., as in SOAP.  
* A method for distributing objects, especially in component-based software engineering such as COM, CORBA, etc.  
* A method for detecting changes in time-varying data.  

For some of these features to be useful, architecture independence must be maintained. For example, for maximal use of distribution, a computer running on a different hardware architecture should be able to reliably reconstruct a serialized data stream, regardless of endianness. This means that the simpler and faster procedure of directly copying the memory layout of the data structure cannot work reliably for all architectures. Serializing the data structure in an architecture independent format means preventing the problems of byte ordering, memory layout, or simply different ways of representing data structures in different programming languages.

Inherent to any serialization scheme is that, because the encoding of the data is by definition serial, extracting one part of the serialized data structure requires that the entire object be read from start to end, and reconstructed. In many applications this linearity is an asset, because it enables simple, common I/O interfaces to be utilized to hold and pass on the state of an object. In applications where higher performance is an issue, it can make sense to expend more effort to deal with a more complex, non-linear storage organization.

Even on a single machine, primitive pointer objects are too fragile to save because the objects to which they point may be reloaded to a different location in memory. To deal with this, the serialization process includes a step called unswizzling or pointer unswizzling, where direct pointer references are converted to references based on name or position. The deserialization process includes an inverse step called pointer swizzling.

Since both serializing and deserializing can be driven from common code (for example, the Serialize function in Microsoft Foundation Classes), it is possible for the common code to do both at the same time, and thus, 1) detect differences between the objects being serialized and their prior copies, and 2) provide the input for the next such detection. It is not necessary to actually build the prior copy because differences can be detected on the fly. The technique is called differential execution. It is useful in the programming of user interfaces whose contents are time-varying — graphical objects can be created, removed, altered, or made to handle input events without necessarily having to write separate code to do those things.


