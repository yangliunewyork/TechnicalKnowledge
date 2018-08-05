__Public-key cryptography__, or __asymmetric cryptography__, is any cryptographic system that uses pairs of keys: public keys which may be disseminated widely, and private keys which are known only to the owner. This accomplishes two functions: authentication, where the public key verifies that a holder of the paired private key sent the message, and encryption, where only the paired private key holder can decrypt the message encrypted with the public key. 

In a public key encryption system, any person can encrypt a message using the receiver's public key. That encrypted message can only be decrypted with the receiver's private key. To be practical, the generation of a public and private key -pair must be computationally economical. The strength of a public key cryptography system relies on the computational effort (work factor in cryptography) required to find the private key from its paired public key. Effective security only requires keeping the private key private; the public key can be openly distributed without compromising security.

Public key cryptography systems often rely on cryptographic algorithms based on mathematical problems that currently admit no efficient solution, particularly those inherent in certain integer factorization, discrete logarithm, and elliptic curve relationships. Public key algorithms, unlike symmetric key algorithms, do not require a secure channel for the initial exchange of one or more secret keys between the parties.[2]

Because of the computational complexity of asymmetric encryption, it is usually used only for small blocks of data, typically the transfer of a symmetric encryption key (e.g. a session key). This symmetric key is then used to encrypt the rest of the potentially long message sequence. The symmetric encryption/decryption is based on simpler algorithms and is much faster.[3]

In a public key signature system, a person can combine a message with a private key to create a short digital signature on the message. Anyone with the corresponding public key can combine a message, a putative digital signature on it, and the known public key to verify whether the signature was valid, i.e. made by the owner of the corresponding private key. Changing the message, even replacing a single letter, will cause verification to fail. In a secure signature system, it is computationally infeasible for anyone who does not know the private key to deduce it from the public key or any number of signatures, or to find a valid signature on any message for which a signature has not hitherto been seen. Thus the authenticity of a message can be demonstrated by the signature, provided the owner of the private key keeps the private key secret.[4][5]

Public key algorithms are fundamental security ingredients in cryptosystems, applications and protocols. They underpin various Internet standards, such as Transport Layer Security (TLS), S/MIME, PGP, and GPG. Some public key algorithms provide key distribution and secrecy (e.g., Diffie–Hellman key exchange), some provide digital signatures (e.g., Digital Signature Algorithm), and some provide both (e.g., RSA).

Public key cryptography finds application in, among others, the information technology security discipline, information security. Information security (IS) is concerned with all aspects of protecting electronic information assets against security threats.[6] Public key cryptography is used as a method of assuring the confidentiality, authenticity and non-repudiability of electronic communications and data storage. 

### Description

Two of the best-known uses of public key cryptography are:

* Public key encryption, in which a message is encrypted with a recipient's public key. The message cannot be decrypted by anyone who does not possess the matching private key, who is thus presumed to be the owner of that key and the person associated with the public key. This is used in an attempt to ensure confidentiality.
* Digital signatures, in which a message is signed with the sender's private key and can be verified by anyone who has access to the sender's public key. This verification proves that the sender had access to the private key, and therefore is likely to be the person associated with the public key. This also ensures that the message has not been tampered with, as a signature is mathematically bound to the message it originally was made with, and verification will fail for practically any other message, no matter how similar to the original message.

An analogy to public key encryption is that of a locked mail box with a mail slot. The mail slot is exposed and accessible to the public – its location (the street address) is, in essence, the public key. Anyone knowing the street address can go to the door and drop a written message through the slot. However, only the person who possesses the key can open the mailbox and read the message.

An analogy for digital signatures is the sealing of an envelope with a personal wax seal. The message can be opened by anyone, but the presence of the unique seal authenticates the sender.

A central problem with the use of public key cryptography is confidence/proof that a particular public key is authentic, in that it is correct and belongs to the person or entity claimed, and has not been tampered with or replaced by a malicious third party. The usual approach to this problem is to use a public key infrastructure (PKI), in which one or more third parties – known as certificate authorities – certify ownership of key pairs. PGP, in addition to being a certificate authority structure, has used a scheme generally called the "web of trust", which decentralizes such authentication of public keys by a central mechanism, and substitutes individual endorsements of the link between user and public key. To date, no fully satisfactory solution to the "public key authentication problem" has been found.

### Example

<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/3/32/Public-key-crypto-1.svg/500px-Public-key-crypto-1.svg.png">

An unpredictable (typically large and random) number is used to begin generation of an acceptable pair of keys suitable for use by an asymmetric key algorithm.

<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/f/f9/Public_key_encryption.svg/500px-Public_key_encryption.svg.png">

In an asymmetric key encryption scheme, anyone can encrypt messages using the public key, but only the holder of the paired private key can decrypt. Security depends on the secrecy of the private key.

<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/4/4c/Public_key_shared_secret.svg/500px-Public_key_shared_secret.svg.png">

In the Diffie–Hellman key exchange scheme, each party generates a public/private key pair and distributes the public key. After obtaining an authentic copy of each other's public keys, Alice and Bob can compute a shared secret offline. The shared secret can be used, for instance, as the key for a symmetric cipher.

<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/a/a7/Private_key_signing.png/500px-Private_key_signing.png">

In this example the message is only signed and not encrypted. 1) Alice signs a message with her private key. 2) Bob can verify that Alice send the message and that the message has not been modified.

### Typical use

Public key cryptography is often used to secure electronic communication over an open networked environment such as the Internet, without relying on a hidden or covert channel, even for key exchange. Open networked environments are susceptible to a variety of communication security problems, such as man-in-the-middle attacks and spoofs. Communication security typically includes requirements that the communication must not be readable during transit (preserving confidentiality), the communication must not be modified during transit (preserving the integrity of the communication), the communication must originate from an identified party (sender authenticity), and the recipient must not be able to repudiate or deny receiving the communication. Combining public key cryptography with an Enveloped Public Key Encryption (EPKE)[14] method, allows for the secure sending of a communication over an open networked environment. In other words, even if an adversary listens to an entire conversation including the key exchange, the adversary would not be able to interpret the conversation.

The distinguishing technique used in public key cryptography is the use of asymmetric key algorithms, where a key used by one party to perform encryption is not the same as the key used by another in decryption. Each user has a pair of cryptographic keys – a public encryption key and a private decryption key. For example, a key pair used for digital signatures consists of a private signing key and a public verification key. The public key may be widely distributed, while the private key is known only to its proprietor. The keys are related mathematically, but the parameters are chosen so that calculating the private key from the public key is unfeasible.

In contrast, symmetric key algorithms use a single secret key, which must be shared and kept private by both the sender (for encryption) and the receiver (for decryption). To use a symmetric encryption scheme, the sender and receiver must securely share a key in advance.

Because symmetric key algorithms are nearly always much less computationally intensive than asymmetric ones, it is common to exchange a key using a key-exchange algorithm, then transmit data using that key and a symmetric key algorithm. PGP and the SSL/TLS family of schemes use this procedure, and are thus called hybrid cryptosystems. 

