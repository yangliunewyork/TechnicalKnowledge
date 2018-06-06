A package manager or package management system is a collection of software tools that automates the process of installing, upgrading, configuring, and removing computer programs for a computer's operating system in a consistent manner.

A package manager deals with packages, distributions of software and data in archive files. Packages contain metadata, such as the software's name, description of its purpose, version number, vendor, checksum, and a list of dependencies necessary for the software to run properly. Upon installation, metadata is stored in a local package database. Package managers typically maintain a database of software dependencies and version information to prevent software mismatches and missing prerequisites. They work closely with software repositories, binary repository managers, and app stores.

Package managers are designed to eliminate the need for manual installs and updates. This can be particularly useful for large enterprises whose operating systems are based on Linux and other Unix-like systems, typically consisting of hundreds or even tens of thousands of distinct software packages.

# Functions

A software package is an archive file containing a computer program as well as necessary metadata for its deployment. The computer program can be in source code that has to be compiled and built first.[3] Package metadata include package description, package version, and dependencies (other packages that need to be installed beforehand).

Package managers are charged with the task of finding, installing, maintaining or uninstalling software packages upon the user's command. Typical functions of a package management system include:

* Working with file archivers to extract package archives
* Ensuring the integrity and authenticity of the package by verifying their digital certificates and checksums
* Looking up, downloading, installing or updating existing software from a software repository or app store
* Grouping packages by function to reduce user confusion
* Managing dependencies to ensure a package is installed with all packages it requires, thus avoiding "dependency hell"

#### Challenges with shared libraries

Computer systems that rely on dynamic library linking, instead of static library linking, share executable libraries of machine instructions across packages and applications. In these systems, complex relationships between different packages requiring different versions of libraries results in a challenge colloquially known as "dependency hell". On Microsoft Windows systems, this is also called "DLL hell" when working with dynamically linked libraries. Good package management is vital on these systems. The Framework system from OPENSTEP was an attempt at solving this issue, by allowing multiple versions of libraries to be installed simultaneously, and for software packages to specify which version they were linked against.

### Comparison with build automation utility

Most software configuration management systems treat building software and deploying software as separate, independent steps. A build automation utility typically takes human-readable source code files already on a computer, and automates the process of converting them into a binary executable package on the same computer. Later a package manager typically running on some other computer downloads those pre-built binary executable packages over the internet and installs them.

However, both kinds of tools have many commonalities. For example, the dependency graph topological sorting used in a package manager to handle dependencies between binary components is also used in a build manager to handle the dependency between source components. For example, many makefiles support not only building executables, but also installing them with make install. For example, every package manager for a source-based distribution – Portage, Sorcery, Homebrew, etc. – supports converting human-readable source code to binary executables and installing it.









