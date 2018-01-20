# Salt 

https://www.iamle.com/archives/1541.html  

https://en.wikipedia.org/wiki/Salt_(cryptography)  

https://www.addedbytes.com/blog/why-you-should-always-salt-your-hashes  

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


### Usage

The reason that __salts__ are used is that people tend to choose the same passwords, and not at all randomly. Many used passwords out there are short real words, to make it easy to remember, but this also enables for an attack.

As you may know, passwords are generally not stored in cleartext, but rather hashed. If you are unsure of the purpose of a hash-function, please read up on that first.

Now, what the attackers can do is to simply generate a list of common passwords and their corresponding hashes. Comparing the hashes that a site has stored with the table will, if common passwords are being used, reveal the passwords to the attacker.

A salt is simply added to make a common password uncommon. A salt value is generated at random and can be fairly small, the only purpose is to lower the probability that the hash-value will be found in any pre-calculated table. A common way to combine the salt and the password is to simply concatenate them, i.e. the stored hash value is Hash(salt||password). The common password password1 now magically becomes, e.g., 6$dK,3password1 and is very unlikely to be found in a table.

The salt can be stored completely in the clear in the database, next to the hashed value. Once the attacker has the database and wants to find the passwords, he needs to generate the pre-calculated table for each salt individually, a costly operation.

Yet another way to defend against this kind of attack is to slow down the attacker. This can be achieved by iterating the hash-function many times, i.e. storing Hash(Hash(Hash(Hash…(Hash(salt||password)))…). Also, a __pepper__ can be used, which is another random value concatenated to the password, such that the stored value is Hash(pepper||salt||password). The pepper is then not stored at all and therefore all possible values of the pepper need to be tested when trying to log in. Using 8 bits for the pepper give 256 possible values, which is very fast when the true user tries to log in. However the attack will work 256 times slower since all pepper values need to be tested for each password!

# encryption, hashing, and salting

Without going into too technical and mathematical detail, it might be useful to explain a little bit about the difference between _encryption_, _hashing_, and _salting_.

### Encryption

Encryption has been around for an awfully long time. The Egyptions used it to create mystery and amusement, and the Romans used it to send secret messages. When you encrypt a password, you apply some sort of algorithm which scrambles it up. Applying the key, unscrambles it.

ROT13 is a simple example of an encryption algorithm. It basically replaces each letter with one 13 places away in the alphabet.

```
Don't drink the wine. 
    = Qba'g qevax gur jvar.
```

ROT13 is obviously quite a weak algorithm, but it's useful to illustrate the key point here - Encrypted data is reversible. It's like that by design. __There's no point encrypting a secret message if the person at the other end is unable to decipher it. Therefore, it's useful for things like credit card numbers, or emails. The web browser you're reading this on is also using encryption.__

The server encrypts the data, sends it over a secure SSL connection to your browser, which decrypts it so you can read it.

### Hashing

__Hashing is different from encryption in that once the data is encoded, it can't be decoded. Well, at least it's extremely difficult to do so. Unlike encryption, the output is always of a fixed length, depending on the algorithm you use.__

Using our phrase from before, and the MD5 algorithm we get ...

```
Don't drink the wine. 
    = b290557177ec5dd7098d1de84616dd04
```

If we try a longer phrase ...

```
Please don't drink the wine, it tastes terrible. 
    = fd870b20869d9ae05d84e3d7fbed0c94
```

You will see that the results are both the same length. This means, that multiple inputs could result in the same output, called a _collission_.

__Hashing is useful when storing things which you don't need to read back, but you need to check. Passwords are the primary example. Instead of storing the clear text, you store the hashed version. Then, when someone types in their password, you apply the same hashing algorithm and compare it with what you have in the database. If they match, then the gates open.__

Hash functions can also be used to test whether information has been tampered with. When sending an email, you first share a secret value that only you and the receiver know of. Before sending the email, you sign it with your secret value and produce the hash value. Then send your clear text email (without the secret value) along with the hash value. Your friend can then do the same process and if the hashes are the same, then they know your message hasn't been tampered with along the way. This technique is called Message Authentication Code or Hash Based Message Authentication Code.

__The important factor for hashing algorithms is that they only work one way. The only way to work out the original value, is by brute force. Trying multiple values to see if they produce the same hash.__

This is particularly problematic with passwords which are generally short and use commonly found words. It wouldn't take a modern computer very long to run through a large dictionary (or use existing rainbow tables) and figure out the hashed result of every common password.

That's where salting comes in.

### Salting
Beside clogging up your arteries, salts can clog up anyone trying to crack a hashed password. They work by adding an extra secret value to the end of the input, extending the length of the original password.

Say your password is rocky and the salt value is i.love.salt. The hash value would be made up from both of these together rockyi.love.salt. This provides some protection for those people who use common words as their password. However, if someone learns of the salt value you use, then they just add it to the end (or start) of each dictionary word they try in their attack.

To make this more difficult you can use random salts, one for each password. It obviously needs to be stored in the database somewhere matched up with the user account, but it does make brute force attacking much more difficult. Finally, you can create a salt from multiple parts, you can use the current date-time, the username, a secret phrase, a random value, or a combination of all of these.

