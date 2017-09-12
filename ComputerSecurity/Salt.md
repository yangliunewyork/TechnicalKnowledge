* https://en.wikipedia.org/wiki/Salt_(cryptography)

__In cryptography, a salt is random data that is used as an additional input to a one-way function that "hashes" a password or passphrase. Salts are closely related to the concept of nonce. The primary function of salts is to defend against dictionary attacks or against its hashed equivalent, a pre-computed rainbow table attack.__

Salts are used to safeguard passwords in storage. Historically a password was stored in plaintext on a system, but over time additional safeguards developed to protect a user's password against being read from the system. A salt is one of those methods.

A new salt is randomly generated for each password. In a typical setting, the salt and the password (or its version after Key stretching) are concatenated and processed with a cryptographic hash function, and the resulting output (but not the original password) is stored with the salt in a database. Hashing allows for later authentication without keeping and therefore risking the plaintext password in the event that the authentication data store is compromised.

Since salts do not have to be memorized by humans they can make the size of the rainbow table required for a successful attack prohibitively large without placing a burden on the users. Since salts are different in each case, they also protect commonly used passwords, or those who use the same password on several sites, by making all salted hash instances for the same password different from each other.

Cryptographic salts are broadly used in many modern computer systems, from Unix system credentials to Internet security.

# Example usage

Here is a simplified example usage of a salt value for storing passwords. This first table has two username and password combinations. The password is not stored.

```
Username	  Password
user1	      password123
user2	      password123
```

The salt value is generated at random and can be any length, in this case the salt value is 8 bytes (64-bit) long. The hashed value is the hash of the salt value appended to the plaintext password. Both the salt value and hashed value are stored.

```
Username	Salt Value	      String to be Hashed	          Hashed Value = SHA256(Password + Salt Value)
user1	    E1F53135E559C253	password123+E1F53135E559C253	72ae25495a7981c40622d49f9a52e4f1565c90f048f59027bd9c8c8900d5c3d8
user2	    84B03D034B409D4E	password123+84B03D034B409D4E	b4b6603abc670967e99c7e7f1389e40cd16e78ad38eb1468ec2aa1e62b8bed3a
```

As you can see from the hashed value, even though the plaintext passwords are the same, the hashed values are different. This is why the salt value prevents dictionary attacks, with the added benefit that users with the same password won't both be compromised if one password is cracked. While this does protect from an attacker using a leaked database of password hashes to attack other accounts with the same password, it does not protect a user from having their simple (commonly used or easily guessable) password guessed.

The purpose of a hash and salt process in password security is not to prevent a password from being guessed, but to prevent a leaked password database from being used in further attacks.


