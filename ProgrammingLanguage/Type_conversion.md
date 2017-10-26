In computer science, __type conversion__, __type casting__, and __type coercion__ are different ways of changing an entity of one data type into another. An example would be the conversion of an integer value into a floating point value or its textual representation as a string, and vice versa. Type conversions can take advantage of certain features of type hierarchies or data representations. _Two important aspects of a type conversion is whether it happens implicitly or explicitly, and whether the underlying data representation is converted from one representation into another, or a given representation is merely reinterpreted as the representation of another data type._ In general, both primitive and compound data types can be converted.

Each programming language has its own rules on how types can be converted. Languages with __strong typing__ typically do little implicit conversion and discourage the reinterpretation of representations, while languages with __weak typing__ perform many implicit conversions between data types. Weak typing language often allow forcing the compiler to arbitrarily interpret a data item as having different representations—this can be a non-obvious programming error, or a technical method to directly deal with underlying hardware.

In most languages, the word coercion is used to denote an implicit conversion, either during compilation or during run time. For example, in an expression mixing integer and floating point numbers (like 5 + 0.1), the compiler will automatically convert integer representation into floating point representation so fractions are not lost. Explicit type conversions are either indicated by writing additional code (e.g. adding type identifiers or calling built-in routines) or by coding conversion routines for the compiler to use when it otherwise would halt with a type mismatch.

In most ALGOL-like languages, such as Pascal, Modula-2, Ada (programming language) and Delphi, conversion and casting are distinctly different concepts. In these languages, conversion refers to either implicitly or explicitly changing a value from one data type storage format to another, e.g. a 16-bit integer to a 32-bit integer. The storage needs may change as a result of the conversion, including a possible loss of precision or truncation. The word cast, on the other hand, refers to explicitly changing the interpretation of the bit pattern representing a value from one type to another. For example, 32 contiguous bits may be treated as an array of 32 booleans, a 4-byte string, an unsigned 32-bit integer or an IEEE single precision floating point value. Because the stored bits are never changed, the programmer must know low level details such as representation format, byte order, and alignment needs, to meaningfully cast.

In the C family of languages and ALGOL 68, the word cast typically refers to an explicit type conversion (as opposed to an implicit conversion), causing some ambiguity about whether this is a re-interpretation of a bit-pattern or a real data representation conversion. More important is the multitude of ways and rules that apply to what data type (or class) is located by a pointer and how a pointer may be adjusted by the compiler in cases like object (class) inheritance.













