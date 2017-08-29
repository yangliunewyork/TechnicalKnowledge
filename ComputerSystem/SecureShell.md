* https://www.digitalocean.com/community/tutorials/how-to-configure-ssh-key-based-authentication-on-a-linux-server

Secure Shell (SSH) is a cryptographic network protocol for operating network services securely over an unsecured network. The best known example application is for remote login to computer systems by users.

SSH provides a secure channel over an unsecured network in a client-server architecture, connecting an SSH client application with an SSH server. Common applications include remote command-line login and remote command execution, but any network service can be secured with SSH. The protocol specification distinguishes between two major versions, referred to as SSH-1 and SSH-2.

### Definition

SSH uses public-key cryptography to authenticate the remote computer and allow it to authenticate the user, if necessary. 

There are several ways to use SSH; one is to use automatically generated public-private key pairs to simply encrypt a network connection, and then use password authentication to log on.

Another is to use a manually generated public-private key pair to perform the authentication, allowing users or programs to log in without having to specify a password. In this scenario, anyone can produce a matching pair of different keys (public and private). __The public key is placed on all computers that must allow access to the owner of the matching private key (the owner keeps the private key secret).__ While authentication is based on the private key, the key itself is never transferred through the network during authentication. SSH only verifies whether the same person offering the public key also owns the matching private key. In all versions of SSH it is important to verify unknown public keys, i.e. associate the public keys with identities, before accepting them as valid. Accepting an attacker's public key without validation will authorize an unauthorized attacker as a valid user.

__Note that we can use public-key to encrypt message and private-key to decript message, while we can also use private-key to encrypt message and public-key to decript message. Which way we should choose depeneds on the actual context.__

### How SSH works
Secure Shell (SSH) keys are based on the principle of Public-key cryptography.

#### In a nutshell: 

__A pair of encryption keys are generated which are mathematically linked to each other: a private key and a public key. The public key is used to encrypt a message whereas the private key is used to decrypt it. This provides a very nice property which allows anyone having access to the public key to encrypt a message that can only be decrypted by someone with access to the private key.__ 

__The inverse of this property is used for creating *digital signatures* in which a sender uses the private key to digitally sign a message and a receiver uses the corresponding public key (which has been verified via other channels to belong to the sender) to verify the signature. The receiver can then be confident that the message was indeed from someone with access to the private key. This forms the basis of public key authentication.__

#### The SSH protocol uses keys for authentication in two ways: 

##### Authenticating users  
This is where the SSH server verifies the identity of the user that is connecting. SSH offers various methods of authenticating users. Password authentication is the most common one but public key authentication is another.
When using public key authentication the SSH server checks if the user trying to authenticate to an account that has an authorized public key is in possession of the corresponding private key. Keys used for this purpose are referred to as SSH user keys.

##### Authenticating servers  
This is where the SSH client verifies the identity of the SSH server. Allows users connecting to a server to verify that this is in fact the same SSH server I connected to the last time or that this is indeed the server that it claims to be (basically to prevent a Man-in-the-middle attack). Keys used for this purpose are referred to as SSH host keys.

When referring to SSH keys the speaker could be referring to either of these (user keys or host keys). Most often than not (unless you’re a system administrator) when someone talks about SSH keys they’re generally referring to user keys.

While the public key is meant to be shared (in the case of SSH keys copied to the SSH server under a particular location) the private key is, as it’s name implies, meant to be kept private as anyone having access to the private key would be able to decrypt and sign messages on the owner’s behalf. Some general guidelines for protecting a private key are ensuring secure file system permissions (when the key is stored on disk) and generally not copying it from the system where it was generated. It’s also possible (and highly recommended) to encrypt SSH keys with a passphrase. Doing so will prevent someone who managed to get a copy of the private key of using it without having to also know the passphrase.

One additional and interesting note regarding SSH keys is that using SSH keys in user authentication actually provides better protection (than for example password authentication) against a Man-in-the-middle attack in the case where the attacker has compromised the SSH server. This has to do with the way session identifiers are calculated when using public key authentication.

### Key management

On Unix-like systems, the list of authorized public keys is typically stored in the home directory of the user that is allowed to log in remotely, in the file ~/.ssh/authorized_keys.[7] This file is respected by SSH only if it is not writable by anything apart from the owner and root. When the public key is present on the remote end and the matching private key is present on the local end, typing in the password is no longer required (some software like Message Passing Interface (MPI) stack may need this password-less access to run properly). However, for additional security the private key itself can be locked with a passphrase.

The private key can also be looked for in standard places, and its full path can be specified as a command line setting (the option -i for ssh). The ssh-keygen utility produces the public and private keys, always in pairs.

SSH also supports password-based authentication that is encrypted by automatically generated keys. In this case the attacker could imitate the legitimate server side, ask for the password, and obtain it (man-in-the-middle attack). However, this is possible only if the two sides have never authenticated before, as SSH remembers the key that the server side previously used. The SSH client raises a warning before accepting the key of a new, previously unknown server. Password authentication can be disabled.

### How To Configure SSH Key-Based Authentication on a Linux Server

An SSH server can authenticate clients using a variety of different methods. The most basic of these is password authentication, which is easy to use, but not the most secure.

Although passwords are sent to the server in a secure manner, they are generally not complex or long enough to be resistant to repeated, persistent attackers. Modern processing power combined with automated scripts make brute forcing a password-protected account very possible. Although there are other methods of adding additional security (fail2ban, etc.), SSH keys prove to be a reliable and secure alternative.

SSH key pairs are two cryptographically secure keys that can be used to authenticate a client to an SSH server. Each key pair consists of a public key and a private key.

The private key is retained by the client and should be kept absolutely secret. Any compromise of the private key will allow the attacker to log into servers that are configured with the associated public key without additional authentication. As an additional precaution, the key can be encrypted on disk with a passphrase.

The associated public key can be shared freely without any negative consequences. The public key can be used to encrypt messages that only the private key can decrypt. This property is employed as a way of authenticating using the key pair.

The public key is uploaded to a remote server that you want to be able to log into with SSH. The key is added to a special file within the user account you will be logging into called ~/.ssh/authorized_keys.

When a client attempts to authenticate using SSH keys, the server can test the client on whether they are in possession of the private key. If the client can prove that it owns the private key, a shell session is spawned or the requested command is executed.

An overview of the flow is shown in this diagram:

![alt](https://assets.digitalocean.com/articles/ssh_key_overview/ssh-key-auth-flow.png)

The Secure Shell (SSH) system can be configured to allow the use of different types of authentication.  The usual sort of authentication requires you to authenticate with a password, but you can also authenticate using Public-key Cryptography.  You do this by generating a SSH key pair, consisting of a public key and a private key.  You keep the __private key on your own system__, or on the system you're __connecting from__, and you copy the __public key__ to the system you're __connecting to__.  (Note that these keys are only used for authentication purposes, and play no role once the connection is established.)


