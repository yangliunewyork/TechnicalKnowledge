A digital signature is a mathematical scheme for presenting the authenticity of digital messages or documents. A valid digital signature gives a recipient reason to believe that the message was created by a known sender (authentication), that the sender cannot deny having sent the message (__non-repudiation__), and that the message was not altered in transit (integrity).

Digital signatures are a standard element of most cryptographic protocol suites, and are commonly used for software distribution, financial transactions, contract management software, and in other cases where it is important to detect forgery or tampering.

Digital signatures are often used to implement __electronic signatures__, a broader term that refers to any electronic data that carries the intent of a signature, but not all electronic signatures use digital signatures.

Digital signatures employ asymmetric cryptography. In many instances they provide a layer of validation and security to messages sent through a non-secure channel: Properly implemented, a digital signature gives the receiver reason to believe the message was sent by the claimed sender. Digital seals and signatures are equivalent to handwritten signatures and stamped seals. Digital signatures are equivalent to traditional handwritten signatures in many respects, but properly implemented digital signatures are more difficult to forge than the handwritten type. Digital signature schemes, in the sense used here, are cryptographically based, and must be implemented properly to be effective. Digital signatures can also provide non-repudiation, meaning that the signer cannot successfully claim they did not sign a message, while also claiming their private key remains secret. Further, some non-repudiation schemes offer a time stamp for the digital signature, so that even if the private key is exposed, the signature is valid. Digitally signed messages may be anything representable as a bitstring: examples include electronic mail, contracts, or a message sent via some other cryptographic protocol.

<img src="https://upload.wikimedia.org/wikipedia/commons/thumb/a/a7/Private_key_signing.png/375px-Private_key_signing.png">

In this example the message is only signed and not encrypted. 1) Alice signs a message with her private key. 2) Bob can verify that Alice sent the message and that the message has not been modified.

### How does a Digital Signature Work?

The digital signature can be considered as a numerical value that is represented as a sequence of characters. The creation of a digital signature is a complex mathematical process that can only be created by a computer.

Consider a scenario where Alice has to digitally sign a file or an email and send it to Bob.

1. Alice selects the file to be digitally signed or clicks on 'sign' in her email application  
2. The hash value of the file content or the message is calculated by Alice's computer  
3. This hash value is encrypted with Alice's Signing Key (which is a Private Key) to create the Digital Signature.  
4. Now, the original file or email message along with its Digital Signature are sent to Bob.  
5. After Bob receives the signed message, the associated application (such as email application) identifies that the message has been signed. Bob's computer then proceeds to:  
  * Decrypt the Digital Signature using Alice's Public Key
  * Calculate the hash of the original message
  * Compare the (a) hash it has computed from the received message with the (b) decrypted hash received with Alice's message.
6. Any difference in the hash values would reveal tampering of the message.  

<img src="https://www.instantssl.com/images/digital-signature.png">

#### How do I create a Digital Signature?

You can obtain a digital signature from a reputable certificate authority such as Comodo, or you can create it yourself. You need a digital certificate to digitally sign a document. However, if you create and use a self-signed certificate the recipients of your documents will not be able to verify the authenticity of your digital signature. They will have to manually trust your self-signed certificate.

If you want the recipients of your documents to be able to verify the authenticity of your digital signature then you must obtain a digital certificate from a reputable CA. After downloading and installing the certificate - you will be able to use the 'Sign' and 'Encrypt' buttons on your mail client to encrypt and digitally sign your emails. This makes more sense in a business scenario, as it assures the recipient that it was genuinely sent by you and not by some impersonator.


