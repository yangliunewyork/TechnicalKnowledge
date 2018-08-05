https://technet.microsoft.com/en-us/library/bb123848(v=exchg.65).aspx. 

Although public key cryptography simplifies key management by allowing one key pair to be used by many people, there is a problem: how to distribute a public key so that the user can find it and know that it is valid.

### Understanding Digital Certificates and Public Key Cryptography

A digital certificate is a digital form of identification, much like a passport or driver's license. A digital certificate is a digital credential that provides information about the identity of an entity as well as other supporting information. A digital certificate is issued by an authority, referred to as a certification authority (CA). Because a digital certificate is issued by a certification authority, that authority guarantees the validity of the information in the certificate. Also, a digital certificate is valid for only a specific period of time.

Digital certificates provide support for public key cryptography because digital certificates contain the public key of the entity identified in the certificate. Because the certificate matches a public key to a particular individual, and that certificate's authenticity is guaranteed by the issuer, the digital certificate provides a solution to the problem of how to find a user's public key and know that it is valid. These problems are solved by a user obtaining another user's public key from the digital certificate. The user knows it is valid because a trusted certification authority has issued the certificate.

In addition, digital certificates rely on public key cryptography for their own authentication. When a digital certificate is issued, the issuing certification authority signs the certificate with its own private key. To validate the authenticity of a digital certificate, a user can obtain that certification authority's public key and use it against the certificate to determine if it was signed by the certification authority.

##### Understanding How Digital Certificates Are Structured

For a digital certificate to be useful, it has to be structured in an understandable and reliable way so that the information within the certificate can be easily retrieved and understood. For example, passports follow a similar structure allowing people to easily understand the information in a type of passport that they may never have seen before. In the same way, as long as digital certificates are standardized, they can be read and understood regardless of who issued the certificate.

The S/MIME standard specifies that digital certificates used for S/MIME conform to the International Telecommunications Union (ITU) X.509 standard. S/MIME version 3 specifically requires that digital certificates conform to version 3 of X.509. Because S/MIME relies on an established, recognized standard for the structure of digital certificates, the S/MIME standard builds on that standard's growth and thus increases its acceptance.

The X.509 standard specifies that digital certificates contain standardized information. Specifically, X.509 version 3 certificates contain the following fields:

* Version number   The version of the X.509 standard to which the certificate conforms.
* Serial number   A number that uniquely identifies the certificate and is issued by the certification authority.
* Certificate algorithm identifier   The names of the specific public key algorithms that the certification authority has used to sign the digital certificate.
* Issuer name   The identity of the certification authority who actually issued the certificate.
* Validity period   The period of time for which a digital certificate is valid and contains both a start date and an expiration date.
* Subject name   The name of the owner of the digital certificate.
* Subject public key information   The public key that is associated with the owner of the digital certificate and the specific public key algorithms associated with the public key.
* Issuer unique identifier   Information that can be used to uniquely identify the issuer of the digital certificate.
* Subject unique identifier   Information that can be used to uniquely identify the owner of the digital certificate.
* Extensions   Additional information that is related to the use and handling of the certificate.
* Certification authority's digital signature   The actual digital signature made with the certification authority's private key using the algorithm specified in the certificate algorithm identifier field.  

##### Digital Certificates and Public Key Infrastructure

One of the benefits of public key cryptography is that it reduces key management because one key pair takes the place of numerous symmetric keys. This benefit is further enhanced by digital certificates, which allow public keys to be distributed and managed. However, digital certificates are not self-managing. By design, digital certificates are widely circulated, so the management of these certificates must address the distributed nature of digital certificates. Digital certificates require a functioning infrastructure to manage the certificates in the context within which they are going to be used. Public key infrastructure (PKI) is inseparable from digital certificates. PKI is responsible for issuing certificates, ensuring the distribution of these certificates through a directory, and validating certificates. PKI is responsible for the underlying work that supports digital certificates and enables them to provide the capabilities that services such as S/MIME rely on.

Because of the size and complexity of the topic, PKI is beyond the scope of this book. The information presented here focuses on how PKI and digital certificates work in conjunction with message security. There are many excellent resources that address PKI. You can obtain more information about PKI from your PKI vendor's documentation and from other PKI-specific sources.

### How PKI Works with Message Security



PKI provides the means for digital certificates to be used by issuing certificates and making them accessible through a directory. PKI also validates digital certificates by verifying the authenticity of the certificate, the validity of the certificate, and that the certificate is trustworthy. These services are crucial to digital certificates because digital certificates rely on a distributed model by using third-party certification authorities.

The specific way that digital certificates are issued and published to a directory depends on the specific PKI product and its implementation. In general, PKI issues digital certificates and publishes information about these certificates to a directory where that information can be accessed by other applications. Some of this information is used for validating digital certificates. As discussed in "Putting Public Key Cryptography Together with Message Security" in Understanding Public Key Cryptography, message security operations require access to the public keys of both senders and recipients. Because the digital certificate provides this information, accessing users' digital certificates is crucial to a message security system. By providing access to digital certificates, PKI builds on the benefits that public key cryptography offers in terms of simplified key management by eliminating the need to manually exchange keys. Instead, PKI makes digital certificates available through a directory so that they can be retrieved by applications when needed.

To understand how PKI validates a certificate, remember the role that the certification authority has in issuing the digital certificate. As discussed in "Understanding Digital Certificates and Public Key Cryptography" earlier in this topic, the issuing certification authority vouches for the validity of the identity, and shows this by using its public key to sign the digital certificate. Checking the authenticity of a certificate means that the certification authority's digital signature must be verified. PKI validates a certificate by providing the means by which the issuing certificate authority's signature can be verified. If the signature cannot be verified, the certificate is known to be untrustworthy.

As mentioned in at the beginning of this topic, no security method is perfect. A digital certificate can be compromised, usually by loss of the private key. For digital certificates to be trustworthy, there must be a way to cancel or "revoke" a digital certificate before its expiration, much like a stolen credit card can be canceled. Certificate revocation is another of the critical services that PKI provides to support digital certificates and is another part of the process of verifying the digital certificate.

Because PKI ensures that digital certificates are trustworthy, PKI is an integral part of digital certificates. You cannot use digital signatures without PKI. Because Exchange Server 2003 supports X.509 v3 certificates, the specific PKI that supports an Exchange installation will depend on the digital certificates used with Exchange. From the standpoint of message security, however, all PKIs provide these fundamental services in support of digital certificates. The differences between specific PKIs are implementation and design related, and are specific to each PKI deployment.


# Putting Digital Certificates Together with Message Security

### How Digital Certificates Are Used for Digital Signatures

As discussed in "Public Key Cryptography and Digital Signatures" in Understanding Public Key Cryptography, the relationship of a public key to a user's private key allows a recipient to authenticate and validate a sender's message. Digital certificates provide support to public key cryptography by providing a reliable means to distribute and access public keys. When a sender is signing a message, the sender provides the private key that is associated with the public key available on the digital certificate. In turn, when the recipient is validating a digital signature on a message, the recipient is obtaining the public key to perform that operation from the sender's digital certificate. The following figure shows the sequence of signing with the addition of the supporting elements of digital certificates. 

#### Digital certificates and digital signing of an e-mail message

<img src="https://i-technet.sec.s-msft.com/dynimg/IC140896.gif">

1. Message is captured.
2. Hash value of the message is calculated.
3. Sender's private key is retrieved from the sender's digital certificate.
4. Hash value is encrypted with the sender's private key.
5. Encrypted hash value is appended to the message as a digital signature.
6. Message is sent.

The following figure shows the sequence of verifying with the addition of the supporting elements of digital certificates. 

##### Digital certificates and verifying a digital signature of an e-mail message

<img src="https://i-technet.sec.s-msft.com/dynimg/IC123447.gif">



1. Message is received.
2. Digital signature containing encrypted hash value is retrieved from the message.
3. Message is retrieved.
4. Hash value of the message is calculated.
5. Sender's public key is retrieved from the sender's digital certificate.
6. Encrypted hash value is decrypted with the sender's public key.
7. Decrypted hash value is compared against the hash value produced on receipt.
8. If the values match, the message is valid.

### How Digital Certificates Are Used for Message Encryption

Just as digital certificates support digital signatures by making public keys available for the verification process, digital certificates also support message encryption by making public keys available so that the keys can be used for the encryption process. As discussed in "Public Key Cryptography and Message Encryption" in Understanding Public Key Cryptography, a sender can access the recipient's public key, which allows the sender to encrypt the message, knowing that only the recipient can decrypt the message. This time it is the recipient's digital certificate that makes the encryption possible. As with digital signatures, the public key from the digital certificate makes the operation possible. The following figure shows the sequence of encrypting with the supporting elements of digital certificates. 

##### Digital certificates and encryption of an e-mail message

<img src="https://i-technet.sec.s-msft.com/dynimg/IC30294.gif">



1. Message is captured.
2. Public key is retrieved from the recipient's digital certificate.
3. One-time symmetric session key is generated.
4. Encryption operation is performed on the message using the session key.
5. Session key is encrypted using the recipient's public key.
6. Encrypted session key is included with the encrypted message.
7. Message is sent.

##### Digital certificates and decrypting a an e-mail message

<img src="https://i-technet.sec.s-msft.com/dynimg/IC46408.gif">

1. Message is received.
2. Encrypted message and encrypted session key are retrieved from the message.
3. Recipient's private key is retrieved from the recipient's digital certificate.
4. Session key is decrypted with the recipient's private key from the recipient's digital certificate.
5. Message is decrypted with the decrypted session key.
6. Unencrypted message is returned to the recipient.

##### How Digital Certificates Are Used for Digital Signatures and Message Encryption

Digital signatures and message encryption complement one another. The following figure shows the sequence of signing and encrypting with the addition of the supporting elements of a digital signature. 

<img src="https://i-technet.sec.s-msft.com/dynimg/IC96458.gif">

1. Message is captured.
2. Hash value of the message is calculated.
3. Sender's private key is retrieved from the sender's digital certificate.
4. Recipient's public key is retrieved from the recipient's digital certificate.
5. Hash value is encrypted with the sender's private key.
6. Encrypted hash value is appended to the message as a digital signature.
7. One-time symmetric session key is generated.
8. Encryption operation is performed on the message using a session key.
9. Session key is encrypted using the recipient's public key.
10. Encrypted session key is included with the encrypted message.
11. Message is sent.

##### Digital certificates and decrypting an e-mail message and verifying a digital signature

<img src="https://i-technet.sec.s-msft.com/dynimg/IC130504.gif">

1. Message is received.
2. Encrypted message and encrypted session key are retrieved from the message.
3. Recipient's private key is retrieved from the recipient's digital certificate.
4. Session key is decrypted with recipient's private key from the recipient's digital certificate.
5. Message is decrypted with the decrypted session key.
6. Digital signature containing encrypted hash value is retrieved from the message.
7. Hash value of the message is calculated.
8. Sender's public key is retrieved from the sender's digital certificate.
9. Encrypted hash value is decrypted with the sender's public key.
10. Decrypted hash value is compared against the hash value produced on receipt.
11. If the values match, the message is valid.
12. Unencrypted message is returned to the recipient.
